#include "global.h"

void InitGFX(){
	sftd_init();
	sf2d_init();
	font = sftd_load_font_mem(font_ttf, font_ttf_size);
	img = sfil_load_PNG_buffer(bottom_png, SF2D_PLACE_RAM);
	sf2d_set_clear_color(RGBA8(0, 162, 232, 255));
	sftd_draw_textf(font, 0, 0, RGBA8(255, 0, 0, 255), 14, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
}

void FinitGFX(){
	fsEndUseSession();
	fsExit();
	sftd_fini();
	sf2d_fini();
}

void DisplayText(char* text, int x, int y, int size, int R, int G, int B){
	sftd_draw_text(font, x, y,  RGBA8(R, G, B, 255), size, text);
}

int DisplaySaves(){
	int y;
	while(aptMainLoop()){
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_A){
			Backup();
		}
		if(kDown & KEY_B){
			break;
		}
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sftd_draw_textf(font, 0, 0, RGBA8(255, 255, 255, 255), 14, "Displaying saves for %s:", list[num]);
		for(y = 0; y <= entries[num]; y++){
			sftd_draw_textf(font, 0, (y + 1) * fontspace, RGBA8(255, 255, 255, 255), 14, "- %s", saves[num][y]);
		}
		DisplayText("Press A to create a backup", 0, (entries[num] + 3) * fontspace, 14, 255, 255, 255);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	return 0;
}