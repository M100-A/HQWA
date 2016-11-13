//
// gamelogic00.c
//
// This is group 0 of scene ids.
//
// Essentially, this is the main menu display of the program.
//

#include "common.h"
#include "gamelogic.h"

// external linkage to the game variables.

extern  char    gcDebugFlag;

extern  char    gcClearToStartFlag;


//
// Main Menu Scene function.
//
int gamelogic00_scene0000 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer (">Main Menu\n\nHedonism Quest, Wilda\'s Ascension (HQWA). Version 0.71\n\nLicense:CC BY 4.0 (type \"credits\" and press \"Enter\" to see more)\n\nThis text game has heavy adult and sexual content and is not meant for minors. At bare minimum, you should be above the \"age of consent\" to play this game. If you don\'t know what \"age of consent\" is, then exit now.\n\nTo exit this game.. Type \"exit\" and press the \"Enter\" key, or hold down the \"Ctrl\" key and press the \"Q\" key.\n\nIf you want help about the interface, or detail about other keyboard shortcuts, type \"help\" below and press the \"Enter\" key.\n\n");
    if (iRet != 0) return iRet;

    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Start new game", 1001, 0);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToCommandList ("Startup Error, Scroll up to see", 9, 0);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Help", 1, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Exit", 9, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("About Hedonism Quest, Wilda\'s Ascension", 2, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Load previous game", 4, 0);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// Help screen Scene function.
//
int gamelogic00_scene0001 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer (">Help\n\nNote: the bundled \"HQWA Help.pdf\" has a better description of this interface, and screen-shots.\n\nThere are 3 keyboard shortcuts:\n\nCtrl-Q and Ctrl-C is the quick exit from the game. This will NOT save your current game state.\n\nCtrl-S accesses the save menu, where you can save your current game in a save slot, then continue playing.\n\nCtrl-U returns you to the main menu. This will NOT save your current game state.\n\nIf you want to load a previously saved game, then go to the \"Main Menu\" (using Ctrl-U) and access the \"Load previous game\" menu selection.\n\nUse the \"Start new game\" from the \"Main Menu\" to start a new game.\n\nThe program interface has 3 modes, Text-scroll, Direct-input and Arrow-selection.\n\n\n::Text-scroll\n\nThis is where there is more text to be shown to the user than can fit in the screen window.\n\nYou can tell when you are in \"text-scroll mode\" by the inverted <more> in the bottom right corner of the window.\n\nYou can resize the screen window at anytime.\n\nYou can also \"scroll up\" into \"dim text\". The dimmed text is the previous actions/events that has happened. The game will only hold onto 64-kilobytes of previous text actions, so only the reasonably recent events/actions will be remembered. Those events/actions are included in the save files, and restored when those files are loaded.\n\nYou can jump to the bottom of text using the \"end\" key, and to the top of the current text using the \"home\" key.\n\nYou can scroll the text up and down using the up and down arrow keys, as well as the page-up and page-down keys.\n\n\n::Direct-input\n\nThis is the default command entry mode (unless you are using the -t command line switch when starting the program, then the default is \"Arrow-selection\")\n\nYou can tell when you are in \"direct input mode\" when the input caret (>) is bold. The other giveaway is the fact that the interface is telling you how many commands can match on this action input.\n\nThe program has an auto-complete function, where you type the first single, or number of letters, and it narrows down the matches.\n\nFor example: when the game is allowing you to navigate, \"n\", \"e\", \"s\" and \"w\" is all you need to enter to select \"north\", \"east\", \"south\" and \"west\", because there are no other actions that begin with those characters.\n\nThe help PDF has a better explanation of this.\n\nThe \"delete\" and \"backspace\" keys can be used to erase characters. Left and right arrows both enable you to navigate into an entered command. But it is far easier to use \"Arrow-selection\", if not the auto-complete function to enter commands.\n\n\n::Arrow-selection\n\nThis used to be called \"Tab-selection\" because the hot-key to get into and out of this is to use the tab key. Once in \"Tab-selection\" mode, the up-down and left-right arrow keys are used to select between the potential commands.\n\nIf no characters were entered in \"Direct-input\" mode, then the entire list will be there.\n\nThe help PDF has a better explanation of this.\n\nThis is the bottom of the help page. Below should be an entry prompt (keep scrolling, you will see it) were you can return to the main menu, or you can go to either the \"About\" or \"Credits\" pages.\n\n");
    if (iRet != 0) return iRet;

    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Start new game", 1001, 0);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToCommandList ("Startup Error, Scroll up to see", 9, 0);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("About Hedonism Quest, Wilda\'s Ascension", 2, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Load previous game", 4, 0);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// About screen Scene function.
//
int gamelogic00_scene0002 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer (">About Hedonism Quest, Wilda\'s Ascension\n\nThis is an interactive-fiction-like text novel game, except that the interface is a little different. Details about the interface are described over in the help page.\n\nThis page is about the game story. This is adult fiction, which is rather heavy on sexual references and encounters.\n\n\nStoryline subjects:\n\nTags, according to http://pastebin.com/Su7gb2iq\n[Lct]= Lactation\n[Mtc]= Mental change\n[Mdc]= Mind Control/Hypnosis\n[Prg]= Pregnancy\n[Tcl]= Tentacles\n\nThere is also Latex, Masturbation, Female on Female, and Dirty Language.\n\n\nDevelopment:\n\nAs a project, development commenced on Thursday 18th August 2016.\nThe first release was on Saturday 17th September 2016.\nThe DEVELOPMENT file has more detail.\n\n\nUse of of the CURSES API:\n\nCURSES was picked because it is multi-computer-platform capable. It is multi-platform only because some nice people have created Windows interface replacement versions of the CURSES API. CURSES is available for free. If the development libraries for CURSES are not supplied as part of the operating system, they can be downloaded and installed.\n\nCURSES itself is related to the entire concept of a command line interface. Command line interface programs are not going away anytime soon and they will stick around as long as the various flavors of *NIXes (including Linux) continue to exist.\n\n");
    if (iRet != 0) return iRet;

    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Start new game", 1001, 0);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToCommandList ("Startup Error, Scroll up to see", 9, 0);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Help", 1, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Load previous game", 4, 0);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// Credits screen Scene function.
//
int gamelogic00_scene0003 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer (">Credits\n\nHedonism Quest, Wilda\'s Ascension (HQWA) is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0).\n\nhttp://creativecommons.org/licenses/by/4.0/\n..and..\n(LICENSE file) http://creativecommons.org/licenses/by/4.0/legalcode\n\nIf you take this game and/or story, modify it (or translate it into another language), you need to leave everything on this credit page alone and add your own details to it (of course).\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToDialogBuffer ("Concept, dialog and code was originally by M100.\nThanks to the participants on the #/d/evs rizon.net IRC channel for guidance, as well as putting up with occasional ranting while making this.\nThanks to the participants on the #hypno rizon.net IRC channel for the inspiration.\n\n");
    if (iRet != 0) return iRet;

    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Start new game", 1001, 0);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToCommandList ("Startup Error, Scroll up to see", 9, 0);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Help", 1, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("About Hedonism Quest, Wilda\'s Ascension", 2, 0);
    if (iRet != 0) return iRet;
    if (gcClearToStartFlag == 1)
    {
        iRet = mutils_addToCommandList ("Load previous game", 4, 0);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// Load games Scene function.
//
int gamelogic00_scene0004 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iOffset;
    char cLock = FALSE;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer (">Load Previous Game\n\n");
    if (iRet != 0) return iRet;

    for (iOffset = 0; iOffset < 9; iOffset++)
    {
        char    szDateTime[30];
        char    szInputString[100];

        szDateTime[0] = 0;

        sprintf (szInputString, "save%d.txt", iOffset + 1);

        iRet = statefile_parseSaveFile (szInputString, szDateTime);

        if (iRet == 1)
        {
            sprintf (szInputString, "Slot %d is invalid (%s) !\n", iOffset + 1, szDateTime);
        }
        else if (iRet == 0)
        {
            sprintf (szInputString, "Load from slot %d", iOffset + 1);

            iRet = mutils_addToCommandList (szInputString, 5, iOffset);

            sprintf (szInputString, "Slot %d was saved: %s\n", iOffset + 1, szDateTime);

            cLock = TRUE;
        }
        else // iRet == 2
        {
            sprintf (szInputString, "Slot %d is empty.\n", iOffset + 1);
        }

        iRet = mutils_addToDialogBuffer (szInputString);
        if (iRet != 0) return iRet;
    }

    if (cLock == FALSE)
    {
        iRet = mutils_addToDialogBuffer ("\nThere are NO valid saves to load !\n\n");
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("\nSelect from one of the above save files, or just return to the main menu.\n\n");
        if (iRet != 0) return iRet;
    }

    //Note: Scene id 5 is special and does not exist in the lookup table. The main function looks out for it and loads up whatever is at the memory offset.

    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    if (iRet != 0) return iRet;

    return 0;
}

//
// Game exit function.
//
int gamelogic00_scene0009 (int iSubSceneId, char cSubFlag)
{
    // exit curses mode..
#ifndef __PDCURSES__
    //
    // Why knock out the use of endwin() for PDCURSES??.. well it crashes if I leave it in.
    //
    endwin();
#endif

    // exit the program.. it's that simple..
    exit (0);
}



