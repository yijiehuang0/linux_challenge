#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static char* eudyptula_id = "my_id";

MODULE_LICENSE("GLP");

static ssize_t eudyptula_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t eudyptula_write(struct file *, const char *, size_t, loff_t *);


static const struct file_operations eudyputula_file_ops = {
	.owner = THIS_MODULE,
	.read = eudyptula_read,
	.write = eudyptula_write
};

static struct miscdevice device = {
    MISC_DYNAMIC_MINOR,
    "eudyptula_char_misc_device",
    &eudyputula_file_ops
};


static ssize_t eudyptula_read(struct file *f, char *buffer, size_t count,
	loff_t *offset)
{
   // read from buffer to userspace
   int eudyptula_id_len = strlen(eudyptula_id);
   return simple_read_from_buffer(buffer, count, offset, eudyptula_id,
		eudyptula_id_len);
}

static ssize_t eudyptula_write(struct file *f, const char *buffer, size_t count,
	loff_t *offset)
{
	char msg[16] = {0};
	int ret;

	ret = simple_write_to_buffer(msg, sizeof(msg), offset, buffer, count);
	if (ret < 0)
		return ret;

	if (!strncmp(msg, eudyptula_id, strlen(eudyptula_id))
		&& count - 1 == strlen(eudyptula_id))
		return count;

	return -EINVAL;
}


int init_module(void)
{
    int error = misc_register(&device);
    if(error != 0)
       pr_debug("Failed Registering Eudyptula Misc Char Device");
    return error;
}

void cleanup_module()
{
    misc_deregister(&device);
}


/*
 *
 *
struct miscdevice  {
	int minor;
	const char *name;
	const struct file_operations *fops;
	struct list_head list;
	struct device *parent;
	struct device *this_device;
	const struct attribute_group **groups;
	const char *nodename;
	umode_t mode;
};

extern int misc_register(struct miscdevice *misc);
extern void misc_deregister(struct miscdevice *misc);

	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
*/
