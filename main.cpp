#include <iostream>
#include <gtkmm.h>

#include "csvmanipull.hpp"

class window : public Gtk::Window {
public:
    window() {
        set_title("Test Window");
        set_default_size(400, 200);

        m_rotulo.set_text("Hello World!");
        set_child(m_rotulo);
    }

private:
    Gtk::Label m_rotulo;
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.sample.window");

    return app->make_window_and_run<window>(argc, argv);
}