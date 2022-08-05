# Fool

## Description
Fool is a program designed to spoof mime types on text files using magic bytes in order to aid in successful exploitation of file upload vulnerabilities.

## Usage
```
target/release/fool [IN_FILE] [OUT_FILE.EXTENSION]
```
In order to select a mime type, use the corresponding file extension commonly seen for that filetype.
eg:
```
target/release/fool payload.php payload.png
```

The following extensions types are currently supported by fool:
- gif
- jpg
- png

## Building
```
cargo build --release
```

## References
[File Signature List](https://www.garykessler.net/library/file_sigs.html)
