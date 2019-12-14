# Progress Report for RSI
### By **Youssef Beltagy** and **Mike Miller**

This is the documentation for the Remote site Incubator (RSI) project.


## Objective 
We want to build a sensor-system to observe and document the hatching conditions of fish. For now, we know that we need to deploy a prototype for Coho salmon sometime in January of 2020. Later on, we expect that the sensor system would be used to observe Kokanee salmon in the Lake Washington/Sammamish watershed. This project is sponsored by [Jeff Jensen, Ph.D](https://www.uwb.edu/biological-sciences/faculty/biology/jjensen).


## Motivation
Jeff explains, in his biography, "Kokanee populations crashed in Lake Washington in the 1920’s, and in Lake Sammamish in the 1970’s, to the point that native kokanee are known to exist only in a few tributaries of Lake Sammamish." This project is an attempt to help Jeff get more data on salmon, and automate the data-collection process.

We believe this project is important (and are commited to it) because there is currently nothing similar for it, so what we make will most likely be used and make an effect. Furthermore, the alternative to the RSI is going down to the incubator and staying there during sunset hours (most of the salmon leave the incubator at sunset) to count the salmon as they leave the incubator.

This project should allow Jeff (and hopefully other researchers) to know the exact count of the fish (instead of an approximation from the sunset hours) and the living conditions of the fish while on campus.


## Specifications
Jeff wants a remote sensor system that makes readings and sends them to him remotely, so he doesn't have to go down to the incubator to know how the salmon fish are doing (thus the "remote site" in the project's name). Through conversing with him, we identified the quantities and features that he is interested in.

Jeff wants to know these quantities (ordered in terms of priority).
1. The number of fish that manage to hatch
2. The waterflow into the incubator
3. The Temperature inside the incubator
4. The Dissolved Oxygen content of incubator
5. The turbidity of the water in the incubator
6. The PH of the water in the incubator

Jeff wants to be able to install the incubator where our fish counter would not have access to WiFi or power. For that we have to solve two technical problems.
1. Communication without WiFi
2. Access to power without the power-grid

Ideally, we would also like to make a friendly user interface, but our focus is for the RSI to output a comma delimited file that can be used by data analysis software.


## Progress
In this quarter, we managed to build the custom fish-counter sensor and wrote the code for it. We tested the fish-counter to the best of our abilities. The only remaining tests are with a dead fish (to simulate a living one) and testing on the field.

We also made a prototype for the data collection system, using an arduino Mega, that we can deploy (but is far from perfect). We currently have the first two sensors, the fish-counter and the flow meter. The sensors' data is time-stamped with a real-time-clock module, and saved to an SD card. To get feedback about the system when we are on-site, we have a small monitor that shows what the last readings were.

We demoed what we had to Jeff and got his feedback. Jeff explained that the fish-counter might be too narrow and can thus cause the incubator to overfill with water and overflow. Thus, we will have to widen the 3d-printed tube of fish-counter and use multiple of them. Jeff told us that the next most important thing to him now is to add the remote functionality. 

We went with Jeff to see where the first RSI (the one that will be deployed in January) will be located. Fortunately, for the first deployment, we will have access to a power socket so we can focus on the data-collection and transmission system for now. When we have a satisfactory data collection and transmission system, we will focus on finding a solution to the power problem.


# Appendix
> anything else we want to say

## Sensor Choice reasoning and current progress
> explanation of why we chose every specific sensor and any information needed to know about the sensor. Don't worry about the technical details. It is too early for that.

**Fish Counter**

**Flow**

**Temperature**

**Turbidity**

**PH**

**Dissolved Oxygen**

**SD card module**

**RTC**

**OLED Screen**

