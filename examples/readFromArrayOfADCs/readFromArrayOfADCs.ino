
#include "HX710Array.h"



////////////////////////////////////////////////////////////////
// PARAMETERS
////////////////////////////////////////////////////////////////

const int PD_SCK = 2;
const int DOUT0 = 3;
const int DOUT1 = 4;
const int DOUT2 = 5;

#define SERIAL_PLOTTER



////////////////////////////////////////////////////////////////
// SETUP
////////////////////////////////////////////////////////////////

HX710Array ps;

void setup() {
    Serial.begin( 115200 );
    int douts[] = { DOUT0 , DOUT1 , DOUT2 };
    ps.initialize( PD_SCK , 3 , douts );
}



////////////////////////////////////////////////////////////////
// LOOP
////////////////////////////////////////////////////////////////

void loop() {
    int32_t value0, value1, value2;
    
    while( !ps.isReady() );
    ps.readAndSelectNextData( HX710_DIFFERENTIAL_INPUT_40HZ );
    value0 = ps.getLastDifferentialInput( 0 );
    value1 = ps.getLastDifferentialInput( 1 );
    value2 = ps.getLastDifferentialInput( 2 );
    
#ifdef SERIAL_PLOTTER
    Serial.print( value0 );
    Serial.print( "\t" );
    Serial.print( value1 );
    Serial.print( "\t" );
    Serial.println( value2 );
#else
    Serial.print( "differential input of ADC0 (40 Hz): " );
    Serial.println( value0 );
    Serial.print( "differential input of ADC1 (40 Hz): " );
    Serial.println( value1 );
    Serial.print( "differential input of ADC2 (40 Hz): " );
    Serial.println( value2 );
    Serial.println();
#endif
}