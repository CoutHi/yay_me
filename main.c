#include <glib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <libnotify/notify.h>
#include <libnotify/notification.h>
#include <libnotify/notify-enum-types.h>
#include <libnotify/notify-features.h>
#include <signal.h>

// This doesn't ever need to change
#define NOTIFICATION_MESSAGE "It's Monday! You might want to update your system."

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

// Used to query the server for testing and debugging
void graceful_exit(int signal){
   notify_uninit(); 
   printf("\nTerminated\n");
   exit(EXIT_SUCCESS);
}

int main(){

    // Initialize libnotify, exit if it fails
    if (!notify_init("Update Reminder")) {
        fprintf(stderr, "Failed to initialize libnotify\n");
        exit(EXIT_FAILURE);
    }   

    char *name = NULL, *vendor = NULL, *version = NULL, *spec_version = NULL;

    // Get server information, used for testing/debugging
    if (notify_get_server_info(&name, &vendor, &version, &spec_version)) {
        printf("\nName: %s\nVendor: %s\nVersion: %s\nSpec Version: %s\n",
            name, vendor, version, spec_version);
        
        // Free the allocated memory
        g_free(name);
        g_free(vendor);
        g_free(version);
        g_free(spec_version);
    } else {
        fprintf(stderr, "Failed to get server info\n");
    }

//    Not stable and well supported yet
//    notify_set_app_icon("./online-arcade-pc-game-pacman.svg");

    // We need to exit gracefully if termination signal is received, uninitializing libnotify before we exit
    signal(SIGINT, graceful_exit);

    while(1) {

        time_t t = time(NULL);
        struct tm* local = localtime(&t);
        
        // Use this string to check against desired date
        char time_string[4];

        // We only need the current day, so we invoke %a
        strftime(time_string, sizeof time_string, "%a", local);
        // For Debugging
        printf("\n%s",time_string);

        if (is_monday(time_string) == 0){
            NotifyNotification* notification = notify_notification_new("Update Reminder",NOTIFICATION_MESSAGE, NULL);
            if(notification != NULL){
                notify_notification_show(notification,NULL);
                // free the notification variable
                g_object_unref(G_OBJECT(notification));
            }
            else {
                fprintf(stderr, "Failed to create notification!\n");
            }
        }

        // Run the program every hour
        sleep(3600);
    }
    // We should never get here, but just in case we do a graceful exit.
    notify_uninit();
    exit(EXIT_SUCCESS);
}
