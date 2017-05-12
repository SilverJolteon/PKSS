#include "global.h"

FS_Archive InitSD(char* directory){
	FSUSER_OpenArchive(&sdmc_arch, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	if(directory != NULL){
		FSUSER_CreateDirectory(sdmc_arch, fsMakePath(PATH_ASCII, directory), 0);
	}
	return 0;
}

u64 InitGame(u64 titleid, char* name){
	u64 read = 0;
	u32 num_sdtitles;
	u64* sd_titles;
	amInit();
	AM_GetTitleCount(mediatype, &num_sdtitles);
	sd_titles = malloc(num_sdtitles*sizeof(u64));
	AM_GetTitleList(NULL, mediatype, num_sdtitles, sd_titles);
	for(x = 0; x < (signed)num_sdtitles; x++){
		if(sd_titles[x] == titleid){
			read = titleid;
		}
	}
	amExit();
	return read;
}

FS_Archive GetArch(){
	int error = 0;
	u32* path;
	FS_Path game_binpath;
	
	lowerid = (u32)(titleid);
	upperid = (u32)(titleid >> 32);
	
	path = (u32[3]){mediatype, lowerid, upperid};
	game_binpath = (FS_Path){PATH_BINARY, 12, path};
	error = FSUSER_OpenArchive(&game_arch, ARCHIVE_USER_SAVEDATA, game_binpath);
	if(error != 0){
		return 1;
	}
	return 0;
}