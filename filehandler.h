#ifndef NETFILEHANDLER_H
#define NETFILEHANDLER_H

#define MEGABYTE 1000000

#include <glibmm/ustring.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>


class FileHandler {
private:
	std::string network_adapter;
	int time_window; // The time in seconds to check add for bytes_limit
	long bytes_limit; // Bytes to download before triggering alarm
	long data_used_offset; // for zeroing the counter when appropriate
	bool zero_data_usage; // whether to zero data counter or not.
	bool keep_above; // A bool on whether to keep the main window on top.
	bool window_stick; // A bool on whether to keep on active workspace.
	double bytes_uploaded, bytes_downloaded;
	std::ifstream net_file_handle;
	std::string proc_net_dev_line;
	std::vector<Glib::ustring> adapter_names;
	bool load_adapter_names( void );
	bool process_network_line( void );

public:
	FileHandler( void );
	bool load_settings( void );
	bool save_settings( void );
	bool read_network_file( void );
	int get_number_interfaces( void );
	Glib::ustring get_interface_name( int number );
	bool get_keep_above( void );
	bool get_window_stick( void );
	void set_keep_above( bool value );
	void set_window_stick( bool value );
	double get_megabytes_uploaded( void );
	double get_megabytes_downloaded( void );
	double get_total_megabytes( void );
	long get_total_bytes( void );
	int get_time_window( void );
	void set_time_window( int );
	long get_bytes_limit( void );
	void set_bytes_limit( long );
	std::string get_interface( void );
	void set_interface( std::string );
	void set_zero_data_usage( bool );
	bool get_zero_data_usage( void );
	void set_data_used_offset( long );
	long get_data_used_offset( void );
};

#endif
