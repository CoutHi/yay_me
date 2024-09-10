all:
	gcc main.c -o ./update_reminder

install:
	gcc main.c -o /usr/bin/update_reminder
