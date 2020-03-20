#progma once
#include <gtkmm.h>
#include <gdkmm/color.h>


void render_color_to_window(
        const Cairo::RefPtr<Cairo::Context> &cr, 
        const Gdk::Rectangle &ca, 
        const Gdk::Color &color
);

class Widget_Color : public Gtk::DrawingArea 
{
private:
    Gdk::Color color;

    sigc::signal<void> signal_activate_;

public:
    sigc::signal<void>& signal_activate() { return signal_activate_; }
    sigc::signal<void>& signal_clicked() { return signal_activate_; }

    const Gdk::Color& get_value const;
    void set_value(const Gdk::Color &x);

    Widget_Color();
    ~Widget_Color();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool on_event(GdkEvent *event);
};


