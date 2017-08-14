#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>

#include "font_ttf.h"
#include "fontb_ttf.h"
#include "top_png.h"
#include "bottom_png.h"
#include "UI_png.h"
#include "savemenu_png.h"
#include "blank_png.h"
#include "saves_png.h"
#include "cursorl_png.h"
#include "cursorr_png.h"
#include "arrowl_png.h"
#include "arrowr_png.h"
#define AREA(px, py, xmin, ymin, xmax, ymax) ((px < xmax && px > xmin) && (py < ymax && py > ymin))

int x, page, ChooseGame(), buffer_to_file();
char* InitPath();
char* GetString();
char* get_files();
char* file_to_buffer();
char* u16str2str();
FS_Archive InitSD(), GetArch();
u64 InitGame(), filesize_to_u64(), GetTitleID();
void InitGFX(), FinitGFX(), DisplayText(), Menu(), Menu2(), Menu3(), CheckGame(), Backup(), ReadConfig(), WriteConfig(), GetSaveInfo();

extern int num, fontspace, active[], entries[6], hour, minute;
extern char list[6][4];
extern char listdir[6][32];
extern char trainer[16];
extern char saves[6][64][64];
extern char* version;
extern char* header;
extern char* dir;
extern char* dir2;
extern char* dir3;
extern char* gameversion;
extern char* gamepath;
extern u32 lowerid, upperid;
extern u64 titleid;
extern FS_Archive sdmc_arch, game_arch;
extern FS_MediaType mediatype;
extern sftd_font* font;
extern sftd_font* fontb;
extern sf2d_texture* top;
extern sf2d_texture* bottom;
extern sf2d_texture* UI;
extern sf2d_texture* savemenu;
extern sf2d_texture* blank;
extern sf2d_texture* saveslots;
extern sf2d_texture* cursorl;
extern sf2d_texture* cursorr;
extern sf2d_texture* arrowl;
extern sf2d_texture* arrowr;

typedef struct{
	u64 titleid;
	char* name;
}gametitle;

typedef struct{
	int InitX;
	int InitY;
}CenterText;

gametitle getName();

CenterText Center();