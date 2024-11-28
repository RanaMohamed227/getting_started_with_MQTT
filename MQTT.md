## MQTT

![Screenshot 2024-11-28 104832](https://github.com/user-attachments/assets/1721e81e-0f58-411f-8d35-6951f6c473ed)


Imagine a scenario where i want to post on Facebook i am the publisher or the admin then the Facebook or the place where i publish is called broker and the viewers or people who interact on the post (likes or whatever) are called subscribers

Note:
admin share the post on the facebook or broker (وسيط)  2na mr7t4 gave this post to a certain one but the facabook gave it to all


----------------------------------------

## MQTT: messaging protocol 

devices in the network send messages to each other


smart home: application sends messages to home elements 

so, we use mqtt so they communicate with each other:
the most important protocol in IOT





![Screenshot 2024-11-28 105517](https://github.com/user-attachments/assets/add35b7c-f4d3-4d7c-86b2-ef58603d0173)




--------------------------
If we have three sensors in the network each responsible for a specific task
i want to read the readings of these sensors and send it to devices

so the sensors first sends the info or readings to the broker and the broker decides where to send these info


## But how the broker chooses that subscriber??

Based on the topic : بقوله ابعت درجة الحرارة للناس بتاعت التوبيك
2kni subscribed fi private group or page
1- Smart home -sensors-


![Screenshot 2024-11-28 111528](https://github.com/user-attachments/assets/58363565-74c1-49db-949f-aa02add2c556)




2- Car comm

car (Publisher) sends Speed info then sends it to server MQTT (broker) then the subscribers who share the same topic reads or have access to these info


------------------------
## Can the publisher be a subscriber ,too. 


some cases require the mobile app to be publisher and sometimes i need to be subscriber. 
Client --> Publisher / subscriber



![Screenshot 2024-11-28 113436](https://github.com/user-attachments/assets/34126470-6b3a-4180-be7f-223036232865)



------
## the Message sent to the broker can be command or data  


--> the topic can be a word or subtopics 
--> Topic is similar to channel in data transformation 




![Screenshot 2024-11-28 114141](https://github.com/user-attachments/assets/cefc0e02-8453-467c-b937-00bf30abb0d9)



-------------------
## Publisher : Sends data or commands
## subscriber : receive data or commands

## Broker:  manage and route the data or commands


--> MQTT 

1- require minimal resources 

2- Bidirectional comm protocol publisher and subscriber at the same time

3- very secure --> the data can be encrypted inside the broker 

4- access control list --> password to topics not only shared topic but like a two step authentication

5- unsecured port 1883

6- secured port 8883

7- Highly scalable 
- easy to maintain clients addresses or IDs 
- The only things required are the broker IP address and the topic name

8- Reliable 
-  QoS: Quality of service 
- 1- QoS 0 (Level 0): the message is sent once   موصلتش مش مهم بيبعت المسدج مرة وصلت خلاص
-UNreliable 
- 2- QoS 1 (Level 1): the message  is sent once but perhaps more (1 or more)
-- waits for acknowledgment sends it until recieving ack.
- 3- QoS 2 (Level 2): the message  is sent once only
-- uses four step handshake 
1- to avoid the problem of level 1 of a possible duplication we sent it again but with duplication flag




![Screenshot 2024-11-28 124114](https://github.com/user-attachments/assets/248bb404-69a1-4a1f-a257-55d581f7c1e3)





