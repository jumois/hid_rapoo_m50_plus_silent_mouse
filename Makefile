obj-m += hid-rapoo-m50-plus-silent-mouse.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
install:
	cp $(shell pwd)/hid-rapoo-m50-plus-silent-mouse.ko /lib/modules/$(shell uname -r)/kernel/drivers/hid/
	depmod -a
uninstall:
	rm $(shell pwd)/hid-rapoo-m50-plus-silent-mouse.ko /lib/modules/$(shell uname -r)/kernel/drivers/hid/hid-rapoo-m50-plus-silent-mouse.ko
	depmod -a
dkms:
	make -C $(INCLUDEDIR) M=$(PWD) modules

