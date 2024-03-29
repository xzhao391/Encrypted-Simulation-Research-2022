This section introduced the implementation of nonlinear dynamics of the plants by using Simulink, the interface between the Simulink S function and Dll, and how to export FMU from Simulink. 

/* -------------------------------------------------------------------- Teleoperation System ----------------------------------------------------------- */

Inside the teleoperation system, two control loops of the local and remote plants are intertwined. Let the coefficients $m$, $b$, $\mu$, $\tau$, and $f$ denote system mass, damping, friction coefficient, actuator force, and external force; furthermore, let the subscript $m$ and $s$ denote the local and remote system.
The plant dynamics is modeled as:
     $$m_m \ddot{x}_m + b_m \dot{x}_m + \mu_m sign (\dot{x}_m) = \tau_m + f_m$$
     $$m_s \ddot{x}_s + b_s \dot{x}_s + \mu_s sign (\dot{x}_s) = \tau_s - f_s$$
The equation is implemented in Simulink as shown in Fig. 1.

<p align="center">
<img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/Teleoperation_Simulink.png" width="600" height="400">
</p>

<p align="center">
Fig. 1: Simulink implementation of Teleoperation system dynamics
</p>

/* --------------------------------------------------------------------- Duffing Oscillator --------------------------------------------------------------- */

The duffing equation is represented by $$\ddot x + \delta \dot x + \alpha x + \beta x ^{3}= \gamma \cos(\omega t)$$, where the coefficients $\delta, \alpha, \beta, \gamma, \omega$  denote system damping, linear stiffness, amount of non-linearity in the restoring force, amplitude of the driving force, and angular frequency of the force. The discretized equation is implemented in Simulink as shown in Fig. 2.

<p align="center">
<img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/Duffing_Simulink.png" width="600" height="400">
</p>

<p align="center">
Fig. 2: Simulink implementation of Duffing equations
</p>

/* ----------------------------------------------------------------- Simulink/C++ Interface ------------------------------------------------------------ */

With the complexity of the encrypted control scheme, it is more efficient to write the control scheme in C++ and access it by Simulink through the S-function block. The S-function builder integrates a C/C++ code by building a C MEX S-function. Inside the s function, the S-function will load the previously compiled dll. _stdcall that tells the compiler the rules for setting up the stack, pushing arguments, and getting a return value. LoadLibrary()/dlopen() is used to load the library, GetProcAddress()/dlsym() is used to load the symbols and call the function.

     
In a real-time environment, generic API calls can be unacceptably slow, especially when many solution steps are involved. The code generator can speed up S-functions in standalone applications that it generates by embedding user-written algorithms within auto-generated functions, rather than indirectly calling S-functions via the generic API. This form of optimization is called inlining. TLC inlines S-functions, resulting in faster, optimized code[1]. To inline the S-function, clicks on the generating Wrapper TLC while building the S-function, as shown in X2.  

/* ----------------------------------------------------------------------- FMU Export ------------------------------------------------------------------ */

To export the Simulink into FMU, in the Model settings, check the fixed-step solver and change the system target file to ert_shrlib, which generates a shared library target. Then, it is ready to export to FMU after setting the time step and initial conditions



Reference: 
[1] https://www.mathworks.com/help/rtw/tlc/inlining-s-functions-with-tlc.html
