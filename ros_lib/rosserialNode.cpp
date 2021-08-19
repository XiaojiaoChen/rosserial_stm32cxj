/*
 * rosserialNode.cpp
 *
 *  Created on: Aug 18, 2021
 *      Author: Xiaojiao Chen
 *       Email: yii402072495@gmail.com
 */

#include "rosserialNode.h"



RosserialNode rosserialNode; //Global variable


/*If you already have your own HAL_UART_TxCpltCallback function, just put the TxCallback() function inside of your code.and uncomment below */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	rosserialNode.TxCallback(huart);
}


/*If you already have your own HAL_UART_RxCpltCallback function, just put the RxCallback() function inside of your code.and uncomment below */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	rosserialNode.RxCallback(huart);
}





RosserialNode::RosserialNode() :
#if PUBLISHER_NUMBER>=1
		Publisher1_Name(Publisher1_TopicName, &pubData1),
#endif
#if PUBLISHER_NUMBER>=2
		Publisher2_Name(Publisher2_TopicName, &pubData2),
	#endif
#if PUBLISHER_NUMBER>=3
		Publisher3_Name(Publisher3_TopicName, &pubData3),
	#endif
#if SUBSCRIBER_NUMBER>=1
		Subscriber1_Name(Subscriber1_TopicName, &rosserial_sub1Callback),
#endif
#if SUBSCRIBER_NUMBER>=2
		Subscriber2_Name(Subscriber2_TopicName, &rosserial_sub2Callback),
	#endif
#if SUBSCRIBER_NUMBER>=3
		Subscriber3_Name(Subscriber3_TopicName, &rosserial_sub3Callback),
	#endif
				rosuart(&(DEFAULT_ROS_HUART)) {
	setPort(rosuart);
	nh.initNode();
#if PUBLISHER_NUMBER>=1
	nh.advertise(publisher1);
#endif
#if PUBLISHER_NUMBER>=2
	            nh.advertise(publisher2);
	#endif
#if PUBLISHER_NUMBER>=3
	            nh.advertise(publisher3);
	#endif

}
;

void RosserialNode::setPort(UART_HandleTypeDef *huart){
	rosuart = huart;
	nh.getHardware()->setPort(huart);
}


/********************** put spinOnce() in loop routine*******************
 loop{
 rosserialNode.spinOnce();
 }*/
void RosserialNode::spinOnce() {
	nh.spinOnce();
}

void RosserialNode::TxCallback(UART_HandleTypeDef *huart) {
	if (rosuart == huart) {
		nh.getHardware()->flush();
	}
}

void RosserialNode::RxCallback(UART_HandleTypeDef *huart) {
	if (rosuart == huart) {
		nh.getHardware()->reset_rbuf();
	}
}


