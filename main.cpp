#include "mbed.h"                   //including mbed.h
AnalogIn analog_value(PA_0);        //Setting pin PA0 (A0) as Anlog Input
Serial pc(SERIAL_TX, SERIAL_RX);    //Create an object of Serial Class


const float c1 = 1.009249522e-03;
const float c2 = 2.378405444e-04;
const float c3 = 2.019202697e-07;

float calcTempOriginal(float adcReading) {
    float R0 = 10000.0; // Nominal resistance (10kΩ)
    float R = R0 / adcReading - R0; // Calculating resistance
    
    float T = 1.0 / (c1 + c2 * log(R) + c3 * pow(log(R), 3)); // Temperature calculation
    
    return T - 273.15; // Convert temperature to Celsius
}

float calcTempNegLog(float adcReading) {
    float R0 = 10000.0; // Nominal resistance (10kΩ)
    float R = -(R0 / adcReading - R0);
    
    float T = 1.0 / (c1 + c2 * log(R) + c3 * pow(log(R), 3)); // Temperature calculation
    
    return T - 273.15; // Convert temperature to Celsius
}

float calcTempArduino(float adcReading)
{
    float R1 = 10000.0; 
    float R2 = R1 * (1023.0 / adcReading - 1.0);

    float logR2 = log(R2);

    float T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));

    return T - 273.15;

}

int main() {
    float meas;
    float temp;
    while(1) {
        meas = analog_value.read();
        temp = calcTempNegLog(meas);
        pc.printf("temp  %.2f ^C\r\n", temp);
        ThisThread::sleep_for(10);
    }
}