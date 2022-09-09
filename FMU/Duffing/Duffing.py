from fmpy import *
from matplotlib import pyplot as plt

def column(matrix, i):
    return [row[i] for row in matrix]

fmu = 'D://Enc_3//Git//FMU//duffing_new.fmu'
result = simulate_fmu(fmu,output_interval=.03)
print(result)
x = column(result, 1)
x_dot = column(result, 2)
plt.plot(x, x_dot)
plt.show()

