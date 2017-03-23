#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>

void resolveIP(struct hostent *ghbn){
	struct in_addr  **pptr;
	pptr = (struct in_addr **)ghbn->h_addr_list;
	//while( *pptr != NULL ){
                printf("ip address: %s\n", inet_ntoa(**(pptr)));
        //}
}

int main(int argc, char *argv[]){
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd;
	unsigned short port = 8780;
	
	char host_name[100];
	//memset(host_name, 0, 100);
	if(argc == 1) {
 		printf( "Enter a value :\n");
 		scanf("%s",host_name);
		h = gethostbyname(host_name);
		resolveIP(h);
	}else{
    		h = gethostbyname(argv[1]);
		resolveIP(h);
       		printf("\n");
    	}	
	
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket \n");
	}
	if ((h=gethostbyname(host_name)) == NULL) {
		printf("Unknown host \n");
	}
	
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	saddr.sin_port = htons(port);
	
	if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect \n");
	}else{
		printf("Connect successfully\n");
	}
	return 0;

}

