#include <Arduino.h>
#define CH_A 4
#define CH_C 10

#define MA1 11
#define MA2 6
#define MB2 3
#define MB1 5

unsigned long pulse_duration_A; 
unsigned long pulse_duration_C;
 
byte PWM_A;
byte PWM_B;

//channel A threshhold values change or modify using trim
const int min_pulse_A = 1131;
const int max_pulse_A = 2030;
const uint16_t mid_pulse_min_A = 1479; //lower bound of deadzone for channel A
const uint16_t mid_pulse_max_A = 1485; //lower bound of deadzone for channel A

//channel C threshhold values change or modify using trim
const int min_pulse_C = 970;
const int max_pulse_C = 1850;
const uint16_t mid_pulse_min_C = 1479; //lower bound of deadzone for channel A
const uint16_t mid_pulse_max_C = 1485; //lower bound of deadzone for channel A

void stop(uint8_t a){
  analogWrite(a, 255);
}

void off(uint8_t a){
  digitalWrite(a, LOW);
}

void forward(uint8_t a, byte b){
  analogWrite(a, b);
}

void backward(uint8_t a, byte b){
  analogWrite(a, b);
}

void setup() {
  pinMode(CH_A, INPUT);
  pinMode(CH_C, INPUT);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pulse_duration_A = pulseIn(CH_A, HIGH);
  pulse_duration_C = pulseIn(CH_C, HIGH);

  //Serial.println(pulse_duration_A);
  //Serial.print("\t");
  //Serial.println(pulse_duration_C);

  // --- Process Channel A (Motor 1) ---
  if (pulse_duration_A >= mid_pulse_min_A && pulse_duration_A <= mid_pulse_max_A){
    PWM_A = 0;
    off(MA1);
    off(MA2);
  }else if (pulse_duration_A < mid_pulse_min_A){
    PWM_A = map(pulse_duration_A, min_pulse_A, mid_pulse_min_A, 255, 0);
    PWM_A = constrain(PWM_A, 0, 255);
    forward(MA1, PWM_A);
    off(MA2);
  }else if (pulse_duration_A > mid_pulse_max_A){
    PWM_A = map(pulse_duration_A, mid_pulse_max_A, max_pulse_A, 0, 255);
    PWM_A = constrain(PWM_A, 0, 255);
    forward(MA2, PWM_A);
    off(MA1);
  }

  // --- Process Channel C (Motor 1) ---
  if (pulse_duration_C >= mid_pulse_min_C && pulse_duration_C <= mid_pulse_max_C){
    PWM_B = 0;
    off(MB1);
    off(MB2);
  }else if (pulse_duration_C < mid_pulse_min_C){
    PWM_B = map(pulse_duration_C, min_pulse_C, mid_pulse_min_C, 255, 0);
    PWM_B = constrain(PWM_B, 0, 255);
    forward(MB1, PWM_B);
    off(MB2);
  }else if (pulse_duration_C > mid_pulse_max_C){
    PWM_B = map(pulse_duration_C, mid_pulse_max_C, max_pulse_C, 0, 255);
    PWM_B = constrain(PWM_B, 0, 255);
    forward(MB2, PWM_B);
    off(MB1);
  }
  Serial.print(PWM_A);
  Serial.print("\t");
  Serial.println(PWM_B);
}