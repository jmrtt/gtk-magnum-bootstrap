#ifndef GTKMM_APPLICATION_WINDOW_H
#define GTKMM_APPLICATION_WINDOW_H

#include "GtkMagnum.h"

#include <gtkmm/window.h>

class ApplicationWindow : public Gtk::Window {

public:
    ApplicationWindow();
    virtual ~ApplicationWindow();

protected:
    GtkMagnum _glArea;
};

#endif // GTKMM_APPLICATION_WINDOW_H
