use gtk4::prelude::*;
use gtk4::{glib, Settings, Application, ApplicationWindow, Box, Label, Button, Orientation, Entry, Window};
mod libs;
use libs::{ list_dir, exec_appimage, copy_appimage, list_appimages_installed, verify_file, verify_folder };

fn main() -> glib::ExitCode {

    verify_folder();
    verify_file();


    let app = Application::builder()
        .application_id("org.appimage.manager")
        .build();

    app.connect_activate(|app| {
        if let Some(settings) = Settings::default() {
            settings.set_gtk_application_prefer_dark_theme(true);
        }

        let m_box = Box::builder()
            .orientation(Orientation::Vertical)
            .spacing(5)
            .build();

        let m_label = Label::builder()
            .label("AppImages")
            .build();

        let m_add_button = Button::builder()
            .icon_name("list-add-symbolic")
            .tooltip_text("Add New")
            .build();
        m_box.append(&m_add_button);

        let m_refresh_button = Button::builder()
            .icon_name("view-refresh-symbolic")
            .tooltip_text("Refresh")
            .build();
        // m_refresh_button.connect_clicked(|b| );
        m_box.append(&m_refresh_button);

        m_box.append(&m_label);


        let m_button_box = Box::builder()
            .orientation(Orientation::Vertical)
            .build();

        
        let appimages_list: Vec<String> = match list_appimages_installed() {
            Ok(v) => v,
            Err(e) => {
                eprintln!("{e}");
                return;
            }
        };

        for appimage in appimages_list {
            let m_din_button = Button::with_label(&appimage);
            m_din_button.connect_clicked(move |_| {
                if let Err(e) = libs::exec_appimage(appimage.clone()) {
                    eprintln!("{e}");
                }
            });

            m_button_box.append(&m_din_button);
        }

        m_box.append(&m_button_box);

        m_refresh_button.connect_clicked(move |_| {
            let appimages_list: Vec<String> = match list_appimages_installed() {
                Ok(v) => v,
                Err(e) => {
                    eprintln!("{e}");
                    return;
                }
            };

            while let Some(child) = m_button_box.first_child() {
                m_button_box.remove(&child);
            }

            for appimage in appimages_list {
                let m_din_button = Button::with_label(&appimage);
                m_din_button.connect_clicked(move |_| {
                    if let Err(e) = libs::exec_appimage(appimage.clone()) {
                        eprintln!("{e}");
                    }
                });

                m_button_box.append(&m_din_button);
            }
        });


        let window = ApplicationWindow::builder()
            .application(app)
            .title("AppImage Manager")
            .default_width(800)
            .default_height(600)
            .child(&m_box)
            .build();




        let principal = window.clone();
        m_add_button.connect_clicked(move |_| {
            let m_second_box = Box::builder()
                .orientation(Orientation::Vertical)
                .build();

            let m_entry1 = Entry::builder()
                .placeholder_text("AppImage Name")
                .build();

            let m_entry2 = Entry::builder()
                .placeholder_text("AppImage Path")
                .build();


            let m_clone_entry1 = m_entry1.clone();
            let m_clone_entry2 = m_entry2.clone();
            let m_enter_button = Button::with_label("Send");
            m_enter_button.connect_clicked(move |_| {
                copy_appimage(m_clone_entry1.text().to_string(), m_clone_entry2.text().to_string());
            });


            m_second_box.append(&m_entry1);
            m_second_box.append(&m_entry2);
            m_second_box.append(&m_enter_button);


            let add_window = Window::builder()
                .title("AppImage Manager / Add New")
                .default_width(300)
                .default_height(150)
                .transient_for(&principal)
                .modal(true)
                .child(&m_second_box)
                .build();

            add_window.present();
        });




        window.present();
    });

    app.run()
}
