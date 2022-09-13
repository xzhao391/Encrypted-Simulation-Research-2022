This section introduces the implementation of Dyer's SHE to control/autonomous systems using C++ and shows how to generate .dll from Cmake. 

__declspec(dllexport) at the beginning of the function is used to export the function from a DLL. [&] at the beginning of each sub_function to allow access from each other. The negative or Positive value of a number is encrypted separately since there isn't an easy way to change the sign of the cipher text. Due to quantization, each ciphertext should have the same depth(previous times of multiplication) to perform correctly. To return the values, the decrypted values are put into an array. The CMakeLists.txt adds the source files and outputs the shared library called <name>.dll, which can then be used for simulation in FMU. 

/* -------------------------------------------------------------------- Teleoperation System ----------------------------------------------------------- */
        
For the teleopeation system, the dll implements the controller. Inside the controller, the SHE algorithm encrypts the dynamics outputs from the local and remote plants including: accelerations, velocities, displacements, as well as gains. Then, the controller will do the computation in encryption and output the decrypted forces back to the plants. A representative symmetric control scheme utilizing PD feedback with inertial and friction compensation is considered in this case study:

$$\tau_m=(m_{m}-m_{ms}) \ddot{x}_m + k_p (x_s-x_m) +
k_d (\dot{x}_s-\dot{x}_m)+ 0.9 \mu_m sign (\dot{x}_m)$$

$$\tau_s=(m_{s}-m_{ms}) \ddot{x}_s + k_p (x_m-x_s)+
k_d (\dot{x}_m-\dot{x}_s)+ 0.9 \mu_s sign (\dot{x}_s)$$

/* --------------------------------------------------------------------- Duffing Oscillator --------------------------------------------------------------- */        
The Duffing equation is discretized with a step time $T_s$ for the current time $t=k T_s (k=0,1,2,\cdots$) and encrypted by using SHE. The main purpose of the encryption is to treat the parameters, $\alpha, \beta, \gamma, \delta$, as well as $\ddot x$, in the ciphertext. Compared to teleoperation encryption, more powerful sets of security parameters are needed due to the triple multiplications. 

$$Enc (\ddot x_k) = Enc(\gamma) \otimes Enc(\cos(\omega t))$$
        
$$\oplus Enc(-\delta) \otimes Enc(\dot x_k)$$
        
$$\oplus Enc(-\alpha) \otimes Enc(x_k)$$
        
$$\oplus Enc(-\beta) \otimes Enc(x_k^{3})$$
        
$$Enc(\dot x_{k+1})=Enc(T_s) \otimes Enc(\ddot x_k) \oplus Enc(\dot x_k)$$

$$Enc(x_{k+1})=Enc(T_s) \otimes Enc(\dot x_k) \oplus Enc(x_k)$$
