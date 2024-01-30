#include <linux/init.h>    //  from /usr/src
#include <linux/module.h>  //  from /usr/src

static struct file_system_type 
custom_fs_descriptor {
	.owner = THIS_MODULE,         //  link counter
	.name = "custom_fs",          
	.mount = custom_fs_mount,     //  mount func
	.kill_sb = kill_block_super,  //  unmount func
	.fs_flags = FS_REQUIRES_DEV,  //  filesystem requires disk
};

static int __init 
custom_fs_init (void) {
	pr_err ("custom fs module loaded\n");
	register_filesystem (&custom_fs_descriptor);	

	return 0;
}

static void __exit custom_fs_fini (void) {
	pr_err ("custom fs module unloaded\n");
	unregister_filesystem (&custom_fs_descriptor);
}

module_init (custom_fs_init);
module_exit (custom_fs_fini);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("AUTHOR");
