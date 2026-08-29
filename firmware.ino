/*
  ============================================
  Digital Voltmeter - Official Firmware v1.0
  ============================================

  Target chip: ATmega328P-P (bare chip, 16MHz external crystal,
  programmed via ISP through J1)

  Function: Reads a 0-20V DC input through a resistor divider
  on ADC0, and displays the measured voltage on a 16x2 LCD.

  --------------------------------------------
  HARDWARE PIN MAPPING (matches the schematic)
  --------------------------------------------
  ATmega pin | Arduino name | Function
  -----------|--------------|------------------
  Pin 4      | D2 (PD2)     | LCD RS
  Pin 5      | D3 (PD3)     | LCD E
  Pin 6      | D4 (PD4)     | LCD DB4
  Pin 11     | D5 (PD5)     | LCD DB5
  Pin 12     | D6 (PD6)     | LCD DB6
  Pin 13     | D7 (PD7)     | LCD DB7
  Pin 23     | A0 (PC0)     | ADC input (from R3/R4 divider)

  --------------------------------------------
  VOLTAGE DIVIDER
  --------------------------------------------
  R3 = 30k (top, from probe input)
  R4 = 10k (bottom, to GND)
  Scales 0-20V input down to 0-5V at the ADC pin.
  Ratio to undo in software = (R3+R4)/R4 = 4.0

  --------------------------------------------
  BEFORE FIRST REAL USE
  --------------------------------------------
  1. Burn the bootloader onto U1 via J1 (if not already done),
     using an Arduino-as-ISP or USBasp programmer, board setting
     "Arduino Uno" (same chip/fuses/16MHz crystal).
  2. Upload this sketch through the same ISP connection.
  3. Calibrate: apply a known, accurate voltage (measured with a
     trusted multimeter) to the probes, and adjust
     CALIBRATION_FACTOR below until the LCD matches that reading.
     Re-upload after changing it.
*/

#include <LiquidCrystal.h>

// ---------------- Pin setup ----------------
const int PIN_RS = 2;
const int PIN_EN = 3;
const int PIN_D4 = 4;
const int PIN_D5 = 5;
const int PIN_D6 = 6;
const int PIN_D7 = 7;

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_D4, PIN_D5, PIN_D6, PIN_D7);

const int ADC_PIN = A0;

// ---------------- Circuit constants ----------------
const float VREF = 5.0;             // ADC reference voltage (AVCC/AREF)
const int   ADC_MAX = 1023;         // 10-bit ADC resolution
const float DIVIDER_RATIO = 4.0;    // (R3 + R4) / R4 = (30k + 10k) / 10k

// ---------------- Calibration ----------------
// Set this after testing against a known-accurate voltage source.
// Formula: CALIBRATION_FACTOR = actual / displayed
float CALIBRATION_FACTOR = 1.0;

// ---------------- Sampling ----------------
const int   NUM_SAMPLES     = 30;   // averaged per reading, reduces noise/jitter
const int   SAMPLE_DELAY_MS = 2;    // small delay between samples
const int   UPDATE_DELAY_MS = 250;  // how often the display refreshes

// ---------------- Safety display ----------------
const float OVER_RANGE_VOLTS = 20.5; // slightly above rated 20V max

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digital");
  lcd.setCursor(0, 1);
  lcd.print("Voltmeter v1.0");
  delay(1500);
  lcd.clear();
}

void loop() {
  float vIn = readVoltage();

  lcd.setCursor(0, 0);
  lcd.print("Voltage:");

  lcd.setCursor(0, 1);
  if (vIn > OVER_RANGE_VOLTS) {
    lcd.print("OVER RANGE!   ");
  } else {
    lcd.print(vIn, 2);
    lcd.print(" V");
    lcd.print("      "); // clears leftover digits from a previous longer reading
  }

  delay(UPDATE_DELAY_MS);
}

// Reads and averages the ADC, then converts to the real input voltage
float readVoltage() {
  long sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += analogRead(ADC_PIN);
    delay(SAMPLE_DELAY_MS);
  }
  float rawAverage = sum / (float)NUM_SAMPLES;

  float vAtPin = (rawAverage / (float)ADC_MAX) * VREF;
  float vIn = vAtPin * DIVIDER_RATIO * CALIBRATION_FACTOR;

  return vIn;
}
