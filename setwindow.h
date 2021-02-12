#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <glibmm/ustring.h>
#include <glibmm/refptr.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include "gtkmm/buttonbox.h"
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/switch.h>

class SettingsWindow : public Gtk::Window {
	private:
	long data_used_offset;
	Glib::ustring bytes_ustring;
	Gtk::Box window_box, left_box, right_box;
	Gtk::Box check_button_box, alert_box, bytes_entry_box;
	Gtk::Box seconds_spin_button_box, bytes_reset_box;
	Gtk::ButtonBox ok_button_box;
	Gtk::Frame combo_box_frame, check_button_frame, alert_frame;
	Gtk::Frame bytes_reset_frame;
	Gtk::ComboBoxText combo_box_text;
	Gtk::CheckButton keep_above_checkbutton, window_stick_checkbutton;
	Gtk::CheckButton bytes_reset_checkbutton;
	Gtk::Entry bytes_entry;
	Gtk::Label bytes_label, seconds_per_label, seconds_label;
	Glib::RefPtr<Gtk::Adjustment> seconds_ref_ptr;
	Gtk::SpinButton seconds_spin_button;
	Gtk::Button bytes_reset_button, settings_ok_button;

	public:
	SettingsWindow( void );
	void show( void );
	void connect_slot( Glib::SignalProxy<void>::SlotType );

	protected:
	void get_all_settings( void );
	void set_all_settings( void );
	void on_settings_ok_button_clicked( void );
	void on_bytes_reset_checkbutton_toggled( void );
	void on_bytes_reset_button_clicked( void );
};

#endif