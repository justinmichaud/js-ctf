FROM docker.io/i386/alpine:3.20

ENV KERNEL=lts
ENV ADDPKGS="libgcc skalibs gdb gcompat"

RUN apk add openrc alpine-base agetty alpine-conf $ADDPKGS

RUN if [ "$KERNEL" == "lts" ]; then \
    apk add linux-lts \
            linux-firmware-none \
            linux-firmware-sb16; \
else \
    apk add linux-$KERNEL; \
fi

# RUN apk --no-cache add ca-certificates wget
# RUN wget -q -O /etc/apk/keys/sgerrand.rsa.pub https://alpine-pkgs.sgerrand.com/sgerrand.rsa.pub
# RUN wget https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.35-r0/glibc-2.35-r0.apk
# RUN apk --no-cache add --force-overwrite glibc-2.35-r0.apk
# RUN apk add --force-overwrite alpine-baselayout-data

RUN sed -i 's/getty 38400 tty1/agetty --autologin root tty1 linux/' /etc/inittab
RUN echo 'ttyS0::respawn:/sbin/agetty --autologin root -s ttyS0 115200 vt100' >> /etc/inittab
RUN echo "root:" | chpasswd

RUN setup-hostname localhost

# Adding networking.sh script (works only on lts kernel yet)
# RUN if [ "$KERNEL" == "lts" ]; then \
#     echo -e "rmmod ne2k-pci && modprobe ne2k-pci\nhwclock -s\nsetup-interfaces -a -r" > /root/networking.sh && \
#     chmod +x /root/networking.sh; \
# fi

# RUN echo 'console.log("Hello, world!");' > /root/hello.js

COPY build-32.zip /root/build.zip
RUN unzip /root/build.zip -d /root/

# RUN rm -f /root/libicudata.so.72
# RUN rm -f /root/libicuuc.so.72
RUN rm -f /root/libgcc_s.so.1
RUN rm -f /root/bad.ld-linux.so.2
# RUN mv /root/bad.ld-linux.so.2 /root/ld-linux.so.2
# RUN rm -f /root/libicui18n.so.72
RUN rm -f /root/libc.so.6
# RUN rm -f /root/libm.so.6
RUN rm -f /root/libstdc++.so.6


# https://wiki.alpinelinux.org/wiki/Alpine_Linux_in_a_chroot#Preparing_init_services
RUN for i in devfs dmesg mdev hwdrivers; do rc-update add $i sysinit; done
RUN for i in hwclock modules sysctl hostname syslog bootmisc; do rc-update add $i boot; done
RUN rc-update add killprocs shutdown

# Generate initramfs with 9p modules
RUN mkinitfs -F "ata base ide scsi virtio ext4 9p" $(cat /usr/share/kernel/$KERNEL/kernel.release)
