
#include <mm.h>
#include <errno.h>
#include <file.h>

int generic_mmap (struct file *fp)
{
  vm_area_t *vma;
  
  vma = (vm_area_t *)kmalloc(sizeof(vm_area_t), GFP_KERNEL);
  if (!vma)
    return -ENOMEM;
  vma->vm_start = (unsigned long) kmalloc(fp->f_inode->i_size, GFP_KERNEL);
  if (!vma->vm_start) {
    kfree(vma);
    return -ENOMEM;
  }
  vma->vm_end = vma->vm_start + fp->f_inode->i_size;
  fp->f_vma = vma;
  return 0;
}