//
// savescreen.c
//
// some memory utilities for the program.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"
#include "mapdata.h"

//
// global variables for the command list.
//

char    gcSaveScrListAlloc = FALSE;
struct  mutils_commandlist  *gstruct_SaveScrList;
int     giSaveScrListSize;
int     giSaveScrListUsed;

//
// Function to clear (and also init, if used for the first time), the command list.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int savescreen_initAndClearCommandList ()
{
    int iOffset;

    //
    // If memory is uninitialized, allocate and initialize it..
    //
    if (gcSaveScrListAlloc == FALSE)
    {
        // Note: the parameters have been adjusted to not be as big for the limited size of the save screen data.
        giSaveScrListSize = 12;

        gstruct_SaveScrList = (struct mutils_commandlist *)malloc ((size_t)sizeof (struct mutils_commandlist) * (size_t)((size_t)giSaveScrListSize + (size_t)1));

        if (gstruct_SaveScrList == NULL)
            return 1;

        gcSaveScrListAlloc = TRUE;

        for (iOffset = 0; iOffset < giSaveScrListSize; iOffset++)
        {
            gstruct_SaveScrList[iOffset].cUseFlag = 0;
            gstruct_SaveScrList[iOffset].iCommandSize = 62;
            gstruct_SaveScrList[iOffset].iSceneId = -1;
            gstruct_SaveScrList[iOffset].iSubSceneId = -1;

            gstruct_SaveScrList[iOffset].pszCommand = (char *)malloc ((size_t)(gstruct_SaveScrList[iOffset].iCommandSize + 2));

            if (gstruct_SaveScrList[iOffset].pszCommand == NULL)
                return 1;

            gstruct_SaveScrList[iOffset].pszCommand[0] = 0;
        }

        giSaveScrListUsed = 0;
    }
    //
    // Otherwise.. this is a VERY simple clean of what we have..
    //
    else
    {
        for (iOffset = 0; iOffset < giSaveScrListUsed; iOffset++)
        {
            gstruct_SaveScrList[iOffset].cUseFlag = 0;
            gstruct_SaveScrList[iOffset].pszCommand[0] = 0;
            gstruct_SaveScrList[iOffset].iSceneId = -1;
            gstruct_SaveScrList[iOffset].iSubSceneId = -1;
        }

        giSaveScrListUsed = 0;
    }

    return 0;
}

//
// function to add an entry to the command list (which sorts the entry into the list)
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int savescreen_addToCommandList (char *pszCommand, int iSceneId, int iSubSceneId)
{
    int iLen;
    int iOffset;
//    int iRevOffset;
//    char *pszTemp1;
//    int iTemp1;

    iLen = strlen (pszCommand);

    // if the list is currently empty, just load in this entry at the top.
    if (giSaveScrListUsed == 0)
    {
        iOffset = 0;
    }
    else
    {
        // we must have an existing entry already.. so.. just append to the end (save list processing is simpler)

        // first, check to see if we are "expanding" the list..
        if (giSaveScrListUsed >= giSaveScrListSize)
        {
            int iNewSize;
            int iOldSize;
            struct  mutils_commandlist *structMemData;

            iOldSize = giSaveScrListSize;
            iNewSize = giSaveScrListSize + 20;

            while (iNewSize % 64)
                iNewSize++;

            structMemData = (struct mutils_commandlist *)realloc ((VOID *)gstruct_SaveScrList, (size_t)sizeof (struct  mutils_commandlist) * (size_t)((size_t)iNewSize + (size_t)1));

            if (structMemData == NULL)
            {
                return 1;
            }

            // move in the new offset and size..
            gstruct_SaveScrList = structMemData;
            giSaveScrListSize = iNewSize;

            // then init up the data..
            for (iOffset = iOldSize; iOffset < giSaveScrListSize; iOffset++)
            {
                gstruct_SaveScrList[iOffset].cUseFlag = 0;
                gstruct_SaveScrList[iOffset].iCommandSize = 62;
                gstruct_SaveScrList[iOffset].iSceneId = -1;
                gstruct_SaveScrList[iOffset].iSubSceneId = -1;

                gstruct_SaveScrList[iOffset].pszCommand = (char *)malloc ((size_t)(gstruct_SaveScrList[iOffset].iCommandSize + 2));

                if (gstruct_SaveScrList[iOffset].pszCommand == NULL)
                    return 1;

                gstruct_SaveScrList[iOffset].pszCommand[0] = 0;
            }

            // I do the expansion here, so it is less of a problem later..
        }

        // don't bother with the sort code.. just insert it at the end.
        iOffset = giSaveScrListUsed;
    }

    // it does not matter if it this is an appendage, insert or a new.. the code is the same..

    // check to see if the amount of memory allocated for the command string is enough..
    if (iLen > gstruct_SaveScrList[iOffset].iCommandSize)
    {
        int iNewSize;
        char *pcMemData;

        iNewSize = iLen + 20;

        while (iNewSize % 64)
            iNewSize++;
        iNewSize -= 2;

        pcMemData = (char *)realloc ((VOID *)gstruct_SaveScrList[iOffset].pszCommand,
                                      (size_t)(iNewSize + 2));

        if (pcMemData == NULL)
        {
            return 1;
        }

        // It is VERY bad to bail from here.. because it means that data can be lost when it is an insert..
        // the reason is obvious.. we have already moved the tail entry where it is outside of the bounds of giCommandListUsed..

        gstruct_SaveScrList[iOffset].pszCommand = pcMemData;
        gstruct_SaveScrList[iOffset].iCommandSize = iNewSize;
    }

    // copy in the data..
    strcpy (gstruct_SaveScrList[iOffset].pszCommand, pszCommand);
    gstruct_SaveScrList[iOffset].iSceneId = iSceneId;
    gstruct_SaveScrList[iOffset].iSubSceneId = iSubSceneId;
    gstruct_SaveScrList[iOffset].cUseFlag = 1;
    giSaveScrListUsed++;

    return 0;
}


//
// global variables for the "SaveScr" dialog buffer.
//

char    gcSaveScrBufferAlloc = FALSE;
char    *gpszSaveScrBuffer;
int     giSaveScrBufferSize;
int     giSaveScrBufferUsed;

//
// Function to clear (and also init, if used for the first time), the "SaveScr" dialog buffer allocation.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int savescreen_initAndClearDialogBuffer ()
{
    int iOffset;

    if (gcSaveScrBufferAlloc == FALSE)
    {
        giSaveScrBufferSize = 2046;

        gpszSaveScrBuffer = (char *)malloc ((size_t)(giSaveScrBufferSize + 2));

        if (gpszSaveScrBuffer == NULL)
            return 1;

        gcSaveScrBufferAlloc = TRUE;

        // the idea is I set the amount used to the buffer allocation, then the below for loop initialize the entire buffer, and reset it.
        giSaveScrBufferUsed = 2047;
        // this isn't really necessary..
    }

    for (iOffset = 0; iOffset < giSaveScrBufferUsed; iOffset++)
    {
        gpszSaveScrBuffer[iOffset] = 0;
    }

    giSaveScrBufferUsed = 0;

    return 0;
}

//
// function to add dialog onto the end of the "SaveScr" memory buffer..
//  .. while making sure that the dialog string can fit..
//  .. and to expand the buffer if necessary.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int savescreen_addToDialogBuffer (char *pszString)
{
    int iStrLen = strlen (pszString);
    int iCalcLen = iStrLen + giSaveScrBufferUsed;

    // if the calcuated length exceeds what we have for a memory allocation..
    if (iCalcLen > giSaveScrBufferSize)
    {
        // .. then it is time to increase the memory buffer allocation.
        int iNewSize = iCalcLen + 100;
        char *pcMemData;
        int iOffset;

        // round up..
        while (iNewSize % 2048)
            iNewSize++;

        // decrement by 2 (it is added in by the realloc)..
        iNewSize -= 2;

        // now for the realloc..
        pcMemData = (char *)realloc ((VOID *)gpszSaveScrBuffer, (size_t)(iNewSize + 2));

        if (pcMemData == NULL)
            return 1;

        // Note: realloc keeps the data that was originally allocated intact (so I have heard)..
        //  however, the expanded memory area can have random crap in it (assuming that the OS
        //  isn't clearing memory as a security measure).. for safety sake.. I am going to
        //  zero out that memory..

        // then init the expanded memory area..
        for (iOffset = giSaveScrBufferSize; iOffset < iNewSize; iOffset++)
        {
            pcMemData[iOffset] = 0;
        }

        // Now to save aside the references..
        gpszSaveScrBuffer = pcMemData;
        giSaveScrBufferSize = iNewSize;
    }

    // if we needed to expand the memory to store this new piece of dialog.. it would have been done in the above..

    // so just copy in the string..
    strcpy (&gpszSaveScrBuffer[giSaveScrBufferUsed], pszString);
    // Note: it is not necessary to make sure that the string is capped, because strcpy above would have copied across the null terminator as well.
    // gpszDialogBuffer[iCalcLen] = 0;

    giSaveScrBufferUsed = iCalcLen;

    return 0;
}

//
// function to figure out the number of rows in the "SaveScr" dialog buffer.
//
// Returns:
// line offset.
//
int savescreen_calcDialogRows (int iScrWidth)
{
    char    *pszBase = gpszSaveScrBuffer;
    int     iRows = 0;
    int     iOffset;
    int     iSpaceOffset;

    while (1)
    {
        while (1)
        {
            if (pszBase[0] != ' ')
                break;

            pszBase++;
        }

        iOffset = 0;
        iSpaceOffset = -1;

        // first pass, find if this is a null or CR char..
        while (1)
        {
            if (pszBase[iOffset] == '\n')
                break;
            if (pszBase[iOffset] == 0)
                break;
            if (iOffset >= iScrWidth)
                break;
            if (pszBase[iOffset] == ' ')
                iSpaceOffset = iOffset;

            iOffset++;
        }

        // if the line is blank.. skip it..
        if (iOffset == 0)
        {
            // if this is the end.. break..
            if (pszBase[iOffset] == 0)
            {
                break;
            }

            pszBase++;

            iRows++;
            continue;
        }

        // if this is the end.. print the output, and then break..
        if (pszBase[iOffset] == 0)
        {
            break;
        }

        // if this is a newline.
        if (pszBase[iOffset] == '\n')
        {
            pszBase += (iOffset + 1);

            iRows++;
            continue;
        }

        // to have reached this point, there are no newlines, and we are in the middle of the string..

        // if we did not find a space character
        if (iSpaceOffset == -1)
        {
            pszBase += iOffset;

            iRows++;
            continue;
        }

        // otherwise.. we do have a space character..
        pszBase += (iSpaceOffset + 1);

        // increment the row offset..
        iRows++;
    }

    return (iRows);
}


// linkage to the file load structure..
extern  struct	futils_filebuff         gstruct_FileBuff;

// linkage to the global variable for defining that tab mode is the default mode
extern  char    gcTabDefault;

// linkage to the actionstate data.
extern  struct  actionstate_invdescription gstructInventoryDescription[];
extern  struct  actionstate_inventory *gpstructActStateInventory;
extern  short   gsActStateInventorySize;
extern  struct  actionstate_charstats gstructActStateCharWilda;
extern  struct  actionstate_charstats gstructActStateCharCrystal;
extern  struct  actionstate_opponentstats gstructActStateOpponent;
extern  struct  actionstate_globalvars gstructActStateGlobal;

// linkage to the mapdata.
extern  char    gszMapName[];
extern  struct  mapdata_posdatadynamic *gpstructMapPosDynamicCurrent;
extern  short   gsMapPosStaticCurrentSize;
extern  struct  mapdata_linkdatadynamic *gpstructMapLinkDynamicCurrent;
extern  short   gsMapLinkDynamicCurrentSize;

// linkage to the mutils data.
extern  struct  mutils_commandlist  *gstruct_CommandList;
extern  int     giCommandListUsed;
extern  char    *gpszDialogBuffer;
extern  int     giDialogBufferUsed;
extern  int     giDialogBufferSize;
extern  char    *gpszArchiveBuffer;
extern  int     giArchiveBufferUsed;

//
// function to handle the keyboard input for the player for the savescreen.
//
int savescreen_playerInteract ()
{
    int     iKey;
    char    *pszBase;
    int     iRowOut;
    int     iRowStart;
    int     iRowOffset;
    int     iScrHeight;
    int     iScrWidth;
    int     iSpaceOffset;
    char    cFullScreenFlag;
    char    cClearScreenFlag;
    char    cRememberEditFlag;
    char    szInputString[900];
    char    szWorkString[410];
    int     iOffset;
    int     iEndOffset;
    int     iEditRow;
    int     iPosition;
    int     iPosWinEnd;
    char    cKeyMode;
    char    cEnterAction;
    int     iCommands;
    int     iCommandOffset;
    char    *pszCommand;
    int     iCount;
    int     iLen;
    int     iLen2;

    int     iSceneId;
    int     iSubSceneId;
    int     iRet;

    // init data.. (main menu)
    iSceneId = 0;
    iSubSceneId = 0;

    // reset the command list for the savescreen
    savescreen_initAndClearCommandList ();

    // reset the dialog buffer for the savescreen as well
    savescreen_initAndClearDialogBuffer ();

    // somewhere in here, the dialog and the menu items for the save screen is populated.

    iRet = savescreen_addToDialogBuffer ("]Save current game[\n\n");
    if (iRet != 0) return iRet;

    for (iOffset = 0; iOffset < 9; iOffset++)
    {
        char    szDateTime[300];

        szDateTime[0] = 0;

        iRet = savescreen_parseSaveFile (iOffset + 1, szDateTime);

        if (iRet == 1)
        {
            sprintf (szInputString, "Slot %d is invalid (%s) !\n", iOffset + 1, szDateTime);
        }
        else if (iRet == 0)
        {
            sprintf (szInputString, "Slot %d was saved: %s\n", iOffset + 1, szDateTime);
        }
        else // iRet == 2
        {
            sprintf (szInputString, "Slot %d is empty.\n", iOffset + 1);
        }

        iRet = savescreen_addToDialogBuffer (szInputString);
        if (iRet != 0) return iRet;
    }

    iRet = savescreen_addToDialogBuffer ("\n");
    if (iRet != 0) return iRet;

    iRet = savescreen_addToCommandList ("Save to slot 1", 1, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 2", 2, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 3", 3, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 4", 4, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 5", 5, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 6", 6, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 7", 7, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 8", 8, 0);
    if (iRet != 0) return iRet;
    iRet = savescreen_addToCommandList ("Save to slot 9", 9, 0);
    if (iRet != 0) return iRet;

    // dialog should always be capped like this.. so that it works within the screen scroll.
    savescreen_addToDialogBuffer (">\n");

    for (iOffset = 0; iOffset < 399; iOffset++)
        szInputString[iOffset] = 0;

    // re-init the scrolling area..
    pszBase = gpszSaveScrBuffer;
    iRowOut = 0;
    iRowStart = 0;
    cFullScreenFlag = 0;
    cRememberEditFlag = 0;
    cClearScreenFlag = 1; // forces the clear of the screen
    cKeyMode = 0;
    iEditRow = 5;
    iPosition = 0;
    cEnterAction = 0;
    iCommands = 0;
    iCommandOffset = 0;
    iCount = 0;

#ifdef __PDCURSES__
    // the usage of resize_term is for PDCURSES, to enable it to pickup when someone has changed the terminal window area, without this
    //  PDCURSES will readjust its buffers and allow the getmaxyx to pickup the changed screen area.
    resize_term (0, 0);
#endif

    // get the screen resolution again..
    getmaxyx (stdscr, iScrHeight, iScrWidth);

    // if default tab mode is enabled, setup the variables
    if (gcTabDefault != 0)
    {
        // iCommands would already be 0 from the above setting.

        // just count.. it should not be a problem, as the user would have not entered any partial values yet.
        for (iOffset = 0; iOffset < giSaveScrListUsed; iOffset++)
        {
            iCommands++;
        }
    }

    while (1)
    {
        // this is in scroll mode..
        if (cKeyMode == 0)
        {
            pszBase = gpszSaveScrBuffer;
            iRowOut = 0;
            cFullScreenFlag = 0;
            iOffset = 0;

            if (cClearScreenFlag)
            {
                clear ();
                cClearScreenFlag = 0;
            }

            // this is the code that skips the lines that we have already scrolled past.
            if (iRowStart != 0)
            {
                iRowOffset = 0;

                while (iRowStart > iRowOffset)
                {
                    while (1)
                    {
                        if (pszBase[0] != ' ')
                            break;

                        pszBase++;
                    }

                    iOffset = 0;
                    iSpaceOffset = -1;

                    // first pass, find if this is a null or CR char..
                    while (1)
                    {
                        if (pszBase[iOffset] == '\n')
                            break;
                        if (pszBase[iOffset] == 0)
                            break;
                        if (iOffset >= iScrWidth)
                            break;
                        if (pszBase[iOffset] == ' ')
                            iSpaceOffset = iOffset;

                        iOffset++;
                    }

                    // if the line is blank.. skip it..
                    if (iOffset == 0)
                    {
                        // if this is the end.. break..
                        if (pszBase[iOffset] == 0)
                        {
//                              iRowStart = iRowOffset;

                            break;
                        }

                        pszBase++;

                        iRowOffset++;
                        continue;
                    }

                    // if this is the end.. print the output, and then break..
                    if (pszBase[iOffset] == 0)
                    {
//                          iRowStart = iRowOffset;

                        break;
                    }

                    // if this is a newline.
                    if (pszBase[iOffset] == '\n')
                    {
                        pszBase += (iOffset + 1);

                        iRowOffset++;
                        continue;
                    }

                    // to have reached this point, there are no newlines, and we are in the middle of the string..

                    // if we did not find a space character
                    if (iSpaceOffset == -1)
                    {
                        pszBase += iOffset;

                        iRowOffset++;
                        continue;
                    }

                    // otherwise.. we do have a space character..
                    pszBase += (iSpaceOffset + 1);

                    // increment the row offset..
                    iRowOffset++;
                }
            }

            // this is the code that displays the lines we are looking at.
            while (1)
            {
                if ((iRowOut + 1) > iScrHeight)
                {
                    cFullScreenFlag = 1;
                    break;
                }

                move (iRowOut, 0);
                iOffset = 0;
                iSpaceOffset = -1;

                while (1)
                {
                    if (pszBase[0] != ' ')
                        break;

                    pszBase++;
                }

                // first pass, find if this is a null or CR char..
                while (1)
                {
                    if (pszBase[iOffset] == '\n')
                        break;
                    if (pszBase[iOffset] == 0)
                        break;
                    if ((iRowOut + 1) >= iScrHeight)
                    {
                        if (iOffset >= (iScrWidth - 8))
                            break;
                    }
                    if (iOffset >= iScrWidth)
                        break;
                    if (pszBase[iOffset] == ' ')
                        iSpaceOffset = iOffset;

                    iOffset++;
                }

                // if the line is blank.. skip it..
                if (iOffset == 0)
                {
                    // if this is the end.. break..
                    if (pszBase[iOffset] == 0)
                        break;

                    iRowOut++;
                    pszBase++;

                    continue;
                }

                // if this is the end.. print the output, and then break..
                if (pszBase[iOffset] == 0)
                {
                    printw ("%s", pszBase);
                    break;
                }

                // if this is a newline.
                if (pszBase[iOffset] == '\n')
                {
                    addnstr (pszBase, iOffset);

                    iRowOut++;
                    pszBase += (iOffset + 1);

                    continue;
                }

                // to have reached this point, there are no newlines, and we are in the middle of the string..

                // if we did not find a space character
                if (iSpaceOffset == -1)
                {
                    addnstr (pszBase, iOffset);

                    iRowOut++;
                    pszBase += iOffset;

                    continue;
                }

                // otherwise.. we do have a space character..
                addnstr (pszBase, iSpaceOffset);
                iRowOut++;
                pszBase += (iSpaceOffset + 1);
            }

            if ((iRowOut < 3) && (iRowStart > 0))
            {
                iRowStart--;
                if (iRowStart)
                    iRowStart--;
                continue;
            }

            if (cFullScreenFlag == 1)
            {
                attron (A_REVERSE | A_BOLD);
                move (iScrHeight - 1, iScrWidth - 7);
                addstr ("<more>");
                attroff (A_REVERSE | A_BOLD);
            }
            else
            {
                iEditRow = iRowOut - 1;

                if (gcTabDefault != 0)
                {
                    if (cRememberEditFlag != 0)
                    {
                        mvaddch (iEditRow, 0, '>' | A_BOLD);
                        cKeyMode = 10;
                    }
                    else
                    {
                        mvaddch (iEditRow, 0, ':');
                        cKeyMode = 20;
                    }
                }
                else
                {
                    if (cRememberEditFlag != 0)
                    {
                        mvaddch (iEditRow, 0, ':');
                        cKeyMode = 20;
                    }
                    else
                    {
                        mvaddch (iEditRow, 0, '>' | A_BOLD);
                        cKeyMode = 10;
                    }
                }
                continue;
            }

            // refresh the screen..
            refresh();

            iKey = getch ();

            // home key..
            if (iKey == KEY_HOME)
            {
                iRowStart = 0;
                cClearScreenFlag = 1;
                continue;
            }

            // end key..
            if (iKey == KEY_END)
            {
                cKeyMode = 5;
                continue;
            }

            // Ctrl-Q & Ctrl-C
            if ((iKey == 17) || (iKey == 3))
            {
                iSceneId = -3;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-U -- main menu
            if (iKey == 21)
            {
                iSceneId = -2;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-S/ESC -- returns back to the current scene without doing anything
            if ((iKey == 19) || (iKey == 27))
            {
                iSceneId = -1;
                iSubSceneId = 0;
                break;
            }

            if (iKey == KEY_RESIZE)
            {
#ifdef __PDCURSES__
                resize_term (0, 0);
#endif
                cClearScreenFlag = 1;
                getmaxyx (stdscr, iScrHeight, iScrWidth);
                continue;
            }

            if (iKey == KEY_DOWN)
            {
                iRowStart++;
                cClearScreenFlag = 1;

                continue;
            }

            if (iKey == KEY_UP)
            {
                if (iRowStart > 0)
                {
                    iRowStart--;
                    cClearScreenFlag = 1;
                }

                continue;
            }

            if (iKey == KEY_NPAGE)
            {
                for (iOffset = 0; iOffset < (iScrHeight - 1); iOffset++)
                {
                    iRowStart++;
                }

                cClearScreenFlag = 1;

                continue;
            }

            if (iKey == KEY_PPAGE)
            {
                if (iRowStart > 0)
                {
                    for (iOffset = 0; iOffset < (iScrHeight - 1); iOffset++)
                    {
                        iRowStart--;

                        if (iRowStart == 0)
                            break;
                    }

                    cClearScreenFlag = 1;
                }

                continue;
            }
        }
        // this is the re-calc mode for a resize of the two line editor modes..
        else if (cKeyMode == 5)
        {
            cClearScreenFlag = 1;
            getmaxyx (stdscr, iScrHeight, iScrWidth);
            pszBase = gpszSaveScrBuffer;

            iRowOffset = 0;

            while (1)
            {
                while (1)
                {
                    if (pszBase[0] != ' ')
                        break;

                    pszBase++;
                }

                iOffset = 0;
                iSpaceOffset = -1;

                // first pass, find if this is a null or CR char..
                while (1)
                {
                    if (pszBase[iOffset] == '\n')
                        break;
                    if (pszBase[iOffset] == 0)
                        break;
                    if (iOffset >= iScrWidth)
                        break;
                    if (pszBase[iOffset] == ' ')
                        iSpaceOffset = iOffset;

                    iOffset++;
                }

                // if the line is blank.. skip it..
                if (iOffset == 0)
                {
                    // if this is the end.. break..
                    if (pszBase[iOffset] == 0)
                    {
                        iRowStart = iRowOffset;

                        break;
                    }

                    pszBase++;

                    iRowOffset++;
                    continue;
                }

                // if this is the end.. print the output, and then break..
                if (pszBase[iOffset] == 0)
                {
                    iRowStart = iRowOffset;

                    break;
                }

                // if this is a newline.
                if (pszBase[iOffset] == '\n')
                {
                    pszBase += (iOffset + 1);

                    iRowOffset++;
                    continue;
                }

                // to have reached this point, there are no newlines, and we are in the middle of the string..

                // if we did not find a space character
                if (iSpaceOffset == -1)
                {
                    pszBase += iOffset;

                    iRowOffset++;
                    continue;
                }

                // otherwise.. we do have a space character..
                pszBase += (iSpaceOffset + 1);

                // increment the row offset..
                iRowOffset++;
            }

            iRowStart -= (iScrHeight - 1);
            while (iRowStart < 0)
                iRowStart++;

            cKeyMode = 0;

            continue;
        }
        // this is the editor processing mode..
        else if (cKeyMode == 10)
        {
            // first, count the matches..
            iCount = 0;
            iLen = strlen (szInputString);

            for (iOffset = 0; iOffset < giSaveScrListUsed; iOffset++)
            {
                if (iLen != 0)
                {
                    if (futils_strnicmp (gstruct_SaveScrList[iOffset].pszCommand, szInputString, iLen) == 0)
                    {
                        pszCommand = gstruct_SaveScrList[iOffset].pszCommand;
                        iSceneId = gstruct_SaveScrList[iOffset].iSceneId;
                        iSubSceneId = gstruct_SaveScrList[iOffset].iSubSceneId;
                        iCount++;
                    }
                }
                else
                {
                    pszCommand = gstruct_SaveScrList[iOffset].pszCommand;
                    iSceneId = gstruct_SaveScrList[iOffset].iSceneId;
                    iSubSceneId = gstruct_SaveScrList[iOffset].iSubSceneId;
                    iCount++;
                }
            }

            if (iCount != iCommands)
            {
                iCommands = iCount;

                for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                    szWorkString[iOffset] = ' ';

                szWorkString[iScrWidth - 1] = 0;

                mvaddstr (iEditRow + 1, 0, szWorkString);

                if (iCommands == 0)
                {
                    attron(A_DIM);
                    mvaddnstr (iEditRow + 1, 0, "-No commands..", iScrWidth - 1);
                    attroff(A_DIM);
                    iSceneId = -1;
                    iSubSceneId = -1;
                }
                else
                {
                    if (iCommands == 1)
                    {
                        if (strcmp (pszCommand, szInputString) == 0)
                        {
                            attron(A_DIM);
                            mvaddnstr (iEditRow + 1, 0, "press <enter> to action.", iScrWidth - 1);
                            attroff(A_DIM);
                            cEnterAction = 1;
                        }
                        else
                        {
                            cEnterAction = 0;

                            iLen2 = strlen (pszCommand);

                            if (iLen2 > (iScrWidth - 3))
                            {
                                iOffset = 0;

                                while (iLen2 > (iScrWidth - 3))
                                {
                                    iLen2--;
                                    iOffset++;
                                }

                                mvaddch (iEditRow + 1, 0, '.' | A_BOLD);
                                attron(A_DIM);
                                addstr (&pszCommand[iOffset]);
                                attroff(A_DIM);
                                addch ('?' | A_BOLD);
                            }
                            else
                            {
                                sprintf (szWorkString, ":%s", pszCommand);
                                attron(A_DIM);
                                mvaddnstr (iEditRow + 1, 0, szWorkString, iScrWidth - 3);
                                attroff(A_DIM);
                                addch ('?' | A_BOLD);
                            }
                        }
                    }
                    else
                    {
                        sprintf (szWorkString, "+ %d commands..", iCommands);
                        attron(A_DIM);
                        mvaddnstr (iEditRow + 1, 0, szWorkString, iScrWidth - 1);
                        attroff(A_DIM);
                        iSceneId = -1;
                        iSubSceneId = -1;
                    }
                }

            }

            // now for displaying the text that the user is editing.
            iLen = strlen (szInputString);

            if (iLen > (iScrWidth - 2))
            {
                // ok.. it gets complex.. the length of the string is too long for the screen.

                // first, work out which end we are truncating from..
                // this is based upon exactly where the "iPosition" is right now.

                iLen2 = iScrWidth / 2;
                iPosWinEnd = iLen - iLen2;

                // first mode.. is when the position of the cursor is on the right..
                if (iPosition > iPosWinEnd)
                {
                    mvaddch (iEditRow, 1, '.' | A_DIM);
                    iOffset = iLen - (iScrWidth - 3);
                    mvaddstr (iEditRow, 2, &szInputString[iOffset]);
                    move (iEditRow, 2 + iPosition - iOffset);
                }
                // second mode.. is when the position of the cursor is on the left..
                else if (iPosition < iLen2)
                {
                    mvaddnstr (iEditRow, 1, szInputString, (iScrWidth - 3));
                    mvaddch (iEditRow, (iScrWidth - 2), '.' | A_DIM);
                    move (iEditRow, 1 + iPosition);
                }
                // third mode.. when the cursor is dead center.
                else
                {
                    iOffset = (iPosition - iLen2) + 1;
                    mvaddch (iEditRow, 1, '.' | A_DIM);
                    mvaddch (iEditRow, (iScrWidth - 2), '.' | A_DIM);
                    mvaddnstr (iEditRow, 2, &szInputString[iOffset], (iScrWidth - 4));
                    move (iEditRow, iLen2 + 1);
                }
            }
            else
            {
                // this is the simpler and more straightforward code.
                mvaddstr (iEditRow, 1, szInputString);
                move (iEditRow, 1 + iPosition);
            }

            refresh();

            iKey = getch ();

            // Ctrl-Q & Ctrl-C
            if ((iKey == 17) || (iKey == 3))
            {
                iSceneId = -3;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-U
            if (iKey == 21)
            {
                iSceneId = -2;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-S/ESC -- returns back to the current scene without doing anything
            if ((iKey == 19) || (iKey == 27))
            {
                iSceneId = -1;
                iSubSceneId = 0;
                break;
            }

            // resize key
            if (iKey == KEY_RESIZE)
            {
#ifdef __PDCURSES__
                resize_term (0, 0);
#endif
                cKeyMode = 5;
                if (gcTabDefault != 0)
                    cRememberEditFlag = 1;
                else
                    cRememberEditFlag = 0;
                iCommands = -1;
                continue;
            }

            // home key..
            if (iKey == KEY_HOME)
            {
                iRowStart = 0;

                if (gcTabDefault != 0)
                    cRememberEditFlag = 1;
                else
                    cRememberEditFlag = 0;

                cClearScreenFlag = 1;
                cKeyMode = 0;
                iCommands = -1;

                continue;
            }

            // left key..
            if (iKey == KEY_LEFT)
            {
                if (iPosition > 0)
                    iPosition--;

                continue;
            }

            // up key..
            if (iKey == KEY_UP)
            {
                if (iRowStart > 0)
                {
                    if (gcTabDefault != 0)
                        cRememberEditFlag = 1;
                    else
                        cRememberEditFlag = 0;

                    iRowStart--;
                    cClearScreenFlag = 1;
                    cKeyMode = 0;
                    iCommands = -1;
                }

                continue;
            }

            // page up key..
            if (iKey == KEY_PPAGE)
            {
                if (iRowStart > 0)
                {
                    for (iOffset = 0; iOffset < (iScrHeight - 1); iOffset++)
                    {
                        iRowStart--;

                        if (iRowStart == 0)
                            break;
                    }

                    if (gcTabDefault != 0)
                        cRememberEditFlag = 1;
                    else
                        cRememberEditFlag = 0;

                    cClearScreenFlag = 1;
                    cKeyMode = 0;
                    iCommands = -1;
                }

                continue;
            }

            // right key..
            if (iKey == KEY_RIGHT)
            {
                if (iPosition < (int)strlen (szInputString))
                    iPosition++;

                continue;
            }

            // enter key..
            if ((iKey == 10) || (iKey == 13))
            {
                if (iCommands == 1)
                {
                    for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                        szWorkString[iOffset] = ' ';

                    szWorkString[iScrWidth - 1] = 0;

                    mvaddstr (iEditRow + 1, 0, szWorkString);

                    strcpy (szInputString, pszCommand);
                    iPosition = strlen (pszCommand);

                    if (iPosition > (iScrWidth - 2))
                    {
                        iOffset = strlen (pszCommand) - (iScrWidth - 2);
                        sprintf (szWorkString, "%s", &pszCommand[iOffset]);

                        mvaddch (iEditRow, 0, '.' | A_DIM);
                        attron(A_BOLD);
                        mvaddnstr (iEditRow, 1, szWorkString, iScrWidth - 2);
                        attroff(A_BOLD);
                    }
                    else
                    {
                        iOffset = 0;

                        sprintf (szWorkString, "#%s", pszCommand);
                        attron(A_BOLD);
                        mvaddnstr (iEditRow, 0, szWorkString, iScrWidth - 1);
                        attroff(A_BOLD);
                    }

                    move (iEditRow, (1 + iPosition) - iOffset);

                    refresh ();

                    break;
                }

                beep ();

                continue;
            }

            // tab key (and down key)..
            if ((iKey == KEY_DOWN) || (iKey == 9))
            {
                if (iCommands == 1)
                {
                    strcpy (szInputString, pszCommand);
                    iPosition = strlen (szInputString);
                    iCommands = -1;

                    continue;
                }
                else if (iCommands > 1)
                {
                    cKeyMode = 20;
                    iCommandOffset = 0;
                    mvaddch (iEditRow, 0, ':');
                    continue;
                }
            }

            // backspace key..
            if ((iKey == KEY_BACKSPACE) || (iKey == 8))
            {
                if (iPosition > 0)
                {
                    iPosition--;

                    for (iOffset = iPosition; iOffset < (int)((int)strlen (szInputString) + 1); iOffset++)
                        szInputString[iOffset] = szInputString[iOffset + 1];

                    mvaddch (iEditRow, strlen (szInputString) + 1, ' ');

                    // force a re-evaluate
                    iCommands = -1;
                }
                // this makes backspace function the same as delete when at char position 0.
                else if (iPosition == 0)
                {
                    for (iOffset = iPosition; iOffset < (int)((int)strlen (szInputString) + 1); iOffset++)
                        szInputString[iOffset] = szInputString[iOffset + 1];

                    mvaddch (iEditRow, strlen (szInputString) + 1, ' ');

                    // force a re-evaluate
                    iCommands = -1;
                }

                continue;
            }

            // delete key..
            if (iKey == KEY_DC)
            {
                if ((strlen (szInputString) > 0) && (strlen (szInputString) != iPosition))
                {
                    for (iOffset = iPosition; iOffset < (int)((int)strlen (szInputString) + 1); iOffset++)
                        szInputString[iOffset] = szInputString[iOffset + 1];

                    mvaddch (iEditRow, strlen (szInputString) + 1, ' ');

                    // force a re-evaluate
                    iCommands = -1;
                }
                // this makes delete function the same as back when at the end of the string.
                else if ((strlen (szInputString) == iPosition) && (iPosition))
                {
                    iPosition--;

                    for (iOffset = iPosition; iOffset < (int)((int)strlen (szInputString) + 1); iOffset++)
                        szInputString[iOffset] = szInputString[iOffset + 1];

                    mvaddch (iEditRow, strlen (szInputString) + 1, ' ');

                    // force a re-evaluate
                    iCommands = -1;
                }

                continue;
            }

            // characters we are accepting into the string..
            if (((iKey >= 'A') && (iKey <= 'Z')) || ((iKey >= 'a') && (iKey <= 'z')) || ((iKey >= '0') && (iKey <= '9')) || (iKey == '-') || (iKey == ',') || (iKey == ' ') || (iKey == '\''))
            {
                if ((iCommands == 1) && (cEnterAction == 1))
                    iCommands = -1;

                // if this is at the end of the line already.. just put in the character..
                if (strlen (szInputString) == iPosition)
                {
                    szInputString[iPosition] = iKey;
                    szInputString[iPosition + 1] = 0;
                    iPosition++;

                    continue;
                }

                // otherwise.. this isn't at the end of the line..
                // first move everything at the end out.
                iEndOffset = strlen (szInputString);
                iOffset = iEndOffset;
                szInputString[iOffset + 2] = 0;

                while (1)
                {
                    if (iOffset < iPosition)
                        break;

                    szInputString[iOffset + 1] = szInputString[iOffset];

                    if (iOffset == 0)
                        break;

                    iOffset--;
                }

                // insert the key..
                szInputString[iPosition] = iKey;
                iPosition++;

                continue;
            }
        }
        // this is the tab selection mode..
        else
        {
            iCount = 0;
            iLen = strlen (szInputString);

            for (iOffset = 0; iOffset < giSaveScrListUsed; iOffset++)
            {
                if (iLen != 0)
                {
                    if (futils_strnicmp (gstruct_SaveScrList[iOffset].pszCommand, szInputString, iLen) == 0)
                    {
                        if (iCount == iCommandOffset)
                        {
                            pszCommand = gstruct_SaveScrList[iOffset].pszCommand;
                            iSceneId = gstruct_SaveScrList[iOffset].iSceneId;
                            iSubSceneId = gstruct_SaveScrList[iOffset].iSubSceneId;
                        }

                        iCount++;
                    }
                }
                else
                {
                    if (iCount == iCommandOffset)
                    {
                        pszCommand = gstruct_SaveScrList[iOffset].pszCommand;
                        iSceneId = gstruct_SaveScrList[iOffset].iSceneId;
                        iSubSceneId = gstruct_SaveScrList[iOffset].iSubSceneId;
                    }

                    iCount++;
                }
            }

            for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                szWorkString[iOffset] = ' ';
            szWorkString[iScrWidth - 1] = 0;

            // first, wipe out the ENTIRE entry line..
            mvaddnstr (iEditRow, 0, szWorkString, iScrWidth - 1);

            // build the detail for the comment line..
            sprintf (szWorkString, ":command %d of %d..", iCommandOffset + 1, iCommands);
            szWorkString[iScrWidth - 1] = 0;

            // render the comment line..
            attron(A_DIM);
            mvaddnstr (iEditRow + 1, 0, szWorkString, iScrWidth - 1);
            attroff(A_DIM);

            // now for the harder stuff.. the entry line.
            iLen2 = strlen (pszCommand);

            if (iLen2 >= (iScrWidth - 2))
            {
                // this is where i have to deal with the fact that the window will be too small for the ENTIRE command display.

                // let's check to see if our tail end of the command is going to fit..
                iLen2 = iLen2 - iLen;

                // if the tail-end is not going to fit in one piece, then this is slightly easier.
                if (iLen2 >= (iScrWidth - 2))
                {
                    while (iLen2 > (iScrWidth - 2))
                    {
                        iLen2--;
                        iLen++;
                    }

                    mvaddch (iEditRow, 0, '.');
                    mvaddnstr (iEditRow, 1, &pszCommand[iLen], iLen2);
                    move (iEditRow, iScrWidth - 1);
                }
                // if the tail end is going to be in two peices.. then this becomes more complex..
                else
                {
                    iLen2 = strlen (pszCommand);
                    iOffset = 0;

                    while (iLen2 > (iScrWidth - 2))
                    {
                        iLen2--;
                        iOffset++;
                    }

                    mvaddch (iEditRow, 0, '.');
                    attron(A_BOLD);
                    mvaddnstr (iEditRow, 1, &pszCommand[iOffset], iLen - iOffset);
                    attroff(A_BOLD);
                    addstr (&pszCommand[iLen]);

                    move (iEditRow, iScrWidth - 1);
                }
            }
            else
            {
                // this is the easier code (no overrun).. just put the detail there..

                mvaddch (iEditRow, 0, '>');
                attron(A_BOLD);
                mvaddnstr (iEditRow, 1, pszCommand, iLen);
                attroff(A_BOLD);
                addstr (&pszCommand[iLen]);
                move (iEditRow, 1 + strlen (pszCommand));
            }

            refresh();

            iKey = getch ();

            // Ctrl-Q & Ctrl-C
            if ((iKey == 17) || (iKey == 3))
            {
                iSceneId = -3;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-U
            if (iKey == 21)
            {
                iSceneId = -2;
                iSubSceneId = 0;
                break;
            }

            // Ctrl-S/ESC -- returns back to the current scene without doing anything
            if ((iKey == 19) || (iKey == 27))
            {
                iSceneId = -1;
                iSubSceneId = 0;
                break;
            }

            // resize key
            if (iKey == KEY_RESIZE)
            {
#ifdef __PDCURSES__
                resize_term (0, 0);
#endif
                cKeyMode = 5;
                if (gcTabDefault != 0)
                    cRememberEditFlag = 0;
                else
                    cRememberEditFlag = 1;
                continue;
            }

            // home key..
            if (iKey == KEY_HOME)
            {
                int iRowStartNew;

                iRowStartNew = mutils_calcRowStartOffset (iScrWidth);

                if (iRowStartNew != iRowStart)
                {
                    iRowStart = iRowStartNew;

                    if (gcTabDefault != 0)
                        cRememberEditFlag = 0;
                    else
                        cRememberEditFlag = 1;

                    cClearScreenFlag = 1;
                    cKeyMode = 0;
                    iCommands = -1;
                }

                continue;
            }

            // left and up keys..
            if ((iKey == KEY_LEFT) || (iKey == KEY_UP))
            {
                if (iCommandOffset <= 0)
                    iCommandOffset = iCommands;

                iCommandOffset--;
                continue;
            }

            // right and down keys..
            if ((iKey == KEY_RIGHT) || (iKey == KEY_DOWN))
            {
                iCommandOffset++;

                if (iCommandOffset >= iCommands)
                    iCommandOffset = 0;

                continue;
            }

            // page up key..
            if (iKey == KEY_PPAGE)
            {
                if (iRowStart > 0)
                {
                    for (iOffset = 0; iOffset < (iScrHeight - 1); iOffset++)
                    {
                        iRowStart--;

                        if (iRowStart == 0)
                            break;
                    }

                    if (gcTabDefault != 0)
                        cRememberEditFlag = 0;
                    else
                        cRememberEditFlag = 1;

                    cClearScreenFlag = 1;
                    cKeyMode = 0;
                }

                continue;
            }

            // enter key..
            if ((iKey == 10) || (iKey == 13))
            {
                strcpy (szInputString, pszCommand);
                iPosition = strlen (pszCommand);

                for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                    szWorkString[iOffset] = ' ';

                szWorkString[iScrWidth - 1] = 0;

                mvaddstr (iEditRow + 1, 0, szWorkString);

                if (iPosition > (iScrWidth - 2))
                {
                    iOffset = strlen (pszCommand) - (iScrWidth - 2);
                    sprintf (szWorkString, "%s", &pszCommand[iOffset]);

                    mvaddch (iEditRow, 0, '.' | A_DIM);
                    attron(A_BOLD);
                    mvaddnstr (iEditRow, 1, szWorkString, iScrWidth - 2);
                    attroff(A_BOLD);
                }
                else
                {
                    iOffset = 0;

                    sprintf (szWorkString, "#%s", pszCommand);
                    attron(A_BOLD);
                    mvaddnstr (iEditRow, 0, szWorkString, iScrWidth - 1);
                    attroff(A_BOLD);
                }

                move (iEditRow, (1 + iPosition) - iOffset);

                refresh ();

                break;
            }

            // backspace & delete keys..
            if ((iKey == KEY_BACKSPACE) || (iKey == 8) || (iKey == KEY_DC))
            {
                // This forces the mode back to direct entry, and deletes a character off the end.
                strcpy (szInputString, pszCommand);
                iPosition = strlen (pszCommand) - 1;
                szInputString[iPosition] = 0;

                for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                    szWorkString[iOffset] = ' ';

                szWorkString[iScrWidth - 1] = 0;

                cKeyMode = 10;
                mvaddstr (iEditRow, 1, szWorkString);
                mvaddch (iEditRow, 0, '>' | A_BOLD);
                iCommands = -1;
                continue;
            }

            // tab key..
            if (iKey == 9)
            {
                for (iOffset = 0; iOffset < (iScrWidth - 1); iOffset++)
                    szWorkString[iOffset] = ' ';

                szWorkString[iScrWidth - 1] = 0;

                cKeyMode = 10;
                mvaddstr (iEditRow, 1, szWorkString);
                mvaddch (iEditRow, 0, '>' | A_BOLD);
                iCommands = -1;
                continue;
            }
        }
    }

    //
    // To have reached here, means that the player as selected an entry..
    //

    // indicate that the program should exit
    if (iSceneId == -3)
        return 1;

    // jump to the main menu
    if (iSceneId == -2)
        return 10;

    // return without doing anything
    if (iSceneId == -1)
        return 0;

    // this is the name of the save file.
    sprintf (szWorkString, "save%d.txt", iSceneId);

    // wipe the file buffer
    iRet = futils_wipeFileBuffer (&gstruct_FileBuff);

    //
    // Now to create the save file data, start with the common variables.
    //

    if (iRet == 0)
    {
        struct tm *ptmDateTime;
        time_t tTimeNow;

        time (&tTimeNow);
        ptmDateTime = localtime (&tTimeNow);

        sprintf (szInputString, "##HQWAGlobal\n=12\n%04d-%02d-%02d-%02d-%02d-%02d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
                (int)ptmDateTime->tm_year + 1900,
                (int)ptmDateTime->tm_mon + 1,
                (int)ptmDateTime->tm_mday,
                (int)ptmDateTime->tm_hour,
                (int)ptmDateTime->tm_min,
                (int)ptmDateTime->tm_sec,
                (int)gstructActStateGlobal.sMapId,
                (int)gstructActStateGlobal.sActId,
                (int)gstructActStateGlobal.sPosId,
                (int)gstructActStateGlobal.cEnteredDungeon,
                (int)gstructActStateGlobal.sAct1Monsters,
                (int)gstructActStateGlobal.sAct2Monsters,
                (int)gstructActStateGlobal.sAct3Monsters,
                (int)gstructActStateGlobal.sAct4Monsters,
                (int)gstructActStateGlobal.cGingerEncounter);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        szInputString[0] = 0;
        for (iOffset = 0; iOffset < 50; iOffset++)
        {
            if (gstructActStateGlobal.caEncounterArray[iOffset] == 0)
                szInputString[iOffset] = '0';
            else
                szInputString[iOffset] = '1';
        }
        szInputString[50] = 0;
        strcat (szInputString, "\n");

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        szInputString[0] = 0;
        for (iOffset = 0; iOffset < 8; iOffset++)
        {
            if (gstructActStateGlobal.caAct3UnlockArray[iOffset] == 0)
                szInputString[iOffset] = '0';
            else
                szInputString[iOffset] = '1';
        }
        szInputString[8] = 0;
        strcat (szInputString, "\n");

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    //
    // Now for the data for Wilda.
    //

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd ("##Wilda\n=18\n", &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        sprintf (szInputString, "%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d\n%d\n%d\n%d\n",
                (int)gstructActStateCharWilda.structE.iNum, gstructActStateCharWilda.structE.fFraction,
                (int)gstructActStateCharWilda.structS.iNum, gstructActStateCharWilda.structS.fFraction,
                (int)gstructActStateCharWilda.structM.iNum, gstructActStateCharWilda.structM.fFraction,
                (int)gstructActStateCharWilda.structK.iNum, gstructActStateCharWilda.structK.fFraction,
                (int)gstructActStateCharWilda.structF.iNum, gstructActStateCharWilda.structF.fFraction,
                (int)gstructActStateCharWilda.structL.iNum, gstructActStateCharWilda.structL.fFraction,
                (int)gstructActStateCharWilda.structR.iNum, gstructActStateCharWilda.structR.fFraction,
                (int)gstructActStateCharWilda.structO.iNum, gstructActStateCharWilda.structO.fFraction,
                (int)gstructActStateCharWilda.structV.iNum, gstructActStateCharWilda.structV.fFraction,
                (int)gstructActStateCharWilda.structA.iNum, gstructActStateCharWilda.structA.fFraction,
                (int)gstructActStateCharWilda.structW.iNum, gstructActStateCharWilda.structW.fFraction,
                (int)gstructActStateCharWilda.structG.iNum, gstructActStateCharWilda.structG.fFraction,
                (int)gstructActStateCharWilda.structB.iNum, gstructActStateCharWilda.structB.fFraction,
                (int)gstructActStateCharWilda.structC.iNum, gstructActStateCharWilda.structC.fFraction,
                (int)gstructActStateCharWilda.sSlotW,
                (int)gstructActStateCharWilda.sSlotG,
                (int)gstructActStateCharWilda.sSlotB,
                (int)gstructActStateCharWilda.sSlotC);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    //
    // Now for the data for Crystal.
    //

    if (iRet == 0)
    {
        if (gstructActStateGlobal.sActId == 3)
        {
            iRet = futils_addStringToFileBufferEnd ("##Crystal\n=18\n", &gstruct_FileBuff);
        }
        else
        {
            iRet = futils_addStringToFileBufferEnd ("##Crystal\n=0\n", &gstruct_FileBuff);
        }
    }

    if ((iRet == 0) && (gstructActStateGlobal.sActId == 3))
    {
        sprintf (szInputString, "%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d %.3f\n%d\n%d\n%d\n%d\n",
                (int)gstructActStateCharCrystal.structE.iNum, gstructActStateCharCrystal.structE.fFraction,
                (int)gstructActStateCharCrystal.structS.iNum, gstructActStateCharCrystal.structS.fFraction,
                (int)gstructActStateCharCrystal.structM.iNum, gstructActStateCharCrystal.structM.fFraction,
                (int)gstructActStateCharCrystal.structK.iNum, gstructActStateCharCrystal.structK.fFraction,
                (int)gstructActStateCharCrystal.structF.iNum, gstructActStateCharCrystal.structF.fFraction,
                (int)gstructActStateCharCrystal.structL.iNum, gstructActStateCharCrystal.structL.fFraction,
                (int)gstructActStateCharCrystal.structR.iNum, gstructActStateCharCrystal.structR.fFraction,
                (int)gstructActStateCharCrystal.structO.iNum, gstructActStateCharCrystal.structO.fFraction,
                (int)gstructActStateCharCrystal.structV.iNum, gstructActStateCharCrystal.structV.fFraction,
                (int)gstructActStateCharCrystal.structA.iNum, gstructActStateCharCrystal.structA.fFraction,
                (int)gstructActStateCharCrystal.structW.iNum, gstructActStateCharCrystal.structW.fFraction,
                (int)gstructActStateCharCrystal.structG.iNum, gstructActStateCharCrystal.structG.fFraction,
                (int)gstructActStateCharCrystal.structB.iNum, gstructActStateCharCrystal.structB.fFraction,
                (int)gstructActStateCharCrystal.structC.iNum, gstructActStateCharCrystal.structC.fFraction,
                (int)gstructActStateCharCrystal.sSlotW,
                (int)gstructActStateCharCrystal.sSlotG,
                (int)gstructActStateCharCrystal.sSlotB,
                (int)gstructActStateCharCrystal.sSlotC);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    //
    // Now for the data for the opponent.
    //

    if (iRet == 0)
    {
        if (gstructActStateOpponent.cActive != 0)
        {
            iRet = futils_addStringToFileBufferEnd ("##Opponent\n=5\n", &gstruct_FileBuff);
        }
        else
        {
            iRet = futils_addStringToFileBufferEnd ("##Opponent\n=0\n", &gstruct_FileBuff);
        }
    }

    if ((iRet == 0) && (gstructActStateOpponent.cActive != 0))
    {
        sprintf (szInputString, "%d\n%d\n%d\n%d\n%d\n",
                (int)gstructActStateOpponent.iRage,
                (int)gstructActStateOpponent.iFear,
                (int)gstructActStateOpponent.iConfidence,
                (int)gstructActStateOpponent.iDesire,
                (int)gstructActStateOpponent.iHitPoints);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    //
    // Now for the data for the inventory.
    //

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd ("##Inventory\n=26\n", &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        for (iOffset = 0; (int)(gsActStateInventorySize - 1) > iOffset; iOffset++)
        {
            if (gstructInventoryDescription[iOffset + 1].cEffectivenessFlag == 1)
            {
                // items with effectiveness are special.
                if (gpstructActStateInventory[iOffset + 1].sCount != 0)
                {
                    sprintf (szInputString, "e %d %.3f\n",
                            gpstructActStateInventory[iOffset + 1].structEff.iNum,
                            gpstructActStateInventory[iOffset + 1].structEff.fFraction);
                }
                else
                {
                    strcpy (szInputString, "0\n");
                }
            }
            else
            {
                if (gpstructActStateInventory[iOffset + 1].sCount == 0)
                {
                    strcpy (szInputString, "0\n");
                }
                else if (gstructInventoryDescription[iOffset + 1].cMultiFlag == 1)
                {
                    sprintf (szInputString, "%d\n", (int)gpstructActStateInventory[iOffset + 1].sCount);
                }
                else
                {
                    strcpy (szInputString, "1\n");
                }
            }

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);

            if (iRet)
                break;
        }
    }

    //
    // Now for the PosId data.
    //

    if (iRet == 0)
    {
        sprintf (szInputString, "##PosIdTable\n=%d\n", (int)gsMapPosStaticCurrentSize);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        for (iOffset = 0; (int)gsMapPosStaticCurrentSize > iOffset; iOffset++)
        {
            sprintf (szInputString, "%d %d %d\n",
                    (int)gpstructMapPosDynamicCurrent[iOffset].sVisitCount,
                    (int)gpstructMapPosDynamicCurrent[iOffset].cRand1,
                    (int)gpstructMapPosDynamicCurrent[iOffset].cRand2);

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);

            if (iRet)
                break;
        }
    }

    //
    // Now for the LinkId data.
    //

    if (iRet == 0)
    {
        sprintf (szInputString, "##LinkIdTable\n=%d\n", (int)gsMapLinkDynamicCurrentSize);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        for (iOffset = 0; (int)gsMapLinkDynamicCurrentSize > iOffset; iOffset++)
        {
            sprintf (szInputString, "%d %d %d %d\n",
                    (int)gpstructMapLinkDynamicCurrent[iOffset].sVisitCount,
                    (int)gpstructMapLinkDynamicCurrent[iOffset].cStatus,
                    (int)gpstructMapLinkDynamicCurrent[iOffset].cRand1,
                    (int)gpstructMapLinkDynamicCurrent[iOffset].cRand2);

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);

            if (iRet)
                break;
        }
    }

    //
    // Now for the selection command data.
    //

    if (iRet == 0)
    {
        sprintf (szInputString, "##CommandList\n=%d\n", (int)giCommandListUsed);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        for (iOffset = 0; (int)giCommandListUsed > iOffset; iOffset++)
        {
            sprintf (szInputString, "%d %d %s\n",
                    (int)gstruct_CommandList[iOffset].iSceneId,
                    (int)gstruct_CommandList[iOffset].iSubSceneId,
                    gstruct_CommandList[iOffset].pszCommand);

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);

            if (iRet)
                break;
        }
    }

    //
    // Now for the archive data.
    //

    if (iRet == 0)
    {
        sprintf (szInputString, "##ArchiveBuf\n-%d\n", (int)strlen (gpszArchiveBuffer));

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd (gpszArchiveBuffer, &gstruct_FileBuff);
    }

    //
    // Now for the dailog data.
    //

    if (iRet == 0)
    {
        sprintf (szInputString, "##DialogBuf\n-%d\n", (int)strlen (gpszDialogBuffer));

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuff);
    }

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd (gpszDialogBuffer, &gstruct_FileBuff);
    }

    //
    // trailer line.
    //

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd ("##End##\n\n", &gstruct_FileBuff);
    }

    //
    // Write the file.
    //

    if (iRet == 0)
    {
        unlink (szWorkString);

        futils_writeFileHeaderAndData (szWorkString, "!Version 0.01\n", gstruct_FileBuff.pcData);
    }

    //
    // Inform the user about the success of writing the save file.
    //
    clear ();
    if (iRet == 0)
        sprintf (szInputString, "Written %s successfully.", szWorkString);
    else
        sprintf (szInputString, "Failure writing %s !", szWorkString);
    attron(A_BOLD);
    mvaddstr (1, 1, szInputString);
    attroff(A_BOLD);

    // refresh the screen..
    refresh();

    // sleep for a second
    futils_sleep (1000);

    iSceneId = iSubSceneId;

    return 0;
}

//
// function to load in a save file and to partially parse it, verifying if it is usable.
//
// Note: this function does not actually load the save file, as it is meant to extract
//   and check only some detail from the file for the purposes of showing the file in a
//   list of save/load slots.
//
// returns 2 if non-existent (not enough data to indicate that it is there).
// returns 1 if invalid (could at least retrieve the date/time).
// returns 0 if it appears to be a valid save.
//
int savescreen_parseSaveFile (int iSaveId, char *pszDateTime)
{
    char    szInputString[900];
    char    szWorkString[20];
    int     iOffset;
    int     iMapId;
    int     iActId;
    int     iPosId;
    int     iValue;
    char    cEnteredDungeon;
    int     iYear;
    int     iMonth;
    char    *pszMonth;
    int     iDay;
    int     iHour;
    int     iMin;
    int     iSec;
    int     iRet;

    sprintf (szWorkString, "save%d.txt", iSaveId);

    // load the entire save file into the memory buffer
    iRet = futils_loadFileIntoMemory (szWorkString, &gstruct_FileBuff);

    if (iRet != 0)
        return 2;

    // start with the version line..
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 898) != 0)
    {
        return 2;
    }
    szInputString[898] = 0;

    // check to see if it starts with what we want
    if (szInputString[0] != '!')
        return 2;
    // otherwise I don't care what it says

    //
    // Global values section
    //

    // next the global values section (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 2;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##HQWAGlobal") != 0)
        return 2;

    // next the global values section (size line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 2;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=12") != 0)
        return 2;

    // next the date/time field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 20) != 0)
        return 2;
    szInputString[20] = 0;

    // Check the date/time field (and format it).

    // 00000000001111111111
    // 01234567890123456789
    // YYYY-MM-DD-hh-mm-ss

    if ((szInputString[4] != '-') || (szInputString[7] != '-') || (szInputString[10] != '-') || (szInputString[13] != '-') || (szInputString[16] != '-') || (szInputString[19] != 0))
    {
        return 2;
    }

    szInputString[4] = 0;
    szInputString[7] = 0;
    szInputString[10] = 0;
    szInputString[13] = 0;
    szInputString[16] = 0;

    iYear = atoi (szInputString);
    iMonth = atoi (&szInputString[5]);
    iDay = atoi (&szInputString[8]);
    iHour = atoi (&szInputString[11]);
    iMin = atoi (&szInputString[14]);
    iSec = atoi (&szInputString[17]);

    if ((iYear < 1) || (iMonth < 1) || (iDay < 1) || (iHour < 0) || (iMin < 0) || (iSec < 0) || (iMonth > 12) || (iDay > 31) || (iHour > 23) || (iMin > 59) || (iSec > 59))
    {
        return 2;
    }

    switch (iMonth)
    {
    case 1:
        pszMonth = "Jan";
        break;
    case 2:
        pszMonth = "Feb";
        break;
    case 3:
        pszMonth = "Mar";
        break;
    case 4:
        pszMonth = "Apr";
        break;
    case 5:
        pszMonth = "May";
        break;
    case 6:
        pszMonth = "Jun";
        break;
    case 7:
        pszMonth = "Jul";
        break;
    case 8:
        pszMonth = "Aug";
        break;
    case 9:
        pszMonth = "Sep";
        break;
    case 10:
        pszMonth = "Oct";
        break;
    case 11:
        pszMonth = "Nov";
        break;
    case 12:
        pszMonth = "Dec";
        break;
    default:
        pszMonth = "Unk";
        break;
    }

    sprintf (pszDateTime, "%04d-%s-%02d %02d:%02d:%02d",
            iYear,
            pszMonth,
            iDay,
            iHour,
            iMin,
            iSec);

    // the MapId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iMapId = atoi (szInputString);
    if ((iMapId < 1) || (iMapId > 3))
        return 1;

    // the ActId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iActId = atoi (szInputString);
    if ((iActId < 1) || (iActId > 4))
        return 1;

    // the PosId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iPosId = atoi (szInputString);
    if (iPosId < 1)
        return 1;

    // the EnteredDungeon field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    cEnteredDungeon = (char)atoi (szInputString);
    if ((cEnteredDungeon != 1) && (cEnteredDungeon != 0))
        return 1;

    // the following 4 fields are not checked, but are read/interpreted
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;

    // the 10th line is the encounter stats, which is a bit longer
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 58) != 0)
        return 1;

    // the 11th line is the act3 unlockables.
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;

    //
    // Wilda values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Wilda") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=18") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 18 > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
    }

    //
    // Crystal values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Crystal") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (iActId == 3)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=18") != 0)
            return 1;

        // just verify that we can load the data.
        for (iOffset = 0; 18 > iOffset; iOffset++)
        {
            if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
                return 1;
        }
    }
    else
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=0") != 0)
            return 1;
    }

    //
    // Opponent values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Opponent") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=0") != 0)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=5") != 0)
            return 1;

        // just verify that we can load the data.
        for (iOffset = 0; 5 > iOffset; iOffset++)
        {
            if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
                return 1;
        }
    }

    //
    // Inventory values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Inventory") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=26") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 26 > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
    }

    //
    // PosId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##PosIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
    }

    //
    // LinkId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##LinkIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
    }

    //
    // Command List section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##CommandList") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 148) != 0)
            return 1;
    }

    //
    // Archive Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##ArchiveBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuff.ulBufferPos += (unsigned long)iValue;

    //
    // Dialog Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##DialogBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuff.ulBufferPos += (unsigned long)iValue;

    //
    // Trailer line
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##End##") != 0)
        return 1;

    return 0;
}

//
// function to load in a single map position element.
//
int savescreen_loadPosIdElement (struct mapdata_posdatadynamic *pstructStat)
{
    char    szInputString[50];
    int     iOffset1;
    int     iOffset2;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;
    szInputString[49] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    iOffset1 = 0;

    while (1)
    {
        if (szInputString[iOffset1] == 0)
            return 1;

        if (szInputString[iOffset1] == ' ')
            break;

        iOffset1++;
    }

    szInputString[iOffset1] = 0;
    iOffset1++;

    iOffset2 = iOffset1;

    while (1)
    {
        if (szInputString[iOffset2] == 0)
            return 1;

        if (szInputString[iOffset2] == ' ')
            break;

        iOffset2++;
    }

    szInputString[iOffset2] = 0;
    iOffset2++;

    pstructStat->sVisitCount = (short)atoi (szInputString);
    pstructStat->cRand1 = (char)atoi (&szInputString[iOffset1]);
    pstructStat->cRand2 = (char)atoi (&szInputString[iOffset2]);

    return 0;
}

//
// function to load in a single map link element.
//
int savescreen_loadLinkIdElement (struct mapdata_linkdatadynamic *pstructStat)
{
    char    szInputString[60];
    int     iOffset1;
    int     iOffset2;
    int     iOffset3;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 58) != 0)
        return 1;
    szInputString[58] = 0;
    szInputString[59] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    iOffset1 = 0;

    while (1)
    {
        if (szInputString[iOffset1] == 0)
            return 1;

        if (szInputString[iOffset1] == ' ')
            break;

        iOffset1++;
    }

    szInputString[iOffset1] = 0;
    iOffset1++;

    iOffset2 = iOffset1;

    while (1)
    {
        if (szInputString[iOffset2] == 0)
            return 1;

        if (szInputString[iOffset2] == ' ')
            break;

        iOffset2++;
    }

    szInputString[iOffset2] = 0;
    iOffset2++;

    iOffset3 = iOffset2;

    while (1)
    {
        if (szInputString[iOffset3] == 0)
            return 1;

        if (szInputString[iOffset3] == ' ')
            break;

        iOffset3++;
    }

    szInputString[iOffset3] = 0;
    iOffset3++;

    pstructStat->sVisitCount = (short)atoi (szInputString);
    pstructStat->cStatus = (char)atoi (&szInputString[iOffset1]);
    pstructStat->cRand1 = (char)atoi (&szInputString[iOffset2]);
    pstructStat->cRand2 = (char)atoi (&szInputString[iOffset3]);

    return 0;
}

//
// function to load in a single command element.
//
int savescreen_loadCommandElement ()
{
    char    szInputString[150];
    int     iOffset1;
    int     iOffset2;
    int     iSceneId;
    int     iSubSceneId;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 148) != 0)
        return 1;
    szInputString[148] = 0;
    szInputString[149] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    iOffset1 = 0;

    while (1)
    {
        if (szInputString[iOffset1] == 0)
            return 1;

        if (szInputString[iOffset1] == ' ')
            break;

        iOffset1++;
    }

    szInputString[iOffset1] = 0;
    iOffset1++;

    iOffset2 = iOffset1;

    while (1)
    {
        if (szInputString[iOffset2] == 0)
            return 1;

        if (szInputString[iOffset2] == ' ')
            break;

        iOffset2++;
    }

    szInputString[iOffset2] = 0;
    iOffset2++;

    iSceneId = (int)atoi (szInputString);
    iSubSceneId = (int)atoi (&szInputString[iOffset1]);

    if (mutils_addToCommandList (&szInputString[iOffset2], iSceneId, iSubSceneId))
        return 1;

    return 0;
}

//
// function to load in a single inventory element.
//
int savescreen_loadInventoryElement (int iInvOffset)
{
    char    szInputString[50];
    int     iOffset1;
    int     iOffset2;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;
    szInputString[49] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    // handle the empty values separately
    if ((szInputString[0] == '0') && (szInputString[1] == 0))
    {
        gpstructActStateInventory[iInvOffset].sCount = 0;
        gpstructActStateInventory[iInvOffset].structEff.iNum = 0;
        gpstructActStateInventory[iInvOffset].structEff.fFraction = 0;

        return 0;
    }

    // handle the single values separately
    if ((szInputString[0] == '1') && (szInputString[1] == 0))
    {
        // a singular count, with the effectiveness flag being set is NOT right.
        if (gstructInventoryDescription[iInvOffset].cEffectivenessFlag == 1)
            return 1;

        gpstructActStateInventory[iInvOffset].sCount = 1;
        gpstructActStateInventory[iInvOffset].structEff.iNum = 0;
        gpstructActStateInventory[iInvOffset].structEff.fFraction = 0;

        return 0;
    }

    // if what we have is unequal to a "single effective entry"..
    if (strncmp (szInputString, "e ", 2) != 0)
    {
        // without the multi-flag, this inventory entry should not be other than 0 or 1 (which are handled above).
        if (gstructInventoryDescription[iInvOffset].cMultiFlag == 0)
            return 1;

        gpstructActStateInventory[iInvOffset].structEff.iNum = 0;
        gpstructActStateInventory[iInvOffset].structEff.fFraction = 0;

        gpstructActStateInventory[iInvOffset].sCount = (short)atoi (szInputString);

        // should not be here with a result of 0, because we checked the 0 value manually above.
        if (gpstructActStateInventory[iInvOffset].sCount == 0)
            return 1;

        return 0;
    }

    // an entry that is marked as an "effective" value, that should not have an "effective" value is not right.
    if (gstructInventoryDescription[iInvOffset].cEffectivenessFlag == 0)
        return 1;

    iOffset1 = 2;

    iOffset2 = iOffset1;

    while (1)
    {
        if (szInputString[iOffset2] == 0)
            return 1;

        if (szInputString[iOffset2] == ' ')
            break;

        iOffset2++;
    }

    szInputString[iOffset2] = 0;
    iOffset2++;

    gpstructActStateInventory[iInvOffset].structEff.iNum = (int)atoi (&szInputString[iOffset1]);
    gpstructActStateInventory[iInvOffset].structEff.fFraction = (float)atof (&szInputString[iOffset2]);
    gpstructActStateInventory[iInvOffset].sCount = 1;

    return 0;
}

//
// function to load in a single character structured stat.
//
int savescreen_loadCharStatElement (struct actionstate_stat *pstructStat)
{
    char    szInputString[50];
    int     iOffset;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;
    szInputString[49] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    iOffset = 0;

    while (1)
    {
        if (szInputString[iOffset] == 0)
            return 1;

        if (szInputString[iOffset] == ' ')
            break;

        iOffset++;
    }

    szInputString[iOffset] = 0;
    iOffset++;

    pstructStat->iNum = (int)atoi (szInputString);

    pstructStat->fFraction = (float)atof (&szInputString[iOffset]);

    return 0;
}

//
// function to load in an the structured elements for a character.
//
int savescreen_loadCharStats (struct actionstate_charstats *pstructCharStats)
{
    char    szInputString[50];

    //
    // Load the 14 stat elements
    //
    if (savescreen_loadCharStatElement (&pstructCharStats->structE))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structS))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structM))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structK))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structF))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structL))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structR))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structO))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structV))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structA))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structW))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structG))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structB))
        return 1;
    if (savescreen_loadCharStatElement (&pstructCharStats->structC))
        return 1;


    //
    // Load the 4 clothing slots
    //
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    pstructCharStats->sSlotW = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    pstructCharStats->sSlotG = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    pstructCharStats->sSlotB = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
        return 1;

    pstructCharStats->sSlotC = (short)atoi (szInputString);

    return 0;
}

//
// function to load in a save file to activate it for real.
//
// returns 1 if there was a problem.
// returns 0 if the save was loaded.
//
int savescreen_loadSaveFile (int iSaveId)
{
    char    szInputString[900];
    char    szWorkString[20];
    int     iOffset;
    int     iValue;
    int     iRet;

    sprintf (szWorkString, "save%d.txt", iSaveId);

    sprintf (szInputString, "Loading %s", szWorkString);

    clear ();
    attron(A_DIM);
    mvaddstr (2, 1, szInputString);
    attroff(A_DIM);
    refresh ();

    // load the entire save file into the memory buffer
    iRet = futils_loadFileIntoMemory (szWorkString, &gstruct_FileBuff);

    if (iRet != 0)
        return 1;

    // start with the version line..
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 898) != 0)
    {
        return 1;
    }
    szInputString[898] = 0;

    // check to see if it starts with what we want
    if (szInputString[0] != '!')
        return 1;
    // otherwise I don't care what it says

    //
    // Global values section
    //

    // next the global values section (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##HQWAGlobal") != 0)
        return 1;

    // next the global values section (size line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=12") != 0)
        return 1;

    // next the date/time field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 20) != 0)
        return 1;
    szInputString[20] = 0;

    // Check the date/time field.

    // 00000000001111111111
    // 01234567890123456789
    // YYYY-MM-DD-hh-mm-ss

    if ((szInputString[4] != '-') || (szInputString[7] != '-') || (szInputString[10] != '-') || (szInputString[13] != '-') || (szInputString[16] != '-') || (szInputString[19] != 0))
    {
        return 1;
    }

    // we are not doing anything with the date/time other than verifying it's format.

    // the MapId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sMapId = (short)atoi (szInputString);
    if ((gstructActStateGlobal.sMapId < 1) || (gstructActStateGlobal.sMapId > 3))
        return 1;

    // the ActId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sActId = (short)atoi (szInputString);
    if ((gstructActStateGlobal.sActId < 1) || (gstructActStateGlobal.sActId > 4))
        return 1;

    // the PosId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sPosId = (short)atoi (szInputString);
    if (gstructActStateGlobal.sPosId < 1)
        return 1;

    // cDirect is a transient variable, that is used to create dialog. It does not need to
    //   be restored as part of loading a save (and it isn't saved anyway)

    // the EnteredDungeon field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.cEnteredDungeon = (char)atoi (szInputString);
    if ((gstructActStateGlobal.cEnteredDungeon != 1) && (gstructActStateGlobal.cEnteredDungeon != 0))
        return 1;

    // sAct1Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sAct1Monsters = (short)atoi (szInputString);

    // sAct2Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sAct2Monsters = (short)atoi (szInputString);

    // sAct3Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sAct3Monsters = (short)atoi (szInputString);

    // sAct4Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.sAct4Monsters = (short)atoi (szInputString);

    // cGingerEncounter
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    gstructActStateGlobal.cGingerEncounter = (char)atoi (szInputString);
    if ((gstructActStateGlobal.cGingerEncounter != 1) && (gstructActStateGlobal.cGingerEncounter != 0))
        return 1;

    // caEncounterArray
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 58) != 0)
        return 1;
    szInputString[58] = 0;

    // this array has to be EXACTLY 50 characters long.
    if (strlen (szInputString) != 50)
        return 1;

    // load in the array data.
    for (iOffset = 0; iOffset < 50; iOffset++)
    {
        if (szInputString[iOffset] == '0')
            gstructActStateGlobal.caEncounterArray[iOffset] = 0;
        else
            gstructActStateGlobal.caEncounterArray[iOffset] = 1;
    }

    // caAct3UnlockArray
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // this array has to be EXACTLY 8 characters long.
    if (strlen (szInputString) != 8)
        return 1;

    // load in the array data.
    for (iOffset = 0; iOffset < 8; iOffset++)
    {
        if (szInputString[iOffset] == '0')
            gstructActStateGlobal.caAct3UnlockArray[iOffset] = 0;
        else
            gstructActStateGlobal.caAct3UnlockArray[iOffset] = 1;
    }

    //
    // Ok, at this point we have our map number and act number.
    //
    // Before loading the rest of the save file, I am going to setup the map data appropriately.
    // but only if we have entered the dungeon
    //

    if (gstructActStateGlobal.cEnteredDungeon)
    {
        sprintf (szWorkString, "Map%dAct%d", gstructActStateGlobal.sMapId, gstructActStateGlobal.sActId);

        // now init (and allocate) the map data.
        iRet = mapdata_selectAndInitMapData (szWorkString);

        if (iRet != 0)
            return 1;

        // this will not work if the current position is outside of the limits of the map.
        if (gstructActStateGlobal.sPosId > gsMapPosStaticCurrentSize)
            return 1;
    }
    else
    {
        gsMapLinkDynamicCurrentSize = 0;
        gsMapPosStaticCurrentSize = 0;
    }

    // force init the other values
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;

    attron(A_DIM);
    mvaddstr (3, 1, "Global vars loaded");
    attroff(A_DIM);
    refresh ();

    //
    // Wilda values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Wilda") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=18") != 0)
        return 1;

    // load in Wilda's stats
    iRet = savescreen_loadCharStats (&gstructActStateCharWilda);
    if (iRet != 0)
        return 1;

    //
    // Crystal values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Crystal") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (gstructActStateGlobal.sActId == 3)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=18") != 0)
            return 1;

        // load in Crystal's stats
        iRet = savescreen_loadCharStats (&gstructActStateCharCrystal);
        if (iRet != 0)
            return 1;
    }
    else
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=0") != 0)
            return 1;
    }

    //
    // Opponent values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Opponent") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=0") != 0)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=5") != 0)
            return 1;

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;

        if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
            return 1;

        gstructActStateOpponent.iRage = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;

        if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
            return 1;

        gstructActStateOpponent.iFear = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;

        if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
            return 1;

        gstructActStateOpponent.iConfidence = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;

        if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
            return 1;

        gstructActStateOpponent.iDesire = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;

        if ((szInputString[0] == '#') || (szInputString[0] == '=') || (szInputString[0] == '!'))
            return 1;

        gstructActStateOpponent.iHitPoints = (int)atoi (szInputString);
    }

    attron(A_DIM);
    mvaddstr (4, 1, "Character Stats Loaded");
    attroff(A_DIM);
    refresh ();

    //
    // Inventory values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Inventory") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=26") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 26 > iOffset; iOffset++)
    {
        iRet = savescreen_loadInventoryElement (iOffset + 1);
        if (iRet != 0)
            return 1;
    }

    attron(A_DIM);
    mvaddstr (5, 1, "Inventory Loaded");
    attroff(A_DIM);
    refresh ();

    //
    // PosId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##PosIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // check the value against the size of the table when this map/act is loaded.
    if (iValue != gsMapPosStaticCurrentSize)
        return 1;

    // load the data in.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        iRet = savescreen_loadPosIdElement (&gpstructMapPosDynamicCurrent[iOffset]);
        if (iRet != 0)
            return 1;
    }

    //
    // LinkId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##LinkIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // check the value against the size of the table when this map/act is loaded.
    if (iValue != gsMapLinkDynamicCurrentSize)
        return 1;

    // load the data in.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        iRet = savescreen_loadLinkIdElement (&gpstructMapLinkDynamicCurrent[iOffset]);
        if (iRet != 0)
            return 1;
    }

    attron(A_DIM);
    mvaddstr (6, 1, "Dynamic map data loaded");
    attroff(A_DIM);
    refresh ();

    //
    // Command List section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##CommandList") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // wipe the existing command list
    mutils_initAndClearCommandList ();

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        iRet = savescreen_loadCommandElement ();
        if (iRet != 0)
            return 1;
    }

    attron(A_DIM);
    mvaddstr (7, 1, "Command list loaded");
    attroff(A_DIM);
    refresh ();

    //
    // Archive Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##ArchiveBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    if (iValue > 65535)
        return 1;

    // copy the archive data straight over
    strncpy (gpszArchiveBuffer, &gstruct_FileBuff.pcData[gstruct_FileBuff.ulBufferPos], iValue);
    gpszArchiveBuffer[iValue] = 0;
    giArchiveBufferUsed = iValue;

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuff.ulBufferPos += (unsigned long)iValue;

    //
    // Dialog Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##DialogBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    // if the data is larger than what we have allocated for buffer.
    if (iValue > giDialogBufferSize)
    {
        // .. then it is time to increase the memory buffer allocation.
        int iNewSize = iValue + 100;
        char *pcMemData;

        // round up..
        while (iNewSize % 8192)
            iNewSize++;

        // decrement by 2 (it is added in by the realloc)..
        iNewSize -= 2;

        // now for the realloc..
        pcMemData = (char *)realloc ((VOID *)gpszDialogBuffer, (size_t)(iNewSize + 2));

        if (pcMemData == NULL)
            return 1;

        // I don't care if realloc is going to keep it all, I am about to overwrite it..

        // Now to save aside the references..
        gpszDialogBuffer = pcMemData;
        giDialogBufferSize = iNewSize;
    }

    // copy the archive data straight over
    strncpy (gpszDialogBuffer, &gstruct_FileBuff.pcData[gstruct_FileBuff.ulBufferPos], iValue);
    gpszDialogBuffer[iValue] = 0;
    giDialogBufferUsed = iValue;

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuff.ulBufferPos += (unsigned long)iValue;

    //
    // Trailer line
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuff, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##End##") != 0)
        return 1;

    attron(A_DIM);
    mvaddstr (8, 1, "Dialog loaded");
    attroff(A_DIM);

    return 0;
}

