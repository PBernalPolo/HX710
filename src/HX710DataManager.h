#ifndef _HX710_DATA_MANAGER_H_
#define _HX710_DATA_MANAGER_H_


#include "Arduino.h"


#define HX710_DATAMANAGER_DIFFERENTIAL_INPUT_10HZ  25
#define HX710_DATAMANAGER_OTHER_INPUT_40HZ  26
#define HX710_DATAMANAGER_DIFFERENTIAL_INPUT_40HZ  27



class HX710DataManager {

    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        void initialize( uint8_t DOUT );  // initializes the data manager
        bool isReady();  // checks if the ADC is ready to send data
        void beginData();  // initializes the data register pointed by the data pointer
        void readBitAndAddToData();  // reads a new bit, and adds it to the data register pointed by the data pointer
        void endData( uint8_t pulses );  // finalizes the data representation, and updates the data pointer depending on the number of pulses
        int32_t getLastDifferentialInput();  // gets the last differential input reading
        int32_t getLastOtherInput();  // gets the last reading from the other input


    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void setDataPointerToDifferentialInputRegister();  // sets the data pointer to the differential input register
        void setDataPointerToOtherInputRegister();  // sets the data pointer to the other input register        


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private :
        uint8_t dout;  // DOUT
        int32_t differentialInput;
        int32_t otherInput;
        int32_t* dataPointer;

};



#endif  // #ifndef _HX710_DATA_MANAGER_H_
