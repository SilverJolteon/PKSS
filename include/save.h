#ifndef SAVE_H
#define SAVE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "fs.h"
#include "game.h"

#define GAME_NUM 14

class save_t{
	public:
		save_t(std::string name);
		void getTime();
		int getIndex();
		void setCurrent();
		std::string name;
		std::string time;
		bool current;
};

int getCurrent();

extern std::vector<std::vector<save_t*>> savelist;
extern int selected_save;

#endif