#include "fs_typedefs.h"

//  custom fs superblock destructor - in kill_block_super
static void custom_fs_put_super (super_block *sb) {
	pr_err ("custom_fs superblock destroyed");
}

//  custom fs superblock methods
static const super_operations custom_fs_super_ops = {
	.put_super = custom_fs_put_super
};

static int custom_fs_fill_sb (super_block *sb, void *data, int silent) {
	
	sb->s_magic = CUSTOM_FS_MAGIC;
	sb->s_op = &custom_fs_super_ops;

	inode *root = new_inode (sb);	
	if (!root) {
		pr_err ("inode allocation failed\n");
		return -ENOMEM;
	}

	root->i_ino = 0;
	root->i_sb = sb;
	root->i_atime = root->i_mtime = root->i_ctime = current_time(root);
	
	inode_init_owner (NULL, NULL, root, S_IFDIR);

	sb->s_root = d_make_root (root);
	if (!sb->s_root) {
		pr_err ("root creation failed\n");
		return -ENOMEM;
	}

	return 0;
}

//  returns new directory entry - root of our filesystem
static dentry *
custom_fs_mount (file_system_type *fs_type, int flags,
	const char *dev, void *data) {
	
	dentry *const entry = mount_bdev (fs_type, flags, 
		dev, data, custom_fs_fill_sb);  //  bdev - block device

	if (IS_ERR(entry)) pr_err ("custom fs mounting failed\n");
	else pr_err ("custom fs mounted\n");

	return entry;
} 

static file_system_type 
custom_fs_descriptor = {
	.owner = THIS_MODULE,         //  link counter for module fs (NULL for statically linked)
	.name = "custom_fs",          
	.mount = custom_fs_mount,     //  mount func - reads sb from disk to memory
	.kill_sb = kill_block_super,  //  unmount func - provided by kernel
	.fs_flags = FS_REQUIRES_DEV   //  filesystem requires disk (i.e. block device)
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

module_init (custom_fs_init);  //  -> init_module
module_exit (custom_fs_fini);  //  -> cleanup_module

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("AUTHOR");
