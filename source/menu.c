#include "global.h"

int Menu(){
	CheckGame();
	consoleClear();
	printf("\x1b[0m");
	printf("\x1b[0;0H%s", header);
	printf("\x1b[2;0H");
	if(active[0] == 1){
		printf("X: Left\n");
	}
	if(active[1] == 1){
		printf("Y: Right\n");
	}
	if(active[2] == 1){
		printf("Omega Ruby: Up\n");
	}
	if(active[3] == 1){
		printf("Alpha Sapphire: Down\n");
	}
	if(active[4] == 1){
		printf("Sun: X\n");
	}
	if(active[5] == 1){
		printf("Moon: Y");
	}
	
	while(aptMainLoop()){
		hidScanInput();
		u32 kDown = hidKeysDown();
		
		int chose = 0;
		
		if(kDown & (KEY_START)){
			break;
		}
		if((kDown & KEY_DLEFT) && (ChooseGame("X") == 1) && (active[0] == 1)){
			chose = 1;
			num = 0;
		}
		if((kDown & KEY_DRIGHT) && (ChooseGame("Y") == 1) && (active[1] == 1)){
			chose = 1;
			num = 1;
		}
		if((kDown & KEY_DUP) && (ChooseGame("OR") == 1) && (active[2] == 1)){
			chose = 1;
			num = 2;
		}
		if((kDown & KEY_DDOWN) && (ChooseGame("AS") == 1) && (active[3] == 1)){
			chose = 1;
			num = 3;
		}
		if((kDown & KEY_X) && (ChooseGame("S") == 1) && (active[4] == 1)){
			chose = 1;
			num = 4;
		}
		if((kDown & KEY_Y) && (ChooseGame("M") == 1) && (active[5] == 1)){
			chose = 1;
			num = 5;
		}
		if(chose == 1){
			GetArch();
			Backup();
			printf("\x1b[0m");
			printf("\x1b[6;0HBacked up to sdmc:%s", gamepath);
		}
		
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();		
	}
	gfxExit();
	return 0;
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