#include <string.h>
#include <stdlib.h>
#include <stat.h>
#include <vfs_devfs.h>

static zDir* devfs_opendir(struct zFileSystem* fs, const char *name, zDir* dir){
	if( *(name+fs->mpoint->mpathlen) ){
		return NULL;
	}
	
	memset(dir,0,sizeof(zDir));
	dir->mpoint=fs->mpoint;
	return dir;
}


extern zDevice* kdevlist[];
static zDirent* devfs_readdir(struct zFileSystem* fs, zDir *dirp){
	fs;
	if( kdevlist[dirp->d_off] == 0 ){
		return 0;
	}
	
	dirp->dirent.d_mode= 0666;
	dirp->dirent.d_type=kdevlist[dirp->d_off]->devtype;
	strcpy(dirp->dirent.d_name, kdevlist[dirp->d_off++]->devname);
	
	return(&dirp->dirent);
}

static int devfs_closedir(struct zFileSystem* fs, zDir *dirp){
	fs;dirp;
	return 0;
}

zFileSystem kvfs_devfs= {
	.fstype=FS_ROOT,
	.mpoint=&kmpoints[1],
	.opendir = devfs_opendir,
	.readdir = devfs_readdir,
	.closedir = devfs_closedir
};
