#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
// #include <Preferences.h>
#include <IRremote.hpp>
#include "IR_commands_defination.h"

#define DECODE_NEC          // Includes Apple and Onkyo
#define DELAY_AFTER_SEND 50

#if !defined(RAW_BUFFER_LENGTH)
#  if RAMEND <= 0x4FF || RAMSIZE < 0x4FF
#define RAW_BUFFER_LENGTH  120
#  elif RAMEND <= 0xAFF || RAMSIZE < 0xAFF // 0xAFF for LEONARDO
#define RAW_BUFFER_LENGTH  400 // 600 is too much here, because we have additional uint8_t rawCode[RAW_BUFFER_LENGTH];
#  else
#define RAW_BUFFER_LENGTH  750
#  endif
#endif

#define MARK_EXCESS_MICROS    20    // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.

//#define DEBUG // Activate this for lots of lovely debug output from the decoders.



const char* ssid = "Yurid_h";  //replace
const char* password =  "0538777185"; //replace

AsyncWebServer server(80);
// Preferences prefs;
TFT_eSPI tft = TFT_eSPI();


int relayPin = 38;

int SEND_BUTTON_PIN = 0; //APPLICATION_PIN
int DELAY_BETWEEN_REPEAT = 50;
uint16_t sAddress = 0x7080;
uint8_t sCommand_VOL_UP = 0xC7;
uint8_t sCommand_VOL_DOWN = 0xC8;
uint16_t s16BitCommand = 0x5634;
uint8_t sRepeats = 0;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void sender();

void setup(){
  pinMode(SEND_BUTTON_PIN, INPUT_PULLUP);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(4, ledChannel);
  ledcWrite(ledChannel, 100);
  
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);


  
  Serial.begin(115200);
  #if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif

    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
    // IrSender.enableIROut(38);
    Serial.print(F("Ready to send IR signals at pin " STR(IR_SEND_PIN) " on press of button at pin "));
    Serial.println(SEND_BUTTON_PIN);

 
  WiFi.begin(ssid, password);
 
   while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    tft.drawString("Connecting to WiFi..", 5, 40, 4); //
  }
  
  Serial.println(WiFi.localIP());
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Connected to " + WiFi.localIP().toString(), 20, 10, 2); //
 
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });

  server.on("/relay/off", HTTP_GET   , [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    tft.drawString(keyOff.name + " >>>", 20, 60, 4); //
    Serial.println("Key OFF");
    IrSender.sendNEC(keyOff.address, keyOff.command, sRepeats);
    delay(DELAY_AFTER_SEND); 
    tft.drawString("                                        ", 20, 60, 4); //
    
  });
   server.on("/relay/on", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    tft.drawString(keyOn.name + " >>>", 20, 60, 4); //
    Serial.println("Key ON");
    IrSender.sendNEC(keyOn.address, keyOn.command, sRepeats);
    delay(DELAY_AFTER_SEND); 
    tft.drawString("                                        ", 20, 60, 4); //
  });

   server.on("/relay/vol_up", HTTP_GET   , [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "ok");
    tft.drawString(keyVolUp.name + " >>>", 20, 60, 4); //
    Serial.println("Key VOL UP");
    IrSender.sendNEC(keyVolUp.address, keyVolUp.command, sRepeats);
    delay(DELAY_AFTER_SEND); 
    tft.drawString("                                        ", 20, 60, 4); //
    
  });
   server.on("/relay/vol_down", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    tft.drawString(keyVolDown.name + " >>>", 40, 60, 4); //
    Serial.println("Key VOL DOWN");
    IrSender.sendNEC(keyVolDown.address, keyVolDown.command, sRepeats);
    delay(DELAY_AFTER_SEND); 
    tft.drawString("                                        ", 20, 60, 4); //
  });
  
  server.on("/relay/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain","ok");
    
  });
  
  server.on("/relay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(digitalRead(relayPin)));
    tft.drawString("                                        ", 20, 60, 4); //
  });
  
  server.begin();
}
 
void loop(){
     // If button pressed, send the code.
    bool tSendButtonIsActive = (digitalRead(SEND_BUTTON_PIN) == LOW); // Button pin is active LOW

  if (tSendButtonIsActive) {    
      sender();
  }   
}

void sender(){
  Serial.println(F("Send NEC with 16 bit address"));
  Serial.flush();
  // IrSender.sendNEC(sAddress & 0xFF, sCommand_1, sRepeats);
  IrSender.sendNEC(sAddress, sCommand_VOL_DOWN, sRepeats);
  delay(DELAY_AFTER_SEND); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}




