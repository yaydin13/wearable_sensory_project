#define FLEX_4 A0 
#define FLEX_6 A1
#define FLEX_10 A2
#define FLEX_14 A3 
#define FLEX_19 A4
#define FLEX_22 A5
// Measure the voltage at 5V and the actual resistance of your
// 56k resistor, and enter them below:
const float VCC = 5.00; // Measured voltage of Ardunio 5V line
const float R_DIV = 56000.0; 

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE[6] = {11318.45,10925.24,12526.31,10925.24,11003.51,12038.01}; // resistance when straight
const float BEND_RESISTANCE[6] = {21731.35,18984.29,24460.67,18303.50,20485.98,25011.17}; // resistance at 90 deg
float f0_reading;
float f1_reading;
float f2_reading;
float f3_reading;
float f4_reading;
float f5_reading;
int count=0,loopcount=0;
const int buzzer = 9; 

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_4, INPUT);
  pinMode(FLEX_6, INPUT);
  pinMode(FLEX_10, INPUT);
  pinMode(FLEX_14, INPUT);
  pinMode(FLEX_19, INPUT);
  pinMode(FLEX_22, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  float f0_reading= singleReading(FLEX_4,0);
  float f1_reading= singleReading(FLEX_6,1);
  float f2_reading= singleReading(FLEX_10,2);
  float f3_reading= singleReading(FLEX_14,3);
  float f4_reading= singleReading(FLEX_19,4);
  float f5_reading= singleReading(FLEX_22,5);
  int channel=1;
  if(channel==0){

  Serial.println(String(count)+"-"+String(f0_reading));
  count++;
  Serial.println(String(count)+"-"+String(f1_reading));
  count++;
  Serial.println(String(count)+"-"+String(f2_reading));
  count++;
  Serial.println(String(count)+"-"+String(f3_reading));
  count++;
  Serial.println(String(count)+"-"+String(f4_reading));
  count++;

  Serial.println(String(count)+"-"+String(f5_reading));
  count=0;
}else{
  Serial.println(String(f0_reading)+" "+String(f1_reading)+" "+String(f2_reading)+" "+String(f3_reading)+" "+String(f4_reading)+" "+String(f5_reading)+"\r");
}
  delay(120);
  
if(f5_reading>17){
  tone(buzzer, 1000);
  }else{
  noTone(buzzer); 
  }

}

float singleReading(int pin,int x){
  int flexADC = analogRead(pin);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
   // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE[x], BEND_RESISTANCE[x],
                   0, 90.0);
  if(angle<0){
    angle=0.0;
  }
 //Serial.println("Resistance: " + String(flexR) + " ohms");
 return angle;
  
  }
