PAM - Physical Activity Monitor
Jonathan DePrizio
jondeprizio@gmail.com
January, 2014

---

The goal of this project was to create a physical implementation of a typical activity monitor; that is, display CPU and memory usage using an Arduino.  I also included net send/recv indicators as well as HDD read/write indicators.  LEDs exist for temperature warnings, but these are not currently implemented [1].

The wiring is pretty simple; if someone wants a sketch, let me know and I'll draw it up.  But basically, the 7-segment displays used are Microtivity 7-segment displays, model IS111.  They're common cathode displays.  The individual LEDs are also wired as common cathode.

The pins are as follows:
A0 = tens digit for CPU
A1 = ones digit for CPU
A2 = tens digit for MEM
A3 = ones digit for MEM
A4 = indicator LEDs for HDD, NET, etc..

These are set to OUTPUT/LOW when the display being controlled is the active display; otherwise they're set to INPUT (the LEDs are multiplexed with a common cathode).  Pins 2 through 8 are the anodes; the decimal indicator in the 7-segment display is not used.  The following are the arduino:7-segment pairings, using the labels on the Microtivity package:

Pin 2 = A
Pin 3 = F
Pin 4 = B
Pin 5 = G
Pin 6 = E
Pin 7 = C
Pin 8 = D


On the server side, I'm simply using psutil and pySerial to build and send a string of 8 bytes, of the format:
[CPU Tens][CPU Ones][Mem Tens][Mem Ones][Net Recv][Net Send][Disk Read][Disk Write]

The CPU and Memory indicators can be anything from 0-9.  Net and disk can be either 0 (no activity) or 1 (activity).  If you wanted to go crazy, these are actually single bits worth of data; but for simplicity, they're conveyed as full chars. 

I don't plan on expanding this project further, but I'm open to answering any questions via email (above).

Footnotes:
[1] The reason that the temperature LEDs aren't currently implemented is that the only way I can find to get the data from the command line (without writing the server code using Apple's libraries in Objective C) is to use Marcel Bresink's temperature monitor application (http://www.bresink.com/osx/TemperatureMonitor.html).  Unfortunately this would mean spawning a new process for each loop, which is something I really didn't want to do.  In the future, it would be good to rewrite the server to query this data, but that's not going to happen any time soon.
