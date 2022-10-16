
#include "HX710.h"



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

HX710& HX710::initialize( uint8_t PD_SCK , uint8_t DOUT ) {
    // we initialize the HX710ClockManager
    this->initializeClockManager( PD_SCK );
    // we initialize the HX710DataManager
    this->dm.initialize( DOUT );
    // we reset
    this->powerDown();
    this->powerUp();
    // and we read for the first time to select the default response
    this->readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_10HZ );
    return *this;
}


bool HX710::isReady() {
    return this->dm.isReady();
}


int32_t HX710::getLastDifferentialInput() {
    return this->dm.getLastDifferentialInput();
}


int32_t HX710::getLastOtherInput() {
    return this->dm.getLastOtherInput();
}



////////////////////////////////////////////////////////////////
// PROTECTED METHODS
////////////////////////////////////////////////////////////////

void HX710::beginData() {
    this->dm.beginData();
}


void HX710::readBitAndAddToData() {
    this->dm.readBitAndAddToData();
}


void HX710::endData( uint8_t pulses ) {
    this->dm.endData( pulses );
}
