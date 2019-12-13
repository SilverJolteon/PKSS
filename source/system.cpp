#include "system.h"

std::string SYS::getString(std::string description){
	SwkbdState state;
	char* input = new char[64];
	
	swkbdInit(&state, SWKBD_TYPE_QWERTY, 2, 64);
	swkbdSetHintText(&state, description.c_str());

	swkbdInputText(&state, input, 64);
	
	std::string name(input);
	char symbols[] = {'.', ',', '/', '\\', '<', '>', ':', '"', '|', '?', '*'};
	for(unsigned int i = 0; i < name.length(); i++){
		for(int j = 0; j < 11; j++){
			if(name[i] == symbols[j]) name[i] = ' ';
		}
	}
	if(name[name.length() - 1] == ' ') name.erase(name.length() - 1, name.length());
	
	return name;
}

void SYS::selectGame(game_t* &game){
	FS_Path game_binpath;
	uint32_t lowerid = (uint32_t)(game->titleid);
	uint32_t upperid = (uint32_t)(game->titleid >> 32);
	uint32_t path[3] = {mediatype, lowerid, upperid};
	game_binpath = (FS_Path){PATH_BINARY, 12, path};
	FSUSER_OpenArchive(&game_arch, ARCHIVE_USER_SAVEDATA, game_binpath);
}

int SYS::backupSave(game_t* &game, std::string savename){
	FS::directory(SAVE_PATH + "/" + game->name, CREATE_DIR);
	std::string savepath = SAVE_PATH + "/" + game->name + "/" + savename;
	FS::directory(savepath, DELETE_DIR);
	FS::directory(savepath, CREATE_DIR);
	
	file_t files = FS::getFiles(game_arch, "/");
	
	if(files.num > 0){
		for(int i = 0; i < files.num; i++){
			char* buffer = FS::fileToBuffer(game_arch, "/", files.data[i]);
			std::string filepath = "/" + files.data[i];
			uint64_t size = FS::int82uint64(game_arch, filepath);
			FS::bufferToFile(sdmc_arch, buffer, size, savepath, files.data[i]);
			free(buffer);
		}
	}
	
	int index = game->getIndex();
	bool previous = false;
	int pre_index;
	for(size_t i = 0; i < savelist[index].size(); i++){
		if(!savename.compare(savelist[index][i]->name)){
			previous = true;
			pre_index = i;
		}
	}
	if(!previous){
		savelist[index].push_back(new save_t(savename));
		savelist[index][savelist[index].size()-1]->setCurrent(index);
	}
	else{
		savelist[index][pre_index]->setCurrent(index);
	}
	CFG::writeConfig();
	return 0;
}

void SYS::restoreSave(game_t* &game, save_t* &save){
	if(save == NULL) return;
	std::string savepath = SAVE_PATH + "/" + game->name + "/" + save->name + "/";
	FSUSER_OpenArchive(&sdmc_arch, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	
	file_t sdmc_files = FS::getFiles(sdmc_arch, savepath);
	file_t game_files = FS::getFiles(game_arch, "/");
	if(sdmc_files.num > 0){
		for(int i = 0; i < game_files.num; i++){
			std::string filepath = "/" + game_files.data[i];
			FSUSER_DeleteFile(game_arch, fsMakePath(PATH_ASCII, filepath.c_str()));
		}
	}
	for(int i = 0; i < sdmc_files.num; i++){
		char* buffer = FS::fileToBuffer(sdmc_arch, savepath, sdmc_files.data[i]);
		std::string filepath = savepath + sdmc_files.data[i];
		uint64_t size = FS::int82uint64(sdmc_arch, filepath);
		FS::bufferToFile(game_arch, buffer, size, "/", sdmc_files.data[i]);
	}
	
	uint32_t uniqueid = ((uint32_t)(game->titleid)) >> 8;
	uint64_t securein = ((uint64_t)SECUREVALUE_SLOT_SD << 32) | (uniqueid << 8);
	uint8_t secureout;
	FSUSER_ControlSecureSave(SECURESAVE_ACTION_DELETE, &securein, 8, &secureout, 1);
	
	int game_index = game->getIndex();
	int save_index = save->getIndex(game_index);
	savelist[game_index][save_index]->setCurrent(game_index);
	CFG::writeConfig();
}

void SYS::deleteSave(game_t* &game){
	file_t files = FS::getFiles(game_arch, "/");
	for(int i = 0; i < files.num; i++){
		std::string filepath = "/" + files.data[i];
		FSUSER_DeleteFile(game_arch, fsMakePath(PATH_ASCII, filepath.c_str()));
	}
	FSUSER_ControlArchive(game_arch, ARCHIVE_ACTION_COMMIT_SAVE_DATA, NULL, 0, NULL, 0);
}

void SYS::launchGame(game_t* &game){
	uint8_t param[0x300];
	uint8_t hmac[0x20];
	memset(param, 0, sizeof(param));
	memset(hmac, 0, sizeof(hmac));
	APT_PrepareToDoApplicationJump(0, game->titleid, 1);
	APT_DoApplicationJump(param, sizeof(param), hmac);
}