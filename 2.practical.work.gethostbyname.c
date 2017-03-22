#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void resolveIP(struct hostent *ghbn){
	struct in_addr  **pptr;
	pptr = (struct in_addr **)ghbn->h_addr_list;
	while( *pptr != NULL ){
                printf("ip address: %s\n", inet_ntoa(**(pptr++)));
        }
}
int main(int argc, char *argv[]){
	struct hostent *ghbn;
	char host_name[100];
	//memset(host_name, 0, 100);
	if (argc == 1) {
 		printf( "Enter a value :\n");
 		scanf("%s",host_name);
		ghbn = gethostbyname(host_name);
		resolveIP(ghbn);
	}else{
    		ghbn = gethostbyname(argv[1]);
		resolveIP(ghbn);
       		printf("\n");
    	}
	/*if (ghbn)
		printf(inet_ntoa(**(ghbn->h_addr_list)) + "\n");
	else
        herror("gethostbyname");
 	*/
	return 0;
}
