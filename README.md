# Use iproute2 as library

## Why create this project

1. There is no libraries to obtain the network information/statistics/... data from interfaces. 
   You need re-invent the wheel to write the code to get such information with socket interface. maybe you cost much time to write the code to meet the requirement.  

2. _iproute2_ is easy to use tools to operate network in the *inx system. like check the IP, Add/Del/Mod the interface, monitor the working status of the network/interfaces.

3. so, why we don't make _iproute2_ as a standard library?! Here it is! 
   you can use the ip.h as the only header file in your source code, make the same thing like operator on the 'ip' tools.
   
4. Have fun!

## How to compile this

1. libiproute2.x.x.x
   
   x.x.x is the version number of library, which is the same with the lastest tag of offical iproute2.
   - make all (The library libiproute2.x.x.x was located in the iproute2/lib/, the header file <ip.h> was located in the iproute2/include)
   
2. iproute2 "Header files" and "Library file"
   - iproute2_as_lib provide C/C++ API.
   
3. Example
   - In the example folder, I write some user cases how to extract the information from the dump string. and you can make what you want with the api.
   
## Contract    
eshenhu x gmail.com




