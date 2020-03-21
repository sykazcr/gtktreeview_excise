//#progma once
#include <gtkmm.h>
#include <gdkmm/color.h>
#include <vector>


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

    const Gdk::Color& get_value() const;
    void set_value(const Gdk::Color &x);

    Widget_Color();
    ~Widget_Color();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool on_event(GdkEvent *event);
};

struct PaletteSetsItem
{
    Gdk::Color color;
    std::string name;

    PaletteSetsItem(){};

    PaletteSetsItem(const Gdk::Color color, const std::string& name)
        :color(color) { } ;

};

class PaletteSets : public std::vector<PaletteSetsItem>
{
    std::string name_;
public:
    PaletteSets();
    PaletteSets(const std::string& name_);

    static PaletteSets load_from_file(const std::string& filename);
};

class Pane_Bars : public Gtk::Grid
{
    PaletteSets palettesets_;

    Gtk::Grid table;

public:
    void set_palette(const PaletteSets& s);
    const PaletteSets& get_palette() const { return palettesets_; }

    int size() const;

    void refresh();

    Pane_Bars();
    ~Pane_Bars();
};




