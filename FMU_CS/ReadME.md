FMU Co-Simulation

The teleoperation system is separated into three parts: master, control, and slave, and each part is exported into FMU separately. 

The tele.py loads all three FMUs and identifies the variables to show in the result, the FMU model, and builds the connection among the models by connecting the variables. Then the configuration is loaded into a new FMU, teleoperation.fmu in this case.

This FMU container allows connections between the inputs and the outputs of the multiple FMUs and run in a parallel way. However, this causes time delays during communication. In this case, the master transfer the position data to the controller, which has a one-time step delay. The controller then transfers the tau_s to the slave, and the salve returns the position to controller, which has a two-time step delay. Finally, the controller return tau_m return to the master. So, there is a total delay of 4-time step. Therefore, if we can run the model with the time step of .02 s in Simulink, we have to run the model with .005 s in the FMU container.  
