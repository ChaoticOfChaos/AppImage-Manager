#include <iostream>
#include <gtkmm.h>

#include "csvmanipull.hpp"
#include "libs.hpp"

class window : public Gtk::Window {
public:
    window(const std::vector<std::string>& appImages) : m_box(Gtk::Orientation::VERTICAL, 10), m_button_box(Gtk::Orientation::VERTICAL, 5) {

        Gtk::Settings::get_default()->property_gtk_application_prefer_dark_theme() = true;
        set_title("AppImage Manager");
        set_default_size(800, 600);

        m_box.set_margin(20);
        m_frame.set_text("None Clicks Yet!");

        m_box.append(m_frame);
        
        for (const auto& appImage : appImages) {

            auto* button = Gtk::make_managed<Gtk::Button>(appImage);

            button->signal_clicked().connect([this, name = appImage] {

                m_frame.set_text("You Selected: " + name);
                exec_appimage(name);

            });

            m_button_box.append(*button);

        }

        m_box.append(m_button_box);
        set_child(m_box);

    }

private:
    Gtk::Box m_box, m_button_box;
    Gtk::Label m_frame;

};

int main(int argc, char* argv[]) {
    CSVManipulation::ReadFile config_file("./settings.csv");
    if (config_file.read() != 0) system("touch ./settings.csv");

    std::vector<std::string> appImages;

    appImages = listDir("./appimages/");

    auto app = Gtk::Application::create("org.appimage.manager");
    return app->make_window_and_run<window>(argc, argv, appImages);

}
