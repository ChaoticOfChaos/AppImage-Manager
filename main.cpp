#include <iostream>
#include <gtkmm.h>

#include "csvmanipull.hpp"
#include "libs.hpp"

class window : public Gtk::Window {
public:
    window(const std::vector<std::string>& appImages) : m_box(Gtk::Orientation::VERTICAL, 10) {
        set_title("AppImage Manager");
        set_default_size(800, 600);

        m_box.set_margin(20);
        m_frame.set_text("None Clicks Yet!");
        m_button.set_label("Click Here!");

        m_button.signal_clicked().connect(sigc::mem_fun(*this, &window::on_click));

        m_box.append(m_frame);
        m_box.append(m_button);
        set_child(m_box);
    }

private:
    void on_click() {
        m_clicks++;
        m_frame.set_text("Clicks: " + std::to_string(m_clicks));
    }

    Gtk::Box m_box;
    Gtk::Label m_frame;
    Gtk::Button m_button;
    int m_clicks = 0;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> appImages;

    appImages = listDir("./appimages/");

    auto app = Gtk::Application::create("org.appimage.manager");
    return app->make_window_and_run<window>(argc, argv, appImages);
}