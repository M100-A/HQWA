//
// common.h
//
// Common header file, where I dump system wide configuration things, such as include files, and my own generic definitions and functions.
//

//
// Given that I tend to write "semi-portable" code, there is a lot of ifdef WIN32 stuff in here..
//
// Unless I test for the platform, there is no gurantee that it will work..
//

#ifdef WIN32

#include	<curses.h>
#include	<stdio.h>		// for sprintf
#include	<stdlib.h>
#include	<fcntl.h>
#include	<io.h>
#include	<math.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<string.h>		// for strlen
#include	<memory.h>		// for malloc
#include	<time.h>		// for localtime
#include	<ctype.h>		// for islower, isupper
//#include	<signal.h>

#define PURE_WINDOWS_VERSION  1

#ifdef PURE_WINDOWS_VERSION
#undef MOUSE_MOVED
#include <windows.h>
#endif

#else //WIN32

#ifdef HAVE_CONFIG_H
#include	<config.h>
#endif

#include    <ncurses.h>     // for the *NIX curses library
#include	<stdio.h>
#include	<stdarg.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<math.h>
#include	<ctype.h>
#include	<string.h>		// for strlen
#include	<memory.h>		// for malloc
#include	<time.h>		// for localtime
//#include	<signal.h>		// for signal stuff
#include	<poll.h>		// for poll (used to simulate sleep()).
#include	<dirent.h>
#include    <ncurses.h>     // for the *NIX curses library

#endif //WIN32


#ifdef WIN32

//----------------------------------------------------------------------
//
// Windows port over stuff.
//

#define PERM_FILE (_S_IREAD | _S_IWRITE)

#define VOID void
#define BOOL int
#define HANDLE int

#define TRUE 1
#define FALSE 0
#define unlink _unlink

#else

//----------------------------------------------------------------------
//
// *nix port over stuff.
//

#define VOID void
#define BOOL int
#define HANDLE int
#define _open open
#define _close close
#define _O_RDONLY O_RDONLY
#define _O_WRONLY O_WRONLY
#define _O_CREAT O_CREAT
#define _O_APPEND O_APPEND
#define _O_TRUNC O_TRUNC
#define _O_EXCL O_EXCL
#define _O_BINARY 0
#define _O_RSYNC O_RSYNC
#define _fstat fstat
#define _stat stat
#define _read read
#define _lseek lseek
#define _write write
#define _unlink unlink
#define _getpid getpid
#define stricmp strcasecmp
#define TRUE 1
#define FALSE 0

#define PERM_FILE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

#endif // WIN32


//----------------------------------------------------------------------
//
// defines for file utils..
//

// definition for buffered file I/O structure
struct	futils_filebuff
{
                    // pointer to the buffer
	char	        *pcData;
                    // size of allocated buffer
	unsigned long	ulBufferSize;
                    // position in the buffer
	unsigned long	ulBufferPos;
                    // amount of data currently in buffer
	unsigned long	ulBufferMax;

	unsigned long   ulFileTotSpc;
                    // set if there is a memory buffer allocated !
	BOOL			bMemFlag;
};

// replacement for strnicmp
int futils_strnicmp (char *pszStr1, char *pszStr2, size_t iLength);

// generic sleep function
void futils_sleep (int iTimeout);

// preallocate the memory image
int futils_preAllocateBuffer (unsigned long ulBufferSize, struct futils_filebuff *pstructFullFile);

// load text file into memory image
int futils_loadFileIntoMemory (char *pszFileName, struct futils_filebuff *pstructFullFile);

// read a single line from a file
int futils_readLineFromMemoryNoEndLineCombo (struct futils_filebuff *pstructFullFile, char *pszBuf, unsigned long ulMaxlen);

// wipe the memory buffer for output buffering
int futils_wipeFileBuffer (struct futils_filebuff *pstructFullFile);

// append a string to the memory output buffer
int futils_addStringToFileBufferEnd (char *pszBuf, struct futils_filebuff *pstructFullFile);

// appends a log entry to a file
void futils_writeFileHeaderAndData (char *pszFileName, char *pszHeader, char *pszData);


//----------------------------------------------------------------------
//
// defines for memory utils..
//

// definition for the temporary command struct
struct  mutils_commandlist
{
    char    cUseFlag;       // in use flag
    char    *pszCommand;    // command string
    int     iCommandSize;   // size of the command string
    int     iSceneId;       // scene id this entry corresponds to
    int     iSubSceneId;    // sub-scene id for this entry
};

// initialize the command list storage
int mutils_initAndClearCommandList ();

// add a command to the list storage
int mutils_addToCommandList (char *pszCommand, int iSceneId, int iSubSceneId);

// initialize and clear the dialog buffer storage
int mutils_initAndClearDialogBuffer ();

// suffix dialog into the dialog buffer
int mutils_addToDialogBuffer (char *pszString);

// migrate dialog to archive, and clear the dialog buffer
void mutils_addDialogToArchive (int iEndSubtract);

// calculate the row start offset based upon the archive data
int mutils_calcRowStartOffset (int iScrWidth);

// calculate the number of rows of the dialog buffer
int mutils_calcDialogRows (int iScrWidth);


//----------------------------------------------------------------------
//
// defines for savescreen functions..
//

// initialize the savescreen command list storage
int savescreen_initAndClearCommandList ();

// add a command to the savescreen list storage
int savescreen_addToCommandList (char *pszCommand, int iSceneId, int iSubSceneId);

// initialize and clear the savescreen dialog buffer storage
int savescreen_initAndClearDialogBuffer ();

// suffix dialog into the savescreen dialog buffer
int savescreen_addToDialogBuffer (char *pszString);

// calculate the number of rows of the savescreen dialog buffer
int savescreen_calcDialogRows (int iScrWidth);

// create and display the save screen
int savescreen_playerInteract ();

// function to parse a save file (for display on the load or save dialog screens)
int savescreen_parseSaveFile (int iSaveId, char *pszDateTime);

// function to load a save file
int savescreen_loadSaveFile (int iSaveId);

