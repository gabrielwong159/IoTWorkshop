# IoT Workshop - Open House 2017
Control a strip of LEDs via WiFi using a NodeMCU board, and a website.

## Getting Started
To begin, you will need a WS2812 LED strip, a NodeMCU board, and a MicroUSB data cable for connecting to the board.
In addition, you should have the [Arduino IDE](https://www.arduino.cc/en/main/software) already installed on your computer.

### Prerequisites
1. Click on the 'Clone or download' button above, followed by 'Download ZIP', to download the files into your desktop.
2. Extract the files from the downloaded ZIP.

### Setting up
1. Open the folder and move `wifi.h` from `docs` to the same folder as `wifi-server.ino`
2. Open `wifi-server.ino`, and click on the tab named `wifi.h` to edit it
3. Change `_ssid` and `_password` accordingly
4. Set up your Arduino IDE for the NodeMCU according to the instructions [here]()
5. Upload your code to the board.

## Running it
Go to [http://esp8266.local/](http://esp8266.local/). Have fun!