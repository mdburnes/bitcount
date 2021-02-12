#ifndef GTK_TIMER_MAINWINDOW_H
#define GTK_TIMER_MAINWINDOW_H

#define LABEL_TEXT_SIZE 36

#include "setwindow.h"
#include "barchart.h"

#include "sigc++/functors/slot.h"
#include "glibmm/refptr.h"
#include "glibmm/ustring.h"
#include "gtkmm/label.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/buttonbox.h"
#include "gtkmm/checkbutton.h"
#include "gtkmm/window.h"

#include <cstdio>

class MainWindow : public Gtk::Window {
	private:
	char label_text[LABEL_TEXT_SIZE];
	long data_used_offset;
	SettingsWindow settings_window;
	BarChart bar_chart;
	Gtk::Box box_1;
	Gtk::ButtonBox b_box_1;
	Gtk::Button set_button;
	Gtk::Label mb_label;
	Gtk::CheckButton activate_check_button;
	Glib::ustring text_string;
	sigc::slot<bool> timer_slot;
	sigc::connection timer_connection;

	public:
	MainWindow( void );

	protected:
	bool alert_user;
	int timer_active;
	bool on_timeout( int number );
	void on_activate_check_button_toggled( void );
	void on_set_button_clicked( void );
	Glib::SignalProxy<void>::SlotType my_slot;
	void update_settings( void );
};

#endif
