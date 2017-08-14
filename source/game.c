#include "global.h"

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

void CheckGame(){
	int y;
	for(y = 0; y < 6; y++){
		gametitle result = getName(list[y], 1);
		if(InitGame(result.titleid, result.name) == result.titleid){
			active[y] = 1;
		}
		else{
			active[y] = 0;
		}
	}
}

int ChooseGame(char* game){
	gameversion = game;
	gametitle result = getName(game, 0);
	if(InitGame(result.titleid, result.name) == result.titleid){
		gamepath = result.name;
		titleid = result.titleid;
		if(GetArch() == 0){
			InitSD(result.name, "+");
		}
		return 1;
	}
	else{
		return 0;
	}
	return 0;
}

void GetSaveInfo(char* directory){
	FILE *mainfile;
	unsigned char buffer;
	char* temp = gamepath;
	char* filepath = "null";
	filepath = calloc(strlen(temp) + 5, 1);
	sprintf(filepath, "%s/%s", temp, "main");
	mainfile = fopen(filepath, "r+");
	trainer[0] = '\0';
	if((strcmp(gameversion, "S") != 0) && (strcmp(gameversion, "M") != 0)){
		for(x = 0x14048; x < 0x14062; x+=2){
			fseek(mainfile, x, SEEK_SET);
			fread(&buffer, 1, 1, mainfile);
			if(buffer != 0x0){
				sprintf(trainer, "%s%c", trainer, buffer);
			}
		}
		fseek(mainfile, 0x1801, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		hour = buffer * 256;
		fseek(mainfile, 0x1800, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		hour = buffer + hour;
		fseek(mainfile, 0x1802, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		minute = buffer;
	}
	else{
		for(x = 0x1238; x < 0x1254; x+=2){
			fseek(mainfile, x, SEEK_SET);
			fread(&buffer, 1, 1, mainfile);
			if(buffer != 0x0){
				sprintf(trainer, "%s%c", trainer, buffer);
			}
		}
		fseek(mainfile, 0x40C01, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		hour = buffer * 256;
		fseek(mainfile, 0x40C00, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		hour = buffer + hour;
		fseek(mainfile, 0x40C02, SEEK_SET);
		fread(&buffer, 1, 1, mainfile);
		minute = buffer;
	}
	fclose(mainfile);	
}