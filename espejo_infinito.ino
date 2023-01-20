#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#define PIN 6 // We designate our data pin.
#define NUMPIXELS 100 // Designate how many pixels we have in our RGB LED strip.

// Define the number of pixels of the tape and the data pin.
// Parameter 1 = number of pixels on the tape.
// Parameter 2 = number of data pin of the Arduino.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int pinTrigger = 0;  // Variable containing the number of the pin to which the trigger signal is connected.
const int pinEcho = 1;     // Variable containing the number of the pin to which the "echo" signal is connected.
const int sensorPin=2;    // We declare the Relay on pin 2 of the arduino.
const int micPin  = 3;    // We declare the Relay on pin 3 of the arduino.
const int pinRele = 5;    // We declare the Relay on pin 5 of the arduino.
int val = 0; // Variable for assigning the PIR sensor reading.
int estadoPir= LOW;
float distmax=1000.00;
float distmin=30.00;
int micVal  = 0;



void setup()
{
pinMode(pinTrigger, OUTPUT); // Configure the "trigger" pin as output.
pinMode(pinEcho, INPUT);  // Configure the "echo" pin as input.
digitalWrite(pinTrigger, LOW); // Set the trigger pin to low voltage (0V).
pinMode(pinRele, OUTPUT); // Pin 5 of the arduino is assigned as the output for the Rele.
pinMode(sensorPin, INPUT); // Pin 2 is assigned as input for the sensor signal.
pinMode(micPin, INPUT); //Pin 3 is assigned as input for the sensor signal.
pixels.begin(); // We initialize our RGB LED strip.
Serial.begin(9600);
}

void loop()
{
//We declare several color combinations.
uint32_t rojo = pixels.Color(150,0,0);
uint32_t verde = pixels.Color(0,150,0);
uint32_t azul = pixels.Color(0,0,150);
uint32_t amarillo = pixels.Color(150,130,0);
uint32_t morado = pixels.Color(128,0,128);
uint32_t blanco = pixels.Color(150,150,255);
int control=0;
int modo=0;
int delayval = 10; // Fifty millisecond pause.
int cont=0;
val = digitalRead(sensorPin); //Reads the value of the variable (val).
if (val == HIGH) // If it detects that there is movement, it activates the LED connected to pin 6 of the arduino.
{
  digitalWrite(pinRele, LOW);
  if (estadoPir==LOW)  // If previously turned off
  {
    Serial.println("Sensor activado");
    estadoPir = HIGH;
    delay(100);
    while(control==0)
    {
      long t; // Unsigned long variable that will contain the time it takes for the signal to go and come back.
      long d; // Variable of type float that will contain the distance in cm.
      digitalWrite(pinTrigger, HIGH); // Set the "trigger" pin to high voltage (5V).
      delayMicroseconds(10); //We wait on this line to get a 10us pulse.
      digitalWrite(pinTrigger, LOW); // We set the "trigger" pin to low voltage (0V).
      t = pulseIn(pinEcho, HIGH);    // We use the function pulseIn() to measure the time.
      d = t/59; // Get the distance.
      Serial.print("Distancia: ");
      Serial.print(d);      // Serially send the value of the distance.
      Serial.print("cm");
      Serial.println();
      Serial.print("Tiempo: ");
      Serial.print(t);       // Serially send the time value.
      Serial.print("s");
      Serial.println();
      if(d > distmax || d < distmin)// We assign a maximum and minimum distance.
      {
        control=1;
      }
      while(cont<10){
        micVal = digitalRead(micPin);
        if (micVal==HIGH) 
        {
          modo++;
          if(modo>5){
            modo=0;
         }
        }
        cont++;
        delay(10);
      }
      cont=0;
      switch(modo)
      {
        case 0:
            for(int i=9;i<NUMPIXELS;i++)
            {
              pixels.setPixelColor(i, rojo); // Moderate brightness in red.
              pixels.show();   // We show and update the color of the pixel of our RGB led strip.
              delay(delayval);  // Pause for a period of time (in milliseconds).
            }
          break;
        case 1:
             for(int i=9;i<NUMPIXELS;i++)
             {
               pixels.setPixelColor(i, verde);  // Moderate brightness in green.
               pixels.show();   // We show and update the color of the pixel of our RGB led strip.
               delay(delayval); // Pause for a period of time (in milliseconds).
             }
             break;
        case 2:
            for(int i=9;i<NUMPIXELS;i++)
            {
              
              pixels.setPixelColor(i, amarillo); // Moderate brightness in yellow.
              pixels.show();  // We show and update the color of the pixel of our RGB led strip.
              delay(delayval); // Pause for a period of time (in milliseconds).
            }
            break;
       case 3:
             for(int i=9;i<NUMPIXELS;i++)
            {
              pixels.setPixelColor(i, azul); // Moderate brightness in blue.
              pixels.show();   // We show and update the color of the pixel of our RGB led strip.
              delay(delayval); // Pause for a period of time (in milliseconds).
            }
            break;
       case 4:
             for(int i=9;i<NUMPIXELS;i++)
            {
              pixels.setPixelColor(i, blanco); // Moderate brightness in white.
              pixels.show();  // We show and update the color of the pixel of our RGB led strip.
              delay(delayval); // Pause for a period of time (in milliseconds).
            }
            break;
        case 5:
             for(int i=9;i<NUMPIXELS;i++)
            {
              pixels.setPixelColor(i, morado); // Moderate brightness in purple.
              pixels.show();   // We show and update the color of the pixel of our RGB led strip.
              delay(delayval);// Pause for a period of time (in milliseconds).
            }
            break;     
      }
    }
  }
  digitalWrite(pinRele, HIGH); // LED OFF.
}else
{
 digitalWrite(pinRele, HIGH); // LED OFF.
 if (estadoPir == HIGH)  // If it was previously on.
  {
    Serial.println("Sensor parado");
    estadoPir  = LOW;
  }
}
}
