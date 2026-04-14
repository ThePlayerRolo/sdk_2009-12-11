#ifndef RVL_SDK_ARC_H
#define RVL_SDK_ARC_H

/*******************************************************************************
 * headers
 */

#include <revolution/types.h>

/*******************************************************************************
 * macros
 */

#define ARC_ENTRY_NUM_INVALID   (-1)

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

typedef s32 ARCEntryNum;

// [SPQE7T]/ISpyD.elf:.debug_info::0x119a90
typedef struct ARCHandle
{
	void		*archiveStartAddr;	// size 0x04, offset 0x00
	void		*FSTStart;			// size 0x04, offset 0x04
	void		*fileStart;			// size 0x04, offset 0x08
	u32			entryNum;			// size 0x04, offset 0x0c // more accurately entryCount
	const char	*FSTStringStart;	// size 0x04, offset 0x10
	u32			FSTLength;			// size 0x04, offset 0x14
	u32			currDir;			// size 0x04, offset 0x18 // more accurately what ARCDir calls entryNum
} ARCHandle; // size 0x1c

// [SPQE7T]/ISpyD.elf:.debug_info::0x368e0b
typedef struct ARCFileInfo
{
	ARCHandle	*handle;		// size 0x04, offset 0x00
	u32			startOffset;	// size 0x04, offset 0x04
	u32			length;			// size 0x04, offset 0x08
} ARCFileInfo; // size 0x0c

// [SPQE7T]/ISpyD.elf:.debug_info::0x3749e4
typedef struct ARCDir
{
	ARCHandle	*handle;	// size 0x04, offset 0x00
	u32			entryNum;	// size 0x04, offset 0x04
	u32			location;	// size 0x04, offset 0x08
	u32			next;		// size 0x04, offset 0x0c
} ARCDir; // size 0x10

// [SPQE7T]/ISpyD.elf:.debug_info::0x374a3e
typedef struct ARCDirEntry
{
	ARCHandle	*handle;	// size 0x04, offset 0x00
	u32			entryNum;	// size 0x04, offset 0x04
	BOOL		isDir;		// size 0x04, offset 0x08
	const char	*name;		// size 0x04, offset 0x0c
} ARCDirEntry; // size 0x10

/*******************************************************************************
 * functions
 */

BOOL ARCInitHandle(void *bin, ARCHandle *handle);
BOOL ARCOpen(ARCHandle *handle, const char *filename, ARCFileInfo *af);
BOOL ARCFastOpen(ARCHandle *handle, s32 entrynum, ARCFileInfo *af);
s32 ARCConvertPathToEntrynum(ARCHandle *handle, const char *path);
void *ARCGetStartAddrInMem(ARCFileInfo *af);
u32 ARCGetLength(ARCFileInfo *af);
BOOL ARCClose(ARCFileInfo *af);
BOOL ARCChangeDir(ARCHandle *handle, const char *dirname);
BOOL ARCOpenDir(ARCHandle *handle, const char *dirname, ARCDir *dir);
BOOL ARCReadDir(ARCDir *dir, ARCDirEntry *direntry);
BOOL ARCCloseDir(ARCDir *dir);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_DARCH_H
