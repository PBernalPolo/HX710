#ifndef _HX710_ARRAY_H_
#define _HX710_ARRAY_H_


#include "HX710Template.h"
#include "HX710DataManager.h"



class HX710Array  :  public HX710Template {

    ////////////////////////////////////////////////////////////////
    // PUBLIC CONSTRUCTORS AND DESTRUCTORS
    ////////////////////////////////////////////////////////////////
    public:
        HX710Array();
        ~HX710Array();

    ////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ////////////////////////////////////////////////////////////////
    public:
        HX710Array& initialize( uint8_t PD_SCK , uint8_t NADCs , int* DOUTs );
        bool isReady();  // checks if the ADCs are ready to send measurement
        int32_t getLastDifferentialInput( uint8_t adcIndex );  // gets the last differential input reading
        int32_t getLastOtherInput( uint8_t adcIndex );  // gets the last reading from other input


    ////////////////////////////////////////////////////////////////
    // PROTECTED METHODS
    ////////////////////////////////////////////////////////////////
    protected:
        void beginData();
        void readBitAndAddToData();
        void endData( uint8_t pulses );


    ////////////////////////////////////////////////////////////////
    // PRIVATE METHODS
    ////////////////////////////////////////////////////////////////
    private:
        void deleteDataManagers();


    ////////////////////////////////////////////////////////////////
    // PRIVATE VARIABLES
    ////////////////////////////////////////////////////////////////
    private :
        int N;  // number of ADCs
        HX710DataManager** dm;  // pointer to array of pointers to HX710DataManager

};



#endif  // #ifndef _HX710_ARRAY_H_
