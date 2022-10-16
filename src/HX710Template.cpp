
#include "HX710Template.h"



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

HX710Template& HX710Template::initializeClockManager( uint8_t PD_SCK ) {
    this->cm.initialize( PD_SCK );
    return *this;
}


HX710Template& HX710Template::powerDown() {
    this->cm.powerDown();
    return *this;
}


HX710Template& HX710Template::powerUp() {
    this->cm.powerUp();
    return *this;
}


HX710Template& HX710Template::readAndSelectNextData( uint8_t pulses ) {
    delayMicroseconds( 1 );  // T1: DOUT falling edge to PD_SCK rising edge
    // we read the 24 bits that compose the measured data
    this->beginData();
    for(uint8_t i=0; i<24; i++) {
        this->cm.sendClockPulse();
        this->readBitAndAddToData();
    }
    // we continue sending pulses to select the next data mode
    for(uint8_t i=24; i<pulses; i++) {
        this->cm.sendClockPulse();
    }
    // finally we conclude the representation in the data register
    this->endData( pulses );
    return *this;
}
