#include <iostream>
#include <gtkmm.h>

#include "csvmanipull.hpp"
#include "libs.hpp"

class add_window : public Gtk::Window {
public:
    add_window() : m_box(Gtk::Orientation::VERTICAL, 10), m_button("Send") {
        set_title("AppImage Manager / Add New");
        set_default_size(300, 150);

        m_box.set_margin(10);

        m_entry1.set_placeholder_text("AppImage Name");
        m_entry2.set_placeholder_text("AppImage Path");

        m_box.append(m_entry1);
        m_box.append(m_entry2);
        m_box.append(m_button);

        set_child(m_box);

        m_button.signal_clicked().connect(sigc::mem_fun(*this, &add_window::on_button_clicked));
    }

private:
    void on_button_clicked() {
        copy_appimage(m_entry1.get_text(), m_entry2.get_text());
    }

    Gtk::Box m_box;
    Gtk::Entry m_entry1, m_entry2;
    Gtk::Button m_button;
};

class window : public Gtk::Window {
public:
    window(const std::vector<std::string>& appImages) : m_box(Gtk::Orientation::VERTICAL, 10), m_button_box(Gtk::Orientation::VERTICAL, 5) {

        Gtk::Settings::get_default()->property_gtk_application_prefer_dark_theme() = true;
        set_title("AppImage Manager");
        set_default_size(800, 600);

        m_box.set_margin(20);
        m_label.set_text("AppImage Manager");

        m_add_button.signal_clicked().connect(sigc::mem_fun(*this, &window::call_add_window));
        m_add_button.set_label("Add New AppImage");
        m_box.append(m_add_button);

        m_box.append(m_label);
        
        for (const auto& appImage : appImages) {

            auto* button = Gtk::make_managed<Gtk::Button>(appImage);

            button->signal_clicked().connect([this, name = appImage] {

                m_label.set_text("Starting: " + name);
                exec_appimage(name);

            });

            m_button_box.append(*button);

        }

        m_box.append(m_button_box);
        set_child(m_box);

    }

private:
    void call_add_window() {
        if (!m_second) {
            m_second = std::make_unique<add_window>();
            m_second->set_transient_for(*this);

            m_second->signal_hide().connect([this]() { m_second.reset(); });
        }
        m_second->present();
    }

    Gtk::Box m_box, m_button_box;
    Gtk::Label m_label;
    Gtk::Button m_add_button;
    std::unique_ptr<add_window> m_second;

};

int main(int argc, char* argv[]) {
    CSVManipulation::ReadFile config_file("./settings.csv");
    if (config_file.read() != 0) system("touch ./settings.csv");

    std::vector<std::string> appImages;

    appImages = listDir("./appimages/");

    auto app = Gtk::Application::create("org.appimage.manager");
    return app->make_window_and_run<window>(argc, argv, appImages);

}
