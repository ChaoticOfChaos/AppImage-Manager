use std::fs;
use std::io;
use std::path::Path;
use std::error::Error;
use std::process::Command;

pub fn list_dir(dir: impl AsRef<Path>) -> io::Result<Vec<String>> {
    Ok(fs::read_dir(dir)?
        .filter_map(Result::ok)
        .filter(|e| e.file_type().map(|t| t.is_file()).unwrap_or(false))
        .filter_map(|e| {
            e.path()
                .file_stem()
                .map(|s| s.to_string_lossy().into_owned())
        })
    .collect())
}

pub fn exec_appimage(appimage_name: String) -> Result<(), Box<dyn Error>> {
    let config_path = dirs::config_dir().ok_or("Open Config Path Error")?;
    let mut reader = csv::Reader::from_path(config_path.join("appimage-manager/settings.csv"))?;

    for result in reader.records() {
        let reg = result?;
        
        if reg.get(0) == Some(appimage_name.as_str()) {
            let runner = Command::new(&reg[1]).spawn()?;
            println!("Stating AppImage {}", &reg[1]);
            return Ok(());
        }
    }


    Ok(())
}

pub fn copy_appimage(appimage_name: String, appimage_path: String) -> Result<(), Box<dyn Error>> {
    let origin_path = Path::new(&appimage_path);
    let config_dir = dirs::config_dir().ok_or("Open Config Path Error")?;
    let destiny_dir = config_dir.join("appimage-manager/appimages");
    let config_file_path = config_dir.join("appimage-manager/settings.csv");

    let name = origin_path
        .file_name()
        .ok_or("File Path Dont Exist")?;

    let destiny_file = destiny_dir.join(name);
    fs::copy(origin_path, &destiny_file)?;

    let file = fs::OpenOptions::new()
        .append(true)
        .create(true)
        .open(config_file_path)?;

    let mut writer = csv::WriterBuilder::new()
        .has_headers(false)
        .from_writer(file);

    writer.write_record([appimage_name.as_str(), destiny_file.to_string_lossy().as_ref()])?;
    writer.flush()?;

    Ok(())
}

pub fn list_appimages_installed() -> Result<Vec<String>, Box<dyn Error>> {
    let mut returner: Vec<String> = Vec::new();
    let config_dir = dirs::config_dir().ok_or("Open Config Path Error")?;
    let config_file_path = config_dir.join("appimage-manager/settings.csv");

    let mut reader = csv::Reader::from_path(config_file_path)?;

    for result in reader.records() {
        let reg = result?;
        returner.push(reg[0].to_string());
    }


    Ok(returner)
}

pub fn verify_folder() -> Result<(), Box<dyn Error>> {
    let config_dir = dirs::config_dir().ok_or("Open Config Path Error")?;
    let folder = config_dir.join("appimage-manager/appimages/");

    if !folder.exists() {
        fs::create_dir_all(folder)?;
    }


    Ok(())
}

pub fn verify_file() -> Result<(), Box<dyn Error>> {
    let config_dir = dirs::config_dir().ok_or("Open Config Path Error")?;
    let config_file = config_dir.join("appimage-manager/settings.csv");

    if !config_file.exists() {
        fs::write(&config_file, "name,path\n")?;
    }


    Ok(())
}
