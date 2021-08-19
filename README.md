# rosserial_stm32cxj

This is a package for ROS Serial communication with STM32Cube generated project based on two repos [rosserial_stm32](https://github.com/yoneken/rosserial_stm32) and [rosserial_stm32f7](https://github.com/fdila/rosserial_stm32f7). 

Previously when using rosserial_stm32 packages, they make my Inc/ folder swelled and broken my whole code hiarchkey.  Also, the related codes are seperated small pieces that need to be placed at different locations. This causes that everytime when I use rosserial on different project, I need to find a example template.

Therefore, I would like to make this rosserial communication more organized and more convinient to use, aiming at:
1. making the stm32 code clean
2. plug and play


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Feature
* Built-in publishers and subscribers. (maximum 3 for each currently)
* Built-in message variables.
* Built-in global variable named rosserialNode for handleing all the built-in resources.

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Usage
1. Install this ROS package
    ```sh
    cd ~/catkin_ws/src
    git clone https://github.com/XiaojiaoChen/rosserial_stm32cxj.git
    ```
    ```sh
    cd ..
    catkin_make
    source devel/setup.sh
    ```
2. Generate libs

    ```sh
    cd yourSTM32Project/Core

    rosrun rosserial_stm32cxj make_libraries.py .
    ```

    * This command will generate a subfolder rosserialInc/ under your Inc/ folder. All rosserial files are located inside the rosserialInc/ subfolder.
    * if the STM32 project is not on the same machine, just directly run the last command, and mannualy merge the generated Inc/ folder with your STM32 project Inc/ folder.


3. Add the rosserialInc/ folder to your inlcude search path of your STM32 Project. 

    * In STM32CubeIDE, this could be done by first refreshing the project, then right clicking the rosserialInc/ folder from the project exploer panel in STM32CubeIDE, and choosing "Add/Remove include path". 


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Use rosserial communication in your STM32 Project
 

1. prerequisite. 
    * usart properly initiated, with Tx and Rx DMA Enabled, Tx and Rx Global Interrupt Enabled.
    * rosserialInc/ is in your include search path.

2. Include "ros.h" in your file
    ```c
    #include "ros.h"
    ```
    * It has a built-in global variable named rosserialNode to manage all the rosserial resources, already exported as below. You can directly use this variable only if "ros.h" is inlcuded.
        ```c
        //No need to add to your file, you can directly use this variable if "ros.h" is included
        extern RosserialNode rosserialNode; 
        ```
3. Define parameters in "rosserialNode.h":

    * some parameters are necessary to be modified with your application, such as the usart port, topic names,  message types, and corresponding headers.

    * some are not necessary to be changed. They have default values that you can directly use, such as built-in publishers, subscribers, message variables, callbackFunctionNames. Just suit your need.
    
        1. usart port ..........................................(default: huart3   )
        2. publisher number. ............................(default: 1, max 3)
        2. subscriber number.............................(default: 1, max 3)
        3. pub topic names................................(default: "pubTopic1","pubTopic2","pubTopic3")
        3. pub variable types.............................(default: std_msgs::String)
        3. pub variable names...........................(default: pubData1,pubData2,pubData3)
        3. sub topic names................................(default: "subTopic1","subTopic2","subTopic3")
        3. sub variable types............................(default: std_msgs::String)
        3. sub variable names...........................(default: subData1,subData2,subData3)
        5. publisher names...............................(default: publisher1,publisher2,publisher3)
        6. subscriber names..............................(default: subscriber1,subscriber2,subscriber3)
        7. subsciber callback function name...(default: sub1Callback,sub2Callback,sub3Callback)
        8. include message headers

    * A glimpse of the code in "rosserialNode.h" is:

        ```c
        #include "std_msgs/Float64.h"		//include messageType headers

        #include "std_msgs/String.h"		//include messageType headers

        #define DEFAULT_ROS_HUART huart3

        #define PUBLISHER_NUMBER 1

        #define SUBSCRIBER_NUMBER 1

        #define Publisher1_TopicName    	"pubTopic1"

        #define Publisher1_MessageName  	pubData1 

        #define Publisher1_MessageType  	std_msgs::Float64 

        #define Publisher1_Name		  		publisher1

        #define Subscriber1_TopicName 			"subTopic1" 

        #define Subscriber1_MessageName 		subData1 

        #define Subscriber1_MessageType 		std_msgs::String 

        #define Subscriber1_Name		  		subscriber1	

        #define Subscriber1_CallbackFunc_Name   sub1Callback  
        ```
4. publish data with
    ```c
    rosserialNode.pubData1.data = 1;
    rosserialNode.publisher1.pub(&rosserialNode.pubData1);
    ```
5. Subscribe data with implemention of your subcallback functions in your own file:
    ```c
    void sub1Callback(const std_msgs::String &msg)
    {
        rosserialNode.subData1.data = msg.data;
    }
    ```
    * your subscribe callback function name and message type should be consistant with what you have defined previously. 
    * If you didn't define your callback function name, you could use the default name sub1Callback directly.

6. Add spinOnce() routine to your loop:
    ```c
    loop(){
        rosserialNode.spinOnce();
    }
    ```
7. (Optional) Adjust HAL Callback functions according to the needs.

    * This package has built-in HAL_UART_TxCpltCallback and HAL_UART_RxCpltCallback functions in "rosserialNode.cpp" as
        ```c
        /*Built-in HAL UART Tx and Rx Callback functions*/
        void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
        {
            rosserialNode.TxCallback(huart);    
        }

        void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
        {
            rosserialNode.RxCallback(huart);
        }
        ```
    * If you have your own implementation of these two functions, then just comment out above functions, and add the content to your functions, as
        ```c
        /*Your version of HAL callback functions*/
        HAL_UART_TxCpltCallback(){
            /*
                Your Tx callback content 
            */
            rosserialNode.TxCallback(huart);//Add this
        };
        HAL_UART_RxCpltCallback(){
            /*
                Your Rx callback content 
            */
            rosserialNode.RxCallback(huart);//Add this
        };
        ``` 


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Connection with ROS Master
1. Connect STM32 board with your ROS Master through the  specified usart.
     ```sh
    roscore
    ```

2. find your serial port :
    ```sh
    dmesg | grep tty
    ```
3. run a rosserial client from a terminal:
    ```sh
    rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200
    ```
    or in a launch file:
    ```sh
    <launch>
    <node pkg="rosserial_python" type="serial_node.py" name="serial_node">
        <param name="port" value="/dev/ttyACM0"/>
        <param name="baud" value="115200"/>
    </node>
    </launch>
    ```

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Example on STM32F767ZI Nucleo Board
* usart 3, with a baudrate of 57600