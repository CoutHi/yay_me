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
	install -m 0755 $(TARGET) /usr/bin/$(TARGET)
	cp $(SERVICE) /etc/systemd/system/
	systemctl enable --now $(TARGET).service

clean:
	rm -f /usr/bin/$(TARGET) /etc/systemd/system/$(TARGET).service
