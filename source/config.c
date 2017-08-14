#include "global.h"

void ReadConfig(){
	FILE *config;
	char line[64];
	int sgame = 0, toggle = 0, l = -1;
	
	config = fopen("/PKSS/config", "r+");
	
	if(!(config = fopen("/PKSS/config", "r+"))){
		InitSD("/PKSS", "+");
		config = fopen("/PKSS/config", "w");
	}
	memset(&saves[0], 0, sizeof(saves));
	for(x = 0; x < 6; x++){
		entries[x] = 0;
	}
	while(fgets(line, sizeof(line), config) != NULL){
		if((line[0] == 'X') && (line[1] == ':')){
			sgame = 0, toggle = 1, l = -1;
		}
		if((line[0] == 'Y') && (line[1] == ':')){
			sgame = 1, toggle = 1, l = -1;
		}
		if((line[0] == 'O') && (line[1] == 'R') && (line[2] == ':')){
			sgame = 2, toggle = 1, l = -1;
		}
		if((line[0] == 'A') && (line[1] == 'S') && (line[2] == ':')){
			sgame = 3, toggle = 1, l = -1;
		}
		if((line[0] == 'S') && (line[1] == ':')){
			sgame = 4, toggle = 1, l = -1;
		}
		if((line[0] == 'M') && (line[1] == ':')){
			sgame = 5, toggle = 1, l = -1;
		}
		if((line[0] == '{') || (line[0] == '}')){
			toggle = 1, l = -1;
		}
		if(line[0] == '|'){
			toggle = 1, l--;
		}
		if((toggle == 0) && (line != NULL)){
			char temp[64] = "";
			for(x = 0; x < strlen(line)-1; x++){
				sprintf(temp, "%s%c", temp, line[x]);
			}
			sprintf(saves[sgame][l], temp);
			entries[sgame]++;
		}
		toggle = 0;
		l++;
	}
	fclose(config);	
}

void WriteConfig(){
	int i;
	FILE *config;
	config = fopen("/PKSS/config", "w");
	
	fprintf(config, "{\nX:");
	for(i = 0; i < entries[0]; i++){
		if(entries[0] > 0){
			fprintf(config, "\n%s", saves[0][i]);
		}
	}
	fprintf(config, "\n}\n{\nY:");
	for(i = 0; i < entries[1]; i++){
		if(entries[1] > 0){
			fprintf(config, "\n%s", saves[1][i]);
		}
	}
	fprintf(config, "\n}\n{\nOR:");
	for(i = 0; i < entries[2]; i++){
		if(entries[2] > 0){
			fprintf(config, "\n%s", saves[2][i]);
		}
	}
	fprintf(config, "\n}\n{\nAS:");
	for(i = 0; i < entries[3]; i++){
		if(entries[3] > 0){
			fprintf(config, "\n%s", saves[3][i]);
		}
	}
	fprintf(config, "\n}\n{\nS:");
	for(i = 0; i < entries[4]; i++){
		if(entries[4] > 0){
			fprintf(config, "\n%s", saves[4][i]);
		}
	}
	fprintf(config, "\n}\n{\nM:");
	for(i = 0; i < entries[5]; i++){
		if(entries[5] > 0){
			fprintf(config, "\n%s", saves[5][i]);
		}
	}
	fprintf(config, "\n}");
	fclose(config);
}