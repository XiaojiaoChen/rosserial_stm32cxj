/*
 * ros.h
 *
 *  Created on: Aug 18, 2021
 *      Author: Xiaojiao Chen
 *       Email: yii402072495@gmail.com
 */

#ifndef __ROS_H_
#define __ROS_H_

/**
 * Configure:
 * 1. Complete the Configuration Zone.
 * 2. Include "ros.h" in your file. (Now you got a global variable named rosserialNode that can be directly used)
 * 3. put rosserialNode.spinOnce() in your loop()
 * 4. Implement your subscriber callback function in your file
 * 5. (optional*) if you have your own HAL_UART_TxCpltCallback or HAL_UART_RxCpltCallback implemented,
 * 	  add the content under the same name in RosserialNode.cpp to your version, and comment the version in RosserialNode.cpp.
 *      
 * example usage(with default value):
 * 1.pubData1.data = 1;
 *	rosserialNode.publisher1.pub(&pubData1);
 *
 * 2.void rosserial_sub1Callback(const std_msgs::String &msg) //define your sub callback in your user file with same name
    {
        subData1.data = msg.data;
    }
 */


/*********************************************************************************************
**********************************  	              	  ************************************
**********************************  Configuration  Zone   ************************************
**********************************  	   BEGIN     	  ***********************************
********************************************************************************************/
/*USER CODE BEGIN*/

#include "std_msgs/Float64.h"		//include messageType headers

#include "std_msgs/String.h"		//include messageType headers

#define DEFAULT_ROS_HUART huart3 //choose  your uart for ROS serial

#define PUBLISHER_NUMBER 1  //define how many publisher you have, currently <=3

#define SUBSCRIBER_NUMBER 1 //define how many subscriber you have

#if PUBLISHER_NUMBER >= 1
#define Publisher1_TopicName    	"pubTopic1"        	//define your Topic Name string to be published
#define Publisher1_MessageName  	pubData1         	//name your variable to be published
#define Publisher1_MessageType  	std_msgs::Float64 	//define your variable Type
#define Publisher1_Name		  		publisher1			//name a publisher for this topic
#endif
#if PUBLISHER_NUMBER >= 2
#define Publisher2_TopicName    	"pubTopic2"        	//define your Topic Name string to be published
#define Publisher2_MessageName  	pubData2         	//name your variable to be published
#define Publisher2_MessageType  	std_msgs::String 	//define your variable Type
#define Publisher2_Name		  		publisher2			//name a publisher for this topic
#endif
#if PUBLISHER_NUMBER >= 3
#define Publisher3_TopicName    	"pubTopic3"        	//define your Topic Name string to be published
#define Publisher3_MessageName  	pubData3         	//name your variable to be published
#define Publisher3_MessageType  	std_msgs::Float64 	//define your variable Type
#define Publisher3_Name		  		publisher3			//name a publisher for this topic
#endif

#if SUBSCRIBER_NUMBER >= 1
#define Subscriber1_TopicName 			"subTopic1"                 //define your sub topic name string
#define Subscriber1_MessageName 		subData1                    //name your local variable for receiving sub data
#define Subscriber1_MessageType 		std_msgs::String            //define your local variable type
#define Subscriber1_Name		  		subscriber1					//name a subscriber for this topic
#define Subscriber1_CallbackFunc_Name   sub1Callback                //define your sub callback function name
#endif
#if SUBSCRIBER_NUMBER >= 2
#define Subscriber2_TopicName 			"subTopic2"                 //define your sub topic name string
#define Subscriber2_MessageName 		subData2                    //name your local variable for receiving sub data
#define Subscriber2_MessageType 		std_msgs::String            //define your local variable type
#define Subscriber2_Name		  		subscriber2					//name a subscriber for this topic
#define Subscriber2_CallbackFunc_Name   sub2Callback                //define your sub callback function name
#endif
#if SUBSCRIBER_NUMBER >= 3
#define Subscriber3_TopicName 			"subTopic3"                 //define your sub topic name string
#define Subscriber3_MessageName 		subData3                    //name your local variable for receiving sub data
#define Subscriber3_MessageType 		std_msgs::String            //define your local variable type
#define Subscriber3_Name		  		subscriber3					//name a subscriber for this topic
#define Subscriber3_CallbackFunc_Name   sub3Callback                //define your sub callback function name
#endif

/*USER CODE END*/
/*********************************************************************************************
**********************************  	              	  	************************************
**********************************  Configuration  Zone  	************************************
**********************************  	   END     	  		***********************************
********************************************************************************************/



/*************************No need to modify the following unless you know what you are doing*********/

#include "ros/node_handle.h"
#include "STM32Hardware.h"
#include "main.h"  
//#include "stm32f1xx_hal.h" if necessary
namespace ros{
    typedef NodeHandle_<STM32Hardware> NodeHandle; // default 25, 25, 512, 512
}
#include "rosserialNode.h"



#endif /* __ROS_H_ */
