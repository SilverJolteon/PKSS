#ifndef GAME_H
#define GAME_H

#include <3ds.h>
#include <iostream>
#include <vector>
#include "fs.h"

class game_t{
	public:
		game_t(std::string name, uint64_t titleid);
		void checkInstalled();
		int getIndex();
		std::string name;
		uint64_t titleid;
		bool installed;		
		C2D_Sprite icon;
};

namespace GAME{
	void init();
}

extern std::vector<game_t*> gamelist;
extern int selected_game;

#endif