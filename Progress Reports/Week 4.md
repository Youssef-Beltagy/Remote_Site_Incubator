## Week 4 Report (2/1 - 2/7)

### Deadline 2/7/2020 (EOD)

Delayed the deadline because both Mike and I have exams on Tuesday.



We changed our objective. Because we might not be able to buy a 3G cellular network module before deployment, we will focus on getting a prototype that works with Wifi for now and add the cellular network once we are confident we can give Jeff a prototype whenever he asks for it.



I discovered the existence of Matlab's ThingSpeak, so we will use that for our server side.



### Objectives

- [x] WiFi + ThingSpeak

- [ ] ADD low power mode

- [ ] ADD GSM module and remote functionality

- [ ] Test low power mode with GSM module

- [ ] ADD the PH Sensor

- [ ] Begin next week's report

  

### Possibly

- [ ] ADD PH Sensor

- [x] See If I can make Classes and use OOP with ISR instead of this namespace festival

  No conclusion yet, but it is too early to worry about that now.

- [ ] ADD Dissolved oxygen sensor



### Notes

I want a pin to control the current going to the sensors. Apparently, I can disconnect them and reconnect them without issues.

Apparently, the fishcounter (implemented as volatile int that is incremented by an ISR) doesn't work in light sleep mode. My guess is this is because the processor is sleeping so the ISR is not working. A solution would be to set the interrupt pin as a wakeup signal. My concern would be whether the esp32 can wakeup and notice the interrupt at the same time. It may not be able to do that.

I mean that by the time the esp32 wakes up, the signal would already be high. Then the ISR won't be triggered and the fishcount would be incorrect.

What I want would be for the esp32 to wakeup and trigger the ISR at the same time. Then the ISR would increment the fish and put the esp32 to sleep again.