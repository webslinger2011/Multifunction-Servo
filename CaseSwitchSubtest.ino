/*Switch case example using 6 Push Buttons
 *by Webslinger2011
 *Use LCD Library from Frank de Brabander
 *Multiple Servo Control
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x3F,16, 2);//Set LCD i2C address and lcd size
Servo sg90;

//Toggles the main menu
int Setvariable=0;
int Upbutton = 5;
int Downbutton = 6;

//Toggles the sub menu with fixed servo angle
int Setvariable2;
int SelectUp = 2;
int SelectDown = 4;


//Controls the Servo in Manual Mode
int Setservoangle = 0;
int Upservo = 7;
int Downservo = 8;

const unsigned long Interval = 1000;
unsigned long previousTime = 0;

const unsigned long Interval2 = 1000;
unsigned long previousTime2 = 0;

void setup() {
  Serial.begin(9600);
  sg90.attach(3);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);  //Set LCD cursor to upper left corner: column 0, row 0
  lcd.print("Webslinger2011");  //Print my message
  pinMode(Upbutton,INPUT_PULLUP);
  pinMode(Downbutton,INPUT_PULLUP);
  pinMode(SelectUp,INPUT_PULLUP);
  pinMode(SelectDown,INPUT_PULLUP);
  pinMode(Upservo,INPUT_PULLUP);
  pinMode(Downservo,INPUT_PULLUP);  
  lcd.clear();
  delay(2000);
}
void loop() {
  unsigned long currentTime = millis();//Start the time 
  unsigned long currentTime2 = millis();//Start the time 
  Serial.println(Setvariable);
  digitalRead(Upbutton);
  digitalRead(Downbutton);
  digitalRead(SelectUp);
  digitalRead(SelectDown);
  digitalRead(Upservo);
  digitalRead(Downservo);

  if (currentTime - previousTime >= Interval) {//Reads everytime the set Interval is reached
    if (digitalRead(Upbutton) == 0) Setvariable = Setvariable+1; //Setvariable++ (increments the variable)
        if (Setvariable>3) Setvariable = 3;//Counting 4 variables (start from 0 to 3)
    if (digitalRead(Downbutton) == 0) Setvariable = Setvariable-1; // Setvariable-- (decrements the variable)
        if (Setvariable<0) Setvariable = 0; 
      previousTime = currentTime;
      }
      
  if (Setvariable == 0){
    Serial.println("Motor Control 1.1");
    lcd.setCursor(0,0);
    lcd.print("Motor Contrl 1.1");         
    lcd.setCursor(0,1);
    lcd.print("Manual Mode     ");
    if (digitalRead(Upservo) == 0) Setservoangle = Setservoangle+2; //Setvariable++
        if (Setservoangle > 170)Setservoangle = 170; //Set maximum angle
    if (digitalRead(Downservo) == 0) Setservoangle = Setservoangle-2; // Setvariable--
        if (Setservoangle < 30)Setservoangle = 30; //Set minimum angle
    sg90.write(Setservoangle);    
    }
  
  if (Setvariable == 1){
    Serial.println("Motor Control 1.2");
    lcd.setCursor(0,0);
    lcd.print("Motor Contrl 1.2");
    lcd.setCursor(0,1);
    lcd.print("Sweep Mode      ");
    for(Setservoangle=10; Setservoangle<=165; Setservoangle+=1){ //Increment servo angle by 1 degree
    sg90.write(Setservoangle);
    delay(25);}
    for(Setservoangle=165; Setservoangle<=10; Setservoangle-=1){ //Decrement servo angle by 1 degree
    sg90.write(Setservoangle);
    delay(25);}
    }
  
  if (Setvariable == 2){
    Serial.println("Motor Control 1.3");
    lcd.setCursor(0,0);
    lcd.print("Motor Contrl 1.3");
    lcd.setCursor(0,1);
    lcd.print("90/0/180");
    lcd.print("Degrees");

    sg90.writeMicroseconds(1500);// Position servo to 90 degrees
    delay(1000);
    sg90.writeMicroseconds(1000);// Switch ON servo for 1 microsecond
    delay(1000);
    sg90.writeMicroseconds(2000); // 180 degrees is about 2 microseconds
    delay(1000);
    }
  if (Setvariable == 3){
    if (currentTime2 - previousTime2 >= Interval2) {//Reads everytime the set Interval is reached
    if (digitalRead(SelectUp) == 0) Setvariable2 = Setvariable2+1; //Setvariable++ (increments the variable)
        if (Setvariable2>2) Setvariable2 = 2;//Always start count from 0 (3 variables)
    if (digitalRead(SelectDown) == 0) Setvariable2 = Setvariable2-1; // Setvariable-- (decrements the variable)
        if (Setvariable2<0) Setvariable2 = 0;     
    previousTime2 = currentTime2;
      }
    switch (Setvariable2){
            
      case 0:
              Serial.println("Sub 1");
              lcd.setCursor(0,0);
              lcd.print("Position 1      ");
              lcd.setCursor(0,1);
              lcd.print("Servo: ");
              lcd.print("20 deg  ");
              sg90.write(20);// Set servo at 0 degrees
              break; 
      case 1:
              Serial.println("Sub 2");
              lcd.setCursor(0,0);
              lcd.print("Position 2      ");
              lcd.setCursor(0,1);
              lcd.print("Servo: ");
              lcd.print("90 deg");
              sg90.write(90);// Set servo at 90 degrees
              break; 
      default:
              Serial.println("Sub 3");
              lcd.setCursor(0,0);
              lcd.print("Position 3      ");
              lcd.setCursor(0,1);
              lcd.print("Servo: ");
              lcd.print("170 deg");
              sg90.write(170);// Set servo at 170 degrees
              break; 
              }  
     }
}
