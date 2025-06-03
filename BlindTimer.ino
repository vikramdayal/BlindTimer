#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define DIP_SWITCH_PIN 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int buttonPin = 2;
int buttonState = HIGH;
int lastButtonState = HIGH;
int elapsed_time=0;
int timer_on = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // milliseconds
unsigned long timerStart = 0;
unsigned long timerStop = 0;
unsigned long elapsedTime = 0;
unsigned long lastClickTime = 0;
int inSleepMode = LOW;
int SleepAfterMillis = 10000;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Enable internal pull-up for switch
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      // Address might be 0x3D as well
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();
  delay(1000);
  Serial.println("Ready");
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      lastClickTime = millis();
      buttonState = reading;
      if (buttonState == HIGH) {
        Serial.print("State Change timer_on: ");
        Serial.println(timer_on, DEC);
        Serial.println(reading, DEC);
        if (inSleepMode == HIGH) {
          inSleepMode = LOW;
          display.ssd1306_command(SSD1306_DISPLAYON);
        }
        else if (timer_on == LOW) {
          timerStart = lastClickTime;
          display.clearDisplay();
          timer_on = HIGH;
        } else {
          timerStop = lastClickTime;
          elapsedTime = (timerStop - timerStart)/1000;
          timer_on = LOW;
        }
      }
    }
  }
  if (inSleepMode == LOW && millis() - lastClickTime > SleepAfterMillis) {
    Serial.println("going to sleep");
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    inSleepMode = HIGH;
  }
  lastButtonState = reading;
  if (inSleepMode == HIGH) {
    return;
  }
  if (timer_on == HIGH) {
    drawRandomPattern();
  }
  else {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(5, 0);
    display.print("Time:");
    display.println(elapsedTime);
    display.println();
    display.println("press button to start timer");
    display.display();    
  }
}

void drawRandomPattern() {
  uint16_t x0 = random(SCREEN_WIDTH);
  uint16_t y0 = random(SCREEN_HEIGHT);
  uint16_t x1 = random(SCREEN_WIDTH);
  uint16_t y1 = random(SCREEN_HEIGHT);
  uint16_t color = random(0, 2) == 0 ? BLACK : WHITE; // Random color (black or white)
  display.drawLine(x0, y0, x1, y1, color); 
  display.display();
  delay(10); // Optional delay between patterns
}
