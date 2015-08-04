#ifdef __linux__

#include "socket_lib_linux.h"


//Clean and close winsock
void close_socket(int *sock){
	close(*sock);
}

//Get the id of the curretn thread
int get_current_thread_id(){
	return (int)syscall(224);
}

struct thread_parameter{
	int socket;
	void(*callback)(int);
};

//Thread serveur
void* thread_callback(void* data){
	thread_parameter tdata = *(thread_parameter*)data;
	int client = tdata.socket;
	tdata.callback(client);
	return 0;
}

//Fonction for initialize the server mode
void init_server(int port, uint32_t ip, void(*callback)(int)){
	try{

		int socket_desc, client_sock, c, new_sock;
		struct sockaddr_in server, client;

		//Create socket
		socket_desc = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_desc == -1) {
			throw "Could not create socket";
		};

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = ip;
		server.sin_port = htons(port);

		//Bind
		if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
			throw "bind failed";
		}

		//Listen
		listen(socket_desc, 3);

		//Accept and incoming connection
		c = sizeof(struct sockaddr_in);
		while (1){

			if ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
				//throw "accept failed";

				printf("Connection accepted");

				pthread_t sniffer_thread;

				thread_parameter p;
				p.socket = client_sock;
				p.callback = callback;

				if (pthread_create(&sniffer_thread, NULL, thread_callback, &p) < 0) {
					throw "could not create thread";
				}
			}

		}

	}
	catch (char const* error_msg){
		printf("%s\n", error_msg);
	}

}

//Fonction for initialize the client mode
int init_client(int port, uint32_t ip){
	try{

		int sock;
		struct sockaddr_in server;

		//Create socket
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
			throw "Could not create socket";
		}

		server.sin_addr.s_addr = ip;
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		//Connect to remote server
		if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0){
			throw "connect failed";
		}

		return sock;

	}
	catch (char const* error_msg){
		printf("%s\n", error_msg);
		return -1;
	}
}


char* send_and_get_answer(int sock, char *msg){

	try{

		char server_reply[2000];
		int recv_size;

		//Send some data
		if (send(sock, msg, strlen(msg), 0) <= 0){
			throw "send fail";
		}

		//Receive some data
		if ((recv_size = recv(sock, server_reply, 2000, 0)) <= 0){
			throw "recv fail";
		}

		server_reply[recv_size] = '\0';
		return server_reply;

	}
	catch (char const* error_msg){
		printf("%s\n", error_msg);
		return NULL;
	}

}

#endif
