#include "global.h"

void Menu(){
	while(aptMainLoop()){
		CheckGame();
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
		
		if(AREA(touch.px, touch.py, 24, 87, 151, 114) && (ChooseGame("X") == 1) && (active[0] == 1)){
			chose = 1;
			num = 0;
		}
		if(AREA(touch.px, touch.py, 168, 87, 295, 114) && (ChooseGame("Y") == 1) && (active[1] == 1)){
			chose = 1;
			num = 1;
		}
		if(AREA(touch.px, touch.py, 24, 131, 151, 158) && (ChooseGame("OR") == 1) && (active[2] == 1)){
			chose = 1;
			num = 2;
		}
		if(AREA(touch.px, touch.py, 168, 131, 295, 158) && (ChooseGame("AS") == 1) && (active[3] == 1)){
			chose = 1;
			num = 3;
		}
		if(AREA(touch.px, touch.py, 24, 175, 151, 202) && (ChooseGame("S") == 1) && (active[4] == 1)){
			chose = 1;
			num = 4;
		}
		if(AREA(touch.px, touch.py, 168, 175, 295, 202) && (ChooseGame("M") == 1) && (active[5] == 1)){
			chose = 1;
			num = 5;
		}
		if(chose == 1){
			Menu2();
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
		sf2d_end_frame();
		sf2d_swapbuffers();
	}
}

void Menu2(){
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sf2d_draw_texture(top, 0, 0);
			DisplayText(version, 250, 155, 14, 255, 255, 255);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			if(GetArch() == 0){
				sf2d_end_frame();
				sf2d_swapbuffers();
				DisplaySaves();
			}
			else{
				DisplayText("Failed to read game archive!", 0, 0, 14, 255, 0, 0);
			}
		sf2d_end_frame();
		
		sf2d_swapbuffers();
}