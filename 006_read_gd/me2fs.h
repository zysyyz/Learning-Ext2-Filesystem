/*********************************************************************************
	File			: me2fs.h
	Description		: Defines for my ext2 file system

*********************************************************************************/
#ifndef	__ME2FS_H__
#define	__ME2FS_H__

#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <uapi/linux/magic.h>

/*
==================================================================================

	Prototype Statement

==================================================================================
*/

/*
==================================================================================

	DEFINES

==================================================================================
*/
#define	ME2FS_SUPER_MAGIC		EXT2_SUPER_MAGIC		/* 0xEF53				*/

#define	ME2FS_OLD_REV			0
#define	ME2FS_DYNAMIC_REV		1

#define	ME2FS_NDIR_BLOCKS		( 12 )
#define	ME2FS_IND_BLOCK			ME2FS_NDIR_BLOCKS
#define	ME2FS_2IND_BLOCK		( ME2FS_IND_BLOCK + 1 )
#define	ME2FS_3IND_BLOCK		( ME2FS_2IND_BLOCK + 1 )
#define	ME2FS_NR_BLOCKS			( ME2FS_3IND_BLOCK + 1 )

/*
----------------------------------------------------------------------------------
	Special Inode Number
----------------------------------------------------------------------------------
*/
#define	ME2FS_EXT2_BAD_INO		1			/* bad blocks inode					*/
#define	ME2FS_EXT2_ROOT_INO		2
#define	ME2FS_EXT2_BL_INO		5			/* boot loader inode				*/
#define	ME2FS_EXT2_UNDEL_DIR_NO	6			/* undelete directory inode			*/

/*
----------------------------------------------------------------------------------
	Maximal Count of Links to a File
----------------------------------------------------------------------------------
*/
#define	ME2FS_LINK_MAX			32000

/*
---------------------------------------------------------------------------------
	Ext2 Block Group Descriptor
---------------------------------------------------------------------------------
*/
struct ext2_group_desc
{
	__le32	bg_block_bitmap;
	__le32	bg_inode_bitmap;
	__le32	bg_inode_table;
	__le16	bg_free_blocks_count;
	__le16	bg_free_inodes_count;
	__le16	bg_used_dirs_count;
	__le16	bg_pad;
	__le32	bg_reserved[ 3 ];
};

/*
---------------------------------------------------------------------------------
	Ext2 Super Block
---------------------------------------------------------------------------------
*/
struct ext2_super_block
{
	__le32	s_inodes_count;
	__le32	s_blocks_count;
	__le32	s_r_blocks_count;				/* reserved blocks count			*/
	__le32	s_free_blocks_count;
	__le32	s_free_inodes_count;
	__le32	s_first_data_block;
	__le32	s_log_block_size;
	__le32	s_log_frag_size;
	__le32	s_blocks_per_group;
	__le32	s_frags_per_group;
	__le32	s_inodes_per_group;
	__le32	s_mtime;						/* mount time						*/
	__le32	s_wtime;						/* write time						*/
	__le16	s_mnt_count;
	__le16	s_max_mnt_count;
	__le16	s_magic;
	__le16	s_state;						/* file system state				*/
	__le16	s_errors;						/* behaviour when detecting error	*/
	__le16	s_minor_rev_level;				/* minor revision level				*/
	__le32	s_lastcheck;					/* time of last check				*/
	__le32	s_checkinterval;				/* max. time between checks			*/
	__le32	s_creator_os;
	__le16	s_rev_level;					/* revision level					*/
	__le16	s_def_resuid;					/* default uid for reserved blocks	*/
	__le16	s_def_resgid;					/* default gid for reserved blocks	*/
	/* ------------------------------------------------------------------------ */
	/* Dynamic Revision															*/
	/* ------------------------------------------------------------------------ */
	__le32	s_first_ino;					/* first non-reserved inode			*/
	__le16	s_inode_size;					/* size of inode structure			*/
	__le16	s_block_group_nr;				/* block group # of this superblock	*/
	__le32	s_feature_compat;				/* compatible feature set			*/
	__le32	s_feature_incompat;				/* incompatible feature set			*/
	__le32	s_feature_ro_compat;			/* readonly-compatible feature set	*/
	__u8	s_uuid[ 16 ];					/* 128-bit uuid for volume			*/
	char	s_volume_name[ 16 ];			/* volume name						*/
	char	s_last_mounted[ 64 ];			/* directory where last mounted		*/
	__le32	s_algorithm_usage_bitmap;		/* For compression					*/
	/* ------------------------------------------------------------------------ */
	/* Peformance Hints															*/
	/* ------------------------------------------------------------------------ */
	__u8	s_prealloc_blocks;				/* # of blocks to try to preallocate*/
	__u8	s_prealloc_dir_blocks;			/* # of preaalocat for dirs			*/
	__u16	s_padding1;
	/* ------------------------------------------------------------------------ */
	/* Journaling Support														*/
	/* ------------------------------------------------------------------------ */
	__u8	s_journal_uuid[ 16 ];			/* uuid of journal superblock		*/
	__u32	s_journal_inum;					/* inode number of journal file		*/
	__u32	s_journal_dev;					/* device number of journal file	*/
	__u32	s_last_orphan;					/* start of list of inodes to delete*/
	/* ------------------------------------------------------------------------ */
	/* Directory Indexing Support												*/
	/* ------------------------------------------------------------------------ */
	__u32	s_hash_seed[ 4 ];				/* HTREE hash seed					*/
	__u8	s_def_hash_version;				/* default hash version				*/
	__u8	s_reserved_char_pad;
	__u16	s_reserved_word_pad;
	/* ------------------------------------------------------------------------ */
	/* Other options															*/
	/* ------------------------------------------------------------------------ */
	__le32	s_default_mount_opts;
	__le32	s_first_meta_bg;				/* first metablock block group		*/
	__u32	s_reserved[ 190 ];				/* padding to the end				*/

};

/* defines for s_state															*/
#define	EXT2_VALID_FS			( 1 )
#define	EXT2_ERROR_FS			( 2 )

/* defines for s_errors															*/
#define	EXT2_ERRORS_CONTINUE	( 1 )
#define	EXT2_ERRORS_RO			( 2 )
#define	EXT2_ERRORS_PANIC		( 3 )

/* defines for s_creator_os														*/
#define	EXT2_OS_LINUX			( 0 )
#define	EXT2_OS_HURD			( 1 )
#define	EXT2_OS_MASIX			( 2 )
#define	EXT2_OS_FREEBSD			( 3 )
#define	EXT2_OS_LITES			( 4 )

/* defines for s_rev_level														*/
#define	EXT2_GOOD_OLD_REV		( 0 )
#define	EXT2_DYNAMIC_REV		( 1 )

/* defines for s_def_resuid														*/
#define	EXT2_DEF_RESUID			( 0 )

/* defines for s_def_resgid														*/
#define	EXT2_DEF_RESGID			( 0 )

/* defines for s_feature_compat													*/
#define	EXT2_FEATURE_COMPAT_DIR_PREALLOC	( 0x0001 )
#define	EXT2_FEATURE_COMPAT_IMAGC_INODES	( 0x0002 )
#define	EXT2_FEATURE_COMPAT_HAS_JOURNAL		( 0x0004 )
#define	EXT2_FEATURE_COMPAT_EXT_ATTR		( 0x0008 )
#define	EXT2_FEATURE_COMPAT_RESIZE_INO		( 0x0010 )
#define	EXT2_FEATURE_COMPAT_DIR_INDEX		( 0x0020 )

#define	EXT2_FEATURE_COMPAT_SUPP			EXT2_FEATURE_COMPAT_EXT_ATTR

/* defines for s_feature_ro_compat												*/
#define	EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER	( 0x0001 )
#define	EXT2_FEATURE_RO_COMPAT_LARGE_FILE	( 0x0002 )
#define	EXT2_FEATURE_RO_COMPAT_BTREE_DIR	( 0x0004 )
#define	EXT2_FEATURE_RO_COMPAT_ANY			( 0xFFFFFFFF )

#define	EXT2_FEATURE_RO_COMPAT_SUPP	( EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER	|	\
									  EXT2_FEATURE_RO_COMPAT_LARGE_FILE		|	\
									  EXT2_FEATURE_RO_COMPAT_BTREE_DIR )
#define	EXT2_FEATURE_RO_COMPAT_UNSUPPORTED	~EXT2_FEATURE_RO_COMPAT_SUPP

/* defines for s_feature_incompat												*/
#define	EXT2_FEATURE_INCOMPAT_COMPRESSION	( 0x0001 )
#define	EXT2_FEATURE_INCOMPAT_FILETYPE		( 0x0002 )
#define	EXT2_FEATURE_INCOMPAT_RECOVER		( 0x0004 )
#define	EXT2_FEATURE_INCOMPAT_JOURNAL_DEV	( 0x0008 )
#define	EXT2_FEATURE_INCOMPAT_META_BG		( 0x0010 )

#define	EXT2_FEATURE_INCOMPAT_SUPP		( EXT2_FEATURE_INCOMPAT_FILETYPE	|	\
										  EXT2_FEATURE_INCOMPAT_META_BG )
#define	EXT2_FEATURE_INCOMPAT_UNSUPPORTED	~EXT2_FEATURE_INCOMPAT_SUPP

/* defines for s_default_mount_opts and s_mount_opts							*/
#define	EXT2_MOUNT_CHECK					( 0x00000001 )
#define	EXT2_MOUNT_OLDALLOC					( 0x00000002 )
#define	EXT2_MOUNT_GRPID					( 0x00000004 )
#define	EXT2_MOUNT_DEBUG					( 0x00000008 )
#define	EXT2_MOUNT_ERRORS_CONT				( 0x00000010 )
#define	EXT2_MOUNT_ERRORS_RO				( 0x00000020 )
#define	EXT2_MOUNT_ERRORS_PANIC				( 0x00000040 )
#define	EXT2_MOUNT_MINIX_DF					( 0x00000080 )
#define	EXT2_MOUNT_NOBH						( 0x00000100 )
#define	EXT2_MOUNT_NO_UID32					( 0x00000200 )
#define	EXT2_MOUNT_XATTR_USER				( 0x00004000 )
#define	EXT2_MOUNT_POSIX_ACL				( 0x00008000 )
#define	EXT2_MOUNT_XIP						( 0x00010000 )
#define	EXT2_MOUNT_USRQUOTA					( 0x00020000 )
#define	EXT2_MOUNT_GRPQUOTA					( 0x00040000 )
#define	EXT2_MOUNT_RESERVATION				( 0x00080000 )

/*
---------------------------------------------------------------------------------
	Me2fs(Ext2) Super Block Information
---------------------------------------------------------------------------------
*/
struct me2fs_sb_info
{
	/* ------------------------------------------------------------------------ */
	/* buffer cache information													*/
	/* ------------------------------------------------------------------------ */
	struct ext2_super_block		*s_esb;
	struct buffer_head			*s_sbh;
	struct buffer_head			**s_group_desc;
	/* ------------------------------------------------------------------------ */
	/* disk informaiont cache													*/
	/* ------------------------------------------------------------------------ */
	/* super block																*/
	unsigned long				s_sb_block;
	unsigned long				s_mount_opt;
	unsigned short				s_mount_state;
	/* inode																	*/
	unsigned short				s_inode_size;
	unsigned int				s_first_ino;
	unsigned long				s_inodes_per_group;
	unsigned long				s_inodes_per_block;
	unsigned long				s_itb_per_group;
	/* group																	*/
	unsigned long				s_groups_count;
	unsigned long				s_blocks_per_group;
	unsigned long				s_desc_per_block;	/* # of group desc per block*/
	unsigned long				s_gdb_count;		/* # of group desc blocks	*/
	/* fragment																	*/
	unsigned long				s_frag_size;
	unsigned long				s_frags_per_block;
	unsigned long				s_frags_per_group;
	/* defaults																	*/
	kuid_t						s_resuid;
	kgid_t						s_resgid;
};

/*
==================================================================================

	Management

==================================================================================
*/
/*
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	Function	:ME2FS_SB
	Input		:struct super_block *sb
				 < vfs super block >
	Output		:void
	Return		:struct me2fs_inode_info *
				 < me2fs inode information

	Description	:get me2fs_sb_info from vfs super block
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*/
static inline struct me2fs_sb_info *ME2FS_SB( struct super_block *sb )
{
	return( ( struct me2fs_sb_info* )sb->s_fs_info );
}

/*
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
	Function	:ext2GetFirstBlockNum
	Input		:struct super_block *sb
				 < vfs super block >
				 unsined long group_no
				 < group number to get its first block >
	Output		:void
	Return		:unsigned long
				 < first block number >

	Description	:get first block number of the group
_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
*/
static inline unsigned long
ext2GetFirstBlockNum( struct super_block *sb, unsigned long group_no )
{
	unsigned long	first_block_num;

	first_block_num = group_no * le32_to_cpu( ME2FS_SB( sb )->s_blocks_per_group )
					  + le32_to_cpu( ME2FS_SB( sb )->s_esb->s_first_data_block );
	
	return( first_block_num );
}

/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	< Open Functions >

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
#endif	// __ME2FS_H__
