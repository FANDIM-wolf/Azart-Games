/*
Author : Jhon Erikson , Michael Chavale
Email : fandimfromitaly@yandex.ru 
Version v1.1
This program contains  two azart games and functions to create new users
Lisencse : FANDIM_LISCENSE 1.0
*/

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "hacking.c"

#define DATAFILE "/var/chance.data" // file for user data 

//struct data of player 

struct player
{
	int uid;
	int credits;
	int highscore;
	char name[100];
	int (*current_game) ();

};



//This function reads user data from the file 
int  get_player_data() {
	int fd, uid, read_bytes;

	struct user entry;
	uid = getuid();

	fd = open(DATAFILE, O_RDONLY);
	if (fd == -1){
		//it can not open file
		return -1;
	}
	read_bytes = read(fd, &entry, sizeof(struct user));
	while (entry.uid != uid && read_bytes > 0 )
	{
		read_bytes = read(fd, &entry , sizeof(struct user));
	}
	close(fd); // close file

	if (read_bytes < sizeof (struct user) ){

		return -1;
	} // end of the file
    else {
    	player = entry; // copy readed object to  struct player
    }
    return 1;

} 

//this function create new user 

void register_new_player () {
  
  int fd;

  printf("___Registration of new user___\n");
  printf("Enter new name:");
  input_name();

  player.uid = getuid();
  player.highscore = player.credits = 100;

  fd = open(DATAFILE, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
  if (fd == -1){
  	fatal("Sorry , there is error in the program. #rnp1");

  }
  write(fd, &player, sizeof(struct user));
  close(fd);

  printf("\n Welcome to the club , buddy %s.\n", player.name );
  printf("You have got %u credits.\n", player.credits );

}

//this function writes down data player

void update_player_data() {
	int fd, i , read_uid;
	char burned_byte;

	fd = open(DATAFILE , O_RDWR);
	if (fd == -1) {
		fatal("Sorry, there  is  error in the program . #upd1");
	}
	read(fd , &read_uid , 4);
	while (read_uid != player.uid){
		for(i = 0; i < sizeof(struct user ) - 4 ; i++ )
		{
            read(fd ,&burned_byte , 1);
		}
		read(fd, &read_uid , 4);
	}
	write(fd, &(player.credits),4);
	write(fd, &(player.highscore),4);
	write(fd, &(player.name),100);
	close(fd);
}

//this function print your record 

void show_highscore() {

	unsigned int top_score = 0 ;
	char top_name[100];
	struct user entry;
	int fd ;

	printf("\n===|RECORD|===\n");
	fd = open(DATAFILE, O_RDONLY);
	if (fd  == -1){
		fatal("Sorry there is error in the program #sh1");
	}
	while (read(fd, &entry , sizeof (struct user)) > 0  ) 
	{
		//condition
		if (entry.highscore > top_score) {

			top_score = entry.highscore;
			strcpy(top_name, entry.name);
		}
	}
	close(fd);
	if(top_score > player.highscore){
		printf(" %s new  record: %u\n",top_name , top_score );
	}
	else {
		printf("%s Now you  have %u\n", player.highscore );
	}
	printf("==========================================================================\n\n\n", );
}

//strandart jackpot
void jackpot() {}

// jackot with  bonus
void jackpot_plus() {}


// function  for input of name , because scanf  is stopping after first scpace 
void input_name(){

   char *name_ptr , input_char='\n';
   while(input_char == '\n'){
   	scanf("%c" , &input_char);
   }

   name_ptr = (char*)&(player.name);
   while(input_char != '\n'){
   	*name_ptr = input_char;
   	scanf("%c" , &input_char);
   	name_ptr++;
   }
   name_ptr = 0;

}


//this function contains , it allows  to  play game  again
void play_the_game() {

  int play_again = 1;
  int (*game) ();
  char selection;


  while(play_again) {

  	printf("\n DEBUGGING PTG#1\n", player.current_game);
  	if (player.current_game() != -1){

         if (player.credits > player.highscore) {
         	player.highscore = player.credits;
         }
         printf("\n Now you have %u credits:\n" , player.credits);

         update_player_data();
         printf("Do you wanna play again? (y/n)\n");

         selection = '\n';

         while(selection == '\n'){
         	scanf("%c" , &selection);
         }
         if (selection == 'n'){
         	play_again = 0;
         } 
         else {
         	play_again = 0;
         }

  	}
  }

//game pick a number 

}