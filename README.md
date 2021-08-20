# rosserial_stm32cxj

This is a package for ROS Serial communication with STM32Cube generated project based on two repos [rosserial_stm32](https://github.com/yoneken/rosserial_stm32) and [rosserial_stm32f7](https://github.com/fdila/rosserial_stm32f7). 

Previous rosserial_stm32 packages would make the Inc/ folder swelling,  and break the original code organization.  Also, when in use, the codes are small pieces and separated at different locations. It is not convenient to fast deploy a new stm32 project using rosserial.

Therefore, this package aims to make this rosserial communication more organized and more convenient, by wrapping all the rosserial setting and initializations underground. You could now focus more on your data flow directly. 


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Feature
* Only one generated folder for portability and cleanness
* One global variable rosserialNode for organizing rosserial resources with
    * Built-in publishers and subscribers. (maximum 3 for each currently)
    * Built-in message variables.
* fast deployment to new project

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Example
After defining your topic and message parameters in "ros.h", then in your cpp file,
 ```c
 #include "ros.h"

 void sub1Callback(const std_msgs::String &msg){ //receive data
     rosserialNode.subData1.data = msg.data; 
 }

 void loop(){
     rosserialNode.pubData1.data=1;
     rosserialNode.publisher1.publish(&rosserialNode.pubData1);//transmit data

     rosserialNode.spinOnce();
     HAL_Delay(10);
 }
 ```
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

    * This command will generate a subfolder rosserialInc/ under your Inc/ folder. 
    * if the STM32 project is not on the same machine, just directly run the last command, and manually merge the generated Inc/ folder with your STM32 project Inc/ folder.

3. Add the rosserialInc/ folder to your include search path of your STM32 Project. 

    * In STM32CubeIDE, this could be done by first refreshing the project, then right clicking the rosserialInc/ folder from the project explorer panel in STM32CubeIDE, and choosing "Add/Remove include path". 


## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Use rosserial communication in your STM32 Project
* prerequisites: make sure usart has been properly initiated, with Tx and Rx DMA Enabled, Tx and Rx Global Interrupt Enabled. and rosserialInc/ is in your include search path.

1. Define the following parameters in "ros.h":

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
    7. subscriber callback function name...(default: sub1Callback,sub2Callback,sub3Callback)
    8. include message headers

        * some parameters are necessary to be modified with your application, such as the usart port, topic names,  message types, and corresponding headers.

        * some are not necessary to be changed. They have default values that you can directly use, such as built-in publishers, subscribers, message variables, callbackFunctionNames. Just suit your need.

2. Include "ros.h" in your cpp file
    ```c
    #include "ros.h"
    ```
    * It has a built-in global variable named rosserialNode to manage all the rosserial resources that you can directly use.

3. Add spinOnce() routine to your loop:
    ```c
    loop(){
        rosserialNode.spinOnce();
    }
    ```
4. publish data with
    ```c
    rosserialNode.pubData1.data = 1;
    rosserialNode.publisher1.pub(&rosserialNode.pubData1);
    ```
5. Subscribe data with implementation of your subcallback functions in your own file:
    ```c
    void sub1Callback(const std_msgs::String &msg)
    {
        rosserialNode.subData1.data = msg.data;
    }
    ```
    * your subscribe callback function name and message type should be consistent with what you have defined in "ros.h".

6. (Optional) Adjust HAL Callback functions according to your scenario.

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

## ![](https://via.placeholder.com/15/1589F0/000000?text=+) Acknowledgement
* [rosserial_stm32 by yoneken](https://github.com/yoneken/rosserial_stm32)
* [rosserial_stm32f7 by fdila](https://github.com/fdila/rosserial_stm32f7). 