CFLAGS_usb_helloworld.o = -DDEBUG
obj-m += usb_helloworld.o
KDIR ?= /lib/modules/$(shell uname -r)/build
# KDIR ?=../linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
