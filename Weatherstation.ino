//global variables

bool newData = false;

void setup() {
 int pinmin =2;
 int pinmax =13;
 //set all to outputs
 for (int i = pinmin; i<= pinmax; i++){
  pinMode(i,OUTPUT);

 }

 Serial.begin(9600);
 Serial.println("<Arduino is ready>");



  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);

//and with 11 to leave pin 0 and 1 the same for serial operation
//port D = 0 to 7 pins
//PORTD = (PORTD & B00000011) | (ledlibrary[0]<<2);

}


void loop() {
  //program is expecting an incoming number with at most, 1 decimal place of precision- float would be nice
  //low bit is pin 2, and bit next to B is pin 9
  //led library starts at 0, and got up to 9


  const byte ledlibrary[] = {B00010010, B10011111, B00110001, B00010101, B10011100,
                             B01010100, B01010000, B00011111, B00010000, B00011100
    };

   //control pins for leds = 10,11 & 12
  
  //pin 10 = top digit, and 12 is bottom
  //write them high to turn off the 7seg
  const byte topPin =10;
  const byte middlePin = 11;
  const byte bottomPin = 12;   
    
  const byte minussign = B1111101;
  const byte decimalsign = B1101111;
  const byte allLedsOff = B11111111;

  byte topled;
  byte middleled;
  byte bottomled;
  float incomingtemp;
  float incomingtransfer;
  float oldtemp;
  bool tempneg = false;

  
  incomingtransfer = recvfloat();
  
  if (incomingtemp < 0){
    tempneg = true;
  }
  else
  tempneg = false;

  
  if (newData = true){
    incomingtemp = incomingtransfer;
  }
  
  flipNewData();

  

  

  //temperature now stored in incoming temp

  floattodigit(incomingtemp, &topled, &middleled, &bottomled);
  //now the seperated digits are stored in top middle and bottom

  //now need to write to display

  Serial.println("this is topled " + topled);
  Serial.println("this is middleled " + middleled);
  Serial.println("this is bottomled " + bottomled);
  
  

  //numbertodisplay(topled,middleled,bottomled, true);
  


  
 
  
}



//start of functions

//worried about this getting stuck or returning weird things if the timing doesn't sync on rasp

float recvfloat() {
 if (Serial.available() > 0) {
 newData = true;
 return Serial.parseFloat();
 }
}


void flipNewData() {
 if (newData == true) {
 newData = false;
 }
}



void floattodigit (float temp, byte * topled, byte * middleled, byte * bottomled){
  //assuming nothing higher than 99.9 degress
  //should I work with structs or pass it by reference?
  //& to attachec address (put & in when I call function
  // * to get actual value
  if (temp > 99.9 && temp <1000) {
    //cast to 3 digits
    int intTemp = (int) temp;
    
    *bottomled = (byte) (intTemp % 10);
    intTemp = intTemp/10;

    *middleled = (byte) (intTemp % 10);
    intTemp = intTemp/10;
    
    *topled = (byte) (intTemp % 10);
     

    //call function for all 3 active, non zero
    //could call it as like a state machine function or 4 seperate functions
  }
//might get a type mismatch? Not sure what the mod op returns
  else if (temp <= 99.9 && temp >= 10) {
    //shift all into non decimal space
    byte transfertemp = (byte) (temp * 10);
    
    *bottomled = (byte) (transfertemp % 10);
    transfertemp = transfertemp / 10;
    
    *middleled = (byte) (transfertemp % 10);
    transfertemp = transfertemp / 10;
    
    *topled = (byte) (transfertemp % 10);
  
  //call function with one decimal place on middle led  
  }


  else if (temp > 0 && temp < 10){
    
//this is the binary for all LEDs off
    *topled = B11111111;
    //because we want the top to be off

    byte transfertemp = (byte) (temp * 10);

    *bottomled = (byte) (transfertemp % 10);
    transfertemp = transfertemp / 10;
    
    *middleled = (byte) (transfertemp % 10);
    
    
  }

  else {
    //for neg temperatures later to do
    //turning them all off for the moment
    *topled = B11111111;
    *middleled = B11111111;
    *bottomled = B11111111;
  }

}

void numbertodisplay(byte topled, byte  middleled, byte bottomled, bool posorneg){

  const byte ledlibrary[] = {B00010010, B10011111, B00110001, B00010101, B10011100,
                             B01010100, B01010000, B00011111, B00010000, B00011100
    };

  const byte minussign = B1111101;
  const byte decimalsign = B1101111;
  const byte allLedsOff = B11111111;

  const byte topPin =10;
  const byte middlePin = 11;
  const byte bottomPin = 12; 

  //turn led 1 on, and others off
  //pin 10 = top digit, and 12 is bottom
  //write them high to turn off the 7seg

  digitalWrite(topPin, LOW);
  digitalWrite(middlePin, HIGH);
  digitalWrite(bottomPin, HIGH);
//and with 11 to preserve pins 1 and 0 for serial comm
  if (topled ==allLedsOff | topled == minussign){
    PORTD = (PORTD & B00000011) | (topled<<2);
    digitalWrite(8,bitRead(topled,6));
    digitalWrite(9,bitRead(topled,7));
    
  }
  else{
  PORTD = (PORTD & B00000011) | (ledlibrary[topled]<<2);
  digitalWrite(8,bitRead(ledlibrary[topled],6));
  digitalWrite(9,bitRead(ledlibrary[topled],7));
  }

  digitalWrite(topPin, HIGH);
  digitalWrite(middlePin, LOW);
  digitalWrite(bottomPin, HIGH);

  PORTD = (PORTD & B00000011) | (ledlibrary[middleled]<<2);
  digitalWrite(8,bitRead(ledlibrary[middleled],6));
  digitalWrite(9,bitRead(ledlibrary[middleled],7));
  //add decimal point
  digitalWrite(6,LOW);


  digitalWrite(topPin, HIGH);
  digitalWrite(middlePin, HIGH);
  digitalWrite(bottomPin, LOW);

  PORTD = (PORTD & B00000011) | (ledlibrary[bottomled]<<2);
  digitalWrite(8,bitRead(ledlibrary[bottomled],6));
  digitalWrite(9,bitRead(ledlibrary[bottomled],7));

  
}

