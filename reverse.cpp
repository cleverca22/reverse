#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>


int main(int argc,char *argv[]){
	char towav[512],lamecmd[512];
	towav[0]=lamecmd[0]=0;
	int in,remaining=0,bytesr=0,empty;
	int size=0,errsv;
	char *data=NULL;
	char *dataout=NULL;
	char *buf;
	struct stat sizeinfo;
	if (argc!=3)return argc;
	strcpy(towav,"mplayer \"");
	strcat(towav,argv[1]);
	strcat(towav,"\" -srate 44100 -ao pcm:nowaveheader:file=reverse.a:fast -channels 1");
	if(system(towav)==-1)return -1;
	in=open("reverse.a",O_RDONLY);
	//for (int x=0;x<26157312;x++){
	//	read(in,y,1);
	//	data[x]=y[0];
	//	remaining++;
	//}
	if(in <0)return -1;
	if(fstat(in,&sizeinfo)!=0)return 0;
	size=sizeinfo.st_size;
printf("a");
/*data   =new char[size];
printf("b");
	buf=data;
	empty=size;
	while(bytesr=read(in,buf,empty)){
		buf=buf+bytesr;
		empty=empty-bytesr;
		remaining=remaining+bytesr;
	}*/
	data=(char*)mmap(NULL,size,PROT_READ,MAP_SHARED,in,0);
	close(in);
	int out=open("reverse.b",O_CREAT|O_RDWR|O_TRUNC,0644);
	if(out<0)return 5;
	lseek(out,size-1,SEEK_SET);
	write(out,data,1);
	dataout=(char*)mmap(NULL,size,PROT_WRITE|PROT_READ,MAP_SHARED,out,0);
	errsv=errno;
	close(out);
	if(dataout==(char*)-1){
	 printf("error %d\n",errsv);
	 return -2;
	}
printf("c");
//dataout=new char[size];
printf("d");
	remaining=size;
	int y=0;
	for(int x=remaining;x>0;x--){
		if(y%(1024*1024)==0){
			printf(".");
			fflush(stdout);
			msync(dataout,size,MS_SYNC);
		}
		dataout[y]=data[x];
		y++;
	}
printf("e");
//delete [] data;
	munmap(data,size);
printf("f");
data=NULL;
	int bytes=0,offset=0;
/*	while(bytes=write(out,dataout,remaining)){
		dataout=dataout+bytes;
		remaining=remaining-bytes;
	}*/
printf("g");
//delete [] dataout;
	munmap(dataout,size);
dataout=NULL;
printf("h");
	strcpy(lamecmd,"lame -s 44.1 -x reverse.b \"");
	strcat(lamecmd,argv[2]);
	strcat(lamecmd,"\"");
	system(lamecmd);
	return 0;
}
