#ifndef FOOL_H
#define FOOL_H

#define DELIM '.'
#define GIF_BYTES "\x47\x49\x46\x38\x39\x61"
#define JPG_BYTES "\xFF\xD8"
#define PNG_BYTES "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"
#define PNG_TRAILER "\x49\x45\x4E\x44\xAE\x42\x60\x82"

extern void open_file_if_possible(char *path, FILE **file);
extern void write_bytes(char **magic_bytes, char **magic_trailer, FILE **in_file, FILE **out_file);
extern char *get_extension(char *str);
extern void load_magic_bytes(char **magic_bytes, char **magic_trailer, char *extension);
extern void allocate_magic_bytes(char **magic_bytes, char *bytes);

#endif