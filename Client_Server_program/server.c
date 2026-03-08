#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define BUFSIZE 256
void breakBuf(char buf[],char newbuf[][20],int *ptrbuf);/*Breaks the given mathematical operation in to segments*/
int stackBufPop(char stkbuf[][20],int *ptrstkbuf,char newbufmeta[][20],int *ptrbufmeta);/*Used to pop an element from the stack to create the metathematic form*/
int stackBufPush(char st[],char stkbuf[][20],int *ptrbufmeta);/*Used to push an element from the stack to create the metathematic form*/
int stackPopRes(int res[],int *ptrstkres,int *flag);/*Used to pop an element from the stack to calculate the results*/
int stackPushRes(char newmeta[],int res[],int *ptrstkres);/*Used to push an element from the stack to calculate the results*/

int main(int argc,char *argv[])
{
	int socknum,clisocknum,portnum,rwnum,i,clilen,flagbuf=1,flag,clos=0,open=0,j,plbuf=0,*ptrbuf=&plbuf,plstkbuf=BUFSIZE;
	int dif,*ptrstkbuf=&plstkbuf,plbufmeta=0,*ptrbufmeta=&plbufmeta,stkres[BUFSIZE],plstkres=BUFSIZE,*ptrstkres=&plstkres,flagres;
	char buf[BUFSIZE],newbuf[BUFSIZE][20],newbufmeta[BUFSIZE][20],stkbuf[BUFSIZE][20],res[20];
	char strer[]="You have not given a numerical expression that is calculable";
	struct sockaddr_in servad,cliad;
	/*From line 24 to line 79 a check is made to see if the information has been given correctly for the port number an creates a TCP connection*/
	if(argc!=2)
	{
		printf("You have given an incorrect number of data \n");
		exit(1);
	}
	if((strlen(argv[1])>1) && (strlen(argv[1])<6))
	{
		for(i=0;i<strlen(argv[1]);i++)
		{
			if(isdigit(argv[1][i])==0)
			{
				printf("You have not given a valid port number\n");
				exit(1);
			}
		}
	}
	else
	{
		printf("You have not given a valid port number\n");
		exit(1);
	}
	portnum=atoi(argv[1]);
	
	socknum=socket(AF_INET,SOCK_STREAM,0);
	if(socknum<0)
	{
		printf("There was a problem opening the socket\n");
		exit(1);
	}
	bzero((char *)&servad,sizeof(servad));
	servad.sin_family=AF_INET;
	servad.sin_addr.s_addr=INADDR_ANY;
	servad.sin_port=htons(portnum);
	
	if(bind(socknum,(struct sockaddr *)&servad,sizeof(servad))<0)
	{
		printf("There was a problem on binding\n");
		exit(1);
	}
	
	listen(socknum,5);
	clilen=sizeof(cliad);
	clisocknum=accept(socknum,(struct sockaddr *)&cliad,&clilen);
	if(clisocknum<0)
	{
		printf("There was a problem on accept\n");
		exit(1);
	}
	
	bzero(buf,BUFSIZE);
	rwnum=read(clisocknum,buf,BUFSIZE-1);
	if(rwnum<0)
	{
		printf("There was a problem reading from the socket\n");
		exit(1);
	}
	/*From line 80 to line 260 a check is made to see if the information has been given correctly for the mathematical operation*/
	buf[strlen(buf)-1]='\0';
	for(i=0;buf[i]!='\0';i++)
	{
		if((buf[i]<'0' || buf[i]>'9') && buf[i]!='(' && buf[i]!=')' && buf[i]!='+' && buf[i]!='-' && buf[i]!='*' && buf[i]!='/' && buf[i]!='%' && buf[i]!='.')
		{
			flagbuf=0;
		}	
	}
	for(i=0;buf[i]!='\0';i++)
	{
		if(buf[i]=='(')
		{
			open++;
		}
		else if(buf[i]==')')
		{
			clos++;
		}
	}
	if(open!=clos)
	{
		flagbuf=0;
	}
				
	for(i=0;buf[i]!='\0';i++)
	{
		if(buf[i]=='+' ||buf[i]=='*')
		{
			if(buf[i-1]!='\0')
			{
				if((buf[i-1]<'0' || buf[i-1]>'9') && buf[i-1]!=')')
				{
					flagbuf=0;
				}
			}
			else if(buf[i]!='+' && buf[i]!='-' )
			{
				flagbuf=0;
			}
			if(buf[i+1]!='\0')
			{
				if((buf[i+1]<'0' || buf[i+1]>'9') && buf[i+1]!='(')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
		}
		if(buf[i]=='-')
		{
			if(buf[i-1]!='\0')
			{
				if((buf[i-1]<'0' || buf[i-1]>'9') && buf[i-1]!=')' && buf[i-1]!='(')
				{
					flagbuf=0;
				}
			}
			else if(buf[i]!='+' && buf[i]!='-' )
			{
				flagbuf=0;
			}
			if(buf[i+1]!='\0')
			{
				if((buf[i+1]<'0' || buf[i+1]>'9') && buf[i+1]!='(')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
		}
		if(buf[i]=='/' ||buf[i]=='%')
		{
			if(buf[i-1]!='\0')
			{
				if((buf[i-1]<'0' || buf[i-1]>'9') && buf[i-1]!=')')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
			if(buf[i+1]!='\0')
			{
				if((buf[i+1]<'1' || buf[i+1]>'9') && buf[i+1]!='(')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
		}
		else if(buf[i]=='(')
		{
			if(buf[i-1]!='\0')
			{
				if(buf[i-1]!='+' && buf[i-1]!='-' && buf[i-1]!='/' && buf[i-1]!='*' && buf[i-1]!='%' && buf[i-1]!='(')
				{
					flagbuf=0;
				}
			}
			if(buf[i+1]!='\0')
			{
				if((buf[i+1]<'0' || buf[i+1]>'9') && buf[i+1]!='(' && buf[i+1]!='-')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
		}
		else if(buf[i]==')')
		{
			if(buf[i-1]!='\0')
			{
				if((buf[i-1]<'0' || buf[i-1]>'9') && buf[i-1]!=')')
				{
					flagbuf=0;
				}
			}
			else 
			{
				flagbuf=0;
			}
			if(buf[i+1]!='\0')
			{
				if((buf[i+1]>='0' && buf[i+1]<='9') || buf[i+1]=='(' || buf[i+1]=='.')
				{
					flagbuf=0;
				}
			}
		}
		else if(buf[i]=='.')
		{
			if(buf[i-1]!='\0')
			{
				if(buf[i-1]<'0' || buf[i-1]>'9')
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
			if(buf[i+1]!='\0' && buf[i+2]!='\0' && buf[i+3]!='\0')
			{
				if((buf[i+1]<'0' || buf[i+1]>'9') || (buf[i+2]<'0' || buf[i+2]>'9') || (buf[i+3]<'0' || buf[i+3]>'9'))
				{
					flagbuf=0;
				}
			}
			else
			{
				flagbuf=0;
			}
		}
	}
	if(flagbuf==0)
	{
		printf("\n");
		rwnum=write(clisocknum,strer,strlen(strer));
		if(rwnum<0)
		{
			printf("There was an error writing to socket\n");
			exit(1);
		}
		exit(1);
	}
	/*For line 262 to line 362 it creates the metathematic form and calculates the result*/
	for(i=0;i<BUFSIZE;i++)
	{
		for(j=0;j<20;j++)
		{
			newbuf[i][j]='\0';
		}
	}
	for(i=0;i<BUFSIZE;i++)
	{
		for(j=0;j<20;j++)
		{
			newbufmeta[i][j]='\0';
		}
	}
		
	breakBuf(buf,newbuf,ptrbuf);
	for(i=0;i<=*ptrbuf;i++)
	{
		if((strncmp(newbuf[i]," ",1)==0 || strncmp(newbuf[i],"(",1)==0 || strncmp(newbuf[i],")",1)==0) && strlen(newbuf[i])==1)
		{
			dif++;
		}
	}
	for(i=0;i<*ptrbuf;i++)
	{
		if((strncmp(newbuf[i],"+",1)==0 ||strncmp(newbuf[i],"-",1)==0 || strncmp(newbuf[i],"/",1)==0 || strncmp(newbuf[i],"*",1)==0 || strncmp(newbuf[i],"%",1)==0) && strlen(newbuf[i])==1)
		{
			flag=stackBufPush(newbuf[i],stkbuf,ptrstkbuf);
			if(flag==0)
			{
				rwnum=write(clisocknum,strer,strlen(strer));
				if(rwnum<0)
				{
					printf("There was an error writing to socket\n");
					exit(1);
				}
				exit(1);
			}
		}
		else if(strncmp(newbuf[i],")",1)==0)
		{
			flag=stackBufPop(stkbuf,ptrstkbuf,newbufmeta,ptrbufmeta);
			if(flag==0)
			{
				rwnum=write(clisocknum,strer,strlen(strer));
				if(rwnum<0)
				{
					printf("There was an error writing to socket\n");
					exit(1);
				}
				exit(1);
			}
			else
			{
				plbufmeta++;
			}
		}
		else if(strncmp(newbuf[i],"(",1)!=0)
		{
			strcpy(newbufmeta[*ptrbufmeta],newbuf[i]);
			*ptrbufmeta=*ptrbufmeta+1;
		}
	}
	if((*ptrbuf)-dif!=*ptrbufmeta)
	{
		rwnum=write(clisocknum,strer,strlen(strer));
		if(rwnum<0)
		{
			printf("There was an error writing to socket\n");
			exit(1);
		}
		exit(1);
	}
	for(i=0;i<*ptrbufmeta;i++)
	{
		flagres=stackPushRes(newbufmeta[i],stkres,ptrstkres);
		if(flagres==-1)
		{
			rwnum=write(clisocknum,strer,strlen(strer));
			if(rwnum<0)
			{
				printf("There was an error writing to socket\n");
				exit(1);
			}
			exit(1);
		}
	}
	sprintf(res,"%d",stkres[BUFSIZE-1]);
	rwnum=write(clisocknum,res,strlen(res));
	if(rwnum<0)
	{
		printf("There was an error writing to socket\n");
		exit(1);
	}
	bzero(buf,BUFSIZE);
	rwnum=read(clisocknum,buf,BUFSIZE-1);
	if(close(clisocknum)<0)
	{
		printf("There was a problem in closing\n");
		exit(0);
	}
	return 0;
} 


void breakBuf(char buf[],char newbuf[][20],int *ptrbuf)
{
	int i=0,s,j=0,pl=0,flag=0;
	s=strlen(buf);
	while(i<s)
	{
		if(buf[i]=='(' && buf[i+1]=='-')
		{
			strncpy(newbuf[*ptrbuf],"(",1);
			*ptrbuf=*ptrbuf+1;
			j=i+2;
			while((buf[j]>='0' && buf[j]<='9') || buf[j]=='.')
			{	
				pl++;
				j++;
			}
			strncpy(newbuf[*ptrbuf],buf+(i+1),pl+1);
			flag=2;
		}	
		if(buf[i]=='-' && i-1<0)
		{
			j=i+1;
			while((buf[j]>='0' && buf[j]<='9') || buf[j]=='.')
			{	
				pl++;
				j++;
			}
			strncpy(newbuf[*ptrbuf],buf+i,pl+1);
			flag=1;
		}
		else if(buf[i]>='0' && buf[i]<='9')
		{
			j=i;
			while((buf[j]>='0' && buf[j]<='9') || buf[j]=='.')
			{	
				pl++;
				j++;
			}
			strncpy(newbuf[*ptrbuf],buf+i,pl);
		}
		else if(flag!=2 && flag!=3)
		{
			newbuf[*ptrbuf][0]=buf[i];
			pl=1;
		}
		if(pl!=0 && flag==0)
		{
			i=i+pl;
			(*ptrbuf)=(*ptrbuf)+1;
			pl=0;
		}
		else if(pl!=0 && flag==1)
		{
			i=i+pl+1;
			(*ptrbuf)=(*ptrbuf)+1;
			pl=0;
			flag=0;
		}
		else if(pl!=0 && flag==2)
		{
			i=i+pl+2;
			(*ptrbuf)=(*ptrbuf)+1;
			pl=0;
			flag=0;
		}
		else
		{
			i++;
		}		
	}
}

int stackBufPop(char stkbuf[][20],int *ptrstkbuf,char newbufmeta[][20],int *ptrbufmeta)
{
	int i;
	if(*ptrbufmeta<BUFSIZE)
	{
		strcpy(newbufmeta[*ptrbufmeta],stkbuf[*ptrstkbuf]);
		for(i=0;stkbuf[*ptrstkbuf][i]!='\0';i++)
		{
			stkbuf[*ptrstkbuf][i]='\0';
		}
		*ptrstkbuf=*ptrstkbuf+1;
		return 1;
	}
	else
	{
		return 0;
	}	
}


int stackBufPush(char st[],char stkbuf[][20],int *ptrbufmeta)
{
	if((*ptrbufmeta)-1>=0)
	{
		*ptrbufmeta=*ptrbufmeta-1;
		strcpy(stkbuf[*ptrbufmeta],st);
		return 1;
	}
	else
	{
		return 0;
	}
}


int stackPopRes(int res[],int *ptrstkres,int *flag)
{
	int apot;
	if(*ptrstkres<BUFSIZE)
	{
		apot=res[*ptrstkres];
		res[*ptrstkres]=0;
		*ptrstkres=*ptrstkres+1;
		*flag=1;
		return apot;
	}
	else
	{
		*flag=-1;
		return 0;
	}	
}


int stackPushRes(char newmeta[],int res[],int *ptrstkres)
{
	int i=0,f,*flag=&f,pl=0,s=strlen(newmeta),pol,tl,x,y,dap,apot,j=0;
	
	if((strncmp(newmeta,"+",1)==0 ||strncmp(newmeta,"-",1)==0 || strncmp(newmeta,"/",1)==0 || strncmp(newmeta,"*",1)==0 || strncmp(newmeta,"%",1)==0) && s==1)    
	{
		if((*ptrstkres)-1>=0)
		{
			x=stackPopRes(res,ptrstkres,flag);
			if(*flag==-1)
			{
				return -1;
			}
			y=stackPopRes(res,ptrstkres,flag);
			if(*flag==-1)
			{
				return -1;
			}	
			*ptrstkres=*ptrstkres-1;
		}
		if(strncmp(newmeta,"+",1)==0)
		{
			res[*ptrstkres]=x+y;
			return 1;
		}
		else if(strncmp(newmeta,"*",1)==0)
		{
			res[*ptrstkres]=x*y;
			return 1;
		}
		else if(strncmp(newmeta,"-",1)==0)
		{
			res[*ptrstkres]=y-x;
			return 1;
		}
		else if(strncmp(newmeta,"/",1)==0)
		{
			if(x==0)
			{
				return -1;
			}
			else
			{
				res[*ptrstkres]=y/x;
				return 1;
			}
		}
		else if(strncmp(newmeta,"%",1)==0)
		{
			if(x==0)
			{
				return -1;
			}
			else
			{
				res[*ptrstkres]=y%x;
				return 1;
			}
		}
	}
	else
	{
		pol=1;
		apot=0;
		for(i=1;i<s;i++)
		{
			if(newmeta[i]!='.')
			{
				pol=pol*10;
			}
		}
		for(i=0;i<s;i++)
		{
			if(newmeta[i]!='.' && newmeta[i]!='-')
			{		
				apot=apot+((newmeta[i]-'0')*pol);
				pol=pol/10;
			}
		}
		if((*ptrstkres)-1>=0)
		{
			*ptrstkres=*ptrstkres-1;
			if(newmeta[0]=='-')
			{
				res[*ptrstkres]=-apot;
			}
			else
			{
				res[*ptrstkres]=apot;
			}
			return 1;
		}
		else
		{
			return -1;
		}
	}
}
