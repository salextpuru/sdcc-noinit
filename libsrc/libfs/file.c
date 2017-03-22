#include <file.h>
#include <vfs_devfs.h>
#include <vfs_rootfs.h>
#include <string.h>
#include <stdlib.h>
#include <stat.h>

#define MAXPATH_LEN	0x100

zMpoint	kmpoints[MPOINTS_MAX]={
	// RootFS (virtual)
	{
		.dev	= NULL,		// No device
		.minor	= 0,		// Fake number
		.mpath	= "/",		// Mount path
		.mpathlen = 1,		// path len
		.fs	= &kvfs_rootfs,	// fs
		.flags	= MFL_MOUNTED	// Mounted
	},
	// DevFS (virtual)
	{
		.dev	= NULL,		// No device
		.minor	= 0,		// Fake number
		.mpath	= "/dev",	// Mount path
		.mpathlen = 4,		// path len
		.fs	= &kvfs_devfs,	// fs
		.flags	= MFL_MOUNTED	// Mounted
	}
};

// Описатели файлов
static zFile  kfiles[FILES_MAX];
// Указатели на описатели файлов. NULL - файл закрыт. 
static zFile* pkfiles[FILES_MAX];

static char cwd[MAXPATH_LEN];

char *getcwd(char *buf, uint16_t size){
	return cwd;
}

int8_t chdir(const char *path){
	strcpy(cwd, path);
	return 0;
}

zMpoint* kgetmpoint(const char* fullpath){
	uint16_t lmax=0;
	zMpoint* r=NULL;
	zMpoint* b=kmpoints;
	zMpoint* e=kmpoints+MPOINTS_MAX;
	
	while( e!=b){
		//
		if( !strncmp(b->mpath, fullpath, b->mpathlen) ){
			if( lmax<b->mpathlen ){
				lmax=b->mpathlen;
				r=b;
			}
		}
		//
		b++;
	}

	return r;
}

zDir*	opendir(const char *path, zDir* dir){
	zFileSystem* fs;
	zMpoint* mp=kgetmpoint(path);
	if(!mp){
		return  NULL;
	}
	fs = mp->fs;
	
	if(! fs->opendir(fs, path, dir) ){
		return  NULL;
	}
	
	fs->lcounter++;
	
	return dir;
}

int closedir(zDir* dirp){
	zFileSystem* fs;
	if(! dirp ){
		return  -1;
	}
	fs=dirp->mpoint->fs;
	if( fs->closedir) {
		if(fs->closedir(fs, dirp)){
			return -1;
		}
	}
	if(fs->lcounter){
		fs->lcounter--;
	}
	return 0;
}

zDirent* readdir(zDir *dirp){
	zFileSystem* fs;
	if(! dirp ){
		return  NULL;
	}
	fs=dirp->mpoint->fs;
	return fs->readdir(fs,dirp);
}

// Найти и зарезервировать место для файла
static int16_t getSpaceForFile (zFile* f){
	int8_t i;
	for(i=0; i<FILES_MAX; i++){
		if( !pkfiles[i] ){
			pkfiles[i] = f = kfiles + i;
			memset(f, 0, sizeof(zFile) );
			return i;
		}
	}
	f=NULL;
	return -1;
}

static void freeFile(int16_t fd){
	pkfiles[fd]=NULL;
}

int16_t open(const char* path, uint16_t flags, ...){
	va_list va;
	uint16_t mode;
	zFileSystem* fs;
	int16_t fd;
	zFile* f;
	zMpoint* mp=kgetmpoint(path);
	//
	if(!mp){
		return  NULL;
	}
	fs = mp->fs;
	// Есть ли место?
	fd=getSpaceForFile (f);
	if( fd<0){
		// нету
		return -1;
	}
	//
	va_start(va, flags);
	va_arg(mode, uint16_t);
	// Эти флаги уже инициализированы
	f->f_flags = flags;
	f->mpoint = fs->mpoint;
	f->f_mode = mode;
	// Пробуем открыть файл
	if(! fs->open(f, path, flags, mode) ){
		// Не удалось
		freeFile(fd);
		return -1;
	}
	// Удалосики
	fs->lcounter++;
	return fd;
}

int16_t close(uint16_t fd){
	zFileSystem* fs;
	zFile* f=pkfiles[fd];
	if( ! f ){
		return -1;
	}
	
	fs=f->mpoint->fs;
	
	if( fs->close(f) ){
		return -1;
	}
	
	pkfiles[fd]=NULL;
	fs->lcounter--;
	
	return 0;
}
