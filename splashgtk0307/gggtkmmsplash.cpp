// sykazcr
#include <gtkmm.h>
#include <string>
#include <iostream>
#include <glibmm/convert.h>


int main(int argc, char **argv)
{

	try
	{
		App app(etl::dirname(binary_path), &argc, &argv);

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

