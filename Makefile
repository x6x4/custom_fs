
obj-m += build/custom_fs.o
build/custom_fs-objs := build/custom_fs_src.o
build/custom_fs_src.o : src/custom_fs_src.c
	$(CC) -c $< -o $@
 
MAKEFILE_DIR=$(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(MAKEFILE_DIR) clean 
