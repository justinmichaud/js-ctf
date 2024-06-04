FROM i386/debian:bullseye

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && \
    apt --yes --no-install-recommends install \
        linux-image-686 grub2 systemd \
        libterm-readline-perl-perl \
        libc6-dev \
        unzip \
        tmux \
        vim \
        gdb \
        dhcpcd5 \
        net-tools netcat \
    && \
    touch /root/.Xdefaults && \
    echo 'LANG="en_US.UTF-8"' > /etc/default/locale && \
    chsh -s /bin/bash && \
    echo "root:root" | chpasswd && \
    mkdir -p /etc/systemd/system/serial-getty@ttyS0.service.d/ && \
    systemctl enable serial-getty@ttyS0.service && \
    rm /lib/systemd/system/getty.target.wants/getty-static.service && \
    rm /etc/motd /etc/issue && \
    systemctl disable systemd-timesyncd.service && \
    systemctl disable apt-daily.timer && \
    systemctl disable apt-daily-upgrade.timer && \
    systemctl disable dhcpcd.service && \
    echo "tmpfs /tmp tmpfs nodev,nosuid 0 0" >> /etc/fstab \


COPY getty-noclear.conf getty-override.conf /etc/systemd/system/getty@tty1.service.d/
COPY getty-autologin-serial.conf /etc/systemd/system/serial-getty@ttyS0.service.d/

COPY logind.conf /etc/systemd/logind.conf

#COPY xinitrc /root/.xinitrc
COPY xorg.conf /etc/X11/
COPY networking.sh /root/

COPY boot-9p /etc/initramfs-tools/scripts/boot-9p

# this needs to be commented out in order to boot from hdd
RUN printf '%s\n' 9p 9pnet 9pnet_virtio virtio virtio_ring virtio_pci | tee -a /etc/initramfs-tools/modules && \
    echo 'BOOT=boot-9p' | tee -a /etc/initramfs-tools/initramfs.conf && \
    update-initramfs -u

RUN apt-get --yes clean && \
    rm -r /var/lib/apt/lists/* && \
    rm -r /usr/share/doc/* && \
    rm -r /usr/share/man/* && \
    rm -r /usr/share/locale/?? && \
    rm /var/log/*.log /var/log/lastlog /var/log/wtmp /var/log/apt/*.log /var/log/apt/*.xz

COPY build-32.zip /root/build.zip
RUN unzip /root/build.zip -d /root/

RUN echo "deb http://deb.debian.org/debian bookworm main" > /etc/apt/sources.list
RUN apt update
RUN apt install libc6 libc6-dev libc6-dbg --yes

RUN echo "echo 0 | tee /proc/sys/kernel/randomize_va_space" >> ~/.bashrc
RUN echo "setarch i686 -R /bin/bash"> /root/shell.sh; chmod +x /root/shell.sh

RUN echo "LD_LIBRARY_PATH=/root gdb --args /root/jsc 0*.js"> /root/debug.sh; chmod +x /root/debug.sh
RUN echo "LD_LIBRARY_PATH=/root  /root/jsc 0*.js"> /root/run.sh; chmod +x /root/run.sh

RUN echo "LD_LIBRARY_PATH=/root /root/jsc soln/0*.js"> /root/run-0.sh; chmod +x /root/run-0.sh
RUN echo "LD_LIBRARY_PATH=/root gdb --args /root/jsc soln/0*.js"> /root/debug-0.sh; chmod +x /root/debug-0.sh
RUN echo "LD_LIBRARY_PATH=/root /root/jsc soln/1*.js"> /root/run-1.sh; chmod +x /root/run-1.sh
RUN echo "LD_LIBRARY_PATH=/root gdb --args /root/jsc soln/1*.js"> /root/debug-1.sh; chmod +x /root/debug-1.sh
RUN echo "LD_LIBRARY_PATH=/root /root/jsc soln/2*.js"> /root/run-2.sh; chmod +x /root/run-2.sh
RUN echo "LD_LIBRARY_PATH=/root gdb --args /root/jsc soln/2*.js"> /root/debug-2.sh; chmod +x /root/debug-2.sh

# RUN rm -f /root/libicudata.so.72
# RUN rm -f /root/libicuuc.so.72
# RUN rm -f /root/libgcc_s.so.1
# RUN rm -f /root/bad.ld-linux.so.2
# RUN mv /root/bad.ld-linux.so.2 /root/ld-linux.so.2
# RUN rm -f /root/libicui18n.so.72
# RUN rm -f /root/libc.so.6
# RUN rm -f /root/libm.so.6
# RUN rm -f /root/libstdc++.so.6