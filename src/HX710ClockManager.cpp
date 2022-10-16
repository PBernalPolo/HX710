
#include "HX710ClockManager.h"



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

void HX710ClockManager::initialize( uint8_t PD_SCK ) {
    this->sck = PD_SCK;
    pinMode( this->sck , OUTPUT );
}


void HX710ClockManager::powerDown() {
    // "When PD_SCK pin changes from low to high and stays at high for longer than 60μs, HX710 enters power down mode"
    digitalWrite( this->sck , HIGH );
    delayMicroseconds( 61 );
}


void HX710ClockManager::powerUp() {
    // "When PD_SCK returns to low, chip will return back to the setup conditions before power down and enter normal operation mode."
    digitalWrite( this->sck , LOW );
}


void HX710ClockManager::sendClockPulse() {
    digitalWrite( this->sck , HIGH );
    delayMicroseconds( 1 );  // T2+T3: PD_SCK rising edge to DOUT data ready + PD_SCK high time
    digitalWrite( this->sck , LOW );
    delayMicroseconds( 1 );  // T4: PD_SCK low time
}
