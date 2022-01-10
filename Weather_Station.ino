#include <dht.h>

dht DHT;

#define DHT11_PIN 7

#define SHOCK_PIN 2

int Analog_Pin = A0; 
int Digital_Pin = 3; 

int LED = 5;

// Water level sensor pins
#define sensorPower 8
#define sensorPin A1
// Value for storing water level
int val = 0;

void setup(){
  Serial.begin(9600);
  pinMode(Analog_Pin, INPUT);
  pinMode(Digital_Pin, INPUT);
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);

  pinMode(LED, OUTPUT);       // on-board LED, usually pin 13
  pinMode(SHOCK_PIN, INPUT);          // shock sensor pin set to input
}

//This is a function used to get the water sensor reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  //delay(1000);

//earthquake detector
  if (digitalRead(SHOCK_PIN)) {       // shock detected?
    // shock not detected with pull-up resistor
    digitalWrite(LED, LOW);   // switch LED off
  }
  else {
    // shock detected with pull-up resistor
    digitalWrite(LED, HIGH);  // switch LED on
    delay(2000);                      // leave LED on for period
  }

  //thunder detector
  float Analog;
  int Digital;
    
 
  Analog = analogRead(Analog_Pin);
  Digital = digitalRead(Digital_Pin);
    
 
  Serial.print("Analog voltage :"); 
  Serial.print(Analog, 4);  
  Serial.print("V, ");
  Serial.print("Limit :");
  
  if(Digital==HIGH)
  {
      Serial.println(" reached ");
  }
  else
  {
      Serial.println(" Not yet reached ");
  }

  //water sensor
  int level = readSensor();
  
  Serial.print("Water level: ");
  Serial.println(level);
  
  Serial.println("----------------------------------------------------------------");
  delay (200);
}
