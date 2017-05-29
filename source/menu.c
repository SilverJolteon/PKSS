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
		if((AREA(touch.px, touch.py, 24, 87, 151, 114) || ((kDown & KEY_A) && pntx == 18 && pnty == 81)) && (active[0] == 1)){
			ChooseGame("X");
			chose = 1;
			num = 0;
		}
		if((AREA(touch.px, touch.py, 168, 87, 295, 114) || ((kDown & KEY_A) && pntx == 162 && pnty == 81)) && (active[1] == 1)){
			ChooseGame("Y");
			chose = 1;
			num = 1;
		}
		if((AREA(touch.px, touch.py, 24, 131, 151, 158) || ((kDown & KEY_A) && pntx == 18 && pnty == 125)) && (active[2] == 1)){
			ChooseGame("OR");
			chose = 1;
			num = 2;
		}
		if((AREA(touch.px, touch.py, 168, 131, 295, 158) || ((kDown & KEY_A) && pntx == 162 && pnty == 125)) && (active[3] == 1)){
			ChooseGame("AS");
			chose = 1;
			num = 3;
		}
		if((AREA(touch.px, touch.py, 24, 175, 151, 202) || ((kDown & KEY_A) && pntx == 18 && pnty == 169)) && (active[4] == 1)){
			ChooseGame("S");
			chose = 1;
			num = 4;
		}
		if((AREA(touch.px, touch.py, 168, 175, 295, 202) || ((kDown & KEY_A) && pntx == 162 && pnty == 169)) && (active[5] == 1)){
			ChooseGame("M");
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
			CenterText center = Center("Cartridge", 96, 43, 128, 28);
			DisplayText("Cartridge", center.InitX, center.InitY, 14, 255, 255, 255);
			if(active[0] == 1){
				CenterText center = Center("X", 24, 87, 128, 28);
				DisplayText("X", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 87);
			}
			
			if(active[1] == 1){
				CenterText center = Center("Y", 168, 87, 128, 28);
				DisplayText("Y", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 87);
			}
			
			if(active[2] == 1){
				CenterText center = Center("OR", 24, 131, 128, 28);
				DisplayText("OR", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 131);
			}
			
			if(active[3] == 1){
				CenterText center = Center("AS", 168, 131, 128, 28);
				DisplayText("AS", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 131);
			}
			
			if(active[4] == 1){
				CenterText center = Center("S", 24, 175, 128, 28);
				DisplayText("S", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 24, 175);
			}
			
			if(active[5] == 1){
				CenterText center = Center("M", 168, 175, 128, 28);
				DisplayText("M", center.InitX, center.InitY, 14, 255, 255, 255);
			}
			else{
				sf2d_draw_texture(blank, 168, 175);
			}
		if((chose == 1) && (num == 0)){
			sf2d_draw_texture(blank, 24, 87);
			CenterText center = Center("X", 24, 87, 128, 28);
			DisplayText("X", center.InitX, center.InitY, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 1)){
			sf2d_draw_texture(blank, 168, 87);
			CenterText center = Center("Y", 168, 87, 128, 28);
			DisplayText("Y", center.InitX, center.InitY, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 2)){
			sf2d_draw_texture(blank, 24, 131);
			CenterText center = Center("OR", 24, 131, 128, 28);
			DisplayText("OR", center.InitX, center.InitY, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 3)){
			sf2d_draw_texture(blank, 168, 131);
			CenterText center = Center("AS", 168, 131, 128, 28);
			DisplayText("AS", center.InitX, center.InitY, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 4)){
			sf2d_draw_texture(blank, 24, 175);
			CenterText center = Center("S", 24, 175, 128, 28);
			DisplayText("S", center.InitX, center.InitY, 14, 255, 255, 255);
		}
		if((chose == 1) && (num == 5)){
			sf2d_draw_texture(blank, 168, 175);
			CenterText center = Center("M", 168, 175, 128, 28);
			DisplayText("M", center.InitX, center.InitY, 14, 255, 255, 255);
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
	int y, pnt = 25, slide = 0, toggle = 0;
	while(aptMainLoop()){
		int select = ((pnt + 5)/(float)fontspace) + 6 * (page - 1) - 1;
		int pagenum = ceil(entries[num] / (float)6);
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_Y){
			Backup();
		}
		if(kDown & KEY_LEFT){
			if(page > 1){
				toggle = 1;
			}
		}
		if(kDown & KEY_RIGHT){
			if(page < pagenum){
				toggle = 2;
			}
		}
		if(kDown & KEY_UP){
			if(pnt == 25){
				pnt = 6 * fontspace - 5;
			}
			else if(pnt > 25){
				pnt -= fontspace;
			}	
		}
		if(kDown & KEY_DOWN){
			if(pnt == 6 * fontspace - 5){
				pnt = 25;
			}
			else if(pnt < 6 * fontspace - 5){
				pnt += fontspace;
			}
		}
		if(kDown & KEY_B){
			break;
		}
		if(toggle == 1){
			slide += 10;
		}
		if(toggle == 2){
			slide -= 10;
		}
		if(toggle == 1 && slide == 320){
			toggle = 0;
			page--;
			slide = 0;
		}
		if(toggle == 2 && slide == -320){
			toggle = 0;
			page++;
			slide = 0;
		}
		if((toggle == 0) && (kDown & KEY_A) && (strcmp(saves[num][select], "") != 0)){
			Menu3(select);
		}
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			sf2d_draw_texture(saveslots, slide, 0);
			if(toggle == 1){
				sf2d_draw_texture(saveslots, slide - 320, 0);
				for(y = 0; y < 6; y++){
					CenterText center = Center("Loading...", 32, 31 + 30 * y, 256, 28);
					sftd_draw_text(font, slide - 320 + center.InitX, (y + 1) * fontspace + 6, RGBA8(32, 32, 32, 255), 14, "Loading...");
				}
			}
			if(toggle == 2){
				sf2d_draw_texture(saveslots, slide + 320, 0);
				for(y = 0; y < 6; y++){
					CenterText center = Center("Loading...", 32, 31 + 30 * y, 256, 28);
					sftd_draw_text(font, slide + 320 + center.InitX, (y + 1) * fontspace + 6, RGBA8(32, 32, 32, 255), 14, "Loading...");
				}
			}
			sftd_draw_textf(fontb, 75, 9, RGBA8(64, 64, 64, 255), 14, "Displaying saves for %s:", list[num]);
			sftd_draw_text(font, 66, 216, RGBA8(64, 64, 64, 255), 14, "Press Y to create a backup");
		for(((y = ((6 * page) - 6))); y < ((((entries[num] - 6 * page) >= 0) * 6 * page) + (((entries[num] - 6 * page) < 0) * ((6 * (page - 1)) + entries[num] - 6 * (page - 1)))); y++){
			CenterText center = Center(saves[num][y], 32, 31 + 30 * y, 256, 28);
			sftd_draw_textf(font, slide + 45, (y + 1) * fontspace + 6 - 180 * (page - 1), RGBA8(32, 32, 32, 100), 14, "%d", y + 1);
			sftd_draw_textf(font, slide + center.InitX, (y + 1) * fontspace + 6 - 180 * (page - 1), RGBA8(32, 32, 32, 255), 14, "%s", saves[num][y]);
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

void Menu3(int save){
	while(aptMainLoop()){
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(kDown & KEY_B){
			break;
		}
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			CenterText center = Center(saves[num][save], 0, 0, 320, 30);
			sftd_draw_textf(font, center.InitX, center.InitY, RGBA8(32, 32, 32, 255), 14, "%s", saves[num][save]);
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}