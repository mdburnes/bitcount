#define FRAME_BORDER_WIDTH 10
#define BYTES_LOWER_LIMIT 1000		// 1 kilobyte
#define BYTES_UPPER_LIMIT 100000000	// 100 megabytes
#define BYTES_ENTRY_DEFAULT 1000000	// 1 megabyte

#include "setwindow.h"
#include "filehandler.h"

#include "gtkmm/widget.h"
#include <gtkmm/enums.h>

#include <sstream>

extern FileHandler file_handler;

SettingsWindow::SettingsWindow() {
	data_used_offset = 0;
	bytes_ustring = "";
	// Create the box for the main window. It will have two columns.
	window_box.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
	window_box.set_can_focus( false );
	window_box.set_visible( true );
	// Create the box for the left column.
	left_box.set_orientation( Gtk::ORIENTATION_VERTICAL);
	left_box.set_can_focus( false );
	left_box.set_visible( true );
	// Create the box for the right column.
	right_box.set_orientation( Gtk::ORIENTATION_VERTICAL );
	right_box.set_can_focus( false );
	right_box.set_visible( true );
	// Create a frame for the combo box
	combo_box_frame.set_label("Interface");
	combo_box_frame.set_label_align( Gtk::ALIGN_CENTER );
	combo_box_frame.set_can_focus( false );
	combo_box_frame.set_border_width( FRAME_BORDER_WIDTH );
	combo_box_frame.set_visible( true );
	// Create a ComboBoxText for selecting the interface to track
	for( int x = 0; x < file_handler.get_number_interfaces(); x++ ) {
		combo_box_text.append( file_handler.get_interface_name( x ));
	}
	// combo_box_text.set_active_text( file_handler.get_interface() );
	combo_box_text.set_can_focus( true );
	combo_box_text.set_visible( true );
	combo_box_text.set_border_width( FRAME_BORDER_WIDTH );
	// Add the combo box to the combo box frame
	combo_box_frame.add( combo_box_text );
	// Add the frame to the the main window box
	right_box.pack_start(combo_box_frame);
	// Create the check button frame
	check_button_frame.set_can_focus( false );
	check_button_frame.set_visible( true );
	check_button_frame.set_label( "Main Window" );
	check_button_frame.set_label_align( Gtk::ALIGN_CENTER );
	check_button_frame.set_border_width( FRAME_BORDER_WIDTH );
	// Create the check button box
	check_button_box.set_orientation( Gtk::ORIENTATION_VERTICAL );
	check_button_box.set_can_focus( false );
	check_button_box.set_visible( true );
	check_button_box.set_border_width( FRAME_BORDER_WIDTH );
	keep_above_checkbutton.set_label( "Always On Top" );
	// Create the first check button
	keep_above_checkbutton.set_can_focus( true );
	keep_above_checkbutton.set_visible( true );
	// Add check button to check button box
	check_button_box.pack_start( keep_above_checkbutton );
	// Create the second check button
	window_stick_checkbutton.set_label( "Always On Active Desktop" );
	window_stick_checkbutton.set_can_focus( true );
	window_stick_checkbutton.set_visible( true );
	// Add the second check button to the check button box
	check_button_box.pack_start( window_stick_checkbutton );
	// Add the check button box to the check button frame
	check_button_frame.add( check_button_box );
	// Add the ckeck button frame to the main window box
	right_box.pack_start( check_button_frame );
	// Create the alert frame
	alert_frame.set_label( "Alert At" );
	alert_frame.set_label_align( Gtk::ALIGN_CENTER );
	alert_frame.set_can_focus( false );
	alert_frame.set_visible( true );
	alert_frame.set_border_width( FRAME_BORDER_WIDTH );
	// Create the alert box
	alert_box.set_orientation( Gtk::ORIENTATION_VERTICAL );
	alert_box.set_can_focus( false );
	alert_box.set_visible( true );
	// Create the bytes entry box to go in the alert box
	bytes_entry_box.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
	bytes_entry_box.set_can_focus( false );
	bytes_entry_box.set_border_width( FRAME_BORDER_WIDTH );
	bytes_entry_box.set_visible( true );
	// Create the bytes entry
	bytes_entry.set_can_focus( true );
	bytes_entry.set_visible( true );
	// Add bytes_entry to the bytes entry box
	bytes_entry_box.pack_start( bytes_entry );
	// Create bytes label
	bytes_label.set_text( "Bytes" );
	bytes_label.set_can_focus( false );
	bytes_label.set_visible( true );
	// Add the bytes label to the bytes entry box
	bytes_entry_box.pack_start( bytes_label );
	// Add the bytes entry box to the alert box
	alert_box.pack_start( bytes_entry_box );
	// Create the seconds spin button box
	seconds_spin_button_box.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
	seconds_spin_button_box.set_can_focus( false );
	seconds_spin_button_box.set_border_width( FRAME_BORDER_WIDTH );
	seconds_spin_button_box.set_visible( true );
	// Create seconds per label
	seconds_per_label.set_text( "Per" );
	seconds_per_label.set_can_focus( false );
	seconds_per_label.set_visible( true );
	// Create seconds label
	seconds_label.set_text( "Second(s)" );
	seconds_label.set_can_focus( false );
	seconds_label.set_visible( true );
	// Create a seconds adjustment reference pointer and the spin button
	seconds_ref_ptr = Gtk::Adjustment::create( 1.0, 1.0, 10.0 );
	seconds_spin_button.set_adjustment( seconds_ref_ptr );
	seconds_spin_button.set_can_focus( true );
	seconds_spin_button.set_visible( true );
	// Add to spin button stuff to the spin button box
	seconds_spin_button_box.pack_start( seconds_per_label );
	seconds_spin_button_box.pack_start( seconds_spin_button );
	seconds_spin_button_box.pack_start( seconds_label );
	// Add the seconds spin button box to the alert box
	alert_box.pack_start( seconds_spin_button_box );
	// Add the alert box to the alert frame
	alert_frame.add( alert_box );
	// Add the alert frame to the main window box
	left_box.pack_start( alert_frame );
	// Create bytes reset box
	bytes_reset_box.set_orientation( Gtk::ORIENTATION_VERTICAL );
	bytes_reset_box.set_can_focus( false );
	bytes_reset_box.set_border_width( FRAME_BORDER_WIDTH );
	bytes_reset_box.set_visible( true );
	// Create bytes reset frame
	bytes_reset_frame.set_label( "Reset Counter" );
	bytes_reset_frame.set_label_align( Gtk::ALIGN_CENTER );
	bytes_reset_frame.set_border_width( FRAME_BORDER_WIDTH );
	bytes_reset_frame.set_can_focus( false );
	bytes_reset_frame.set_visible( true );
	// Create bytes reset switch
	bytes_reset_checkbutton.set_can_focus( true );
	bytes_reset_checkbutton.set_visible( true );
	bytes_reset_checkbutton.set_label( "Zero Data Usage?" );
	bytes_reset_checkbutton.set_active( false );
	// Put bytes reset switch inside bytes reset box
	bytes_reset_box.pack_start( bytes_reset_checkbutton );
	// Create bytes reset button
	bytes_reset_button.set_label( "Reset" );
	bytes_reset_button.set_can_focus( true );
	bytes_reset_button.set_visible( true );
	bytes_reset_button.set_sensitive( false );
	// Put the bytes reset button inside the bytes reset box
	bytes_reset_box.pack_start( bytes_reset_button );
	// Put bytes reset box inside bytes reset frame
	bytes_reset_frame.add( bytes_reset_box );
	// PUt bytes reset frame inside main window box
	left_box.pack_start( bytes_reset_frame );
	// Create the ok button box
	ok_button_box.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
	ok_button_box.set_can_focus( false );
	ok_button_box.set_visible( true );
	// Create the ok button
	settings_ok_button.set_label( "Ok" );
	settings_ok_button.set_can_focus( true );
	settings_ok_button.set_visible( true );
	// Add ok button to ok button box
	ok_button_box.pack_start( settings_ok_button );
	// Add ok button box to right box
	right_box.pack_start( ok_button_box );
	// Add left and right boxes to window box
	window_box.pack_start( left_box );
	window_box.pack_start( right_box );
	// Add window box to the actual window
	add( window_box );
	set_title( "Settings" );
	set_modal( true );

	// connect signals here
	settings_ok_button.signal_clicked().connect(
		sigc::mem_fun(this, &SettingsWindow::on_settings_ok_button_clicked));
	bytes_reset_checkbutton.signal_clicked().connect(
		sigc::mem_fun(this,
			&SettingsWindow::on_bytes_reset_checkbutton_toggled));
	bytes_reset_button.signal_clicked().connect(
		sigc::mem_fun(this, &SettingsWindow::on_bytes_reset_button_clicked));
}

/* We are going to override the show function and use it to load
 * the settings. That way we will be sure that we are always working
 * with the actual settings every time the window opens
 */
void SettingsWindow::show( void ) {
	get_all_settings();
	Gtk::Window::show();
}

void SettingsWindow::connect_slot(Glib::SignalProxy<void>::SlotType slot ) {
	settings_ok_button.signal_clicked().connect( slot );
}

void SettingsWindow::get_all_settings( void ) {
	combo_box_text.set_active_text( file_handler.get_interface() );
	keep_above_checkbutton.set_active( file_handler.get_keep_above() );
	window_stick_checkbutton.set_active( file_handler.get_window_stick() );
	seconds_spin_button.set_value( (double)file_handler.get_time_window() );
	bytes_reset_checkbutton.set_active( file_handler.get_zero_data_usage() );
	std::stringstream ss;
	ss << file_handler.get_bytes_limit();
	bytes_ustring = ss.str();
	bytes_entry.set_text( bytes_ustring );
	// The data_used_offset isn't necessary to load.
}

void SettingsWindow::set_all_settings( void ) {
	std::stringstream strstrm;
	long bytes_entry_test;
	file_handler.set_keep_above( keep_above_checkbutton.get_active() );
	file_handler.set_window_stick( window_stick_checkbutton.get_active() );
	file_handler.set_interface( combo_box_text.get_active_text() );
	strstrm << bytes_entry.get_text();
	strstrm >> bytes_entry_test;
	if( bytes_entry_test < BYTES_LOWER_LIMIT || 
					bytes_entry_test > BYTES_UPPER_LIMIT) {
		bytes_entry_test = BYTES_ENTRY_DEFAULT;
		bytes_entry.set_text( "1000000" );
	}
	file_handler.set_bytes_limit( bytes_entry_test );
	file_handler.set_time_window( (int)seconds_spin_button.get_value() );
	file_handler.set_zero_data_usage( bytes_reset_checkbutton.get_active() );
	file_handler.set_data_used_offset( data_used_offset );	
}

void SettingsWindow::on_settings_ok_button_clicked( void ) {
	set_all_settings();
	this->hide();
}

void SettingsWindow::on_bytes_reset_checkbutton_toggled( void ) {
	bytes_reset_checkbutton.get_active() ?
		bytes_reset_button.set_sensitive( true ) :
		bytes_reset_button.set_sensitive( false );
}

void SettingsWindow::on_bytes_reset_button_clicked( void ) {
	data_used_offset = file_handler.get_total_bytes();
}