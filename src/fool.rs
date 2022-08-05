use std::fs;
use std::io::{ErrorKind};
use std::path::Path;
use std::collections::HashMap;

struct Magic {
    head: Vec<u8>,
    tail: Vec<u8>,
}

fn get_magicks() -> HashMap<&'static str, Magic> {
    let magic = HashMap::<&'static str, Magic>::from([
        ("gif", Magic { head: b"\x47\x49\x46\x38\x39\x61".to_vec(), tail: b"".to_vec() }),
        ("jpg", Magic { head: b"\xFF\xD8".to_vec(), tail: b"".to_vec() }),
        ("png", Magic { head: b"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A".to_vec(), tail: b"\x49\x45\x4E\x44\xAE\x42\x60\x82".to_vec() }),
    ]);
    return magic;
}

pub fn write_file(in_file_path: &Path, out_file_path: &Path) -> String {
    // read file in
    let in_file_contents = match fs::read(in_file_path) {
        Err(e) => match e.kind() {
            ErrorKind::NotFound => return format!("{:?} not found", in_file_path),
            ErrorKind::PermissionDenied => return format!("Read permission denied to {:?}", in_file_path),
            _ => return "Something failed during file read...".to_string(),
        },
        Ok(f) => f,
    };

    // get out file extension
    let out_file_extension = match out_file_path.extension() {
        None => return format!("No extension for {:?}!", out_file_path.file_name()),
        Some(thing) => thing
            .to_str()
            .unwrap()
            .to_lowercase(),
    };

    // generate the magic bytes hashmap
    let magicks = get_magicks();
    let magic = match magicks.get(out_file_extension.as_str()) {
        None => return format!("No magic values for .{}", out_file_extension),
        Some(thing) => thing,
    };

    // concat the magic bytes and infile
    let mut out_file_contents: Vec<u8> = Vec::new();
    out_file_contents.extend(&magic.head);
    out_file_contents.extend(&in_file_contents);
    out_file_contents.extend(&magic.tail);

    // write the file out
    match fs::write(out_file_path, out_file_contents) {
        Err(e) => match e.kind() {
            ErrorKind::PermissionDenied => return format!("Write permission denied to {:?}", out_file_path),
            _ => return "Something failed during file write...".to_string(),
        }
        _ => "",
    };
    
    return format!("Success creating {:?}", out_file_path);
}
