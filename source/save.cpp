#include "save.h"

save_t::save_t(std::string name):name(name){
	current = false;
}

void save_t::getTime(){
	std::ifstream file(name + "/main", std::ios::binary);
	if(!file.is_open()) return;
	uint64_t buffer;
	file.seekg(0x1800, file.beg);
	file.read((char*)&buffer, 4);
	file.close();
	int hours = buffer & 0xFFFF;
	int minutes = (buffer >> 16) & 0xFF;
	int seconds = (buffer >> 24) & 0xFF;
	if(hours < 10) time += "0";
	if(hours < 100) time += "0";
	time += std::to_string(hours);
	time += ":";
	if(minutes < 10) time += "0";
	time += std::to_string(minutes);
	time += ":";
	if(seconds < 10) time += "0";
	time += std::to_string(seconds);
}

void save_t::setCurrent(){
	for(size_t i = 0; i < savelist[selected_game].size(); i++){
		savelist[selected_game][i]->current = false;
	}
	current = true;
}

int getCurrent(){
	for(size_t i = 0; i < savelist[selected_game].size(); i++){
		if(savelist[selected_game][i]->current) return i;
	}
	return -1;
}

std::vector<std::vector<save_t*>> savelist(GAME_NUM);
int selected_save = 0;