## Installation and configuration of ubuntu 16.04

Create a bootable USB from windows
    
    Use "rawrite32" to .

Upgrade
    
    sudo apt update & apt upgrade

Firewall: NetFilter/iptables

    sudo iptables -L 

Runlevel

    $ systemctl get-default
       graphical.target
    $ systemctl list-units --type=target
    $ systemctl set-default multi-user.target  : is runlevel3


Desktop

    package: gnome-shell


Activate root

    sudo passwd root
    ; To disable root
    sudo passwd -d root 


Disable ipv6

    # add to /etc/sysctl.conf
    net.ipv6.conf.all.disable_ipv6 = 1
    net.ipv6.conf.default.disable_ipv6 = 1
    net.ipv6.conf.lo.disable_ipv6 = 1

Create an icon in Dash panel

    ; create file ~/.local/share/applications/android-studio.desktop
    [Desktop Entry]
    Name=the name you want shown
    Comment=
    Exec=/opt/android-studio/bin/studio.sh
    Icon=icon name
    Terminal=false
    Type=Application
    StartupNotify=true

compiz: high cpu

    apt install compizconfig-settings-manager
	On OpenGL, uncheck the option "Sync to VBlank"
	
	
## Power Optimisation
- Decrease screen brightness
- Firefox
  - Image Block extension
  - Do these tweaks
    http://www.makeuseof.com/tag/speed-up-firefox-immediately-with-these-6-simple-tweaks/
- powertop: good pckage
- Disable N/I-Watchdog
  https://fixmynix.com/disable-nmi-watchdog-linux/
- increase dirty writeback timout from 500 to 1500(15seconds)
  in file /proc/sys/vm/dirty_writeback_centisecs
- See these tricks(For Thinkpad)
  http://www.thinkwiki.org/wiki/How_to_reduce_power_consumption
  Bee carfull: dont activate laptop_mode!
- Install Package **laptop-mode-tools**:
  https://doc.ubuntu-fr.org/laptop-mode-tools

## Services 
Three tools: systemd, upstart, SystemV

- Systemd: replaces upstart and systemV(old)
```
   - List services started on boot
     systemd-analyze blame
   - Disable/Enable a service
     systemctl disable|enable <Nom_du_service>.service
   - start/stop a service 
     systemctl stop|start <Nom_du_service>.service
```

- SystemV
```
  - Scripts in: /etc/init.d/
  - stop/start
    service start apache2
```
  
## Apache PHP MySQL
Installation
```
  sudo apt-get install apache2 php mysql-server
```
- securing Apache
  http://xianshield.org/guides/apache2.0guide.html


## Packages
- Terminator : the best terminal 
- Konsole: mieux que Gnome Terminal


## VirtualBox

#### Networking
1. NAT : Browse the Web from the Guest
2. Host-only networking: Access the Guest from the Host (and Other Guests). But not outside world.
  - Open VirtualBox, File>Preferences>NetWork, and add Host-only-Networks (vboxnet0)
  ```
    Disable DHCP
    Ipv4 address: 10.98.56.1
    Mask : 255.255.255.0
    Ipv6 address null, length 0
  ```
  - Open Settings of the VM, and set vboxnet0 network.
  - on Geust
  ```
  ifconfig -a   ; find the mounted nic device. 
  edit /etc/network/interfaces
     auto enp0s3
     iface enp0s3 inet static
       address 10.98.56.101
       netmask 255.255.255.0
       broadcast 10.98.56.256
       gateway 10.98.56.1
  sudo /etc/init.d/networking restart
  ```
- Internal networking: Guest communicate only with other guests.
- Bridged networking: the virtual machines can talk to each other and the host as if 
  they were connected through a physical Ethernet switch. the VM can directly communicate with the outside world.
- Host-only networking:  A virtual network interface (similar to a loopback interface) is created on the host, 
  providing connectivity among virtual machines and the host. 
  For example, one virtual machine may contain a web server and a second one a database, and since they 
  are intended to talk to each other, the appliance can instruct VirtualBox to set up a host-only 
  network for the two. 
  A second (bridged) network would then connect the web server to the outside world to serve data to, 
  but the outside world cannot connect to the database.

#### Shared folder
You must install VBox additions to use shared folders

shared folder permission denied
```
 sudo adduser your-user vboxsf
 sudo reboot now
```













