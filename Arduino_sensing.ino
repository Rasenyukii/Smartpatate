//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 160  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;
const int LED1 = 7;
const int LED2 = 6;
const int LED3 = 5;
 
   
   

void setup()
{
  
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;

  
  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);


  


  Serial.begin(115200);

  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;         //-+
}

void loop()
{
  unsigned int d;
  int Max = 0, Fmax = 0;

  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
   
    freq[d] = d;

    


    if ( v > Max)
      {
         Max = v;
         Fmax = d;
      }}

     digitalWrite(LED1, LOW);
     digitalWrite(LED3, LOW);
     digitalWrite(LED2, LOW);
     Serial.print(Fmax);
     Serial.print("\n");
     
     if (( Fmax > 70 ) && ( Fmax <= 90 ))
      {
          digitalWrite(LED1, HIGH);
          digitalWrite(LED3, LOW);
     digitalWrite(LED2, LOW);
          
         
      }
     if (( Fmax > 95 ) && ( Fmax <= 120 ))
      {
          digitalWrite(LED2, HIGH);
          digitalWrite(LED3, LOW);
          digitalWrite(LED1, LOW);
         
      
      }
      if (( Fmax > 120 ) && ( Fmax <= 200))
      {
          digitalWrite(LED3, HIGH);
          digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
                
      }
 //   plot(v,0);              //-Display
 //   plot(results[d],1);
  // delayMicroseconds(1);
  


 

  TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)
}
   

