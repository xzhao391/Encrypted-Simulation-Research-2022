This section introduces the implementation of Dyer's SHE to control/autonomus system using C++ and shows how to generate .dll from Cmake. 

The dll can implement different control/autonomus system while separting them from the FMU’s internal operation. This architecture enables the user
to exchange a particular cypher.dll for a cypher.dll that implements the same interface for testing different cryptographic systems. The interface serves as a convenient test bed for evaluating the feasibility of different encrypted cyberphysical systems.

For the teleopeation system, the dll implements the controller. Inside the controller, the SHE algorithm encrypts the dynamics outputs from the local and remote plants including: accelerations, velocities, displacements, as well as gains. Then, the controller will do the computation in encryption and output the decrypted forces back to the plants. A representative symmetric control scheme utilizing PD feedback with inertial and friction compensation is considered in this case study:

$$\tau_m=(m_{m}-m_{ms}) \ddot{x}_m + k_p (x_s-x_m) +
\nonumber\\&k_d (\dot{x}_s-\dot{x}_m)+ 0.9 \mu_m \sign (\dot{x}_m)$$
     
This section also applies the SHE approach to the Duffing oscillator that includes a third degree of polynomials term. The duffing equation is represented by 

