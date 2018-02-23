#ifndef _FS_H
#define _FS_H

#include <types.h>
#include <file.h>
#include <ide.h>

#define BH_BUSY 0x0000001
#define BH_DATA_VALID 0x0000002

struct buffer_head {
  int b_dev;
  u32   b_block;
  int   b_status;
  char* b_data;  /*ptr to data area*/
  
  struct buffer_head * b_next; /*ptr to next buf on hash queue*/
  struct buffer_head * b_prev;

  struct buffer_head * b_next_free; /*ptr to next buf on freelist*/
  struct buffer_head * b_prev_free; 
};

struct inode {
	int  i_mode;		 /* File mode */
	int  i_uid;	  	/* Owner Uid */
	int  i_size;	 	/* Size in bytes */
	int  i_atime;		/* Access time */
	int  i_ctime;		/* Creation time */
	int  i_mtime;		/* Modification time */
	int  i_dtime;		/* Deletion Time */
	int  i_gid;	  	/* Group Id */
	int  i_links_count;  /* Links count */
	int  i_blocks;   	/* Blocks count !*/
	int  i_flags;		/* File flags */
	
	u32  i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	
	u32  i_version;	   /* File version (for NFS) */
	u32  i_file_acl;	  /* File ACL */
	u32  i_dir_acl;	   /* Directory ACL */
	u32  i_faddr;		 /* Fragment address */
	u8  i_frag;		  /* Fragment number */
	u8  i_fsize;		 /* Fragment size */
	u16 i_pad1;
	u32  i_reserved2[2];
};


/*main.c*/
extern dev_t root_dev;

/*namei.c*/
int namei (char * pathname, int prot, struct file * fp);

/*open.c*/
int sys_open (char * filepath, int mode);
struct file* open_root (int mode);

/*read_write.c*/
int sys_read (int fd, char* buf, int count);
int sys_write (int fd, char* buf, int count);

/*fs.c*/
int do_ls();
int do_cd(char* path);
int do_pwd();



#endif 