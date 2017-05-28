#include "global.h"

void InitGFX(){
	sftd_init();
	sf2d_init();
	font = sftd_load_font_mem(font_ttf, font_ttf_size);
	fontb = sftd_load_font_mem(fontb_ttf, font_ttf_size);
	top = sfil_load_PNG_buffer(top_png, SF2D_PLACE_RAM);
	bottom = sfil_load_PNG_buffer(bottom_png, SF2D_PLACE_RAM);
	UI = sfil_load_PNG_buffer(UI_png, SF2D_PLACE_RAM);
	blank = sfil_load_PNG_buffer(blank_png, SF2D_PLACE_RAM);
	saveslots = sfil_load_PNG_buffer(saves_png, SF2D_PLACE_RAM);
	sf2d_set_clear_color(RGBA8(100, 100, 120, 255));
	sftd_draw_textf(font, 0, 0, RGBA8(255, 0, 0, 255), 14, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
	sftd_draw_textf(fontb, 0, 0, RGBA8(255, 0, 0, 255), 14, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:-.'!?()\"end");
}

void FinitGFX(){
	fsEndUseSession();
	fsExit();
	sftd_fini();
	sf2d_fini();
}

void DisplayText(char* text, int x, int y, int size, int R, int G, int B){
	sftd_draw_text(fontb, x, y,  RGBA8(R, G, B, 255), size, text);
}

int DisplaySaves(){
	int y;
	while(aptMainLoop()){
		int pagenum = ceil(entries[num] / (float)5);
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_A){
			Backup();
		}
		if(kDown & KEY_LEFT){
			if(page > 1){
				page--;
			}
		}
		if(kDown & KEY_RIGHT){
			if(page < pagenum){
				page++;
			}
		}
		if(kDown & KEY_B){
			break;
		}
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			sf2d_draw_texture(saveslots, 0, 0);
			sftd_draw_textf(fontb, 75, 9, RGBA8(64, 64, 64, 255), 14, "Displaying saves for %s:", list[num]);
			sftd_draw_text(font, 66, 216, RGBA8(64, 64, 64, 255), 14, "Press A to create a backup");
		for(((y = ((6 * page) - 6))); y < ((((entries[num] - 6 * page) >= 0) * 6 * page) + (((entries[num] - 6 * page) < 0) * ((6 * (page - 1)) + entries[num] - 6 * (page - 1)))); y++){
			sftd_draw_textf(font, 45, (y + 1) * fontspace + 6 - 180 * (page - 1), RGBA8(32, 32, 32, 255), 14, "%d) %s", y + 1, saves[num][y]);
		}
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
	return 0;
}