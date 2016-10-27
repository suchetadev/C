/* This is a client program. It will send request to main server */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>


int main(int argc, char *argv[]) {

	int sock;	
	struct sockaddr_in server;
	char buff[1024];
	char *server_ip;
	unsigned short server_port;
	char operation_server_info[1024];
 	char ip[20]="",port[20]="";
        char *p;

        
	/*variables for operation server*/
        int operation_sock;
        struct sockaddr_in operation_server;
        char operation_server_ip[1024];
	int  operation_server_port;
	char operation_buff[1024];	
	char result[1024];

	server_ip = "127.0.0.1";
	server_port = 5000;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("socket failed");
		exit(1);
	}

	server.sin_family = PF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_port = htons(server_port);

	if (connect (sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror(" connection failed");
		exit(1);
	}
	
	printf("\n Enter the operation you want to perform : ");
	//gets(buff);
	fgets(buff,5, stdin);
	int len = strlen(buff);
	if (len > 0 && buff[len-1] == '\n') {
  		buff[len-1] = '\0';
	}
		
	if (send(sock, buff, sizeof(buff), 0) < 0) {
		perror(" data send failed");
		exit(1);
	} else {
		printf("\n Operation is sent to main server: [%s]\n",buff);
	}
	if(recv(sock,operation_server_info,sizeof(operation_server_info),0) < 0){
		perror(" data recv failed");
	} else 
	{
		printf("\n IP address and port number received from main server: [%s] \n ",operation_server_info);
		p=strtok(operation_server_info,":");
		if(p!=NULL)
		{
			strcpy(ip,p);
			p=strtok(NULL,":");
			if(p!=NULL)
				strcpy(port,p);
		}
		
        	strcpy(operation_server_ip,ip);
   		operation_server_port=atoi(port);
		
		
		operation_sock = socket(PF_INET, SOCK_STREAM, 0); 	
        	if(operation_sock < 0) {                        
			perror("operation socket failed"); 
			exit(1);
		}
		operation_server.sin_family = PF_INET;
		operation_server.sin_addr.s_addr = inet_addr(operation_server_ip);
		operation_server.sin_port = htons(operation_server_port);

		if (connect (operation_sock, (struct sockaddr *) &operation_server, sizeof(operation_server)) < 0) {
		perror(" connection failed");
		exit(1);
 		}
	
		printf("\n Enter the numbers : ");
		//gets(operation_buff);
		fgets(operation_buff,10, stdin);
		int len2 = strlen(operation_buff);
		if (len2 > 0 && operation_buff[len2-1] == '\n') {
			operation_buff[len2-1] = '\0';
		}

		if (send(operation_sock, operation_buff, sizeof(operation_buff), 0) < 0) {
			perror(" data send failed");
			exit(1);
		} else {
			printf("\n Numbers are sent to the operation server: [%s]", operation_buff);
		}
		
		if(recv(operation_sock,result,sizeof(result),0) < 0){
			perror(" data recv failed");
		} else 
		{
			printf("\n Result received from operation server: %s \n ",result);
		
		}
	}
	sleep(3);	
	close(sock);
        sleep(3);
	close(operation_sock);
		
return 0;	
}
