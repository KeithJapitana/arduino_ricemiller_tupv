// Sensor Threshold 
int ML1 = 14;
int ML2 = 13;
int TL  = 34;
int IRL = 80;


//LCD SECTION 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#include <dht.h>

 

 
    
//SENSORS SECTION ------
dht DHT; 
int TempI = 0;
#define DHTpin 10
#define IRpin A1
#define Moispin A0
  
  



void setup() {

  lcd.begin(16,2); 
  pinMode(DHTpin,INPUT);
  pinMode(IRpin, INPUT);
  pinMode(Moispin, INPUT);
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH);

 
  
  
}

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}


void loop() {
//Sensor DHT --------
  int readData = DHT.read22(DHTpin); 
  float t = DHT.temperature;
  int dhtnow[10];
  int dhtraw = 0;
  int dhtcomp = 0;
  int dhtppm = 0;
  int dhttotal = 0;
  for (int b = 0; b<10; b++)
  {
    dhtnow[b] = t;
    delay(100);
  }

  for (int b = 0; b<10; b++)
  {
    dhttotal = dhttotal + dhtnow[b];
  }
  dhtraw = dhttotal/10;
  dhtcomp = dhtraw ;
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(11, 1);
  lcd.print(dhtcomp);
/*------------------------------------------------------------------------------------------------------------------------------------- */


  //Sensor Moisture --------------------------
  int Mnow[10];
  int Mraw = 0;
  int Mcomp = 0;
  int Mppm = 0;
  int Mtotal = 0;
  int percent = 0;
  for (int c = 0; c<10; c++)
  {
    Mnow[c] = analogRead(A0);
    delay(100);
  }

  for (int c = 0; c<10; c++)
  {
    Mtotal = Mtotal + Mnow[c];
  }
  Mraw = Mtotal/10;
  Mcomp = Mraw ;
  Mppm = map(Mcomp,0,1023,100,0);
   lcd.setCursor(0,0);
   lcd.print("MOISTURE.");
   lcd.setCursor(11, 0);
   lcd.print(Mppm);
  
  /*------------------------------------------------------------------------------------------------------------------------------------- */
  // IR SENSOR SECTION -------------------------------------------------
  int IRppm = 0;
  int IRcomp = 0;
  IRcomp = analogRead(A1);
  delay(500);
  IRppm = map(IRcomp,0,1023,100,0);
  

/*------------------------------------------*/

  //Algorithm Section

  // Process 1 Heating
  if(Mppm>ML1)
  { 
    
    //mixer on
    //mwire on
    //blow on
  if(dhtcomp>TL)
  {
    digitalWrite(7,HIGH);
    //mwire off
   
  }
  else{
    digitalWrite(7,LOW);
    //mwire on
  }
  
  }
  else
  {
    
    // mixer off
    // mwire off
    // blow off
  }

  // Process 2 

  if(IRppm>IRL)
  
  {
    digitalWrite(13,HIGH);
  if (Mppm<ML1)
  {
      //reverse 
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  delay(4000);
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(12, HIGH);
  delay(10000);
   //forward 
   digitalWrite(12, LOW);
  delay(4000);
  digitalWrite(12, HIGH);
  delay(1000);

    
  }
  else 
  {
    // CLOSE DOOR
    // OFF MOTOR
    // MIXER ON
  }
  
    
  }
  else
  {
    digitalWrite(13,LOW);
  }
  
  
 
}
