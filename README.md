# rosserial_stm32cxj

This is a package for ROS Serial communication with STM32Cube generated project based on two repos [rosserial_stm32](https://github.com/yoneken/rosserial_stm32) and [rosserial_stm32f7](https://github.com/fdila/rosserial_stm32f7). 

Previously when using rosserial_stm32 packages, they make my Inc/ folder swelled and broken my whole code hiarchkey.  Also, the related codes are seperated small pieces that need to be placed at different locations. This causes that everytime when I use rosserial on different project, I need to find a example template.

Therefore, I would like to make this rosserial communication more organized and more convinient to use, aiming at:
1. making the stm32 code clean
2. plug and play


# Feature
### 1. Built-in publishers and subscribers. (maximum 3 for each currently)
### 2. Built-in message variables.
### 3. Built-in global variable named rosserialNode for handleing all the built-in resources.

# Usage
## 1. Install this ROS package

```sh
cd ~/catkin_ws/src
```
```sh
git clone https://github.com/XiaojiaoChen/rosserial_stm32cxj.git
```
```sh
cd ..
```
```sh
catkin_make
```
```sh
source devel/setup.sh
```
## 2. Generate libs
### 1. if the STM32 project is on the same machine
```sh
cd yourSTM32Project/Core
```
```sh
rosrun rosserial_stm32cxj make_libraries.py .
```
This will generate a rosserialInc/ folder inside your Inc/ folder.

### Or if the STM32 project is not on the same machine, just directly run:
```sh
rosrun rosserial_stm32cxj make_libraries.py .
```
This will generate a Inc/ folder at your current path.

you need to manually merge the generated Inc/ folder with your STM32 project Inc folder.

### 2. Add the rosserialInc/ folder to your inlcude search path in your STM32 Project. 

* In STM32CubeIDE, this could be done by first refreshing the project, then right click the rosserialInc folder from the project exploer panel in your STM32CubeIDE, choose "Add/Remove include path". 

"""

## 3. use rosserial communication in your STM32 project

### 1. prerequisite. 
* Make sure that your usart is initiated with:
1. Tx DMA Enabled
2. Rx DMA Enabled
3. TxRx Global Interrupt Enabled

* Make sure you have add the folder rosserialInc/ in your include search path.

### 2. Include "ros.h" in your file
```c
 #include "ros.h"
 ```
 now you get a built-in global variable rosserialNode to access all the resources.
### 3. Define parameters in "rosserialNode.h":
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
### 4. publish data with
```c
rosserialNode.pubData1.data = 1;
rosserialNode.publisher1.pub(&rosserialNode.pubData1);
```
### 5. subscribe data with implemention of subcallback functions in your own file:
```c
void sub1Callback(const std_msgs::String &msg)
{
	rosserialNode.subData1.data = msg.data;
}
```

### 6. add routine function in your code:
```c
loop(){
    rosserialNode.spinOnce();
}
```
### 6. (Optional) If you have your onw version of HAL_UART_TxCpltCallback() or HAL_UART_RxCpltCallback(), then add the content under the same functionname in rosserialNode.cpp to your function, and comment the function out  in rosserialNode.cpp.
```c
/*comment these two functions out in rosserialNode.cpp if you have your version. Add the content to your function*/
// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	rosserialNode.TxCallback(huart);    
// }

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	rosserialNode.RxCallback(huart);
// }
```
# Advanced
you could easily add more publishers and subscribers by modifying the rosserialNode class. 