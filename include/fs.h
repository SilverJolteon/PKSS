#ifndef FS_H
#define FS_H

#include <3ds.h>
#include <citro2d.h>
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

struct smdhHeader_s{
    uint32_t magic;
    uint16_t version;
    uint16_t reserved;
};

struct smdhTitle_s{
    uint16_t shortDescription[0x40];
    uint16_t longDescription[0x80];
    uint16_t publisher[0x40];
};

struct smdhSettings_s{
    uint8_t gameRatings[0x10];
    uint32_t regionLock;
    uint8_t matchMakerId[0xC];
    uint32_t flags;
    uint16_t eulaVersion;
    uint16_t reserved;
    uint16_t defaultFrame;
    uint32_t cecId;
};

struct smdh_s{
    smdhHeader_s header;
    smdhTitle_s applicationTitles[16];
    smdhSettings_s settings;
    uint8_t reserved[0x8];
    uint8_t smallIconData[0x480];
    uint16_t bigIconData[0x900];
};

extern std::string SAVE_PATH;
extern FS_Archive sdmc_arch, game_arch;
extern FS_MediaType mediatype;

char* uint162int8(uint16_t* in);

namespace FS{
	void directory(std::string dir, bool option);
	C2D_Sprite getIcon(uint64_t titleid, FS_MediaType mediatype, int w, int h);
	std::string getTitle(uint64_t titleid, FS_MediaType mediatype);
	dir_t getDirs(std::string path);
	file_t getFiles(FS_Archive arch, std::string path);
	char* fileToBuffer(FS_Archive arch, std::string dirpath, std::string filename);
	void bufferToFile(FS_Archive arch, char* buffer, uint64_t size, std::string dirpath, std::string filename);
	uint64_t int82uint64(FS_Archive arch, std::string filepath);
}

#endif