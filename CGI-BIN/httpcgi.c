//
// httpcgi.c
//
// functions to interact with the CGI-BIN interface for HTTP..
//

#include "common.h"

//
// sub-function used by httpcgi_urlConvertList ().
//
char httpcgi_fromHex (char ch)
{
    return isdigit (ch) ? ch - '0' : tolower (ch) - 'a' + 10;
}


//
// Function to convert URL encoded data (can be used for query string, but I use it for post data).
//
// This changes the data into a list where each entry is terminated by a newline character,
//  except the last, which is terminated with a NULL.
//
void httpcgi_urlConvertList (char *pPostData, char *pOutput, int iLen)
{
    int i;
    char *pTemp;

    // first, I zero out the entire output storage.
    for (i = 0; i < (iLen + 1); i++)
        pOutput[i] = 0;
    // it is up to the caller to pre-alloc the memory block large enough for iLen + 1.

    i = 0;
    pTemp = pPostData;

    while (pTemp[0] != 0)
    {
        // most of this conversion code came from an code snippet on the internet.
        if (pTemp[0] == '%')
        {
            if (pTemp[1] && pTemp[2])
            {
                pOutput[i] = httpcgi_fromHex(pTemp[1]) << 4 | httpcgi_fromHex(pTemp[2]);
                pTemp += 2;
            }
        }
        else if (pTemp[0] == '+')
        {
            pOutput[i] = ' ';
        }
        // this is one of my additions, to turn the list-entry into something that is new-line terminated.
        else if (pTemp[0] == '&')
        {
            // & symbols should be % escaped by the browser (as part of URLencoding) anyway.
            pOutput[i] = '\n';
        }
        else
        {
            pOutput[i] = pTemp[0];
        }
        i++;
        pTemp++;
    }
}


//
// To work with the converted name-value data (pre-formatted by httpcgi_urlConvertList),
// to extract the data for a "named-value".
//
// Note: it is a good idea to call this with the trailing "=" sign in pszLock, and this is a
// case-sensitive function.
//
int httpcgi_extractEntry (char *pPostData, char *pszLock, char *pszOutput, int iMax)
{
    int iPos = 0;
    int iCount = 0;
    int iComp = (int)strlen (pszLock);

    for (iPos = 0; iPos < (iMax + 1); iPos++)
        pszOutput[iPos] = 0;

    iPos = 0;

    while (1)
    {
        if (pPostData[iPos] == 0)
            break;

        // simple attempt to match..
        if (strncmp (&pPostData[iPos], pszLock, iComp) == 0)
        {
            iPos += iComp;
            while (1)
            {
                if ((pPostData[iPos] == '\n') || (pPostData[iPos] == 0))
                    return 0;

                if (iCount >= iMax)
                    return 0;

                pszOutput[iCount] = pPostData[iPos];

                iCount++;
                iPos++;
            }
        }

        // if no match, then find the start of the next name-value pair.
        while (1)
        {
            if ((pPostData[iPos] == '\n') || (pPostData[iPos] == 0))
                break;

            iPos++;
        }

        if (pPostData[iPos] == 0)
            break;
        if (pPostData[iPos] == '\n')
            iPos++;
    }

    return 1;
}


//
// My generic error output and bail function for CGI-BIN programs.
//
void httpcgi_errorOutput (char *szErrorResult, int iErrorCode)
{
    printf ("Content-type: text/html\nPragma: No-cache\nCache-Control: no-cache\n\n");
    printf ("<!DOCTYPE html>\n<html>\n<body>\nProgram Error:<br/>\n&nbsp;&nbsp;%04d: %s.<br/>\n</body>\n</html>\n", iErrorCode, szErrorResult);
    exit (0);
}

