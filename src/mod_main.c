/*!
 * \file 	mod_main.c
 * \brief 	Module init/exit functions
 * \author 	O.D
 * \version 0.1
 * \date 	September 4th, 2018
 *
 * O.D - September 4th, 2018
 * File creation.
 * Define module init and exit functions when module is loaded and unloaded.
 *
 */
 
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/proc_fs.h>

#include "procfs_entry.h"

static int __init mod_init(void);
static void __exit mod_exit(void);

MODULE_AUTHOR("O.D");
MODULE_DESCRIPTION(MOD_DESCRIPT);
MODULE_LICENSE(MOD_LIC);
MODULE_VERSION(MOD_VER);
MODULE_ALIAS(MOD_ALIAS);

/*!
 * \fn 		mod_init
 * \brief 	Module init
 * \param 	void
 * \return 	0
 * \author 	O.D
 */
int __init mod_init(void)
{
    printk(KERN_INFO "module loaded: %s v%s, %s\n", MOD_ALIAS, MOD_VER, MOD_DESCRIPT);

    if (proc_entry_init() < 0)
        return -1;    
        
    return 0;
}

/*!
 * \fn 		mod_exit
 * \brief 	Module exit
 * \param 	void
 * \return 	void
 * \author 	O.D
 */
void __exit mod_exit(void)
{
    printk(KERN_INFO "module unloaded: %s\n", MOD_ALIAS);
    proc_entry_exit();
}

module_init(mod_init);
module_exit(mod_exit);

