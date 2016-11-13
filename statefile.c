//
// statefile.c
//
// save/load functions for save files.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"
#include "mapdata.h"

// linkage to the file load structure..
extern  struct	futils_filebuff         gstruct_FileBuffGen;

// linkage to the mutils data.
extern  struct  mutils_commandlist  *gstruct_CommandList;
extern  int     giCommandListUsed;
extern  char    *gpszDialogBuffer;
extern  int     giDialogBufferUsed;
extern  int     giDialogBufferSize;
extern  char    *gpszArchiveBuffer;
extern  int     giArchiveBufferUsed;

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

#ifndef INTERFACE_CURSES
extern char     gszSessionTrackingId[50];
#endif //INTERFACE_CURSES

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
int statefile_parseSaveFile (char *pszFileName, char *pszDateTime)
{
    char    szInputString[900];
    int     iOffset;
    int     iMapId;
    int     iActId;
    int     iPosId;
    int     iValue;
    char    cEnteredDungeon;
    int     iYear;
    int     iMonth;
#ifdef INTERFACE_CURSES
    char    *pszMonth;
#endif // INTERFACE_CURSES
    int     iDay;
    int     iHour;
    int     iMin;
    int     iSec;
    int     iRet;

    // load the entire save file into the memory buffer
    iRet = futils_loadFileIntoMemory (pszFileName, &gstruct_FileBuffGen);

    if (iRet != 0)
        return 2;

    // start with the version line..
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 898) != 0)
    {
        return 2;
    }
    szInputString[898] = 0;

#ifdef INTERFACE_CURSES
    // check to see if it starts with what we want
    if (szInputString[0] != '!')
        return 2;
#else
    // check to see if it starts with what we want
    if (szInputString[0] != '*')
        return 2;
#endif //INTERFACE_CURSES

    // otherwise I don't care what it says

    //
    // Global values section
    //

    // next the global values section (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 2;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##HQWAGlobal") != 0)
        return 2;

    // next the global values section (size line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 2;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=15") != 0)
        return 2;

    // next the date/time field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 20) != 0)
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

#ifdef INTERFACE_CURSES
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
#else

    {
        struct tm tmDateTime;
        time_t tTimeNow;

        tmDateTime.tm_year = iYear - 1900;
        tmDateTime.tm_mon = iMonth - 1;
        tmDateTime.tm_mday = iDay;
        tmDateTime.tm_hour = iHour;
        tmDateTime.tm_min = iMin;
        tmDateTime.tm_sec = iSec;
        tmDateTime.tm_isdst = -1;

        tTimeNow = mktime (&tmDateTime);

        sprintf (pszDateTime, "%ld", tTimeNow);
    }

#endif //INTERFACE_CURSES

    // the MapId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iMapId = atoi (szInputString);
    if ((iMapId < 1) || (iMapId > 3))
        return 1;

    // the ActId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iActId = atoi (szInputString);
    if ((iActId < 1) || (iActId > 4))
        return 1;

    // the PosId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    iPosId = atoi (szInputString);
    if (iPosId < 1)
        return 1;

    // the EnteredDungeon field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    cEnteredDungeon = (char)atoi (szInputString);
    if ((cEnteredDungeon != 1) && (cEnteredDungeon != 0))
        return 1;

    // the following 4 fields are not checked, but are read/interpreted
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;

    // the 10th line is the encounter stats, which is a bit longer
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 58) != 0)
        return 1;

    // the 11th line is the act3 unlockables.
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;

    // the 12th, 13th and 14th lines are not checked, but are read/interpreted
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;

    //
    // Wilda values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Wilda") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=18") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 18 > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
    }

    //
    // Crystal values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Crystal") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
            if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
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
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Opponent") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
            if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
                return 1;
        }
    }

    //
    // Inventory values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Inventory") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=26") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 26 > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
    }

    //
    // PosId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##PosIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
    }

    //
    // LinkId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##LinkIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
    }

    //
    // Command List section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##CommandList") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '=')
        return 1;

    iValue = atoi (&szInputString[1]);

    // just verify that we can load the data.
    for (iOffset = 0; iValue > iOffset; iOffset++)
    {
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 148) != 0)
            return 1;
    }

    //
    // Archive Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##ArchiveBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuffGen.ulBufferPos += (unsigned long)iValue;

    //
    // Dialog Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##DialogBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuffGen.ulBufferPos += (unsigned long)iValue;

    //
    // Trailer line
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##End##") != 0)
        return 1;

    return 0;
}


//
// Sub function to check if this line is what it should be.
//
int statefile_checkLineNonString (char *pszLine)
{
    if ((pszLine[0] == '#') || (pszLine[0] == '=') || (pszLine[0] == '!'))
        return 1;

    return 0;
}


//
// function to load in a single map position element.
//
int statefile_loadPosIdElement (struct mapdata_posdatadynamic *pstructStat)
{
    char    szInputString[50];
    int     iOffset1;
    int     iOffset2;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;
    szInputString[49] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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
int statefile_loadLinkIdElement (struct mapdata_linkdatadynamic *pstructStat)
{
    char    szInputString[60];
    int     iOffset1;
    int     iOffset2;
    int     iOffset3;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 58) != 0)
        return 1;
    szInputString[58] = 0;
    szInputString[59] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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
int statefile_loadCommandElement ()
{
    char    szInputString[150];
    int     iOffset1;
    int     iOffset2;
    int     iSceneId;
    int     iSubSceneId;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 148) != 0)
        return 1;
    szInputString[148] = 0;
    szInputString[149] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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
int statefile_loadInventoryElement (int iInvOffset)
{
    char    szInputString[50];
    int     iOffset1;
    int     iOffset2;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;
    szInputString[49] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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
int statefile_loadCharStatElement (struct actionstate_stat *pstructStat)
{
    char    szInputString[50];
    int     iOffset;

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
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
int statefile_loadCharStats (struct actionstate_charstats *pstructCharStats)
{
    char    szInputString[50];

    //
    // Load the 14 stat elements
    //
    if (statefile_loadCharStatElement (&pstructCharStats->structE))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structS))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structM))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structK))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structF))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structL))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structR))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structO))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structV))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structA))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structW))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structG))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structB))
        return 1;
    if (statefile_loadCharStatElement (&pstructCharStats->structC))
        return 1;


    //
    // Load the 4 clothing slots
    //
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    pstructCharStats->sSlotW = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    pstructCharStats->sSlotG = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    pstructCharStats->sSlotB = (short)atoi (szInputString);

    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
        return 1;
    szInputString[48] = 0;

    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    pstructCharStats->sSlotC = (short)atoi (szInputString);

    return 0;
}


//
// function to load in a save file to activate it for real.
//
// returns 1 if there was a problem.
// returns 0 if the save was loaded.
//
int statefile_loadSaveFile (char *pszFileName)
{
    char    szInputString[900];
    char    szWorkString[20];
    int     iOffset;
    int     iValue;
    int     iRet;

#ifdef INTERFACE_CURSES
    sprintf (szInputString, "Loading %s", pszFileName);

    clear ();
    attron(A_DIM);
    mvaddstr (2, 1, szInputString);
    attroff(A_DIM);
    refresh ();
#endif

    // load the entire save file into the memory buffer
    iRet = futils_loadFileIntoMemory (pszFileName, &gstruct_FileBuffGen);

    if (iRet != 0)
        return 1;

    // start with the version line..
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 898) != 0)
    {
        return 1;
    }
    szInputString[898] = 0;

#ifdef INTERFACE_CURSES
    // check to see if it starts with what we want
    if (szInputString[0] != '!')
        return 2;
    // otherwise I don't care what it says
#else
    // check to see if it starts with what we want
    if (szInputString[0] != '*')
        return 2;

    // copy aside the tracking id.
    strncpy (gszSessionTrackingId, &szInputString[1], 48);
    gszSessionTrackingId[48] = 0;
#endif //INTERFACE_CURSES

    //
    // Global values section
    //

    // next the global values section (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##HQWAGlobal") != 0)
        return 1;

    // next the global values section (size line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=15") != 0)
        return 1;

    // next the date/time field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 20) != 0)
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
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sMapId = (short)atoi (szInputString);
    if ((gstructActStateGlobal.sMapId < 1) || (gstructActStateGlobal.sMapId > 3))
        return 1;

    // the ActId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sActId = (short)atoi (szInputString);
    if ((gstructActStateGlobal.sActId < 1) || (gstructActStateGlobal.sActId > 4))
        return 1;

    // the PosId field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sPosId = (short)atoi (szInputString);
    if (gstructActStateGlobal.sPosId < 1)
        return 1;

    // cDirect is a transient variable, that is used to create dialog. It does not need to
    //   be restored as part of loading a save (and it isn't saved anyway)

    // the EnteredDungeon field
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.cEnteredDungeon = (char)atoi (szInputString);
    if ((gstructActStateGlobal.cEnteredDungeon != 1) && (gstructActStateGlobal.cEnteredDungeon != 0))
        return 1;

    // sAct1Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sAct1Monsters = (short)atoi (szInputString);

    // sAct2Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sAct2Monsters = (short)atoi (szInputString);

    // sAct3Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sAct3Monsters = (short)atoi (szInputString);

    // sAct4Monsters
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.sAct4Monsters = (short)atoi (szInputString);

    // cGingerEncounter
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.cGingerEncounter = (char)atoi (szInputString);
    if ((gstructActStateGlobal.cGingerEncounter != 1) && (gstructActStateGlobal.cGingerEncounter != 0))
        return 1;

    // caEncounterArray
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 58) != 0)
        return 1;
    szInputString[58] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

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

    // cDirect
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.cDirect = (char)atoi (szInputString);

    // cStairDirect
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.cStairDirect = (char)atoi (szInputString);

    // cStairUpDown
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;
    if (statefile_checkLineNonString (szInputString) != 0) return 1;

    gstructActStateGlobal.cStairUpDown = (char)atoi (szInputString);

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (3, 1, "Global vars loaded");
    attroff(A_DIM);
    refresh ();
#endif

    //
    // Wilda values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Wilda") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=18") != 0)
        return 1;

    // load in Wilda's stats
    iRet = statefile_loadCharStats (&gstructActStateCharWilda);
    if (iRet != 0)
        return 1;

    //
    // Crystal values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Crystal") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (gstructActStateGlobal.sActId == 3)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=18") != 0)
            return 1;

        // load in Crystal's stats
        iRet = statefile_loadCharStats (&gstructActStateCharCrystal);
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
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Opponent") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=0") != 0)
    {
        // if it isn't what we are expecting.. ignore this file.
        if (strcmp (szInputString, "=5") != 0)
            return 1;

        // do not forget to set the active flag
        gstructActStateOpponent.cActive = 1;

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;
        if (statefile_checkLineNonString (szInputString) != 0) return 1;

        gstructActStateOpponent.iRage = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;
        if (statefile_checkLineNonString (szInputString) != 0) return 1;

        gstructActStateOpponent.iFear = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;
        if (statefile_checkLineNonString (szInputString) != 0) return 1;

        gstructActStateOpponent.iConfidence = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;
        if (statefile_checkLineNonString (szInputString) != 0) return 1;

        gstructActStateOpponent.iDesire = (int)atoi (szInputString);

        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 48) != 0)
            return 1;
        szInputString[48] = 0;
        if (statefile_checkLineNonString (szInputString) != 0) return 1;

        gstructActStateOpponent.iHitPoints = (int)atoi (szInputString);
    }
    else
    {
        // clear the active flag
        gstructActStateOpponent.cActive = 0;

        // and make sure all of the other values are 0.
        gstructActStateOpponent.iRage = 0;
        gstructActStateOpponent.iFear = 0;
        gstructActStateOpponent.iConfidence = 0;
        gstructActStateOpponent.iDesire = 0;
        gstructActStateOpponent.iHitPoints = 0;
    }

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (4, 1, "Character Stats Loaded");
    attroff(A_DIM);
    refresh ();
#endif

    //
    // Inventory values section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##Inventory") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "=26") != 0)
        return 1;

    // just verify that we can load the data.
    for (iOffset = 0; 26 > iOffset; iOffset++)
    {
        iRet = statefile_loadInventoryElement (iOffset + 1);
        if (iRet != 0)
            return 1;
    }

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (5, 1, "Inventory Loaded");
    attroff(A_DIM);
    refresh ();
#endif

    //
    // PosId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##PosIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
        iRet = statefile_loadPosIdElement (&gpstructMapPosDynamicCurrent[iOffset]);
        if (iRet != 0)
            return 1;
    }

    //
    // LinkId section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##LinkIdTable") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
        iRet = statefile_loadLinkIdElement (&gpstructMapLinkDynamicCurrent[iOffset]);
        if (iRet != 0)
            return 1;
    }

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (6, 1, "Dynamic map data loaded");
    attroff(A_DIM);
    refresh ();
#endif

    //
    // Command List section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##CommandList") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
        iRet = statefile_loadCommandElement ();
        if (iRet != 0)
            return 1;
    }

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (7, 1, "Command list loaded");
    attroff(A_DIM);
    refresh ();
#endif

    //
    // Archive Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##ArchiveBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    if (szInputString[0] != '-')
        return 1;

    iValue = atoi (&szInputString[1]);

#ifdef INTERFACE_CURSES
    if (iValue > 65535)
        return 1;
#else
    if (iValue > 16383)
        return 1;
#endif // INTERFACE_CURSES

    // copy the archive data straight over
    strncpy (gpszArchiveBuffer, &gstruct_FileBuffGen.pcData[gstruct_FileBuffGen.ulBufferPos], iValue);
    gpszArchiveBuffer[iValue] = 0;
    giArchiveBufferUsed = iValue;

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuffGen.ulBufferPos += (unsigned long)iValue;

    //
    // Dialog Buffer section
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##DialogBuf") != 0)
        return 1;

    // following line count (second line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
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
    strncpy (gpszDialogBuffer, &gstruct_FileBuffGen.pcData[gstruct_FileBuffGen.ulBufferPos], iValue);
    gpszDialogBuffer[iValue] = 0;
    giDialogBufferUsed = iValue;

    // make the buffer reader jump ahead by the value we have defined.
    gstruct_FileBuffGen.ulBufferPos += (unsigned long)iValue;

    //
    // Trailer line
    //

    // section identifier (first line)
    if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szInputString, 18) != 0)
        return 1;
    szInputString[18] = 0;

    // if it isn't what we are expecting.. ignore this file.
    if (strcmp (szInputString, "##End##") != 0)
        return 1;

#ifdef INTERFACE_CURSES
    attron(A_DIM);
    mvaddstr (8, 1, "Dialog loaded");
    attroff(A_DIM);
#endif

    return 0;
}


//
// function to write out the variables to a save file.
//
int statefile_writeSaveFile (char *pszFileName)
{
    char    szInputString[900];
    int     iOffset;
    int     iRet;

    // wipe the file buffer
    iRet = futils_wipeFileBuffer (&gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    //
    // Start with the global variables.
    //

    {
        struct tm *ptmDateTime;
        time_t tTimeNow;

        time (&tTimeNow);
        ptmDateTime = localtime (&tTimeNow);

        sprintf (szInputString, "##HQWAGlobal\n=15\n%04d-%02d-%02d-%02d-%02d-%02d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
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
    }

    iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    if (iRet == 0)
    {
        sprintf (szInputString, "%d\n%d\n%d\n",
                (int)gstructActStateGlobal.cDirect,
                (int)gstructActStateGlobal.cStairDirect,
                (int)gstructActStateGlobal.cStairUpDown);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    if (iRet != 0)
        return 1;


    //
    // Now for the data for Wilda.
    //

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd ("##Wilda\n=18\n", &gstruct_FileBuffGen);
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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    //
    // Now for the data for Crystal.
    //

    if (iRet == 0)
    {
        if (gstructActStateGlobal.sActId == 3)
        {
            iRet = futils_addStringToFileBufferEnd ("##Crystal\n=18\n", &gstruct_FileBuffGen);
        }
        else
        {
            iRet = futils_addStringToFileBufferEnd ("##Crystal\n=0\n", &gstruct_FileBuffGen);
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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    //
    // Now for the data for the opponent.
    //

    if (iRet == 0)
    {
        if (gstructActStateOpponent.cActive != 0)
        {
            iRet = futils_addStringToFileBufferEnd ("##Opponent\n=5\n", &gstruct_FileBuffGen);
        }
        else
        {
            iRet = futils_addStringToFileBufferEnd ("##Opponent\n=0\n", &gstruct_FileBuffGen);
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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    //
    // Now for the data for the inventory.
    //

    if (iRet == 0)
    {
        iRet = futils_addStringToFileBufferEnd ("##Inventory\n=26\n", &gstruct_FileBuffGen);
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

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);

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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    }

    if (iRet == 0)
    {
        for (iOffset = 0; (int)gsMapPosStaticCurrentSize > iOffset; iOffset++)
        {
            sprintf (szInputString, "%d %d %d\n",
                    (int)gpstructMapPosDynamicCurrent[iOffset].sVisitCount,
                    (int)gpstructMapPosDynamicCurrent[iOffset].cRand1,
                    (int)gpstructMapPosDynamicCurrent[iOffset].cRand2);

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);

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

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
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

            iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);

            if (iRet)
                break;
        }
    }

    if (iRet != 0)
        return 1;

    //
    // Now for the selection command data.
    //

    sprintf (szInputString, "##CommandList\n=%d\n", (int)giCommandListUsed);

    iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    for (iOffset = 0; (int)giCommandListUsed > iOffset; iOffset++)
    {
        sprintf (szInputString, "%d %d %s\n",
                (int)gstruct_CommandList[iOffset].iSceneId,
                (int)gstruct_CommandList[iOffset].iSubSceneId,
                gstruct_CommandList[iOffset].pszCommand);

        iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);

        if (iRet != 0)
            return 1;
    }

    //
    // Now for the archive data.
    //

    sprintf (szInputString, "##ArchiveBuf\n-%d\n", (int)strlen (gpszArchiveBuffer));

    iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    iRet = futils_addStringToFileBufferEnd (gpszArchiveBuffer, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    //
    // Now for the dailog data.
    //

    sprintf (szInputString, "##DialogBuf\n-%d\n", (int)strlen (gpszDialogBuffer));

    iRet = futils_addStringToFileBufferEnd (szInputString, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    iRet = futils_addStringToFileBufferEnd (gpszDialogBuffer, &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    //
    // trailer line.
    //

    iRet = futils_addStringToFileBufferEnd ("##End##\n\n", &gstruct_FileBuffGen);
    if (iRet != 0)
        return 1;

    //
    // Write the file.
    //

    unlink (pszFileName);

#ifdef INTERFACE_CURSES
    futils_writeFileHeaderAndData (pszFileName, "!Version 0.70\n", gstruct_FileBuffGen.pcData);
#else
    sprintf (szInputString, "*%s\n", gszSessionTrackingId);

    futils_writeFileHeaderAndData (pszFileName, szInputString, gstruct_FileBuffGen.pcData);
#endif //INTERFACE_CURSES

    return 0;
}


