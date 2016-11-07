#define P25 D7
#define P10 D6

#define SAMPLELENGTH 30000 // 30seg

unsigned long sampleTime = 0;

volatile unsigned long p25Time = 0;
volatile unsigned long p25Duration = 0;
volatile unsigned long p25LowLength = 0;

volatile unsigned long p10Time = 0;
volatile unsigned long p10Duration = 0;
volatile unsigned long p10LowLength = 0;

void setup() {
  Serial.begin(115200);
  pinMode(P25,INPUT);
  pinMode(P10,INPUT);
  attachInterrupt(digitalPinToInterrupt(P25), P25Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(P10), P10Change, CHANGE);
  sampleTime = millis();
}

void P25Change(){
  unsigned long ms = micros();
  if(digitalRead(P25)==HIGH){
    p25Duration = ms - p25Time;
    p25LowLength += p25Duration;
  }else{
    p25Time = ms;
  }
}
void P10Change(){
  unsigned long ms = micros();
  if(digitalRead(P10)==HIGH){
    p10Duration = ms - p10Time;
    p10LowLength += p10Duration;
  }else{
    p10Time = ms;
  }
}

void loop() {
  unsigned long sampleLength = millis()-sampleTime;
  if (sampleLength > SAMPLELENGTH){    
    Serial.print("P25 concentration: ");
    Serial.print(calcConcentration(sampleLength,p25LowLength));
    Serial.println(" pcs/0.01cf");
    p25LowLength = 0;

    Serial.print("P10 concentration: ");
    Serial.print(calcConcentration(sampleLength,p10LowLength));
    Serial.println(" pcs/0.01cf");
    p10LowLength = 0;

    sampleTime = millis();
  }
}

// untested blackmagic from spec
float calcConcentration(unsigned long sampleLength, unsigned long lowLength){
  float ratio = lowLength/(sampleLength*10.0);
  return 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
}
