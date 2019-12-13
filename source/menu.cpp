#include "menu.h"
#include "gfx.h"
#include "system.h"
#include "config.h"
#include "save.h"
#define AREA(px, py, xmin, ymin, xmax, ymax) ((px < xmax && px > xmin) && (py < ymax && py > ymin))

std::string version = "v0.9.0";

void mainmenu(){
	
	int selected = 6;
	while(aptMainLoop()){
		hidScanInput();
		uint32_t kDown = hidKeysDown();
		touchPosition touch;
		hidTouchRead(&touch);
		
		bool transition = false;
		
		if(kDown & KEY_START) break;
		
		if((kDown & KEY_A) && gamelist[selected]->installed){
			transition = true;
		}
		
		if(kDown & KEY_UP){
			if(selected == 6) selected = 12;
			else if(selected == 7) selected = 13;
			else selected -= 2;
		}
		if(kDown & KEY_DOWN){
			if(selected == 12) selected = 6;
			else if(selected == 13) selected = 7;
			else selected += 2;
		}
		if((kDown & KEY_LEFT) || (kDown & KEY_RIGHT)){
			if(selected & 1) selected--;
			else selected++;
		}
		
		C2D_start_frame(TOP_SCREEN);	
			C2D_draw_texture(TOP_PNG, 0, 0);
			C2D_draw_text(version, 250, 155, 14, 0xFFFFFF);
		C2D_end_frame();
		
		C2D_start_frame(BOTTOM_SCREEN);
			C2D_draw_texture(BOTTOM_PNG, 0, 0);
			C2D_draw_texture(UI_PNG, 0, 0);

			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 2; j++){
					int index = ((i << 1 | j) + 6);
					int x = 24 + (j * 144);
					int y = 62 + (i * 44);
					if(AREA(touch.px, touch.py, x, y, x+127, y+27)){
						selected = index;
						if(gamelist[index]->installed) transition = true;
					}
					if(transition && selected == index) C2D_draw_texture(BLANK_PNG, x, y);
					if(gamelist[index]->installed) C2D_draw_text(gamelist[index]->name.substr(8), x, y, x+127, y+27, 14, 0xFFFFFF);
					else C2D_draw_texture(BLANK_PNG, x, y);
				}
			}
			C2D_draw_texture(CURSORL_PNG, (18 + ((selected&1) * 144)), (56 + (((selected/2)-3) * 44)));
			C2D_draw_texture(CURSORR_PNG, 127 + (18 + ((selected&1) * 144)), (56 + (((selected/2)-3) * 44)));
			
			
		C2D_end_frame();
		
		if(transition){
			svcSleepThread(100000000);
			savemenu(selected);
		}
	}
	exitGFX();
	romfsExit();
}

void savemenu(int game){
	SYS::selectGame(gamelist[game]);
	int entry = 0, page = 0, transition_offset = 0, transition_direction = 0;
	int prev_page, next_page;
	std::string current_save = savelist[game][getCurrent(game)]->name;
	std::string top_text = "Press Y to backup \"" + current_save + "\"";
	while(aptMainLoop()){
		hidScanInput();
		uint32_t kDown = hidKeysDown();
		touchPosition touch;
		hidTouchRead(&touch);
		int page_num = ceil(savelist[game].size() / (float)6);
		int max_entry = 6*(1&&(page_num-page-1)) + (savelist[game].size() - (page_num-1)*6)*(0==(page_num-page-1)) - 1;
		bool selected = false;
		if(kDown & KEY_B) break;
		if((kDown & KEY_LEFT) || (AREA(touch.px, touch.py, 9, 110, 22, 129))){
			if(page_num > 1) transition_direction = -1;
		}
		if((kDown & KEY_RIGHT) || (AREA(touch.px, touch.py, 297, 110, 310, 129))){
			if(page_num > 1) transition_direction = 1;
		}
		if(kDown & KEY_UP){
			if(entry > 0) entry--;
			else if(entry == 0) entry = max_entry;
		}
		if(kDown & KEY_DOWN){
			if(entry < max_entry) entry++;
			else if(entry == max_entry) entry = 0;
		}
		if(page > 0) prev_page = page - 1;
		else if(page == 0) prev_page = page_num - 1;
		if(page < (page_num - 1)) next_page = page + 1;
		else if(page == (page_num - 1)) next_page = 0;
		
		if(transition_direction == -1) transition_offset += 15;
		if(transition_direction == 1) transition_offset -= 15;
		if(transition_direction == -1 && transition_offset >= 320){
			entry = 0;
			transition_direction = 0;
			transition_offset = 0;
			page = prev_page;
		}
		if(transition_direction == 1 && transition_offset <= -320){
			entry = 0;
			transition_direction = 0;
			transition_offset = 0;
			page = next_page;
		}
		if(kDown & KEY_A) selected = true;
		C2D_start_frame(TOP_SCREEN);	
			C2D_draw_texture(TOP_PNG, 0, 0);
			C2D_draw_text(version, 250, 155, 14, 0xFFFFFF);
		C2D_end_frame();
		
		C2D_start_frame(BOTTOM_SCREEN);
			C2D_draw_texture(BOTTOM_PNG, 0, 0);
			if(kDown & KEY_Y){
				SYS::backupSave(gamelist[game], current_save);
				top_text = "Backed up \"" + current_save + "\"";
				//std::string savename = SYS::getString("Enter Save Name");
				//if(savename.compare("")) SYS::backupSave(gamelist[game], savename);
			}
			C2D_draw_text(top_text, 0, 16, 319, 16, 14, 0x404040);
			for(size_t i = 0; i < 6 && i < savelist[game].size() - (page*6); i++){
				int x = 32 + transition_offset;
				int y = 32 * (i + 1);
				if(AREA(touch.px, touch.py, x, y, x+255, y+27)){
					entry = i;
					selected = true;
				}
				C2D_draw_texture(SAVES_PNG, x, y);
				if(savelist[game][i+(page*6)]->current) C2D_draw_text(savelist[game][i+(page*6)]->name, x, y, x+255, y+27, 14, 0xA02020);
				else C2D_draw_text(savelist[game][i+(page*6)]->name, x, y, x+255, y+27, 14, 0x202020);
			}
			if(transition_direction != 0){
				int temp_page;
				if(transition_direction == -1) temp_page = prev_page;
				if(transition_direction == 1) temp_page = next_page;
				for(size_t i = 0; i < 6 && i < savelist[game].size() - (temp_page*6); i++){
					int x = 32 + transition_offset + (transition_direction * 320);
					int y = 32 * (i + 1);
					C2D_draw_texture(SAVES_PNG, x, y);
					if(savelist[game][i+(temp_page*6)]->current) C2D_draw_text(savelist[game][i+(temp_page*6)]->name, x, y, x+255, y+27, 14, 0xA02020);
					else C2D_draw_text(savelist[game][i+(temp_page*6)]->name, x, y, x+255, y+27, 14, 0x202020);
				}
			}
			if(page_num > 1){
				C2D_draw_texture(ARROWL_PNG, 9, 110);
				C2D_draw_texture(ARROWR_PNG, 297, 110);
			}
			if(transition_direction == 0 && savelist[game].size() > 0){
				C2D_draw_texture(CURSORL_PNG, 26, 25 + (entry * 32));
				C2D_draw_texture(CURSORR_PNG, 26+255, 25 + (entry * 32));
			}
			if(selected) savefilemenu(game, (page*6) + entry);
	}
}

void savefilemenu(int game, int save){
	while(aptMainLoop()){
		hidScanInput();
		uint32_t kDown = hidKeysDown();
		if(kDown & KEY_B) break;
		if(kDown & KEY_A){
			SYS::selectGame(gamelist[game]);
			SYS::restoreSave(gamelist[game], savelist[game][save]);
			SYS::launchGame(gamelist[game]);
		}
		C2D_start_frame(TOP_SCREEN);	
			C2D_draw_texture(TOP_PNG, 0, 0);
			C2D_draw_text(version, 250, 155, 14, 0xFFFFFF);
		C2D_end_frame();
		C2D_start_frame(BOTTOM_SCREEN);	
			C2D_draw_texture(BOTTOM_PNG, 0, 0);
			C2D_draw_texture(SAVEMENU_PNG, 0, 0);
			C2D_draw_text("Launch " + savelist[game][save]->name, 24, 62, 295, 89, 14, 0xFFFFFF);
		C2D_end_frame();
	}
}