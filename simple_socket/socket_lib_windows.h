#ifdef _WIN32

#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <stdint.h> 
#pragma comment(lib,"ws2_32.lib")


//Clean and close winsock
void close_socket(int *sock);

//Get the id of the curretn thread
int get_current_thread_id();

//Fonction for initialize winsock in server mode 
void init_server(int port, uint32_t ip, void(*callback)(int));

//Fonction for initialize winsock in client mode
int init_client(int port, uint32_t ip);

//Function for send a message and get the answer
char* send_and_get_answer(int sock, char *msg);

#endif
