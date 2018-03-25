#include <ESP8266WiFi.h>



const char* ssid     = "Puppet Guest";
const char* password = "argon4949";
int8_t utc_offset = -7; // hours off of UTC... -7 for PST?
const char* location = "portland%2C%20or";

const char* path_prefix2 = "query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22";
const char* path_postfix2 = "%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";

const char* path_prefix = "/v1/public/yql?q=select%20item.condition.code%2C%20item.condition.text%20%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22";
const char* path_postfix = "%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys";
const char* host = "query.yahooapis.com";
const int httpPort = 80;

int16_t weathercode = -1;
int16_t createhour, createmin, temperature;

void setup() {
  Serial.begin(115200);
  delay(10);  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}

uint32_t timekeep=0xFFFF;

void loop() {
  uint32_t currTime = millis();
  if ((timekeep > currTime)  || (currTime > (timekeep + 30000))) {
    timekeep = currTime;
    updateWeather();
    getTemperature();

  }

}

void getTemperature() {
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = String(path_prefix2) + String(location) + String(path_postfix2);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);

   while(client.available()){
    String line = client.readStringUntil('\r');
    int i = line.indexOf(String("\"temp\":"));
    if (i < 0)
      continue;
    //Serial.println(line);
    temperature = line.substring(i+8).toInt();
    Serial.print("temperature: ");
    Serial.println(temperature);
    
   }
}


void updateWeather() {
  
  Serial.print("Connecting to "); Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  
  // We now create a URI for the request

  String url = String(path_prefix) + String(location) + String(path_postfix);
  
  Serial.print("Requesting URL: ");  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  

  weathercode = -1;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    int i = line.indexOf(String("\"code\":"));
    if (i < 0) continue;
    //Serial.println(line);
    weathercode = (line.substring(i+8)).toInt();

    // extract hour and minute
    i = line.indexOf(String("\"created\":"));
    if (i < 0) continue;
    createhour = (line.substring(i+22)).toInt();
    createmin = (line.substring(i+25)).toInt();
  }
  
  Serial.println("Closing connection");

  // convert from UTC to local
  createhour += 24;
  createhour += utc_offset;
  createhour %= 24;
  Serial.print("\nWeather code: "); Serial.print(weathercode);
  Serial.print(" @ "); Serial.print(createhour); Serial.print(":"); Serial.println(createmin);

  // Get the current time of day, between 0 and 65535
  //uint16_t timeofday = map((createhour * 60) + createmin, 0, 1440, 0, 65535);

  //Serial.print("Time of day = "); Serial.print(timeofday); Serial.println("/65535");
  
 

  // weathercode = 46; // hardcode weather animation test

  switch (weathercode) {
    case 0: // tornado!
      Serial.println("tornado");
      // lotsa cloud, no rain, and wind!
      break;
    case 1: // tropical storm
      Serial.println("tropical storm");
      // no cloud, a lot of rain, no snow, no thunder and lotsa wind!
      break;
    case 2: // hurricane
      Serial.println("hurricane");
      // some cloud, some rain, no snow, no thunder and lotsa wind!
      break;

    case 3: // severe thunder
      Serial.println("severe thunder");
      // some cloud, no rain, no snow, mega lightning, some wind!
      break;

    case 4: // thunder
      Serial.println("thunder");
      // some cloud, no rain, no snow, some lightning, some wind!
      break;

    case 5: // mixed rain + snow
    case 6: // mixed rain and sleet
    case 7: // mixed snow and sleet
    case 18: // sleet
    case 35: // mixed rain/hail
      Serial.println("Rain/Snow/Sleet");
      // some cloud, some rain, some snow, no lightning, no wind!
      break;

    case 8: // freezing drizzle
    case 9: // drizzle
      Serial.println("Drizzle");
      // some cloud, a little rain, no snow, no lightning, no wind!
      break;

    case 10: // freezing rain
    case 11: // showers
    case 12: // showers
      Serial.println("Rain/Showers");
      // some cloud, lotsa rain, no snow, no lightning, no wind!
      break;

    case 13: // snow flurries
    case 14: // light snow showers
      Serial.println("flurries");
      // some cloud, no rain, some snow, no lightning, no wind!
      break;
      
    case 15: // blowing snow
      Serial.println("blowing snow");
      // some cloud, no rain, snow, no lightning, lotsa wind!
      break;

    case 16: // snow
    case 17: // hail
    case 42: // scattered snow showers
      Serial.println("snow");
      // some cloud, no rain, snow, no lightning, no wind!
      break;
      
    case 41: // heavy snow
    case 43: // heavy snow
      Serial.println("heavy snow");
      // some cloud, no rain, lotsa snow, no lightning, no wind!
      break;

    case 31: // clear (night)
    case 32: // sunny
    case 33: // fair (night)
    case 34: // fair (day)
    case 25: // hot
    case 36: // cold
      Serial.println("Clear/fair");
      // no cloud, no rain, no snow, no lightning, no wind!
      break;

    case 23: // blustery
    case 24: // windy
      Serial.println("Windy");
      // no cloud, no rain, no snow, no lightning, lots wind
      break;

    case 26: // cloudy
    case 19: // dust
      Serial.println("Cloudy");
      // lotsa cloud, nothing else
      break;

    case 27: // mostly cloudy
    case 28: // mostly cloudy
    case 20: // foggy
    case 22: // smoky
      Serial.println("mostly Cloudy");
      // lotsa cloud, nothing else
      break;

    case 29: // partly cloudy
    case 30: // partly cloudy
    case 44: // partly cloudy
    case 21: // haze
      Serial.println("Partly Cloudy");
      // lotsa cloud, nothing else
      break;

    case 37: // isolated thunderstorms
    case 47: // isolated thundershowers
      Serial.println("isolated thunderstorms");
      // some cloud, some rain, no snow, some lite, no wind
      break;

    case 38: // scattered thunderstorms
    case 39: // scattered thundershowers
      Serial.println("scattered thundershowers");
      // some cloud, some rain, no snow, some lite, no wind
      break;

    case 45: // thundershowers
      Serial.println("thundershowers");
      // some cloud, rain, no snow, lite, no wind
      break;

    case 40: // scattered showers
      Serial.println("scattered showers");
      // some cloud, some rain, no snow, no lite, no wind
      break;

    case 46: // snow showers
      Serial.println("snow showers");
      // some cloud, some rain, some snow, no lite, no wind
      break;
      
    default:
      break;
  }

}
