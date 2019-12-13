#include "config.h"

void CFG::readConfig(){
	for(size_t i = 0; i < gamelist.size(); i++){
		savelist[i].clear();
		dir_t saves = FS::getDirs(SAVE_PATH + "/" + gamelist[i]->name + "/");
		for(int j = 0; j < saves.num; j++){
			std::string savepath = SAVE_PATH + "/" + gamelist[i]->name + "/" + saves.data[j];
			//savelist[i].push_back(new save_t(saves.data[j]));
			file_t files = FS::getFiles(sdmc_arch, savepath);
			if(files.num > 0) savelist[i].push_back(new save_t(saves.data[j]));
			else FSUSER_DeleteDirectoryRecursively(sdmc_arch, fsMakePath(PATH_ASCII, savepath.c_str()));
		}
	}
	std::ifstream config(SAVE_PATH + "/config");
	if(!config.is_open()){
		FS::directory(SAVE_PATH, CREATE_DIR);
		return;
	}
	int i = 0;
	bool read = false;
	std::string buffer;
	while(getline(config, buffer)){		
		if(!buffer.compare("}")){
			read = false;
			i++;
		}
		if(read){
			for(std::size_t j = 0; j < savelist[i].size(); j++){
				if(!buffer.compare(savelist[i][j]->name)){
					savelist[i][j]->current = true;
				}
			}
		}
		
		if(!buffer.compare("{")) read = true;		
	}
	config.close();
}

void CFG::writeConfig(){
	std::ofstream config(SAVE_PATH + "/config");
	for(int i = 0; i < GAME_NUM; i++){
		config << gamelist[i]->name << std::endl << "{";
		for(std::size_t j = 0; j < savelist[i].size(); j++){
			if(savelist[i][j]->current) config << std::endl << savelist[i][j]->name;
		}
		config << std::endl << "}" << std::endl;
	}
	config.close();
}