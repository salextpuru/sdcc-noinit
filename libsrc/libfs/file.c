#include <file.h>
#include <stdlib.h>

static zMpoint	kmpoints[MPOINTS_MAX]={
	// RootFS (virtual)
	{
		.dev	= NULL,		// No device
		.minor	= 0,		// Fake number
		.mpath	= "/",		// Mount path
		.fstype	= FS_ROOT,	// ROOTFS type
		.flags	= MFL_MOUNTED	// Mounted
	},
	// DevFS (virtual)
	{
		.dev	= NULL,		// No device
		.minor	= 0,		// Fake number
		.mpath	= "/dev",	// Mount path
		.fstype	= FS_DEV,	// ROOTFS type
		.flags	= MFL_MOUNTED	// Mounted
	}
};

static zDir* rootfs_opendir(struct zFileSystem* fs, const char *name, zDir* dir){
	name; dir;
	return 0;
}

static zDirent* rootfs_readdir(struct zFileSystem* fs, zDir *dirp, zDirent *entry){
	dirp; entry;
	return 0;
}

static int rootfs_closedir(struct zFileSystem* fs, zDir *dirp){
	dirp;
	return 0;
}

static zFileSystem rootfs= {
	.fstype=FS_ROOT,
	.mpoint=&kmpoints[0],
	.opendir = rootfs_opendir,
	.readdir = rootfs_readdir,
	.closedir = rootfs_closedir
};

static zDir* devfs_opendir(struct zFileSystem* fs, const char *name, zDir* dir){
	name; dir;
	return 0;
}

static zDirent* devfs_readdir(struct zFileSystem* fs, zDir *dirp, zDirent *entry){
	dirp; entry;
	return 0;
}

static int devfs_closedir(struct zFileSystem* fs, zDir *dirp){
	dirp;
	return 0;
}

static zFileSystem devfs= {
	.fstype=FS_ROOT,
	.mpoint=&kmpoints[0],
	.opendir = devfs_opendir,
	.readdir = devfs_readdir,
	.closedir = devfs_closedir
};
