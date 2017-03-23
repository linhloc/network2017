#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
int main(int argc, char *argv[]){
	int sockfd, clen, clientfd;
	struct sockaddr_in saddr, caddr;
	unsigned short port = 8784;
	
	if (sockfd=socket(AF_INET, SOCK_STREAM, 0) < 0) {
		printf("Error creating socket \n");
		
	}
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);
	
	if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("Error binding \n");
	}
	if (listen(sockfd, 5) < 0) {
		printf("Error listening \n");
		
	}
	
	clen=sizeof(caddr);
	
	if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
		printf("Error accepting connection \n");	
	}else{
		printf("Accepted connection");
	}
	return 0;

}

