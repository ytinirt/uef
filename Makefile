KERNELDIR := /lib/modules/$(shell uname -r)/build
    # The current directory is passed to sub-makes as argument
PWD := $(shell pwd)

CC = gcc

obj-m := uef_module.o

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *~ core .depend .*.cmd *.mod.c .tmp_versions *.order *.symvers

clean:
	rm -rf *.o *.ko *~ core .depend .*.cmd *.mod.c .tmp_versions *.order *.symvers

.PHONY: modules clean
