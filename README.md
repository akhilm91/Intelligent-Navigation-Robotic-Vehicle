# Intelligent-Navigation-Robotic-Vehicle
Using PIC18F4550 MCU

The aim of this project is to design an intelligent Navigation Robotic vehicle that performs the following tasks:

Robotic the vehicle will move in a forward direction in a straight path. The locomotion for the vehicle will be implemented by using two stepper motors driven in a full step mode by using Port of the micro interfaced with a stepper motor driver.
The vehicle will able to detect and count these markers (black strips). The sensing of these markers implemented by using a Photo-Reflective Optical sensor mounted at an appropriate position underneath the vehicle.
This robotic vehicle, every time one of these markers is detected, should respond by giving an audio signal through a Piezo Buzzer and a visual response should also be given by a single 7-segment LED.


Robot needs to use PIC18F4550 from Microchip as MCU and the Vehicle chassis is made by recycling trays used to keeps FPGAs.

Three proximity sensors are used to sense objects in front, right and left side of the vehicle and change directions accordingly.

Robotic Vehicle working Method: 

- Forward direction with no obstacle. 
- Forward direction with obstacle. Vehicle to move back and turn either left or right. 
- Forward direction with obstacle in front and on the left. Vehicle to move back slightly (optional) and turn right and proceed to move forward thereafter. 
- Forward direction with obstacle in front and on the right. Vehicle to move back slightly (optional) and turn left and proceed to move forward thereafter. 
- Forward direction with obstacle in front, on the left and on the right. Vehicle to move back slightly and clear from all obstacles and rotate 180 degree and continue to move forward thereafter. The counter of the 7-segment during the forward path (up count) and reverse path (down count) will be counted. Upon reaching zero it will stop the vehicle.
