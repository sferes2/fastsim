#! /usr/bin/env python
from waflib.Configure import conf

@conf
def configure(conf) :
    print 'configuring'
    sdl = conf.check_cfg(package='sdl',
        args='--cflags --libs',
        msg="Checking for SDL (optional)",
        uselib_store='SDL',
        mandatory=False)
    if sdl:
        conf.env['CXXFLAGS'] += ['-DUSE_SDL']

def build(bld):
    bld.stlib('cxx', 'staticlib',
        source = 'display.cpp laser.cpp main.cpp map.cpp radar.cpp light_sensor.cpp robot.cpp linear_camera.cpp',
        includes = '. ../../',
        target = 'fastsim',
        uselib = 'SDL BOOST')

    bld.program('cxx', 'program',
        source = 'test_fastsim.cpp',
        includes = '. ../../',
        use = 'sferes2 fastsim',
        uselib = 'BOOST BOOST_UNIT_TEST_FRAMEWORK SDL',
        target = 'test_fastsim')


    bld.program('cxx', 'program',
        source = 'fastsim_keyboard.cpp',
        includes = '. ../../',
        use = 'sferes2 fastsim',
        uselib = 'SDL',
        target = 'fastsim_keyboard')
