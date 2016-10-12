#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int isopen(int fd){

	struct stat buffer;

	int in = fstat(fd, &buffer);
	if(in == 0){
		return 1;
	}else if(in < 0){
		printf("Errno: %d\n", errno);
		return 0;
	}	
}


int main(void){
	int nopen, fd, in;

	in = open("nopen.c", O_RDONLY);

	for(nopen = fd = 0; fd < getdtablesize(); fd++){
		printf("Valor do nopen: %d\n", nopen);
		if(isopen(fd)){
			nopen++;
		}
	}

	printf("Existem %d descritores abertos\n", nopen);

	return 0;
}