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

static char cwd[MAXPATH_LEN];

char *getcwd(char *buf, uint16_t size){
	return cwd;
}

int8_t chdir(const char *path){
	strcpy(cwd, path);
	return 0;
}
