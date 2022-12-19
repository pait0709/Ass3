#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/syscalls.h>


static int pid;
module_param(pid, int, 0);

static int __init pid_details_init(void)
{
    struct task_struct *task;
    struct pid *pid_struct;

    printk(KERN_INFO "Retrieving details for PID %d\n", pid);

    pid_struct = find_get_pid(pid);
    task = get_pid_task(pid_struct, PIDTYPE_PID);

    if (task == NULL) {
        printk(KERN_INFO "No task found for PID %d\n", pid);
        return -1;
    }

    printk(KERN_INFO "Process name: %s\n", task->comm);
    printk(KERN_INFO "Process PID: %d\n", task->pid);
    printk(KERN_INFO "Process UID: %d\n", task->cred->uid.val);
    printk(KERN_INFO "Process Group ID: %d\n", task->group_leader->pid);
    

    return 0;
}

static void __exit pid_details_exit(void)
{
    printk(KERN_INFO "Exiting pid_details module\n");
}

module_init(pid_details_init);
module_exit(pid_details_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavit");
MODULE_DESCRIPTION("Kernel module to retrieve details for a given PID");

