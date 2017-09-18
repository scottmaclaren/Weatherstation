void setup() {
 int pinmin =2;
 int pinmax =13;
 //set all to outputs
 for (int i = pinmin; i<= pinmax; i++){
  pinMode(i,OUTPUT);
 }




  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);

//and with 11 to leave pin 0 and 1 the same for serial operation
//port D = 0 to 7 pins
//PORTD = (PORTD & B00000011) | (ledlibrary[0]<<2);

}


void loop() {
  
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

 
  for (int x = 10; x<=12; x++){
  digitalWrite(x,LOW);
  
    for (int i = 0; i<=9; i++){
      PORTD = (PORTD & B00000011) | (ledlibrary[i]<<2);
      digitalWrite(8,bitRead(ledlibrary[i],6));
      digitalWrite(9,bitRead(ledlibrary[i],7));
      delay(500);
    }
  delay(100);
  digitalWrite(x,HIGH);  
  }
  
}

void floattodigit (float temp){
  //assuming nothing higher than 99.9 degress

  if (temp > 99.9) {
        
  }
}

