#ifndef _HX710_H_
#define _HX710_H_



#include "Arduino.h"



#define HX710_DIFFERENTIAL_INPUT_10HZ  25
#define HX710_TEMPERATURE_40HZ         26
#define HX710_DIFFERENTIAL_INPUT_40HZ  27




class HX710 {

    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        bool isReady();
        HX710& powerDown();
        HX710& powerUp();
        HX710& initialize( uint8_t DOUT , uint8_t PD_SCK );
        HX710& readAndSelectNextData( uint8_t pulses );  // reads data, and selects next data using the number of pulses
        int32_t getLastDifferentialInput();  // gets the last differential input reading
        int32_t getLastTemperature();  // gets the last temperature reading


    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void setDataPointerToDifferentialInputRegister();
        void setDataPointerToTemperatureRegister();
        void sendClockPulse();
        void addBitToData( int value );


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private :
        uint8_t dout;  // DOUT
        uint8_t sck;  // PD_SCK
        int32_t differentialInput;
        int32_t temperature;
        int32_t* dataPointer;

};



#endif  // #ifndef _HX710_H_
