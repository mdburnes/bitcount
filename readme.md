# Introduction

I do a lot of work away from a dedicated Internet connection. I have no choice but to rely on mobile data over a metered connection to access the Internet. But having to keep track of how much data my computer is using moment to moment isn't something that was easily available on Linux. I created bitcount in an attempt to solve this problem.

# Other solutions

There are several Linux programs that can tell you your data usage. Of those programs, they generally fall into one of three categories: interface addons, command line programs, or network scale monitoring.

Most desktops (well, all that I am aware of) have an addon that can be installed to show you your data usage in real time. The positive side of interface addons is that they are always on the screen so that you can see your data usage in real time. In fact, these are reliable and do a wonderful job. I use the Gnome desktop and have one installed, but you have to keep a constant eye on them or you will inadvertently download a huge amount of data before you realize you are doing so. This is especially true when you use automatic updates.

Then there are the command line programs. It is easy to find command line programs that provide exactly the information you might need. Their main drawback is that they are either not on the screen or they are taking up too much screen real estate. And if they are off the screen, there is no way to know how much data is being used at that moment.

Finally there is the class of programs that is intended for entire networks. I find them to just be too big for the simple job of monitoring data usage on a laptop computer over a metered connection.

When I developed under Microsoft Windows, I used an application called [Bit Meter 2](https://codebox.net/pages/bitmeter2). In fact, BitCount is loosely based on Bit Meter 2.

This is what led me to create a solution that would work on Linux.

# What I needed a data monitor to accomplish on a metered network

The most important thing that I wanted was something that would actively alert me when I was using beyond a specific amount of data over a specific amount of time. For example, I wanted it to alert me if I was using more than 1 megabyte over a 3 second period. This setting also needed to be adjustable. Perhaps it would be better to know if I was using more that 500 kilobytes over a 2 second period or some other combination.

Since there are also times when I know that I am going to be using a large burst of data, I needed a way to disable and reinable it so that it would only alert me when I wanted to know instead of constantly bothering me.

I wanted the program to pop up its main window if it was off screen.

I wanted the program to show me my data usage using a bar graph so that I could tell exactly how my data was being used.

I wanted this program to display the total data usage since my laptop was booted. If I had been using it for a long time, or I switched from a non-metered network to a metered network, I needed to be able to reset the data usage counter.

And of course I needed to be able to choose the interface for the program to count.

# What BitCount does

BitCount doesn't look at packages, it only counts bits through a specific interface. In fact, it doesn't even count the bits itself; instead, it uses the data provided by the Linux kernel to the /proc/net/dev file. It reads this file once per second, parses the data, and stores the last six minutes of it for calculations.

Once it has the data, it displays an entry of your total usage and a bar graph showing your usage per second.

If you use more data than its alert setting, it will display its main window if it is off screen.
