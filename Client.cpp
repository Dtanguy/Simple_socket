#include <stdio.h>
#include <iostream>

#include "simple_socket/socket_lib.h"



int main(int argc, char *argv[]){

	printf("Client\n");
	int sock = init_client(8888, inet_addr("127.0.0.1"));

	if (sock < 0){
		//Error
		return -1;
	}
	printf("Connection succes, write what you want to send and press ENTER\n");

	char msg[1000];
	while(scanf("%s", msg)){
		char *answer = send_and_get_answer(sock, msg);
		if (answer != NULL){
			printf("%s\n", answer);
		}
	}

	close_socket(&sock);
	return 0;
}
