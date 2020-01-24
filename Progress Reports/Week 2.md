## Week 2 Report (1/18 - 1/24)

### Deadline 2/2/2020 (EOD)

The 2's are a coincidence. This is the deadline by which I should have added all the modules I want to add and figured out their connections. I should have also finished any low-power mode thing by then. The fish come out at the end of February or beginning of March, and Mike needs time to figure out his power calculations, design a PCB, and order it.

We also need to make a case and BOM for the RSI. Ideally we want to get everything we need by 2/9/2020, so Mike can have time to measure the components, design a PCB, and get it from China. I will spend that time helping mike, learning how to design a PCB, improving the code, and maybe designing a fancy case (or resorting to a lunch box--they are waterproof. Why would I care for more?).

### Objectives

- [ ] ADD PH Sensor
- [x] ADD Temperature Sensor
- [x] Clean the Code a little
- [ ] Be prepared for the GSM module and Sim card (ideally, I want to add them, but they will come in the middle of the week when I'm too busy)
- [x] Meet Jeff
- [x] Begin next week's report



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
- [ ] I broke your esp32, yay! It wasn't my fault. I swear. I treated it with love. The female usb port was not soldered properly; it broke off. I bought a replacement from Amazon.



### Notes

Yay, I managed to switch back to the esp32. Which means that the most up to date code is the Sensors Network.ino in the esp32 code Folder.

I cleaned the code a little, but I'm having trouble using classes because of the Interrupt service routines. For now, I'm using namespaces. I want to change that in the future. I'm having trouble uploading the code to the esp32 after it compiles. I'm assuming my computer is on drugs again.

My computer was on drugs. My esp32 has this annoying issue in which I have to press the boot button while uploading. Even that didn't work, but when my computer had a good night, everything was fine the next morning! Voila, Magic!

Okay, the SIM card is here 1/23/2020.



### Notes After Meeting Jeff

- The fish move out of the incubator in late February/Early march
- If we fail, we can still deploy it (with no fish) until may as a simulation
- Ideally we should make a kit that costs 400 Dollars or Less
- Time is the highest priority (money is the second)--typical
- Have mike show the mesh fish counter to see if it will injure the fish.
- one temp sensor is enough (could try two for variation in temperature because of flow)
- Prepare a Kit for sophomore/Junior EE engineer who can make it their projects to assemble this and hopefully improve it.