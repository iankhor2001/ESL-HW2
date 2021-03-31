My waveform will peak at S=1.
There will be 0.5Hz, 1Hz, 2Hz, 5Hz, 10Hz, and 15Hz.

[DISPLAY]
The display will have a pointer and the menu of all the selected frequencies.
Use up and down buttons to get around the menu, and select using the select button.
Once selected, the pointer will fix at that frequency, and it will become red.
To return back to the menu, press the up and down button together and hold them for a period.

The code for the display is from Line 33 to Line 104.
display() is for printing the initial menu, plus the frequencies displays too.
change_mode() is called then either up button or down button is pressed. It overwrite the previous pointer to empty space and write a WHITE point on the next frequency.
select_mode() is called when the frequency is selected. It turns the pointer RED.
release_mode() is called when returning to the menu. It turns the pointer WHITE.

[GENERATING THE WAVEFORM]
I used two FOR loops to generate the waveform. The signal climbed to the peak with 9 times the speed than going down to the bottom. To change the frequency, the program will change the steps of the FOR loop. To increase the frequency, lower the step, and vise versa.
The cutoff frequency is about 10Hz. I used a 16k Ohm resistor and 1nF capacitor.
Once 1000 samples is recorded, the program will stop generating the second DAC signal. However, the initial signal is still produced.

[SAMPLING]
The signal is passed through the RC filter and back to ADC port. The program then record the signal strength and generate the same signal from another DAC port. This signal is finally tested with the Picoscope.

[ANALYSIS]
To get a correct analysis, you have to run the FFT.py program first and then only press the select button. To get the second sample, refresh the program and repeat the procedure.
