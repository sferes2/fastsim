#! /usr/bin/env python
import Options;
import commands

def set_options(opt) : pass

# def detect_sdl(conf):
#     env = conf.env
#     opt = Options.options
#     ret = conf.find_program('sdl-config')
#     conf.check_message_1('Checking for SDL (optional)')
#     if not ret:
#         conf.check_message_2('not found', 'YELLOW')
#         return 0
#     conf.check_message_2('ok')
#     res = commands.getoutput('sdl-config --cflags --libs')
#     config_c.parse_flags(res, 'SDL', env)
#     return 1

# def detect(conf):
#     return detect_sdl(conf)

def configure(conf) : pass
#    conf.env['CPPPATH_SDL'] = commands.getoutput('sdl-config --cflags')
#    conf.env['LIBPATH_SDL'] = commands.getoutput('sdl-config --libs')
    


def build(bld):
    uselib_ = 'BOOST'
    model = bld.new_task_gen('cxx', 'staticlib')
    model.source = 'display.cpp laser.cpp main.cpp map.cpp radar.cpp light_sensor.cpp robot.cpp linear_camera.cpp'
    model.includes = '. ../../'
    model.target = 'fastsim'
    model.uselib = 'SDL BOOST'

    test_fastsim = bld.new_task_gen('cxx', 'program')
    test_fastsim.source = 'test_fastsim.cpp'
    test_fastsim.includes = '. ../../'
    test_fastsim.uselib_local = 'sferes2 fastsim'
    if Options.options.apple:
        test_fastsim.uselib = 'SDL'
    else:
        test_fastsim.uselib = 'BOOST_UNIT_TEST_FRAMEWORK SDL'
        test_fastsim.unit_test = 1

    test_fastsim.target = 'test_fastsim'


    fastsim_keyboard = bld.new_task_gen('cxx', 'program')
    fastsim_keyboard.source = 'fastsim_keyboard.cpp'
    fastsim_keyboard.includes = '. ../../'
    fastsim_keyboard.uselib_local = 'sferes2 fastsim'
    fastsim_keyboard.uselib = 'SDL'        
    fastsim_keyboard.target = 'fastsim_keyboard'




