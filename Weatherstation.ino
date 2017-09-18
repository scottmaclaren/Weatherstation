void setup() {
 int pinmin =2;
 int pinmax =13;
 //set all to outputs
 for (int i = pinmin; i<= pinmax; i++){
  pinMode(i,OUTPUT);
 }
//low bit is pin 2, and bit next to B is pin 9
//led library starts at 0, and got up to 9
byte ledlibrary[] = {B00010010, B10011111,B00010101, B00110001, B00010101,B10011100, B00011111, B00010000,
  B00011100
  };

 byte minussign = B1111101;
 byte decimalsign = B1101111;
//control pins for leds = 10,11 & 12
//pin 10 = top digit, and 12 is bottom

digitalWrite(10,LOW);
digitalWrite(11,HIGH);
digitalWrite(12,HIGH);

//and with 11 to leave pin 0 and 1 the same for serial operation
//port D = 0 to 7 pins
//PORTD = (PORTD & B00000011) | (ledlibrary[0]<<2);

// PORTB = PORTB | (ledlibrary[0]<<6); didn't use because would need to 
//maintain 3 pins for 7seg multiplexing
//digitalWrite(8,bitRead(ledlibrary[0],6));
//digitalWrite(9,bitRead(ledlibrary[0],7));



}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i<=9, i++){
    PORTD = (PORTD & B00000011) | (ledlibrary[i]<<2);
    digitalWrite(8,bitRead(ledlibrary[i],6));
    digitalWrite(9,bitRead(ledlibrary[i],7));
  }
  
  
}

void floattodigit (float temp){
  //assuming nothing higher than 99.9 degress

  if (temp > 99.9) {
        
  }
}

