#include <iostream>
#include <3ds.h>

#include "menu.h"
#include "gfx.h"
#include "system.h"
#include "config.h"

using namespace std;

int main(){
	romfsInit();
	initGFX();
	C2D_start_frame(TOP_SCREEN);	
		C2D_draw_texture(TOP_PNG, 0, 0);
		C2D_draw_text(version, 250, 155, 14, 0xFFFFFFFF);
	C2D_end_frame();
	C2D_start_frame(BOTTOM_SCREEN);	
		C2D_draw_text("Loading...", 0, 0, 319, 239, 14, 0xFFFFFFFF);
	C2D_end_frame();
	GAME::init();
	CFG::readConfig();
	mainmenu();
	exitGFX();
	romfsExit();
	return 0;
}