# Encrypted-Simulation-Research-2022

The goal of the research is to establish functional mockup units (FMU) co-simulation methods to simulate and evaluate encrypted dynamic systems using somewhat homomorphic encryption (SHE). The proposed approach encrypts the entire dynamic system expressions including: model parameters, state variables, feedback gains, and sensor signals, and perform computation in the ciphertext space to simulate dynamic behaviors or generate motion commands to servo systems. The developed FMU co-simulation helps analyze the relationship between security parameters and performance.

The modular structure of FMU may be used in conjunction with the aforementioned cypher-interface, to create an encrypted cyber-physical testbed. A particular FMU system is paired with different implementations of cypher.dll to test which cypher/securityparameters are best compatible with the particular system. An example of this workflow can be seen in Fig. 1. 


<img src="https://github.com/xzhao391/Encrypted-Simulation-Research-2022/blob/main/Picture/testbed-flow.png" width="600" height="400">

<p align="center">
Fig. 1 Simulink implementation of Teleoperation system dynamics
</p>
