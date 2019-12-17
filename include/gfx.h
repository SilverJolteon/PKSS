#ifndef GFX_H
#define GFX_H

#include <citro2d.h>
#include <iostream>
#include <vector>

enum{
	ARROWL_PNG,
	ARROWR_PNG,
	BLANK_PNG,
	BOTTOM_PNG, 
	CURSORL_PNG,
	CURSORR_PNG,
	SAVEMENU_PNG,
	SAVES_PNG,
	TOP_PNG,
	UI_PNG,
	X_PNG
};

extern C3D_RenderTarget* TOP_SCREEN;
extern C3D_RenderTarget* BOTTOM_SCREEN;

void initGFX();
void exitGFX();
void C2D_start_frame(C3D_RenderTarget* screen);
void C2D_end_frame();
void C2D_draw_texture(size_t index, int x, int y);
void C2D_draw_texture(C2D_Sprite sprite, int x, int y);
void C2D_draw_text(std::string str, int x0, int y0, int x1, int y1, int size, uint32_t color);
void C2D_draw_text(std::string str, int x, int y, int size, uint32_t color);

#endif