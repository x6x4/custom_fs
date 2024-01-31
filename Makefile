
obj-m += custom_fs.o
custom_fs-objs := custom_fs_src.o
 
MAKEFILE_DIR=$(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) clean 
