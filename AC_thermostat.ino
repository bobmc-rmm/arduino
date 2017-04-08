// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  AC_thermostat.ino 
 * @brief Improves Honeywell A/C using LM35 sensor
 * - temperature was varying 4 degrees
 * - varies < 1.0 with the Arduino Uno and LM35 
 * 
 * 13aug05a  2013aug20a 2013aug21 2013sep07 2017apr07
 */ 

int LED_pin = 13;
int RELAY_pin = 12;			// switch
int times = 0;
int inLM35 = A0;  // sense using LM35 temperature sensor
int inAdj = A1;  // temperature setting;
int sv,sv2,sum,sum2,numLines, hot;
float fv, fv2, diff;

void do_init(void);
void shuffle(void);

/// the setup routine runs once when you press reset:
void setup() {                
   // initialize the digital pin as an output.
   sum = sv = sv2 = sum2 = numLines = 0;
   analogReference(INTERNAL);
   Serial.begin(9600);
   pinMode(LED_pin, OUTPUT);
   pinMode(RELAY_pin, OUTPUT);
   digitalWrite(RELAY_pin,LOW);
   hot = 0;
}

/// the loop routine monitors temperature and sets A/C on-off
void loop() {
   digitalWrite(LED_pin, HIGH);   // turn the LED_PIN on
   delay(300);               // delay for a blink
   sv = analogRead(inLM35);
   digitalWrite(LED_pin, LOW);    // turn the LED_PIN off
   sv2 = analogRead(inAdj);
   sum += sv;
   sum2 += sv2;
   if( (times & 0xf) == 0xf) {
      int iv;
      //fv = (5.0 * sv * 100)/1024.0;

      fv = (sum / 16.0) / 9.31;
      sum = 0;
      iv = (int)(fv*10.0);
      fv = iv / 10.0;
  
      fv2 = (sum2 / 16.0) / 9.31;
      sum2 = 0;
      iv = (int)(fv2*10.0);
      fv2 = iv / 10.0;

      diff = fv - fv2;
    
      if( diff > 0.3 ){
	 digitalWrite(RELAY_pin, HIGH);
	 hot = 1;
      }
       
      if( diff < 0.1 ){
	 digitalWrite(RELAY_pin, LOW);
	 hot = 0;
      }
       
     
      //Serial.print("C1=,");  
      Serial.print(fv); Serial.print(",");
      //Serial.print("C2=,");  
      Serial.print(fv2); Serial.print(",");
      Serial.print(hot); Serial.print(",");

      Serial.println( ++numLines);
   }
   times++;
   delay(800);               // wait for a second
}

