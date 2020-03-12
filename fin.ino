#include <Servo.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);//lcd initialisation
Servo myservo; //server initialisation
int sensor_pin = A0;
//define the analog pin to which the soil moisture sensor is connected
int sensor_pin1=A1;
int motor = 8; // moto pin of pump
int pos = 0; //
//define the digital pin to which dc water pump is to be connected
int tx = 1;
//define the transmitter pin0
int rx = 0;
//define the receiver pin
int output_value ;
int output_value1;
//integer to store the output value of soil moiture sensor
const int analogOutPin = 1; 
//set analog output pin to pin 1
int threshold = 800;
//set the threshold value = 800
int current_value;
int current_value1;
//integer to store current value of soil moisture sensor reading
const int trigPin = 7;
const int echoPin = 6;
// defines variables
long duration;
int distance;
void setup() 
//void setup runs once
{  myservo.attach(9);
lcd.begin(16,2);
lcd.print("monitoring"); // lcd welcome display
   Serial.begin(9600);
   //begin serial communication at baud rate 9600
   Serial.println("Reading From the Sensor ...");
   //print that readin from soil moisture sensor has begun
   pinMode(motor, OUTPUT);
   //set motor pin as OUPUT
   pinMode(tx, OUTPUT);
   //set transmitter pin as OUTPUT
   pinMode(rx, INPUT);
   //set receiver pin as OUTPUT
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
   delay(2000);
   //create a delay of 2s
   }

void loop() 
//void loop runs continuously
{     
   //send the output_value to transmitter pin
  lcd.clear();
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
 analogWrite(analogOutPin, 0); 
   analogWrite(analogOutPin, output_value); 
   if(distance<15){ 
   Serial.print("water level is low....");
   
   lcd.print("water level is low");
   }
   delay(1000);
   output_value= analogRead(sensor_pin);
   //read the value of soil moisture sensor and store it in output_value 
   current_value = output_value;
   //set current_value equal to output_value
   output_value= constrain(output_value,330,1023); 
   //set the contrain on output_value. Minimum = 10 Maximum = 1023 
   output_value= map(output_value,330,1023,100,0); 
   //map the output_value
   analogWrite(analogOutPin, 0); 
   analogWrite(analogOutPin, output_value); 
   //send the output_value to transmitter pin
   Serial.print("Moisture of plant 1 : ");
   //print Moisture:
   Serial.print(output_value);
   //print the output_value
   Serial.println("%");
   //print %
   lcd.print("plant 1 : ");
   //print Moisture:
   lcd.print(output_value);
   //print the output_value
   lcd.print("%");
      if(current_value >=threshold)
   //check if current_value >= 800
   {
    //if yes then
    Serial.println("water level low... turning water pump on..");
    //print water level low.. turning water pump on..
    myservo.write(40);  
    digitalWrite(motor,HIGH);
    //turn on the dc water pump
    delay(1000);
   }
   else
   {
    //if no then
    Serial.println("Water level high... turning water pump off");
    //print water leve high.. turning water pump off..
    digitalWrite(motor,LOW);
    //turn off the dc water pump
   }
   delay(4000);
   lcd.clear();
   output_value1= analogRead(sensor_pin1);
   //read the value of soil moisture sensor and store it in output_value 
   current_value1 = output_value1;
   //set current_value equal to output_value
   output_value1= constrain(output_value1,330,1023); 
   //set the contrain on output_value. Minimum = 10 Maximum = 1023 
   output_value1= map(output_value1,330,1023,100,0); 
   //map the output_value
   analogWrite(analogOutPin, 0); 
   analogWrite(analogOutPin, output_value1); 
   //send the output_value to transmitter pin
   Serial.print("Moisture of plant 2: ");
   //print Moisture:
   Serial.print(output_value1);
   //print the output_value
   Serial.println("%");
   //print %
   lcd.print(" plant 2 : ");
   //print Moisture:
   lcd.print(output_value1);
   //print the output_value
   lcd.print("%");
   if(current_value1 >=threshold)
   //check if current_value >= 800
   {
    //if yes then
    Serial.println("water level low... turning water pump on..");
     myservo.write(0);     
    //print water level low.. turning water pump on..
    digitalWrite(motor,HIGH);
    //turn on the dc water pump
      delay(1000);
   }
   else
   {
    //if no then
    Serial.println("Water level high... turning water pump off");
    //print water leve high.. turning water pump off..
    digitalWrite(motor,LOW);
    //turn off the dc water pump
   }
   //create a delay of 3 second
   delay(2000);
}
