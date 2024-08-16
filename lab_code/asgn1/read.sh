make && \
sudo dmesg -C
sudo insmod ./asgn1.ko && \
sudo chown pi:pi /dev/asgn1 && \
echo hello > /dev/asgn1 && \
cat /dev/asgn1
dmesg --level=warn+
sudo rmmod asgn1 
