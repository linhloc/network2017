#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

int connected(int sockfd, int clen, struct sockaddr_in caddr){
	int clientfd;
	if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
		printf("Error accepting connection \n");	
	}else{
		printf("Accepted connection\n");
	}
	return clientfd;
}

int main(int argc, char *argv[]){
	int sockfd, clen, connectedState, clientfd;;
	struct sockaddr_in saddr, caddr;
	unsigned short port = 9999;
	char buffer[1000];
	
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket \n");
		
	}
	
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
	clientfd = connected(sockfd, clen, caddr);
	while(1){
		//recv() from client
		memset(&buffer, 0, sizeof(buffer));
		recv(clientfd, buffer, sizeof(buffer), 0);
		//printf() to STDOUT
		printf("%s \n",buffer);
		//Scanf from STDIN
		//scanf("%s", buffer);
		memset(&buffer, 0, sizeof(buffer));
		gets(buffer);
		//Send to client
		send(clientfd, buffer, strlen(buffer), 0);
	}
	return 0;

}

