CC = gcc
CFLAGS = -Wall -g
LIBS = `pkg-config --cflags --libs libnotify glib-2.0`

TARGET = update_reminder
SRC = main.c
SERVICE = update_reminder.service

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

install:
	install -m 0755 $(TARGET) /usr/local/bin/$(TARGET)
	cp $(SERVICE) /etc/systemd/user/
	systemctl --user enable --now $(TARGET).service

clean:
	rm -f /usr/local/bin/$(TARGET) ~/.config/systemd/user/$(TARGET).service
	systemctl --user disable --now update_reminder.service
