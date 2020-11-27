#include "esphome.h"
class My_dust_Sensor : public PollingComponent, public Sensor {
 public:
  My_dust_Sensor() : PollingComponent(5000) {}  // period between updates, here 10s
  

  void setup() override {

    pinMode(D4, OUTPUT);     // sensor led pin         
    pinMode(A0, INPUT);      // output form sensor
    
   }

  void update() override {

    int samplingTime = 280;
    int deltaTime = 40;
    int sleepTime = 9680;
    int numReadings = 10;
    int o = 0;
  
    float voMeasured = 0;
    float calcVoltage = 0;
    float dustDensity = 0;



    for (o = 0; o < numReadings; o++){
    
    digitalWrite(D4,LOW);              // power on the LED
    delayMicroseconds(samplingTime);            // delay
    voMeasured = voMeasured + analogRead(A0);    // read ADC (sensor)
    delayMicroseconds(deltaTime);             // delay
    digitalWrite(D4,HIGH);             // turn the LED off
    delayMicroseconds(sleepTime);           // delay
    //delay(1000);
    }
    
    voMeasured = voMeasured / numReadings;       // smoothing
    calcVoltage = voMeasured * (5.0 / 1024.0);
    dustDensity = 0.17 * calcVoltage - 0.1;

    //value = 0.17 * value - 0.1;        // calculate value (for GP2Y1010AU0F reads) 
  
  

    publish_state(dustDensity);              // publish
  }
};
