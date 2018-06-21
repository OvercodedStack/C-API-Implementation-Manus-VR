# C++ API Implementation of Manus VR  
Author: **Esteban Segarra**  
Primary mantainer: **Esteban Segarra**

This is a parallel project running alongside the C# implementation of the Manus VR hand set, which can be found [here](https://github.com/OvercodedStack/C-Sharp-API-Implementation-ManusVR). This API aims to be as efficient as possible while combining the data collected from the Manus VR devices and stringing them together into a data structure that's more sensible than 
what the Manus VR SDK provides at present (Manus VR SDK in use: v1.1.1). The API can work with one or two hands simultaneously connected to the computer. 


## Requirements:

Manus VR SDK V1.1.1  
Visual Studio 2017 or C++ compatible IDE

## Use 
This API was OOP designed with the use of the header-only SDK provided by Manus. The program is split into 4 header and implementation files as stated below: 


- Finger.cpp/h  *A finger class for each manus hand. Contains data relating to raw, quaternion/vector data, and Manus Profile data.*
- Manus_hand_obj.cpp/h *The representation of the Manus VR hand itself. Contains arrays of finger data, positional, and wrist data*
- Manus_interpreter.cpp/h *Concerns itself with reading in the data collected from the SDK and turning it into data structure using one of the previous data formats.* 
- ManusHandConverter.cpp/h *A breif example program that utilizes the data collected and outputs to a command prompt. The Main loop contains a couple of already filled-in implementations for your convenience.*

In addition, there is a previous implementation by Megan Zimmerman that utilized the SDK previously. 


## Aknowledgements

- Megan Zimmerman for providing the initial code
- Manus VR
- The NIST SURF program
