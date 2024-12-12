#include <SimpleKeypad.h> 

const byte nb_rows = 4;               // four rows
const byte nb_cols = 4;               // four columns
char key_chars[nb_rows][nb_cols] = {  // The symbols of the keys
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[nb_rows] = { PA7, PA6, PA5, PA4 };  // The pins where the rows are connected
byte colPins[nb_cols] = { PA3, PA2, PA1, PA0 };  // The pins where the columns are connected

//byte rowPins[nb_rows] = { PA6, PA5, PA4, PA3 };  // The pins where the rows are connected
//byte colPins[nb_cols] = { PA2, PA1, PA0, PC15 };  // The pins where the columns are connected

//другой вариант подключения
// byte rowPins[nb_rows] = {PB9, PB8, PB7, PB6};           // The pins where the rows are connected
// byte colPins[nb_cols] = {PB5, PB4, PB3, PA15};           // The pins where the columns are connected

SimpleKeypad kp1((char*)key_chars, rowPins, colPins, nb_rows, nb_cols);  // New keypad called kp1

#include <USBComposite.h>
USBHID HID;
HIDKeyboard Keyboard(HID);
USBCompositeSerial CompositeSerial;


void setup() {
  HID.begin(CompositeSerial, HID_KEYBOARD);
  while (!USBComposite)
    ;
  Keyboard.begin();
}

void loop() {
  String buf;
  char key = kp1.getKey();  // The getKey function scans the keypad every 10 ms and returns a key only one time, when you start pressing it
  if (key) {                // If getKey returned any key
    switch (key) {
      case '*':
        buf = "*";
        Keyboard.println(buf);
        //CompositeSerial.println(buf);s
        break;
      case '#':
        buf = "#";
        Keyboard.println(buf);
        //CompositeSerial.println(buf);s
        break;
      case '0':
        buf = "0";
        Keyboard.println(buf);
        break;
      case 'A':
        buf = "A";
        Keyboard.println(buf);
        break;
      case 'B':
        buf = "B";
        Keyboard.println(buf);
        break;
      case 'C':
        buf = "C";
        Keyboard.println(buf);
        break;
      case 'D':
        buf = "D";
        Keyboard.println(buf);
        break;
      case '1':
        buf = "1";
        Keyboard.println(buf);
        break;
      case '2':
        buf = "2";
        Keyboard.println(buf);
        break;
      case '3':
        buf = "3";
        Keyboard.println(buf);
        break;
      case '4':
        buf = "4";
        Keyboard.println(buf);
        break;
      case '5':
        buf = "5";
        Keyboard.println(buf);
        break;
      case '6':
        buf = "6";
        Keyboard.println(buf);
        break;
      case '7':
        buf = "7";
        Keyboard.println(buf);
        break;
      case '8':
        buf = "8";
        Keyboard.println(buf);
        break;
      case '9':
        buf = "9";
        Keyboard.println(buf);
        break;
    }
  }
}

void Copy() {
  Keyboard.press(KEY_LEFT_CTRL);  // Press Ctrl
  Keyboard.press('c');            // Press C
  Keyboard.releaseAll();          // Release all keys
}

void Paste() {
  Keyboard.press(KEY_LEFT_CTRL);  // Press Ctrl
  Keyboard.press('v');            // Press V
  Keyboard.releaseAll();          // Release all keys
}

void PrintText(String txt) {
  Keyboard.print(txt);
}

void SwitchLayout() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.releaseAll();
}