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
	int backupSave(std::string savename);
	void restoreSave();
	void deleteSave();
	void launchGame();
}

#endif