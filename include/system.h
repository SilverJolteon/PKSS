#ifndef SYSTEM_H
#define SYSTEM_H

#include <3ds.h>
#include <cstring>
#include "game.h"
#include "fs.h"
#include "save.h"
#include "config.h"

namespace SYS{
	std::string getString(std::string description);
	void selectGame(game_t* &game);
	int backupSave(game_t* &game, std::string savename);
	void restoreSave(game_t* &game, save_t* &save);
	void deleteSave(game_t* &game);
	void launchGame(game_t* &game);
}

#endif