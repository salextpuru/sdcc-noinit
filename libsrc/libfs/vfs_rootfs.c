#include <string.h>
#include <stdlib.h>
#include <stat.h>
#include "vfs_rootfs.h"

static const char* rootfs_dirs[]={
	"bin",
	"etc",
	"dev",
	"proc",
	"sys",
	"tmp",
	"var",
	NULL
};

static zDir* rootfs_opendir(struct zFileSystem* fs, const char *name, zDir* dir){
	if( *(name+fs->mpoint->mpathlen) ){
		return NULL;
	}
	
	memset(dir,0,sizeof(zDir));
	dir->mpoint=fs->mpoint;
	return dir;
}

static zDirent* rootfs_readdir(struct zFileSystem* fs, zDir *dirp){
	fs;
	if( rootfs_dirs[dirp->d_off] == 0 ){
		return 0;
	}
	
	dirp->dirent.d_mode=0777;
	dirp->dirent.d_type=S_IFDIR;
	strcpy(dirp->dirent.d_name, rootfs_dirs[dirp->d_off++]);
	
	return(&dirp->dirent);
}

static int rootfs_closedir(struct zFileSystem* fs, zDir *dirp){
	fs;dirp;
	return 0;
}

zFileSystem kvfs_rootfs= {
	.fstype=FS_ROOT,
	.mpoint=&kmpoints[0],
	.opendir = rootfs_opendir,
	.readdir = rootfs_readdir,
	.closedir = rootfs_closedir
};
