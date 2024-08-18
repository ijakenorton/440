make && \
sudo dmesg -C
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1 && \
cat ./asgn1_skel.c > /dev/asgn1 && \
cat /dev/asgn1
dmesg 
sudo rmmod asgn1 
