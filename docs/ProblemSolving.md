# Problem Solving

A friend advised me to keep a running record of the problems I face and how I solved them. While this is already late in the project, nothing is too late.

Since this is not an official document, I do not guarantee I will update or quality-proof it.

## Wakeup time resets between boots

The wakeup time resets to its default value every boot. This means that the esp will always sleep the sleepDuration when it is woken up. I confirmed this by printing wakeup timestamp in every boot. This would mean that the recording intervals will not be regular and the esp32 might have to use wifi every time it wakes.

The esp32 will be more power efficient and have better defined behavior if I fix this bug. So I will.

I think the problem is wakeupTime is not volatile so it might be edited in the cache but not saved in memory. When I tried to make it volatile, I got the errors seen below:

```
In file included from include/Settings.h:54:0,
                from src\main.cpp:281:
include/FishCounterAndSleep.h: In function 'void FishCounterAndSleep::process_wakeup()':
include/FishCounterAndSleep.h:36:15: error: binding 'volatile DateTime' to reference of type 'const DateTime&' discards qualifiers
    if(now >= wakeupTime){
            ^
```

So I can't make wakeupTime volatile. To circumvent that, I made a struct that contains all the necessary information to construct a DateTime object. I made an object of this class and made it volatile. At the beginning of every boot, I copy the values from this object and put it in wakeupTime. At the end of every boot, I set this object to wakeupTime.


## Syncronize fishCount

I may have to syncronize fishCount with a mutex.

## 6/24/2021 Restarting the project in Summer 2021

That friend was a genius. What little I wrote helped me remember one of the major bugs I faced. I also know that the way it is handled doesn't make sense.

