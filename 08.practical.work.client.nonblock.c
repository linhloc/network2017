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


int connectToServer(struct hostent *h, struct sockaddr_in saddr,int sockfd, unsigned short port){
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	saddr.sin_port = htons(port);
	
	if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect \n");
	}else{
		printf("Connect successfully\n");
		return 1;
	}
}

int main(int argc, char *argv[]){
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd, stateConnect;
	unsigned short port = 9999;
	char buffer[1000], str[100];
	char host_name[100];
	int count; char c;
	//memset(host_name, 0, 100);
	if(argc == 1) {
 		printf( "Enter a host name :\n");
 		scanf("%s",host_name);
		h = gethostbyname(host_name);
		//resolveIP(h);
	}else{
    		h = gethostbyname(argv[1]);
		//resolveIP(h);
       		printf("\n");
    	}
    	sockfd=socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) {
		printf("Error creating socket \n");
	}
	//reuse addressing
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 },sizeof(int));
	
	//non blocking client
	int fl = fcntl(sockfd, F_GETFL, 0);
	fl |= O_NONBLOCK;
	fcntl(sockfd, F_SETFL, fl);
	
	if ((h=gethostbyname(host_name)) == NULL) {
		printf("Unknown host \n");
	}
	stateConnect = connectToServer(h, saddr, sockfd, port);
	
	//while(true)
	while(1) {
		//scanf from STDIN
		printf("Client: ");
		//memset(&buffer, 0, sizeof(buffer));
		scanf("%s",buffer);
		//gets(buffer);
		/*while(strcmp(buffer,"/quit") == 0) {
			while((count = read(sockfd, &c, sizeof(c))) > 0);
			//shutdown(sockfd, SHUT_DRWR);
			close(sockfd);
			exit(1);
		}*/
		//send() to server
		send(sockfd, buffer, strlen(buffer), 0);
		memset(&buffer, 0, sizeof(buffer));
		//Recv() from server
		//recv(sockfd, buffer,sizeof(buffer),0);
		//Print() to STDOUT
		//printf("Server: %s \n", buffer);
		//memset(&buffer, 0, sizeof(buffer));
	}
	return 0;

}

