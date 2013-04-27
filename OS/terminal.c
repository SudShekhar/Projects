//Made by Sudhanshu Shekhar

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>
struct s{
	char *name;
	int pid;
	int back;
	int end;
};
typedef struct s s;
s lst[500];
int COUNT;
char hostname[100];
char *username;
void run(char**,int,int);
void runhist(int,int);
void feed(char **arg,int back);
int userDef(char **,int);
char path[100];
char home[100];

void cmdline()
{
	printf("<%s@%s:%s>",username,hostname,home);
	fflush(stdout);
}
void sig_handler(int signum)
{
	if(signum==2 || signum==20)
	{
		printf("\nEnter \"quit\" to exit\n");
		cmdline();
	}
	signal(SIGINT,sig_handler);
	signal(SIGTSTP,sig_handler);
	return;
}
void child(int sig)
{	
	pid_t pid1;
	pid1 = waitpid(WAIT_ANY, NULL, WNOHANG);
	int i;
	if(pid1!=-1)
	{
		for(i=0;i<COUNT;i++)
		{
			if(lst[i].pid==pid1)
			{
				lst[i].end=1;
				if(lst[i].back)
				{
					printf("\n%s finished successfully with pid %d\n",lst[i].name,pid1);
					cmdline();
				}
				break;
			}
		}	
	}
	signal(SIGCHLD, child);
	return ;
}

//handles PID commands
void pidrel(char *arg)
{
	int i;
	if(!strcmp(arg,"all"))
	{
		printf("List of all processes spawned from this shell:\n");
		for(i=0;i<COUNT-1;i++)
		{
			printf("command name: %s process id :%d\n",lst[i].name,lst[i].pid);


		}
	}
	else{
		printf("List of currently executing processes spawned from this shell:\n");
		for(i=0;i<COUNT-1;i++)
		{
			if(!lst[i].end)
			{
				printf("command name: %s process id :%d\n",lst[i].name,lst[i].pid);
			}
		}

	}
}

//pipeling handled here
void pip(int NUM,char **arg,int pi,int out)
{		
	int i,j;
	char line[500];
	int n;
	int k=0;
	j=0;
	pid_t pid;
	int fd[2*(pi+out)];
	for(i=0;i<=pi+out;i++)pipe(fd+2*i);
	int pno=1;
	int O=0;
	while(j<NUM)
	{
		while(( j<NUM && strcmp("|",arg[j]) && strcmp("<",arg[j]) && strcmp(">",arg[j])))
		{
			j++;
			//	fprintf(stderr,"made j %d\n",j);
		}
		char *arr[10];
		for(i=0;i<j-k;i++)
		{
			arr[i]=strdup(arg[i+k]);
		}

		arr[j-k]=NULL;
		int back=0;
		//for background process checking
		for (i=0;i<j-k;i++)
		{
			//	fprintf(stderr,"checkin %s\n",arr[i]);
			if (!(strcmp(arr[i],"&")))
				back=1;
		}

		if(back)
		{
			arr[(j-k)-1]=NULL;
		}
		feed(arr,back);
		COUNT++;
		FILE *fp1,*fp2;
		int redir=0,red=0;
		if(k==0)
		{	
			if(j<NUM && !strcmp(arg[j],"<"))
			{
				fp1=fopen(arg[j+1],"r");
				if(fp1==NULL)
				{
					printf("File doesn't exist\n");
				//	cmdline();
					return;
				}
				j+=2;
				redir=1;
			}
			if(j<NUM && !strcmp(arg[j],">"))
			{
				fp2=fopen(arg[j+1],"w");
				j+=2;
				red=1;
			}
			pid=fork();
			if(!pid)
			{
				if(redir)
					dup2(fileno(fp1),0);

				close(fd[pno-1]);

				if(red)
					dup2(fileno(fp2),1);
				else
					dup2(fd[pno],1);

				if(!(userDef(arr,j-k)))
				{

					run(arr,back,0);

				}

				//run(arr,back,0);

				close(fd[pno]);
				exit(0);
			}
			else
			{
				lst[(COUNT)-1].pid = pid;
				if(!back)
					lst[(COUNT)-1].end=1;
				close(fd[pno]);
				waitpid(pid,NULL,0);
			}
		}
		else
		{
			if(j==NUM-2 && !strcmp(arg[j],">"))
			{
				fp2=fopen(arg[j+1],"w");
				j+=2;
				red=1;
			}

			pid=fork();
			if(!pid)
			{
				close(fd[pno-2]);
				close(fd[pno-1]);
				dup2(fd[pno-3],0);
				if(red)
				{	//printf("redirectiong\n");
					dup2(fileno(fp2),1);
				}
				else

					dup2(fd[pno],1);



				if(!(userDef(arr,j-k)))
				{

					run(arr,back,0);

				}

				//run(arr,back,0);

				//	fflush(stdout);
				close(fd[pno-3]);
				close(fd[pno]);
				close(fileno(fp2));
				exit(0);

			}
			else
			{	
				lst[(COUNT)-1].pid = pid;

				if(!back)
					lst[(COUNT)-1].end=1;
				close(fd[pno-2]);
				//close(fd[2]);
				close(fd[pno]);
				if(red==1)	
					fclose(fp2);
				waitpid(pid,NULL,0);
			}
		}
		for(i=0;i<10;i++)arr[i]=NULL;

		//if(back)j++;
		k=j+1;
		j++;
		//printf("value of j is %d and NUM is %d\n",j,NUM);

		if(j>=NUM )
		{				
			n=read(fd[pno-1],line,500);
			if(!red)
			{
				write(STDOUT_FILENO,line,n);
			}
			//else 
			//	write(fileno(fp2),line,n);
		}
		pno+=2;
	}
	return;
}
int main()
{	
	COUNT=0;
	char inp[100];
	int host_size;
	getcwd(path,100);
	strcpy(home,"~");
	char *stock=strdup(path);

	while(1)
	{
		int flag=0;
		host_size=gethostname(hostname,100);
		username=getenv("USER");
		int start=0;
		cmdline();
		char c;
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, sig_handler);
		signal(SIGCHLD,child);	

		gets(inp);
		if(!strcmp(inp,"quit"))
		{
			exit(0);
		}
		int j;
		int i=0;
		char *arg[10];

		int NUM=0;
		c='a';
		while(inp[i]==' ')
		{
			start++;
			i++;
		}
		while(c!='\0')
		{
			c=inp[i++];
			if(!c)break;
			while(inp[start]==' ')
			{
				start++;
				i++;
			}


			if(inp[i]==' ' || inp[i]=='\0')
			{
				arg[NUM]=(char*)malloc(sizeof(char)*(i-start+1));
				for (j=0;j<i-start;j++)
				{
					arg[NUM][j]=inp[j+start];
				}
				arg[NUM][i]='\0';
				NUM++;
				start=i+1;
			}

		}
		arg[NUM]=NULL;

	//read in command with arguements

		if(!strcmp(arg[0],"cd"))	
		{
			feed(arg,0);
			COUNT++;

			if((NUM==1) || (NUM==2 && !strcmp(arg[1],"~")))
			{
				strcpy(home,"~");
				getcwd(path,100);
				chdir(path);

			}
			//Assuming script only goes max upto its home directory
			else if(strcmp(arg[0],"cd")==0 && NUM>1)
			{

				if(!strcmp(arg[1],".."))
				{
					int l1=strlen(home);
					int l2=strlen(path);
					int iter;
					for(iter=l1-1;iter>=0;iter--)
						if(home[iter]=='/')
						{
							home[iter]='\0';
							flag=1;
							break;
						}
					if(iter<=0)
					{
						flag=1;
						strcpy(home,"~");
						strcpy(path,stock);
						chdir(path);

					}
					else
					{


						for(iter=l2-1;iter>=0;iter--)
							if(path[iter]=='/')
							{
								path[iter]='\0';
								break;
							}
					}
				}

				//i.e. we have reached the home directory
				if(flag==0)
				{
					strcat(home,"/");
					strcat(home,arg[1]);
					strcat(path,"/");
					strcat(path,arg[1]);
					chdir(path);
				}

			}
			lst[COUNT-1].end=1;
			lst[COUNT-1].pid=getpid();
		}


		int back=0;
		int pi=0;
		int out=0;
		int in=0;
		for(i=0;i<NUM;i++)
		{
			if(!strcmp("|",arg[i]))
			{
				pi++;
			}
			if(!strcmp("&",arg[i]))back=1;
			if(!strcmp(">",arg[i]))out++;
			if(!strcmp("<",arg[i]))in++;
		}



		if(pi || out || in)
			pip(NUM,arg,pi,out);
		else 
		{
			feed(arg,back);
			COUNT++;
			if(!userDef(arg,NUM)) 
				run(arg,back,0);
			else 
			{
				lst[COUNT-1].end=1;
				lst[COUNT-1].pid=getpid();
			}	

		}


	}
	return 0;

}	

int userDef(char **arg,int NUM)
{

	// Checking for PID related cmds		
	if(!strcmp(arg[0],"pid"))
	{
		if(NUM==1)
		{
			printf("command name: ./a.out process id: %d\n",getpid());
		}
		else
			pidrel(arg[1]);
		return 1; 
	}
	//History cmnds
	if(!(strcmp("hist",arg[0]))) 
	{	
		runhist(1,0);
		return 1;
	}
	if((strstr(arg[0],"hist")))
	{
		if (arg[0][0]=='!')
		{
			runhist(3,arg[0][5]-48);
		}
		else
		{
			runhist(2,arg[0][4]-48);

		}
		return 1;
	}
	return 0;
}
void feed(char **arg,int back)
{
	lst[COUNT].name=strdup(arg[0]);
	lst[COUNT].back=back;
	lst[COUNT].end=0;
}

void runhist(int type,int n)
{	int i;
	lst[(COUNT)-1].pid=getpid();
	switch(type)
	{
		case 1: //int i;
			for(i=0;i<COUNT-1;i++)
			{
				printf("%d. %s\n",i+1,lst[i].name);
			}
			break;
		case 2: //int i;
			for(i=0;i<n && i<COUNT-1;i++)
			{
				printf("%d. %s\n",i+1,lst[i].name);
			}
			break;
		case 3: 
			if(n>COUNT || n==0)
			{
				printf("please try again\n");

				cmdline();
			}
			else
				if(!userDef(&lst[n-1].name,1))
					run(&lst[(n) -1].name,lst[(n) -1].back,1);
			break;
	}
	return;
}
void run(char **arg,int back,int rep)
{
	//Got to ensure we dont store repeated commands
	int send;
	char *A[2];
	if (rep)
	{
		A[0]=arg[0];
		A[1]=NULL;
	}


	//It's an executable command (sys defined one)
	pid_t pid1,pid2;
	pid1=fork();
	if(pid1==-1)
	{
		printf("Error occured\n");
		exit(1);
	}
	if(pid1==0)
	{

		if(!rep)
		{

			if(back)
			{
				printf("\ncommand %s pid %d\n",arg[0],getpid());
				cmdline();
			}
			execvp(*arg,arg);

		}
		else 
		{
			if(back)
			{
				printf("\ncommand %s pid %d\n",A[0],getpid());
				cmdline();
			}
			execvp(*A,A);

		}
		_exit(0);
	}	
	else
	{
		if(!back)	
		{	
			waitpid(pid1,NULL,0);
		}
		if(!rep)
			lst[(COUNT)-1].pid = pid1;

		if(!back && !rep)
			lst[(COUNT)-1].end=1;
	}

}	

