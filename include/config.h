#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include "fs.h"
#include "game.h"
#include "save.h"

namespace CFG{
	void readConfig();
	void writeConfig();
}

#endif