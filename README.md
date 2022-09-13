# Encrypted-Simulation-Research-2022

The goal of the research is to establish functional mockup units (FMU) co-simulation methods to simulate and evaluate encrypted dynamic systems using somewhat homomorphic encryption (SHE). The proposed approach encrypts the entire dynamic system expressions including: model parameters, state variables, feedback gains, and sensor signals, and perform computation in the ciphertext space to simulate dynamic behaviors or generate motion commands to servo systems. The developed FMU co-simulation helps analyze the relationship between security parameters and performance.

The modular structure of FMU may be used in conjunction with the aforementioned cypher-interface, to create an encrypted cyber-physical testbed. A particular FMU system is paired with different implementations of cypher.dll to test which cypher/securityparameters are best compatible with the particular system. An example of this workflow can be seen in Fig. 1. 

<p align="center">
<img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/testbed-flow.png" width="600" height="150">
</p>

<p align="center">
 (a) Testbed Flow: Evaluation scheme to find successful security parameters, where ε is the measured error, εT the error tolerance, τ the measured simulation-cycle time, and τT the simulation-cycle time tolerance.
 </p>
 
 <p align="center">
 <img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/testbed-staging.png" width="600" height="180">
</p>

<p align="center">
Testbed staging: Construct system from FMU composition, and select the cypher to be tested. Here the “Test Bed” blockrefers to Fig. 1a.
 </p>

<p align="center">
Fig. 1: FMU/Cypher test-bed: System simulation is constructed by linking FMUs chosen from a remote repository. A cypher is then selected to be tested for compatibility with the given FMU system.
</p>

/* --------------------------------------------------------------------- Duffing Oscillator --------------------------------------------------------------- */
The duffing equation is represented by $$\ddot x + \delta \dot x + \alpha x + \beta x ^{3}= \gamma \cos(\omega t)$$, where the coefficients $\delta, \alpha, \beta, \gamma, \omega$  denote system damping, linear stiffness, amount of non-linearity in the restoring force, amplitude of the driving force, and angular frequency of the force.

The Duffing equation is discretized with a step time $T_s$ for the current time $t=k T_s (k=0,1,2,\cdots$) and encrypted by using SHE, as shown in Fig. 3. The main purpose of the encryption is to treat the parameters, $\alpha, \beta, \gamma, \delta$, as well as $\ddot x$, in the ciphertext. Compared to teleoperation encryption, more powerful sets of security parameters are needed due to the triple multiplications. 

 <p align="center">
 <img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/duffing-fmu_Ueda.png" width="600" height="180">
</p>

<p align="center">
Fig. 1: All parameters in the duffing equations were encrypted and ran in FMU, where $$F=\cos(\omega t)$$ is the forcing function, and $$x_k = x(k T_s)$$.
</p>
