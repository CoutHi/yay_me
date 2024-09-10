CC = gcc
CFLAGS = -Wall -g
LIBS = `pkg-config --cflags --libs libnotify glib-2.0`

TARGET = yay_me
SRC = main.c
SERVICE = yay_me.service

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

install:
	install -m 0755 $(TARGET) /usr/local/bin/$(TARGET)
	cp $(SERVICE) /etc/systemd/user/
	systemctl --user enable --now $(SERVICE)

clean:
	rm -f /usr/local/bin/$(TARGET) /etc/systemd/user/$(SERVICE)
	systemctl --user disable --now $(SERVICE)
