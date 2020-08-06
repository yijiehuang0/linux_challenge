#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/debugfs.h>

static char* eudyptula_id = "my_id";
static char* dir_name = "eudyputula";
static char* id_name = "id";
static struct dentry* dir;

MODULE_LICENSE("GLP");

static ssize_t eudyptula_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t eudyptula_write(struct file *, const char *, size_t, loff_t *);

static const struct file_operations eudyputula_file_ops = {
	.owner = THIS_MODULE,
	.read = eudyptula_read,
	.write = eudyptula_write
};

static ssize_t eudyptula_read(struct file *f, char *buffer, size_t count,
	loff_t *offset)
{
   int eudyptula_id_len = strlen(eudyptula_id);
   return simple_read_from_buffer(buffer, count, offset, eudyptula_id,
		eudyptula_id_len);
}

static ssize_t eudyptula_write(struct file *f, const char *buffer, size_t count,
	loff_t *offset)
{
	char msg[16] = {0};
	int error;

	error = simple_write_to_buffer(msg, sizeof(msg), offset, buffer, count);
	if (error < 0)
		return error;

	if (!strncmp(msg, eudyptula_id, strlen(eudyptula_id))
		&& count - 1 == strlen(eudyptula_id))
		return count;

	return -EINVAL;
}


int init_module(void)
{
    dir = debugfs_create_dir(dir_name, NULL);
    if (IS_ERR_VALUE(dir)) {
        pr_debug("Error creating directory");
        return -ENODEV;
    }
    struct dentry *file = debugfs_create_file(id_name, 0666, dir, NULL,
            &eudyputula_file_ops);
    if (IS_ERR_VALUE(file)) {
        pr_debug("Error creating id file");
        return -ENODEV;
    }

    return 0;
}

void cleanup_module()
{
    debugfs_remove_recursive(dir);
}

