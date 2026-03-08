/* Ioannis Nikas
   AM:2022202300148
   dit23148@go.uop.gr
   
   Konstantinos Papapanagiotou
   AM:2022202300225
   dit23225@go.uop.gr
  */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define MOVES 100
void makemap(char** tmp ,int d ,int sizeN ,int sizeM);
void printmap(char **map,int sizeN,int sizeM,char character);
int checkmoves(char moves[],int len,int sizeN,int sizeM);
int Leiaresults(char** map,int grammiL,int stiliL,int* loses,int sizeN);
int main(void)
{
	char **map ,moves[MOVES]={0},temp;
	int i ,j ,N,M,difficulty,len,grammiL,stiliL,grammi1,stili1,grammi2,stili2,pl=0,*loses,loseL,grammiD,stiliD,grammiDnext,stiliDnext;
	int steps=0,resultL=1,level=1,grammiLnext,stiliLnext;
	double stomove,Dmove=40;
	srand(time(NULL));
	loseL=0;
	loses=&loseL;
	printf("The pruduct of the rows and columns must be more than 50 and the rows and columns must be less than or equal to 26\n");
	printf("Give the number of rows and columns of the map :");
	do
	{
		scanf("%d %d",&N,&M);
		if(N*M<50 || N>26 || M>26)
		{
			printf("The price you gave is outrageous\nGive a new one :");
		}
		printf("\n");
	}while(N*M<50 || N>26 || M>26);
	printf("Give the difficulty level\n");
	printf("1:EASY 2:AVERAGE 3:DIFFICULT 4:IMPOSSIBLE :");
	do
	{
		scanf("%d",&difficulty);
		getchar();
		if(difficulty<1 || difficulty>4)
		{
			printf("The price you gave is outrageous\nGive a new one :");
		}
	}while(difficulty<1 || difficulty>4);
	printf("\n\n");
	
	while(N*M>=50)
	{
		if(resultL==1)
		{
			map=(char**)malloc(N*sizeof(char*));
			if(map==NULL)
			{
				printf("There is not enought space to execute the program");
				exit(0);
			}
			for(i=0; i<N; i++)
			{
				map[i]=(char*)malloc(M*sizeof(char));
				if(map[i]==NULL)
				{
					printf("There is not enought space to execute the program");
					exit(0);
				}
			}
			makemap(map,difficulty,N,M);
			printmap(map,N,M,'A');
			resultL=0;
		}
		do
		{
			printf("You can do any or all of the following moves\n");
			printf("Give 'u' or 'U' to make Leia do up\nGive 'd' or 'D' to make Leia go down\n");
			printf("Give 'l' or 'L' to make Leia go left\nGive 'r' or 'R' to make Leia go right\n");
			printf("Give 'h' or 'H' to print all the elements of the map\n");
			printf("Give 'x' or 'X' to exit from the game\n");
			printf("Give '>'to move an obsacle from one position to enother.You must give first the columns and then the rows\n\n");
			printf("Level :%d\n",level);
			printf("Make your moves :");
			fgets(moves,sizeof(moves),stdin); 
			len=strlen(moves);
			moves[len-1]='\0';
			len=strlen(moves);
		}while((checkmoves(moves,len,N,M))==0);
		
		for(i=0; i<N; i++)
		{
			for(j=0; j<M; j++)	
			{
				if(map[i][j]=='L')
				{
					grammiL=i;
					stiliL=j;
				}
				else if(map[i][j]=='D')
				{
					grammiD=i;
					stiliD=j;
				}
			}
		}
		printf("%d   %d\n",grammiD,stiliD);
		for(i=0; i<len; i++)
		{
			if(moves[3]=='>')
			{
				grammi1=((moves[1]-48)*10 + moves[2]-48)-1;
				grammi2=((moves[5]-'0')*10 + moves[6]-'0')-1;
				stili1=toupper(moves[0])-'A';
				stili2=toupper(moves[4])-'A';
				if((grammi1<N && grammi1>=0) && (grammi2<N && grammi2>=0) && (stili1<M && stili1>=0) && (stili1<M && stili1>=0))
				{
					printf("%d %d   %d %d\n",grammi1,stili1,grammi2,stili2);
					if(map[grammi1][stili1]!='X')
					{
						printf("At this point there is no obstacle to move\n");
					}
					else if(map[grammi2][stili2]!='.')
					{
						printf("At this point there is enother element and the obstacle cannot be placed\n");
					}
					else if(map[grammi1][stili1]=='X' && map[grammi2][stili2]=='.')
					{
						temp=map[grammi1][stili1];
						map[grammi1][stili1]=map[grammi2][stili2];
						map[grammi2][stili2]=temp;
						grammi1=grammi2=stili1=stili2=0;
						printmap(map,N,M,'A');
					}
					for(j=0; moves[j]!='\0'; j++)
					{
						moves[j]='\0';
					}
					break;
				}
				else
				{
					for(j=0; moves[j]!='\0'; j++)
					{
						moves[j]='\0';
					}
					printf("Some of the coordinates you give are off the map");
					break;
				}
			}		
			else if(moves[i]=='H' || moves[i]=='h')
			{
				if(len=1)
				{
					printmap(map,M,N,'H');
					break;
				}
				else
				{
					printf("You can execute this command\n");
					break;
				}
			}
			else if(moves[i]=='X' || moves[i]=='x')
			{
				printf("You gave the comant witch end this game!!!\n");
				exit(0);
			}
			else if(moves[i]=='U' || moves[i]=='u')
			{
				grammiLnext=grammiL-1;
				stiliLnext=stiliL;
				if(grammiLnext<0 || map[grammiLnext][stiliLnext]=='X')
				{
					printf("You can execute this command\n");
					break;
				}
				else
				{
					resultL=Leiaresults(map,grammiLnext,stiliLnext,loses,N);
					if(resultL==0)
					{
						temp=map[grammiL][stiliL];
						map[grammiL][stiliL]=map[grammiLnext][stiliLnext];	
						map[grammiLnext][stiliLnext]=temp;
						grammiL=grammiLnext;
						stiliL=stiliLnext;
						steps++;
					}
					else
					{
						N--;
						M--;
						steps=0;
						loseL=0;
						level++;
						break;
					}
				}
			}
			else if(moves[i]=='D' || moves[i]=='d')
			{
				grammiLnext=grammiL+1;
				stiliLnext=stiliL;
				if(grammiLnext>N-1 || map[grammiLnext][stiliLnext]=='X')
				{
					printf("You can execute this command\n");
					break;
				}
				else
				{
					resultL=Leiaresults(map,grammiLnext,stiliLnext,loses,N);
					if(resultL==0)
					{
						temp=map[grammiL][stiliL];
						map[grammiL][stiliL]=map[grammiLnext][stiliLnext];	
						map[grammiLnext][stiliLnext]=temp;
						grammiL=grammiLnext;
						stiliL=stiliLnext;
						steps++;
					}
					else
					{
						N--;
						M--;
						steps=0;
						loseL=0;
						level++;
						break;
					}
				}
			}
			else if(moves[i]=='R' || moves[i]=='r')
			{
				stiliLnext=stiliL+1;
				grammiLnext=grammiL;
				if(stiliLnext>M-1 || map[grammiLnext][stiliLnext]=='X')
				{
					printf("You can execute this command\n");
					break;
				}
				else
				{
					resultL=Leiaresults(map,grammiLnext,stiliLnext,loses,N);
					if(resultL==0)
					{
						temp=map[grammiL][stiliL];
						map[grammiL][stiliL]=map[grammiLnext][stiliLnext];	
						map[grammiLnext][stiliLnext]=temp;
						grammiL=grammiLnext;
						stiliL=stiliLnext;
						steps++;
					}
					else
					{
						N--;
						M--;
						steps=0;
						loseL=0;
						level++;
						break;
					}
				}
			}
			else if(moves[i]=='L' || moves[i]=='l')
			{
				stiliLnext=stiliL-1;
				grammiLnext=grammiL;
				if(stiliL<=0 || map[grammiL][stiliL]=='X')
				{
					printf("You can execute this command\n");
					break;
				}
				else
				{
					resultL=Leiaresults(map,grammiLnext,stiliLnext,loses,N);
					if(resultL==0)
					{
						temp=map[grammiL][stiliL];
						map[grammiL][stiliL]=map[grammiLnext][stiliLnext];	
						map[grammiLnext][stiliLnext]=temp;
						grammiL=grammiLnext;
						stiliL=stiliLnext;
						steps++;
					}
					else
					{
						N--;
						M--;
						steps=0;
						loseL=0;
						level++;
						break;
					}
				}
			}
			else if(moves[i]!='>' && toupper(moves[i])!='U' && toupper(moves[i])!='L' && toupper(moves[i])!='D' && toupper(moves[i])!='R' && toupper(moves[i])!='X' && toupper(moves[i])!='H') 
			{
				printf("You can execute this command\n");
				break;
			}
			if(steps%2==0)
			{
				if(grammiD-1>=0)
				{
					if(map[grammiD-1][stiliD]!='X' && map[grammiD-1][stiliD]!='@' && map[grammiD-1][stiliD]!='R' && sqrt(pow(((grammiD-1)-grammiL),2)+pow((stiliD-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD-1)-grammiL),2)+pow((stiliD-stiliL),2));
						grammiDnext=grammiD-1;
					}
				}
				if(grammiD+1<N)
				{
					if(map[grammiD+1][stiliD]!='X' && map[grammiD+1][stiliD]!='@' && map[grammiD+1][stiliD]!='R'&& grammiD+1<N && sqrt(pow(((grammiD+1)-grammiL),2)+pow((stiliD-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD+1)-grammiL),2)+pow((stiliD-stiliL),2));
						grammiDnext=grammiD=+1;
					}
				}
				if(stiliD-1>=0)
				{
					if(map[grammiD][stiliD-1]!='X' && map[grammiD][stiliD-1]!='@' && map[grammiD][stiliD-1]!='R' && sqrt(pow((grammiD-grammiL),2)+pow(((stiliD-1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow((grammiD-grammiL),2)+pow(((stiliD-1)-stiliL),2));
						stiliDnext=stiliD-1;
						printf("%lf\n",Dmove);
						printf("%d   %d\n",grammiDnext,stiliDnext);
					}
				}
				if(stiliD+1<M)
				{
					if(map[grammiD][stiliD+1]!='X' && map[grammiD][stiliD+1]!='@' && map[grammiD][stiliD+1]!='R'&& stiliD+1<M && sqrt(pow((grammiD-grammiL),2)+pow(((stiliD+1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow((grammiD-grammiL),2)+pow(((stiliD+1)-stiliL),2));
						stiliDnext=stiliD+1;
					}
				}
				if(stiliD+1<M && grammiD+1<N)
				{
					if(map[grammiD+1][stiliD+1]!='X' && map[grammiD+1][stiliD+1]!='@' && map[grammiD+1][stiliD+1]!='R'&& sqrt(pow(((grammiD+1)-grammiL),2)+pow(((stiliD+1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD+1)-grammiL),2)+pow(((stiliD+1)-stiliL),2));
						stiliDnext=stiliD+1;
						grammiDnext=grammiD+1;
					}
				}
				if(stiliD+1<M && grammiD-1>=0 )
				{
					if(map[grammiD-1][stiliD+1]!='X' && map[grammiD-1][stiliD+1]!='@' && map[grammiD-1][stiliD+1]!='R'&& sqrt(pow(((grammiD-1)-grammiL),2)+pow(((stiliD+1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD-1)-grammiL),2)+pow(((stiliD+1)-stiliL),2));
						stiliDnext=stiliD+1;
						grammiDnext=grammiD-1;
					}
				}
				if(stiliD-1>=0 && grammiD+1<N)
				{
					if(map[grammiD+1][stiliD-1]!='X' && map[grammiD+1][stiliD-1]!='@' && map[grammiD+1][stiliD-1]!='R'&&  sqrt(pow(((grammiD+1)-grammiL),2)+pow(((stiliD-1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD+1)-grammiL),2)+pow(((stiliD-1)-stiliL),2));
						stiliDnext=stiliD-1;
						grammiDnext=grammiD+1;
					}
				}
				if(stiliD-1>=0 && grammiD-1>=0)
				{
					if(map[grammiD-1][stiliD-1]!='X' && map[grammiD-1][stiliD-1]!='@' && map[grammiD-1][stiliD-1]!='R'&& sqrt(pow(((grammiD-1)-grammiL),2)+pow(((stiliD-1)-stiliL),2))<Dmove)
					{
						Dmove=sqrt(pow(((grammiD-1)-grammiL),2)+pow(((stiliD-1)-stiliL),2));
						stiliDnext=stiliD-1;
						grammiDnext=grammiD-1;
					}
				}
				if(map[grammiDnext][stiliDnext]=='L')
				{
					for(i=0; i<N; i++)
					{
						free(map[i]);
					}
					free(map);
					printf("Darth Vader manage to cupture you and you just lost the game!!!\n");
					exit(0);
				}
				else
				{
					temp=map[grammiD][stiliD];
					map[grammiD][stiliD]=map[grammiDnext][stiliDnext];
					map[grammiDnext][stiliDnext]=temp;
					stiliD=stiliDnext;
					grammiD=grammiDnext;
					Dmove=40;
				}
			}
			printmap(map,N,M,'A');
		}	
		if(N*M<50)
		{
			printf("You manage to complete all levels and you WON THE GAME !!!!!");
		}
	}		
	
	return 0;
}




void makemap(char** tmp ,int d ,int sizeN ,int sizeM)
{
	int i ,j,sto,emp,grammi,stili,pos;
	double sto1 ,emp1 ,grammi1,stili1;
	if(d==1)
	{
		sto1=(sizeN*sizeM)*0.02;
		emp1=(sizeN*sizeM)*0.13;
	}
	else if(d==2)
	{
		sto1=(sizeN*sizeM)*0.05;
		emp1=(sizeN*sizeM)*0.1;
	}
	else if(d==3)
	{
		sto1=(sizeN*sizeM)*0.1;
		emp1=(sizeN*sizeM)*0.05;
	}
	else
	{
		sto1=(sizeN*sizeM)*0.15;
		emp1=0;
	}
	sto=(int)sto1;
	emp=(int)emp1;
	
	for(i=0; i<sizeN; i++)
	{
		for(j=0; j<sizeM; j++)
		{
			tmp[i][j]='.';
		}
	}
	pos=rand()%4;
	if(pos==0)
	{
		tmp[0][0]='D';
	}
	else if(pos==1)
	{
		tmp[0][sizeM-1]='D';
	}
	else if(pos==2)
	{
		tmp[sizeN-1][0]='D';
	}
	else
	{
		tmp[sizeN-1][sizeM-1]='D';
	}
	
	do
	{
		grammi1=(double)rand()/((double)RAND_MAX+1);
		stili1=(double)rand()/((double)RAND_MAX+1);
		grammi1=grammi1*sizeN;
		stili1=stili1*sizeM;
		grammi=(int)grammi1;
		stili=(int)stili1;
		if(tmp[grammi][stili]!='D')
		{
			tmp[grammi][stili]='R';
		}
	}while(tmp[grammi][stili]=='D');
	
	do
	{
		grammi1=(double)rand()/((double)RAND_MAX+1);
		stili1=(double)rand()/((double)RAND_MAX+1);
		grammi1=grammi1*sizeN;
		stili1=stili1*sizeM;
		grammi=(int)grammi1;
		stili=(int)stili1;
		if(tmp[grammi][stili]!='D' && tmp[grammi][stili]!='R')
		{
			tmp[grammi][stili]='L';
		}
	}while(tmp[grammi][stili]=='D' || tmp[grammi][stili]=='R');
	
	if(d==4)
	{
		do
		{
			grammi1=(double)rand()/((double)RAND_MAX+1);
			stili1=(double)rand()/((double)RAND_MAX+1);
			grammi1=grammi1*sizeN;
			stili1=stili1*sizeM;
			grammi=(int)grammi1;
			stili=(int)stili1;
			if(tmp[grammi][stili]!='D' && tmp[grammi][stili]!='R' && tmp[grammi][stili]!='L'&& tmp[grammi][stili]!='@' )
			{
				tmp[grammi][stili]='@';
				sto--;
			}
		}while((tmp[grammi][stili]=='D' || tmp[grammi][stili]=='R'|| tmp[grammi][stili]=='L'|| tmp[grammi][stili]=='@') && sto!=0);
	}
	else
	{
		do
		{
			grammi1=(double)rand()/((double)RAND_MAX+1);
			stili1=(double)rand()/((double)RAND_MAX+1);
			grammi1=grammi1*sizeN;
			stili1=stili1*sizeM;
			grammi=(int)grammi1;
			stili=(int)stili1;
			if(tmp[grammi][stili]!='D' && tmp[grammi][stili]!='R' && tmp[grammi][stili]!='L'&& tmp[grammi][stili]!='@' )
			{
				tmp[grammi][stili]='@';
				sto--;
			}
		}while((tmp[grammi][stili]=='D' || tmp[grammi][stili]!='R'|| tmp[grammi][stili]!='L'|| tmp[grammi][stili]!='@')&& sto!=0);
		do
		{
			grammi1=(double)rand()/((double)RAND_MAX+1);
			stili1=(double)rand()/((double)RAND_MAX+1);
			grammi1=grammi1*sizeN;
			stili1=stili1*sizeM;
			grammi=(int)grammi1;
			stili=(int)stili1;
			if(tmp[grammi][stili]!='D' && tmp[grammi][stili]!='R' && tmp[grammi][stili]!='L'&& tmp[grammi][stili]!='@'&& tmp[grammi][stili]!='X')
			{
				tmp[grammi][stili]='X';
				emp--;
			}
		}while((tmp[grammi][stili]=='D' || tmp[grammi][stili]=='R'|| tmp[grammi][stili]=='L'|| tmp[grammi][stili]=='@'|| tmp[grammi][stili]=='X') && emp!=0);
	 }
}






void printmap(char **map,int sizeN,int sizeM,char character)
{
	int i,j,grammi,stili,arithmos,k,plstl=1,count=0;
	int linePrint = 0;
	char gramma='A';
	for(i=0; i<sizeN; i++)
	{
		for(j=0; j<sizeM; j++)
		{
			if(map[i][j]=='L')
			{
				grammi=i;
				stili=j;
				break;
			}
		}
	}
	for(k=0; k<(3+(sizeM*2)-1); k++)
	{
		if(linePrint >= 4)
		{
			if (gramma <= 'Z')
			{
				printf("%c ",gramma);
				gramma++;
				count++;
				if(count==sizeM)
				{
					break;
				}
			}	
		} else {
			printf(" ");
		}
		linePrint++;
	}
	printf("\n");
	for(k=0; k<(3+(sizeM*2)); k++)
	{ 
		printf("%c",'-');
	} 
	printf("\n");
	if(character!='H')
	{
		for(i=0; i<sizeN; i++)
		{
			
			if(i+1<=9)
			{
				printf("%d%d| ",0,i+1);
			} else {
				printf("%d| ", i+1);
			}
			for(j=0; j<sizeM; j++)
			{
				if(i!=grammi && j!=stili && map[i][j]!='D' && map[i][j]!='X')
				{
					printf("%c ",'#');
				}
				else
				{
					printf("%c ",map[i][j]);
				}	
			}
		printf("\n");
		}
	}
	else
	{
		for(i=0; i<sizeN; i++)
		{
			if(i+1<=9)
			{
				printf("%d%d| ",0,i+1);
			} else {
				printf("%d| ", i+1);
			}
			for(j=0; j<sizeM; j++)
			{
				printf("%c ",map[i][j]);
			}
		printf("\n");
		}
	}
	printf("\n");
}


int checkmoves(char moves[],int len,int sizeN,int sizeM)
{
	int i;
	
	for(i=0;moves[i]!='\0';i++)
	{
		if(isalnum(moves[i])==0 && moves[i]!='>') 	
		{
			printf("You can execute this command\n");
			return 0;
		}
	}	
	for(i=0;moves[i]!='\0';i++)
	{
		if(len>1 && (moves[i]=='x' || moves[i]=='X'))
		{
			printf("You can execute this command\n");
			return 0;
		}
	}
	
	
	return 1;
}




int Leiaresults(char** map,int grammiL,int stiliL,int* loses,int sizeN)
{
	int i;
	if(map[grammiL][stiliL]=='D')
	{
		printf("Darth Vader have cupture you.You just lost the game !!!\n");
		exit(0);
	}
	else if(map[grammiL][stiliL]=='@')
	{
		(*loses)++;
		if(*loses==2)
		{
			for(i=0; i<sizeN; i++)
			{
				free(map[i]);
			}
			free(map);
			printf("You fought the second stormtrooper but because you are seriously injured he manage to impale you and you lost the game !!!\n");
			exit(0);
		}
		else
		{
			printf("You fought the first stormtrooper and you manage to eliminate him but you were seriously injured,becareful !!!\n");
			map[grammiL][stiliL]='.';
			return 0;
		}
	}
	else if(map[grammiL][stiliL]=='R')
	{
		printf("You manage to find R2D2 and you complete this level !!!\n\n");
		for(i=0; i<sizeN; i++)
		{
			free(map[i]);
		}
		free(map);
		return 1;
	}
	else
	{
		return 0;
	}
}
