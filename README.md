# Rotary Encoder OLED Input for ESP8266 (NodeMCU)

This project allows you to input text using a rotary encoder and display it on a 128x64 I2C OLED screen. The hardware setup is based on the NodeMCU ESP8266 board.

## 🛠️ Hardware Requirements

- NodeMCU (ESP8266)
- Rotary Encoder with push button
- SSD1306 OLED display (128x64, I2C interface)
- Breadboard and jumper wires

## 📌 Pin Connections

| Component       | NodeMCU Pin |
|----------------|-------------|
| OLED SDA       | D2          |
| OLED SCL       | D1          |
| Rotary CLK     | D5 (GPIO14) |
| Rotary DT      | D6 (GPIO12) |
| Rotary SW      | D7 (GPIO13) |

## 📦 Libraries Used

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

You can install these libraries using the Arduino Library Manager.

## 📋 Features

- Rotate the encoder to select characters (A-Z, space, backspace).
- Press the button to add the selected character or delete (⬅).
- Display the typed text in real-time on the OLED screen.

## 🚀 Getting Started

1. Wire your components according to the table above.
2. Open the `.ino` file in the Arduino IDE.
3. Install the required libraries.
4. Select the correct board (NodeMCU 1.0) and port.
5. Upload the sketch to the device.

## 🧠 Usage

- Turn the knob left/right to scroll through characters.
- Press the button to add the character to the text.
- Select ⬅ and press to delete the last character.

## 📄 License

This project is licensed under the MIT License.