# yay_me()

### What is it?
If you're like me and can't stop running the update command on your arch system every damn minute, maybe this program can help you.
It simply sends you a notification that you might want to update every monday, that's all it does, yet maybe it's enough to make us stop, we'll see.

### Installation

Just copy the repo and run: 
```console
make

sudo make install
```
that's all.

### Usage

It's handled automatically by systemd, but if you want to run it manually you can do:

```console
yay_me &
```
### Disabling the daemon
Run:
```console
systemctl --user disable --now yay_me.service
```

### Uninstallation

Go to the git directory and run:

```console
sudo make clean
```

## Please report any bugs you encounter
