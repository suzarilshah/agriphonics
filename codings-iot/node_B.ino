#include <ESP8266WiFi.h>
#include "src/iotc/common/string_buffer.h"
#include "src/iotc/iotc.h"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define WIFI_SSID "<ENTER WIFI SSID HERE>"
#define WIFI_PASSWORD "<ENTER WIFI PASSWORD HERE>"

const char* SCOPE_ID = "<ENTER SCOPE ID HERE>";
const char* DEVICE_ID = "<ENTER DEVICE ID HERE>";
const char* DEVICE_KEY = "<ENTER DEVICE primary/secondary KEY HERE>";

const int analogInPin = A0;
float calibration_value = 20.24 - 0.7; 
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;


void on_event(IOTContext ctx, IOTCallbackInfo* callbackInfo);
#include "src/connection.h"

void on_event(IOTContext ctx, IOTCallbackInfo* callbackInfo) {
  // ConnectionStatus
  if (strcmp(callbackInfo->eventName, "ConnectionStatus") == 0) {
    LOG_VERBOSE("Is connected ? %s (%d)",
                callbackInfo->statusCode == IOTC_CONNECTION_OK ? "YES" : "NO",
                callbackInfo->statusCode);
    isConnected = callbackInfo->statusCode == IOTC_CONNECTION_OK;
    return;
  }

  // payload buffer doesn't have a null ending.
  // add null ending in another buffer before print
  AzureIOT::StringBuffer buffer;
  if (callbackInfo->payloadLength > 0) {
    buffer.initialize(callbackInfo->payload, callbackInfo->payloadLength);
  }

  LOG_VERBOSE("- [%s] event was received. Payload => %s\n",
              callbackInfo->eventName, buffer.getLength() ? *buffer : "EMPTY");

  if (strcmp(callbackInfo->eventName, "Command") == 0) {
    LOG_VERBOSE("- Command name was => %s\r\n", callbackInfo->tag);
  }
}

void setup() {
  Serial.begin(9600);
  connect_wifi(WIFI_SSID, WIFI_PASSWORD);
  connect_client(SCOPE_ID, DEVICE_ID, DEVICE_KEY);

  if (context != NULL) {
    lastTick = 0;  // set timer in the past to enable first telemetry a.s.a.p
  }
  Serial.println("Start Project PH");  
}

void loop() {
  if (isConnected) {
    unsigned long ms = millis();
    if (ms - lastTick > 10000) {  // send telemetry every 10 seconds
      char msg[64] = {0};
      int pos = 0, errorCode = 0;

      lastTick = ms;
      if (loopId++ % 2 == 0) {  // send telemetry
        pos = snprintf(msg, sizeof(msg) - 1, "{\"accelerometerX\": %d}",
                       10 + (rand() % 20));
        errorCode = iotc_send_telemetry(context, msg, pos);
      } else {  // send property
        pos = snprintf(msg, sizeof(msg) - 1, "{\"dieNumber\":%d}",
                       1 + (rand() % 5));
        errorCode = iotc_send_property(context, msg, pos);
      }
      msg[pos] = 0;

      if (errorCode != 0) {
        LOG_ERROR("Sending message has failed with error code %d", errorCode);
      }
    }

    iotc_do_work(context);  // do background work for iotc
  } else {
    iotc_free_context(context);
    context = NULL;
    connect_client(SCOPE_ID, DEVICE_ID, DEVICE_KEY);
  }
  
  for (int i = 0; i < 10; i++) {
      buf[i] = analogRead(analogInPin);
      delay(10);
      }
  for (int i = 0; i < 9; i++) 
  {
      for (int j = i + 1; j < 10; j++)
      {
           if (buf[i] > buf[j]) 
           {
               temp = buf[i];
               buf[i] = buf[j];
               buf[j] = temp;
           }
      }
  }
      
  avgValue = 0;
  for (int i = 2; i < 8; i++)avgValue += buf[i];
  float pHVol = (float)avgValue*3.3/4096.0/6;
        pHVol = -15.7 * pHVol + calibration_value;
  Serial.print("pH Level = ");
  Serial.println(pHVol);
  Blynk.virtualWrite(V4,pHVol);
  Blynk.run();
  delay(1000);
}
