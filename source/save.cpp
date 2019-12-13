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

int save_t::getIndex(int game){
	for(std::size_t i = 0; i < savelist[game].size(); i++){
		if(!name.compare(savelist[game][i]->name)){
			return i;
		}
	}
	return 0;
}

void save_t::setCurrent(int game){
	for(size_t i = 0; i < savelist[game].size(); i++){
		savelist[game][i]->current = false;
	}
	current = true;
}

int getCurrent(int game){
	for(size_t i = 0; i < savelist[game].size(); i++){
		if(savelist[game][i]->current) return i;
	}
	return 0;
}

std::vector<std::vector<save_t*>> savelist(GAME_NUM);