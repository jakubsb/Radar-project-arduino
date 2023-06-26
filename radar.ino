#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define LED_GREEN 2
#define LED_RED 3
#define PIN_TRIG 11
#define PIN_ECHO 12

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);
long duration;
long distance;


void setup() {
  myservo.attach(13);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  lcd.begin();
  lcd.backlight();
  lcd.clear();

}

void loop() {
  for(int i=0;i<=180;i++){
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);      
    myservo.write(i);
    delay(30);
    distance = calculateDistance();
    lcd.setCursor(0, 0);
    lcd.print("angle: ");
    lcd.print(i);
    lcd.print(char(223));  // znak stopni
    lcd.setCursor(0, 1);
    lcd.print("distance: ");
    lcd.print(distance);
    lcd.setCursor(14, 1);
    lcd.print("cm");
    delay(200);
    lcd.setCursor(8, 0);  //
    lcd.print("   ");     // zamiast lcd.clear()
    lcd.setCursor(11, 1); // angle:, distance: i cm zostają na wyświetlaczu
    lcd.print("   ");     //
    delay(10);
  }

  for(int i=180;i>=0;i--){  
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    myservo.write(i);
    delay(30);
    distance = calculateDistance();
    lcd.setCursor(0, 0);
    lcd.print("angle: ");
    lcd.print(i);
    lcd.print(char(223));  // znak stopni
    lcd.setCursor(0, 1);
    lcd.print("distance: ");
    lcd.print(distance);
    lcd.setCursor(14, 1);
    lcd.print("cm");
    delay(200);
    lcd.setCursor(8, 0);  //
    lcd.print("   ");     // zamiast lcd.clear()
    lcd.setCursor(11, 1); // angle:, distance: i cm zostają na wyświetlaczu
    lcd.print("   ");     //
    delay(10);
  }
}

int calculateDistance(){
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH); 
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);
  distance = (duration*0.0343)/2;

if (distance == 0){
  while (distance == 0){
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, HIGH); 
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    duration = pulseIn(PIN_ECHO, HIGH);
    distance = (duration*0.0343)/2; 
  }
  }
  else{

    if (distance < 50){
      digitalWrite(LED_RED, HIGH);
      delay(30);
    }
    else{
      digitalWrite(LED_GREEN, HIGH);
      delay(30);
    }
  }
  
  return distance;  
}
