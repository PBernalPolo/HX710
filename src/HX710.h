#ifndef _HX710_H_
#define _HX710_H_


#include "HX710Template.h"
#include "HX710DataManager.h"



class HX710  :  public HX710Template {

    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        HX710& initialize( uint8_t PD_SCK , uint8_t DOUT );
        bool isReady();  // checks if the ADC is ready to send measurement
        int32_t getLastDifferentialInput();  // gets the last differential input reading
        int32_t getLastOtherInput();  // gets the last reading from other input


    ////////////////////////////////////////////////////////////////
    // PROTECTED METHODS
    ////////////////////////////////////////////////////////////////
    protected:
        void beginData();
        void readBitAndAddToData();
        void endData( uint8_t pulses );


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private :
        HX710DataManager dm;

};



#endif  // #ifndef _HX710_H_
