
#include "HX710DataManager.h"



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

void HX710DataManager::initialize( uint8_t DOUT ) {
    this->dout = DOUT;
    this->differentialInput = 0;
    this->otherInput = 0;
    this->setDataPointerToDifferentialInputRegister();
    // we set the input pin
    pinMode( this->dout , INPUT );
}


bool HX710DataManager::isReady() {
    // "When output data is not ready for retrieval, digital output pin DOUT is high."
    return ( digitalRead( this->dout ) == 0 );
}


void HX710DataManager::beginData() {
    *(this->dataPointer) = 0;
}


void HX710DataManager::readBitAndAddToData() {
    // we read the bit
    int value = digitalRead( this->dout );
    // we shift the data one place to the left
    *(this->dataPointer) <<= 1;
    // we add the last bit reading
    *(this->dataPointer) |= value;
}


void HX710DataManager::endData( uint8_t pulses ) {
    // first, we finalize the data representation
    //   this shifts the data to the left part of the int32_t register
    *(this->dataPointer) <<= 8;
    //   this shifts the data to the right part of the int32_t register, but copies the sign bit, correctly formatting for an int32_t
    *(this->dataPointer) >>= 8;
    // then, we update the data pointer depending on the number of pulses
    if( pulses == HX710_DATAMANAGER_OTHER_INPUT_40HZ ) {
        this->setDataPointerToOtherInputRegister();
    } else {
        this->setDataPointerToDifferentialInputRegister();
    }
}


int32_t HX710DataManager::getLastDifferentialInput() {
    return this->differentialInput;
}


int32_t HX710DataManager::getLastOtherInput() {
    return this->otherInput;
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void HX710DataManager::setDataPointerToDifferentialInputRegister() {
    this->dataPointer = &(this->differentialInput);
}


void HX710DataManager::setDataPointerToOtherInputRegister() {
    this->dataPointer = &(this->otherInput);
}
