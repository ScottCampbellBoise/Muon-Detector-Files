
/**
 * Cosmic Ray Data Sensor Calibration Protocol for Geske Lab, Gonzaga University
 * @Author: Scott Campbell
 * @Version: 1.0 - 22 July 2018
 * 
 * Program to isolate cosmic ray events that pass through two blocks of scintillator stacked verticallly
 * 
 * Compile Settings for Teensy 3.6:
 * 
 * Board = Teensy 3.6
 * USB Type = Serial
 * CPU Speed = 240MHz (Overclock)
 * Optimize = Faster
 * Programmer = AVRISP mkll
 */

#include <ADC.h>

ADC *adc = new ADC();

const int detector_1 = A2; // TOP detector in stack
const int detector_2 = A3; // BOTTOM detector in the stack

double conv; // Conversion factor from analog input to voltage level
double cutoff; // Sets min level to trigger a measurement recording, default 750 mV
const int num_samples = 10; // Sets the number of samples to take when a pulse is detected

int data_points[num_samples]; // Array to store samples from a detected particle
long t = 100000;

int pulse_id = 0;

void setup(){
  pinMode(detector_1,INPUT);
  pinMode(detector_2,INPUT);
  pinMode(12,OUTPUT);

  adc->setReference(ADC_REFERENCE::REF_3V3);//Sets the reference voltage, default REF_3V3
                                            //*If changed you must change the conv variable to match
  adc->setAveraging(1); //Set the number of averages, default 1
  adc->setResolution(12);//Set bits of resoloution, default 12
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED);//Default HIGH_SPEED
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED);//Default HIGH_SPEED
  
  conv = 3.3/4096;
  cutoff = 350; // 350 default for 'ideal' performance
 
  Serial.begin(250000); // Setting serial line speed, default 250000 baud 

  String conv_string=".000805664"; String cutoff_string=cutoff;
  String millis_string = millis();
  String samp_string = num_samples;

  delay(5000); // Wait for the recieving program to be initilized...

  Serial.println("Opening Parameters:");
  Serial.println("Time (millis): "+millis_string);
  Serial.println("Analog Reference Voltage: 3.3V");
  Serial.println("Analog Averaging: 1 Average/Read");
  Serial.println("Analog Conversion Speed: High Speed");
  Serial.println("Analog Sampling Speed: High Speed");
  Serial.println("Conversion Factor: "+conv_string);
  Serial.println("Cutoff Level: "+cutoff_string);
  Serial.println("Samples per Collection: "+samp_string);
  Serial.println("Cosmic Ray Isolation");
  
  Serial.println("\n\n\n");
}

void loop() {
  while(true)
  {
    if(adc->analogRead(detector_1) > cutoff)
    {
      if(adc->analogRead(detector_2) > cutoff)
      {  
        
        for(int i=0; i<num_samples; i++)
        {
          data_points[i] = adc->analogRead(detector_1); // sample the top detector
        }
        if(adc->analogRead(detector_2) > 2*cutoff/3){ // make sure that there really is a coincidence event happening...
          PORTB |= (1<<4);
          String time_string = t;
          String id_string = pulse_id; pulse_id++;
          
          Serial.println("Pulse ID: "+id_string);
          Serial.println("Time (millis): "+time_string);
          for(int i=0;i<num_samples;i++){
            if(i==0)
            {
              Serial.print("{");
            }
            Serial.print(data_points[i]);
            Serial.print(",");
          }
          Serial.print("}");
          Serial.println("\n\n");
  
          delay(20); // wait until the particle has completely passed... 20ms default
          PORTB &= ~(1<<4);
        }
      }  
    }
    adc->printError(); // Print any errors that there may be in reading the input
    }
}

