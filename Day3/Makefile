KERN_SRC = /lib/modules/$(shell uname -r)/build

obj-m += testm_len_files_struct.o

all:
	make -C $(KERN_SRC) M=$(PWD) modules
clean:
	make -C $(KERN_SRC) M=$(PWD) clean
