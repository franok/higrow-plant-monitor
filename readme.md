# ESP32 HiGrow Plant Monitor

## Hardware

**ESP32 DHT11 WIFI Bluetooth Soil Temperature Humidity Sensor18650**

### Technical details:
- Board name: WeMos Wifi & Bluetooth Battery
- Chip: ESP32-D0WDQ6 (revision 1)
- Crystal: 40MHz
- Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse


## Development

- Copy `credentials.h.template` to `credentials.h` and edit it.
- If needed, modify `config.h`.
- `higrow-plant-monitor.ino` is the entry point

### Configuration for programming the board

- Download Arduino IDE v2
- Install Serial USB Drivers:
  - For Windows:
    - Download CP210x_Windows_Drivers from https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads and install it.
    - Download CH341SER_WIN_3.5 from https://github.com/wemos/ch340_driver/raw/master/CH341SER_WIN_3.5.ZIP and run SETUP.EXE
  - For Mac/Linux: ???
- File > Preferences:
    - Add Boards Manager URL: `https://dl.espressif.com/dl/package_esp32_index.js`
- Select the board `WeMos WiFi&Bluetooth Battery`
  - under: Tools > Board > esp32

### Arduino Programming Knowledge

- `.ino` files are concatenated for conversion and compilation. 
- The file with the same name as the project folder is first and other .ino files are attached in alphabet order. 
- Global variables are visible starting from the place where they are defined, to the end of the resulting concatenated file.

### Arduino Libraries

Tools > Manage Libraries

- DHT Sensor Library
by Adafruit
  - version used: 1.2.3

- ArduinoJson
by Benoit Blanchon
  - version used: 6.20.0
  - https://arduinojson.org/v6/doc/
  - calculate byteBuffer size for json payload:
  https://arduinojson.org/v6/assistant/


## Troubleshooting

### Debug HTTP requests
print to stdout all incoming traffic on server
```
$ nc -l -p <port>
```

### Arduino Programming Errors
strange output in Serial monitor, caused by:
```
Serial.println("Do not concat " + var + "like this, it causes undefined behaviour!");
```

```
Serial.print("This is the correct ");
Serial.print("way to ");
Serial.print("concat strings with a variable ");
Serial.println(var);
```

## Related Links

https://blog.csdn.net/coolwaterld/article/details/83783013

https://github.com/LilyGO/higrowopen

https://github.com/fclairamb/higrow-esp32/blob/main/higrow-esp32.ino#L18

https://www.fambach.net/esp32-highgrow-pflanzenspiess/

https://github.com/sfambach/esp32/tree/master/boards/HighGrow/src/HiGrowESP32MQTT

