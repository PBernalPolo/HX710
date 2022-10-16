
#include "HX710Array.h"



////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////

HX710Array::HX710Array() {
}


HX710Array::~HX710Array() {
    this->deleteDataManagers();
}



////////////////////////////////////////////////////////////////
// PUBLIC METHODS
////////////////////////////////////////////////////////////////

HX710Array& HX710Array::initialize( uint8_t PD_SCK , uint8_t NADCs , int* DOUTs ) {
    // we initialize the HX710ArrayClockManager
    this->initializeClockManager( PD_SCK );
    // we initialize the HX710ArrayDataManager array
    this->N = NADCs;
    this->deleteDataManagers();  // we make sure that there is no memory leaks
    this->dm = new HX710DataManager*[NADCs];
    for(int i=0; i<this->N; i++) {
        this->dm[i] = new HX710DataManager();
        this->dm[i]->initialize( DOUTs[i] );
    }
    // we reset
    this->powerDown();
    this->powerUp();
    // and we read for the first time to select the default response
    this->readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_10HZ );
    return *this;
}


bool HX710Array::isReady() {
    for(int i=0; i<this->N; i++) {
        if( !this->dm[i]->isReady() ) {
            return false;
        }
    }
    return true;
}


int32_t HX710Array::getLastDifferentialInput( uint8_t adcIndex ) {
    return this->dm[adcIndex]->getLastDifferentialInput();
}


int32_t HX710Array::getLastOtherInput( uint8_t adcIndex ) {
    return this->dm[adcIndex]->getLastOtherInput();
}



////////////////////////////////////////////////////////////////
// PROTECTED METHODS
////////////////////////////////////////////////////////////////

void HX710Array::beginData() {
    for(int i=0; i<this->N; i++) {
        this->dm[i]->beginData();
    }
}


void HX710Array::readBitAndAddToData() {
    for(int i=0; i<this->N; i++) {
        this->dm[i]->readBitAndAddToData();
    }
}


void HX710Array::endData( uint8_t pulses ) {
    for(int i=0; i<this->N; i++) {
        this->dm[i]->endData( pulses );
    }
}



////////////////////////////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////////////////////////////

void HX710Array::deleteDataManagers() {
    for(int i=0; i<this->N; i++) {
        delete &(this->dm[i]);
    }
    delete[] this->dm;
    this->dm = NULL;
}
