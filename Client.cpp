#include <stdio.h>
#include <iostream>

#include "simple_socket/socket_lib.h"



int main(int argc, char *argv[]){

	/* Initialise a client on the port 8888 and the localhost ip*/
	int sock = init_client(8888, inet_addr("127.0.0.1"));

	/* Check if the init succes */
	if (sock < 0){
		//Error
		return -1;
	}

	/* Print something */
	printf("Connection succes, write what you want to send and press ENTER\n");

	/* Send what you write and get the answer */
	char msg[1000];
	while(scanf("%s", msg)){
		char *answer = send_and_get_answer(sock, msg);
		if (answer != NULL){
			printf("%s\n", answer);
		}
	}

	/* Close the socket */
	close_socket(&sock);

	return 0;
}
