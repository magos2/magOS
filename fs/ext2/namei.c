#include <string.h>
#include <ext2.h>
#include <file.h>
#include <errno.h>
#include <sched.h>
#include <kernel.h>

/*Algorithm:
  IN                     OUT
  path=/usr/local        buf=usr, return=/local 
  path=usr/local         buf=usr, return=/local 
  path=local             buf=local, return=NULL
 */
char* path_walk(char *path, char* buf)
{
  char *pathp = path;
  char *bufp  = buf;
  while (*pathp == '/') pathp++; /*skipe next slashes: /////local*/
  for (; *pathp != '/' && *pathp != '\0'; pathp++, bufp++)
    *bufp = *pathp;
  *bufp = '\0';
  return pathp;         
}


int check_access(inode) {
  return 0;
}

/* namei : convert a pathname to inode.
 * in : pathname ,ex. "/home/test/ab.txt", "./test/ab.txt", ../test/ab.txt, /bin/shell
 * out : inode
 * ret : error code
 */
int namei (char * pathname, int prot, struct file * fp)
{
  struct ext2_inode* work_inode;
  int inum, err;
  char dname[EXT2_NAME_LEN];
  char* path_ptr, *mmap;
  struct ext2_dir_entry * dentry; 
  struct file *ftemp;
  
  ftemp = (struct file*)kmalloc(sizeof(struct file), GFP_KERNEL);
  *ftemp = *fp;
  if (pathname[0] == '/') 
    work_inode = current->root->f_inode;
  else
    work_inode = current->pwd->f_inode;
  path_ptr = pathname;  
  do {
    path_ptr = path_walk(path_ptr, dname);
    if (!IS_DIR(work_inode)) 
      return -ENOTDIR;
    if (check_access(work_inode))
      return -EACCES;
    if (work_inode == current->root->f_inode && strcmp((char*)dname,"..") == 0)
      continue;
    if (strcmp(dname,"..") == 0 || strcmp(dname,".") == 0)
      continue;
    ftemp->f_inode = work_inode;
    err = ftemp->f_op->mmap (ftemp);
    if (err < 0)
      return err;
    mmap = (char *)ftemp->f_vma->vm_start;
    err = ftemp->f_op->read (ftemp, mmap, ftemp->f_inode->i_size);
    if (err < 0)
      goto bad_namei_cleanup;
    //search dname in dentries
    dentry = (struct ext2_dir_entry *)mmap;
    inum = 0;
    while ((unsigned long)dentry < ((unsigned long)mmap + work_inode->i_size)) {
      if (strncmp (dname, dentry->name, dentry->name_len) == 0) {
        inum = dentry->inode;
        break;
      }
      dentry = (struct ext2_dir_entry *)((char*)dentry + dentry->rec_len);
    }
    kfree(mmap);
    kfree(ftemp->f_vma);
    if (!inum)
      return -ENOENT;
    work_inode = ext2_read_inode (fp->f_hd, inum);
  } while (*path_ptr);
  
  if (!inum)
     return -ENOENT;
  fp->f_inum = inum;
  fp->f_inode = work_inode;
  fp->f_size = work_inode->i_size;
  strncpy (&dname[0], &fp->f_name[0], FILE_NAME_LEN);
  return 0;
bad_namei_cleanup:
  kfree(ftemp);
  kfree(ftemp->f_vma);
  return err;
}
  
  
  
  
  