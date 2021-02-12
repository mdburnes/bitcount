objects = main.o mainwindow.o barchart.o setwindow.o filehandler.o

bitcount : $(objects)
	g++ $(objects) -o bitcount `pkg-config gtkmm-3.0 --libs`

main.o : main.cc mainwindow.h filehandler.h setwindow.h
	g++ main.cc -c -o main.o `pkg-config gtkmm-3.0 --cflags`

mainwindow.o : mainwindow.cc mainwindow.h filehandler.h setwindow.h
	g++ mainwindow.cc -c -o mainwindow.o `pkg-config gtkmm-3.0 --cflags`

barchart.o : barchart.cc barchart.h filehandler.h
	g++ barchart.cc -c -o barchart.o `pkg-config gtkmm-3.0 --cflags`

setwindow.o : setwindow.cc setwindow.h filehandler.h
	g++ setwindow.cc -c -o setwindow.o `pkg-config gtkmm-3.0 --cflags`

filehandler.o : filehandler.cc filehandler.h
	g++ filehandler.cc -c -o filehandler.o `pkg-config gtkmm-3.0 --cflags`

.PHONY : clean

clean :
	-rm bitcount $(objects)
