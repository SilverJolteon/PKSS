#include "gfx.h"

C3D_RenderTarget* TOP_SCREEN;
C3D_RenderTarget* BOTTOM_SCREEN;

static C2D_SpriteSheet spriteSheet;
static C2D_Sprite* sprites;
static size_t numSprites;
static C2D_Font font;

void initGFX(){
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	TOP_SCREEN = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	BOTTOM_SCREEN = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	font = C2D_FontLoad("romfs:/gfx/fontb.bcfnt");
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	numSprites = C2D_SpriteSheetCount(spriteSheet);
	sprites = new C2D_Sprite[numSprites];
	for(size_t i = 0; i < numSprites; i++){
		C2D_SpriteFromSheet(&sprites[i], spriteSheet, i);
	}
	if(!spriteSheet) svcBreak(USERBREAK_PANIC);
}

void exitGFX(){
	C2D_SpriteSheetFree(spriteSheet);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
}

void C2D_start_frame(C3D_RenderTarget* screen){
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(screen, C2D_Color32(0, 0, 0, 255));
	C2D_SceneBegin(screen);
}

void C2D_end_frame(){
	C3D_FrameEnd(0);
}

void C2D_draw_texture(size_t index, int x, int y){
	sprites[index].params.pos.x = x;
	sprites[index].params.pos.y = y;
	C2D_DrawSprite(&sprites[index]);
}

void C2D_draw_text(std::string str, int x0, int y0, int x1, int y1, int size, uint32_t color){
	color = (((color & 0x0000FF) << 16) | (color & 0x00FF00) | ((color & 0xFF0000) >> 16)) | 0xFF000000;
	float x, y, width = 0;
	float sizef = size * (0.5/(float)16);
	C2D_Text text;
	C2D_TextBuf buffer = C2D_TextBufNew(324);
	C2D_TextFontParse(&text, font, buffer, str.c_str());
	C2D_TextGetDimensions(&text, sizef, sizef, &width, NULL);
	x = round((((x1 - x0) + 1) - width)/(float)2) + x0;
	y = round((((y1 - y0) + 1) - size)/(float)2) + y0 - 2;
	
	C2D_TextOptimize(&text);
	C2D_DrawText(&text, C2D_WithColor, x, y, 0.5f, sizef, sizef, color);
	C2D_TextBufDelete(buffer);
}

void C2D_draw_text(std::string str, int x, int y, int size, uint32_t color){
	color = (((color & 0x0000FF) << 16) | (color & 0x00FF00) | ((color & 0xFF0000) >> 16)) | 0xFF000000;
	float sizef = size * (0.5/(float)16);
	C2D_Text text;
	C2D_TextBuf buffer = C2D_TextBufNew(324);
	C2D_TextFontParse(&text, font, buffer, str.c_str());
	C2D_TextOptimize(&text);
	C2D_DrawText(&text, C2D_WithColor, (float)x, (float)y, 0.5f, sizef, sizef, color);
	C2D_TextBufDelete(buffer);
}