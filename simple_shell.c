#include <stdio.h>
// include string.h to be able to use the string library in c
#include <string.h>
#include <unistd.h>
// include stdlib.h to privide compatible implicit declaration of built-in function ‘exit’
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/wait.h>

// Function to get the current directory
int getDirectory ();
// Fuction to count the number of words in the command
int numOfWords (char command []);
// Function to split the command array into an array of strings
char **splittingTheCommand (char *command, int num);

int main(){

   printf("******************    Welcome to my simple shell    ******************\n\n\n");
	while(1){
      // display a prompt 
		printf("Micho.Shell ");    
		
		// calling teh getDirectory function
		getDirectory ();
		
		// create a string for command
		char command[100]; 	
		// reading the command line	
		scanf("%[^\n]%*c", command);  
		
		/* strcmp is used to compare 2 strings in c language
		 if strcmp returns ZERO in case of MATCHING */
		if (! strcmp(command, "exit")) {
		   // exit the shell if the command = exit
		   break;
		   }
		
		 
	  int  num = numOfWords(command);
	   
	  // creating an array of pointers that each element in the command array is a string 
	  char **arguments;
	  // calling the function to split the command into an array of strings
	  arguments = splittingTheCommand(command, num);
		
		
		
		
		pid_t child, parent;
		//duplicate
		child=fork();
		//statu of the child;
		int status; 
	
		if(child == 0){
		
			execvp(arguments[0], arguments); //execvp has its parameters as array of strings
			perror("error"); //only get here on error
			exit(1);}
		else if (child > 0){parent = wait(&status);}
		else{//error: The return of fork() is negative
	    			perror("fork failed");_exit(2); /*exit failure, hard*/ }
	
	free(arguments);

		
	}
	return 0;
}

int getDirectory () {

   // creating an array of characters to store path
	char cwd[PATH_MAX];
	// getting the current path
	// after getting the path if the array cwd is not empty  
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       // print the path
       printf(/*"Current working dir:*/ "-> %s $ ", cwd);
      // if the array is empty after getting the path 
   } else {
      // print an error
      perror("getcwd() error");
      // return 1 for error
      return 1;
   }
   return 0;
}

int numOfWords (char command []){
   // intialinzing the integer num by value 1
   int num = 1;
	/* finding the number of words in the the command
	   by passing through all the characters in the array */
	for(int i=0; i<strlen(command) ;i++){
	   // if the current character is space
	   if (command[i]==' ') 
	      // then increase the num by one
	      num++;
	}
	//returning the value of the variable num
   return num;
}


char **splittingTheCommand (char *command, int num) {
   // creating an array of pointers that each element in the command array is a string 
	char **arguments = (char **)malloc(num* sizeof(char*)); 
	int i = 0;
	//storing the first word as an element in the string
	arguments[0] = strtok(command, " ");
		
   //check that the spaces between the words of the command 
	while (arguments[i] != NULL) {
	      //storing each word as an element in the string
			arguments[++i] = strtok(NULL," ");
   }
   return arguments;
}


/*(https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split) for splittig a string
(https://www.usna.edu/Users/cs/aviv/classes/ic221/s16/lec/14/lec.html) the system functions */

