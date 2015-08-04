#ifdef _WIN32

#include "socket_lib_windows.h"


//Clean and close winsock
void close_socket(int *sock){
	closesocket(*sock);
	WSACleanup();
}

//Get the id of the curretn thread
int get_current_thread_id(){
	return GetCurrentThreadId();
}

struct thread_parameter{
	int socket;
	void(*callback)(int);
};

//Thread serveur
unsigned __stdcall thread_callback(void* data){
	thread_parameter tdata = *(thread_parameter*)data;
	int client = tdata.socket;
	tdata.callback(client);
	return 0;
}

//Fonction for initialize the server mode
void init_server(int port, uint32_t ip, void(*callback)(int)){

	WSADATA wsaData;
	int iResult;
	int sock;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult){ goto end; }

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET){ goto end; }

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = ip;

	iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));
	if (iResult){ goto end; }

	iResult = listen(sock, SOMAXCONN);
	if (iResult){ goto end; }

	//Loop
	int client;
	while (client = accept(sock, 0, 0)){

		if (client == INVALID_SOCKET){
			printf("invalid client socket", GetLastError());
			continue;
		}


		printf("New client\n");


		thread_parameter p;
		p.socket = client;
		p.callback = callback;

		_beginthreadex(0, 0, thread_callback, &p, 0, 0);


	}

end:
	close_socket(&sock);
	
}

//Fonction for initialize the client mode
int init_client(int port, uint32_t ip){

	WSADATA wsaData;
	int iResult;
	int sock;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult){
		close_socket(&sock);
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET){
		close_socket(&sock);
		return -1;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = ip;

	iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));
	if (iResult){
		close_socket(&sock);
		return -1;
	}

	return sock;
}


//Function for send a message and get the answer
char* send_and_get_answer(int sock, char *msg){

	if (send(sock, msg, strlen(msg), 0) >= 0){

		char server_reply[2000];
		int recv_size;

		if ((recv_size = recv(sock, server_reply, 2000, 0)) != SOCKET_ERROR){
			server_reply[recv_size] = '\0';
			return server_reply;
		}

	}

	return NULL;
}

#endif
