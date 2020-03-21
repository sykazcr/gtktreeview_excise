#include  "colorgrid.h"
#include <iostream>

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
    ;
}

Pane_Bars::~Pane_Bars()
{
    ;
}

int Pane_Bars:: size() const
{
    return 0;
}

void Pane_Bars:: refresh()
{
    ;
    
}

MainWin::MainWin()
    :m_Label1("CAT", false),
    m_Label2("DOGGGG", false)
{
    m_frm.set_label("Bars");
    add( m_frm );
    m_frm.add(m_hbox);
    pane.set_row_spacing(4);
    pane.set_column_spacing(4);

    m_hbox.set_border_width(8);
    m_hbox.pack_start( pane , Gtk::PACK_SHRINK);
    pane.set_size_request(600,400);
    pane.attach(m_Label1, 0, 0, 1, 1);
    pane.attach(m_Label2, 1, 1, 1, 1);
    set_border_width( 16 );
    show_all();
}



int main( int argc, char *argv[] )
{
    Gtk::Main kit( argc, argv );
    MainWin mainwin;
    Gtk::Main::run( mainwin );

    return 0;
}

