# rosserial_stm32cxj

This is a rosserial stm32 communication package based on two repos [rosserial_stm32](https://github.com/yoneken/rosserial_stm32) and [rosserial_stm32f7](https://github.com/fdila/rosserial_stm32f7). 

This package aims to make rosserial_stm32 communication more organized by constraing the related code to one folder, and convenient for new deployment by wrapping some infrastructural code.


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Feature
* one folder for portability and cleanness
* built-in global rosserialNode with internal publisher and subscriber.

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Example Usage
1. config your publisher and subscriber informations in "rosserialNode.cpp"
2. in your main file,

    ```c
    #include "ros.h"
    extern RosserialNode rosserialNode;//optional declaration

    void setup(){
        rosserialNode.init(&huart1); //init port
    }
    void loop(){
        rosserialNode.publish(&(yourPubData));//pub data
        rosserialNode.spinOnce();
    }

    //sub callback
    void sub1Callback(const std_msgs::String &msg){
        //code here
    }
    ```
## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Installation
1. Install the ROS package
    ```sh
    cd ~/catkin_ws/src
    git clone https://github.com/XiaojiaoChen/rosserial_stm32cxj.git
    ```
    ```sh
    cd ..
    catkin_make
    source devel/setup.sh
    ```
2. Generate libs anywhere, for example in the package folder:

    ```sh
    roscd rosserial_stm32cxj
    rosrun rosserial_stm32cxj make_libraries.py .
    ```
    This will generate a rosserialInc/ foler in the rosserial_stm32cxj package.
    
3. Copy the generated rosserialInc/ to your STM32 project and add the rosserialInc/ folder to your **include path** and **source path**. 

4. In your STM32 project, configure "rosserialNode.cpp" and write your rosserial communication codes following the example usage.


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Connection with ROS Master
*  run a rosserial client node in the host machine:
    ```sh
    roscore
    rosrun rosserial_python serial_node.py
    ```
    * The defaul baudrate is 57600 
    * for a specific port and baudrate, use

        ```sh
        rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200
        ```
        portname could be identified by
        ```sh
        dmesg | grep tty
        ```


* Or using a launch file:
    ```sh
    <launch>
    <node pkg="rosserial_python" type="serial_node.py" name="serial_node">
        <param name="port" value="/dev/ttyACM0"/>
        <param name="baud" value="115200"/>
    </node>
    </launch>
    ```

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Acknowledgement
* [rosserial_stm32 by yoneken](https://github.com/yoneken/rosserial_stm32)
* [rosserial_stm32f7 by fdila](https://github.com/fdila/rosserial_stm32f7). 