#include "global.h"

char* version = "0.5.1";
char* header;
char list[6][2] = {"X", "Y", "OR", "AS", "S", "M"};
int num, entries[6] = {-1, -1, -1, -1, -1, -1}, active[] = {0, 0, 0, 0, 0, 0};;
char saves[6][64][64];
char* dir = "/PKSS";
char* dir2 = "null";
char* dir3 = "null";
char* gameversion = "null";
char* gamepath = "null";
u32 lowerid, upperid;
u64 titleid;
FS_Archive sdmc_arch, game_arch;
FS_MediaType mediatype = MEDIATYPE_SD;

gametitle getName(char* game, int check){
	char* dir2 = calloc(strlen("/PKSS") + 20, 1);
	
	if(strcmp(game, "X") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_X", dir);
		}
		gametitle result = {0x0004000000055D00, dir2};
		return result;
	}
	else if(strcmp(game, "Y") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_Y", dir);
		}
		gametitle result = {0x0004000000055E00, dir2};
		return result;
	}
	else if(strcmp(game, "OR") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_Omega_Ruby", dir);
		}
		gametitle result = {0x000400000011C400, dir2};
		return result;
	}
	else if(strcmp(game, "AS") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_Alpha_Sapphire", dir);
		}
		gametitle result = {0x000400000011C500, dir2};
		return result;
	}
	else if(strcmp(game, "S") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_Sun", dir);
		}
		gametitle result = {0x0004000000164800, dir2};
		return result;
	}
	else if(strcmp(game, "M") == 0){
		if(check == 0){
			sprintf(dir2, "%s/Pokemon_Moon", dir);
		}
		gametitle result = {0x0004000000175E00, dir2};
		return result;
	}
	gametitle result = {0x0, "/PKSS/NULL"};
	return result;
}

int main(){
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	consoleClear();
	header = calloc(strlen("PKSS v") + 10, 1);
	sprintf(header, "PKSS v%s", version);
	printf("\x1b[0m");
	printf("\x1b[0;0H%s", header);
	ReadConfig();
	Menu();
	return 0;
}

int ChooseGame(char* game){
	gameversion = game;
	consoleClear();
	printf("\x1b[0m");
	printf("\x1b[0;0H%s", header);
	printf("\x1b[2;0HReading Game...");
	gametitle result = getName(game, 0);
	if(InitGame(result.titleid, result.name) == result.titleid){
		printf("\x1b[4;0H");
		printf("\x1b[32mRead Game!\x1b[2m");
		InitSD(result.name);
		gamepath = result.name;
		titleid = result.titleid;
		return 1;
	}
	else{
		printf("\x1b[4;0H");
		printf("\x1b[31mFailed to read game!\x1b[2m");
		return 0;
	}
	return 0;
}

char* InitPath(char* pathname){
	char* dir3 = calloc(strlen(pathname) + 20, 1);
	gametitle result = getName(gameversion, 0);
	sprintf(dir3, "%s/%s", result.name, pathname);
	return dir3;
}

char* GetString(char* desc){
	SwkbdState state;
	char* input = calloc(64, 1);
	
	swkbdInit(&state, SWKBD_TYPE_QWERTY, 2, 64);
	swkbdSetHintText(&state, desc);

	swkbdInputText(&state, input, 64);
	if(strcmp(input, "") == 0){
		return NULL;
	}
	char* temp = gamepath;
	char* temp2 = "null";
	temp2 = calloc(strlen(temp) + strlen(input) + 10, 1);
	sprintf(temp2, "%s/%s", temp, input);
	gamepath = temp2;
	return input;
}