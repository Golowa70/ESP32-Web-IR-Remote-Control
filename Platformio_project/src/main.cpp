#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>
#include "IR_commands_defination.h"
//#include <Preferences.h>

#define DECODE_NEC // Includes Apple and Onkyo
#define DELAY_AFTER_SEND 50

#if !defined(RAW_BUFFER_LENGTH)
#if RAMEND <= 0x4FF || RAMSIZE < 0x4FF
#define RAW_BUFFER_LENGTH 120
#elif RAMEND <= 0xAFF || RAMSIZE < 0xAFF // 0xAFF for LEONARDO
#define RAW_BUFFER_LENGTH 400            // 600 is too much here, because we have additional uint8_t rawCode[RAW_BUFFER_LENGTH];
#else
#define RAW_BUFFER_LENGTH 750
#endif
#endif

#define MARK_EXCESS_MICROS 20 // Adapt it to your IR receiver module. 20 is recommended for the cheap VS1838 modules.
// #define DEBUG // Activate this for lots of lovely debug output from the decoders.

const char *ssid = "Yurid_h";        // replace
const char *password = "0538777185"; // replace

AsyncWebServer server(80);
// Preferences prefs;
TFT_eSPI tft = TFT_eSPI();

int relayPin = 38;

const int8_t SEND_BUTTON_PIN = 0; // APPLICATION_PIN
const int DELAY_BETWEEN_REPEAT = 50;
uint8_t sRepeats = 0;

const int lcdPwmFreq = 5000;
const int lcdPwmChannel = 1; // 0 work with ttgo configuration
const int lcdPwmResolution = 8;

void sender();
void tftClearString();
void deviceCommmandHandler(Command commands_set[], int setLength, int key);

void setup()
{
  pinMode(SEND_BUTTON_PIN, INPUT_PULLUP);

  // pinMode(relayPin, OUTPUT);
  // digitalWrite(relayPin, HIGH);

  ledcSetup(lcdPwmChannel, lcdPwmFreq, lcdPwmResolution);
  ledcAttachPin(4, lcdPwmChannel);
  ledcWrite(lcdPwmChannel, 100);

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  Serial.begin(115200);
  delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!

  IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
  // IrSender.enableIROut(38);
  Serial.print(F("Ready to send IR signals at pin " STR(IR_SEND_PIN) " on press of button at pin "));
  Serial.println(SEND_BUTTON_PIN);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
    tft.drawString("Connecting to WiFi..", 5, 40, 4); //
  }

  Serial.println(WiFi.localIP());
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Connected to " + WiFi.localIP().toString(), 20, 10, 2); //

  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello World"); });

  server.on("/device_command/off", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain", "ok");
              int size = sizeof(avr161_commands_set) / sizeof(Command);
              deviceCommmandHandler(avr161_commands_set, size, ON);

              // tft.drawString(keyOff.name + " >>>", 20, 60, 4); //
              // Serial.println("Key OFF");
              // IrSender.sendNEC(keyOff.address, keyOff.command, sRepeats);
              // delay(DELAY_AFTER_SEND);
              // tftClearString();
            });
  server.on("/device_command/on", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain", "ok");
              tft.drawString(keyOn.name + " >>>", 20, 60, 4); //
              Serial.println("Key ON");
              IrSender.sendNEC(keyOn.address, keyOn.command, sRepeats);
              delay(DELAY_AFTER_SEND);
              tftClearString(); });

  server.on("/device_command/vol_up", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain", "ok");
              tft.drawString(keyVolUp.name + " >>>", 20, 60, 4); //
              Serial.println("Key VOL UP");
              IrSender.sendNEC(keyVolUp.address, keyVolUp.command, sRepeats);
              delay(DELAY_AFTER_SEND);
              tftClearString(); });
  server.on("/device_command/vol_down", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain", "ok");
              tft.drawString(keyVolDown.name + " >>>", 40, 60, 4); //
              Serial.println("Key VOL DOWN");
              IrSender.sendNEC(keyVolDown.address, keyVolDown.command, sRepeats);
              delay(DELAY_AFTER_SEND);
              tftClearString(); });

  server.on("/device_command/toggle", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "ok"); });

  server.on("/device_command", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              request->send(200, "text/plain", String(digitalRead(relayPin)));
              tftClearString(); });

  server.begin();
}

void loop()
{
  // If button pressed, send the code.
  bool tSendButtonIsActive = (digitalRead(SEND_BUTTON_PIN) == LOW); // Button pin is active LOW

  if (tSendButtonIsActive)
  {
    //
  }
}

void tftClearString()
{
  tft.drawString("                                        ", 20, 60, 4); //
}

void deviceCommmandHandler(Command commands_set[], int length, int key)
{
  tft.drawString(commands_set[key].name + " >>>", 40, 60, 4); //
  Serial.println("Key " + commands_set[key].name + " pressed");
  IrSender.sendNEC(commands_set[key].address, commands_set[key].command, sRepeats);
  delay(DELAY_AFTER_SEND);
  tftClearString();
}
