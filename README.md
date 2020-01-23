# Progress Report for RSI
### By **Youssef Beltagy** and **Mike Miller**

This is the documentation for the Remote site Incubator (RSI) project. For up to date information on my daily suffering, please go to the Progress Reports Folder.

The most up to date code is the Sensors_Network in the esp32 code Folder. I may have uploaded it in the middle of a debugging session. so it doesn't necessarily work, cheers!

I love my life.

## Objective 
We want to build a sensor-system to observe and document the hatching conditions of fish. For now, we know that we need to deploy a prototype for Coho salmon sometime in January of 2020. Later on, the sensor system will be used to observe Kokanee salmon in the Lake Washington/Sammamish watershed. This project is sponsored by [Jeff Jensen, Ph.D](https://www.uwb.edu/biological-sciences/faculty/biology/jjensen), and supervised by [Hrair Aintablian, Ph.D](https://www.uwb.edu/engineering-math/faculty/electrical-engineering/haintablian).



## Motivation
Jeff explains, in his biography, "Kokanee populations crashed in Lake Washington in the 1920’s, and in Lake Sammamish in the 1970’s, to the point that native kokanee are known to exist only in a few tributaries of Lake Sammamish." This project is an attempt to help Jeff get more data on salmon, and automate the data-collection process.

We believe this project is important (and are commited to it) because there is currently nothing similar to it, so what we make will most likely be used and make an effect. Furthermore, the alternative to the RSI is going down to the incubator and staying there during sunset hours (most of the salmon leave the incubator at sunset) to count the salmon as they leave the incubator. After this project, we don't want anyone to spend their evening in the cold, counting fish.

This project should allow Jeff (and hopefully other researchers) to know the exact count of the fish (instead of an approximation from the sunset hours) and the living conditions of the fish from his computers (and hopefully phone).



## Specifications
Jeff wants a remote sensor-system that makes readings and sends them to him, so he doesn't have to go down to the incubator to know how the salmon fish are doing (thus the "remote site" in the project's name). Through conversing with him, we identified the quantities and features that he is interested in.

Jeff wants to know these quantities (ordered in terms of priority).
1. The number of fish that manage to hatch
2. The waterflow into the incubator
3. The Temperature inside the incubator
4. The Dissolved Oxygen content of the water inside the incubator
5. The turbidity of the water in the incubator
6. The PH of the water in the incubator

Jeff wants to be able to install the incubator where our fish counter would not have access to WiFi or power. For that we have to solve two technical problems.
1. Communication without WiFi
2. Access to power without the power-grid

Ideally, we would also like to make a user-friendly interface, but our focus is for the RSI to output a comma delimited file that can be used by data analysis software.



## Progress
In this quarter, we managed to build the custom fish-counter sensor and wrote the code for it. We tested the fish-counter to the best of our abilities. The only remaining tests are with a dead fish (to simulate a living one) and testing on the field.

We made a prototype for the data collection system, using an Arduino Mega, that we can deploy (but is far from perfect). We currently have the first two sensors, the fish-counter and the flow meter. The sensors' data is time-stamped with a real-time-clock module, and saved to an SD card. To get feedback about the system while we are on-site, we have a small monitor that shows what the last readings were.

We demoed what we had to Jeff and got his feedback. Jeff explained that the fish-counter might be too narrow and can cause the incubator to overfill with water and overflow. We will have to widen the 3d-printed tube of the fish-counter and use multiple of them. Jeff told us that the next most important thing to him now is to add the remote functionality. 

We went with Jeff to see where the first RSI (the one that will be deployed in January) will be located. Fortunately, for the first deployment, we will have access to a power socket so we can focus on the data-collection and transmission system for now. When we have a satisfactory data collection and transmission system, we will focus on finding a solution to the power problem.

### Demo

This is the current prototype (I took this picture at home, so it doesn't have the fish-counter, but we demoed with the fish-counter). When we deploy it, we will use a PCB to get rid of the Wires.

![Demo](https://raw.githubusercontent.com/Youssef-Beltagy/Remote_Site_Incubator/master/Images/Demo1.jpg)


This is an up close image of what the screen prints.

![Demo up-close](https://raw.githubusercontent.com/Youssef-Beltagy/Remote_Site_Incubator/master/Images/Demo3.jpg)


### Deployment Location

This is where the RSI will be placed. A kind couple will allow us to put it under their porch.
![Image of deployment location](https://raw.githubusercontent.com/Youssef-Beltagy/Remote_Site_Incubator/master/Images/Deployment_Location2.jpg)


## Next Steps
Organized by category


### Data Collection and Transmission
+ [ ] Research and add module for remote communication (please see the appendix)
+ [ ] Widen the fish-counter sensor and make more of it
+ [ ] Add Turbidity Sensor
+ [ ] Add PH Sensor
+ [ ] Add Dissolved Oxygen Sensor


### Data Integrity
+ [ ] Test all sensors and make excel sheets of our sensor vs calibrated sensor from labs
+ [ ] check whether the sensors should be used, calibrated, or eliminated


### Power
+ [ ] Measure the *typical* power draw of the system
+ [ ] Assess feasibility of using solar panels
+ [ ] Assess battery options and feasibility of using disposable battery


### Usability and Maintainability
+ [ ] Clean the code and refactor it
+ [ ] Make classes and libraries for the flow-meter and fish-counter
+ [ ] Document how to use the system and put everything in one location so Jeff can easily use it
+ [ ] Make it really easy to use so Jeff would give it to others as well



## Appendix
In here we include more information about each sensor, any module that we used, and any other details. It is still a work-in-progress, so please excuse me, Harry. I don't intend to finish this part until we are finished testing all the sensors and are satisfied with them.


### Sensors

**Remote Communication**

For remote communications, our initial research showed us that we can use two approaches:
- [Phone Network](https://www.adafruit.com/product/1963)
- [Satellite Internet](https://www.rock7.com/products-rockblock)

The links are just examples of what we can use. We think the satellite internet solution would be too expensive to use. We will likely use the Phone network solution.


**Fish Counter**

This sensor was custom build for this project. It is an IR light-gate. It is a photo-diode directly in front of an IR diode. Normally the photodiode outputs a high voltage. But when something blocks the IR light to it, it outputs a lower voltage. The output from photodiode is noisy, though, so we have a schmidt trigger with a capacitor to output clean Digital HIGH/LOW signals. The hardware part of the sensor should output a HIGH value when it detects a fish.

On the software side, we use interrupts to measure the time between when the signal went from LOW-to-HIGH and then back again to HIGH-to-LOW. We use this time to disregard noise. If the time is not too shor or too long (you set time thresholds), we know we detected a fish.

![Image of fish-counter](https://raw.githubusercontent.com/Youssef-Beltagy/Remote_Site_Incubator/master/Images/Fish_Counter.jpg)


**Flow**

This sensor works by counting the number of rotations of a turbine.


**Temperature**

We implemented the code for this sensor but didn't add it to the prototype because the only functional sensor wasn't with us at the time.


**Turbidity**

We have not added The Turbidity sensor yet. This sensor can be calibrated, but it was tested with 5V input. If we can't supply and measure 5V, this sensor might become tricky.


**PH**

We have not added the PH sensor yet.


**Dissolved Oxygen**

This sensor needs Maintainence every month or so.


**SD card module**

We store our comma separated text file in a micro SD card. We need this module.


**RTC**

We added a real-time-clock module to keep track of time even if the microprocessor is rebooted.


**OLED Screen**

We added a small screen to know whether the system is working or not without needing a computer.

