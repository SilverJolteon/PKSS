#include "global.h"

char* version = "v0.6.5";
char* header;
char list[6][4] = {"X", "Y", "OR", "AS", "S", "M"};
int num, page = 1, fontspace = 30, entries[6] = {0, 0, 0, 0, 0, 0}, active[] = {0, 0, 0, 0, 0, 0};
char saves[6][64][64];
char* dir = "/PKSS";
char* dir2 = NULL;
char* dir3 = NULL;
char* gameversion = NULL;
char* gamepath = NULL;
u32 lowerid, upperid;
u64 titleid;
FS_Archive sdmc_arch, game_arch;
FS_MediaType mediatype = MEDIATYPE_SD;
sftd_font* font;
sftd_font* fontb;
sf2d_texture* top;
sf2d_texture* bottom;
sf2d_texture* UI;
sf2d_texture* blank;
sf2d_texture* saveslots;

int main(){
	InitGFX();
	header = calloc(strlen("PKSS v") + 10, 1);
	sprintf(header, "PKSS %s", version);
	ReadConfig();
	Menu();
	FinitGFX();
	return 0;
}