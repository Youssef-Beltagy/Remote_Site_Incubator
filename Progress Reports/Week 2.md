## Week 2 Report (1/18 - 1/24)

### Deadline 2/2/2020 (EOD)

The 2's are a coincidence. This is the deadline by which I should have added all the modules I want to add and figured out their connections. I should have also finished any low-power mode thing by then.

### Objectives

- [ ] ADD PH Sensor
- [x] ADD Temperature Sensor
- [x] Clean the Code a little
- [ ] Be prepared for the GSM module and Sim card (ideally, I want to add them, but they will come in the middle of the week when I'm too busy)
- [x] Meet Jeff
- [ ] Begin next week's report



### Possibly

- [x] Test esp32 again (mine/mike's) with (old/new) sd cards



### Preparations for Jeff's meeting

- Report current status
- What are his current priorities?
- Is the updated design of the fish counter acceptable or does he foresee issues?
- Multiple temp sensors? Average? Measure in different locations?
- One more time, is it safe to add a flow meter with a narrower cross sectional area than the pipes before the incubator's intake pipe?
- I can store all the fish without losing any data, but with a significantly more annoying system (rotate through EEPROM). Does he want that?
- Do we have money?
- When will he deploy?
- Will giving him a cleaned up version of the report help with writing the grant?
- What does he think of the report?
- Mention Lana's grading issue + suggest solutions (office hours, check email, schedule a meeting)

##### ASK Mike before meeting

- [ ] What does he think about parallel programming? It can be fun, but I don't think we need it. It will complicate everything.
- [ ] I broke your esp32, yay! It wasn't my fault. I swear. I treated it normally. The female usb port was not soldered properly, it broke off. I bought a replacement from Amazon.



### Notes

Yay, I managed to switch back to the esp32. Which means that the most up to date code is the Sensors Network.ino in the esp32 code Folder.

I cleaned the code a little, but I'm having trouble using classes because of the Interrupt service routines. For now, I'm using namespaces. I want to change that in the future. I'm having trouble uploading the code to the esp32 after it compiles. I'm assuming my computer is on drugs again.