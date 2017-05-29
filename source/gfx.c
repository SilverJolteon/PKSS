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
	cursorl = sfil_load_PNG_buffer(cursorl_png, SF2D_PLACE_RAM);
	cursorr = sfil_load_PNG_buffer(cursorr_png, SF2D_PLACE_RAM);
	arrowl = sfil_load_PNG_buffer(arrowl_png, SF2D_PLACE_RAM);
	arrowr = sfil_load_PNG_buffer(arrowr_png, SF2D_PLACE_RAM);
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

CenterText Center(char* text, int ix, int iy, int iw, int ih){
	int width = sftd_get_text_width(font, 14, text);
	ix = round((iw - width)/(float)2) + ix;
	iy = round((ih - 14)/(float)2) + iy - 2;
	CenterText center = {ix, iy};
	return center;
}