from fmpy import *
from matplotlib import *
from fmpy.util import plot_result
import numpy as np
from matplotlib import pyplot as plt

from fmpy import simulate_fmu, plot_result
from fmpy.fmucontainer import create_fmu_container, Variable, Connection, Configuration, Component, Unit, BaseUnit, DisplayUnit, SimpleType
from fmpy.validation import validate_fmu
from fmpy.util import validate_signal, read_csv

# fmu1 = 'D:/Enc_3/FMU_test/add1.fmu'
# dump(fmu1)
# fmu2 = 'D:/Enc_3/FMU_test/add2.fmu'
# dump(fmu2)
# fmu3 = 'D:/Enc_3/FMU_test/add3.fmu'
# dump(fmu3)

# fmu_ball = 'D:/Enc_3/FMPy-main/tests/resources/Ticker.fmu'
# dump(fmu_ball)
def test_create_fmu_container_me(resources_dir):

    configuration = Configuration(
        parallelDoStep=True,
        variables=[
            Variable(
                type='Real',
                variability='discrete',
                causality='output',
                initial='calculated',
                name='xm_discrete',
                mapping=[('master', 'xm_discrete')]
            ),
            Variable(
                type='Real',
                variability='discrete',
                causality='output',
                initial='calculated',
                name='xs_discrete',
                mapping=[('slave', 'xs_discrete')]
            ),
            Variable(
                    type='Real',
                    variability='discrete',
                    causality='output',
                    initial='calculated',
                    name='tau_m',
                    mapping=[('controller', 'tau_m')]
            ),
            Variable(
                    type='Real',
                    variability='discrete',
                    causality='output',
                    initial='calculated',
                    name='tau_s',
                    mapping=[('controller', 'tau_s')]
            ),
            Variable(
                    type='Real',
                    variability='continuous',
                    causality='output',
                    initial='calculated',
                    name='a',
                    mapping=[('master', 'a')]
            ),
            Variable(
                    type='Real',
                    variability='continuous',
                    causality='output',
                    initial='calculated',
                    name='b',
                    mapping=[('controller', 'b')]
            ),
            Variable(
                    type='Real',
                    variability='continuous',
                    causality='output',
                    initial='calculated',
                    name='c',
                    mapping=[('slave', 'c')]
            ),
        ],
        components=[
            Component(
                filename=resources_dir + '/master.fmu',
                interfaceType='CoSimulation',
                name='master'
            ),
            Component(
                filename=resources_dir + '/controller.fmu',
                interfaceType='CoSimulation',
                name='controller'
            ),
            Component(
                filename=resources_dir + '/slave.fmu',
                interfaceType='CoSimulation',
                name='slave'
            ),
        ],
        connections=[
            Connection('master', 'xm_discrete', 'controller', 'xm_discrete'),
            Connection('master', 'dxm', 'controller', 'dxm'),
            Connection('master', 'ddxm', 'controller', 'ddxm'),
            Connection('controller', 'tau_m', 'master', 'tau_m'),
            Connection('controller', 'tau_s', 'slave', 'tau_s'),
            Connection('slave', 'xs_discrete', 'controller', 'xs_discrete'),
            Connection('slave', 'dxs', 'controller', 'dxs'),
            Connection('slave', 'ddxs', 'controller', 'ddxs'),

            Connection('master', 'a', 'controller', 'a'),
            Connection('controller', 'b', 'slave', 'b'),
        ]
    )

    filename = 'teleoperation.fmu'

    create_fmu_container(configuration, filename)

    problems = validate_fmu(filename)

    assert not problems

    result = simulate_fmu(filename, start_time=0, stop_time=10, output_interval=.001)

    plot_result(result)


dir = 'D:/Enc_3/FMU_test'
test_create_fmu_container_me(dir)
