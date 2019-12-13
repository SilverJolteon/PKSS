#ifndef GAME_H
#define GAME_H

#include <3ds.h>
#include <iostream>
#include <vector>
#include "fs.h"

//enum game_vector_id{RE, BL, YE, GO, SI, CR, X, Y, OR, AS, SU, MO, US, UM};

class game_t{
	public:
		game_t(std::string name, uint64_t titleid);
		void checkInstalled();
		int getIndex();
		std::string name;
		uint64_t titleid;
		bool installed;		
};

namespace GAME{
	void init();
}

extern std::vector<game_t*> gamelist;

#endif