obj-m += splitmod.o
splitmod-objs := start.o stop.o

KERNEL_SOURCE = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_SOURCE) M=$(PWD) modules
clean:
	make -C $(KERNEL_SOURCE) M=$(PWD) clean