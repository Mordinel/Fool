use std::path::Path;
mod fool;

fn main() {
    let args: Vec<String> = std::env::args().collect();

    if args.len() != 3 {
        println!("Usage: {} <in file> <out file.extension>", args[0]);
        return;
    }

    let in_file = Path::new(&args[1]);
    let out_file = Path::new(&args[2]);
    println!("{}", fool::write_file(in_file, out_file));
}
