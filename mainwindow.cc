#include "mainwindow.h"
#include "setwindow.h"
#include "filehandler.h"

#include "glibmm/main.h"
#include "glibmm/refptr.h"
#include "glibmm/ustring.h"
#include "gtkmm/box.h"
#include "gtkmm/enums.h"
#include "gtkmm/textbuffer.h"
#include "sigc++/adaptors/bind.h"
#include "sigc++/connection.h"
#include "sigc++/functors/mem_fun.h"
#include "sigc++/functors/slot.h"

#include <iostream>
#include <sstream>

extern FileHandler file_handler;

MainWindow::MainWindow( void ) {
	data_used_offset = 0;
	box_1.set_visible( true );
	box_1.set_can_focus( false );
	box_1.set_orientation( Gtk::ORIENTATION_VERTICAL );
	mb_label.set_visible( true );
	mb_label.set_can_focus( false );
	mb_label.set_text( "0.000 MB" );
	box_1.pack_start( mb_label, Gtk::PACK_SHRINK );
	bar_chart.set_visible( true );
	bar_chart.set_can_focus( false );
	bar_chart.set_size_request( 250, 50 );
	box_1.pack_start( bar_chart );
	b_box_1.set_visible( true );
	b_box_1.set_can_focus( false );
	b_box_1.set_halign( Gtk::ALIGN_CENTER );
	activate_check_button.set_label( "Alert" );
	activate_check_button.set_visible( true );
	activate_check_button.set_can_focus( true );
	activate_check_button.set_receives_default( false );
	activate_check_button.set_active( true );
	b_box_1.pack_start( activate_check_button, Gtk::PACK_EXPAND_WIDGET );
	set_button.set_label( "Set" );
	set_button.set_visible( true );
	set_button.set_can_focus( true );
	b_box_1.pack_start( set_button, Gtk::PACK_EXPAND_WIDGET );
	box_1.pack_start( b_box_1, Gtk::PACK_SHRINK );
	alert_user = true;
	timer_active = 0;

	add(box_1);
	set_title("BitCount");

	// starting the timer callback when the program starts
	timer_slot = sigc::bind(
		sigc::mem_fun(*this, &MainWindow::on_timeout), timer_active );
	timer_connection = Glib::signal_timeout().connect( timer_slot, 1000  );

	// connecting signals to slots here
	activate_check_button.signal_toggled().connect(
		sigc::mem_fun(this, &MainWindow::on_activate_check_button_toggled));
	set_button.signal_clicked().connect(
		sigc::mem_fun(this, &MainWindow::on_set_button_clicked));
	my_slot = sigc::mem_fun(this, &MainWindow::update_settings);
	settings_window.connect_slot( my_slot );
}

void MainWindow::update_settings( void ) {
	// std::cout << "Updating settings." << std::endl;
	data_used_offset = 0;
	if( file_handler.get_zero_data_usage() ) {
		data_used_offset = file_handler.get_data_used_offset();
	}
	this->set_keep_above( file_handler.get_keep_above() );
	file_handler.get_window_stick() ?
		this->stick() :
		this->unstick();
}

bool MainWindow::on_timeout( int number ) {
	if( !file_handler.read_network_file() ) return false;
	double data_used = file_handler.get_total_bytes() - data_used_offset;
	data_used /= MEGABYTE;
	snprintf(label_text, LABEL_TEXT_SIZE, "%.3f MB", data_used );
	mb_label.set_text(label_text);
	bar_chart.update_network_usage();
	if( bar_chart.is_alert_threshold_reached() && alert_user ) this->present();
	// force a redraw
	auto win = get_window();
	if (win)
		{
			Gdk::Rectangle r(0, 0, get_allocation().get_width(),
							 get_allocation().get_height());
			win->invalidate_rect(r, false);
		}
    return true;
}

void MainWindow::on_activate_check_button_toggled( void ) {
	alert_user = activate_check_button.get_active();
}

void MainWindow::on_set_button_clicked(void) {
	settings_window.show();
}

