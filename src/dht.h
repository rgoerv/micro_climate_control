#ifndef DHT_H_
#define DHT_H_

#define DHT11_PIN 6

void Request();
void Response();
unsigned char Receive_data();
void DHT_Process(unsigned char* humi, unsigned char* temp);

#endif /* DHT_H_ */