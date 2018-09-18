#include "GtkMagnum.h"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Vector2.h>

using namespace Magnum::Math::Literals;

GtkMagnum::GtkMagnum()
{
    set_size_request(800, 600);

    set_required_version(4, 5); // desired gl version

    signal_realize().connect(sigc::mem_fun(this, &GtkMagnum::onRealize));
    signal_render().connect(sigc::mem_fun(this, &GtkMagnum::onRender));
    signal_unrealize().connect(sigc::mem_fun(this, &GtkMagnum::onUnrealize));
}

void GtkMagnum::onRealize()
{
    throw_if_error();
    make_current();
    _context = std::make_unique<Magnum::Platform::GLContext>();

    _magnumObjs = std::make_unique<MagnumObjects>();

    struct TriangleVertex {
        Magnum::Vector2 position;
        Magnum::Color3 color;
    };
    const TriangleVertex data[]{
        { { -0.5f, -0.5f }, 0xff0000_rgbf }, /* Left vertex, red color */
        { { 0.5f, -0.5f }, 0x00ff00_rgbf }, /* Right vertex, green color */
        { { 0.0f, 0.5f }, 0x0000ff_rgbf } /* Top vertex, blue color */
    };

    _magnumObjs->buffer.setData(data, Magnum::GL::BufferUsage::StaticDraw);
    _magnumObjs->mesh.setPrimitive(Magnum::GL::MeshPrimitive::Triangles)
        .setCount(3)
        .addVertexBuffer(_magnumObjs->buffer, 0, Magnum::Shaders::VertexColor2D::Position{},
            Magnum::Shaders::VertexColor2D::Color{
                Magnum::Shaders::VertexColor2D::Color::Components::Three });
}

bool GtkMagnum::onRender(const Glib::RefPtr<Gdk::GLContext>& context[[maybe_unused]])
{
    // Clear canvas:
    Magnum::GL::defaultFramebuffer.clear(Magnum::GL::FramebufferClear::Color | Magnum::GL::FramebufferClear::Depth);

    _magnumObjs->mesh.draw(_magnumObjs->shader);

    queue_draw();
    return true;
}

void GtkMagnum::onUnrealize()
{
    _context.reset();
}
