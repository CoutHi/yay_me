# Update_Reminder

### What is it?
If you're like me and can't stop running the update command on your arch system every damn minute, maybe this program can help you.
It simply sends you a notification that you might want to update every monday, that's all it does, yet maybe it's enough to make us stop, we'll see.

### Installation

Just copy the repo and run: 
```console
make

sudo make install
```
, that's all.

### Usage

You can do 
```console
update_reminder &
```
This way, it'll run in the background. 

A systemd file is in the works to automate the running as well so you don't need to worry about anything.

### Disabling the daemon
Run:
```console
systemctl --user disable --now update_reminder.service
```

### Uninstallation

Go to the git directory and run:

```console
sudo make clean
```

## Please report any bugs you encounter
