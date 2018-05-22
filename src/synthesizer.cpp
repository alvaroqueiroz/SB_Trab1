#include "synthesizer.h"
using namespace std;


int synthesizer (){
    remove_file ();


    return 0;
}

void remove_file (){
    if (!get_key()){
        if (remove ("intermediary.csv") != 0){
            perror( "Error deleting file" );
        }else{
            puts( "File successfully deleted" );
        }
    }
    return;
}


int get_key(){
    char key;
    cout << "Would you like to keep the intermediary files? [Y/N]" << endl;
    cin >> key;
    if( key == 'Y' || key == 'y' || key == 'N' || key == 'n' ){
        if (key == 'Y' || key == 'y'){
            return 1;
        }else{
            return 0;
        }
    }
    return 0;
}
