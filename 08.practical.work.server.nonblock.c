#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int sockfd, clen, connectedState, clientfd;
	struct sockaddr_in saddr, caddr;
	unsigned short port = 9999;
	char buffer[1000], str[100];
	int count; char c;
	
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("Error creating socket \n");
	}
	//reuse addressing
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 },sizeof(int));
	
	//non blocking server
	int fl = fcntl(sockfd, F_GETFL, 0);
	fl |= O_NONBLOCK;
	fcntl(sockfd, F_SETFL, fl);
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);
	
	if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("Error binding \n");
	}else{
		printf("listening a connection\n");
	}
	
	if (listen(sockfd, 5) < 0) {
		printf("Error listening \n");
	}
	clen=sizeof(caddr);
	
	while(1){
		clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen);
		
		if (clientfd > 0){	//non blocking client
			int fl = fcntl(clientfd, F_GETFL, 0);
			fl |= O_NONBLOCK;
			fcntl(clientfd, F_SETFL, fl);
		
			while(1){
				//recv() from client
				memset(&buffer, 0, sizeof(buffer));
				if(recv(clientfd, buffer, sizeof(buffer), 0) > 0){
					//printf() to STDOUT
					printf("Client: %s \n",buffer);
				}
				//Scanf from STDIN
				//printf("Server: ");
				//scanf("%s", buffer);
				/*if(strcmp(buffer,"/dc") == 0) {
					while((count = read(sockfd, &c, sizeof(c))) > 0);
					shutdown(sockfd, SHUT_WR);
					close(sockfd);
					//exit(1); //do not exit to wait for other client to connect
				}*/
				//memset(&buffer, 0, sizeof(buffer));
				//gets(buffer);
				//Send to client
				//send(clientfd, buffer, strlen(buffer), 0);
			}
		}
	}
	return 0;

}

