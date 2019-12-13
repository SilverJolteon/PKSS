#ifndef FS_H
#define FS_H

#include <3ds.h>
#include <iostream>
#include <vector>

#define CREATE_DIR 0
#define DELETE_DIR 1

struct file_t{
	int num = 0;
	std::vector<std::string> data;
};

struct dir_t{
	int num = 0;
	std::vector<std::string> data;
};

extern std::string SAVE_PATH;
extern FS_Archive sdmc_arch, game_arch;
extern FS_MediaType mediatype;

namespace FS{
	void directory(std::string dir, bool option);
	dir_t getDirs(std::string path);
	file_t getFiles(FS_Archive arch, std::string path);
	char* fileToBuffer(FS_Archive arch, std::string dirpath, std::string filename);
	void bufferToFile(FS_Archive arch, char* buffer, uint64_t size, std::string dirpath, std::string filename);
	uint64_t int82uint64(FS_Archive arch, std::string filepath);
}

#endif