#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

/* This function is called when the module is loaded. */
int simple_init(void)
{
	int days[] = {1, 2, 3, 4};
	int months[] = {7, 8, 9, 10};
	int years[] = {1994, 1995, 1996, 1997};
	int i;

       printk(KERN_INFO "------ Loading Module\n");

	LIST_HEAD(birthday_list);

	struct birthday *person;

	for (i = 0; i < 4; ++i) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = days[i];
		person->month = months[i];
		person->year = years[i];
		INIT_LIST_HEAD(&person->list);

		list_add_tail(&person->list, &birthday_list);
	}

	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = 2;
	person->month = 8;
	person->year = 1995;
	INIT_LIST_HEAD(&person->list);

	list_add_tail(&person->list, &birthday_list);

	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list) {
		printk("day: %d, month: %d, year: %d\n", ptr->day, ptr->month, ptr->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

