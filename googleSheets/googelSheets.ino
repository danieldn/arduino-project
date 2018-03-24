#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <TembooSSL.h>
#include "TembooAccount.h" // Contains Temboo account information

WiFiSSLClient client;

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);

  int wifiStatus = WL_IDLE_STATUS;

  // Determine if the WiFi Shield is present
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");

    // If there's no WiFi shield, stop here
    while(true);
  }

  Serial.println("OK");

  // Try to connect to the local WiFi network
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID, WPA_PASSWORD);

    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }
    delay(5000);
  }

  Serial.println("Setup complete.\n");
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running InitializeOAuth - Run #" + String(calls++));

    TembooChoreoSSL InitializeOAuthChoreo(client);

    // Invoke the Temboo client
    InitializeOAuthChoreo.begin();

    // Set Temboo account credentials
    InitializeOAuthChoreo.setAccountName(TEMBOO_ACCOUNT);
    InitializeOAuthChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    InitializeOAuthChoreo.setAppKey(TEMBOO_APP_KEY);
    InitializeOAuthChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);

    // Set Choreo inputs
    String ScopeValue = "https://spreadsheets.google.com/feeds";
    InitializeOAuthChoreo.addInput("Scope", ScopeValue);
    String ClientIDValue = "307973360975-ie9n7ghd509ld29hm48h8udkc7mj70no.apps.googleusercontent.com";
    InitializeOAuthChoreo.addInput("ClientID", ClientIDValue);

    // Identify the Choreo to run
    InitializeOAuthChoreo.setChoreo("/Library/Google/OAuth/InitializeOAuth");

    // Run the Choreo; when results are available, print them to serial
    InitializeOAuthChoreo.run();

    while(InitializeOAuthChoreo.available()) {
      char c = InitializeOAuthChoreo.read();
      Serial.print(c);
    }
    InitializeOAuthChoreo.close();
  }

  Serial.println("\nWaiting...\n");
  delay(30000); // wait 30 seconds between InitializeOAuth calls
}
