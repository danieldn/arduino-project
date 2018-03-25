# Paladin

Arduino project for IoT Hackathon 2018 by Women Who Code (Portland) at Puppet.
\#WWCodeHack18


## Team Members

_Amber Stone, Erika Martinez, Daniel Nguyen, Diana Connolly, Erika Martinez, Larry Phi Chiem, Polina Jastrzebska_

## Hardware

[Feather Huzzah] <https://learn.adafruit.com/adafruit-feather-huzzah-esp8266?view=a>

[PIR Sensor] <https://www.adafruit.com/product/189>

## Hardware Setup and Testing

[Feather Huzzah Setup and Blink Test - Follow instructions here] <https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide>

[PIR Sensor "Hello World"] <https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/testing-a-pir>

## Setup Notes

Setting up the Feather Huzzah was fairly straightforward using the instructions for the Blink Test 

Setting up the PIR Sensor "Hello World" test equired a bit more troubleshooting. 

We found the PIR to be extremely sensitive, not only to movement, but to bright light. 
Using the 3.3V output of the huzzah as the power source excaborated the sensitivity. 
We dialed the sensitivity potentiometer down to the lowest sensitivity possible and used the 5V USB power output of huzzah. This enabled a successful test. We are using a ceramic bowl and cup to simulate a dark room for our demo.

## Website for Presentation

[Watt's Up!] <http://10.0.13.6:5000/>

## What's Next? Exciting project plans for the future

Setting the sensor up to connect to actual light controlls

View Yahoo weather API's to control internal lighting

Build Backend storage to facilitate collection and analysis of data


