/*
 * rosserialNode.cpp
 *
 *  Created on: Aug 18, 2021
 *      Author: Xiaojiao Chen
 *       Email: yii402072495@gmail.com
 */

#include "rosserialNode.h"


/*************************User Config Zone begin***********************/

/*1.necessary headers*/
#include "std_msgs/Float32.h"		//include pub messageType headers
#include "std_msgs/String.h"		//include sub messageType headers

/*1.modify your pub variable, could be external, */
std_msgs::Float32 pubVariable;
//extern std_msgs::Float32 pubVariable;
ros::Publisher publisher1("pubTopic",  &(pubVariable));  //dont modify the publisher name

/*1.dummy sub callback, implement in your own file */
__weak void sub1Callback(const std_msgs::String &msg){  //dont modify the sub callback name
	UNUSED(msg);
	//implement your sub callback content in your file
} 
ros::Subscriber<std_msgs::String> subscriber1("subTopic", &sub1Callback); 

/*************************User Config Zone End  ***********************/







RosserialNode rosserialNode;//global variable

/*If you already have your own HAL_UART_TxCpltCallback function, just put the TxCallback() function inside of your code.and comment out below */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	rosserialNode.TxCallback(huart);
}

/*If you already have your own HAL_UART_RxCpltCallback function, just put the RxCallback() function inside of your code.and comment out below */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rosserialNode.RxCallback(huart);
}


void  RosserialNode::init(UART_HandleTypeDef *huart)
{

	rosuart= huart;

	initNode((char *)rosuart);

	advertise(publisher1);

	subscribe(subscriber1);

};


void RosserialNode::TxCallback(UART_HandleTypeDef *huart)
{
	if (rosuart == huart)
	{
		getHardware()->flush();
	}
}

void RosserialNode::RxCallback(UART_HandleTypeDef *huart)
{
	if (rosuart == huart)
	{
		getHardware()->reset_rbuf();
	}
}

void RosserialNode::publish(const ros::Msg * msg){

	publisher1.publish(msg);
}
