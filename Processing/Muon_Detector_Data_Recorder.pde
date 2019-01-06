/**
*  @Author: Scott Campbell
*  @Version: 1.1, August 2, 2018
*  
*  This program connects to the Teensy 3.6 microcontroller over a usb serial connection,
*  and writes all incoming information to a txt file. Must be run within 5 seconds after 
*  starting the Teensy 3.6 microcontroller for all data and information to be preserved.
*  To exit out of the program, press any key while the runtime window is selected.
*/

import processing.serial.*;
Serial mySerial;
PrintWriter output;

boolean time_set = false;
long open_time = -1;

int open_hour;
int open_minute;
int open_second;
int open_millis;
int open_day;
int open_month;
int open_year;

void setup() {
   mySerial = new Serial( this,"/dev/cu.usbmodem3318111", 250000 ); // CHANGE to the Serial connection your Teensy is using. Can be found on the Arduino IDE
   output = createWriter( "/myData.txt" ); // CHANGE to the location where you want your data to be stored...
    
    String date = day()+"/"+month()+"/"+year();
    String time = hour()+"/"+minute()+"/"+second()+"/"+millis();
    output.println("DATE<"+date+">");
    output.println("TIME<"+time+">\n");
    
}
void draw() {
    if (mySerial.available() > 0 ) {
         String value = mySerial.readString();
         if ( value != null ) {
             //if(!time_set){setTime(value);}
             //String time_stamp = getTimeStamp(value);
             output.println(value);
         }
    }
}

void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    exit();  // Stops the program
}

String getTimeStamp(String value){
  int pos_1 = value.indexOf("Time (millis): ");
  int pos_2 = value.indexOf("{");
  String time_stamp = "";
  try{
     long meas_time = Integer.parseInt(value.substring(pos_1,pos_2));
     long elapsed_time = meas_time - open_time;
     
     int elapsed_days = 0;
     while(elapsed_time >= 86400000){elapsed_days++; elapsed_time-=86400000;}
     int elapsed_hours = 0;
     while(elapsed_time >= 3600000){elapsed_hours++; elapsed_time-=3600000;}
     int elapsed_minutes = 0;
     while(elapsed_time >= 60000){elapsed_minutes++; elapsed_time-=60000;}
     int elapsed_seconds = 0;
     while(elapsed_time >= 1000){elapsed_seconds++; elapsed_time-=1000;}
     int elapsed_millis = (int)elapsed_time;
     time_stamp += (open_day+elapsed_days)+"/"+(open_month)+"/"+(open_year);
     time_stamp += ", "+(open_hour+elapsed_hours)+"/"+(open_minute+elapsed_minutes)+"/";
     time_stamp += (open_second+elapsed_seconds)+"/"+(elapsed_millis);
     return time_stamp;
  }catch(Exception e){return "TIME NOT SET...";}
} 

void setTime(String value){
  int pos_1 = value.indexOf("Time (millis): ");
  int pos_2 = value.indexOf("{");
  try{
     open_time = Integer.parseInt(value.substring(pos_1,pos_2).trim());
     open_millis = millis();
     open_second = second();
     open_minute = minute();
     open_hour = hour();
     open_day = day();
     open_month = month();
     open_year = year();
     time_set = true;
  }catch(Exception e){output.println("error setting time...");}
}