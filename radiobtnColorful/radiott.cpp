#include  "radiott.h"
#include <iostream>


void render_color_to_window(
        const Cairo::RefPtr<Cairo::Context> &cr, 
        const Gdk::Rectangle &ca, 
        const Gdk::Color &color)
{
	const int height(ca.get_height());
	const int width(ca.get_width());

	{
		Gdk::Color c = color; 
        cr->set_source_rgb(c.get_red(), c.get_green(), c.get_blue());
        cr->rectangle(ca.get_x(), ca.get_y(), width-1, height-1);
        cr->fill();
	}
}

Widget_Color::Widget_Color()
{
	//color=Gdk::Color("#808080");
	color=Gdk::Color("red");
	set_size_request(216,12);
}

Widget_Color::~Widget_Color()
{
}

void
Widget_Color::set_value(const Gdk::Color &x)
{
//	assert(x.is_valid());
	color=x;
	queue_draw();
}

const Gdk::Color &
Widget_Color::get_value() const
{
//	assert(color.is_valid());
	return color;
}


bool
Widget_Color::on_event(GdkEvent *event)
{
	switch(event->type)
	{
	case GDK_BUTTON_PRESS:
		if(event->button.button==1)
		{
//			signal_activate_();
			return true;
		}
		break;

	default:
		break;
	}
	return false;
}

bool
Widget_Color::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
	render_color_to_window(cr, Gdk::Rectangle(0,0,get_width(),get_height()), color);
	return true;
}

//-----------------------------------------------------------
PaletteSets::PaletteSets()
{
    ;
}

PaletteSets::PaletteSets(const std::string& s)
{
    std::cout<< s<< std::endl;
}


PaletteSets PaletteSets::load_from_file(const std::string& f)
{
    PaletteSets P;
    return P;
}

//-------------------------------------------------------------
Pane_Bars::Pane_Bars()
{
//    add(table);
    attach(table, 3, 0, 3, 1);
    attach(tableR, 7, 0, 3, 1);
    set_default_palette();
    show_all_children();
}

Pane_Bars::~Pane_Bars()
{
    ;
}

void Pane_Bars::set_default_palette()
{
    refresh();
}

Gdk::Color Pane_Bars::get_color(int i) const
{
    switch(i%3) {
        case 0:
            return Gdk::Color("red");
            break;
        case 1:
            return Gdk::Color("blue");
            break;
        case 2:
            return Gdk::Color("green");
            break;
        default:
            return Gdk::Color("yellow");
    }
    //return palettesets_[i].color;
}

int Pane_Bars:: size() const
{
    return 24;
}

void Pane_Bars:: refresh()
{
    const int width{1};
    
    table.foreach(sigc::mem_fun(table, &Gtk::Grid::remove));

    for(int i=0;i<size();i++) {
        Widget_Color* widget_color(manage(new Widget_Color()));
        widget_color->set_value(get_color(i));
		int c(i%width),r(i/width);
		table.attach(*widget_color, c, r, 1, 1);
    }
    // Radio buttons
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(
#if 0
        "button { border: none; border-radius: 0%; }"
#endif
        "button {background-image: image(cyan); border:none;}\
        button:hover {background-image: image(#eb8c34);}\
        button:active {background-image: image(yellow);}"
        );
    for(int i=0;i<size();i++) {
        Gtk::RadioButton* radi(Gtk::manage(new Gtk::RadioButton()));
        radi->set_mode(false); // not show maru.
        radi->set_size_request(200,10);
		int c(i%width),r(i/width);
        radi->get_style_context()->add_provider(
                    css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
		tableR.attach(*radi, c, r, 1, 1);
    }
    table.show_all();
    tableR.show_all();
    queue_draw();
    
}

MainWin::MainWin()
    :m_Label1("CAT1", false),
    m_Label2("DOGGGG2", false),
    m_Label3("DOGGGG3", false),
    m_Label4("DOGGGG4", false)
{
    m_frm.set_label("Bars-grid--600x400");
    add( m_frm );
    m_frm.add(m_hbox);
    pane.set_row_spacing(4);
    pane.set_column_spacing(4);

    m_hbox.set_border_width(8);
    m_hbox.pack_start( pane , Gtk::PACK_SHRINK);
    pane.set_size_request(600,400);
    pane.attach(m_Label1, 0, 1, 1, 1);
    pane.attach(m_Label2, 1, 0, 1, 1);
//    pane.attach(m_Label3, 2, 0, 1, 1);
    pane.attach(m_Label4, 6, 0, 1, 1);

    pane.attach(m_swti, 1, 1, 3, 2);
    
//        "button {background-image: image(cyan); border:2px solid #000000;}
//
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(
        "button { background-image: url(\"./image/blue.png\"); border: none; border-radius: 1%; }\
        button:checked {background-image: url(\"./image/green.png\");}\
        button:active {background-image: image(yellow);}"
#if 0
        "button {background-image: image(cyan); border:1px;}\
        button:hover {background-image: image(#eb8c34);}\
        button:active {background-image: image(yellow);}"
#endif
#if 0
        "\
        button {\
              display: inline-block;\
              text-decoration: none;\
              color: #668ad8;\
              width: 120px;\
              height: 120px;\
              line-height: 120px;\
              border-radius: 50%;\
              border: double 4px #668ad8;\
              text-align: center;\
              overflow: hidden;\
              transition: .6s;\
          }\
          \
          button:hover {\
              -webkit-transform: rotateY(360deg);\
              transform: rotateY(360deg);\
          }\
          "
#endif
        );
    m_togi.get_style_context()->add_provider(
                css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    m_togi.set_size_request(100, 60);
    m_togi.set_name("togi");
//    m_togi.override_background_color(Gdk::RGBA("#eb8c34"), Gtk::StateFlags::STATE_FLAG_NORMAL);
    pane.attach(m_togi, 3, 3, 3, 3); set_border_width( 16 );
    show_all();
}



int main( int argc, char *argv[] )
{
    Gtk::Main kit( argc, argv );
    MainWin mainwin;
    Gtk::Main::run( mainwin );

    return 0;
}

