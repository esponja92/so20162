#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

char* mode;

int walk_dir (const char *path, void (*func) (const char *)){

	printf("Chegou aqui pelo menos\n");

	DIR *dirp;
	struct dirent *dp;
	char *p, *full_path;
	int len;

	/* abre o diretório */

	if ((dirp = opendir (path)) == NULL)
		return (-1);

	len = strlen (path);

	/* aloca uma área na qual, garantidamente, o caminho caberá */
	if ((full_path = malloc (len + NAME_MAX + 2)) == NULL){

		closedir (dirp);
		return (-1);
	}

	/* copia o prefixo e acrescenta a ‘/’ ao final */
	memcpy (full_path, path, len);
	p = full_path + len; 
	*p++ = '/'; /* deixa “p” no lugar certo! */

	while ((dp = readdir (dirp)) != NULL){

		/* ignora as entradas “.” e “..” */
		if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0)
			continue;

		strcpy (p, dp->d_name);

		/* “full_path” armazena o caminho */
		(*func) (full_path);
	}

	free (full_path);
	closedir (dirp);
	return (0);

} /* end walk_dir */

void contador(const char *diretorio){
	printf("A função contador recebeu %s\n", diretorio);
}

int main(int argc, char** argv){

	int rdlbc;
	char* caminho;

	/*
	Trata as opções
	*/
	rdlbc = getopt(argc,argv,"rdlbc");
	switch(rdlbc){
		case 'r':
			printf("r\n");
			break;
		case 'd':
			printf("d\n");
			break;
		case 'l':
			printf("l\n");
			break;
		case 'b':
			printf("b\n");
			break;
		case 'c':
			printf("c\n");
			break;
		case '?':
			printf("Parametro não aceito. Seguindo com default -d\n");
		default:
			printf("r\n");
	}

	/*
	Verifica se o usuário informou algum caminho. Se não, o caminho setado é o "."
	*/
	if(argv[argc - 1][0] == '/'){
		caminho = argv[argc - 1];
	}
	else{
		caminho = ".";
	}

	//printf("%s\n", caminho);
	walk_dir(caminho, &contador);

	return 0;
}
