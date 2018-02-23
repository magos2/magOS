# Ubuntu Installation Automation
---------------------------------------------------------------
Kickstat is developped by RedHat

These are step by step for ubuntu server 16.04.

Install  package: system-config-kickstart

Generate kickstart file

    admin2@vbox:~$ system-config-kickstart  #save as ks.cfg

Personalise ks.cfg and  ks.presseed 

Mount ISO

    mount -t iso9660 -o loop ~/utils/ubuntu-16.04.2-server-amd64.iso /mnt/cdrom

Personalization 

    mkdir /tmp/ubuntu_custom
    cd /mnt/cdrom/
    tar cf - . | (cd /tmp/ubuntu_custom && tar xfp -)
    cp ~/magOS/documentation/ks.* /tmp/ubuntu_custom/

Edit isolinux/txt.cfg

    label install
     menu label ^Install Ubuntu Server
     kernel /install/vmlinuz
     append  file=/cdrom/ks.preseed ks=cdrom:/ks.cfg vga=788 initrd=/install/initrd.gz quiet  ---

Create ISO

    apt install mkisofs
    cd /tmp/ubuntu_custom
    mkisofs -o ~/utils/ubuntu-16.04.2-server-amd64_custom.iso -V "ubuntu-16.04 amd64 Custom ISO" \
            -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table \
            -J -R /tmp/ubuntu_custom/ 

  
# PXE Boot Install
----------------------------------------------------------------------
Conditions

    192.168.0.1: router (i.e. LAN default gateway) and DNS recursive server
    192.168.0.2: Server (will host a DHCP and TFTP server)
    192.168.0.x: Client (to be installed)
 

# Docs
---------------------------------------------------------------
- https://doc.ubuntu-fr.org/kickstart
- https://wiki.dinfadom.com/index.php/Kickstart_-_Ubuntu_16.04_LTS
- Kickstart and VirtualBox: https://gist.github.com/jtyr/816e46c2c5d9345bd6c9


