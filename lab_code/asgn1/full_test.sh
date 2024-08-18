make && \
sudo dmesg -C
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1 && \
gcc ./test_all.c -o test_all && \
./test_all
dmesg 
sudo rmmod asgn1 
