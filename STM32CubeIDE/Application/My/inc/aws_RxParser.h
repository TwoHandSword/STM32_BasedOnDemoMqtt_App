/*
 * aws_RxParser.h
 *
 *  Created on: 2022. 1. 5.
 *      Author: yg
 */

#ifndef APPLICATION_MY_INC_AWS_RXPARSER_H_
#define APPLICATION_MY_INC_AWS_RXPARSER_H_


void aws_RxMqttParse(const char * pPayload , int payloadlen, const char *pTopicName, int topicnamelen);


#endif /* APPLICATION_MY_INC_AWS_RXPARSER_H_ */
