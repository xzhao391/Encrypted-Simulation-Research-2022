from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
from fmpy.util import plot_result, download_test_file
import numpy as np
import shutil

from fmpy import *
from matplotlib import *
from fmpy.util import plot_result
import numpy as np
from matplotlib import pyplot as plt

from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
from fmpy.util import plot_result, download_test_file
import numpy as np
import shutil

def column(matrix, i):
    return [row[i] for row in matrix]

fmu = 'C:/Users/xzhao/Desktop\Docker_test\encrypted_teleoperation_input.fmu'
dump(fmu)
bit_length_list = [64]
for i in range(len(bit_length_list)):
    result = simulate_fmu(fmu,
                          start_time=0,
                          stop_time=3,
                          step_size=.1,
                          start_values={'bit_length': bit_length_list[i], 'rho': 1, 'rho_': 32, 'delta': .01})
    #print(result)
    #plot_result(result)
    t = column(result, 0)
    out_m = column(result, 1)
    out_s = column(result, 2)
    test = [.5] * 626;
    plt.plot(t, out_m)
    plt.plot(t, out_s)
    plt.legend(["Dataset 1", "Dataset 2"])
    plt.show()




# def column(matrix, i):
#     return [row[i] for row in matrix]
#
# fmu = 'D:\Enc_3\Dyer_dll\encrypted_teleoperation_2021a.fmu'
# dump(fmu)
# result = simulate_fmu(fmu)
# print(result)
# #plot_result(result)
# t = column(result, 0)
# out_m = column(result, 1)
# out_s = column(result, 2)
# test = [.5] * 626;
# plt.plot(t, out_m)
# plt.plot(t, out_s)
# plt.legend(["Dataset 1", "Dataset 2"])
# plt.show()
