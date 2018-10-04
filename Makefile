######################
Kernel module Makefile
######################

#Genral paths
PWD := $(shell pwd)
SRC_PATH := ./src

#User customization
MODULE_NAME := perso_procfs

#Environment configuration
CFLAGS_MODULE += -Werror -DDEBUG
ARCH := x86
KERNELDIR := /lib/modules/`uname -r`/build

#Source files
SOURCE_FILES := src/mod_main.c \
		src/procfs_entry.c

#Clean files
clean-files := $(SRC_PATH)/*.o
clean-files += *.o *~ core .depend .*.cmd *.ko *.mod.c *.order *.symvers

ifneq ($(KERNELRELEASE),)
	#Kbuild part of Makefile
	obj-m := $(MODULE_NAME).o
	$(MODULE_NAME)-y := $(SOURCE_FILES:.c=.o)
	ccflags-y := -I$(src)/inc
else
	#Normal Makefile	
default:
	$(MAKE) ARCH=$(ARCH) -C $(KERNELDIR) M=$(PWD) modules
	
modules_install:
	$(MAKE) ARCH=$(ARCH) -C $(KERNELDIR) M=$(PWD) modules_install
	
#Test targets if needed ...
endif

#A clean target allready exists in the kernel Makefile but does not clean
#everything in $(MODULE_NAME)-obj
clean:
	@rm -f $(clean-files)
	@rm -rf .tmp_versions/
