# ECO-oneM2M
IIIT H Team 2 Project for KETI oneM2M hackathon 

The project is built on various platforms like Arduino, Django, Onem2m and Alexa 

Instructions for usage:
1) The arduino IDE is used to compile the arduino sketches 
2) The Django projects are built using Pycharm Community edition
3) The Alexa skill is built on the Alexa developer console
4) The OM2M version of Onem2m is built using the Eclipse IDE.
5) pip install requirements.txt and then run the django server, 
6) run reddis server 
7) run om2m server

1) Arduino Sketches:
	There are two scripts, one to get the sensor data from the PIR sensors, and the other is to actuate the hardware components connected.
a) The KETI_PIR script is used to get the data from the Onem2m, whenever there is no motion recorded in the PIR sensors for a set time, the cicuit sends a switch off command to the Onem2m server
b) The Actuation_PIR script helps in subscribing to the Alexa container and the pir output. The default behaviour is to switch off the lights based on the pir command, but we also have provided a manual 
   override option through Alexa.

2) Django project:
	The django project consists of a dashboard made of HTML and CSS and also servers a processing entity for all the requests. 
	This project also handles the Alexa requests from the user. All the actuation requests are taken care of in the project. 

3) Alexa skill:
	The skill can be imported into the developer console and can be invoked using "Alexa Smart Control" intent.

4) OM2M: run the start script based on the operating system.

5) After uploading the codes to the devices

	a. Actuation device has to subscribe to Master_cont
	b. Actuation device has to subscribe to Data container of the device 
	c. Dashboard has to subscribe to Data Data container of the device 
	
6) The json files are postman collections necessary to create the necessary containers