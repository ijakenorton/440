sudo dmesg -C
make && \
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1
sudo chown pi:pi /proc/asgn1_proc
sudo dmesg
