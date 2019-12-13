#ifndef SAVE_H
#define SAVE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "fs.h"

#define GAME_NUM 14

class save_t{
	public:
		save_t(std::string name);
		void getTime();
		int getIndex(int game);
		void setCurrent(int game);
		std::string name;
		std::string time;
		bool current;
};

int getCurrent(int game);

extern std::vector<std::vector<save_t*>> savelist;

#endif