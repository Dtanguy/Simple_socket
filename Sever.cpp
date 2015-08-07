#include <stdio.h>
#include <iostream>
#include "simple_socket/socket_lib.h"



//Thread for earch client connected
void client_thread(int socket){

	printf("Client connected\n");
	char client_msg[2000];
	int recv_size;
	while ((recv_size = recv(socket, client_msg, 2000, 0)) > 0){

		client_msg[recv_size] = '\0';
		printf("%s \t i have receive : %d\n", client_msg, get_current_thread_id());
		if (send(socket, "ok", strlen("ok"), 0) <= 0){
			//error
		}

	}
	return;
}



int main(int argc, char *argv[]){

	printf("Server\n");
	init_server(8888, INADDR_ANY, client_thread);

	return 0;
}
