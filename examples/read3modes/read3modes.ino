
#include "HX710.h"



////////////////////////////////////////////////////////////////
// PARAMETERS
////////////////////////////////////////////////////////////////

const int DOUT = 4;
const int PD_SCK = 3;

#define SERIAL_PLOTTER



////////////////////////////////////////////////////////////////
// SETUP
////////////////////////////////////////////////////////////////

HX710 ps;

void setup() {
    Serial.begin( 115200 );
    ps.initialize( PD_SCK , DOUT );
}



////////////////////////////////////////////////////////////////
// LOOP
////////////////////////////////////////////////////////////////

void loop() {
    int32_t v1, v2, v3;
    
    while( !ps.isReady() );
    ps.readAndSelectNextData( HX710_OTHER_INPUT_40HZ );
    v1 = ps.getLastDifferentialInput();
    
    while( !ps.isReady() );
    ps.readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_40HZ );
    v2 = ps.getLastOtherInput();
    
    while( !ps.isReady() );
    ps.readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_10HZ );
    v3 = ps.getLastDifferentialInput();
    
#ifdef SERIAL_PLOTTER
    Serial.print( v1 );
    Serial.print( "\t" );
    Serial.print( v2 );
    Serial.print( "\t" );
    Serial.println( v3 );
#else
    Serial.print( "differential input (10 Hz): " );
    Serial.println( v1 );
    Serial.print( "temperature (40 Hz): " );
    Serial.println( v2 );
    Serial.print( "differential input (40 Hz): " );
    Serial.println( v3 );
    Serial.println();
#endif
}