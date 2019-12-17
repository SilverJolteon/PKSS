#include "FS.h"

std::string SAVE_PATH = "/PKSS";
FS_Archive sdmc_arch, game_arch;
FS_MediaType mediatype = MEDIATYPE_SD;

void FS::directory(std::string dir, bool option){
	FSUSER_OpenArchive(&sdmc_arch, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	if(option == CREATE_DIR){
		FSUSER_CreateDirectory(sdmc_arch, fsMakePath(PATH_ASCII, dir.c_str()), 0);
	}
	else if(option == DELETE_DIR){
		FSUSER_DeleteDirectoryRecursively(sdmc_arch, fsMakePath(PATH_ASCII, dir.c_str()));
	}	
}

char* uint162int8(uint16_t* in){
	char* out = (char*)malloc(1);
	int i = 1;
	while(in[i-1] < 128){
		out[i-1] = (char)(in[i-1]);
		i++;
		out = (char*)realloc(out, i);
	}
	return out;
}

smdh_s* loadSMDH(uint64_t titleid, FS_MediaType mediatype){
	uint32_t low = (uint32_t)titleid;
	uint32_t high = (uint32_t)(titleid >> 32);
	Handle handle;
	uint32_t archpath[] = {low, high, mediatype, 0};
	uint32_t filepath[] = {0x0, 0x0, 0x2, 0x6E6F6369, 0x0};
	FS_Path archpath_bin = {PATH_BINARY, 0x10, archpath};
    FS_Path filepath_bin = {PATH_BINARY, 0x14, filepath};
	FSUSER_OpenFileDirectly(&handle, ARCHIVE_SAVEDATA_AND_CONTENT, archpath_bin, filepath_bin, FS_OPEN_READ, 0);
	uint32_t read = 0;
	smdh_s *smdh = new smdh_s;
	FSFILE_Read(handle, &read, 0, smdh, sizeof(smdh_s));
	FSFILE_Close(handle);
	return smdh;
}

C2D_Sprite FS::getIcon(uint64_t titleid, FS_MediaType mediatype, int w, int h){
	smdh_s *smdh = loadSMDH(titleid, mediatype);
	C3D_Tex* tex = new C3D_Tex;
	static constexpr Tex3DS_SubTexture subtexture = {48, 48, 0.0f, 48 / 64.0f, 48 / 64.0f, 0.0f};
	C3D_TexInit(tex, 64, 64, GPU_RGB565);
	tex->border = 0xFFFFFFFF;
	C3D_TexSetWrap(tex, GPU_CLAMP_TO_BORDER, GPU_CLAMP_TO_BORDER);
	uint16_t* dst = (uint16_t*)tex->data + (64 - 48) * 64;
	uint16_t* src = (uint16_t*)smdh->bigIconData;
	for(int i = 0; i < 48; i+=8){
		std::copy(src, src + 48 * 8, dst);
		src += 48 * 8;
		dst += 64 * 8;
	}
	C2D_Sprite icon;
	C2D_SpriteFromImage(&icon, C2D_Image{tex, &subtexture});
	C2D_SpriteScale(&icon, w/48.0f, h/48.0f);
	return icon;
}

std::string FS::getTitle(uint64_t ID, FS_MediaType mediatype){
	smdh_s *smdh = loadSMDH(ID, mediatype);
	return std::string(uint162int8((uint16_t *)smdh->applicationTitles[1].shortDescription));
}

dir_t FS::getDirs(std::string path){
	Handle handle;
	dir_t dirs;
	uint32_t read;
	FS_DirectoryEntry get_ent;
	FSUSER_OpenArchive(&sdmc_arch, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&handle, sdmc_arch, fsMakePath(PATH_ASCII, path.c_str()));
	do{
		FSDIR_Read(handle, &read, 1, &get_ent);
		if(read == 1){
			dirs.num++;
			dirs.data.push_back(uint162int8(get_ent.name));
		}
	}while(read > 0);
	FSDIR_Close(handle);
	return dirs;
}

file_t FS::getFiles(FS_Archive arch, std::string path){
	Handle handle;
	file_t files;
	uint32_t read;
	FS_DirectoryEntry get_ent;
	if(arch == sdmc_arch) FSUSER_OpenArchive(&arch, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
	FSUSER_OpenDirectory(&handle, arch, fsMakePath(PATH_ASCII, path.c_str()));
	do{
		FSDIR_Read(handle, &read, 1, &get_ent);
		if(read == 1){
			files.num++;
			files.data.push_back(uint162int8(get_ent.name));
		}
	}while(read > 0);
	FSDIR_Close(handle);
	return files;
}

char* FS::fileToBuffer(FS_Archive arch, std::string dirpath, std::string filename){
	uint32_t read;
	uint64_t filesize;
	std::string file_in = dirpath + filename;
	char* buffer = NULL;
	Handle file_handle;
	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, file_in.c_str()), FS_OPEN_READ, 0);
	FSFILE_GetSize(file_handle, &filesize);
	buffer = (char*)malloc(filesize+1);
	FSFILE_Read(file_handle, &read, 0, buffer, filesize);
	FSFILE_Close(file_handle);
	return buffer;
}

void FS::bufferToFile(FS_Archive arch, char* buffer, uint64_t size, std::string dirpath, std::string filename){
	uint32_t written;
	std::string file_out = dirpath + "/" + filename;
	Handle file_handle;
	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, file_out.c_str()), FS_OPEN_WRITE | FS_OPEN_CREATE, 0);
	FSFILE_Write(file_handle, &written, 0, buffer, size, FS_WRITE_FLUSH | FS_WRITE_UPDATE_TIME);
	if(arch == game_arch){
		FSUSER_ControlArchive(game_arch, ARCHIVE_ACTION_COMMIT_SAVE_DATA, NULL, 0, NULL, 0);
	}
	FSFILE_Close(file_handle);
}

uint64_t FS::int82uint64(FS_Archive arch, std::string filepath){
	uint64_t filesize;
	Handle file_handle;
	FSUSER_OpenFile(&file_handle, arch, fsMakePath(PATH_ASCII, filepath.c_str()), FS_OPEN_READ, 0);
	FSFILE_GetSize(file_handle, &filesize);
	FSFILE_Close(file_handle);
	return filesize;
}

