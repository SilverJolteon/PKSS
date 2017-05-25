#include "global.h"

void Menu(){
	CheckGame();
	while(aptMainLoop()){
		hidScanInput();
		u32 kDown = hidKeysDown();
		touchPosition touch;
		hidTouchRead(&touch);
		
		int chose = 0;
		if(kDown & KEY_START){
			break;
		}
		
		if(AREA(touch.px, touch.py, 27, 95, 147, 114) && (ChooseGame("X") == 1) && (active[0] == 1)){
			chose = 1;
			num = 0;
		}
		if(AREA(touch.px, touch.py, 151, 95, 272, 114) && (ChooseGame("Y") == 1) && (active[1] == 1)){
			chose = 1;
			num = 1;
		}
		if(AREA(touch.px, touch.py, 27, 125, 147, 144) && (ChooseGame("OR") == 1) && (active[2] == 1)){
			chose = 1;
			num = 2;
		}
		if(AREA(touch.px, touch.py, 151, 125, 272, 144) && (ChooseGame("AS") == 1) && (active[3] == 1)){
			chose = 1;
			num = 3;
		}
		if(AREA(touch.px, touch.py, 27, 155, 147, 174) && (ChooseGame("S") == 1) && (active[4] == 1)){
			chose = 1;
			num = 4;
		}
		if(AREA(touch.px, touch.py, 151, 155, 272, 174) && (ChooseGame("M") == 1) && (active[5] == 1)){
			chose = 1;
			num = 5;
		}
		if(chose == 1){
			Menu2();
		}
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			DisplayText(header, 0, 0, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sf2d_draw_texture(img, 0, 0);
			DisplayText("PKSS", 130, 66, 14, 255, 255, 255);
			if(active[0] == 1){
				DisplayText("X", 84, 96, 14, 255, 255, 255);
			}
			if(active[1] == 1){
				DisplayText("Y", 207, 96, 14, 255, 255, 255);
			}
			if(active[2] == 1){
				DisplayText("OR", 78, 126, 14, 255, 255, 255);
			}
			if(active[3] == 1){
				DisplayText("AS", 201, 126, 14, 255, 255, 255);
			}
			if(active[4] == 1){
				DisplayText("S", 84, 156, 14, 255, 255, 255);
			}
			if(active[5] == 1){
				DisplayText("M", 206, 156, 14, 255, 255, 255);
			}
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}

void Menu2(){
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			DisplayText(header, 0, 0, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			if(GetArch() == 0){
				if(entries[num] <= -1){
					Backup();
				}
				if(entries[num] > -1){
					sf2d_end_frame();
					sf2d_swapbuffers();
					DisplaySaves();
				}
			}
			else{
				DisplayText("Failed to read game archive!", 0, 0, 14, 255, 0, 0);
			}
		sf2d_end_frame();
		
		sf2d_swapbuffers();
	
}