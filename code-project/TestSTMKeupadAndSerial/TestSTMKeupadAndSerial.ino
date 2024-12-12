#include <USBComposite.h>
#include <SimpleKeypad.h>

// Пины и клавиатура
const byte nb_rows = 4;               
const byte nb_cols = 4;               
char key_chars[nb_rows][nb_cols] = {  
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[nb_rows] = { PA7, PA6, PA5, PA4 };
byte colPins[nb_cols] = { PA3, PA2, PA1, PA0 };
SimpleKeypad kp1((char*)key_chars, rowPins, colPins, nb_rows, nb_cols);

USBHID HID;
HIDKeyboard Keyboard(HID);
USBCompositeSerial CompositeSerial;

// 0 - английская, 1 - русская
int currentLayout = 0;   // Считаем что начали с английской
int desiredLayout = 0;   // Желаемая раскладка, получаемая по COM

void setup() {
  HID.begin(CompositeSerial, HID_KEYBOARD);
  
  while (!USBComposite);
  
  Keyboard.begin();
  CompositeSerial.println("Device ready: HID + Serial");
  CompositeSerial.println("Send '0' for English, '1' for Russian layout (switch occurs on next key press)");
}

void loop() {
  // Читаем данные от COM-порта, чтобы обновить desiredLayout
  while (CompositeSerial.available()) {
    char c = CompositeSerial.read();
    if (c == '0') {
      desiredLayout = 0;
      CompositeSerial.println("Next key press will switch to English if needed.");
    } else if (c == '1') {
      desiredLayout = 1;
      CompositeSerial.println("Next key press will switch to Russian if needed.");
    }
  }

  // Читаем клавишу с клавиатуры
  char key = kp1.getKey();
  if (key) {
    // Перед печатью проверяем, не надо ли переключить раскладку
    if (desiredLayout != currentLayout/*тут нужно определить, какие символы (рус\англ) содержит то, что нам необходимо ввести, и переключится на необходжимую раскладку*/) {
      // Переключаемся
      SwitchLayout();
      currentLayout = desiredLayout; 
      CompositeSerial.println("Layout switched before printing key.");
    }
    
    // Теперь печатаем
    Keyboard.print(key);
    CompositeSerial.print("Key pressed: ");
    CompositeSerial.println(key);
  }
}

void Copy() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('c');
  Keyboard.releaseAll();
}

void Paste() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('v');
  Keyboard.releaseAll();
}

void SwitchLayout() {
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.releaseAll();
}
