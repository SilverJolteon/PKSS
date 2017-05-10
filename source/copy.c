#include "global.h"

char* get_files(FS_Archive arch, char* path){
	Handle handle;
	char* files;
	u32 read;
	FS_DirectoryEntry get_ent;
	
	FSUSER_OpenDirectory(&handle, arch, fsMakePath(PATH_ASCII, path));
	files = NULL;
	FSDIR_Read(handle, &read, 1, &get_ent);
	files = realloc(files, 1*sizeof(char*));
	files = u16str2str(get_ent.name);
	FSDIR_Close(handle);

	return files;
}

char* file_to_buffer(FS_Archive arch, char* dirpath, char* filename){
	u32 read;
	u64 file_size;
	char* file_in;
	char* buffer = NULL;
	Handle file_handle;
	
	file_in = calloc(strlen(dirpath)+strlen(filename)+1, 1);
	sprintf(file_in, "%s%s", dirpath, filename);
	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, file_in), FS_OPEN_READ, 0);
	free(file_in);
	FSFILE_GetSize(file_handle, &file_size);
	buffer = malloc(file_size+1);
	FSFILE_Read(file_handle, &read, 0, buffer, file_size);
	FSFILE_Close(file_handle);
	return buffer;
}

int buffer_to_file(FS_Archive arch, char* buffer, u64 size, char* dirpath, char* filename){
	u32 written;
	char* file_out;
	Handle file_handle;
	
	file_out = calloc(strlen(dirpath)+strlen(filename)+1, 1);
	sprintf(file_out, "%s/%s", dirpath, filename);
	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, file_out), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
	free(file_out);
	FSFILE_Write(file_handle, &written, 0, buffer, size, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
	if(arch == game_arch){
		FSUSER_ControlArchive(game_arch, ARCHIVE_ACTION_COMMIT_SAVE_DATA, NULL, 0, NULL, 0);
	}
	
	return 0;
}

char* u16str2str(u16* wstr){
	int len = 0;
	char* str;

	str = malloc(1);
	len++;
	while(wstr[len-1] < 128){
		str[len-1] = (char)(wstr[len-1]);
		len++;
		str = realloc(str, len);
	}

	return str;
}

u64 filesize_to_u64(FS_Archive arch, char* filepath){
	u64 file_size;
	Handle file_handle;

	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, filepath), FS_OPEN_READ, 0);
	FSFILE_GetSize(file_handle, &file_size);
	FSFILE_Close(file_handle);
	return file_size;
}