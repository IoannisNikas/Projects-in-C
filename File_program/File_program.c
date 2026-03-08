/* Ioannis Nikas
   AM:2022202300148
   dit23148@go.uop.gr
   
   Konstantinos Papapanagiotou
   AM:2022202300225
   dit23225@go.uop.gr
  */
  
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
	int year;
	int month;
	int day;
}mydate;

typedef struct
{
	int hour;
	int minutes;
}mytime;

typedef struct bilList
{
	char name[100];
	char cac[100];
	char act[100];
	char country[100];
	char sex[100];
	double billions;
	char ac[13];
	mydate birthdate;
	mytime birthtime;
	struct bilList *next;
	struct bilList *prev;
}billionaire;

billionaire *insert(char **data,billionaire *head,int y,int mo,int d,int mi,int h);
billionaire *delete(billionaire *head,char possision);
void insertFile(billionaire *head,FILE *file);
void findBil(billionaire *head,char infob[]);
int main (void)
{
	srand(time(NULL));
	int i,j,space=0,slash=0,comma=0,y=0,mo=0,d=0,colon=0,semicolon=0,mi=0,h=0,pl=0,flag=0,len=0,gramma=0;
	char infob[300]={0} ,*data[7]={0},fl[100]={0};
	double sum=0;
	billionaire *head,*tmp,*tmp2;
	FILE *file;
	head=NULL;
	while(1)
	{
		printf("To enter a new billioner on the list you must give first of all the command 'newbil' then live a space and after that:\n");
		printf("1.Give the first and then the last name of the billioner\n");
		printf("2.Give the city and the cuntry of his work activity seperated by '/' caracter.If you don't now some of them tipe 'Unknown' or the caracter '?'");
		printf("3.Give the main work activities separated by ',' caracter\n");
		printf("4.Give the country of origin\n");
		printf("5.Give the sex of the billioner('M' for men,'F' for woman,'G' for gay,'N' for non binaire or 'E' for else)\n");
		printf("6.Give the the day,month and year separated by '/' caracter live a space and then give the hour and the minutes of his/her birth seperated by ':' caracter.If you don't now this informations tipe '01/01/1900 0:00'\n");
		printf("7.Give the wealth in billion Dollars\n");
		printf("You mast separate all the data with the ';' caracter\n");
		printf("If you want to finish the game give the comand 'exit'\n");
		printf("If you want to delete one element by the end of the list give the comand 'deleteN' or if you want to delete the first element of the list give the comand 'deleteO'\n"); 
		printf("If you want to save the data from the list to a file give the comand 'save (file name)'\n");
		printf("If you want to calculate the sum of the wealth of billionaires give the command 'sum'\n");
		printf("If you want to print all the elements in the list give the command 'findN *' or 'findC *' or 'findS *'\n");
		printf("\n");
		printf("$> ");
		fgets(infob,sizeof(infob),stdin);
		if(strncmp(infob,"exit",4)==0)
		{
			if(head!=NULL)
			{
				tmp=head;
				tmp2=head;
				while(tmp->next!=head)
				{
					tmp2=tmp;
					tmp=tmp->next;
					free(tmp2);
				}
				free(tmp);
			}
			printf("You gave the comand witch end this program!!!\n");
			exit(0);
		}
		if(strncmp(infob,"newbil ",7)==0)
		{
			for(i=0;infob[i]!='\0';i++)
			{
				if(infob[i]==';')
				{
					semicolon++;
				}
			}
			if(semicolon!=7)
			{
				printf("You forgot to put some of the ';' characters.Give the data for a new billionaire\n");
				flag=1;
			}
			semicolon=0;
			data[0]=strtok(infob+7,";");
			if(data[0]==NULL)
			{
				printf("You have not gave the data the right may.Give new ones\n");
				flag=1;
			}
			else
			{
				for(i=1;i<7;i++)
				{
					data[i]=strtok(NULL,";");
					if(data[i]==NULL)
					{
						break;
					}
				}
					
				for(i=0;data[0][i]!='\0';i++)
				{
					if(isalpha(data[0][i])==0 && data[0][i]!='&' && data[0][i]!=' ')
					{
						printf("You have not privided the correct informations in the field of the firs and last name.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				for(i=1;data[0][i]!='\0';i++)
				{
					if(data[0][i]==' ')
					{
						space++;
							
					}
				}
				if(space==0)
				{
					printf("You have not privided the correct informations in the field of the firs and last name.Give the data for a new billionaire\n");
					flag=1;
				}
				else
				{
					data[0][0]=toupper(data[0][0]);
					for(i=0;data[0][i]!='\0';i++)
					{
						if(data[0][i]==' ')
						{
							data[0][i+1]=toupper(data[0][i+1]);
						}
					}
					space=0;
				}
				space=0;
				len=strlen(data[0]);
				for(i=0;data[0][i]!='\0';i++)
				{
					if(isalpha(data[0][i])!=0)
					{
						gramma++;
					}
				}
				if(len<5 || gramma<4)
				{
					printf("You have not privided the correct informations in the field of the firs and last name.Give the data for a new billionaire\n");
					flag=1;
				}
				len=0;
				gramma=0;
					
				slash=0;
				for(i=0;data[1][i]!='\0';i++)
				{
					if(data[1][i]=='/')
					{
						slash++;
					}
				}
				if(slash==0)
				{
					printf("You have not privided the correct informations in the field of cuntry and city.Give the data for a new billionaire\n");
					flag=1;
				}
				else
				{
					slash=0;
				}
				for(i=0;data[1][i]!='\0';i++)
				{
					if((isalpha(data[1][i]))==0  && data[1][i]!='/' && data[1][i]!='?')
					{
						printf("You have not privided the correct informations in the field of cuntry and city.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				len=strlen(data[1]);
				for(i=0;data[1][i]!='\0';i++)
				{
					if(data[1][i]=='/')
					{
						if(i-1<0 || (isalpha(data[1][i-1])==0 && data[1][i-1]!='?')|| i+1>len-1 || (isalpha(data[1][i+1])==0 && data[1][i-1]!='?'))
						{
							printf("You have not privided the correct informations in the field of cuntry and city.Give the data for a new billionaire\n");
							flag=1;
						}					
					}
				}
				if(len<3)
				{
					printf("You have not privided the correct informations in the field of cuntry and city.Give the data for a new billionaire\n");
					flag=1;
				}
				len=0;
				for(i=0;data[2][i]!='\0';i++)
				{
					if((isalpha(data[2][i]))==0 && data[2][i]!=',' && data[2][i]!=' ')
					{
						printf("You have not privided the correct informations in the field of main work activities.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				len=strlen(data[2]);
				if(len<2)
				{
					printf("You have not privided the correct informations in the field of main work activities.Give the data for a new billionaire\n");
					flag=1;
				}
				len=0;
					
				for(i=0;data[3][i]!='\0';i++)
				{
					if((isalpha(data[3][i]))==0)
					{
						printf("You have not privided the correct informations in the field of country.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				len=strlen(data[2]);
				if(len<2)
				{
					printf("You have not privided the correct informations in the field of main work activities.Give the data for a new billionaire\n");
					flag=1;
				}
				len=0;
					
				if((data[4][0]!='M' && data[4][0]!='F' && data[4][0]!='N' && data[4][0]!='G' && data[4][0]!='E') || strlen(data[4])!=1)
				{
					printf("You have not privided the correct informations in the field of sex.Give the data for a new billionaire\n");
					flag=1;
				} 
				
				for(i=0;data[5][i]!='\0';i++)
				{
					if((isdigit(data[5][i]))==0 && data[5][i]!=':'&& data[5][i]!=' ' && data[5][i]!='/')
					{
						printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				len=strlen(data[5]);
				if(len!=16)
				{
					printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
					flag=1;
				}	
				for(i=0;data[5][i]!='\0';i++)
				{
					if(data[5][i]=='/')
					{
						if(i-1<0 || isdigit(data[1][i-1])!=0 || i+1>len-1 || isdigit(data[1][i+1])!=0)
						{
							printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
							flag=1;
						}
					}
				}
				for(i=0;data[5][i]!='\0';i++)
				{
					if(data[5][i]==':')
					{
						if(i-1<0 || isdigit(data[1][i-1])!=0 || i+1>len-1 || isdigit(data[1][i+1])!=0)
						{
							printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
							flag=1;
						}
					}
				}
				for(i=0;data[5][i]!='\0';i++)
				{
					if(data[5][i]==' ')
					{
						if(i-1<0 || isdigit(data[1][i-1])!=0 || i+1>len-1 || isdigit(data[1][i+1])!=0)
						{
							printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
							flag=1;
						}
					}
				}
				len=0;			
				for(i=0;data[5][i]!='\0';i++)
				{
					if(data[5][i]==':')
					{
						colon++;
					}
					else if(data[5][i]=='/')
					{
						slash++;
					}
					else if(data[5][i]==' ')
					{
						space++;
					}
				}
				if(colon>2 || slash>3 || space>1)
				{
					printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
					flag=1;
				}
				else
				{
					d=(data[5][0]-'0')*10+(data[5][1]-'0');
					mo=(data[5][3]-'0')*10+(data[5][4]-'0');
					y=(data[5][6]-'0')*1000+(data[5][7]-'0')*100+(data[5][8]-'0')*10+(data[5][9]-'0');
					h=(data[5][11]-'0')*10+(data[5][12]-'0');
					mi=(data[5][14]-'0')*10+(data[5][15]-'0');
					if((d<0 || d>31) || (mo<0 || mo>12) || (h<0 || h>24) || (mi<0 || mi>59) || y<1900)
					{
						printf("You have not privided the correct informations in the field of the birthdate and the birthtime.Give the data for a new billionaire\n");
						flag=1;
					}
				}
				colon=0;
				space=0;
				slash=0;
					
				for(i=0;data[6][i]!='\0';i++)
				{
					if((isdigit(data[6][i]))==0 & data[6][i]!='.')
					{
						printf("You have not privided the correct informations in the field of the wealth.Give the data for a new billionaire\n");
						flag=1;
					}
				}		
			}
			if(flag==0)
			{
				head=insert(data,head,y,mo,d,mi,h);
			}
		}
			
		else if(strncmp(infob,"deleteN",7)==0)
		{
			head=delete(head,'N');
		}
		else if(strncmp(infob,"deleteO",7)==0)
		{
			head=delete(head,'O');
		}
		
		else if(strncmp(infob,"save ",5)==0)
		{
			do
			{
				strcpy(fl,infob+5);
				file=fopen(fl,"w");
				if(file==NULL)
				{
					printf("Something went wrong with the file name.Please give a new one\n");
				}
			}while(file==NULL);
			insertFile(head,file);
			fclose(file);
		}
		else if(strncmp(infob,"sum",3)==0)
		{
			if(head!=NULL)
			{
				sum=0;
				tmp=head;
				while(tmp->next!=head)
				{
					sum=sum+tmp->billions;
					tmp=tmp->next;
				}
				sum=sum+tmp->billions;
				printf("The sum of the wealth of billionaires is :%.4f\n",sum);
			}
			else
			{
				printf("The list with the billionaires is empty\n");
			}
		}
		else if(strncmp(infob,"find",4)==0)
		{
			findBil(head,infob);
		}
		
		else
		{
			printf("The command you gave was not found!!!Please give a new one\n");
		}	
		
		printf("\n");
		flag=0;
	}
	return 0;
}



billionaire *insert(char **data, billionaire *head,int y,int mo,int d,int mi,int h)
{
	int i,par[10],pl=0,sum=0,mon=0,cd=0,pro=1;
	double ar;
	char un[100]="Unknown",newc[100]={0};
	billionaire *new,*tmp=head,*tmp2=head;
	
	new=(billionaire *)malloc(sizeof(billionaire));
	if(new==NULL)
	{ 	
		printf("not enaught memory .Please run the program again\n");
		exit(0);
	}
	 	
	strcpy(new->name,data[0]);
	strcpy(new->act,data[2]);
	strcpy(new->country,data[3]);
	strcpy(new->sex,data[4]);
	new->birthdate.year=y;
	new->birthdate.month=mo;
	new->birthdate.day=d;
	new->birthtime.hour=h;
	new->birthtime.minutes=mi;
	new->billions=atof(data[6]);
	for(i=0;data[1][i]!='\0';i++)
	{
		if(data[1][i]=='/')
		{
			if(i-1>=0 && data[1][i-1]=='?'&& data[1][i+1]!='\0' && data[1][i+1]=='?')
			{	
				newc[0]='/';
				strcat(un,newc);
				strcat(un,"Unknown");
				data[1]=un;
			}
			else if(i-1>=0 && data[1][i-1]=='?')
			{
				for(pl=0;data[1][i+pl]!='\0';pl++)
				{
					newc[pl]=data[1][i+pl];
				}
				strcat(un,newc);
				data[1]=un;
				break;
			}
			else if(data[1][i+1]!='\0' && data[1][i+1]=='?')
			{
							
		        	for(pl=0;pl<i+1;pl++)
				{
					newc[pl]=data[1][pl];
				}
				strcat(newc,un);
				data[1]=newc;
			}
		}
	}
	strcpy(new->cac,data[1]);
	
	for(i=0;i<12;i++)
	{
		if(i!=5 && i!=11)
		{
			ar=(double)rand()/((double)RAND_MAX+1);
			ar='0'+ar*9;
			new->ac[i]=(char)ar;
			par[pl]=(int)ar;
			pl++;
		}
		else
		{
			new->ac[i]='-';
		}
	}
	for(i=0;i<10;i++)
	{
		if(i%2!=0)
		{
			par[i]=par[i]*2;
			if(par[i]>10)
			{
				mon=par[i]%10;
				sum=sum+mon+1;
			}
			else
			{
				sum=sum+par[i];
			}
		}
		else
		{
			sum=sum+par[i];
		}
	}
	pro=9*sum;
	cd=pro%10;	
	new->ac[12]=cd+'0';
			
	if(head==NULL)
	{
		new->next=new;
		new->prev=new;
		return new;
	}
	else
	{
		tmp=head;
		while(tmp->next!=head)
		{
			tmp=tmp->next;
		}
		tmp->next=new;
		new->prev=tmp;
		new->next=head;
		head->prev=new;
		return head;
	}
}



billionaire *delete(billionaire *head,char possision)
{
	billionaire *tmp=head,*tmp2=head;
	if(head==NULL)
	{
		printf("You cannot execute this command because the list is empty\n");
		return NULL;
	}
	else if(tmp->next==head)
	{
		free(head);
		return NULL;
	}
	else
	{
		if(possision=='O')
		{
			tmp=head->next;
			tmp->prev=head->prev;
			head->prev->next=tmp;
			free(head);
			return tmp;
		}
		else
		{
			while(tmp->next!=head)
			{
				tmp=tmp->next;
			}
			tmp2=tmp->prev;
			free(tmp);
			head->prev=tmp2;
			tmp2->next=head;
			return head;
		}
	}
}



void insertFile(billionaire *head,FILE *file)
{
	int len[4],i;
	billionaire *tmp;
	if(head!=NULL)
	{
		tmp=head;
		len[0]=strlen(head->name);
		while(tmp->next!=head)
		{
			if(len[0]<strlen(tmp->name))
			{
				len[0]=strlen(tmp->name);
			}
			tmp=tmp->next;
		}
		if(len[0]<strlen(tmp->name))
		{
			len[0]=strlen(tmp->name);
		}
		
		tmp=head;
		len[1]=strlen(head->cac);
		while(tmp->next!=head)
		{
			if(len[1]<strlen(tmp->cac))
			{
				len[1]=strlen(tmp->cac);
			}
			tmp=tmp->next;
		}
		if(len[1]<strlen(tmp->cac))
		{
			len[1]=strlen(tmp->cac);
		}
		
		tmp=head;
		len[2]=strlen(head->act);
		while(tmp->next!=head)
		{
			if(len[2]<strlen(tmp->act))
			{
				len[2]=strlen(tmp->act);
			}
			tmp=tmp->next;
		}
		if(len[2]<strlen(tmp->act))
		{
			len[2]=strlen(tmp->act);
		}
		
		tmp=head;
		len[3]=strlen(head->country);
		while(tmp->next!=head)
		{
			if(len[3]<strlen(tmp->country))
			{
				len[3]=strlen(tmp->country);
			}
			tmp=tmp->next;
		}
		if(len[3]<strlen(tmp->country))
		{
			len[3]=strlen(tmp->country);
		}
	}
			
	if(head==NULL)
	{
		printf("There are no elements in the list so the file will remain empty\n");
	}
	else
	{
		tmp=head;
		while(tmp->next!=head)
		{
			fprintf(file,"%s",tmp->name);
			if(len[0]>strlen(tmp->name))
			{
				for(i=strlen(tmp->name);i<len[0];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->cac);
			if(len[1]>strlen(tmp->cac))
			{
				for(i=strlen(tmp->cac);i<len[1];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->act);
			if(len[2]>strlen(tmp->act))
			{
				for(i=strlen(tmp->act);i<len[2];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->country);
			if(len[3]>strlen(tmp->country))
			{
				for(i=strlen(tmp->country);i<len[3];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');			
			fprintf(file,"%s;%.2d/%.2d/%.2d %.2d:%.2d;%.4f;%s;\n",tmp->sex,tmp->birthdate.day,tmp->birthdate.month,tmp->birthdate.year,tmp->birthtime.hour,tmp->birthtime.minutes,tmp->billions,tmp->ac);
			tmp=tmp->next;
		}
		fprintf(file,"%s",tmp->name);
			if(len[0]>strlen(tmp->name))
			{
				for(i=strlen(tmp->name);i<len[0];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->cac);
			if(len[1]>strlen(tmp->cac))
			{
				for(i=strlen(tmp->cac);i<len[1];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->act);
			if(len[2]>strlen(tmp->act))
			{
				for(i=strlen(tmp->act);i<len[2];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');
			fprintf(file,"%s",tmp->country);
			if(len[3]>strlen(tmp->country))
			{
				for(i=strlen(tmp->country);i<len[3];i++)
				{
					fprintf(file,"%c",' ');
				}
			}
			fprintf(file,"%c",';');			
			fprintf(file,"%s;%.2d/%.2d/%.2d %.2d:%.2d;%.4f;%s;\n",tmp->sex,tmp->birthdate.day,tmp->birthdate.month,tmp->birthdate.year,tmp->birthtime.hour,tmp->birthtime.minutes,tmp->billions,tmp->ac);
			tmp=tmp->next;	
	}
}


void findBil(billionaire *head,char infob[])
{
	int len[4]={0},i;
	billionaire *tmp;
	if(strncmp(infob,"findN *",7)==0 || strncmp(infob,"findC *",7)==0 || strncmp(infob,"findS *",7)==0)
	{
		tmp=head;
		if(tmp!=NULL)
		{
			while(tmp->next!=head)
			{
				if(len[0]<strlen(tmp->name))
				{
					len[0]=strlen(tmp->name);
				}
				if(len[1]<strlen(tmp->cac))
				{
					len[1]=strlen(tmp->cac);
				}	
				if(len[2]<strlen(tmp->act))
				{
					len[2]=strlen(tmp->act);
				}
				if(len[3]<strlen(tmp->country))
				{
					len[3]=strlen(tmp->country);
				}
				tmp=tmp->next;
			}
			if(len[0]<strlen(tmp->name))
			{
				len[0]=strlen(tmp->name);
			}
			if(len[1]<strlen(tmp->cac))
			{
				len[1]=strlen(tmp->cac);
			}	
			if(len[2]<strlen(tmp->act))
			{
				len[2]=strlen(tmp->act);
			}
			if(len[3]<strlen(tmp->country))
			{
				len[3]=strlen(tmp->country);
			}
			tmp=head;
			while(tmp->next!=head)
			{
				printf("%s",tmp->name);
				if(len[0]>strlen(tmp->name))
				{
					for(i=strlen(tmp->name);i<len[0];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->cac);
				if(len[1]>strlen(tmp->cac))
				{
					for(i=strlen(tmp->cac);i<len[1];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->act);
				if(len[2]>strlen(tmp->act))
				{
					for(i=strlen(tmp->act);i<len[2];i++)
					{	
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->country);
				if(len[3]>strlen(tmp->country))
				{
					for(i=strlen(tmp->country);i<len[3];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');			
				printf("%s;%.2d/%.2d/%.2d %.2d:%.2d;%.4f;%s;\n",tmp->sex,tmp->birthdate.day,tmp->birthdate.month,tmp->birthdate.year,tmp->birthtime.hour,tmp->birthtime.minutes,tmp->billions,tmp->ac);
				tmp=tmp->next;
			}
			printf("%s",tmp->name);
				if(len[0]>strlen(tmp->name))
				{
					for(i=strlen(tmp->name);i<len[0];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->cac);
				if(len[1]>strlen(tmp->cac))
				{
					for(i=strlen(tmp->cac);i<len[1];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->act);
				if(len[2]>strlen(tmp->act))
				{
					for(i=strlen(tmp->act);i<len[2];i++)
					{	
						printf("%c",' ');
					}
				}
				printf("%c",';');
				printf("%s",tmp->country);
				if(len[3]>strlen(tmp->country))
				{
					for(i=strlen(tmp->country);i<len[3];i++)
					{
						printf("%c",' ');
					}
				}
				printf("%c",';');			
				printf("%s;%.2d/%.2d/%.2d %.2d:%.2d;%.4f;%s;\n",tmp->sex,tmp->birthdate.day,tmp->birthdate.month,tmp->birthdate.year,tmp->birthtime.hour,tmp->birthtime.minutes,tmp->billions,tmp->ac);
			}
		else
		{
			printf("The list is empty\n");
		}
	}
					
	else
	{
		printf("The command you gave is faulse.Plese give a new one\n");
	}
}				
