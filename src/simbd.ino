#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <max6675.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);  // Set the LCD address to 0x20 for a 16x2 display

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;

// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0;

// Float for Reference Voltage
float ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;

// Variables for Measured Voltage and Calculated Current
double Vout = 0;
double Current = 0;

const double scale_factor = 0.066;  // for 30A current sensor

const double vRef = 5.00;
const double resConvert = 1024;
double resADC = vRef / resConvert;
double zeroPoint = vRef / 2;

// Thermocouple connections
const int thermo1SO = 4;
const int thermo1CS = 6;
const int thermo1CLK = 5;

const int thermo2SO = 7;
const int thermo2CS = 9;
const int thermo2CLK = 8;

MAX6675 thermocouple1(thermo1CLK, thermo1CS, thermo1SO);
MAX6675 thermocouple2(thermo2CLK, thermo2CS, thermo2SO);
//thermister
int THERMISTORPIN = A2,  BCOEFFICIENT = 3380 ;
float THERMISTORNOMINAL = 10000 , TEMPERATURENOMINAL = 25 , SERIESRESISTOR = 10000    ;
int sample[5];

// Declare variables to store the time values
unsigned long t1, t2, dt;
void setup() {
  lcd.init();                      // Initialize the LCD
  lcd.backlight();
  lcd.clear();
  lcd.print("<<----BMS---->>");
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("Smart Battery");
   lcd.setCursor(0, 1);
    lcd.print("Module Design");
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
 
  // Read the Analog Input
  adc_value = analogRead(A0);

  // Determine voltage at ADC input
  adc_voltage = (adc_value * ref_voltage) / 1024.0;

  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2));

  // Display Voltage on LCD
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V: ");
  lcd.print(in_voltage, 3);
  lcd.print("V");

  // Vout is read 1000 Times for precision
  for (int i = 0; i < 1000; i++) {
    Vout = (Vout + (resADC * analogRead(A1)));
    delay(1);
  }

  // Get Vout in mV
  Vout = Vout / 1000;

  // Convert Vout into Current using Scale Factor
  Current = (Vout - zeroPoint) / scale_factor;

  // Display Current on LCD
  lcd.setCursor(0, 1);
  t1 = millis();//time befor current measurement
  if(Current>0.00){
  lcd.print("I: ");
  lcd.print(Current, 3);
  lcd.print("A");
  delay(1000);   }
  // Get the second time value after current measurement
  t2 = millis();
  // Calculate the time difference in seconds
  dt = (t2 - t1) / 1000.0;
//


  // Multiply voltage and current to get power
  float power = in_voltage * Current;

  // Display Power on LCD
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  if(power>0.00){
  lcd.print("P: ");
  lcd.print(power, 2);
  lcd.print("W");
  }
  // Energy of 2X series cell pack(each of 3.7V,1500mah)
  //float Energy = (in_voltage *1.5)/1000;
  float Energy = (in_voltage *Current*dt);
  // Display Energy on LCD
  //delay(2000);
  lcd.setCursor(0, 1);
  if(Energy>0.00){
  lcd.print("E: ");
  lcd.print(Energy, 3);
  lcd.print("kWh");
  }
  delay(1000);


  //......................................................................................................................
  // Get a reading from the temperature sensor lm35:
  int reading = analogRead(A3);

  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);

  // Convert the voltage into the temperature in degree Celsius:
  float temperature = voltage / 10;
  // Display Temperature on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T_Pack_lm35:");
  lcd.print(temperature);
  lcd.print("C");

 //delay(1000);  // Adjust this delay

  // Read temperatures from thermocouples
  float temp1 = thermocouple1.readCelsius();
  float temp2 = thermocouple2.readCelsius();

  // Calculate temperature discrepancy
  float tempDiscrepancy = 2*abs(temp1 - temp2);

  // Display Temperature Discrepancy on LCD
  lcd.setCursor(0, 1);
  lcd.print("T_Disc: ");
  lcd.print(tempDiscrepancy);
  lcd.print(" C");

  delay(1000);
 //temp by thermistor
  int i;
  float average;
 
  // take N samples in a row, with a slight delay
  for (i=0; i< 5; i++) {
   sample[i] = analogRead(THERMISTORPIN);
   delay(10);
  }

  // average all the samples out
  average = 0;
  
  for (i=0; i< 5; i++) {
     average += sample[i];
     
  }
  average /= 5;
   // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
 
 
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= (273.15+1);                         // convert to C
  lcd.clear();
  lcd.print("T_Packntc= ");
  lcd.print((int)steinhart);   
  lcd.print(" C"); 

  delay(1500);            
  lcd.clear();


 
}

