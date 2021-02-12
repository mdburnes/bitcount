#include "barchart.h"
#include "filehandler.h"

#include "gtkmm/widget.h"
#include <cairomm/context.h>

extern FileHandler file_handler;

BarChart::BarChart() {
	for( int x = 0; x < ARRAY_SIZE; x++ ) {
		total_bytes_array[x] = 0;
		bytes_per_sec_array[x] = 0;
	}
}

bool BarChart::on_draw( const Cairo::RefPtr<Cairo::Context>& cr ) {
	Gtk::Allocation allocation = get_allocation();
	int width = allocation.get_width() - 10; // for padding
	int height = allocation.get_height();
	int width_start, height_start, width_padding;
	int line_x, line_y_top, num_bars;
	long bytes_limit;
	double pct;
	width_start = 5;
	height_start = 0;
	width_padding = 5;
	bytes_limit = file_handler.get_bytes_limit();
	cr->set_source_rgb( 0.1, 0.1, 0.1  );
	cr->move_to( width_start, height_start );
	cr->line_to( (width + width_start), height_start );
	cr->line_to( (width + width_start), height );
	cr->line_to( width_start, height );
	cr->line_to( width_start, height_start );
	cr->fill();
	num_bars = width / 4;
	cr->set_line_width( 3.0 );
	cr->set_source_rgb(1, 1, 1);
	if( num_bars > ARRAY_SIZE ) num_bars = ARRAY_SIZE;
	for( int x = 0; x < num_bars; x++ ) {
		line_x = (width - x*4 - 1 + width_start );
		pct = bytes_per_sec_array[(END_OF_ARRAY - x)];
		pct /= bytes_limit;
		pct = (1 - pct) * height;
		cr->move_to( line_x, pct );
		cr->line_to( line_x, height );
	}
	cr->stroke();
	return true;
}

void BarChart::update_network_usage( void ) {
	long total_bytes;
	for( int x = 1; x < ARRAY_SIZE; x++ ) {
		total_bytes_array[(x-1)] = total_bytes_array[x];
		bytes_per_sec_array[(x-1)] = bytes_per_sec_array[x];
	}
	total_bytes = file_handler.get_total_bytes();
	bytes_per_sec_array[END_OF_ARRAY] =
		total_bytes - total_bytes_array[END_OF_ARRAY];
	total_bytes_array[END_OF_ARRAY] = total_bytes;
}

bool BarChart::is_alert_threshold_reached( void ) {
	long used_bytes;
	int time_window;
	time_window = file_handler.get_time_window();
	used_bytes = total_bytes_array[END_OF_ARRAY]
		- total_bytes_array[(END_OF_ARRAY - time_window)];
	if( used_bytes >= file_handler.get_bytes_limit() ) return true;
	return false;
}