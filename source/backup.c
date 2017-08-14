#include "global.h"

void Backup(){
	char* savename = GetString("Enter Save Name");
	InitSD(InitPath(savename), "+");
	char* file;
	u64 size;
	char* filepath;
	char* buf;
	
	file = get_files(game_arch, "/");
	buf = file_to_buffer(game_arch, "/", file);
	filepath = calloc(strlen("/")+strlen(file)+1, 1);
	sprintf(filepath, "/%s", file);
	size = filesize_to_u64(game_arch, filepath);
	buffer_to_file(sdmc_arch, buf, size, gamepath, file);
	free(filepath);
	free(buf);
	
	entries[num]++;
	sprintf((saves[num][entries[num] - 1]), "%s", savename);
	
	WriteConfig();
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