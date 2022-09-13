This section applies the SHE approach to the Duffing oscillator that includes a third degree of polynomials term. The duffing equation is represented by
$$\ddot x + \delta \dot x + \alpha x + \beta x ^{3}= \gamma \cos(\omega t)$$, where the coefficients $\delta, \alpha, \beta, \gamma, \omega$  denote system
damping, linear stiffness, amount of non-linearity in the restoring force, amplitude of the driving force, and angular frequency of the force. 

The equation is discretized with a step time Ts for the current time t = kTs(k = 0, 1, 2, · · · ) and encrypted by using SHEThe main purpose of the encryption is to treat the parameters, $\alpha, \beta, \gamma, \delta$, as well as $\ddot x$, in ciphertext. 

$$Enc(\dot x_{k+1})=Enc(T_s) \otimes Enc(\ddot x_k) \oplus Enc(\dot x_k)$$

$$Enc(x_{k+1})=Enc(T_s) \otimes Enc(\dot x_k) \oplus Enc(x_k)$$
