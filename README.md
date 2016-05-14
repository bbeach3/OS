# OS
Final version of OS course project


In my OS course, a major project, and the bulk of the class, was devoted to developing an OS from a minimally provided structure.

The project was broken down into 6 modules. 
Module 1 - basics. Keyboard functionality, timekeeping, and basic string functions were implemented. 
Module 2 - Process Control Blocks. Implemented these PCBs, which track priority and order-of-arrival of processes, for determining their "fair" flow in a time-share system, as well as the implementation of methods that allow them to function.
Module 3/4 - Combined set of goals: Apply the products of Mod2 to an actual time-share system of our own development (goal 1), using custom-built interrupts on the machine level.
Module 5 - Memory Control Blocks. Chunks of allocated memory, ready for use storing things required by the PCBs. As memory is needed, the first valid MCB is identified. If it is sufficiently larger than the needed size, it is split into parts, and the unused portion is inserted into the list of available blocks. When multiple adjacent blocks are free, they are fused back into larger blocks. 
Module 6 - FAT12 file system. I'll be honest. Crunch time was hitting pretty hard at this point, so I barely recall any specifics. 


Anyone that has participated in a large-scale project will understand the difficulty involved in definitively saying who was responsible for what. In lieu of spending a few hours digging through commits and merges to determine what I made, I'm going to lay down a few guidelines.
*If it involves Mod2 or Mod5, I probably did it.
*If it involves 3/4, there's a reasonably high probability that I did it.
*Due to the stress involved at crunch time, I have no recollection of what I did for mod 6, but it's there in the commit logs if you really need to know.
*In mod1, it's simple: the bulk of my share of the work was implementing the keyboard functionality. I touched up a string function or two, but not much. 
