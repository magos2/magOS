#ifndef _EXT2_H
#define _EXT2_H

/* Docs :
 *   http://e2fsprogs.sourceforge.net/ext2.html
 *   http://www.nongnu.org/ext2-doc/ext2.html
 *   http://wiki.osdev.org/Ext2
 *   http://uranus.chrysocome.net/explore2fs/es2fs.htm
 *   http://perl.plover.com/classes/ext2fs/
 * Disk Organization: Sample 20mb Partition Layout
	Block Offset   Length		Description
	-- block #0 : 1024 bytes, boot block--
    byte 0		 512 bytes	 boot record (if present)
    byte 512	   512 bytes	 additional boot record data (if present)
    -- block group 0, blocks 1 to 8192 --
    byte 1024	  1024 bytes	superblock
    block 2		1 block	   block group descriptor table
    block 3		1 block	   block bitmap
    block 4		1 block	   inode bitmap
    block 5		214 blocks	inode table
    block 219	  7974 blocks   data blocks
    -- block group 1, blocks 8193 to 16384 --
    block 8193	 1 block   	superblock backup
    block 8194	 1 block	   block group descriptor table backup
    block 8195	 1 block	   block bitmap
    block 8196	 1 block	   inode bitmap
    block 8197	 214 blocks    inode table
    block 8408	 7974 blocks   data blocks
    -- block group 2, blocks 16385 to 24576 --
    block 16385	1 block	    block bitmap
    block 16386	1 block	    inode bitmap
    block 16387	214 blocks	 inode table
    block 16601	3879 blocks	data blocks
 *
 * Indirect block : Example: with a 512-byte block size, and 4-byte block pointers, 
                    each indirect block can consist of 128 (512 / 4) pointers.
 */
#include <types.h>

#define EXT2_MAGIC 0xEF53

/*
 * Superblock est un block de 1ko et qui commence à l'octet 1024.
 */
struct ext2_super_block {
	u32  s_inodes_count;	 /* Inodes count */
	u32  s_blocks_count;	 /* Blocks count */
	u32  s_r_blocks_count;   /* Reserved blocks count */
	u32  s_free_blocks_count;/* Free blocks count */
	u32  s_free_inodes_count;/* Free inodes count */
	u32  s_first_data_block; /* First Data Block */
	u32  s_log_block_size;   /* 0=1k block size. 1=2k, 2=4k*/
	long s_log_frag_size;	/* Fragment size */
	u32  s_blocks_per_group; /* # Blocks per group */
	u32  s_frags_per_group;  /* # Fragments per group */
	u32  s_inodes_per_group; /* # Inodes per group */
	u32  s_mtime;	    	/* Mount time */
	u32  s_wtime;		    /* Write time */
	u16 s_mnt_count;	     /* Mount count */
	short  s_max_mnt_count;  /* Maximal mount count */
	u16  s_magic;		    /* Magic signature */
	u16  s_state;		    /* File system state */
	u16  s_errors;	       /* Behaviour when detecting errors */
	u16  s_pad;
	u32  s_lastcheck;	    /* time of last check */
	u32  s_checkinterval;	/* max. time between checks */
	u32  s_padding[238];	 /* Padding to the end of the block */
} __attribute__ ((packed));

/*The Group Descriptors table contains information on the block groups. This data is covers all the groups and is stored in all the groups for redundancy.
 *it is a table of block group.
 * each bitmap must be stored on a single block. so a block of 1k can store a bitmap mapping the states of
 * 8192 blocks. a 4k block, 32.768 blocks.
*/
struct ext2_group_desc {
	u32  bg_block_bitmap;	 	/* The address of the block containing the block bitmap for this group */
	u32  bg_inode_bitmap;		 /* The address of the block containing the inode bitmap for this group */
	u32  bg_inode_table;		  /* Inodes table block : this hold the first block storing inode table*/
	u16  bg_free_blocks_count;	/* Free blocks count */
	u16  bg_free_inodes_count;	/* Free inodes count */
	u16  bg_used_dirs_count;  	/* Directories count */
	u16  bg_pad;
	u32  bg_reserved[3];
} __attribute__ ((packed));


/*
 * Constants relative to the data blocks
 */
#define	EXT2_NDIR_BLOCKS		12
#define	EXT2_IND_BLOCK		  EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK		 (EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK		 (EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS	   	(EXT2_TIND_BLOCK + 1)

#define EXT2_BAD_INO         1  /*Bad blocks inode*/
#define EXT2_ROOT_INO        2  /*Root inode*/
#define EXT2_ACL_IDX_INO     3  /*ACL inode*/
#define EXT2_ACL_DATA_INO	4  /*ACL inode*/
#define EXT2_BOOT_LOADER_INO 5  /*Boot loader inode*/
#define EXT2_UNDEL_DIR_INO   6  /*Undelete directory inode*/
#define EXT2_FIRST_INO       11 /*First non reserved inode*/

/*
 * Structure of an inode on the disk. All inodes are 128 bytes long. so 1k block holds 8 inodes.
 * 4k block, 32 inodes. 
 * size of inode table = s_inodes_per_group/(nb of inodes per block).
 */
struct ext2_inode {
	u16  i_mode;		 /* File mode */
	u16  i_uid;	  	/* Owner Uid */
	u32  i_size;	 	/* Size in bytes */
	u32  i_atime;		/* Access time */
	u32  i_ctime;		/* Creation time */
	u32  i_mtime;		/* Modification time */
	u32  i_dtime;		/* Deletion Time */
	u16  i_gid;	  	/* Group Id */
	u16  i_links_count;  /* Links count */
	u32  i_blocks;   	/* Blocks count !*/
	u32  i_flags;		/* File flags */
	u32  i_reserved1;
	
    /* 
	 * [0] -> [11] : block number (32 bits per block)
	 * [12]        : indirect block number
	 * [13]        : bi-indirect block number
	 * [14]        : tri-indirect block number
	 */
	u32  i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	
	u32  i_version;	   /* File version (for NFS) */
	u32  i_file_acl;	  /* File ACL */
	u32  i_dir_acl;	   /* Directory ACL */
	u32  i_faddr;		 /* Fragment address */
	u8  i_frag;		  /* Fragment number */
	u8  i_fsize;		 /* Fragment size */
	u16 i_pad1;
	u32  i_reserved2[2];
} __attribute__ ((packed));

#define IS_DIR(inode)  (inode->i_mode & EXT2_S_IFDIR)


/*
 * Structure of a directory entry
 */
#define EXT2_NAME_LEN 255

struct ext2_dir_entry {
	u32 inode;			     /* Inode number */
	u16 rec_len;			   /* Directory entry length */
	u16 name_len;		      /* Name length */
	char           name[EXT2_NAME_LEN];   /* File name */
} __attribute__ ((packed));

struct disk {
	dev_t dev;
	struct partition *part;
	struct ext2_super_block *sb;
	u32 blocksize;
	u16 groups;		/* Total number of groups */
	struct ext2_group_desc *gd; 
} __attribute__ ((packed));

/* inode: i_mode */
#define	EXT2_S_IFMT	0xF000	/* format mask  */
#define	EXT2_S_IFSOCK	0xC000	/* socket */
#define	EXT2_S_IFLNK	0xA000	/* symbolic link */
#define	EXT2_S_IFREG	0x8000	/* regular file */
#define	EXT2_S_IFBLK	0x6000	/* block device */
#define	EXT2_S_IFDIR	0x4000	/* directory */
#define	EXT2_S_IFCHR	0x2000	/* character device */
#define	EXT2_S_IFIFO	0x1000	/* fifo */

#define	EXT2_S_ISUID	0x0800	/* SUID */
#define	EXT2_S_ISGID	0x0400	/* SGID */
#define	EXT2_S_ISVTX	0x0200	/* sticky bit */
#define	EXT2_S_IRWXU	0x01C0	/* user access rights mask */
#define	EXT2_S_IRUSR	0x0100	/* read */
#define	EXT2_S_IWUSR	0x0080	/* write */
#define	EXT2_S_IXUSR	0x0040	/* execute */
#define	EXT2_S_IRWXG	0x0038	/* group access rights mask */
#define	EXT2_S_IRGRP	0x0020	/* read */
#define	EXT2_S_IWGRP	0x0010	/* write */
#define	EXT2_S_IXGRP	0x0008	/* execute */
#define	EXT2_S_IRWXO	0x0007	/* others access rights mask */
#define	EXT2_S_IROTH	0x0004	/* read */
#define	EXT2_S_IWOTH	0x0002	/* write */
#define	EXT2_S_IXOTH	0x0001	/* execute */

void ext2_ide_read (struct disk *hd, unsigned long numblock, int size, char* buf);
struct disk *ext2_read_disk_info(dev_t dev);
void ext2_display_disk_info (struct disk *hd);
int ext2_check_disk (struct disk *hd);
int ext2_read_sb (struct disk *hd, struct ext2_super_block* sb);
//struct ext2_super_block *ext2_read_sb(struct disk *hd, int s_part);
//struct ext2_group_desc *ext2_read_gd(struct disk *hd, int s_part);

struct ext2_inode* ext2_read_inode(struct disk *hd, int inum);
struct ext2_inode* ext2_read_root_inode (struct disk *hd);


#endif

