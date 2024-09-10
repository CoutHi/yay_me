#include <glib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <libnotify/notify.h>
#include <signal.h>

#define EXT_SUCCESS 0

char* notification_message = "It's Monday! You might want to update your system.";

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

void graceful_exit(int signal){
   notify_uninit(); 
   printf("\nTerminated\n");
   exit(EXT_SUCCESS);
}

int main(){

    if (!notify_init("Update Reminder")) {
        fprintf(stderr, "Failed to initialize libnotify\n");
        exit(1);
    }   

    signal(SIGINT, graceful_exit);

    while(1) {

        time_t t = time(NULL);
        struct tm* local = localtime(&t);

        char time_string[4];

        strftime(time_string, sizeof time_string, "%a", local);

        if (is_monday(time_string) == 0){
            NotifyNotification* notification = notify_notification_new("Update Reminder",notification_message, NULL);
            if(notification != NULL){
                notify_notification_show(notification,NULL);
                g_object_unref(G_OBJECT(notification));
            }
            else {
                fprintf(stderr, "Failed to create notification!\n");
            }
        }

        sleep(3600);
    }
    notify_uninit();
    exit(EXT_SUCCESS);
}
