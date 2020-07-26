#include <iostream>
#include <string>

class User {

public:
	string name ;
    
    int value_of_the_wallet ;
   
    double id_of_the_user;
    

    int array_of_groups []= {}; 
    
    // function for changing of value of the wallet

    int error_sum(){
       
       cout<<"Error , you have only"<<value_of_the_wallet<<endl;
     
    }

    int  deacrease_value_of_the_wallet (int sum_of_the_purchare) {
         
        int value_of_the_wallet = value_of_the_wallet - sum_of_the_purchare ;

        if (value_of_the_wallet < sum_of_the_purchare) {

           error_sum();
        }

    	return 0 ;
    }
}


