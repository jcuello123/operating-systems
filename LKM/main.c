#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/string.h> 

struct task_struct *g;
struct task_struct *t;
struct task_struct *task;        /*    Structure defined in sched.h for tasks/processes    */
struct task_struct *task_child;        /*    Structure needed to iterate through task children    */
struct list_head *list;            /*    Structure needed to iterate through the list in each task->children struct    */

static struct timer_list my_timer;
int delay = 50;

void my_timer_callback(unsigned long data){
    for_each_process( task ){   
	if (strcmp(task->comm, "main") == 0){
	    
	
         /*    for_each_process() MACRO for iterating through each task in the os located in linux\sched\signal.h    */
        printk(KERN_INFO "\nPARENT PID: %d. PROCESS: %s",task->pid, task->comm);/*    log parent id/executable name/state    */
        do_each_thread(g, t){                        /*    list_for_each MACRO to iterate through task->children    */
 	    printk(KERN_INFO "CHILD PID: %d. PROCESS: %s\n", t->pid, t->comm);
            //task_child = list_entry( list, struct task_struct, sibling );    /*    using list_entry to declare all vars in task_child struct    */
     
           // printk(KERN_INFO "\nCHILD OF %s[%d]. PID: %d. PROCESS: %s",task->comm, task->pid, /*    log child of and child pid/name/state    */
                //task_child->pid, task_child->comm);
        } while_each_thread(g, t);
        printk("-----------------------------------------------------");    /*for aesthetics*/
	}

    }         

        mod_timer(&my_timer, jiffies + msecs_to_jiffies(delay));  

}

int iterate_init(void)                    /*    Init Module    */
{
    setup_timer(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(delay));  
    return 0; 
}                /*    End of Init Module    */
     
void cleanup_exit(void)        /*    Exit Module    */
{
    del_timer(&my_timer);
}                /*    End of Exit Module    */
 
module_init(iterate_init);    /*    Load Module MACRO    */
module_exit(cleanup_exit);    /*    Remove Module MACRO    */
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ITERATE THROUGH ALL PROCESSES/CHILD PROCESSES IN THE OS");
MODULE_AUTHOR("Laerehte");
