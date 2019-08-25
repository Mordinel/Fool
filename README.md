# Fool

## Description
Fool is a program designed to spoof mime types on text files using magic bytes in order to aid in successful exploitation of file upload vulnerabilities.

## Usage
```
./fool [IN_FILE] [OUT_FILE.EXTENSION]
```
In order to select a mime type, use the corresponding file extension commonly seen for that filetype.
eg:
```
./fool payload.php payload.png
```

The following mime types are currently supported by fool:
- gif
- png
- jpg, jpeg

## Building
```
gcc fool.c -o fool
```
