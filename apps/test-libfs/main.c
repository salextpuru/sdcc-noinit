#include <stdlib.h>
#include <conio.h>
//
#include <file.h>


void ls(const char* path){
	static zDir dir;
	
	zDirent* dentry;
	if( opendir(path, &dir ) ){
		printf("[%s] opendir\n",path);
	}
	else{
		printf("[%s] can't opendir\n",path);
		return;
	}
	
	while( dentry = readdir(&dir) ){
		printf("%s %O %O\n",dentry->d_name, dentry->d_type, dentry->d_mode);
	}
}

int main(){
	ccls(016);
	//
// 	printf("%s\n", kgetmpoint("/rc")->mpath );
// 	printf("%s\n", kgetmpoint("/mnt")->mpath );
// 	printf("%s\n", kgetmpoint("/dev/sda")->mpath );
// 	printf("%s\n", kgetmpoint("/")->mpath );
	
	ls("/");
	ls("/fake");
	ls("/dev");
	
	//
	while(1){}
	return 0;
}
