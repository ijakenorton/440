make && \
sudo dmesg -C
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1 && \
gcc ./mem_test.c -o mem_test && \
./mem_test
dmesg 
sudo rmmod asgn1 
