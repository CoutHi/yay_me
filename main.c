#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

int is_monday(char time[]){
    char needed[4] = "Mon"; 

    int i = 0;
    for(i = 0; i < 4; i++){
        if (needed[i] != time[i]){
            return 1;
        }
        else {
            return 0;
        }
    }
}

int main(){

    while(1) {

        time_t t = time(NULL);
        struct tm* local = localtime(&t);

        char time_string[4];

        strftime(time_string, sizeof time_string, "%a", local);
        puts(time_string);

        int status = is_monday(time_string);

        switch (status) {
            case 0:
                system("notify-send \"It's Monday! You might want to update your system.\"");
                break;
            default:
                break;
        }

        sleep(3600);
    }
    return 0;
}
