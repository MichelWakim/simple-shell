#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void main(){

   printf("******************    Welcome to my simple shell    ******************\n");
	while(1){
      //display a prompt 
		printf("Micho.Shell -> ");      
		char str[100]; 		//create a string for command
		scanf("%[^\n]%*c", str); //read the command line           
	
		int num=1;
		for(int i=0; i<strlen(str) ;i++){if (str[i]==' ') num++;}//declaration the number of words in the 
	
		char *arg[num]; //creat an array pointer of strings //it is also an array of strings
		int i=0;arg[0]=strtok(str, " ");//storing the first word as an element in the string

		while(arg[i] != NULL){//check that the spaces between the words of the command 
			arg[++i]= strtok(NULL," ");}//storing each word as an element in the string
		
		
		pid_t child, parent;
		child=fork();//duplicate
		int status; //statue of the child;
	
		if(child==0){
			execvp(arg[0], arg); //execvp has its parameters as array of strings
			perror("error"); //only get here on error
			exit(1);}
		else if (child>0){parent = wait(&status);}
		else{//error: The return of fork() is negative
	    			perror("fork failed");_exit(2); /*exit failure, hard*/ }
	

		
	}
}
/*(https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split) for splittig a string
(https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/14/lec.html) the system functions */

