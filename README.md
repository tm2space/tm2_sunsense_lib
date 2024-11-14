# tm2_sunsense_lib (TM2Space SunSense C library)
![SunSense by TakeMe2Space](https://static.wixstatic.com/media/44d91b_cbcb70695644428fa1a19ff02cfee4a8~mv2.jpg/v1/fill/w_1225,h_689,al_c,q_85,usm_0.66_1.00_0.01,enc_auto/44d91b_cbcb70695644428fa1a19ff02cfee4a8~mv2.jpg)

# About the Library 
This is a C implementation of the TM2S SunSense. It uses the i2c library to communicate with the sensor. The default address of `0x29` on the i2c bus. If you want to optimise the library for other hardware, the customise the `i2c_functions.c` to update the appropiate method of read/write to the i2c bus.

# Communication Protocol
The sensor works on i2c. It returns the `lux_count` as observed by the sensor. The sensor internally updates the `lux_count` every 400ms, esp when there is a substantial change in ambient luminosity. Also the sensor has an internal temperature compensation logic which ensures you do not have to worry about the ambient temperature the sensor is experiencing. Ensure that the operating temperature of the sensor is between -40 to 110 degrees Celcius.
