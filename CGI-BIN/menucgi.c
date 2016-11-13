//
// menucgi.c
//
// menus for the CGI-BIN version..
//

#include "common.h"

//
// In the CURSES version, the main menus are in gamelogic00.c.
//
// In the CGI-BIN version, because I am not using the main game
// interface functions for the main menus, I do them differently,
// so these are away from the gamelogic listings.
//
// gamelogic00.c is removed in the CGI-BIN version of the program.
//

// storage of the file load structure..
extern  struct	futils_filebuff         gstruct_FileBuffOut;

// this is the debug output flag
extern  char    gszVersionStamp[20];

// this is the debug output flag
extern  char    gcDebugFlag;


//
// Function to output the full selection menu.
//
// Assumes that the gstruct_FileBuffOut is setup and partially loaded with HTTP and HTML header information.
// Also assumes that the CWD has been set to where the user data files are.
//
// 0 = main menu config.
// 1 = about menu config.
// 2 = load menu config.
// 3 = credits menu config.
// 4 = spoiler menu config.
// 10 = end game menu config.
//
void menucgi_outputFullMenu (int iRestrict)
{
    int iRet;
    struct stat statFile;

    // About HQWA, menu.

    if (iRestrict != 1)
    {
        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"About HQWA\" /> for information about this game, such as what it is about.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the About menu link", 801);
        }
    }

    if (iRestrict != 10)
    {
        // Start a new HQWA game, menu.

        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Start a new HQWA game\" /> to start a new game.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the start menu link", 802);
        }

        // Resume last HQWA autosave, menu.

        // this entry is always there..

        iRet = stat ("HQWA.autosave.txt", &statFile);

        if (iRet == 0)
        {
            iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

            if (iRet == 0)
                iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

            if ((iRet == 0) && (gcDebugFlag != 0))
                iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

            if (iRet == 0)
                iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Resume last HQWA autosave\" /> to pickup where you last left off.<br/>\n</form>\n", &gstruct_FileBuffOut);

            if (iRet != 0)
            {
                httpcgi_errorOutput ("Could not buffer the autosave load menu link", 803);
            }
        }

        // Load a previously saved HQWA game, menu.

        if (iRestrict != 2)
        {

            // Ok, rather simple, stat every single file name combo..

            iRet = stat ("HQWA.save1.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save2.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save3.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save4.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save5.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save6.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save7.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save8.txt", &statFile);

            if (iRet != 0)
                iRet = stat ("HQWA.save9.txt", &statFile);

            // if none of the save files exist, then don't render the menu entry.

            if (iRet == 0)
            {
                iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

                if (iRet == 0)
                    iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

                if ((iRet == 0) && (gcDebugFlag != 0))
                    iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

                if (iRet == 0)
                    iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Load a previously saved HQWA game\" /> to load a game save you put aside.<br/>\n</form>\n", &gstruct_FileBuffOut);

                if (iRet != 0)
                {
                    httpcgi_errorOutput ("Could not buffer the save load menu link", 804);
                }
            }
        }
    }

    // HQWA credits, menu.

    if (iRestrict != 3)
    {
        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"HQWA credits\" /> for people involved.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the credits menu link", 805);
        }
    }

    // HQWA spoiler, menu.

    if (iRestrict != 4)
    {
        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"HQWA spoilers\" /> Hints, tips, spoilers and cheats.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the credits menu link", 806);
        }
    }

    // HQWA main menu, menu.

    if (iRestrict != 0)
    {
        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

        if ((iRet == 0) && (gcDebugFlag != 0))
            iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);

        if (iRet == 0)
            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"HQWA main menu\" /> to go back to the main menu.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the main menu link", 807);
        }
    }
    else // Back to the list of games, menu.
    {
        iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"main.cgi\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Back to the list of games\" /> to back to the main list.<br/>\n</form>\n", &gstruct_FileBuffOut);

        if (iRet != 0)
        {
            httpcgi_errorOutput ("Could not buffer the game menu link", 808);
        }
    }
}


//
// Function to output the main menu.
//
// Assumes that the gstruct_FileBuffOut is setup and partially loaded with HTTP and HTML header information.
// Also assumes that the CWD has been set to where the user data files are.
//
void menucgi_outputMainMenu ()
{
    int iRet;

    iRet = futils_addStringToFileBufferEnd ("Hedonism Quest, Wilda&apos;s Ascension (HQWA). Version ", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

    if ((iRet == 0) && (gcDebugFlag != 0))
        iRet = futils_addStringToFileBufferEnd (" #CHEAT-MODE-ON", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<br/><br/>\nLicense: <a href=\"http://creativecommons.org/licenses/by/4.0/legalcode\">CC BY 4.0</a><br/><br/>\nThis text game has heavy adult and sexual content and is not meant for minors. At bare minimum, you should be above the &quot;age of consent&quot; to play this game. If you don&apos;t know what &quot;age of consent&quot; is, then close the web browser now.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game main text", 810);
    }

    menucgi_outputFullMenu (0);
}


//
// Function to output the about menu.
//

void menucgi_outputAboutMenu ()
{
    int iRet;

    iRet = futils_addStringToFileBufferEnd ("HQWA is a very simple &apos;interactive-fiction-like&apos; text novel game. This is also a piece of adult fiction, and has some heavy sexual references.<br/><br/>\n<b>Storyline subjects/themes:</b><br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Tags, according to <a href=\"http://pastebin.com/Su7gb2iq\">http://pastebin.com/Su7gb2iq</a><br/>\n[Lct]= Lactation (recurring)<br/>\n[Mtc]= Mental change (progression)<br/>\n[Mdc]= Mind Control/Hypnosis (progression)<br/>\n[Prg]= Pregnancy (recurring)<br/>\n[Tcl]= Tentacles (recurring)<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("There is also Latex (recurring), Masturbation (recurring), Female on Female (recurring), Dirty Language (recurring), and Tentacle Monster Sex (recurring).<br/><br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<b>Game play notes:</b><br/><br/>\nThe PC (Wilda) is given a job to retrieve an artifact from the dungeon below a destroyed temple. The PC can use the pre-payment for the job to buy new gear, before heading to the dungeon. Once the PC goes in, she is not going to come back out till she reaches the goal.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("The first menu selection, defines the difficulty level (easy, medium or hard).<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Use the &apos;Inventory and status&apos; menu selection to manage equipment and to see the character stats.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Navigation within the dungeon is using the traditional &apos;North&apos;, &apos;East&apos;, &apos;South&apos; and &apos;West&apos; menu selections.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<br/><b>ChangeLog:</b><br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<b># Version 0.71 - Sunday 13th November 2016</b><br/>Minor dialog fixes.<br/>Some more dialog fixes.<br/>Resolved an issue that showed up for only the CGI-BIN version, where it wasn't possible to restore a save at the end of the game.<br/>Included a spoilers menu page for the CGI-BIN version.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<b># Version 0.70 - Tuesday 1st November 2016</b><br/>First web server version, which included lots of dialog fixes, game logic fixes, and including the search/replace tag functions (necessary for the web server version).<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game about text", 812);
    }

    menucgi_outputFullMenu (1);
}


//
// Function to output the credits menu.
//

void menucgi_outputCreditsMenu ()
{
    int iRet;

    iRet = futils_addStringToFileBufferEnd ("Hedonism Quest, Wilda&apos;s Ascension (HQWA) is licensed under the Creative Commons Attribution 4.0 International license (CC BY 4.0).<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<a href=\"http://creativecommons.org/licenses/by/4.0/\">http://creativecommons.org/licenses/by/4.0/</a><br/>..and..<br/><a href=\"http://creativecommons.org/licenses/by/4.0/legalcode\">http://creativecommons.org/licenses/by/4.0/legalcode</a><br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("As a project, development commenced on Thursday 18th August 2016.<br/>First release (CURSES version) was on Saturday 17th September 2016.<br/><br/>\nIf you take this game and/or story, modify it (or translate it into another language), you need to leave everything on this credit page alone and add your own details to it (of course).<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Concept, dialog and code was originally by M100.<br/><br/>\nThanks to the participants on the #/d/evs rizon.net IRC channel for guidance, as well as putting up with occasional ranting while making this.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Thanks to the participants on the #hypno rizon.net IRC channel for the inspiration.<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game credits text", 814);
    }

    menucgi_outputFullMenu (3);
}


//
// Function to output the spoilers menu.
//

void menucgi_outputSpoilersMenu ()
{
    int iRet;

    iRet = futils_addStringToFileBufferEnd ("<b>There be spoilers here...</b><br/><br/>The purpose of this page is to provide some hints for Hedonism Quest, Wilda&apos;s Ascension (HQWA). This was created after a 4chan/d /dgg/ query about how to move around, so I decided it would be better for everyone that this detail visible to everyone (plus some more). Primarily because the thread that I posted the comments in is going to be archived and will disappear.<br/><br/>If you don&apos;t want to ruin the experience for yourself, then use the back button now. The information below contains spoilers about the storyline.<br/><br/>If you get lost inside the dungeon (and that isn&apos;t hard, if you are not used to navigating using &quot;description&quot; alone) the maps for the all 3 variants of the dungeon can be found over in the <a href=\"https://github.com/M100-A/HQWA/releases\">releases</a> location for the CURSES version of HQWA.<br/><br/>", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Map set 1 is for easy mode, Map set 2 is for medium mode and Map set 3 is for hard mode. In easy mode, there is a comment when you are at a location where there is a blockage. In medium and hard modes there are no such comments. The replaced maps don't just change the layout, they increase the likelihood of running into monsters at specific locations.<br/><br/>What the maps show is that there are &quot;blockages&quot;. What they do not show are the positions on the map where the PC has to go to &quot;unlock the blockages&quot;. To get past some blockages, you might need to unblock another blockage first. If you want to know exactly where the &quot;hot locations&quot; are on the map to unlock the blockages, look at the <a href=\"https://github.com/M100-A/HQWA\">source code</a>, specifically at the mapdata.c listing. The comments on the map id positions give away that there are events at those positions. The ones with a \"Clk\" value set to something other than 0, are the positions that control the &quot;blockages&quot;.<br/><br/>", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Letting your Stamina hit 0 means a game over. With each monster encounter, your Endurance increases (which defines the maximum amount of Stamina). Your Endurance also increases naturally when you transition between storyline parts. Your Stamina decreases as you walk around the dungeon, so wondering around aimlessly will eventually lead to your demise. Letting your Stamina decrease and your lust rise can result in the PC being less effective during monster combat.<br/><br/>Your equipment becomes less effective the more you use it. Effectiveness is useful for both combat and appearing to be aggressive.<br/><br/>In regards to fighting monsters. The only &quot;fight to the death&quot; is the first monster encounter. After that, all of the &quot;random&quot; monster encounters during Part 1 and Part 2 (up to meeting Crystal and Daisy) the monsters will tend to run away. With that first battle, the PC is going to have to go &quot;all out&quot; because that first monster will NOT run away. During subsequent battles, the PC can be more defensive.<br/><br/>From Part 3 and onwards it is straight sex with the monsters. Traveling with Crystal is important. If you want to preserve your own Stamina, you need to invite her to participate in the monster sex, decreasing your own Stamina hit as a result (60%). You can ask Crystal for her guidance, but once you ask her too much, that is it, you won't ask for her help anymore (meaning you are going to be facing monsters alone as well).<br/><br/>", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("You are on your own in Part 4, but there are no pathway blockages. The game story reaches its conclusion at the end of Part 4.<br/><br/>Only during Part 1 do you have &quot;Stamina Elixirs&quot; in your inventory. You cannot swap over inventory items past Part 1 either. The only use of &quot;Inventory and status&quot; beyond Part 1 is to look at your stats.<br/><br/>", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("<br/><b>Cheat/Debug mode:</b><br/><br/>The CURSES version has this via the -D command line switch.<br/><br/>The web server version does the same thing by altering the URL.<br/><br/>In the address bar of the web browser is a path to the program. When not in &quot;cheat&quot; mode it will be &quot;HQWAv", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd (".cgi&quot;. To activate the &quot;cheat&quot; mode, change the &quot;.cgi&quot; part of the address to &quot;.cheat.cgi&quot;. Doing so will take you back to the main menu, but you will see a notice at the end of the version number at the top of the main menu it will say &quot;#CHEAT-MODE-ON&quot;. The program will maintain the path to the &quot;.cheat.cgi&quot; until you exit &apos;back to the list of games&apos; menu, or you alter the address again.<br/><br/>Within HQWA, the debug/cheat mode turns on debug statements that constantly tell you what map and position you are at. It also tells you about the evaluation for a random monster encounter, and the stats of that monster when the encounter starts. Monsters bail-out of combat early because of their high level of fear. Your actions affect your karma levels, so it gives you an unfair advantage to predict what the monster is about to do, and increase your karma stats as a result.<br/><br/>You are welcome.<br/><br/>M100<br/><br/>", &gstruct_FileBuffOut);

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game spoilers text", 815);
    }

    menucgi_outputFullMenu (4);
}


//
// Function to output the save slot menu.
//

void menucgi_outputSaveMenu ()
{
    int iRet;
    int iSaveRet;
    int iCount;
    char szDateCounter[30];
    char szSavePath[30];

    iRet = futils_addStringToFileBufferEnd ("<script language=\"javascript\">\nfunction convdt(dt) {\nvar cnvDate = new Date(0);\ncnvDate.setUTCSeconds(dt);\ndocument.write(cnvDate.toLocaleString());\n}\n</script>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Pick a slot to save your game in:<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
    {
        for (iCount = 0; iCount < 9; iCount++)
        {
            iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);
            if (iRet != 0) break;

            iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);
            if (iRet != 0) break;

            if (gcDebugFlag != 0)
            {
                iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }

            iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Save to slot ", &gstruct_FileBuffOut);
            if (iRet != 0) break;

            sprintf (szSavePath, "%d", iCount + 1);

            iRet = futils_addStringToFileBufferEnd (szSavePath, &gstruct_FileBuffOut);
            if (iRet != 0) break;

            iRet = futils_addStringToFileBufferEnd ("\" />", &gstruct_FileBuffOut);
            if (iRet != 0) break;

            sprintf (szSavePath, "HQWA.save%d.txt", iCount + 1);

            iSaveRet = statefile_parseSaveFile (szSavePath, szDateCounter);

            if (iSaveRet == 2)
            {
                iRet = futils_addStringToFileBufferEnd (" is currently empty.<br/>\n</form>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
            else if (iSaveRet == 1)
            {
                iRet = futils_addStringToFileBufferEnd (" is invalid (\n<script language=\"javascript\">\nconvdt(", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (szDateCounter, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (");\n</script>\n).<br/>\n</form>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
            else // iSaveRet == 0
            {
                iRet = futils_addStringToFileBufferEnd (" was saved \n<script language=\"javascript\">\nconvdt(", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (szDateCounter, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (");\n</script>\n.<br/>\n</form>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
        }
    }

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game save text", 816);
    }

    menucgi_outputFullMenu (2);
}


//
// Function to output the load slot menu.
//

void menucgi_outputLoadMenu ()
{
    int iRet;
    int iSaveRet;
    int iCount;
    char szDateCounter[30];
    char szSavePath[30];

    iRet = futils_addStringToFileBufferEnd ("<script language=\"javascript\">\nfunction convdt(dt) {\nvar cnvDate = new Date(0);\ncnvDate.setUTCSeconds(dt);\ndocument.write(cnvDate.toLocaleString());\n}\n</script>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
        iRet = futils_addStringToFileBufferEnd ("Pick a slot to load from:<br/><br/>\n", &gstruct_FileBuffOut);

    if (iRet == 0)
    {
        for (iCount = 0; iCount < 9; iCount++)
        {
            sprintf (szSavePath, "HQWA.save%d.txt", iCount + 1);

            iSaveRet = statefile_parseSaveFile (szSavePath, szDateCounter);

            sprintf (szSavePath, "%d", iCount + 1);

            if (iSaveRet == 2)
            {
                iRet = futils_addStringToFileBufferEnd ("<hr/>\nSlot ", &gstruct_FileBuffOut);

                iRet = futils_addStringToFileBufferEnd (szSavePath, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (" is currently empty.<br/>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
            else if (iSaveRet == 1)
            {
                iRet = futils_addStringToFileBufferEnd ("<hr/>\nSlot ", &gstruct_FileBuffOut);

                iRet = futils_addStringToFileBufferEnd (szSavePath, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (" is invalid (\n<script language=\"javascript\">\nconvdt(", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (szDateCounter, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (");\n</script>\n).<br/>\n</form>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
            else // iSaveRet == 0
            {
                iRet = futils_addStringToFileBufferEnd ("<hr/>\n<form action=\"HQWAv", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (gszVersionStamp, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                if (gcDebugFlag != 0)
                {
                    iRet = futils_addStringToFileBufferEnd (".cheat", &gstruct_FileBuffOut);
                    if (iRet != 0) break;
                }

                iRet = futils_addStringToFileBufferEnd (".cgi#current\" method=\"POST\">\n<input type=\"submit\" name=\"menu\" value=\"Slot ", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                sprintf (szSavePath, "%d", iCount + 1);

                iRet = futils_addStringToFileBufferEnd (szSavePath, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd ("\" /> was saved \n<script language=\"javascript\">\nconvdt(", &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (szDateCounter, &gstruct_FileBuffOut);
                if (iRet != 0) break;

                iRet = futils_addStringToFileBufferEnd (");\n</script>\n.<br/>\n</form>\n", &gstruct_FileBuffOut);
                if (iRet != 0) break;
            }
        }
    }

    if (iRet != 0)
    {
        httpcgi_errorOutput ("Could not buffer the game load text", 818);
    }

    menucgi_outputFullMenu (2);
}


