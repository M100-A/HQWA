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

// linkage to the global variable for defining that tab mode is the default mode
extern  char    gcTabDefault;

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

        sprintf (szInputString, "save%d.txt", iOffset + 1);

        iRet = statefile_parseSaveFile (szInputString, szDateTime);

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

    //
    // Leave it to the sub function to write this out.
    //
    iRet = statefile_writeSaveFile (szWorkString);

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

