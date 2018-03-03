int val = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 3 pots.
int lastVal = 0;
int val2 = 0;
int lastVal2 = 0;
int val3 = 0;
int lastVal3 = 0;
int boton=5;
int buttonState=0;
int lastbtnstate=0;
int led1=8;
int led2=9;
int led3=10;
int led4=11;
int led5=12;
int rebote=0;
int infrar=2;

volatile int ISRCounter = 0; //antirrebote
int counter = 0;  //antirrebote

void setup()
{
   Serial.begin(9600);       // Set the speed of the midi port to the same as we will be using in the Hairless Midi software 
   pinMode(boton,INPUT);
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
   pinMode(led3,OUTPUT);
   pinMode(led4,OUTPUT);
   pinMode(led5,OUTPUT);
   attachInterrupt(digitalPinToInterrupt(boton), debounceCount, HIGH); // antirrebote
   pinMode(infrar, INPUT);
   
}

void loop()
{
  buttonState=digitalRead(boton);
   /*if (buttonState == HIGH) {
    if(rebote==1){
      rebote=0;
     }
     else{
    rebote=1;}
    if(buttonState ==HIGH && rebote==1){
      
      val2+=254;
      if(val2>255){
        val2=0;
      }
      MIDImessage(176,2,val2);
    }      
   }*/
   if (counter != ISRCounter){ // si el boton ha sido presionado
    counter = ISRCounter;
    val2=255;    
    MIDImessage(176,2,val2);
    }
    else{
      val2=0;      
    }
    
   val2 = digitalRead(infrar);
   if (val2 != lastVal2){
       if(val2 ==0){
            MIDImessage(176,60,127);
       }
       else{
            MIDImessage(176,60,5);
       }
       
   }
   lastVal2 = val2;
   delay(10);
   
   val3 = analogRead(A0)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val3 != lastVal3) 
   {
     MIDImessage(176,3,val3);
   }         // 176 = CC command, 3 = Which Control, val = value read from Potentionmeter 3
   lastVal3 = val3;
   delay(10); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.

  leds();

}

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}

void leds(){
  int valed=floor(analogRead(A0)/200);
  switch(valed){
    case(0):
      digitalWrite(led5,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led1,LOW);
      break;
      
    case(1):
      digitalWrite(led5,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led1,LOW);
      break;

    case(2):
      digitalWrite(led5,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led1,LOW);
      break;

     case(3):
      digitalWrite(led5,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led2,LOW);
      digitalWrite(led1,LOW);
      break;

      case(4):
      digitalWrite(led5,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led1,LOW);
      break;

      case(5):
      digitalWrite(led5,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led1,HIGH);
      break;
    
   }
}


void debounceCount() // antirrebote
{
  ISRCounter++;
}

