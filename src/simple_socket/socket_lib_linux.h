#ifdef __linux__

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>


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
