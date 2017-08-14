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
		if((AREA(touch.px, touch.py, 24, 87, 151, 114) || ((kDown & KEY_A) && pntx == 18 && pnty == 81)) && (active[0] == 1)){
			if(ChooseGame("X") == 1){
				chose = 1;
				num = 0;
			}
		}
		if((AREA(touch.px, touch.py, 168, 87, 295, 114) || ((kDown & KEY_A) && pntx == 162 && pnty == 81)) && (active[1] == 1)){
			if(ChooseGame("Y") == 1){
				chose = 1;
				num = 1;
			}
		}
		if((AREA(touch.px, touch.py, 24, 131, 151, 158) || ((kDown & KEY_A) && pntx == 18 && pnty == 125)) && (active[2] == 1)){
			if(ChooseGame("OR") == 1){
				chose = 1;
				num = 2;
			}
		}
		if((AREA(touch.px, touch.py, 168, 131, 295, 158) || ((kDown & KEY_A) && pntx == 162 && pnty == 125)) && (active[3] == 1)){
			if(ChooseGame("AS") == 1){
				chose = 1;
				num = 3;
			}
		}
		if((AREA(touch.px, touch.py, 24, 175, 151, 202) || ((kDown & KEY_A) && pntx == 18 && pnty == 169)) && (active[4] == 1)){
			if(ChooseGame("S") == 1){
				chose = 1;
				num = 4;
			}
		}
		if((AREA(touch.px, touch.py, 168, 175, 295, 202) || ((kDown & KEY_A) && pntx == 162 && pnty == 169)) && (active[5] == 1)){
			if(ChooseGame("M") == 1){
				chose = 1;
				num = 5;
			}
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
		if(kDown & KEY_START){
			break;
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
			ChooseGame(list[num]);
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
			CenterText center = Center("Press Y to create a backup", 0, 209, 320, 31);
			sftd_draw_text(font, center.InitX, center.InitY, RGBA8(64, 64, 64, 255), 14, "Press Y to create a backup");
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
		if(kDown & KEY_B){
			break;
		}
	}
}

void Menu3(int save){
		ChooseGame(list[num]);
		char* temp = gamepath;
		char* temp2 = "null";
		temp2 = calloc(strlen(temp) + strlen(saves[num][save]) + 10, 1);
		sprintf(temp2, "%s/%s", temp, saves[num][save]);
		char* launchname = "Launch";
		launchname = calloc(strlen("Launch") + strlen(saves[num][save]) + 10, 1);
		sprintf(launchname, "Launch %s", saves[num][save]);
		gamepath = temp2;
		GetSaveInfo(gamepath);
		char* time = "null";
		time = calloc(strlen("Time:") + 20, 1);
		sprintf(time, "Time: %d:%d", hour, minute);
	
	while(aptMainLoop()){
		
		hidScanInput();
		u32 kDown = hidKeysDown();
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(bottom, 0, 0);
			sf2d_draw_texture(savemenu, 0, 0);
			
			CenterText center = Center(trainer, 0, 10, 320, 18);
			sftd_draw_textf(font, center.InitX, center.InitY, RGBA8(32, 32, 32, 255), 14, "%s", trainer);
			
			CenterText centert = Center(time, 0, 26, 320, 18);
			sftd_draw_textf(font, centert.InitX, centert.InitY, RGBA8(32, 32, 32, 255), 14, "%s", time);
			
			CenterText center1 = Center(launchname, 24, 62, 272, 28);
			sftd_draw_textf(fontb, center1.InitX, center1.InitY, RGBA8(255, 255, 255, 255), 14, "%s", launchname);
			
			CenterText center2 = Center("Copy", 24, 106, 128, 28);
			sftd_draw_textf(font, center2.InitX, center2.InitY, RGBA8(32, 32, 32, 255), 14, "Copy");
			
			CenterText center3 = Center("Rename", 168, 106, 128, 28);
			sftd_draw_textf(font, center3.InitX, center3.InitY, RGBA8(32, 32, 32, 255), 14, "Rename");
			
			CenterText center4 = Center("Delete", 24, 150, 128, 28);
			sftd_draw_textf(font, center4.InitX, center4.InitY, RGBA8(32, 32, 32, 255), 14, "Delete");
			
			CenterText center5 = Center("Options", 168, 150, 128, 28);
			sftd_draw_textf(font, center5.InitX, center5.InitY, RGBA8(32, 32, 32, 255), 14, "Options");
			
		sf2d_end_frame();
		sf2d_swapbuffers();
		/*
		if(kDown & KEY_X){
			sprintf(saves[num][save], "|");
			WriteConfig();
			ReadConfig();
			WriteConfig();
			InitSD(gamepath, "-");
			break;
		}
		*/
		if(kDown & KEY_B){
			break;
		}
	}
}