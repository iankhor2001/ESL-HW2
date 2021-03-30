#include "mbed.h"

// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
AnalogOut  pout(D13);
AnalogIn ain(A0);


float ADCdata;

Thread adc_thread;


void adc_process(){
    while(1){
        ADCdata = ain;
        printf("%f\n", ADCdata);
        pout = ADCdata;
        ThisThread::sleep_for(1ms);
    }
}


int main(void)
{
    int n=10;
    int n_temp=n;
    adc_thread.start(adc_process);
    while (1) {
        // cutoff 736Hz
        for (float i = 0.0f; i < 0.736f; i += 0.00736f*n) {
            aout = i; //
            ThisThread::sleep_for(10ms);
        }
        for (float i = 0.736f; i > 0.0f; i -= 0.000818f*n) {
            aout = i;
            ThisThread::sleep_for(10ms);
        }
        if (n!=n_temp) break;
        // adc_process();
    }



}