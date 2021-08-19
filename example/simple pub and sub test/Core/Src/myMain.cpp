#include "myMain.h"
#include "ros.h"



void sub1Callback(const std_msgs::String &msg){
	rosserialNode.subData1.data = msg.data;
}

void setup(){

}


void loop(){
	rosserialNode.pubData1.data=1;
	rosserialNode.publisher1.publish(&rosserialNode.pubData1);
	rosserialNode.spinOnce();
	HAL_Delay(10);
}
