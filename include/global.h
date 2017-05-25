#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <sfil.h>

#include "font_ttf.h"
#include "bottom_png.h"
#define AREA(px, py, xmin, ymin, xmax, ymax) ((px < xmax && px > xmin) && (py < ymax && py > ymin))

int x, ChooseGame(), buffer_to_file(), DisplaySaves();
char* InitPath();
char* GetString();
char* get_files();
char* file_to_buffer();
char* u16str2str();
FS_Archive InitSD(), GetArch();
u64 InitGame(), filesize_to_u64(), GetTitleID();
void InitGFX(), FinitGFX(), DisplayText(), Menu(), Menu2(), CheckGame(), Backup(), ReadConfig(), WriteConfig();

extern int num, fontspace, active[], entries[6];
extern char list[6][4];
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
extern sf2d_texture* img;

typedef struct{
	u64 titleid;
	char* name;
}gametitle;

gametitle getName();