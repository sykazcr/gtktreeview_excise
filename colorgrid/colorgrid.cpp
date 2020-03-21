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
{
    Pane_Bars pane;
    m_hbox.pack_start( pane);
    m_frm.set_label("Bars");
    m_frm.add(m_hbox);
}



int main( int argc, char *argv[] )
{
    Gtk::Main kit( argc, argv );
    MainWin mainwin;
    Gtk::Main::run( mainwin );

    return 0;
}

