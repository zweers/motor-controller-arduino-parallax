# motor-controller-arduino-parallax
parallax motor controller sketch, added potmeter and comments in code

Functie : (english see below)

Sturen van de juiste signalen naar de motorcontroller (parallax HB25) welke de snelheid van een 12V-gelijkstroommotor regelt.
Een potmeter maakt het mogelijk de motorsnelheid realtime te varieren terwijl de motor draait

Werking:

De parallax motorcontroller vertaalt een pulslengte in een voltage tussen -12V en +12V voor de motor.
Deze puls wordt door een Arduino geleverd.
De pulslengte wordt ingesteld door in de code (de Arduino sketch) de gewenste pulslengtes aan te geven en deze te uploaden naar de Arduino.
De potmeter voltage wordt ingelezen door de Arduino en deze waarde varieert de wachttijden biunnen de arduino sketch. 
Effectief wordt hiermee de periode van de golf veranderd

Function:

Sending of a proper signal to the motordriver )parallax HB25) which controls the speed of a 12V electromotor. 
A potmeter enables adjusting and finetuning the speed during operation

Principle:

The parallax motorcontroller changes a pulslength (provided by the Arduino) into a voltage between -12V and + 12V
Various pulslength are setsequentially in the sketch (code) and this sketch is uploaded to the Arduino.
The pulslengths in the code will generate a pump flow which varies through time. 
A potmeter is added for finetuning during operation so it is not necessary to upload a sketch for every small adjustment in "wavelength"
However for adjusting wave shape another sketch must be upoloaded with different pulslenths

