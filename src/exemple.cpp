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

	int choice = 0;
	printf("Make your choice :\n1) Server\n2) Client\n");
	scanf("%d", &choice);

	if (choice == 1){

		printf("Server\n");
		init_server(8888, INADDR_ANY, client_thread);

	}else if (choice == 2){

		printf("Client\n");
		int sock = init_client(8888, inet_addr("127.0.0.1"));

		if (sock >= 0){
			char msg[1000];
			printf("Connection succes, write what you want to send and press ENTER\n");
			while(scanf("%s", msg)){

				char *answer = send_and_get_answer(sock, msg);
				if (answer != NULL){
					printf("%s\n", answer);
				}
			}


		}

		close_socket(&sock);

	}

	printf("Prosses stoped, press a key to close\n");
	getchar();
	return 0;
}
