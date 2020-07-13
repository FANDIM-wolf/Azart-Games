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
	}
}