#include <Ps3Controller.h>

void setup()
{
    Serial.begin(115200);
    Ps3.begin("a0:5a:5b:a0:07:c4");
    Serial.println("Ready.");
}

void loop()
{
    if(Ps3.isConnected()){

        if( Ps3.data.button.cross ){
            Serial.println("Pressing the cross button");
        }

        if( Ps3.data.button.square ){
            Serial.println("Pressing the square button");
        }

        if( Ps3.data.button.triangle ){
            Serial.println("Pressing the triangle button");
        }

        if( Ps3.data.button.circle ){
            Serial.println("Pressing the circle button");
        }

    }
}
