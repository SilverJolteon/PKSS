#include "game.h"

game_t::game_t(std::string name, uint64_t titleid):name(name), titleid(titleid){
	checkInstalled();
}

void game_t::checkInstalled(){
	uint32_t sdtitles_num;
	uint64_t* sdtitles_IDs;
	amInit();
	AM_GetTitleCount(mediatype, &sdtitles_num);
	sdtitles_IDs = new uint64_t[sdtitles_num * sizeof(uint64_t)];
	AM_GetTitleList(NULL, mediatype, sdtitles_num, sdtitles_IDs);
	for(int i = 0; i < (signed)sdtitles_num; i++){
		if(sdtitles_IDs[i] == titleid){
			installed = true;
			break;
		}
		else installed = false;
	}
}

int game_t::getIndex(){
	for(size_t i = 0; i < gamelist.size(); i++){
		if(titleid == gamelist[i]->titleid){
			return i;
		}
	}
	return 0;
}

void GAME::init(){
	gamelist.push_back(new game_t("Pokemon_Red", 0x0004000000171000));
	gamelist.push_back(new game_t("Pokemon_Blue", 0x0004000000171100));
	gamelist.push_back(new game_t("Pokemon_Yellow", 0x0004000000171200));
	gamelist.push_back(new game_t("Pokemon_Gold", 0x0004000000172600));
	gamelist.push_back(new game_t("Pokemon_Silver", 0x0004000000172700));
	gamelist.push_back(new game_t("Pokemon_Crystal", 0x0004000000172800));
	gamelist.push_back(new game_t("Pokemon_X", 0x0004000000055D00));
	gamelist.push_back(new game_t("Pokemon_Y", 0x0004000000055E00));
	gamelist.push_back(new game_t("Pokemon_Omega_Ruby", 0x000400000011C400));
	gamelist.push_back(new game_t("Pokemon_Alpha_Sapphire", 0x000400000011C500));
	gamelist.push_back(new game_t("Pokemon_Sun", 0x0004000000164800));
	gamelist.push_back(new game_t("Pokemon_Moon", 0x0004000000175E00));
	gamelist.push_back(new game_t("Pokemon_Ultra_Sun", 0x00040000001B5000));
	gamelist.push_back(new game_t("Pokemon_Ultra_Moon", 0x00040000001B5100));
}

std::vector<game_t*> gamelist;