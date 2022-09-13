For the teleopeation system, the dll implements the controller. Inside the controller, the SHE algorithm encrypts the dynamics outputs from the local and remote plants including: accelerations, velocities, displacements, as well as gains. Then, the controller will do the computation in encryption and output the decrypted forces back to the plants. A representative symmetric control scheme utilizing PD feedback with inertial and friction compensation is considered in this case study:

$$\tau_m=(m_{m}-m_{ms}) \ddot{x}_m + k_p (x_s-x_m) +
k_d (\dot{x}_s-\dot{x}_m)+ 0.9 \mu_m sign (\dot{x}_m)$$

$$\tau_s=(m_{s}-m_{ms}) \ddot{x}_s + k_p (x_m-x_s)+
k_d (\dot{x}_m-\dot{x}_s)+ 0.9 \mu_s sign (\dot{x}_s)$$
