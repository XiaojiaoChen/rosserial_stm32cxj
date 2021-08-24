#!/usr/bin/env python

#####################################################################
# Software License Agreement (BSD License)
#
# Copyright (c) 2018, Kenta Yonekura (a.k.a. yoneken), Federica Di Lauro (a.k.a fdila)
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of Willow Garage, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

THIS_PACKAGE = "rosserial_stm32cxj"

__usage__ = """

This package generates files used in your STM32 Project for ROS serial communication.
The aim of this package is try not to mess your STM32 project file organization. 

All files are within the generated rosserialInc/ folder, therefore, you only need to manually include this folder in your STM32 include search path.
Method: right click this folder in your STM32CUBEIDE project explorer, click add to inlcude path>

Usage: 

1. anywhere, run:

rosrun rosserial_stm32cxj make_libraries.py .

Merge the generated Inc/ folder to the target STM32 project Inc folder

add the rosserialInc/ folder to your inlcude search path

or 

2. Inside a STM32 Project folder that contains a subfolder Inc/, direct run the command

rosrun rosserial_stm32cxj make_libraries.py .

add the rosserialInc/ folder to your inlcude search path

"""

__postWords__ = """

Successfully generate rosserial_stm32 libraries in Inc/rosserialInc/.

YOU NEED TO:

Add the rosserialInc/ folder to your inlcude search path of your STM32 Project

"""

import rospkg
import rosserial_client
from rosserial_client.make_library import *

# for copying files
import shutil
import os

ROS_TO_EMBEDDED_TYPES = {
    'bool'    :   ('bool',              1, PrimitiveDataType, []),
    'byte'    :   ('int8_t',            1, PrimitiveDataType, []),
    'int8'    :   ('int8_t',            1, PrimitiveDataType, []),
    'char'    :   ('uint8_t',           1, PrimitiveDataType, []),
    'uint8'   :   ('uint8_t',           1, PrimitiveDataType, []),
    'int16'   :   ('int16_t',           2, PrimitiveDataType, []),
    'uint16'  :   ('uint16_t',          2, PrimitiveDataType, []),
    'int32'   :   ('int32_t',           4, PrimitiveDataType, []),
    'uint32'  :   ('uint32_t',          4, PrimitiveDataType, []),
    'int64'   :   ('int64_t',           8, PrimitiveDataType, []),
    'uint64'  :   ('uint64_t',          8, PrimitiveDataType, []),
    'float32' :   ('float',             4, PrimitiveDataType, []),
    'float64' :   ('float',             4, AVR_Float64DataType, []),
    'time'    :   ('ros::Time',         8, TimeDataType, ['ros/time']),
    'duration':   ('ros::Duration',     8, TimeDataType, ['ros/duration']),
    'string'  :   ('char*',             0, StringDataType, []),
    'Header'  :   ('std_msgs::Header',  0, MessageDataType, ['std_msgs/Header'])
}

# need correct inputs
if (len(sys.argv) < 2):
    print(__usage__)
    exit()
    
# valid output path
path = sys.argv[1]
if not (os.path.isdir(path)):
    print("%s is not a valid output folder path",path)
    exit()
path = os.path.abspath(path)

rospack = rospkg.RosPack()

targetPath = os.path.join(path,"Inc")
if not os.path.isdir(targetPath):
    os.mkdir(targetPath)

desPath = os.path.join(targetPath,"rosserialInc")
if not os.path.isdir(desPath):
    os.mkdir(desPath)

roslib_Path = os.path.join(rospack.get_path(THIS_PACKAGE) , "ros_lib")
print("\nExport Interfaces files ros.h and STM32Hardware.h to %s", desPath)
userbeginStr = "/*USER CODE BEGIN*/"
userendStr = "/*USER CODE BEGIN*/"
userready=0
readReady=-1
files = os.listdir(roslib_Path)
for f in files:
    file = os.path.join(roslib_Path,f)
    if os.path.isfile(file):
        if not (f == 'ros.h' and os.path.exists(os.path.join(desPath,f))):
            shutil.copy(file, desPath)


print("\nExport message_headers to %s", desPath)
rosserial_client_copy_files(rospack, desPath)

# generate messages
rosserial_generate(rospack, desPath, ROS_TO_EMBEDDED_TYPES)

print(__postWords__)