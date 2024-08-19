make && \
sudo dmesg -C
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1 && \
./mmap_test
# dmesg 
sudo rmmod asgn1 
