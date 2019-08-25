#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void open_file_if_possible(char *path, FILE **file, char *type) {
    if (access(path, F_OK|R_OK) == -1) {
        fprintf(stderr, "\"%s\" can not be accessed for \"%s\".\n", path, type);
        *file = NULL;
    } else {
        *file = fopen(path, type); 
    }
}

void write_bytes(char **bytes, FILE **in_file, FILE **out_file) {
    int i;
    int c;

    for(i = 0; (c = *(*bytes + i)) != 0x0; i++) {
        fputc(c, *out_file);
    }
    while ((c = fgetc(*in_file)) != EOF) {
        fputc(c, *out_file);
    }
}

int main(int argc, char *argv[]) {
    FILE *code_file;
    FILE *out_file;
    char *magic_bytes;
    int code_file_length;

    if (argc != 3) {
        fprintf(stderr, "Usage:\n%s [infile] [outfile]\n", argv[0]);
        return 1;
    }

    open_file_if_possible(argv[1], &code_file, "r");
    if (code_file == NULL) {
       return 1;
    }
    
    out_file = fopen(argv[2], "w");
    free(out_file);

    magic_bytes = (char *)malloc(sizeof(char)*6);
    strncpy(magic_bytes, "\x47\x49\x46\x38\x39\x61", 6);

    write_bytes(&magic_bytes, &code_file, &out_file);

    fclose(code_file);
    fclose(out_file);

    return 0;
}
