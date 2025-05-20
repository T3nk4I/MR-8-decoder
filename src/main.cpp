#include <Arduino.h>
#define CH_A 6
#define CH_B 7

unsigned long pulse_duration_A; //min 1090 max 1950
unsigned long pulse_duration_B;

const int min_pulse_A = 1090;
const int max_pulse_A = 1950;
const int min_pulse_B = 1090;
const int max_pulse_B = 1950;

void setup() {
  pinMode(CH_A, INPUT);
  pinMode(CH_B, INPUT);
  Serial.begin(9600);
}

void loop() {
  pulse_duration_A = pulseIn(CH_A, HIGH);
  pulse_duration_B = pulseIn(CH_B, HIGH);
  byte PWM_A = map(pulse_duration_A, min_pulse_A, max_pulse_A, 0, 255);
  byte PWM_B = map(pulse_duration_B, min_pulse_B, max_pulse_B, 0, 255);
  Serial.print(PWM_A);
  Serial.print("\t");
  Serial.println(PWM_B);
  delay(100);
}
