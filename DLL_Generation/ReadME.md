This section introduces the implementation of Dyer's SHE to control/autonomous systems using C++ and shows how to generate .dll from Cmake. The sub_folders explain the implemented dynamics for each dll. 

__declspec(dllexport) at the beginning of the function is used to export the function from a DLL. [&] at the beginning of each sub_function to allow access from each other. The negative or Positive value of a number is encrypted separately since there isn't an easy way to change the sign of the cipher text. Due to quantization, each ciphertext should have the same depth(previous times of multiplication) to perform correctly. To return the values, the decrypted values are put into an array. The CMakeLists.txt adds the source files and outputs the shared library called <name>.dll, which can then be used for simulation in FMU. 


