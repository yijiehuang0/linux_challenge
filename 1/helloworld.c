#include <linux/module.h>   
#include <linux/kernel.h>  
#include <linux/init.h>   

MODULE_LICENSE("GPL");   
MODULE_AUTHOR("EJ Huang");
MODULE_DESCRIPTION("Hello World"); 

static int __init helloworld_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0;    
}

static void __exit helloworld_cleanup(void)
{
    printk(KERN_INFO "Deleted helloworld module.\n");
}

module_init(helloworld_init);      
module_exit(helloworld_cleanup);  
