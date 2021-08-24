/*
 * rosserialNode.h
 *
 *  Created on: Aug 18, 2021
 *      Author: Xiaojiao Chen
 *       Email: yii402072495@gmail.com
 */

#ifndef __ROSSERIALNODE_H_
#define __ROSSERIALNODE_H_

#include "ros.h"
#include "main.h"

extern UART_HandleTypeDef DEFAULT_ROS_HUART;

class RosserialNode {
public:
	RosserialNode();
	void setPort(UART_HandleTypeDef *huart);
	void spinOnce(void);
        // void addPub(char *pubTopicName, (void *)pPubData);
	// void addSub(char *subTopicName, (void *)subCallback);


        void TxCallback(UART_HandleTypeDef *huart);
	void RxCallback(UART_HandleTypeDef *huart);

#if PUBLISHER_NUMBER >= 1
	Publisher1_MessageType Publisher1_MessageName;
	ros::Publisher Publisher1_Name;
#endif
#if PUBLISHER_NUMBER >= 2
        Publisher2_MessageType Publisher2_MessageName;
        ros::Publisher Publisher2_Name;
#endif
#if PUBLISHER_NUMBER >= 3
        Publisher3_MessageType Publisher3_MessageName;
        ros::Publisher Publisher3_Name;
#endif

#if SUBSCRIBER_NUMBER >= 1
	Subscriber1_MessageType Subscriber1_MessageName;
	ros::Subscriber<Subscriber1_MessageType> Subscriber1_Name;
#endif
#if SUBSCRIBER_NUMBER >= 2
        Subscriber2_MessageType Subscriber2_MessageName;
        ros::Subscriber<Subscriber2_MessageType> Subscriber2_Name;
#endif
#if SUBSCRIBER_NUMBER >= 3
        Subscriber3_MessageType Subscriber3_MessageName;
        ros::Subscriber<Subscriber3_MessageType> Subscriber3_Name;
#endif
	UART_HandleTypeDef *rosuart;
	ros::NodeHandle nh;
        uint8_t initiatedFlag;
};

extern RosserialNode rosserialNode;





#endif /* __ROSSERIALNODE_H_ */
