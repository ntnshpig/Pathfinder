#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd){
    if (buf_size < 0 || fd <= 0 || buf_size > 2147483647) return -2;

    buf_size = 1;
    int byte = 0;
    char buf;
    size_t res_bytes = 0;
    mx_strdel(lineptr);
        if ((byte = read(fd, &buf, buf_size)) > 0){
            *lineptr = mx_strjoin(*lineptr, &buf);
            res_bytes += (size_t)byte;
        }
        else {
            return -1;
        }
        while((byte = read(fd, &buf, buf_size)) > 0) {
            if(delim == buf) break;
            res_bytes += (size_t)byte;
            *lineptr = mx_strjoin(*lineptr, &buf);
        }
    return res_bytes;
}
