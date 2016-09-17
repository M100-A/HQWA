//
// futils.c
//
// some file utilities, but it also includes some rather nifty OS level stuff..
//

#include "common.h"

//
// My simple strnicmp function.
//
int futils_strnicmp (char *pszStr1, char *pszStr2, size_t iLength)
{
    int iOffset;

    for (iOffset = 0; iOffset < (int)iLength; iOffset++)
    {
        if ((pszStr1[iOffset] == 0) && (pszStr2[iOffset] == 0))
            return 0; // this is ok, as both strings ended at the same time.. successful match..

        if ((pszStr1[iOffset] == 0) || (pszStr2[iOffset] == 0))
            return 1; // this is not ok.. as the strings are different.. no match..

        if (tolower (pszStr1[iOffset]) != tolower (pszStr2[iOffset]))
            return 1; // this is not ok.. as the strings are different.. no match..
    }

    return 0; // to have reached here.. successful match..
}
// *nix systems don't come with a strnicmp, so I decided to create a VERY simple replacement for it.
// I am after the effect of a non-zero return, for different strings, not to return values that indicate how different the strings are.


//
// My wrapper for the sleep function.
//
void futils_sleep (int iTimeout)
{
#ifdef WIN32
    Sleep (iTimeout);
#else // WIN32
    struct pollfd pollunused;

    poll (&pollunused, 0, iTimeout);
#endif // WIN32
}


//
// My function to preallocate the memory for the memory buffer.
//
int futils_preAllocateBuffer (unsigned long ulBufferSize, struct futils_filebuff *pstructFullFile)
{
    //.. if there is no memory block allocated yet !!!
    if (pstructFullFile->bMemFlag == FALSE)
    {
        pstructFullFile->ulBufferMax = (unsigned long)ulBufferSize;

        if (pstructFullFile->ulBufferMax < 8192)
            pstructFullFile->ulBufferMax = 8192;
        else
        {
            // align the size on a 8192 byte boundary
            while (pstructFullFile->ulBufferMax % 8192)
                pstructFullFile->ulBufferMax++;
        }

        // now we have the size of the memory allocation, lets allocate the memory
        pstructFullFile->pcData = (char *)malloc (pstructFullFile->ulBufferMax + 2);

        // check to see if it was allocated
        if (pstructFullFile->pcData == NULL)
        {
            return 1;
        }

        pstructFullFile->bMemFlag = TRUE;
    }
    // otherwise we are checking to see if the memory block size is enough
    else if (pstructFullFile->ulBufferMax < (unsigned long)(ulBufferSize + 2))
    {
        char *pcMemData;
        unsigned long ulMemAllocAmount;

        ulMemAllocAmount = (unsigned long)ulBufferSize + 2;

        // align the size on a 8192 byte boundary
        while (ulMemAllocAmount % 8192)
            ulMemAllocAmount++;

        pcMemData = (char *)realloc ((VOID *)pstructFullFile->pcData,
                                      (size_t)(ulMemAllocAmount + 2));

        // check to see that we allocated the structures ok
        if (pcMemData == NULL)
        {
            return 1;
        }

        // save in the new values
        pstructFullFile->pcData = pcMemData;
        pstructFullFile->ulBufferMax = ulMemAllocAmount;
    }

    // zero out the other values
    pstructFullFile->pcData[0] = 0;
    pstructFullFile->ulFileTotSpc = 0;
    pstructFullFile->ulBufferPos = 0;

    return 0;
}


//
// My function to pickup an entire file, and load it into a memory buffer.
//
// Returns:
// 0 if ok
// 1 if there was an error
//
int futils_loadFileIntoMemory (char *pszFileName, struct futils_filebuff *pstructFullFile)
{
    int iFileHandle;
    long lFileSize;
    signed int siBytes;

    // open the file
    iFileHandle = _open (pszFileName, _O_RDONLY | _O_BINARY);

    // if the status was -1, then the file was not opened
    if (iFileHandle == -1)
        return 1;

    // figure out the size of the file..
    lFileSize = _lseek (iFileHandle, 0, SEEK_END);
    _lseek (iFileHandle, 0, SEEK_SET);

    // we should now have the size of the file..

    //.. if there is no memory block allocated yet !!!
    if (pstructFullFile->bMemFlag == FALSE)
    {
        pstructFullFile->ulBufferMax = (unsigned long)lFileSize + 2;

        if (pstructFullFile->ulBufferMax < 8192)
            pstructFullFile->ulBufferMax = 8192;
        else
        {
            // align the size on a 8192 byte boundary
            while (pstructFullFile->ulBufferMax % 8192)
                pstructFullFile->ulBufferMax++;
        }

        // now we have the size of the memory allocation, lets allocate the memory
        pstructFullFile->pcData = (char *)malloc (pstructFullFile->ulBufferMax + 2);

        // check to see if it was allocated
        if (pstructFullFile->pcData == NULL)
        {
            _close (iFileHandle);

            return 1;
        }

        pstructFullFile->bMemFlag = TRUE;
    }
    // otherwise we are checking to see if the memory block size is enough
    else if (pstructFullFile->ulBufferMax < (unsigned long)(lFileSize + 2))
    {
        char *pcMemData;
        unsigned long ulMemAllocAmount;

        ulMemAllocAmount = (unsigned long)lFileSize + 2;

        // align the size on a 8192 byte boundary
        while (ulMemAllocAmount % 8192)
            ulMemAllocAmount++;

        pcMemData = (char *)realloc ((VOID *)pstructFullFile->pcData,
                                      (size_t)(ulMemAllocAmount + 2));

        // check to see that we allocated the structures ok
        if (pcMemData == NULL)
        {
            _close (iFileHandle);

            return 1;
        }

        // save in the new values
        pstructFullFile->pcData = pcMemData;
        pstructFullFile->ulBufferMax = ulMemAllocAmount;
    }

    //
    // Now that we have made sure that there are enough bytes allocated, we are going to load
    //  in the file data input !
    //

    // read the data
    siBytes = _read (iFileHandle, pstructFullFile->pcData,
#ifdef WIN32
                     (unsigned int)lFileSize);
#else // WIN32
                     (size_t)lFileSize);
#endif // WIN32

    if (siBytes != (signed int)lFileSize)
    {
        _close (iFileHandle);

        return 1;
    }

    // don't forget to cap the end of the allocated memory buffer
    pstructFullFile->pcData[lFileSize] = 0;
    pstructFullFile->ulFileTotSpc = lFileSize;
    pstructFullFile->ulBufferPos = 0;

    // close the file
    _close (iFileHandle);

    //
    // At this stage the entire buffer is loaded
    //

    return 0;
}


//
// Read a line from a buffered file in memory (using the CR/LF or LF combinations as the line delimiters).
//
// Note: this removes the CR/LF or LF characters from the end of the strings.
//
// Returns:
// 0 if ok
// 1 if there was a file i/o error
// 2 if there was a buffer overrun
// 4 if we have hit the end of the file
//
int futils_readLineFromMemoryNoEndLineCombo (struct futils_filebuff *pstructFullFile, char *pszBuf, unsigned long ulMaxlen)
{
    unsigned long ulCounter;

    // zero out the buffer
    for (ulCounter = 0; ulCounter < ulMaxlen; ulCounter++)
        pszBuf[ulCounter] = 0;
    // I could have just used a memset here.. but who cares..

    // reset the index counter
    ulCounter = 0;

    // while loop to read the data
    while (ulCounter < ulMaxlen)
    {
        // check to see if we have init the vars yet
        if (!pstructFullFile->ulFileTotSpc)
        {
            // this should not be the case with a preloaded file
            return 4;
        }

        // check to see if we have hit the end !!
        if (pstructFullFile->ulBufferPos >= pstructFullFile->ulFileTotSpc)
        {
            return 4;
        }

        // eliminate the <CR> char
        if (pstructFullFile->pcData[pstructFullFile->ulBufferPos] == 0x0d)
        {
            // increment the buffer position
            pstructFullFile->ulBufferPos++;

            continue;
        }

        // copy the data across
        *pszBuf = (char)pstructFullFile->pcData[pstructFullFile->ulBufferPos];

        // use the <NL> char to mark the end of the line
        if (pszBuf[0] == 0x0a)
        {
            // increment the buffer position
            pstructFullFile->ulBufferPos++;

            // don't forget the cap the end of the string
            pszBuf[0] = 0;
            return 0;
        }

        // increment the buffer position
        pstructFullFile->ulBufferPos++;

        // increment the pointers
        ulCounter++;
        pszBuf++;
    }

    // cap the end of the string
    *pszBuf = 0;
    return 2;
}


//
// Function to wipe the memory buffer
//
// The reason that I have this, along with futils_addToFileBuffer() below, is so I can reuse the large
//   input memory buffer for output purposes. These atomic functions are meant to be used by save file
//   processing, to construct most of the save file image in memory before writing it out with
//   futils_writeFileHeaderAndData().
//
int futils_wipeFileBuffer (struct futils_filebuff *pstructFullFile)
{
    if (pstructFullFile->bMemFlag == FALSE)
        return 1;

    pstructFullFile->pcData[0] = 0;
    pstructFullFile->ulFileTotSpc = 0;
    pstructFullFile->ulBufferPos = 0;

    return 0;
}


//
// Function to add a string to the end of a file buffer. If the file buffer isn't big enough to add the
//   string onto the end, this expands the buffer.
//
int futils_addStringToFileBufferEnd (char *pszBuf, struct futils_filebuff *pstructFullFile)
{
    unsigned long ulLen = (unsigned long)strlen (pszBuf);
    unsigned long ulNewLen = pstructFullFile->ulBufferPos + ulLen;

    if (pstructFullFile->ulBufferMax < (unsigned long)(ulNewLen + 2))
    {
        char *pcMemData;
        unsigned long ulMemAllocAmount;

        ulMemAllocAmount = (unsigned long)ulNewLen + 2;

        // align the size on a 8192 byte boundary
        while (ulMemAllocAmount % 8192)
            ulMemAllocAmount++;

        pcMemData = (char *)realloc ((VOID *)pstructFullFile->pcData,
                                      (size_t)(ulMemAllocAmount + 2));

        // check to see that we allocated the structures ok
        if (pcMemData == NULL)
        {
            return 1;
        }

        // save in the new values
        pstructFullFile->pcData = pcMemData;
        pstructFullFile->ulBufferMax = ulMemAllocAmount;
    }

    strcat (pstructFullFile->pcData, pszBuf);
    pstructFullFile->pcData[ulNewLen] = 0;
    pstructFullFile->ulBufferPos = ulNewLen;

    return 0;
}


//
// Append some data to a log file (also used for save files)
//
// Note: this is a void, no return code.. so if it does not write anything, the caller is none the wiser.
//
void futils_writeFileHeaderAndData (char *pszFileName, char *pszHeader, char *pszData)
{
    int iFileHandle;
    long lFileSize;

    //
    // create the log file
    //
    iFileHandle = _open ((char *)pszFileName, _O_WRONLY | _O_CREAT | _O_APPEND | _O_BINARY, PERM_FILE);

    // check to see if we were able to open the file ok
    if (iFileHandle  == -1)
    {
        return;
    }

    // jump to the end of the file (we are appending, not overwriting)
    lFileSize = _lseek (iFileHandle, 0, SEEK_END);

    // if the file is zero size, then write the header.
    if (lFileSize == 0)
    {
        // write the data block
        _write (iFileHandle, pszHeader,
#ifdef WIN32
                (unsigned int)strlen (pszHeader));
#else // WIN32
                (size_t)strlen (pszHeader));
#endif // WIN32
    }

    // write the data block
    _write (iFileHandle, pszData,
#ifdef WIN32
           (unsigned int)strlen (pszData));
#else // WIN32
           (size_t)strlen (pszData));
#endif // WIN32

    // shutdown the output file handle
    _close (iFileHandle);
}


