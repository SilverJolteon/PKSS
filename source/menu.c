#include "global.h"

void Menu(){
	int pntx = 90, pnty = 37;
	CheckGame();
	while(aptMainLoop()){
		page = 1;
		hidScanInput();
		u32 kDown = hidKeysDown();
		touchPosition touch;
		hidTouchRead(&touch);
		num = 255;
		int chose = 0;
		if(kDown & KEY_START){
			break;
		}
		if((AREA(touch.px, touch.py, 24, 87, 151, 114) || ((kDown & KEY_A) && pntx == 18 && pnty == 81)) && (ChooseGame("X") == 1) && (active[0] == 1)){
			chose = 1;
			num = 0;
		}
		if((AREA(touch.px, touch.py, 168, 87, 295, 114) || ((kDown & KEY_A) && pntx == 162 && pnty == 81)) && (ChooseGame("Y") == 1) && (active[1] == 1)){
			chose = 1;
			num = 1;
		}
		if((AREA(touch.px, touch.py, 24, 131, 151, 158) || ((kDown & KEY_A) && pntx == 18 && pnty == 125)) && (ChooseGame("OR") == 1) && (active[2] == 1)){
			chose = 1;
			num = 2;
		}
		if((AREA(touch.px, touch.py, 168, 131, 295, 158) || ((kDown & KEY_A) && pntx == 162 && pnty == 125)) && (ChooseGame("AS") == 1) && (active[3] == 1)){
			chose = 1;
			num = 3;
		}
		if((AREA(touch.px, touch.py, 24, 175, 151, 202) || ((kDown & KEY_A) && pntx == 18 && pnty == 169)) && (ChooseGame("S") == 1) && (active[4] == 1)){
			chose = 1;
			num = 4;
		}
		if((AREA(touch.px, touch.py, 168, 175, 295, 202) || ((kDown & KEY_A) && pntx == 162 && pnty == 169)) && (ChooseGame("M") == 1) && (active[5] == 1)){
			chose = 1;
			num = 5;
		}
		if(kDown & KEY_UP){
			if(pnty > 37){
				pnty -= 44;
			}
			if(pnty == 37){
				pntx = 90;
			}
		}
		if(kDown & KEY_DOWN){
			if(pnty == 37){
				pntx = 18;
			}
			if(pnty < 169){
				pnty += 44;
			}
		}
		if(kDown & KEY_LEFT){
			if(pntx > 18 && pnty != 37){
				pntx -= 144;
			}
		}
		if(kDown & KEY_RIGHT){
			if(pntx < 162 && pnty != 37){
				pntx += 144;
			}
		}
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			sf2d_draw_texture(UI, 0, 0);
			DisplayText("Cartridge", 127, 48, 14, 255, 255, 255);
			if(active[0] == 1){
				DisplayText("X", 83, 92, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 87);
			}
			
			if(active[1] == 1){
				DisplayText("Y", 227, 92, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 87);
			}
			
			if(active[2] == 1){
				DisplayText("OR", 78, 136, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 131);
			}
			
			if(active[3] == 1){
				DisplayText("AS", 222, 136, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 131);
			}
			
			if(active[4] == 1){
				DisplayText("S", 83, 180, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 175);
			}
			
			if(active[5] == 1){
				DisplayText("M", 226, 180, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 175);
			}
		if((chose == 1) && (num == 0)){
			sf2d_draw_texture(blank, 24, 87);
			DisplayText("X", 83, 92, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 1)){
			sf2d_draw_texture(blank, 168, 87);
			DisplayText("Y", 227, 92, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 2)){
			sf2d_draw_texture(blank, 24, 131);
			DisplayText("OR", 78, 136, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 3)){
			sf2d_draw_texture(blank, 168, 131);
			DisplayText("AS", 222, 136, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 4)){
			sf2d_draw_texture(blank, 24, 175);
			DisplayText("S", 83, 180, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 5)){
			sf2d_draw_texture(blank, 168, 175);
			DisplayText("M", 226, 180, 14, 255, 255, 255);
		}
		sf2d_draw_texture(cursorl, pntx, pnty);
		sf2d_draw_texture(cursorr, pntx + 127, pnty);
		sf2d_end_frame();
		sf2d_swapbuffers();
		
		if(chose == 1){
			svcSleepThread(250000000);
			Menu2();
		}
	}
}

void Menu2(){
	int y, pnt = 25;
	while(aptMainLoop()){
		int pagenum = ceil(entries[num] / (float)6);
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_Y){
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
		if(kDown & KEY_UP){
			if(pnt > 25){
				pnt -= fontspace;
			}
		}
		if(kDown & KEY_DOWN){
			if(pnt < 5 * fontspace){
				pnt += fontspace;
			}
		}
		if(kDown & KEY_B){
			break;
		}
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			sf2d_draw_texture(saveslots, 0, 0);
			sftd_draw_textf(fontb, 75, 9, RGBA8(64, 64, 64, 255), 14, "Displaying saves for %s:", list[num]);
			sftd_draw_text(font, 66, 216, RGBA8(64, 64, 64, 255), 14, "Press Y to create a backup");
		for(((y = ((6 * page) - 6))); y < ((((entries[num] - 6 * page) >= 0) * 6 * page) + (((entries[num] - 6 * page) < 0) * ((6 * (page - 1)) + entries[num] - 6 * (page - 1)))); y++){
			sftd_draw_textf(font, 45, (y + 1) * fontspace + 6 - 180 * (page - 1), RGBA8(32, 32, 32, 255), 14, "%d: %s", y + 1, saves[num][y]);
		}
		if(page > 1){
			sf2d_draw_texture(arrowl, 9, 110);
		}
		if(page < pagenum){
			sf2d_draw_texture(arrowr, 297, 110);
		}
		sf2d_draw_texture(cursorl, 25, pnt);
		sf2d_draw_texture(cursorr, 281, pnt);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}