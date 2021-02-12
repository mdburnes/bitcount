#include <gtkmm/application.h>
#include "mainwindow.h"
#include "filehandler.h"

FileHandler file_handler;

int main  (int argc, char *argv[] ) {
	bool has_settings;
	auto app = Gtk::Application::create( argc, argv );
	has_settings = file_handler.load_settings();
	MainWindow main_window;
	if( file_handler.get_keep_above() ) main_window.set_keep_above();
	if( file_handler.get_window_stick() ) main_window.stick();
	if( !app->run( main_window ) ) {
		file_handler.save_settings();
		return 0;
	}
	return 1;
}
