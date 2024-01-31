cmd_/root/custom_fs/build/custom_fs.mod := printf '%s\n'   build/custom_fs_src.o | awk '!x[$$0]++ { print("/root/custom_fs/"$$0) }' > /root/custom_fs/build/custom_fs.mod
