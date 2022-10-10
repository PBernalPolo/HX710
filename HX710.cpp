
#include "HX710.h"



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

bool HX710::isReady() {
    // "When output data is not ready for retrieval, digital output pin DOUT is high."
    return ( digitalRead( this->dout ) == 0 );
}


HX710& HX710::powerDown() {
    // "When PD_SCK pin changes from low to high and stays at high for longer than 60μs, HX710 enters power down mode"
    digitalWrite( this->sck , HIGH );
    delayMicroseconds( 61 );
    return *this;
}


HX710& HX710::powerUp() {
    // "When PD_SCK returns to low, chip will return back to the setup conditions before power down and enter normal operation mode."
    digitalWrite( this->sck , LOW );
    return *this;
}


HX710& HX710::initialize( uint8_t DOUT , uint8_t PD_SCK ) {
    this->dout = DOUT;
    this->sck = PD_SCK;
    this->differentialInput = 0;
    this->temperature = 0;
    // we set the input pin
    pinMode( this->dout , INPUT );
    // we set the output pin
    pinMode( this->sck , OUTPUT );
    // we reset
    this->powerDown();
    this->powerUp();
    // and we read for the first time to select the default response
    this->setDataPointerToDifferentialInputRegister();
    this->readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_10HZ );
    return *this;
}


HX710& HX710::readAndSelectNextData( uint8_t pulses ) {
    *(this->dataPointer) = 0;  // we initialize the data register
    int value;  // we store here the last value read using digitalRead( this->dout )
    delayMicroseconds( 1 );  // T1: DOUT falling edge to PD_SCK rising edge
    // we read the 24 bits that compose the measured data
    for(uint8_t i=0; i<24; i++) {
        this->sendClockPulse();
        value = digitalRead( this->dout );
        this->addBitToData( value );
    }
    // we continue sending pulses to select the next data mode. We also continue to add the last received bit.
    for(uint8_t i=24; i<pulses; i++) {
        this->sendClockPulse();
        this->addBitToData( value );
    }
    // we continue adding the last bit value until we complete the 32 bits of int32_t
    for(uint8_t i=pulses; i<32; i++) {
        this->addBitToData( value );
    }
    // finally, we point to the right register depending on the selected data mode
    if( pulses == HX710_TEMPERATURE_40HZ ) {
        this->setDataPointerToTemperatureRegister();
    } else {
        this->setDataPointerToDifferentialInputRegister();
    }
    return *this;
}


int32_t HX710::getLastDifferentialInput() {
    return this->differentialInput;
}


int32_t HX710::getLastTemperature() {
    return this->temperature;
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void HX710::setDataPointerToDifferentialInputRegister() {
    this->dataPointer = &(this->differentialInput);
}


void HX710::setDataPointerToTemperatureRegister() {
    this->dataPointer = &(this->temperature);
}


void HX710::sendClockPulse() {
    digitalWrite( this->sck , HIGH );
    delayMicroseconds( 1 );  // T2+T3: PD_SCK rising edge to DOUT data ready + PD_SCK high time
    digitalWrite( this->sck , LOW );
    delayMicroseconds( 1 );  // T4: PD_SCK low time
}


void HX710::addBitToData( int value ) {
    *(this->dataPointer) <<= 1;
    *(this->dataPointer) |= value;
}
