//
// Created by kevinche on 12.04.2021.
//
#pragma once
#ifndef SPO_LAB1_NTFS_UTILS_H
#define SPO_LAB1_NTFS_UTILS_H

#endif //SPO_LAB1_NTFS_UTILS_H

struct ntfs_ls_info{
    char *filename;
    int dir;
    struct ntfs_ls_info *next;
};

struct ntfs_ls_info *ls(void *fs_ptr, char *path);
int count_nodes(char *path);
char *cd(void *fs_ptr, char *path);
char *pwd(void *fs_ptr);
char *cp(void *fs_ptr, char *path, char *out_path);
int print_block_devices();
void *init_fs(char *filename);
int close_fs(void *fs_ptr);
int free_infos(struct ntfs_ls_info *inode);