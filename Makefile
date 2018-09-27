##################################################################################
#Important notes from https://www.kernel.org/doc/Documentation/kbuild/modules.txt
#"kbuild" is the build system used by the Linux kernel.
#-C $KDIR
#		The directory where the kernel source is located.
#		"make" will actually change to the specified directory
#		when executing and will change back when finished.
#M=$PWD
#		Informs kbuild that an external module is being built.
#		The value given to "M" is the absolute path of the
#		directory where the external module (kbuild file) is
#		located.
#The file may be as simple as a single line:
#
#	obj-m := <module_name>.o
#
#The kbuild system will build <module_name>.o from <module_name>.c,
#and, after linking, will result in the kernel module <module_name>.ko.
#When the module is built from multiple sources, an additional line is
#needed listing the files:
#
#	<module_name>-y := <src1>.o <src2>.o ...
#
#Instead of adding all object files one by one, there is a quick command to do it:
#
#	<module_name>-y := <src_files>:.c=.o)
#Where <src_files> contains all sources.
#
#$(src) provides the absolute path by
#	pointing to the directory where the currently executing kbuild
#	file is located.
#
#Additional functionality, such as test targets, can be included
#	but should be filtered out from kbuild due to possible name
#	clashes.
#The check for KERNELRELEASE is used to separate the two parts
#	of the makefile:
# -the first pass is by the "make" instance run on the command line; 
# -the second pass is by the kbuild system, which is
#	initiated by the parameterized "make" in the default target.
#
#Modules which are included in the kernel are installed in the
#directory (by running make with modules_install target):
#
#	/lib/modules/$(KERNELRELEASE)/kernel/
#
#And external modules are installed in:
#
#	/lib/modules/$(KERNELRELEASE)/extra/
#For another path see INSTALL_MOD_PATH
#
##################################################################################

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
