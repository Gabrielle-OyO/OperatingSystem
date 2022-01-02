#include <linux/module.h>
MODULE_LICENSE("Dua; BSD/GPL");
#include <linux/init.h>
staic int __init hello_init(void)
{
    printfk("Hello World\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printf("Goodbye\n");
}
module_init(hello_init);
module_exit(helle_exit);