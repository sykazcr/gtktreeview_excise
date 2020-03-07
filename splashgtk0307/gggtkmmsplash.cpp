// sykazcr
#include <cstdio>
#include <gtkmm.h>
#include <string>
#include <iostream>
#include <glibmm/convert.h>

class MainWindow : public Gtk::Window
{

public:
	MainWindow();
	virtual ~MainWindow(){};
private:
    Gtk::Button m_button1, m_button2;
    Gtk::HBox m_hbox;
    //Gtk::Tooltip m_tooltip;
};

MainWindow::MainWindow()
    : m_button1( "button1" ),
      m_button2( "button2" )
{
    m_hbox.pack_start( m_button1 );
    m_hbox.pack_start( m_button2 );

    //m_tooltip.set_text( m_button1, Glib::ustring("button1") );
    //m_tooltip.set_text( m_button2, Glib::ustring("button2") );

    add( m_hbox );
    show_all_children();
}


//-
//---
//-----
//--*** A P P *****************************************************************
//-----
//---
//-
class App : public Gtk::Main {
 
public:

	App(const std::string& dir, int *argc, char ***argv);
	virtual ~App(){};

    MainWindow         *main_window;
};

App::App(const std::string& dir, int *argc, char ***argv) 
{
	main_window = new MainWindow();
	main_window->set_default_size(300, 450);
    main_window->present();
}


//MainWindow         *App::main_window    = NULL;

//-
//---
//-----
//--*** M A I N *****************************************************************
//-----
//---
//-
int main(int argc, char **argv)
{

	try
	{
		App app(std::string("/home/work/splash/"), &argc, &argv);

		app.run();
	}
	catch(int ret)
	{
		std::cerr<<"Application shutdown with errors ("<<ret<<')'<<std::endl;
		return ret;
	}
	catch(std::string& str)
	{
		std::cerr<<"Uncaught Exception:string: "<<str.c_str()<<std::endl;
		throw;
	}
	catch(std::exception& x)
	{
		std::cerr<<"Standard Exception: "<<x.what()<<std::endl;
		throw;
	}
	catch(Glib::Exception& x)
	{
		std::cerr<<"GLib Exception: "<<x.what()<<std::endl;
		throw;
	}
	catch(...)
	{
		std::cerr<<"Uncaught Exception"<<std::endl;
		throw;
	}

	std::cerr<<"Application appears to have terminated successfully"<<std::endl;

	return 0;
}

