#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#define BUFSIZE 256
#define TOKSIZE 10

int main(int argc,char *argv[])
{
	int socknum,portnum,rwnum,i,ipint,j,arrtoklen=0;
	char buf[BUFSIZE],*arrtok[TOKSIZE];
	struct sockaddr_in servad;
	struct hostent *serv;
	/*From line 19 to line 111 a check is made to see if the information has been given correctly for the port number and the IP address an creates a TCP connection*/
	if(argc!=3)
	{
		printf("You have entered the wrong data number\n");
		exit(1);
	}
	if(strlen(argv[1])>6 && strlen(argv[1])<16)
	{
		 arrtok[0]=strtok(argv[1],".");
		 if(arrtok[0]==NULL)
		 {
		 	printf("You have entered the wrong IP addres\n");
		 	exit(0);
		 }
		 arrtoklen++;
		 for(i=1;i<TOKSIZE;i++)
		 {
		 	arrtok[i]=strtok(NULL,".");
		 	if(arrtok[i]==NULL) break;
		 	arrtoklen++;
		 }
		 if(arrtoklen==4)
		 {
		 	for(i=0;i<arrtoklen;i++)
		 	{
		 		for(j=0;j<strlen(arrtok[i]);j++)
		 		{
		 			if(isdigit(arrtok[i][j])==0)
		 			{
		 				printf("You have entered the wrong IP addres\n");
		 				exit(0);
		 			}
		 		}
		 		ipint=atoi(arrtok[i]);
		 		if(ipint<0 || ipint>255)
		 		{
		 			printf("You have entered the wrong IP addres\n");
					exit(0);
	 			}
		 	}
		 }
		 else
		 {
		 	printf("You have entered the wrong IP addres\n");
			exit(0);	
		 }
	}
	else
	{
		printf("You have entered the wrong IP addres\n");
		exit(0);	
	}
	
	if((strlen(argv[2])>1) && (strlen(argv[2])<6))
	{
		for(i=0;i<strlen(argv[2]);i++)
		{
			if(isdigit(argv[2][i])==0)
			{
				printf("You have not given a valid port number\n");
				exit(0);
			}
		}
	}
	else
	{
		printf("You have not given a valid port number\n");
		exit(0);
	}
	portnum=atoi(argv[2]);
	socknum=socket(AF_INET,SOCK_STREAM,0);
	if(socknum<0)
	{
		printf("There was a problem opening the socket\n");
		exit(0);
	}
	
	serv = gethostbyname (argv[1]);
	if(serv==NULL)
	{
		printf("There is no such host\n");
		exit(0);
	}
	bzero((char *)&servad,sizeof(servad));
	servad.sin_family=AF_INET;
	bcopy((char *)serv->h_addr,(char *)&servad.sin_addr.s_addr,serv->h_length);
	servad.sin_port=htons(portnum);
	
	if(connect(socknum,(struct sockaddr *)&servad,sizeof(servad))<0)
	{
		printf("there was a problem on connecting\n");
		exit(0);
	}
	/*From line 113 to line 145 ask the user to give it the mathematical operation,send it to the server to calculate it and it displays it to the user*/ 
	printf("Give the mathimatical operation :");
	bzero(buf,BUFSIZE);
	fgets(buf,BUFSIZE-1,stdin);
	rwnum=write(socknum,buf,strlen(buf));
	if(rwnum<0)
	{
		printf("There was an error writing to socket\n");
		exit(0);
	}
	bzero(buf,BUFSIZE);
	rwnum=read(socknum,buf,BUFSIZE-1);
	if(rwnum<0)
	{
		printf("There was a problem reading from the socket\n");
		exit(0);
	}
	else
	{
		for(i=0;i<strlen(buf);i++)
		{
			if(isdigit(buf[i])==0 && buf[i]!='-')
			{
				printf("%s\n",buf);
				exit(0);
			}
		}
	}
	printf("The result of the arithmetic operation is :%s\n",buf);
	if(close(socknum)<0)
	{
		printf("There was a problem in closing\n");
		exit(0);
	}	
	return 0;
}
