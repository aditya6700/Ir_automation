/*******************************************************************************
 * This is a simple home automation using IR receiver and
 * any remote. The principle behind it is every remote 
 * sends our IR(infrared waves) each have different wavelenght 
 * we just read those values using IR receiver 
 * using any microcontroller or microprocessor we read those values
 * and save them 
 * 
 * here in this project we firstly take some reading of the remote 
 * of our required buttons and compare and use the REALAY(electromagnetic switch)
 * to toggle them.
 * any problems and queires contact :- 9989209310  email :- dsaiaditya@gmail.com
 *********************************************************************************/

// hello vamsi hope you understand it easily

#include <IRremote.h>

const int IR_PIN = 8;   //declaring pin
IRrecv irrecv(IR_PIN);  // creating ir object and giving pin no.
decode_results results;  // creating variable results to store the IR values

//declaring the pin numbers
int fan=3;
int lyt1=4;
int lyt2=5;
int bed=6;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();  // to starat the ir receiver
  irrecv.blink13(true);  //to blink led on arduino everytime we press button on ir remote

  // configuring the pinMode of all the pins 
  pinMode(fan,OUTPUT);
  pinMode(lyt1,OUTPUT);
  pinMode(lyt2,OUTPUT);
  pinMode(bed,OUTPUT);
}

// taking some boolean values to update the condition of the decives and toggle accordingly
bool f=false;
bool l1=false;
bool l2=false;
bool b=false;

void loop(){
  if (irrecv.decode(&results)) // if any sgnl recceived it store in results.value
  {
        Serial.println(results.value, HEX); // the received values are HEXADECIMAL values
        
     if(results.value== (0x72244F1A))
     {
        b=!b;  // toggling the pin if using not conditon
        digitalWrite(bed, b);
     }
     else if(results.value== 0x5D3FC09E || results.value==0xFFD926)
     {
        l1=!l1;
        digitalWrite(lyt1, l1);
     }
     else if(results.value== 0xE4ED513A || results.value==0xFF9966)
     {
        l2=!l2;
        digitalWrite(lyt2, l2);
     }     
     else if(results.value== 0xC963CB9C || results.value==0xFF59A6)
     {
        f=!f;
        digitalWrite(fan, f);
     }
     else if(results.value== 0xD4F20360 || results.value==0xFF7986)
     {
        digitalWrite(fan, LOW);
        digitalWrite(lyt1, LOW);
        digitalWrite(lyt2, LOW);
        digitalWrite(bed, LOW);
     }
        irrecv.resume();  //used to reset the receiver and preaprre for nxt sgnl
  }
}           
