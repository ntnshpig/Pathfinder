#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
	if(!file)  return NULL;
	
	int file1 = open(file, O_RDONLY);
	int file2 = open(file, O_RDONLY);
	//Can`t open
	if(file1 < 0){
		close(file1);
		mx_printerr("error: file ");
        mx_printerr(file); 
        mx_printerr(" does not exist\n");
		exit(-1);
		return NULL;
	}

	int filelen = 0;
	char buf;

    while(read(file2, &buf, 1))
        filelen++;
	
	//Empty file
	if(filelen == 0) {
		mx_printerr("error: file ");
        mx_printerr(file); 
        mx_printerr(" is empty\n");
		exit(-1);
	}

	char *str = mx_strnew(filelen);

	read(file1, str, filelen);
	close(file1);
	
	return str;
}
