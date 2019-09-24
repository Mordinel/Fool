/*
 *  fool.h
 *  Authored by: Mason Soroka-Gill
 */

#ifndef FOOL_H
#define FOOL_H

#define DELIM '.'

#include "signatures.h"

extern void open_file_if_possible(char *path, FILE **file);
extern void write_bytes(char **magic_bytes, char **magic_trailer, FILE **in_file, FILE **out_file);
extern char *get_extension(char *str);
extern void load_magic_bytes(char **magic_bytes, char **magic_trailer, char *extension);
extern void allocate_magic_bytes(char **magic_bytes, char *bytes);

#endif
