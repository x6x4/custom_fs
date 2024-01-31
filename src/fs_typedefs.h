#include <linux/init.h>    //  from /usr/src
#include <linux/module.h>  //  from /usr/src
#include <linux/fs.h>

typedef struct file_system_type file_system_type;
typedef struct dentry dentry;
typedef struct super_block super_block;
typedef struct super_operations super_operations;
typedef struct inode inode;

#define CUSTOM_FS_MAGIC 1408
