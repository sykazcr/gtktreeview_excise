// sykazcr
#include <cstdio>
#include <gtkmm.h>
#include <string>
#include <iostream>
#include <glibmm/convert.h>

#ifndef VERSION
#define VERSION	"unknown"
#define PACKAGE	"MyViewer"
#endif

#ifndef IMAGE_EXT
#	define IMAGE_EXT	"png"
#endif

class SplashProgress;

void info(std::string task)
{
    std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout<< "[TTT] info: " << task << std::endl;
}

void warning(std::string task)
{
    std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout<< "[TTT] warning: " << task << std::endl;
}

//-----
class MainWindow : public Gtk::Window
{

public:
	MainWindow();
	virtual ~MainWindow(){};
private:
    Gtk::Button m_button1, m_button2;
    Gtk::HBox m_hbox;
};

//-----
class App : public Gtk::Main {
 
public:

	App(const std::string& dir, int *argc, char ***argv);
	virtual ~App(){};

    MainWindow         *main_window;
    static void process_all_events(long unsigned int us=1);
};

//-
//---
//-----
//--*** c l a s s ProgressCallback *********************************************
//-----
//---
//-
class ProgressCallback
{
public:

	virtual ~ProgressCallback() { }
	virtual bool task(const std::string &/*task*/) { return true; }
	virtual bool error(const std::string &/*task*/) { return true; }
	virtual bool warning(const std::string &/*task*/) { return true; }
	virtual bool amount_complete(int /*current*/, int /*total*/) { return true; }

	virtual bool valid() const { return true; }
};

typedef ProgressCallback ProgressManager;

//-
//---
//-----
//--*** c l a s s SuperCallback ********************************************
//-----
//---
//-
class SuperCallback : public ProgressCallback
{
	ProgressCallback *cb;
	int start,end,tot;
	int w;
public:

	SuperCallback(): cb(), start(), end(), tot(), w() { }
	SuperCallback(ProgressCallback *cb,int start_, int end_, int total):
		cb(cb),start(start_),end(end_),tot(total),w(end-start)
	{
		//make sure we don't "inherit" if our subcallback is invalid
		if(!cb || !cb->valid())
			cb = NULL;
	}
	virtual bool task(const std::string &task) { if(cb)return cb->task(task); return true; }
	virtual bool error(const std::string &task) { if(cb)return cb->error(task); return true; }
	virtual bool warning(const std::string &task) { if(cb)return cb->warning(task); return true; }
	virtual bool amount_complete(int cur, int total) { if(cb)return cb->amount_complete(start+cur*w/total,tot); return true; }

	virtual bool valid() const { return cb != 0; }
};

class Splash : public Gtk::Window
{
	friend class SplashProgress;

	SplashProgress *cb;

	Gtk::Label *versionlabel;
	Gtk::Label *tasklabel;
	Gtk::ProgressBar *progressbar;

public:

	ProgressCallback *get_callback();

	void enable_startup_notification();

	Splash();
	~Splash();
};



class SplashProgress : public ProgressCallback
{
	Splash &splash;

public:

	SplashProgress(Splash &splash):splash(splash) { }
	virtual bool task(const std::string &task);

}; // end of SplashProgress

//
//--*** CODE IMPL *********************************************
//

bool SplashProgress::task(const std::string &task)
{
    if(splash.tasklabel)
    {
        splash.tasklabel->set_label(task);
        splash.tasklabel->show();
    }

    info(task);

    App::process_all_events(1);
    return true;
}

//-
//---
//-----
//--*** SPLASH  ***********************************************************
//-----
//---
//-
Splash::Splash():
	Gtk::Window(Gtk::WINDOW_TOPLEVEL)
{
	std::string imagepath("./image/");

	// Create the splash image
	Gtk::Image* splash_image = manage(new class Gtk::Image());
	splash_image->set(imagepath + "splash_screen." IMAGE_EXT);
	splash_image->set_alignment(0.5,0.5);
	splash_image->set_padding(0,0);

	// Get the image size
	int image_w = 350; int image_h = 0;
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = splash_image->get_pixbuf();
	if( pixbuf ){
		image_w = pixbuf->get_width();
		image_h = pixbuf->get_height();
	}

	// Create the progress bar
	progressbar = manage(new class Gtk::ProgressBar());
	progressbar->set_size_request(image_w,24);

	// Create the current task label
	tasklabel = manage(new class Gtk::Label());
	tasklabel->set_size_request(image_w,24);
	tasklabel->set_use_underline(false);

	// Create the current task label
	versionlabel = manage(new class Gtk::Label());
	versionlabel->set_label("" VERSION);
	versionlabel->set_size_request(image_w,24);
	versionlabel->set_use_underline(false);
	versionlabel->override_color(Gdk::RGBA("#FFFFFF"));
	versionlabel->show();

	// Create the Gtk::Fixed container and put all of the widgets into it
	Gtk::Fixed* fixed = manage(new class Gtk::Fixed());
	if( pixbuf ) fixed->put(*splash_image, 0, 0);
	fixed->put(*progressbar, 0, image_h+24);
	fixed->put(*tasklabel, 0, image_h);
	fixed->put(*versionlabel, 0, image_h-24);

	// Create shadow around the outside of the window
	Gtk::Frame* frame = manage(new class Gtk::Frame());
	frame->set_shadow_type(Gtk::SHADOW_OUT);
  	frame->add(*fixed);

	// Set up the parameters for this pop-up window
	set_title("Synfig Studio " VERSION);
	set_modal(false);
	property_window_position().set_value(Gtk::WIN_POS_CENTER);
	set_resizable(false);
	set_type_hint(Gdk::WINDOW_TYPE_HINT_SPLASHSCREEN);
	set_auto_startup_notification(false);
	try {
		set_icon_from_file(imagepath+"synfig_icon."+IMAGE_EXT);
	} catch(...) {
		warning("Unable to open "+imagepath+"synfig_icon."+IMAGE_EXT);
	}
	add(*frame);

	// show everything off
	if( pixbuf ) splash_image->show();
	fixed->show();
	frame->show();

	// Once the splash is shown, we want startup stuff to continue as normal
	signal_map().connect(sigc::mem_fun(*this, &Splash::enable_startup_notification));

	cb=new SplashProgress(*this);
}

Splash::~Splash()
{
	delete cb;
}

ProgressCallback* Splash::get_callback()
{
	return cb;
}

void
Splash::enable_startup_notification(){
	set_auto_startup_notification(true);
}

//-
//---
//-----
//--*** M A I N W I N ***********************************************************
//-----
//---
//-
MainWindow::MainWindow()
    : m_button1( "button1" ),
      m_button2( "button2" )
{
    m_hbox.pack_start( m_button1 );
    m_hbox.pack_start( m_button2 );

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
App::App(const std::string& dir, int *argc, char ***argv) 
{
    Splash splash_screen;
    splash_screen.show();
	splash_screen.set_default_size(300, 450);
    splash_screen.present();
    sleep(2);
//splash_screen.set_auto_startup_notification(true);
    sleep(2);
//splash_screen.set_auto_startup_notification(true);

//	main_window = new MainWindow();
//	main_window->set_default_size(300, 450);
//    main_window->present();
}

void App::process_all_events(long unsigned int us)
{
	Glib::usleep(us);
	while(events_pending()) {
		while(events_pending())
			iteration(false);
		Glib::usleep(us);
	}
}



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

