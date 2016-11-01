//
// mutils.c
//
// some memory utilities for the program.
//

#include "common.h"

//
// global variables for the command list.
//

char    gcCommandListAlloc = FALSE;
struct  mutils_commandlist  *gstruct_CommandList;
int     giCommandListSize;
int     giCommandListUsed;

//
// Function to clear (and also init, if used for the first time), the command list.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int mutils_initAndClearCommandList ()
{
    int iOffset;

    //
    // If memory is uninitialized, allocate and initialize it..
    //
    if (gcCommandListAlloc == FALSE)
    {
        giCommandListSize = 36;

        gstruct_CommandList = (struct mutils_commandlist *)malloc ((size_t)sizeof (struct  mutils_commandlist) * (size_t)((size_t)giCommandListSize + (size_t)1));

        if (gstruct_CommandList == NULL)
            return 1;

        gcCommandListAlloc = TRUE;

        for (iOffset = 0; iOffset < giCommandListSize; iOffset++)
        {
            gstruct_CommandList[iOffset].cUseFlag = 0;
            gstruct_CommandList[iOffset].iCommandSize = 126;
            gstruct_CommandList[iOffset].iSceneId = -1;
            gstruct_CommandList[iOffset].iSubSceneId = -1;

            gstruct_CommandList[iOffset].pszCommand = (char *)malloc ((size_t)(gstruct_CommandList[iOffset].iCommandSize + 2));

            if (gstruct_CommandList[iOffset].pszCommand == NULL)
                return 1;

            gstruct_CommandList[iOffset].pszCommand[0] = 0;
        }

        giCommandListUsed = 0;
    }
    //
    // Otherwise.. this is a VERY simple clean of what we have..
    //
    else
    {
        for (iOffset = 0; iOffset < giCommandListUsed; iOffset++)
        {
            gstruct_CommandList[iOffset].cUseFlag = 0;
            gstruct_CommandList[iOffset].pszCommand[0] = 0;
            gstruct_CommandList[iOffset].iSceneId = -1;
            gstruct_CommandList[iOffset].iSubSceneId = -1;
        }

        giCommandListUsed = 0;
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
int mutils_addToCommandList (char *pszCommand, int iSceneId, int iSubSceneId)
{
    int iLen;
    int iOffset;
#ifdef INTERFACE_CURSES
    int iRevOffset;
    char *pszTemp1;
    int iTemp1;
#endif // INTERFACE_CURSES

    iLen = strlen (pszCommand);

    // if the list is currently empty, then it is not necessary to perform an insert sort.. just load in this entry.
    if (giCommandListUsed == 0)
    {
        iOffset = 0;
    }
    else
    {
        // we must have an existing entry already.. so..

        // first, check to see if we are "expanding" the list..
        if (giCommandListUsed >= giCommandListSize)
        {
            int iNewSize;
            int iOldSize;
            struct  mutils_commandlist *structMemData;

            iOldSize = giCommandListSize;
            iNewSize = giCommandListSize + 20;

            while (iNewSize % 64)
                iNewSize++;

            structMemData = (struct mutils_commandlist *)realloc ((VOID *)gstruct_CommandList, (size_t)sizeof (struct  mutils_commandlist) * (size_t)((size_t)iNewSize + (size_t)1));

            if (structMemData == NULL)
            {
                return 1;
            }

            // move in the new offset and size..
            gstruct_CommandList = structMemData;
            giCommandListSize = iNewSize;

            // then init up the data..
            for (iOffset = iOldSize; iOffset < giCommandListSize; iOffset++)
            {
                gstruct_CommandList[iOffset].cUseFlag = 0;
                gstruct_CommandList[iOffset].iCommandSize = 126;
                gstruct_CommandList[iOffset].iSceneId = -1;
                gstruct_CommandList[iOffset].iSubSceneId = -1;

                gstruct_CommandList[iOffset].pszCommand = (char *)malloc ((size_t)(gstruct_CommandList[iOffset].iCommandSize + 2));

                if (gstruct_CommandList[iOffset].pszCommand == NULL)
                    return 1;

                gstruct_CommandList[iOffset].pszCommand[0] = 0;
            }

            // I do the expansion here, so it is less of a problem later..
        }

        // now find if that entry is going to be before anything else in the list..
        for (iOffset = 0; iOffset < giCommandListUsed; iOffset++)
        {
            if (gstruct_CommandList[iOffset].pszCommand[0] == 0)
                continue;

            if (strcmp (gstruct_CommandList[iOffset].pszCommand, pszCommand) > 0)
            {
                break;
            }
        }

#ifdef INTERFACE_CURSES
        // this is for inserting INTO the list..
        if (iOffset < giCommandListUsed)
        {
            // to have reached here, means that this new entry is being inserted either in the middle or at the start of the list.. so everything at
            //  the current offset needs to move down one..

            iRevOffset = giCommandListUsed;

            // this while loop works from the bottom of the list, up to the matching offset.
            while (1)
            {
                if ((iRevOffset < iOffset) || (iRevOffset < 0))
                    break;

                // the idea here is to preserve the size and memory allocation for the command from what we are overwriting..
                pszTemp1 = gstruct_CommandList[iRevOffset + 1].pszCommand;
                iTemp1 = gstruct_CommandList[iRevOffset + 1].iCommandSize;

                // move down everything to the new offset..
                gstruct_CommandList[iRevOffset + 1].cUseFlag = gstruct_CommandList[iRevOffset].cUseFlag;
                gstruct_CommandList[iRevOffset + 1].iSceneId = gstruct_CommandList[iRevOffset].iSceneId;
                gstruct_CommandList[iRevOffset + 1].iSubSceneId = gstruct_CommandList[iRevOffset].iSubSceneId;
                gstruct_CommandList[iRevOffset + 1].pszCommand = gstruct_CommandList[iRevOffset].pszCommand;
                gstruct_CommandList[iRevOffset + 1].iCommandSize = gstruct_CommandList[iRevOffset].iCommandSize;

                // and put in the memory allocation and size specification (swap them over).
                gstruct_CommandList[iRevOffset].pszCommand = pszTemp1;
                gstruct_CommandList[iRevOffset].iCommandSize = iTemp1;

                // decreemnt the counter to move along..
                iRevOffset--;
            }

            // here is where the offset is cleared (to remove any residual from the entry that was moved)..
            gstruct_CommandList[iOffset].cUseFlag = 0;
            gstruct_CommandList[iOffset].iSceneId = -1;
            gstruct_CommandList[iOffset].iSubSceneId = -1;
        }
#else
        // don't bother with the sort code.. just insert it at the end.
        iOffset = giCommandListUsed;
#endif // INTERFACE_CURSES
    }

    // it does not matter if it this is an appendage, insert or a new.. the code is the same..

    // check to see if the amount of memory allocated for the command string is enough..
    if (iLen > gstruct_CommandList[iOffset].iCommandSize)
    {
        int iNewSize;
        char *pcMemData;

        iNewSize = iLen + 20;

        while (iNewSize % 128)
            iNewSize++;
        iNewSize -= 2;

        pcMemData = (char *)realloc ((VOID *)gstruct_CommandList[iOffset].pszCommand,
                                      (size_t)(iNewSize + 2));

        if (pcMemData == NULL)
        {
            return 1;
        }

        // It is VERY bad to bail from here.. because it means that data can be lost when it is an insert..
        // the reason is obvious.. we have already moved the tail entry where it is outside of the bounds of giCommandListUsed..

        gstruct_CommandList[iOffset].pszCommand = pcMemData;
        gstruct_CommandList[iOffset].iCommandSize = iNewSize;
    }

    // copy in the data..
    strcpy (gstruct_CommandList[iOffset].pszCommand, pszCommand);
    gstruct_CommandList[iOffset].iSceneId = iSceneId;
    gstruct_CommandList[iOffset].iSubSceneId = iSubSceneId;
    gstruct_CommandList[iOffset].cUseFlag = 1;
    giCommandListUsed++;

    return 0;
}


//
// global variables for the dialog and archive buffers.
//

char    gcDialogBufferAlloc = FALSE;
char    *gpszDialogBuffer;
int     giDialogBufferSize;
int     giDialogBufferUsed;
char    *gpszArchiveBuffer;
char    *gpszArchiveBufferTemp;
int     giArchiveBufferSize;
int     giArchiveBufferUsed;

//
// Function to clear (and also init, if used for the first time), the dialog buffer allocation.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int mutils_initAndClearDialogBuffer ()
{
    int iOffset;

    if (gcDialogBufferAlloc == FALSE)
    {
        // I only allocate the archive buffer once.

#ifdef INTERFACE_CURSES
        giArchiveBufferSize = 65534;
#else
        giArchiveBufferSize = 16382;
#endif // INTERFACE_CURSES

        gpszArchiveBuffer = (char *)malloc ((size_t)(giArchiveBufferSize + 2));

        if (gpszArchiveBuffer == NULL)
            return 1;

        gpszArchiveBufferTemp = (char *)malloc ((size_t)(giArchiveBufferSize + 2));

        if (gpszArchiveBufferTemp == NULL)
            return 1;

        // reset all of the archive rotational values.
        giArchiveBufferUsed = 0;

        // now for the dialog buffer.

        giDialogBufferSize = 8190;

        gpszDialogBuffer = (char *)malloc ((size_t)(giDialogBufferSize + 2));

        if (gpszDialogBuffer == NULL)
            return 1;

        gcDialogBufferAlloc = TRUE;

        // the idea is I set the amount used to the buffer allocation, then the below for loop initialize the entire buffer, and reset it.
        giDialogBufferUsed = 8191;
        // this isn't really necessary..
    }

    for (iOffset = 0; iOffset < giDialogBufferUsed; iOffset++)
    {
        gpszDialogBuffer[iOffset] = 0;
    }

    giDialogBufferUsed = 0;

    return 0;
}


//
// function to add dialog onto the end of a memory buffer..
//  .. while making sure that the dialog string can fit..
//  .. and to expand the buffer if necessary.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int mutils_addToDialogBuffer (char *pszString)
{
    int iStrLen = (int)strlen (pszString);

    return (mutils_addToDialogBufferLenSpec (pszString, iStrLen));
}


//
// function to add dialog onto the end of a memory buffer..
//  .. while making sure that the dialog string can fit..
//  .. and to expand the buffer if necessary.
//
// Returns:
// 0 if ok
// 1 if there was a memory allocation error
//
int mutils_addToDialogBufferLenSpec (char *pszString, int iStrLen)
{
    int iCalcLen = iStrLen + giDialogBufferUsed;

    // if the calcuated length exceeds what we have for a memory allocation..
    if (iCalcLen > giDialogBufferSize)
    {
        // .. then it is time to increase the memory buffer allocation.
        int iNewSize = iCalcLen + 100;
        char *pcMemData;
        int iOffset;

        // round up..
        while (iNewSize % 8192)
            iNewSize++;

        // decrement by 2 (it is added in by the realloc)..
        iNewSize -= 2;

        // now for the realloc..
        pcMemData = (char *)realloc ((VOID *)gpszDialogBuffer, (size_t)(iNewSize + 2));

        if (pcMemData == NULL)
            return 1;

        // Note: realloc keeps the data that was originally allocated intact (so I have heard)..
        //  however, the expanded memory area can have random crap in it (assuming that the OS
        //  isn't clearing memory as a security measure).. for safety sake.. I am going to
        //  zero out that memory..

        // then init the expanded memory area..
        for (iOffset = giDialogBufferSize; iOffset < iNewSize; iOffset++)
        {
            pcMemData[iOffset] = 0;
        }

        // Now to save aside the references..
        gpszDialogBuffer = pcMemData;
        giDialogBufferSize = iNewSize;
    }

    // if we needed to expand the memory to store this new piece of dialog.. it would have been done in the above..

    // so just copy in the string..
    strncpy (&gpszDialogBuffer[giDialogBufferUsed], pszString, iStrLen);
    // Note: it IS necessary to make sure that the string is capped, because strncpy above does NOT put in the null terminator.
    gpszDialogBuffer[iCalcLen] = 0;

    giDialogBufferUsed = iCalcLen;

    return 0;
}


//
// function to take what is in the dialog buffer and shove it into the archive buffer.
// this also clears the dialog buffer.
//
// Returns: nothing..
//
void mutils_addDialogToArchive (int iEndSubtract)
{
    int iLen1;
    int iOffset;

    // if there is no dialog.. don't bother.. just return.
    if (giDialogBufferUsed == 0)
        return;

    // first.. knock out the subtraction.
    giDialogBufferUsed -= iEndSubtract;

    // check to see if we still fit within the realm of possibility (negative numbers do not work).
    if (giDialogBufferUsed <= 0)
        return;

    iLen1 = giArchiveBufferUsed + giDialogBufferUsed + iEndSubtract;

    //
    // if what we are loading exceeds what we have present
    //
    if (iLen1 > giArchiveBufferSize)
    {
        int iLen2;
        char *pszTemp;
        char cFitLock = 0;

        iOffset = 0;

        //
        // This is the code that knocks out the older dialog, until things fit.
        //
        while (1)
        {
            // this should not happen.. bail out..
            if ((iOffset >= giArchiveBufferUsed) || (gpszArchiveBuffer[iOffset] == 0))
            {
                break;
            }

            // look for the newlines.
            if (gpszArchiveBuffer[iOffset] == '\n')
            {
                while (gpszArchiveBuffer[iOffset] == '\n')
                    iOffset++;

                // this should not happen either.. bail out..
                if ((iOffset >= giArchiveBufferUsed) || (gpszArchiveBuffer[iOffset] == 0))
                {
                    break;
                }

                iLen2 = iLen1 - iOffset;

                // if the calculated size is now smaller than the memory allocation.
                if (iLen2 < giArchiveBufferSize)
                {
                    // break out of the loop
                    cFitLock = 1;
                    break;
                }
            }

            // otherwise increment the start offset.
            iOffset++;
        }

        //
        // if we cannot make the archive buffer small enough, we have to change tack,
        //  and make the dialog fit into the archive (wiping the archive).
        //
        if (cFitLock == 0)
        {
            iOffset = 0;

            iLen1 = giDialogBufferUsed + iEndSubtract;

            //
            // This is the code that knocks out the older dialog, until things fit.
            //
            while (1)
            {
                // this should not happen.. bail out..
                if ((iOffset >= giDialogBufferUsed) || (gpszDialogBuffer[iOffset] == 0))
                {
                    break;
                }

                // look for the newlines.
                if (gpszDialogBuffer[iOffset] == '\n')
                {
                    while (gpszDialogBuffer[iOffset] == '\n')
                        iOffset++;

                    // this should not happen either.. bail out..
                    if ((iOffset >= giDialogBufferUsed) || (gpszDialogBuffer[iOffset] == 0))
                    {
                        break;
                    }

                    iLen2 = iLen1 - iOffset;

                    // if the calculated size is now smaller than the memory allocation.
                    if (iLen2 < giArchiveBufferSize)
                    {
                        // break out of the loop
                        cFitLock = 1;
                        break;
                    }
                }

                // otherwise increment the start offset.
                iOffset++;
            }

            // if this happens, then there is something seriously wrong !!
            if (cFitLock == 0)
                return;

            // Reduce the buffer used by the start subtraction.
            iLen2 -= iEndSubtract;

            //
            // Now to overwrite.
            //
            memcpy ((void *)gpszArchiveBuffer, (void *)(gpszDialogBuffer + iOffset), iLen2);
            giArchiveBufferUsed = iLen2;

            // cap the end of the string.
            gpszArchiveBuffer[iLen2] = 0;

            //
            // Finish by clearing out the dialog buffer before returning.
            //
            for (iOffset = 0; iOffset < giDialogBufferUsed; iOffset++)
            {
                gpszDialogBuffer[iOffset] = 0;
            }

            giDialogBufferUsed = 0;

            return;
        }

        // Reduce the buffer used by the start offset.
        giArchiveBufferUsed -= iOffset;

        // copy the data from the existing archive buffer, to the temporary archive buffer..
        memcpy ((void *)gpszArchiveBufferTemp, (void *)(gpszArchiveBuffer + iOffset), giArchiveBufferUsed + 1);

        // swap the pointers over.
        pszTemp = gpszArchiveBufferTemp;
        gpszArchiveBufferTemp = gpszArchiveBuffer;
        gpszArchiveBuffer = pszTemp;

        // and that is done..
    }

    //
    // Now to append what we have on the end.
    //
    memcpy ((void *)(gpszArchiveBuffer + giArchiveBufferUsed), (void *)gpszDialogBuffer, giDialogBufferUsed);
    giArchiveBufferUsed += giDialogBufferUsed;

    // cap the end of the string.
    gpszArchiveBuffer[giArchiveBufferUsed] = 0;

    //
    // Finish by clearing out the dialog buffer before returning.
    //
    for (iOffset = 0; iOffset < giDialogBufferUsed; iOffset++)
    {
        gpszDialogBuffer[iOffset] = 0;
    }

    giDialogBufferUsed = 0;
}


#ifdef INTERFACE_CURSES
//
// function to to figure out the row start based upon the number of lines the archive buffer.
//
// Returns:
// line offset.
//
int mutils_calcRowStartOffset (int iScrWidth)
{
    char    *pszBase = gpszArchiveBuffer;
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


//
// function to figure out the number of rows in the dialog buffer.
//
// Returns:
// line offset.
//
int mutils_calcDialogRows (int iScrWidth)
{
    char    *pszBase = gpszDialogBuffer;
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
#endif // INTERFACE_CURSES

