#ifndef FOOL_H
#define FOOL_H

#define DELIM '.'
#define GIF_BYTES "\x47\x49\x46\x38\x39\x61"
#define JPG_BYTES "\xFF\xD8"

extern void open_file_if_possible(char *path, FILE **file, char *type);
extern void write_bytes(char **bytes, FILE **in_file, FILE **out_file);
extern char *get_extension(char *str);
extern void load_magic_bytes(char **magic_bytes, char *extension);
extern void allocate_magic_bytes(char **magic_bytes, char *bytes);

#endif