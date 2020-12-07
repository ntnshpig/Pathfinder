#include "../inc/pathfinder.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    parse_file(argv[1]);
}
