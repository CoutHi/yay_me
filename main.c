#include <glib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <libnotify/notify.h>

int is_monday(char time[]){
    char needed[4] = "Mon"; 

    int i = 0;
    for(i = 0; i < 4; i++){
        if (needed[i] != time[i]){
            return 1;
        }
    }
    return 0;
}

int main(){

     if (!notify_init("Update Reminder")) {
        fprintf(stderr, "Failed to initialize libnotify\n");
        return 1;
    }   

    while(1) {

        time_t t = time(NULL);
        struct tm* local = localtime(&t);

        char time_string[4];

        strftime(time_string, sizeof time_string, "%a", local);
        printf("%s",time_string);

        if (is_monday(time_string) == 0){
            NotifyNotification* notification = notify_notification_new("Update Reminder","It's Monday! You might want to update your system.",NULL);
            if(notification != NULL){
                notify_notification_show(notification,NULL);
            }
            else {
                fprintf(stderr, "Failed to create notification!\n");
            }
        }

        sleep(3600);
    }
    notify_uninit();
    return 0;
}
