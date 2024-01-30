obj-m := custom_fs.o
custom_fs-objs := custom_fs_src.o

all:
	cd build
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean 
