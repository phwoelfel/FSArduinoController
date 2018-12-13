#include <Joystick.h>
#include <Keypad.h>

#define JOYSTICK_COUNT 2

Joystick_ Joystick[JOYSTICK_COUNT] = {
  Joystick_(0x07, JOYSTICK_TYPE_GAMEPAD, 26, 0, true, true, false, true, true, false, false, false, false, false, false), // Traktor + 2x2 Kippschalter + 2 Joysticks + 6 Buttons
  Joystick_(0x08, JOYSTICK_TYPE_GAMEPAD, 30, 0, true, true, false, true, true, false, false, false, false, false, false) // 20 LED Buttons + 2 Kippschalter + 2 Joysticks + 6 Buttons
};

const byte K1ROWS = 6;
const byte K1COLS = 6;
//define the cymbols on the buttons of the keypads
char k1Keys[K1ROWS][K1COLS] = {
  {'0','1','2','3','4','a'},
  {'5','6','7','8','9','b'},
  {':',';','<','=','>','c'},
  {'?','@','A','B','C','d'},
  {'e','f','g','H','I','J'},
  {'h','i','j','K','L','M'}
};
byte k1RowPins[K1ROWS] = {43, 45, 47, 49, 51, 53}; //connect to the row pinouts of the keypad
byte k1ColPins[K1COLS] = {52, 50, 48, 46, 44, 42}; //connect to the column pinouts of the keypad

Keypad keypad1 = Keypad( makeKeymap(k1Keys), k1RowPins, k1ColPins, K1ROWS, K1COLS); 


const byte K2ROWS = 4;
const byte K2COLS = 4;
//define the cymbols on the buttons of the keypads
char k2Keys[K2ROWS][K2COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9',':',';'},
  {'<','=','>','?'}
};
byte k2ColPins[K2COLS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte k2RowPins[K2ROWS] = {22, 24, 26, 28}; //connect to the column pinouts of the keypad

Keypad keypad2 = Keypad( makeKeymap(k2Keys), k2RowPins, k2ColPins, K2ROWS, K2COLS); 


void setup() {
  // setup digital pins
  // kippschalter
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  // joystick press
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);

  keypad1.addEventListener(keypad1Event);
  keypad2.addEventListener(keypad2Event);
  
  //setup joystick
  for (int index = 0; index < JOYSTICK_COUNT; index++)
  {
    Joystick[index].begin();
  }
  
  //SerialUSB.begin(0);
  //while(!SerialUSB);

}

void loop() {
  // Kippschalter
  Joystick[0].setButton(14, !digitalRead(31));
  Joystick[0].setButton(15, !digitalRead(30));
  Joystick[0].setButton(16, !digitalRead(33));
  Joystick[0].setButton(17, !digitalRead(32));
  Joystick[1].setButton(20, !digitalRead(35));
  Joystick[1].setButton(21, !digitalRead(34));
  
  // Joysticks buttons
  Joystick[0].setButton(18, !digitalRead(39));
  Joystick[0].setButton(19, !digitalRead(38));
  Joystick[1].setButton(22, !digitalRead(37));
  Joystick[1].setButton(23, !digitalRead(36));

  // right joysticks
  Joystick[1].setXAxis(1023-analogRead(3));
  Joystick[1].setYAxis(1023-analogRead(2));
  Joystick[1].setRxAxis(1023-analogRead(1));
  Joystick[1].setRyAxis(1023-analogRead(0));

  // left joysticks
  Joystick[0].setXAxis(1023-analogRead(7));
  Joystick[0].setYAxis(1023-analogRead(6));
  Joystick[0].setRxAxis(1023-analogRead(5));
  Joystick[0].setRyAxis(1023-analogRead(4));

  char key2 = keypad2.getKey();
  char key = keypad1.getKey();
  
  // a brief delay, so this runs 20 times per second
  delay(50);

}

void keypad2Event(KeypadEvent key){
  int joyButton = key-'0'; // substract ascii char 0 from input to get values from 0 to 29 for the buttons
  //SerialUSB.print("key2 input: ");
  //SerialUSB.println(key);
  //SerialUSB.print("joy2 button: ");
  //SerialUSB.println(joyButton);
  
  switch (keypad2.getState()){
    case PRESSED:
      //SerialUSB.println("PRESSED");
      Joystick[0].pressButton(joyButton);
      break;
    
    case RELEASED:
      //SerialUSB.println("RELEASED");
      Joystick[0].releaseButton(joyButton);
      break;
    
    case HOLD:
      //SerialUSB.println("HOLD");
      Joystick[0].pressButton(joyButton);
      break;
  }
}

void keypad1Event(KeypadEvent key){
  int joyButton = key-'0'; // substract ascii char 0 from input to get values from 0 to 29 for the buttons
  //SerialUSB.print("key1 input: ");
  //SerialUSB.println(key);
  //SerialUSB.print("joy1 button: ");
  //SerialUSB.println(joyButton);


  if(key == 'e' || key == 'f' || key == 'g' || key == 'h' || key == 'i' || key == 'j'){
    if(key == 'e'){
      joyButton = 20;
    }
    if(key == 'f'){
      joyButton = 21;
    }
    if(key == 'g'){
      joyButton = 22;
    }
    if(key == 'h'){
      joyButton = 23;
    }
    if(key == 'i'){
      joyButton = 24;
    }
    if(key == 'j'){
      joyButton = 25;
    }
    // some buttons are joystick 1
    switch (keypad1.getState()){
      case PRESSED:
        //SerialUSB.println("PRESSED");
        Joystick[0].pressButton(joyButton);
        break;
      
      case RELEASED:
        //SerialUSB.println("RELEASED");
        Joystick[0].releaseButton(joyButton);
        break;
      
      case HOLD:
        //SerialUSB.println("HOLD");
        Joystick[0].pressButton(joyButton);
        break;
    }
  }
  else{
    // most buttons are joystick 2
    switch (keypad1.getState()){
      case PRESSED:
        //SerialUSB.println("PRESSED");
        Joystick[1].pressButton(joyButton);
        break;
      
      case RELEASED:
        //SerialUSB.println("RELEASED");
        Joystick[1].releaseButton(joyButton);
        break;
      
      case HOLD:
        //SerialUSB.println("HOLD");
        Joystick[1].pressButton(joyButton);
        break;
    }
  }
}
