/* This is a main sever program. It will accept the operation from client and it will send the ip address and port number of a server who will perform that operation*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

	/* variables */
	int sock;
	struct sockaddr_in server;
	int client_sock;
	char buffer[1024];
	int ret_val,ret_val1,ret_val2,ret_val3,ret_val4;
	
	char add_server_info[]="127.0.0.1:5001";
        char sub_server_info[]="127.0.0.1:5002";
	char multi_server_info[]="127.0.0.1:5003";
	char div_server_info[]="127.0.0.1:5004";
	
	
	/* create a socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);  
	if (sock < 0 ) {
		perror(" Failed to create socket");
		exit(1);
	}

	server.sin_family = PF_INET;
	server.sin_port = htons(5000);
	server.sin_addr.s_addr = INADDR_ANY;	

	/* bind the socket */
	if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
		perror(" Failed to bind socket");
		exit(1);
	}

	/* listen on the socket */
	listen(sock,5);
	printf("\nserver listening...\n");

	/* accept connection from client */
	do {
		client_sock = accept(sock, (struct sockaddr *) 0, 0);
		if (client_sock == -1) {
			perror("accept failed");
		}
		else {
			printf("\nclient connected...\n");
			memset(buffer, 0, sizeof(buffer));
			/* read/write with client */
			
			if ((ret_val = recv(client_sock, buffer, sizeof(buffer), 0)) < 0) {
				perror(" ERRO reading stream message ");
			}
			else if (ret_val == 0) {
				perror(" ending connection ");
			} 
			else {
				printf("\nRequest operation got from client: [%s]", buffer);
			}
			if(strcmp(buffer,"ADD")==0){
				ret_val1=send(client_sock,add_server_info,sizeof(add_server_info),0);
				
 			}
                        else if(ret_val1<0){
			       perror("failed to send ip and port number");
			       break;
			} 
			
			if(strcmp(buffer,"SUB")==0){
				ret_val2=send(client_sock,sub_server_info,sizeof(sub_server_info),0);
				
 			}
                        else if(ret_val2<0){
			       perror("failed to send ip and port number");
			       break;
			} 
			
			if(strcmp(buffer,"MUL")==0){
				ret_val3=send(client_sock,multi_server_info,sizeof(multi_server_info),0);
			
				
 			}
                        else if(ret_val3<0){
			       perror("failed to send ip and port number");
			       break;
			} 
			
			if(strcmp(buffer,"DIV")==0){
				ret_val4=send(client_sock,div_server_info,sizeof(div_server_info),0);
				
				
 			}
                        else if(ret_val4<0){
			       perror("failed to send ip and port number");
			       break;
			} 
			close(client_sock);
		} 

	} while (1);
	
	
	/* close the socket */
	close(sock);

return 0;
}
