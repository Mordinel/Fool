/*
 *  fool.c
 *  Authored by: Mason Soroka-Gill
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fool.h"

/**
 * Opens a file at path, if file exists and is readable.
 */
void open_file_if_possible(char *path, FILE **file) {
    if (access(path, F_OK|R_OK) == -1) {
        *file = NULL;
    } else {
        *file = fopen(path, "r");
    }
}

/**
 * Writes file signature bits at head and tail of in_file to out_file.
 */
void write_bytes(char **magic_bytes, char **magic_trailer, FILE **in_file, FILE **out_file) {
    int i, c;
    /* write header */
    for(i = 0; (c = *(*magic_bytes + i)) != 0x0; i++) {
        fputc(c, *out_file);
    }
    /* write in file data */
    while ((c = fgetc(*in_file)) != EOF) {
        fputc(c, *out_file);
    }
    /* write tail data if it exists */
    if (*magic_trailer != NULL) {
        for(i = 0; (c = *(*magic_trailer + i)) != 0x0; i++) {
            fputc(c, *out_file);
        }
    }
}

/**
 * Returns char pointer to bytes after the last '.' char in string.
 */
char *get_extension(char *str) {
    int i, ext_start;
    int str_length;
    char *extension;

    /* finds index of last DELIM */
    ext_start = -1;
    for (i = 0; *(str + i) != '\0'; i++) {
        if (*(str + i) == DELIM) {
            ext_start = i;
        }
    }

    if (ext_start == -1) {
        return NULL;
    }

    /* allocates memory for extension string */
    str_length = strlen(str);
    extension = (char *)malloc(sizeof(char) * (str_length - ext_start));

    /* write the bytes to new allocated memory */
    for (i = 0; *(str + ++ext_start) != '\0'; i++) {
        *(extension + i) = *(str + ext_start);
    }

    return extension;
}

/**
 * Takes magic bytes pointers, writes the bytes that correspond with the given
 * extension to the pointers.
 */
void load_magic_bytes(char **magic_bytes, char **magic_trailer, char *extension) {
    int i;
    int magic_bytes_len = strlen(extension);
    char *extension_lower = (char *)malloc(sizeof(char) * magic_bytes_len);

    /* converts extension to lower case */
    for (i = 0; i < magic_bytes_len; i++) {
        *(extension_lower + i) = tolower(*(extension + i));
    }

    /* if extension is gif */
    if (strncmp(extension_lower, "gif", 4) == 0) {
        allocate_magic_bytes(magic_bytes, GIF_BYTES);

    /* if extension is a jpeg variant */
    } else if((strncmp(extension_lower, "jpg", 4) == 0) ||
              (strncmp(extension_lower, "jpe", 4) == 0) ||
              (strncmp(extension_lower, "jpeg", 5) == 0)) {
        allocate_magic_bytes(magic_bytes, JPG_BYTES);

    /* if extension is png */
    } else if(strncmp(extension_lower, "png", 4) == 0) {
        allocate_magic_bytes(magic_bytes, PNG_BYTES);
        allocate_magic_bytes(magic_trailer, PNG_TRAILER);

    } else {
        *magic_bytes = NULL;
    }

    free(extension_lower);
}

/**
 * Allocates memory depending on the bytes passed in, copies the bytes to the
 * magic bytes pointer.
 */
void allocate_magic_bytes(char **magic_bytes, char *bytes) {
    int bytes_len = strlen(bytes);
    *magic_bytes = (char *)malloc(sizeof(char) * bytes_len);
    strncpy(*magic_bytes, bytes, bytes_len);
}

int main(int argc, char *argv[]) {
    FILE *in_file, *out_file;
    char *magic_bytes, *magic_trailer, *extension;

    /* incorrect amount of command line operators shows basic help */
    if (argc != 3) {
        fprintf(stderr, "Usage:\n%s [IN_FILE] [OUT_FILE.EXTENSION]\n", argv[0]);
        return 1;
    }

    /* checks last operator for an extension */
    extension = get_extension(argv[2]);
    if (extension == NULL) {
        fprintf(stderr, "Path: \"%s\" doesn't contain an extension.\n", argv[2]);
        return 1;
    }

    /* open the in file for reading */
    open_file_if_possible(argv[1], &in_file);
    if (in_file == NULL) {
        fprintf(stderr, "\"%s\" can not be accessed for reading.\n", argv[1]);
        return 1;
    }

    /* open the out file path for writing */
    out_file = fopen(argv[2], "w");

    magic_bytes = magic_trailer = NULL;
    load_magic_bytes(&magic_bytes, &magic_trailer, extension);

    if (magic_bytes != NULL) {
        write_bytes(&magic_bytes, &magic_trailer, &in_file, &out_file);
    } else {
        fprintf(stderr, "Extension: \"%s\" not supported\n", extension);
        remove(argv[2]);
    }

    /* close file streams & free allocated memory */
    fclose(in_file);
    fclose(out_file);

    free(magic_bytes);
    free(magic_trailer);
    free(extension);

    return 0;
}
