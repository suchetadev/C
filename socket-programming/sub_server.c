/* This is a substraction server*/

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
	int ret_val;
	
	char number1[20]="",number2[20]="";
	int num1,num2;
	char *p;
	int result;
	
	/* create a socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);  
	if (sock < 0 ) {
		perror(" Failed to create socket");
		exit(1);
	}

	server.sin_family = PF_INET;
	server.sin_port = htons(5002);
	server.sin_addr.s_addr = INADDR_ANY;	

	/* bind the socket */
	if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
		perror(" Failed to bind socket");
		exit(1);
	}

	/* listen on the socket */
	listen(sock,5);
	printf("\n substraction server listening...\n");

	/* accept connection from client */
	do {
		client_sock = accept(sock, (struct sockaddr *) 0, 0);
		if (client_sock == -1) {
			perror("accept failed");
		}
		else {
			printf("\n substraction client connected...\n");
			memset(buffer, 0, sizeof(buffer));
			/* read/write with client */
			
			if ((ret_val = recv(client_sock, buffer, sizeof(buffer), 0)) < 0) {
				perror(" ERRO reading stream message ");
			}
			else if (ret_val == 0) {
				perror(" ending connection ");
			} 
			else {
			
				p=strtok(buffer,",");
				if(p!=NULL)
				{
					strcpy(number1,p);
					p=strtok(NULL,":");
					if(p!=NULL)
						strcpy(number2,p);

				}
				num1=atoi(number1);
				num2=atoi(number2);
				result=num1-num2;
				char str_result[5];
				sprintf(str_result, "%d", result);
				if(send(client_sock,str_result,sizeof(str_result),0)<0){
					perror("failed to send ......");
					break;
				}
			}
			sleep(10);	
			close(client_sock);
		} 

	} while (1);
	
	
	/* close the socket */
	close(sock);

return 0;
}
