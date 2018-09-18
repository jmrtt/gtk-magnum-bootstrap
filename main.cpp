#include "ApplicationWindow.h"
#include <gtkmm/application.h>

int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.magnumexample");

    ApplicationWindow window;
    return app->run(window);
}
