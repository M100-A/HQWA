//
// mdialog.c
//
// some dialog utilities for the program.
//

#include "common.h"

//
// I put this listing aside from mutils.c, so that I am not altering mutils.
//
// A feature that I am adding into BMPS, is search/replace operations within the dialog.
// I did create a mutils.c function to support this (mutils_addToDialogBufferLenSpec).
//
// This ENTIRE listing is about managing search/replace actions.
//

//
// This is the static search/replace table.
//
// Offset 0 is the PC name
// Offsets 1-6 are the NPC names (variants)
//
struct  mdialog_searchreplacelist gstructSrchRepList[] =
{
    { "00", "Wilda" },
    { "01", "Amber" },
    { "02", "Bambi" },
    { "03", "Crystal" },
    { "04", "Daisy" },
    { "05", "Eboni" },
    { "06", "Felicity" },
    { "07", "Ginger" },
    { "08", "Natasha" },
    { "09", "Jade" },
    { "10", "Trixie" },
    { "11", "Stacy" },
    { "12", "Popper" },
    { NULL, NULL }
};

short   gsSrchRepListMax = 0;

//
// Small function to init the static search/replace list.
//
void mdialog_initStaticList ()
{
    short sOffset1;

    sOffset1 = 0;

    // find the end of the static list

    while (1)
    {
        if (gstructSrchRepList[sOffset1].pszReplace == NULL)
            break;

        sOffset1++;
    }

    gsSrchRepListMax = sOffset1;
}


//
// This is a front end to mutils_addToDialogBuffer & mutils_addToDialogBufferLenSpec,
// which takes care of looking for Search tags and inputting replacements.
//
// One of the grand assumptions is that the input string is null terminated.
//
// 0 if ok
// 1 if there was a memory allocation error
//
int mdialog_addToDialogWithSrchRep (char *pszString)
{
    int iRet;
    int iStart = 0;
    int iPos = 0;
    int iLen = (int)strlen (pszString);
    int iCalc;

    while (1)
    {
        if (iPos >= iLen)
            break;

        if (pszString[iPos] == '#')
        {
            iCalc = iLen - iPos;

            // check that we have enough bytes to lock onto (so we are not potentially searching off the end of the string somewhere).
            if (iCalc > 4)
            {
                if (pszString[iPos + 4] == '#')
                {
                    short sOffset1;
                    char cLock = 0;

                    iCalc = iPos - iStart;

                    //
                    // This is the static search/replace trigger.
                    //
                    if (pszString[iPos + 1] == '!')
                    {
                        for (sOffset1 = 0; sOffset1 < gsSrchRepListMax; sOffset1++)
                        {
                            if (gstructSrchRepList[sOffset1].pszReplace == NULL)
                                break;

                            if (strncmp (gstructSrchRepList[sOffset1].pszSearch, &pszString[iPos + 2], 2) == 0)
                            {
                                cLock = 1;
                                break;
                            }
                        }

                        if (cLock != 0)
                        {
                            // first dump out the string that we have so far
                            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
                            if (iRet != 0) return iRet;

                            // now set our position past the search/replace key.
                            iPos += 5;
                            iStart = iPos;

                            // now put in the search/replace value
                            iRet = mutils_addToDialogBuffer (gstructSrchRepList[sOffset1].pszReplace);
                            if (iRet != 0) return iRet;

                            continue;
                        }
                    }
                }
            }
        }
        // this is all of the CGI-BIN specific search/replace operations
#ifndef INTERFACE_CURSES
        else if (pszString[iPos] == '&')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iPos++;
            iStart = iPos;

            // insert the replacement character entity.
            iRet = mutils_addToDialogBuffer ("&amp;");
            if (iRet != 0) return iRet;

            continue;
        }
        else if (pszString[iPos] == '<')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iPos++;
            iStart = iPos;

            // insert the replacement character entity.
            iRet = mutils_addToDialogBuffer ("&lt;");
            if (iRet != 0) return iRet;

            continue;
        }
        else if (pszString[iPos] == '>')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iPos++;
            iStart = iPos;

            // insert the replacement character entity.
            iRet = mutils_addToDialogBuffer ("&gt;");
            if (iRet != 0) return iRet;

            continue;
        }
        else if (pszString[iPos] == '\"')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iPos++;
            iStart = iPos;

            // insert the replacement character entity.
            iRet = mutils_addToDialogBuffer ("&quot;");
            if (iRet != 0) return iRet;

            continue;
        }
        else if (pszString[iPos] == '\'')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iPos++;
            iStart = iPos;

            // insert the replacement character entity.
            iRet = mutils_addToDialogBuffer ("&apos;");
            if (iRet != 0) return iRet;

            continue;
        }
        else if (pszString[iPos] == '\n')
        {
            iCalc = iPos - iStart;

            // first dump out the string that we have so far
            iRet = mutils_addToDialogBufferLenSpec (&pszString[iStart], iCalc);
            if (iRet != 0) return iRet;

            // now set our new start position.
            iStart = iPos;

            // now put in the extra HTML formatting
            iRet = mutils_addToDialogBuffer ("<br/>");
            if (iRet != 0) return iRet;

        }
#endif // INTERFACE_CURSES

        iPos++;
    }

    // finish off the string
    return (mutils_addToDialogBuffer (&pszString[iStart]));
}
