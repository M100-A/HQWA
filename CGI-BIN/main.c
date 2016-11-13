//
// main.c
//
// main listing of the program..
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"
#include "mapdata.h"


extern struct  mutils_commandlist  *gstruct_CommandList;
extern int     giCommandListUsed;

extern char    *gpszDialogBuffer;
extern int     giDialogBufferUsed;
extern char    *gpszArchiveBuffer;
extern int     giArchiveBufferUsed;

// storage of the file load structure..
struct	futils_filebuff         gstruct_FileBuffGen;
struct	futils_filebuff         gstruct_FileBuffOut;

// storage for the session tracking id.
char     gszSessionTrackingId[50];

char     gszVersionStamp[20];

// this is the debug output flag
char    gcDebugFlag = 0;
// this is referenced in a lot of the scene files to turn on logging in most places where flags are set and used
// unfortunately, this messes up the dialog display.
// this is turned on by the -D command line switch (CURSES version).


// this is the actual scene list..
struct  main_scenelist gstructSceneList[] =
{
    { 1001, gamelogic01_scene1001 },
    { 1002, gamelogic01_scene1002 },
    { 1003, gamelogic01_scene1003 },
    { 1004, gamelogic01_scene1004 },
    { 1005, gamelogic01_scene1005 },
    { 1006, gamelogic01_scene1006 },
    { 1011, gamelogic01_scene1011 },
    { 1012, gamelogic01_scene1012 },
    { 1013, gamelogic01_scene1013 },
    { 1014, gamelogic01_scene1014 },
    { 1020, gamelogic02_scene1020 },
    { 1021, gamelogic02_scene1021 },
    { 1022, gamelogic02_scene1022 },
    { 1030, gamelogic03_scene1030 },
    { 1031, gamelogic03_scene1031 },
    { 1032, gamelogic03_scene1032 },
    { 1033, gamelogic03_scene1033 },
    { 1034, gamelogic03_scene1034 },
    { 1035, gamelogic03_scene1035 },
    { 1036, gamelogic03_scene1036 },
    { 1040, gamelogic04_scene1040 },
    { 1041, gamelogic04_scene1041 },
    { 1042, gamelogic04_scene1042 },
    { 1050, gamelogic04_scene1050 },
    { 1051, gamelogic04_scene1051 },
    { 1052, gamelogic04_scene1052 },
    { 1060, gamelogic04_scene1060 },
    { 1061, gamelogic04_scene1061 },
    { 1063, gamelogic04_scene1063 },
    { 1070, gamelogic04_scene1070 },
    { 1071, gamelogic04_scene1071 },
    {   -1, NULL                  }
};


//
// main entry point..
//
// (for a CGI-BIN, I cannot work with the command line arguments).
//
int main(void)
{
    char *pszEnvRemoteUser;
    char cEnvRemoteUser = 0;
    char *pszEnvScriptFileName;
    char cEnvScriptFileName = 0;
    char *pszEnvMethod;
    char cEnvMethod = 0;
    char szBasePath[250];
    char szConfigPath[300];
    char szBuffer[1005];
    int iCount = -1;
    int iRet;
    int iPos;
    char *pInputData = NULL;
    char szTrackingId[50];
    char szSceneId[24];
    char szMenuValue[40];
    char cCompleteOutput = 0;
    char cLock = 0;
    int iSceneId = 0;
    int iSubSceneId = 0;
    time_t tTime;

    int iSaveFile = 0;

    int iMainAction = 0;
    // 0 = main menu (default).
    // 1 = about menu.
    // 2 = credits menu.
    // 3 = load menu.
    // 4 = save menu.
    // 5 = change log menu.
    // 6 = spoiler menu.
    // 7 = load action (iSaveFile means something).
    // 8 = save action (iSaveFile means something).
    // 11 = restore last autosave.
    // 10 = game action.
    // 12 = start new.

    // set things up.
    strcpy (gszVersionStamp, "0.71");
    gstruct_FileBuffGen.bMemFlag = FALSE;
    gstruct_FileBuffOut.bMemFlag = FALSE;

    // first look for the REQUEST_METHOD..
    pszEnvMethod = getenv ("REQUEST_METHOD");

    if (pszEnvMethod != NULL)
    {
        if ((int)strlen (pszEnvMethod) != 0)
            cEnvMethod = 1;
    }

    // no REQUEST_METHOD = not running in a CGI-BIN environment.
    if (cEnvMethod == 0)
    {
        printf ("This is a CGI-BIN program, it needs to be executed by a web server that is populating the REQUEST_METHOD environment variable !\n");
        return 1;
    }

    // if we are not a POST operation.
    if (strcmp (pszEnvMethod, "POST") != 0)
    {
        // if we are not a GET operation.
        if (strcmp (pszEnvMethod, "GET") != 0)
        {
            // this program only understands GET and POST.. bail..
            httpcgi_errorOutput ("I only understand GET or POST", 0);
        }

        // set the Env method to 2 (GET)..
        cEnvMethod = 2;
    }
    else // this is a POST operation, get the posted data..
    {
        char *pszEnvContentLength;
        char cEnvContentLength = 0;
        int iLen;
        char *pPostData;
        char *pGetRet;

        // look for CONTENT_LENGTH..
        pszEnvContentLength = getenv ("CONTENT_LENGTH");

        if (pszEnvContentLength != NULL)
        {
            if ((int)strlen (pszEnvContentLength) != 0)
            cEnvContentLength = 1;
        }

        if (cEnvContentLength == 0)
        {
            httpcgi_errorOutput ("Missing CONTENT_LENGTH header for POST data size.", 4);
        }

        iLen = atoi (pszEnvContentLength);

        // I accept up to a certain size..
        if (iLen > 2048)
        {
            httpcgi_errorOutput ("Posted data too large.", 3);
        }

        pInputData = (char *)malloc (iLen + 2);

        if (pInputData == NULL)
        {
            httpcgi_errorOutput ("Unable to allocate memory for PostData.", 5);
        }

        pPostData = (char *)malloc (iLen + 2);

        if (pPostData == NULL)
        {
            httpcgi_errorOutput ("Unable to allocate memory for PostData.", 6);
        }

        // get the posted data (from standard in).
        pGetRet = fgets (pPostData, iLen + 1, stdin);

        if (pGetRet == NULL)
        {
            httpcgi_errorOutput ("Get of PostData failed.", 7);
        }

        // convert the posted data to something more searchable (and printable)..
        httpcgi_urlConvertList (pPostData, pInputData, iLen);

        // free up the posted data, after it has been converted.
        free (pPostData);
    }

    // look up where we are..
    pszEnvScriptFileName = getenv ("SCRIPT_FILENAME");

    if (pszEnvScriptFileName != NULL)
    {
        if ((int)strlen (pszEnvScriptFileName) != 0)
            cEnvScriptFileName = 1;
    }

    if (cEnvScriptFileName == 0)
    {
        printf ("This is a CGI-BIN program, it needs to be executed by a web server that is populating the SCRIPT_FILENAME environment variable !\n");
        return 1;
    }

    strncpy (szBasePath, pszEnvScriptFileName, 198);
    szBasePath[198] = 0;

    // check to see if we are turning on the debug flag
    iPos = (int)strlen (szBasePath);
    if (iPos > 11)
    {
        iPos -= 10;

        if (strcmp (&szBasePath[iPos], ".cheat.cgi") == 0)
            gcDebugFlag = 1;
    }

    // look up who we are..
    pszEnvRemoteUser = getenv ("REMOTE_USER");

    if (pszEnvRemoteUser != NULL)
    {
        if ((int)strlen (pszEnvRemoteUser) != 0)
            cEnvRemoteUser = 1;
    }

    // pre-allocate some working buffers..
    iRet = futils_preAllocateBuffer ((unsigned long)32768, &gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot pre-allocate BuffOut", 1);
    }

    iRet = futils_preAllocateBuffer ((unsigned long)32768, &gstruct_FileBuffGen);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot pre-allocate BuffGen", 1);
    }

    // I set the main command list to be big enough to never expand for this game
    //   (it still can, it is just there is no need).
    iRet = mutils_initAndClearCommandList ();

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot pre-allocate CommandList", 1);
    }

    // I init the dialog buffer last, which inits the fixed archive buffer first.
    //  The dialog buffer is the most likely to grow (and be realloced).
    // setting the order this way reduces the likelihood of memory fragmentation.
    iRet = mutils_initAndClearDialogBuffer ();

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot pre-allocate DialogBuffer", 1);
    }

    // wipe the output buffer..
    iRet = futils_wipeFileBuffer (&gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot wipe BuffOut", 1);
    }

    // start by populating the HTTP return headers (Apache2 is going to add to these anyway).
    iRet = futils_addStringToFileBufferEnd ("Content-type: text/html\nPragma: No-cache\nCache-Control: no-cache\n\n", &gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot start output headers", 11);
    }

    // Note:
    // Apache2.4 handles keepalive from proxied systems (it filters the output from the CGI-BIN program, and changes it to chunked encoding).
    // There was no need to insert a "Connection: close" header in, because Apache2.4 nicely handles things for us.

    // write out the start of the HTML document.
    iRet = futils_addStringToFileBufferEnd ("<!DOCTYPE html>\n<html>\n<head>\n<link rel=\"icon\" type=\"image/x-icon\" href=\"HQWA.ico\" />\n<meta name=\"RATING\" content=\"RTA-5042-1996-1400-1577-RTA\" />\n<title>Hedonism Quest, Wilda\'s Ascension (HQWA) v0.70</title>\n<style type=\"text/css\">\n", &gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Cannot start output initial", 12);
    }

    // try to figure out the "base path"..
    iCount = (int)strlen (szBasePath) - 1;
    while (iCount)
    {
        if (szBasePath[iCount] == '/')
            break;

        iCount--;
    }

    if ((iCount == 0) || (szBasePath[iCount] != '/'))
    {
        httpcgi_errorOutput ("Could not figure out the base path directory", 14);
    }

    // cap the string at this point.
    szBasePath[iCount] = 0;

    // if this is running within an authenticated user environment, go for the configuration file in the directory.
    if (cEnvRemoteUser != 0)
    {
        strcpy (szConfigPath, szBasePath);
        strcat (szConfigPath, "/HQWAv");
        strcat (szConfigPath, gszVersionStamp);
        strcat (szConfigPath, ".conf");

        // load in the configuration file.
        iRet = futils_loadFileIntoMemory (szConfigPath, &gstruct_FileBuffGen);

        if (iRet != 0)
        {
            sprintf (szBuffer, "Could not load [%s]", szConfigPath);
            httpcgi_errorOutput (szBuffer, 16);
        }

        // get the base path for the unique user operation..
        if (futils_readLineFromMemoryNoEndLineCombo (&gstruct_FileBuffGen, szBasePath, 198) != 0)
        {
            sprintf (szBuffer, "Could not read base path from [%s]", szConfigPath);
            httpcgi_errorOutput (szBuffer, 17);
        }
        szBasePath[198] = 0;

        // rewrite the base path to where the authenticated user data is stored.
        strcat (szBasePath, "/");
        strcat (szBasePath, pszEnvRemoteUser);
    }

    // change to the base path directory.
    iRet = chdir (szBasePath);

    if (iRet != 0)
    {
        sprintf (szBuffer, "Could not change to [%s]", szBasePath);
        httpcgi_errorOutput (szBuffer, 21);
    }

    // look for the css override file.
    iRet = futils_loadFileIntoMemory ("user-css.conf", &gstruct_FileBuffGen);

    // if we could not load the css override file, put in a default.
    if (iRet != 0)
    {
        iRet = futils_addStringToFileBufferEnd ("body { font-family: \"Lucida Console\", Monaco, monospace;\ncolor: white;\nbackground-color: black }\n#past { color: rosybrown;\nbackground-color: black }\na { font-family: \"Lucida Console\", Monaco, monospace;\nfont-weight: bold;\ntext-decoration: underline;\ncolor: #EEE8AA;\nbackground-color: black }\n", &gstruct_FileBuffOut);
        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the default stylesheet", 24);
        }
    }
    // otherwise, use the contents of the file.
    else
    {
        iRet = futils_addStringToFileBufferEnd (gstruct_FileBuffGen.pcData, &gstruct_FileBuffOut);
        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the user stylesheet", 25);
        }
    }

    // end the style, along with the http header and start the body.
    iRet = futils_addStringToFileBufferEnd ("</style>\n</head>\n<body>\n", &gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the end of the header", 26);
    }

    // figure out what we are doing.. (cEnvMethod == 1 is a POST operation, 2 is a GET).
    if (cEnvMethod == 1)
    {
        iRet = httpcgi_extractEntry (pInputData, "menu=", szMenuValue, 38);

        if (iRet != 0)
        {
            iRet = httpcgi_extractEntry (pInputData, "game=", szMenuValue, 38);

            if (iRet == 0)
            {
                if (strcmp (szMenuValue, "Submit") == 0)
                {
                    iRet = httpcgi_extractEntry (pInputData, "track=", szTrackingId, 48);

                    if (iRet == 0)
                    {
                        iRet = httpcgi_extractEntry (pInputData, "sc=", szSceneId, 22);

                        if (iRet == 0)
                        {
                            if ((szSceneId[4] == '.') && ((int)strlen (szSceneId) > 5))
                            {
                                szSceneId[4] = 0;

                                iSceneId = atoi (szSceneId);
                                iSubSceneId = atoi (&szSceneId[5]);
                                iCount = 0;

                                while (1)
                                {
                                    if (gstructSceneList[iCount].iSceneId == -1)
                                        break;

                                    if (gstructSceneList[iCount].iSceneId == iSceneId)
                                    {
                                        iMainAction = 10;
                                        break;
                                    }

                                    iCount++;
                                }

                                if (iMainAction != 10)
                                {
                                    sprintf (szBuffer, "Invalid scene id %d", iSceneId);
                                    httpcgi_errorOutput (szBuffer, 41);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (strncmp (szMenuValue, "Start ", 6) == 0)
            {
                iMainAction = 12; // start a new game
            }
            else if (strncmp (szMenuValue, "Save S", 6) == 0)
            {
                iMainAction = 4; // save screen
            }
            else if (strncmp (szMenuValue, "Resume", 6) == 0)
            {
                iMainAction = 11; // restore last autosave
            }
            else if (strncmp (szMenuValue, "Load a", 6) == 0)
            {
                iMainAction = 3; // load screen
            }
            else if (strncmp (szMenuValue, "About ", 6) == 0)
            {
                iMainAction = 1; // about screen
            }
            else if (strncmp (szMenuValue, "HQWA s", 6) == 0)
            {
                iMainAction = 6; // Spoiler menu
            }
            else if (strncmp (szMenuValue, "HQWA c", 6) == 0)
            {
                iMainAction = 2; // credits screen
            }
            else if (strncmp (szMenuValue, "Slot ", 5) == 0)
            {
                if (strncmp (szMenuValue, "Slot 1", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 1; // save file 1
                }
                else if (strncmp (szMenuValue, "Slot 2", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 2; // save file 2
                }
                else if (strncmp (szMenuValue, "Slot 3", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 3; // save file 3
                }
                else if (strncmp (szMenuValue, "Slot 4", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 4; // save file 4
                }
                else if (strncmp (szMenuValue, "Slot 5", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 5; // save file 5
                }
                else if (strncmp (szMenuValue, "Slot 6", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 6; // save file 6
                }
                else if (strncmp (szMenuValue, "Slot 7", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 7; // save file 7
                }
                else if (strncmp (szMenuValue, "Slot 8", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 8; // save file 8
                }
                else if (strncmp (szMenuValue, "Slot 9", 6) == 0)
                {
                    iMainAction = 7; // load action
                    iSaveFile = 9; // save file 9
                }
            }
            else if (strncmp (szMenuValue, "Save t", 6) == 0)
            {
                if (strncmp (szMenuValue, "Save to slot 1", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 1; // save file 1
                }
                else if (strncmp (szMenuValue, "Save to slot 2", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 2; // save file 2
                }
                else if (strncmp (szMenuValue, "Save to slot 3", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 3; // save file 3
                }
                else if (strncmp (szMenuValue, "Save to slot 4", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 4; // save file 4
                }
                else if (strncmp (szMenuValue, "Save to slot 5", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 5; // save file 5
                }
                else if (strncmp (szMenuValue, "Save to slot 6", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 6; // save file 6
                }
                else if (strncmp (szMenuValue, "Save to slot 7", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 7; // save file 7
                }
                else if (strncmp (szMenuValue, "Save to slot 8", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 8; // save file 8
                }
                else if (strncmp (szMenuValue, "Save to slot 9", 14) == 0)
                {
                    iMainAction = 8; // save action
                    iSaveFile = 9; // save file 9
                }
            }
        }
    }

    // if this is the About menu..
    if ((cCompleteOutput == 0) && (iMainAction == 1))
    {
        menucgi_outputAboutMenu ();
        cCompleteOutput = 1;
    }

    // if this is the Credits menu..
    if ((cCompleteOutput == 0) && (iMainAction == 2))
    {
        menucgi_outputCreditsMenu ();
        cCompleteOutput = 1;
    }

    // if this is the Load menu..
    if ((cCompleteOutput == 0) && (iMainAction == 3))
    {
        menucgi_outputLoadMenu ();
        cCompleteOutput = 1;
    }

    // if this is the Save menu..
    if ((cCompleteOutput == 0) && (iMainAction == 4))
    {
        menucgi_outputSaveMenu ();
        cCompleteOutput = 1;
    }

    // if this is the Spoiler menu..
    if ((cCompleteOutput == 0) && (iMainAction == 6))
    {
        menucgi_outputSpoilersMenu ();
        cCompleteOutput = 1;
    }

    // this is the load action
    if ((cCompleteOutput == 0) && (iMainAction == 7))
    {
        sprintf (szBuffer, "cp HQWA.save%d.txt HQWA.autosave.txt", iSaveFile);

        iRet = system (szBuffer);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not rename save file to the autosave file.", 51);
        }

        // now that is complete, perform main action 11, which restores the game from the autosave.
        iMainAction = 11;
    }

    // this is the save action
    if ((cCompleteOutput == 0) && (iMainAction == 8))
    {
        sprintf (szBuffer, "cp HQWA.autosave.txt HQWA.save%d.txt", iSaveFile);

        iRet = system (szBuffer);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not rename autosave file to the save file.", 52);
        }

        // now that is complete, perform main action 11, which restores the game from the autosave.
        iMainAction = 11;
    }

    // if we have come this far without setting things up then we are due to alloc the system.
    if (cCompleteOutput == 0)
    {
        mdialog_initStaticList ();

        iRet = mapdata_checkAllMapData ();

        if (iRet != 0)
            httpcgi_errorOutput ("Error with mapdata init.", 100);

        iRet = actionstate_initInventoryPlusVars ();

        if (iRet != 0)
            httpcgi_errorOutput ("Error with inventory init.", 100);

        // init the random number generator
        srand ((unsigned) time (&tTime));
    }

    // if we are restoring the game from the last save, load the last save.
    if (((iMainAction == 10) || (iMainAction == 11)) && (cCompleteOutput == 0))
    {
        iRet = statefile_loadSaveFile ("HQWA.autosave.txt");

        if (iRet != 0)
        {
            iRet = futils_addStringToFileBufferEnd ("Error: Loading autosave file.<br/>(going back to main)<br/><br/>\n", &gstruct_FileBuffOut);
            if (iRet != 0)
            {
                httpcgi_errorOutput ("Could not buffer autosave warning", 104);
            }

            iMainAction = 0;
        }
    }

    // if we are acting upon a game continuation action, check it.
    if ((iMainAction == 10) && (cCompleteOutput == 0))
    {
        if (strcmp (szTrackingId, gszSessionTrackingId) != 0)
        {
            // if the tracking id is inconsistent, send the player back to the main menu with a warning.
            iRet = futils_addStringToFileBufferEnd ("Error: Tracking Id mismatch.<br/>(going back to main)<br/><br/>\n", &gstruct_FileBuffOut);
            if (iRet != 0)
            {
                httpcgi_errorOutput ("Could not buffer trackingid warning", 105);
            }

            iMainAction = 0;
        }
        else
        {
            cLock = 0;
            iPos = 0;

            for (iPos = 0; iPos < giCommandListUsed; iPos++)
            {
                if (gstruct_CommandList[iPos].cUseFlag == 0)
                    continue;

                if (gstruct_CommandList[iPos].iSceneId != iSceneId)
                    continue;

                if (gstruct_CommandList[iPos].iSubSceneId != iSubSceneId)
                    continue;

                cLock = 1;
                break;
            }

            if (cLock == 0)
            {
                // if the tracking id is inconsistent, send the player back to the main menu with a warning.
                iRet = futils_addStringToFileBufferEnd ("Error: Scene/Sub-Scene Id mismatch.<br/>(going back to main)<br/><br/>\n", &gstruct_FileBuffOut);
                if (iRet != 0)
                {
                    httpcgi_errorOutput ("Could not buffer sceneid warning", 106);
                }

                iMainAction = 0;
            }
        }
    }

    // if this is a start a new game.. start things off.
    if ((iMainAction == 12) && (cCompleteOutput == 0))
    {
        mutils_addToDialogBuffer ("<br/>\n");

        iSubSceneId = 0;
        iSceneId = 1001; // this is the start of the game.
        iCount = 0;

        while (1)
        {
            if (gstructSceneList[iCount].iSceneId == -1)
                break;

            if (gstructSceneList[iCount].iSceneId == 1001)
            {
                iMainAction = 10; // merge into the game continue action
                break;
            }

            iCount++;
        }

        if (iMainAction != 10)
        {
            httpcgi_errorOutput ("Could not find start scene id 1001.0", 107);
        }
    }

    // merge in game start and continue here.
    if ((iMainAction == 10) && (cCompleteOutput == 0))
    {
        // Note: iCount should still set from earlier.
        if (iCount == -1)
        {
            httpcgi_errorOutput ("Scene offset is missing", 109);
        }

        // To make it here means that we have a valid action to continue what we are doing.
        mutils_initAndClearCommandList ();
        mutils_addDialogToArchive (0);

        // this is where the actual referenced function is called.
        iRet = gstructSceneList[iCount].vFunc (iSubSceneId, 0);

        if (iRet != 0)
        {
            sprintf (szBuffer, "Return %d from Scene function %d.%d", iRet, iSceneId, iSubSceneId);
            httpcgi_errorOutput (szBuffer, 110);
        }

        iMainAction = 11; // merge into the restore last save action
    }

    // Here we work with the data that we have restored..
    if ((iMainAction == 11) && (cCompleteOutput == 0))
    {
        pid_t pidMe;

        pidMe = getpid ();

        // rebuild the tracking id.
        sprintf (gszSessionTrackingId, "%ld.%d", tTime, pidMe);

        // rewrite the autosave file.
        iRet = statefile_writeSaveFile ("HQWA.autosave.txt");

        if (iRet != 0)
            httpcgi_errorOutput ("Could not write the autosave file", 120);

        // now start shoving the updated dialog across into the HTTP output buffer.

        iRet = futils_addStringToFileBufferEnd ("<div id=\"past\">\n", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gpszArchiveBuffer, &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd ("</div>\n<div id=\"current\"/>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the archive text", 124);

        iRet = futils_addStringToFileBufferEnd (gpszDialogBuffer, &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the dialog text", 125);

        // if there are no commands, write out the main menu command buttons, and leave it at that.
        if (giCommandListUsed == 0)
        {
            menucgi_outputFullMenu (10);

            cCompleteOutput = 1;
        }
    }

    // if we are still working with start/continue/restored data, and we have actual command entries to work with.
    if ((iMainAction == 11) && (cCompleteOutput == 0))
    {
        iRet = futils_addStringToFileBufferEnd ("<hr>\n<script type=\"text/javascript\">\nfunction enableSubmit() {\n document.forms[\"nav\"][\"submit\"].disabled=false;\n}\n", &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the start of the javascript", 131);

        for (iPos = 0; iPos < giCommandListUsed; iPos++)
        {
            sprintf (szBuffer, "function sel%d%c%d() {\n document.forms[\"nav\"][\"%d%c%d\"].checked=true;\n document.forms[\"nav\"][\"submit\"].disabled=false;\n}\n",
                    (int)gstruct_CommandList[iPos].iSceneId, 'w', (int)gstruct_CommandList[iPos].iSubSceneId,
                    (int)gstruct_CommandList[iPos].iSceneId, '.', (int)gstruct_CommandList[iPos].iSubSceneId);

            iRet = futils_addStringToFileBufferEnd (szBuffer, &gstruct_FileBuffOut);

            if (iRet != 0)
                httpcgi_errorOutput ("Could not buffer menu entry into the javascript section", 132);
        }

        iRet = futils_addStringToFileBufferEnd ("</script>\n<form id=\"nav\" action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n <input type=\"hidden\" name=\"track\" value=\"", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszSessionTrackingId, &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd ("\" />\n", &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the start of the form section", 135);

        for (iPos = 0; iPos < giCommandListUsed; iPos++)
        {
            sprintf (szBuffer, " <input type=\"radio\" id=\"%d%c%d\" name=\"sc\" onchange=\"enableSubmit()\" value=\"%d%c%d\"><a href=\"javascript:void(0);\" onclick=\"sel%d%c%d()\" />%s</a><br>\n",
                    (int)gstruct_CommandList[iPos].iSceneId, '.', (int)gstruct_CommandList[iPos].iSubSceneId,
                    (int)gstruct_CommandList[iPos].iSceneId, '.', (int)gstruct_CommandList[iPos].iSubSceneId,
                    (int)gstruct_CommandList[iPos].iSceneId, 'w', (int)gstruct_CommandList[iPos].iSubSceneId,
                    gstruct_CommandList[iPos].pszCommand);

            iRet = futils_addStringToFileBufferEnd (szBuffer, &gstruct_FileBuffOut);

            if (iRet != 0)
                httpcgi_errorOutput ("Could not buffer menu entry into the form section", 136);
        }

        iRet = futils_addStringToFileBufferEnd (" <input type=\"submit\" id=\"submit\" name=\"game\" value=\"Submit\" disabled>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the end of the form section", 137);

        iRet = futils_addStringToFileBufferEnd ("<hr>\n<center>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n <input type=\"submit\" name=\"menu\" value=\"Save Screen\" />\n <input type=\"submit\" name=\"menu\" value=\"Main Menu\" />\n</form>\n</center>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
            httpcgi_errorOutput ("Could not buffer the end mini-menu", 140);

        cCompleteOutput = 1;
    }

    // default is to dump out the main menu.
    if (cCompleteOutput == 0)
    {
        menucgi_outputMainMenu ();
        cCompleteOutput = 1;
    }

    // cap the end of the HTML document.
    iRet = futils_addStringToFileBufferEnd ("</body>\n</html>\n", &gstruct_FileBuffOut);
    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the end of the document", 999);
    }

    // output the HTML document, and we have finished.
    fputs (gstruct_FileBuffOut.pcData, stdout);
    return 0;
}


