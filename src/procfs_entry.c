
/*!
 * \file 	procfs_entry.c
 * \brief 	Red/Write functions for procfs
 * \author 	O.D
 * \version 0.1
 * \date 	September 4th, 2018
 *
 * O.D - September 4th, 2018
 * File creation.
 * Define RW funtions for procfs entries.
 *
 */
 
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#include "procfs_entry.h"

static int proc_status_fs(struct inode *inode_p, struct file *file_p);
static int proc_status_read(struct seq_file *seq_p, void *data_p);
static ssize_t proc_counter_write(struct file *file_p, const char *user_buf_p, size_t size, loff_t *pos_p);

static char buf_g[30]; /*path to "/proc/MOD_ALIAS" (change path size if needed)*/
static struct proc_dir_entry *proc_dir_p = NULL;
static const struct file_operations proc_status_fops = {
    .owner = THIS_MODULE,
    .open = proc_status_fs,
    .read = seq_read,
    .write = proc_counter_write,
    .llseek = seq_lseek,
    .release = single_release,
};

/*!
 * \fn 		proc_entry_init
 * \brief 	Module init
 * \param 	void
 * \return 	0 if no error, else -1.
 * \author 	O.D
 */
int proc_entry_init(void)
{
    /*sprintf(buf_g, "driver/%s", MOD_ALIAS);*/
    sprintf(buf_g, "%s", MOD_ALIAS);
    proc_dir_p = proc_mkdir(buf_g, NULL);
    
    if (likely(proc_dir_p)) {
        proc_create_data("status", S_IRUGO | S_IWUGO, proc_dir_p, &proc_status_fops, NULL);
        return 0;
    }
    else {
        printk(KERN_INFO "issues creating procfs entry\n");
        return -1;
    }
}

/*!
 * \fn 		proc_entry_exit
 * \brief 	Module exit
 * \param 	void
 * \return 	void
 * \author 	O.D
 */
void proc_entry_exit(void)
{
    /*sprintf(buf_g, "driver/%s", MOD_ALIAS);*/
    sprintf(buf_g, "%s", MOD_ALIAS);
    remove_proc_entry("status", proc_dir_p);
    remove_proc_entry(buf_g, NULL);
}

/*!
 * \fn 		proc_status_fs
 * \brief 	Called from open
 * \param 	struct inode *, struct file *
 * \return 	int: return value of single_open
 * \author 	O.D
 */
int proc_status_fs(struct inode *inode_p, struct file *file_p)
{
    return single_open(file_p, proc_status_read, NULL);
} 

/*!
 * \fn 		proc_status_read
 * \brief 	Callback used by single_open
 *			Do the seq_print here for the user.
 * \param 	struct seq_file *, void *
 * \return 	0
 * \author 	O.D
 */
int proc_status_read(struct seq_file *seq_p, void *data_p)
{
    (void)data_p;
    
    seq_printf(seq_p, "OK\n");

    return 0;
}

/*!
 * \fn 		proc_counter_write
 * \brief 	Called from write
 * \param 	struct file *, const char *, size_t, loff_t *
 * \return 	ssize_t: the buffer size sent by the user
 * \author 	O.D
 */
ssize_t proc_counter_write(struct file *file_p, const char *user_buf_p, size_t size, loff_t *pos_p)
{
    size_t len = 20;
    char buf[21];
    
    (void)pos_p;

    if (len > size)
        len = size;

    if (copy_from_user(buf, user_buf_p, len))
        return -EFAULT;

    buf[len] = 0;

    printk(KERN_INFO "%d char receved from user\n", (int)len);

    return len;   
} 
