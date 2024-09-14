# hid-rapoo-m50-plus-silent-mouse
Fixes Rapoo M50 Plus Silent Mouse side buttons.
Cloned from [hid_mimouse](https://github.com/matega/hid_mimouse) for Xiaomi Silent Mouse
## Prerequisites (on Ubuntu, Debian)
    $ sudo apt install build-essential linux-headers-generic dkms
(If you use a non-generic kernel, you should install the headers for that. DKMS is optional.)
## Building
    $ make
## Installing
    $ sudo make install
## DKMS
    $ sudo dkms add .
    $ sudo dkms install hid_rapoo_m50_plus_silent_mouse/1.0
## Uninstalling
    $ make uninstall
## Uninstalling DKMS
    $ sudo dkms remove hid_rapoo_m50_plus_silent_mouse/1.0 --all
