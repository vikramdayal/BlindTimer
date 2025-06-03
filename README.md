# BlindTimer
Arduino Nano IOT based timer which hides the time while the timer is on.

Most timers display the time while the timer is running. The display of time can provide a bias in some kind of experiments. For example, holding one's breadth. If you are looking at the timer, you might be biased in witholding the gasp to attain a certain milestone.

This timer, when turned on, will display patterns while it is running. At the end of the run, it will display the elapsed time in seconds.

The code is written for an Arduino Nano IOT. It utlizies port D2 as a PULL_UP input via a push nutton. It also utilizes an Adaafruit SSD_1306 display.

