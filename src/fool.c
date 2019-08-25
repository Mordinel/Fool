#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fool.h"

void open_file_if_possible(char *path, FILE **file, char *type) {
    if (access(path, F_OK|R_OK) == -1) {
        *file = NULL;
    } else {
        *file = fopen(path, type);
    }
}

void write_bytes(char **bytes, FILE **in_file, FILE **out_file) {
    int i, c;

    for(i = 0; (c = *(*bytes + i)) != 0x0; i++) {
        fputc(c, *out_file);
    }
    while ((c = fgetc(*in_file)) != EOF) {
        fputc(c, *out_file);
    }
}

char *get_extension(char *str) {
    int i, ext_start;
    int str_length;
    char *extension;

    ext_start = -1;
    for (i = 0; *(str + i) != '\0'; i++) {
        if (*(str + i) == DELIM) {
            ext_start = i;
        }
    }

    if (ext_start == -1) {
        return NULL;
    }

    str_length = (int)strlen(str);
    extension = (char *)malloc(sizeof(char) * (str_length - ext_start));

    for (i = 0; *(str + ++ext_start) != '\0'; i++) {
        *(extension + i) = *(str + ext_start);
    }

    return extension;
}

void load_magic_bytes(char **magic_bytes, char *extension) {
    int i;
    int magic_bytes_len = strlen(extension);
    char *extension_lower = (char *)malloc(sizeof(char) * magic_bytes_len);

    for (i = 0; i < magic_bytes_len; i++) {
        *(extension_lower + i) = tolower(*(extension + i));
    }

    if (strncmp(extension_lower, "gif", 4) == 0) {
        allocate_magic_bytes(magic_bytes, GIF_BYTES);
    } else {
        *magic_bytes = NULL;
    }

    free(extension_lower);
}

void allocate_magic_bytes(char **magic_bytes, char *bytes) {
    int bytes_len = strlen(bytes);
    *magic_bytes = (char *)malloc(sizeof(char) * bytes_len);
    strncpy(*magic_bytes, bytes, bytes_len);
}

int main(int argc, char *argv[]) {
    FILE *in_file, *out_file;
    char *magic_bytes, *extension;

    if (argc != 3) {
        fprintf(stderr, "Usage:\n%s [IN_FILE] [OUT_FILE.EXTENSION]\n", argv[0]);
        return 1;
    }

    extension = get_extension(argv[2]);
    if (extension == NULL) {
        fprintf(stderr, "Path: \"%s\" doesn't contain an extension.\n", argv[2]);
        return 1;
    }

    open_file_if_possible(argv[1], &in_file, "r");
    if (in_file == NULL) {
        fprintf(stderr, "\"%s\" can not be accessed for reading.\n", argv[1]);
        return 1;
    }

    out_file = fopen(argv[2], "w");

    load_magic_bytes(&magic_bytes, extension);

    if (magic_bytes != NULL) {
        write_bytes(&magic_bytes, &in_file, &out_file);
    } else {
        fprintf(stderr, "Extension: \"%s\" not supported\n", extension);
        remove(argv[2]);
    }

    fclose(in_file);
    fclose(out_file);

    free(magic_bytes);
    free(extension);

    return 0;
}
