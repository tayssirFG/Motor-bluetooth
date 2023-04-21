#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int received;       // received value will be stored in this variable
char receivedChar;  // received value will be stored as CHAR in this variable   //****FIRST YOU HAVE TO DOWNLOAD SERIAL BLUETOOTH TERMINAL IN YOUR PHONE ***
const char turnON = 'ON';
const char turnOFF = 'OFF';
const char turnOninv = '0';
const int LEDpin = 25;
int in1 = 11;
int in2 = 12;
int in3 = 14;
int in4 = 32;
int ENA = 36;
int ENB = 13;


void setup() {
  Serial.begin(115200);         //serial monitor
  SerialBT.begin("bluetooth");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON  forward direction send : ON");  //print on serial monitor
  Serial.println("To turn OFF stop motor send: OFF");          // //    ///   ///   ///
  Serial.println("To turn ON reverse direction send: 0");    //   /// /// /// /// //
  Serial.println("hi");
  pinMode(LEDpin, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(in1, OUTPUT);  //defined direction  of pins
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  receivedChar = (char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {

    SerialBT.print("Received:");     // write on BT app
    SerialBT.println(receivedChar);  // write on BT app
    Serial.print("Received:");       //print on serial monitor
    Serial.println(receivedChar);    //print on serial monitor
    SerialBT.println(receivedChar);//print on the app
    SerialBT.write(receivedChar); //print on serial monitor
    if (receivedChar == turnON)

    {
      sens1();                      //Function of forward direction mototr  in the void sens1()
      SerialBT.println("LED ON:");  // write on BT app
      Serial.println("LED ON:");    //write on serial monitor
      digitalWrite(LEDpin, HIGH);   // turn the LED ON
    }
    if (receivedChar == turnOFF) {
      sens2();                       //Function of stop motor  in the void sens2()
      SerialBT.println("LED OFF:");  // write on BT app
      Serial.println("LED OFF:");    //write on serial monitor
      digitalWrite(LEDpin, LOW);     // turn the LED off
    }
    if (receivedChar == turnOninv) {
      sens3();                      //Function of reverse direction motor  in the void sens3()
      SerialBT.println("LED ON:");  // write on BT app
      Serial.println("LED ON:");    //write on serial monitor
      digitalWrite(LEDpin, HIGH);   // turn the LED ON
    }
  }
  delay(300);
}
void sens1() {
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
  ledcAttachPin(ENA, 204); // this for ESP32 same analogwrite(ENA,204);
  ledcAttachPin(ENB, 204);
}
void sens2() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  ledcAttachPin(ENA, 0);
  ledcAttachPin(ENB, 0);
}
void sens3() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
  ledcAttachPin(ENA, 204);
  ledcAttachPin(ENB, 204);
