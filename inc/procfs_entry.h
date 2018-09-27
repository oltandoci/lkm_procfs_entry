#ifndef PROCFS_ENTRY_H_
#define PROCFS_ENTRY_H_

/*!
 * \file 	procfs_entry.h
 * \brief 	Header file for the module
 * \author 	O.D
 * \version 0.1
 * \date 	September 4th, 2018
 */

#define MOD_VER "0.0.0"
#define MOD_LIC "GPL"
#define MOD_DESCRIPT "test module for procfs entry"
#define MOD_ALIAS "perso_procfs"

int proc_entry_init(void);
void proc_entry_exit(void);

#endif
