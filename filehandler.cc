#define FILENAME "/.config/bitcount.conf"
#define PROCFILE "/proc/net/dev"

#include "filehandler.h"

#include <sstream>

#include <ios>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>


FileHandler::FileHandler() {
	network_adapter = "    lo";
	time_window = 3;
	bytes_limit = MEGABYTE; // One megabyte
	data_used_offset = 0;
	zero_data_usage = false;
	keep_above = true;
	window_stick = true;
	load_adapter_names();
}

bool FileHandler::load_settings( void ) {
	size_t string_start, string_end, string_length;
	std::string line_in, key, value, file_name;
	std::ifstream settings_file;
	file_name = getenv( "HOME" );
	file_name.append( FILENAME );
	settings_file.open( file_name );
	if( !settings_file.is_open() ) {
		std::cout << "No settings file found" << std::endl;
		return false;
	}
	while( std::getline( settings_file, line_in ) ) {
		string_end = line_in.length();
		string_length = line_in.find_first_of( ":" );
		key = line_in.substr( 0, string_length );
		string_start = ++string_length;
		value = line_in.substr( string_start, string_end );
		if( key == "network_adapter" ) network_adapter = value;
		if( key == "time_window" ) time_window = std::atoi(value.c_str());
		if( key == "bytes_limit" ) bytes_limit = std::atol(value.c_str());
		if( key == "keep_above" ) keep_above = (bool)std::atoi(value.c_str());
		if( key == "window_stick" ) window_stick =
											(bool)std::atoi(value.c_str());
	}
	return true;
}

bool FileHandler::save_settings( void ) {
	std::string file_name;
	file_name = std::getenv( "HOME" );
	file_name.append( FILENAME );
	std::ofstream settings_file;
	settings_file.open( file_name );
	if( !settings_file.is_open() ) {
		std::cout << "Unable to open settings file."  << std::endl;
		return false;
	}
	settings_file << "network_adapter" << ":" << network_adapter << std::endl;
	settings_file << "time_window" << ":" << time_window << std::endl;
	settings_file << "bytes_limit" << ":" << bytes_limit << std::endl;
	settings_file << "keep_above" << ":" << keep_above << std::endl;
	settings_file << "window_stick" << ":" << window_stick << std::endl;
	settings_file.close();
	return true;
}

bool FileHandler::load_adapter_names( void ) {
	const char net_file_name[] = PROCFILE;
	std::string line_in;
	net_file_handle.open( net_file_name );
	if( !net_file_handle.is_open() ) {
		std::cout << "file failed to open" << std::endl;
		return false;
	}
	while( std::getline( net_file_handle, line_in ) ) {
		if( line_in.substr(6, 1) == ":" ) {
			adapter_names.push_back( line_in.substr(0, 6));
		}
	}
	return true;
}

bool FileHandler::read_network_file( void ) {
	const char net_file_name[] = PROCFILE;
	std::string line_in;
	net_file_handle.open( net_file_name );
	if( !net_file_handle.is_open() ) {
		std::cout << "file failed to open" << std::endl;
		return false;
	}
	while( std::getline( net_file_handle, line_in ) ) {
		if( line_in.substr(0, 6) == network_adapter ) {
			proc_net_dev_line = line_in.substr( 7 );
			process_network_line();
		}
	}
	net_file_handle.close();
	return true;
}

bool FileHandler::process_network_line( void ) {
	size_t string_start = 0;
	size_t string_end = 0;
	size_t string_length = 0;
	for( int x = 0; x < 9; x++ ) {
		string_start = proc_net_dev_line.find_first_of(
								"0123456789", string_end );
		string_end = proc_net_dev_line.find_first_not_of(
								"0123456789", string_start );
		string_length = string_end - string_start;
		if( x == 0 ) bytes_downloaded =
			std::atof(proc_net_dev_line.substr(
						  string_start, string_length ).c_str());
		if( x == 8 ) bytes_uploaded =
			std::atof(proc_net_dev_line.substr(
						  string_start, string_length ).c_str());
		string_start = string_end;
	}
	return true;
}

int FileHandler::get_number_interfaces( void ) {
	return adapter_names.size();
}

Glib::ustring FileHandler::get_interface_name( int number ) {
	if( number < 0 ) return "";
	if( number >= adapter_names.size() ) return "";
	return adapter_names[number];
}

bool FileHandler::get_keep_above( void ) { return keep_above; }

bool FileHandler::get_window_stick( void ) { return window_stick; }

void FileHandler::set_keep_above( bool value ) { keep_above = value; }

void FileHandler::set_window_stick( bool value ) { window_stick = value; }

double FileHandler::get_megabytes_uploaded(void) {
	return (bytes_uploaded / MEGABYTE);
}

double FileHandler::get_megabytes_downloaded(void) {
	return (bytes_downloaded / MEGABYTE);
}

double FileHandler::get_total_megabytes(void) {
	return ((bytes_uploaded + bytes_downloaded) / MEGABYTE);
}

long FileHandler::get_total_bytes( void ) {
	return (bytes_uploaded + bytes_downloaded);
}

int FileHandler::get_time_window(void) { return time_window; }

void FileHandler::set_time_window( int value ) { time_window = value; }

long FileHandler::get_bytes_limit( void ) { return bytes_limit; }

void FileHandler::set_bytes_limit( long limit ) { bytes_limit = limit; }

std::string FileHandler::get_interface( void ) { return network_adapter; }

void FileHandler::set_interface( std::string interface_name ) {
	network_adapter = interface_name;
}

void FileHandler::set_zero_data_usage( bool value ) {
	zero_data_usage = value;
}

bool FileHandler::get_zero_data_usage( void ) { return zero_data_usage; }

void FileHandler::set_data_used_offset( long value ) {
	data_used_offset = value;
}

long FileHandler::get_data_used_offset( void ) { return data_used_offset; }
