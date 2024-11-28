## MQTT


![[Pasted image 20241128104841.png]]

	Imagine a scenario where i want to post on Facebook i am the publisher or the admin then the Facebook or the place where i publish is called broker and the viewers or people who interact on the post (likes or whatever) are called subscribers

Note:
admin share the post on the facebook or broker (وسيط)  2na mr7t4 gave this post to a certain one but the facabook gave it to all


----------------------------------------

## MQTT: messaging protocol 

	devices in the network send messages to each other


	smart home: application sends messages to home elements 

	so, we use mqtt so they communicate with each other:
	the most important protocol in IOT



![[Pasted image 20241128105555.png]]



--------------------------
           If we have three sensors in the network each responsible for a specific task
i want to read the readings of these sensors and send it to devices

so the sensors first sends the info or readings to the broker and the broker decides where to send these info


## But how the broker chooses that subscriber??

Based on the topic : بقوله ابعت درجة الحرارة للناس بتاعت التوبيك
2kni subscribed fi private group or page
1- Smart home -sensors-


![[Pasted image 20241128111542.png]]


2- Car comm

car (Publisher) sends Speed info then sends it to server MQTT (broker) then the subscribers who share the same topic reads or have access to these info


------------------------
## Can the publisher be a subscriber ,too. 


some cases require the mobile app to be publisher and sometimes i need to be subscriber. 
Client --> Publisher / subscriber
![[Pasted image 20241128113445.png]]

------
## the Message sent to the broker can be command or data  


--> the topic can be a word or subtopics 
--> Topic is similar to channel in data transformation 


 ![[Pasted image 20241128114154.png]]


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



![[Pasted image 20241128124128.png]]


