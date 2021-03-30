#include "mbed.h"
#include "uLCD_4DGL.h"
// Initialize a pins to perform analog and digital output functions
// Adjust analog output pin name to your board spec.
AnalogOut  aout(PA_4);
AnalogOut  pout(D13);
AnalogIn ain(A0);
DigitalIn down(A1);
DigitalIn up(A2);
DigitalIn select_pin(A3);
uLCD_4DGL uLCD(D1, D0, D2); 

float ADCdata;
Thread adc_thread;

int mode=0;
int n=10;
void adc_process(){
    while(1){
        ADCdata = ain;
        printf("%f\n", ADCdata);
        pout = ADCdata;
        wait_us(100);
    }
}

void display(){
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,1);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf(" .5Hz"); 

    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,2);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf("  1Hz"); 

    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,3);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf("  2Hz"); 
  
    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,4);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf("  5Hz");

    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,5);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf(" 10Hz");

    uLCD.text_width(2); 
    uLCD.text_height(2);
    uLCD.locate(0,6);
    uLCD.color(GREEN);
    uLCD.printf(" >"); 
    uLCD.printf(" 15Hz");
}

void change_mode(int mode_in){
    int row_now = mode_in+2;
    for(int num=1;num<=6;num++){
        uLCD.locate(0,num);
        if (num==row_now){
            uLCD.color(WHITE);
            uLCD.printf(" >"); 
        }
        else {
            uLCD.printf("  ");
        }
    }
}

void select_mode(int mode_in){
    int row_now = mode_in+2;
    uLCD.locate(0,row_now);
    uLCD.color(RED);
    uLCD.printf(" >"); 
}

void release_mode(int mode_in){
    int row_now = mode_in+2;
    uLCD.locate(0,row_now);
    uLCD.color(WHITE);
    uLCD.printf(" >"); 
}

int main(void)
{
    adc_thread.start(adc_process);
    display();
    while(1){
        int mode_temp = mode;
        if (up.read()==1)
            mode++;
        else if (down.read()==1)
            mode--;
        if(mode>4)
            mode=-1;
        if (mode<-1)
            mode=4;
        if(mode_temp!=mode)
            change_mode(mode);

        switch(mode){
            case -1:
                n=5; //1hz
                break;
            case 0:
                n=10; //1hz
                break;
            case 1:
                n=20; //2hz
                break;
            case 2:
                n=50; //5hz
                break;
            case 3:
                n=100; //10hz
                break;
            case 4:
                n=150; //10hz
                break;
        }

        if (select_pin.read()==1){
            select_mode(mode);
            //10=1hz, 20=2hz, 100=10hz
            while (1) {
            // cutoff 736Hz
                for (float i = 0.0f; i < 0.736f; i += 0.000736f*n) {
                    aout = i; //
                    wait_us(500);
                }
                for (float i = 0.736f; i > 0.0f; i -= 0.0000818f*n) {
                    aout = i;
                    wait_us(500);
                }
                if (up.read()==1 && down.read()==1) {
                    aout=0; 
                    ThisThread::sleep_for(300ms);
                    release_mode(mode);
                    break;
                }
            }
        }
        ThisThread::sleep_for(100ms);
    }
}