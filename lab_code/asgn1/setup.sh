sudo dmesg -C
make && \
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1
sudo chown pi:pi /proc/asgn1_proc
find /usr/include/ -type f -exec cat {} + > /dev/asgn1
cat /dev/asgn1
cat ./Makefile > /dev/asgn1
cat /dev/asgn1


