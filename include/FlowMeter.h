
// //========================================================++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// // I need to solve this namespace issue because it is crippling. I want to be able to make classes with instances.
// namespace FlowMeter{

//     uint8_t secToAvg = 1; // seconds to measure flow and get average
    
//     uint8_t flowPin = 2; // flowmeter pin with default = 2 

//     static volatile uint16_t flowPulses = 0; // number of flow-meter pulses

//     void incrementPulses(){       
//         ++flowPulses;
//     }

//     float getFlow(){
  
//         flowPulses = 0;// reset counter

//         pinMode(FlowMeter::flowPin, INPUT);
        
//         attachInterrupt(digitalPinToInterrupt(FlowMeter::flowPin), incrementPulses, RISING);

//         // Ideally, I'd like to do something concurrently-------------------------------------------------------------------
//         // point to consider: I can't have two flow meters working at the same time becaus flowPulses is static.
//         // If I do that, I will get the sum of the two flows.
//         delay(1000 * secToAvg);// wait some time and get the average
        
//         detachInterrupt(digitalPinToInterrupt(FlowMeter::flowPin));

//         float flow = (float) flowPulses/ (float) (secToAvg);

//         flowPulses = 0;
        
//         return flow;
//     }

//     void setFlowMeterValues(uint8_t tmpflowPin, uint8_t tmpsecToAvg){

//         FlowMeter::secToAvg = tmpsecToAvg;
//         FlowMeter::flowPin = tmpflowPin;
//         FlowMeter::flowPulses = 0;

//         pinMode(FlowMeter::flowPin, INPUT);
      
//     }

// };

