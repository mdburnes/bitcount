#ifndef BARCHART_H
#define BARCHART_H

#define ARRAY_SIZE 360
#define END_OF_ARRAY 359

#include "gtkmm/drawingarea.h"

class BarChart : public Gtk::DrawingArea {
  private:
	long total_bytes_array[ARRAY_SIZE];	// Total bytes per second from net file
	long bytes_per_sec_array[ARRAY_SIZE];	// Calculated bytes per second.

  public:
	BarChart();
	void update_network_usage( void );
	bool is_alert_threshold_reached( void );

  protected:
	bool on_draw( const Cairo::RefPtr<Cairo::Context>& cr ) override;
};

#endif
