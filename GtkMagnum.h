#ifndef GTK_MAGNUM_GL_H
#define GTK_MAGNUM_GL_H

#include <gtkmm/glarea.h>
#include <Magnum/Platform/GLContext.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>

class GtkMagnum : public Gtk::GLArea {
public:
    GtkMagnum();

private:
    /**
     * @brief Method to handle the realize signal, that is emitted when the widget is associated with a
     * Gdk::Window, which mean the signal was called or the widget has been mapped
     */
    void onRealize();

    /**
     * @brief Method to handle signal render, which is emitted every time the contents of the Gtk::GLArea
     * should be redrawn.
     * @param context Gdk::GLContext that is used be GLArea
     * @return true if success, or false otherwise
     */
    bool onRender(const Glib::RefPtr<Gdk::GLContext>& context[[maybe_unused]]);

    /**
     * @brief Called when unrealize signal is called to delete magnum objects while OpenGL context is sill
     * available, since Gtk::GLArea destructor is only called after the parent has destroyed OpenGL
     */
    void onUnrealize();

private:
    /**
     * @brief _context gets the GL context created by GTK GLArea and stores the information for magnum use
     */
    std::unique_ptr<Magnum::Platform::GLContext> _context;

    /**
     * @brief Holds Magnum objects that can only be created when a context is available
     */
    struct MagnumObjects {
        Magnum::GL::Buffer buffer;
        Magnum::GL::Mesh mesh;
        Magnum::Shaders::VertexColor2D shader;
    };

    std::unique_ptr<MagnumObjects> _magnumObjs;
};

#endif // GTK_MAGNUM_GL_H
