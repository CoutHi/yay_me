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
	systemctl --user disable --now update_reminder.service
	rm -f /usr/local/bin/$(TARGET) /etc/systemd/user/$(TARGET).service
