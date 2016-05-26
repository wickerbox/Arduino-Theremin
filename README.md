# Arduino Theremin v1

Playing music by waving your hands over a rangefinder for pitch and pressing capacitive sense pads for key.

<img src="osh-preview.png">

<img src="arduino-theremin.png">

I've <a href="https://oshpark.com/shared_projects/u5dTU3Mx">shared the boards at OSH Park</a>.

## Instructions

1. Program the Arduino Uno
1. To use it, the Uno needs some sort of power, 9V or 5V or whatever.
1. Press the 'reset' button. The red and green lights will blink.
1. The switch normally sits in the 'OFF' position.
1. Flip the switch to the RECORD position to play and record a tune.
1. Move one hand vertically between 1 and about 10 inches above the rangefinder.
1. Use the other hand to press the capacitive sense pads to choose a key.
1. When you're done with a tune, flip the switch back to OFF.
1. When you want to play back the tune, flip the switch to PLAYBACK.
1. The tune will play once through. 
1. To play it again, flip the switch to OFF and then to PLAYBACK.
1. To record a new tune, flip the switch to RECORD, which erases the old tune.

## Bill of Materials

|Refdes|Qty|Description|Digikey|
|------|---|-----------|-------|
|J1|1|CONN HEADER FEMALE .100" SNGL STR 8POS|952-1823-ND|
|LED1|1|LED RED DIFF 5MM ROUND T/H|1125-1188-ND|
|LED2|1|LED GRN DIFF 5MM ROUND T/H|1125-1184-ND|
|R1,R2|2|RES 220 OHM 1/4W 5% CF MINI|S220QCT-ND|
|R3,R4|2|RES 10K OHM 1/4W 5% CF MINI|S10KQCT-ND|
|RV1|1|POT 10K OHM 1/5W PLASTIC LINEAR|987-1301-ND|
|SP1|1|SPEAKER 8 OHM .25W 23MM ROUND|458-1124-ND|
|SW1|1|SWITCH TACTILE SPST-NO 0.05A 24V|SW400-ND|
|SW2|1|SWITCH TOGGLE SPDT 5A 120V|EG2377-ND|
|U1|1|CONN HEADER MALE .100" SNGL STR 40POS|S1012EC-40-ND|

Note: for U1, one 40-position header is the cheapest option (about $0.50) and you can just snap it apart into the sections you need.

|Refdes|Qty|Description|Adafruit|
|------|---|-----------|--------|
|P1|1|Maxbotix Ultrasonic Rangefinder LV-EZ1|Product 172|


