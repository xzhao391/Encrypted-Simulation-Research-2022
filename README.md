# Encrypted-Simulation-Research-2022
FMU, Simulink, Homomorphic Encryption, Teleoperation

FMU 

FMI is an open standard for exchanging dynamical simulation models between different tools in a standardized format. The functional Mock-up Unit is a zip file that contains a simulation model that adheres to the FMI standard. Therefore, the model can be reused and repurposed for different applications.

FMU includes an XML file that defines the structure and binary files that implements the function. Since binary files can only be run on the platform they are compiled for, most FMUs are restricted to running on a single platform such as Windows 64-bit or Linux 32-bit [1]. 
 

Encryption Homomorphic 

The controller architecture and motor signals are processed in homomorphic encryption to avoid data leaking. The homomorphic encryption is written in C++ due to the large data size. They are performed in a single equation of “control” that returns an array of master and slave torque, as shown in X1. The control equation includes all the subfunctions and runs the control scheme. The subfunctions have the format of [&] to access data to other subfunctions, as shown in X2.  

![image](https://user-images.githubusercontent.com/107379730/175787018-4063cc50-936f-492a-a23a-62c76abf9049.png) 

                                                                 X1. Control equation

![image](https://user-images.githubusercontent.com/107379730/175787025-4a1805e9-8207-404b-a866-254e34cd3d00.png)  

                                                                 X2. Subfunction format

Since the Simulink S-function only has compile version of C++14, the control scheme has to be exported to dll that are compiled in C++20. To export in DLL, the control scheme was Extern “C” was used to ensure that the function names are un-mangled, so that the binary files are exported with unchanged names. 


Reference 
[1] https://www.modelon.com/functional-mock-up-interface-fmi/
