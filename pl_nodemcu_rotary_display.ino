
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED kijelző mérete (128x64 pixel)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C cím (általában 0x3C az SSD1306 esetében)
#define OLED_ADDR 0x3C

// NodeMCU I2C bekötés (SDA=D2, SCL=D1)
#define SDA_PIN D2
#define SCL_PIN D1

// OLED objektum létrehozása
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Rotary
#define CLK D5  // GPIO14
#define DT D6   // GPIO12
#define SW D7   // GPIO13

int counter = 0;
int lastStateCLK;
bool buttonPressed = false;

char letters[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
    'U', 'V', 'W', 'X', 'Y', 'Z', '_',  '<',
};

char letters2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ⬅";  

const int lettersCount = sizeof(letters) - 1;  // Méretből kivonjuk a lezáró '\0'-t

String inputText = "";  // A beírt szöveg

void updateDisplay() {
    display.clearDisplay();

    // Kiválasztott karakter megjelenítése
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(40, 5);
    display.print(letters[counter]);

    // Beírt szöveg megjelenítése
    display.setTextSize(2);
    display.setCursor(10, 40);
    display.print("> ");
    display.print(inputText);

    display.display();
}

void setup() {
    // I2C inicializálás
    Wire.begin(SDA_PIN, SCL_PIN);

    // OLED inicializálás
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("SSD1306 nem található!");
        for (;;);
    }

    // Képernyő törlése
    display.clearDisplay();

    // Szöveg beállítása
    display.setTextSize(2);       // Szöveg mérete
    display.setTextColor(WHITE);  // Szöveg színe
    display.setCursor(10, 25);    // Kezdő koordináta (x, y)
    display.println("Hello!");    // Kiírandó szöveg

    // Képernyő frissítése
    display.display();


    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);
    
    Serial.begin(115200);
    lastStateCLK = digitalRead(CLK);
}

void loop() {
    int currentStateCLK = digitalRead(CLK);
    
    if (currentStateCLK != lastStateCLK) {
        if (digitalRead(DT) != currentStateCLK) {
            if(counter<lettersCount){
              counter++;  // Jobbra forgás
            }
        } else {
            if(counter>0){
              counter--;  // Balra forgás
            }
        }
        //Serial.print("Counter: ");
        //Serial.println(counter);
        
        updateDisplay();
    } 
    
    lastStateCLK = currentStateCLK;

    // Gomb figyelése
    if (digitalRead(SW) == LOW && !buttonPressed) {
        //Serial.println("Button Pressed!");
        buttonPressed = true;
        if (letters[counter] == '<') {  
            if (inputText.length() > 0) {
                inputText.remove(inputText.length() - 1);  // Törlés
            }
        } else {
            inputText += letters[counter];  // Karakter hozzáadása
        }
        updateDisplay();
    }

    if (digitalRead(SW) == HIGH) {
        buttonPressed = false;
    }

    delay(5);  // Kis késleltetés a zajszűréshez
}
