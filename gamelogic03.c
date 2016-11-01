//
// gamelogic03.c
//
// This is group 3 of scene ids.
//
// Essentially, this is the all of the inventory management of the game
// (which is rather limited).
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"

// external linkage to the game variables.
extern  char    gcDebugFlag;

// linkage to the actionstate data.
extern  struct  actionstate_invdescription gstructInventoryDescription[];
extern  struct  actionstate_inventory *gpstructActStateInventory;
extern  short   gsActStateInventorySize;
extern  struct  actionstate_charstats gstructActStateCharWilda;
extern  struct  actionstate_charstats gstructActStateCharCrystal;
extern  struct  actionstate_globalvars gstructActStateGlobal;

//
// Setup/Continue the inventory and status.
//
int gamelogic03_scene1030 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[400];
    char szWorking2[32];
    short sOffset1;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        iRet = mdialog_addToDialogWithSrchRep (">Inventory and status\n\n");
        if (iRet != 0) return iRet;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# opens her backpack and checks the contents.\n\n");
        if (iRet != 0) return iRet;
    }

    if (gstructActStateGlobal.sActId == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("In her leather backpack, #!00# currently has:\n");
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[1].sCount == 1)
            iRet = mdialog_addToDialogWithSrchRep ("1 gold piece.\n");
        else
        {
            sprintf (szWorking, "%d gold pieces.\n", (int) gpstructActStateInventory[1].sCount);
            iRet = mdialog_addToDialogWithSrchRep (szWorking);
        }
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[2].sCount != 0)
        {
            if (gpstructActStateInventory[2].sCount == 1)
                iRet = mdialog_addToDialogWithSrchRep ("1 stamina elixir.\n");
            else
            {
                sprintf (szWorking, "%d stamina elixirs.\n", (int) gpstructActStateInventory[2].sCount);
                iRet = mdialog_addToDialogWithSrchRep (szWorking);
            }
            if (iRet != 0) return iRet;
        }

        sprintf (szWorking, "%d torches.\n", (int) gpstructActStateInventory[22].sCount);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;

        iRet = mdialog_addToDialogWithSrchRep ("1 yo-yo (childhood keepsake).\n1 \'holy artifact\' from #!01#, that looks like a dildo, in a box.\n");
        if (iRet != 0) return iRet;
    }
    else if (gstructActStateGlobal.sActId == 2)
    {
        iRet = mdialog_addToDialogWithSrchRep ("In her latex backpack, #!00# currently has:\n0 gold pieces (there will be more when the job is done).\n0 yo-yos (that was from #!00#\'s uncle, damnit).\n");
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[26].sCount != 0)
        {
            iRet = mdialog_addToDialogWithSrchRep ("1 \'holy artifact\', that looks like a dildo, in a box.\n");
            if (iRet != 0) return iRet;
        }
    }
    else if (gstructActStateGlobal.sActId == 3)
    {
        iRet = mdialog_addToDialogWithSrchRep ("In her latex backpack, #!00# currently has:\n0 gold pieces (which isn\'t a big deal right now).\n");
        if (iRet != 0) return iRet;
    }
    else // actid = 4
    {
        iRet = mdialog_addToDialogWithSrchRep ("In her latex backpack, #!00# currently has:\n0 gold pieces (but, who cares about that).\n1 \'holy artifact\' from #!06#, a dildo in a box.\n");
        if (iRet != 0) return iRet;
    }

    // scan the inventory list for things with effectiveness settings.
    for (sOffset1 = 0; (gsActStateInventorySize + 1) > sOffset1; sOffset1++)
    {
        if (gstructInventoryDescription[sOffset1].cEffectivenessFlag == 0)
            continue;

        if (gpstructActStateInventory[sOffset1].sCount == 0)
            continue;

        sprintf (szWorking, "%0.3f", (double)gpstructActStateInventory[sOffset1].structEff.fFraction);
        sprintf (szWorking2, "%d%s", gpstructActStateInventory[sOffset1].structEff.iNum, &szWorking[1]);
        if (sOffset1 > 11)
            sprintf (szWorking, "1 pair of (%s) %s.\n", szWorking2, gstructInventoryDescription[sOffset1].pszName);
        else
            sprintf (szWorking, "1 (%s) %s.\n", szWorking2, gstructInventoryDescription[sOffset1].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

    // and one final thing for act 1.
    if (gstructActStateGlobal.sActId == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("And, 1 leather bivouac sack, attached to the outside of the backpack.\n");
        if (iRet != 0) return iRet;
    }

    iRet = mdialog_addToDialogWithSrchRep ("\n#!00# also is currently:\n");
    if (iRet != 0) return iRet;

    if (gstructActStateCharWilda.sSlotW != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structW.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structW.iNum, &szWorking[1]);
        if (gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName[0] == 'i')
            sprintf (szWorking, "Holding an (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName);
        else
            sprintf (szWorking, "Holding a (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateGlobal.sActId == 1)
    {
        if (gstructActStateGlobal.cEnteredDungeon != 0)
        {
            iRet = mdialog_addToDialogWithSrchRep ("Holding a lit torch.\n");
            if (iRet != 0) return iRet;
        }
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("Holding an aquamarine lantern.\n");
        if (iRet != 0) return iRet;
    }

    if (gstructActStateCharWilda.sSlotC != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structC.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structC.iNum, &szWorking[1]);
        if (gstructInventoryDescription[gstructActStateCharWilda.sSlotC].pszName[0] == 'o')
            sprintf (szWorking, "Wearing an (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotC].pszName);
        else
            sprintf (szWorking, "Wearing a (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotC].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateCharWilda.sSlotB != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structB.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structB.iNum, &szWorking[1]);
        sprintf (szWorking, "Wearing a pair of (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateCharWilda.sSlotG != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structG.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structG.iNum, &szWorking[1]);
        sprintf (szWorking, "Wearing a pair of (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotG].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

#ifdef INTERFACE_CURSES
    // now for the character statistics
    if (gstructActStateGlobal.sActId == 3)
    {
        iRet = mdialog_addToDialogWithSrchRep ("\nStatistics:    #!00#:  #!03#:\n");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        sprintf (szWorking, "Endurance   %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structE.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structE.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        sprintf (szWorking, "Stamina     %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structS.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structS.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        sprintf (szWorking, "Might       %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structM.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structM.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        sprintf (szWorking, "Karma       %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structK.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structK.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        sprintf (szWorking, "Frigidity   %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structF.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structF.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        sprintf (szWorking, "Lust        %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structL.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structL.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        sprintf (szWorking, "Reflexes    %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structR.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structR.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        sprintf (szWorking, "Oral Exp    %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structO.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structO.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        sprintf (szWorking, "Vaginal Exp %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structV.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structV.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        sprintf (szWorking, "Anal Exp    %9s", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structA.fFraction);
        sprintf (szWorking2, " %5d%4s\n\n", gstructActStateCharCrystal.structA.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("\nStatistics:    #!00#:\n");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        sprintf (szWorking, "Endurance   %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        sprintf (szWorking, "Stamina     %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        sprintf (szWorking, "Might       %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        sprintf (szWorking, "Karma       %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        sprintf (szWorking, "Frigidity   %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        sprintf (szWorking, "Lust        %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        sprintf (szWorking, "Reflexes    %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        sprintf (szWorking, "Oral Exp    %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        sprintf (szWorking, "Vaginal Exp %9s\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        sprintf (szWorking, "Anal Exp    %9s\n\n", szWorking2);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }
#else // INTERFACE_CURSES

    iRet = mdialog_addToDialogWithSrchRep ("\n");
    if (iRet != 0) return iRet;

    // here I am going to bypass the Search/Replace functions with direct calls to mutils_addToDialogBuffer() so I can insert HTML tags directly.
    //  If I was to use the Search/Replace functions to try and inject HTML, the function will nicely escape the HTML operations so that
    //  they will be interpreted as text, and not as HTML.

    iRet = mutils_addToDialogBuffer ("<table border=\"1\">");
    if (iRet != 0) return iRet;

    // now for the character statistics
    if (gstructActStateGlobal.sActId == 3)
    {
        // first, the headers..
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Statistics:&nbsp;&nbsp;&nbsp;</td><td align=\"right\">&nbsp;&nbsp;&nbsp;");
        if (iRet != 0) return iRet;
        iRet = mdialog_addToDialogWithSrchRep ("#!00#:");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">&nbsp;&nbsp;");
        if (iRet != 0) return iRet;
        iRet = mdialog_addToDialogWithSrchRep ("#!03#:");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Endurance</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structE.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Stamina</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structS.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Might</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structM.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Karma</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structK.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Frigidity</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structF.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Lust</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structL.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Reflexes</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structR.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Oral&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structO.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Vaginal&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structV.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\";left\">Anal&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharCrystal.structA.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
    }
    else
    {
        // first, the headers..
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Statistics:&nbsp;&nbsp;&nbsp;</td><td alight=\"right\">&nbsp;&nbsp;&nbsp;");
        if (iRet != 0) return iRet;
        iRet = mdialog_addToDialogWithSrchRep ("#!00#:");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Endurance</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Stamina</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Might</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Karma</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Frigidity</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Lust</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Reflexes</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Oral&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Vaginal&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("<tr><td align=\"left\">Anal&nbsp;Exp</td><td align=\"right\">");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        iRet = mdialog_addToDialogWithSrchRep (szWorking2);
        if (iRet != 0) return iRet;
        iRet = mutils_addToDialogBuffer ("</td></tr>");
        if (iRet != 0) return iRet;
    }

    iRet = mutils_addToDialogBuffer ("</table>\n<br/>\n");
    if (iRet != 0) return iRet;

#endif // INTERFACE_CURSES

    if (gpstructActStateInventory[3].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Wield iron double edged sword", 1031, 1);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[4].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Wield steel double edged sword", 1031, 2);
        if (iRet != 0) return iRet;
    }
    // Note: I don't add the menu entry to equip the spanking paddle.
    //   In the storyline script, the spanking paddle assignment to the weapon slot
    //   is forced, and it's removal is also forced. After it is back inside the
    //   inventory, it cannot be equipped again.

    // Also, there are no menu entries for equipping the latex gear. This is also
    //   intentional due to the way that the storyline progresses.
    if (gpstructActStateInventory[6].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Wear leather boy cut sleeveless body suit, with bronze plating", 1032, 1);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[7].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Wear leather thong leotard, with iron plating", 1032, 2);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[8].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Wear chainmail bikini", 1032, 3);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[13].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Put on iron capped leather combat boots", 1033, 1);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[14].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Put on leather combat boots, with protruding steel spikes", 1033, 2);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[17].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Equip iron demi-gauntlets with leather gloves", 1034, 1);
        if (iRet != 0) return iRet;
    }
    if (gpstructActStateInventory[18].sCount != 0)
    {
        iRet = mutils_addToCommandList ("Equip iron demi-gauntlets with chain-mail gloves", 1034, 2);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[2].sCount != 0) && (gstructActStateGlobal.cEnteredDungeon != 0))
    {
        iRet = mutils_addToCommandList ("Drink a stamina elixir", 1035, 0);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Close the backpack", 1036, 0);
    if (iRet != 0) return iRet;

    return 0;
}

//
// Swap over the sword/weapon.
//
int gamelogic03_scene1031 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[400];
    char szWorking2[32];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        switch (iSubSceneId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep (">Wield iron double edged sword\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep (">Wield steel double edged sword\n\n");
            if (iRet != 0) return iRet;
            break;
        }
    }

    // this involves taking the currently selected weapon out of the character slot
    //  and putting it back into the inventory.

    // of course, this reassignment only happens if the slot is already occupied.
    if ((gstructActStateCharWilda.sSlotW > 0) && (gstructActStateCharWilda.sSlotW < 27))
    {
        short sSlot = gstructActStateCharWilda.sSlotW;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# decides that she is going to change over her primary weapon. First, she puts away the ");
        if (iRet != 0) return iRet;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structW.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structW.iNum, &szWorking[1]);
        sprintf (szWorking, "(%s) %s.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;

        // the inventory slot HAS to be empty (because this is an effective entry, and it can only have a count of 1).
        if (gpstructActStateInventory[sSlot].sCount == 0)
        {
            // copy over the effectiveness data..
            gpstructActStateInventory[sSlot].structEff.iNum = gstructActStateCharWilda.structW.iNum;
            gpstructActStateInventory[sSlot].structEff.fFraction = gstructActStateCharWilda.structW.fFraction;

            // and set the counter to say that the inventory is now occupied.
            gpstructActStateInventory[sSlot].sCount = 1;
        }
    }

    // now clear this entry in the character data
    gstructActStateCharWilda.structW.iNum = 0;
    gstructActStateCharWilda.structW.fFraction = (float)0;
    gstructActStateCharWilda.sSlotW = 0;

    switch (iSubSceneId)
    {
    case 1:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structW.iNum = gpstructActStateInventory[3].structEff.iNum;
        gstructActStateCharWilda.structW.fFraction = gpstructActStateInventory[3].structEff.fFraction;
        gstructActStateCharWilda.sSlotW = 3;

        // clear the inventory slot.
        gpstructActStateInventory[3].structEff.iNum = 0;
        gpstructActStateInventory[3].structEff.fFraction = (float)0;
        gpstructActStateInventory[3].sCount = 0;

        break;

    default:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structW.iNum = gpstructActStateInventory[4].structEff.iNum;
        gstructActStateCharWilda.structW.fFraction = gpstructActStateInventory[4].structEff.fFraction;
        gstructActStateCharWilda.sSlotW = 4;

        // clear the inventory slot.
        gpstructActStateInventory[4].structEff.iNum = 0;
        gpstructActStateInventory[4].structEff.fFraction = (float)0;
        gpstructActStateInventory[4].sCount = 0;

        break;
    }

    sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structW.fFraction);
    sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structW.iNum, &szWorking[1]);
    sprintf (szWorking, "Then she pulls out the (%s) %s.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName);
    iRet = mdialog_addToDialogWithSrchRep (szWorking);
    if (iRet != 0) return iRet;

    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// Swap over the outfit.
//
int gamelogic03_scene1032 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[400];
    char szWorking2[32];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        switch (iSubSceneId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep (">Wear leather boy cut sleeveless body suit, with bronze plating\n\n");
            if (iRet != 0) return iRet;
            break;

        case 2:
            iRet = mdialog_addToDialogWithSrchRep (">Wear leather thong leotard, with iron plating\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep (">Wear chainmail bikini\n\n");
            if (iRet != 0) return iRet;
            break;
        }
    }

    // this involves taking the currently selected weapon out of the character slot
    //  and putting it back into the inventory.

    // of course, this reassignment only happens if the slot is already occupied.
    if ((gstructActStateCharWilda.sSlotC > 0) && (gstructActStateCharWilda.sSlotC < 27))
    {
        short sSlot = gstructActStateCharWilda.sSlotC;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structC.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structC.iNum, &szWorking[1]);
        sprintf (szWorking, "#!00# decides that she is going to change her outfit. #!00# takes off her (%s) %s and puts it inside her backpack, despite the fact that she is ", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;

        // if we are in the dungeon.
        if (gstructActStateGlobal.cEnteredDungeon != 0)
        {
            iRet = mdialog_addToDialogWithSrchRep ("standing inside a dungeon. It is not as if she is going to encounter anyone else in here anytime soon.\n\n");
        }
        // otherwise we are still inside the inn
        else
        {
            iRet = mdialog_addToDialogWithSrchRep ("inside an inn room with an open window. It is not as if some pervert is hiding in the outside the window. Besides, if there is a pervert hiding out there, she can hunt them down and make them forget that they ever saw her, with her fist.\n\n");
        }
        if (iRet != 0) return iRet;

        // the inventory slot HAS to be empty (because this is an effective entry, and it can only have a count of 1).
        if (gpstructActStateInventory[sSlot].sCount == 0)
        {
            // copy over the effectiveness data..
            gpstructActStateInventory[sSlot].structEff.iNum = gstructActStateCharWilda.structC.iNum;
            gpstructActStateInventory[sSlot].structEff.fFraction = gstructActStateCharWilda.structC.fFraction;

            // and set the counter to say that the inventory is now occupied.
            gpstructActStateInventory[sSlot].sCount = 1;
        }
    }

    // now clear this entry in the character data
    gstructActStateCharWilda.structC.iNum = 0;
    gstructActStateCharWilda.structC.fFraction = (float)0;
    gstructActStateCharWilda.sSlotC = 0;

    switch (iSubSceneId)
    {
    case 1:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structC.iNum = gpstructActStateInventory[6].structEff.iNum;
        gstructActStateCharWilda.structC.fFraction = gpstructActStateInventory[6].structEff.fFraction;
        gstructActStateCharWilda.sSlotC = 6;

        // clear the inventory slot.
        gpstructActStateInventory[6].structEff.iNum = 0;
        gpstructActStateInventory[6].structEff.fFraction = (float)0;
        gpstructActStateInventory[6].sCount = 0;

        break;

    case 2:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structC.iNum = gpstructActStateInventory[7].structEff.iNum;
        gstructActStateCharWilda.structC.fFraction = gpstructActStateInventory[7].structEff.fFraction;
        gstructActStateCharWilda.sSlotC = 7;

        // clear the inventory slot.
        gpstructActStateInventory[7].structEff.iNum = 0;
        gpstructActStateInventory[7].structEff.fFraction = (float)0;
        gpstructActStateInventory[7].sCount = 0;

        break;

    default:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structC.iNum = gpstructActStateInventory[8].structEff.iNum;
        gstructActStateCharWilda.structC.fFraction = gpstructActStateInventory[8].structEff.fFraction;
        gstructActStateCharWilda.sSlotC = 8;

        // clear the inventory slot.
        gpstructActStateInventory[8].structEff.iNum = 0;
        gpstructActStateInventory[8].structEff.fFraction = (float)0;
        gpstructActStateInventory[8].sCount = 0;

        break;
    }

    sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structC.fFraction);
    sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structC.iNum, &szWorking[1]);
    sprintf (szWorking, "#!00# takes the (%s) %s out of her backpack, and puts it on.", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotC].pszName);
    iRet = mdialog_addToDialogWithSrchRep (szWorking);
    if (iRet != 0) return iRet;

    if (gstructActStateCharWilda.sSlotC == 8)
    {
        iRet = mdialog_addToDialogWithSrchRep (" In the process she accidentally wedgies herself with the chainmail bikini bottom \"Ergh.. whoever designed these things was thinking more with their dick than with their head.\"\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("\n\n");
    }
    if (iRet != 0) return iRet;

    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// Swap over the boots/shoes.
//
int gamelogic03_scene1033 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[500];
    char szWorking2[32];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        switch (iSubSceneId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep (">Put on iron capped leather combat boots\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep (">Put on leather combat boots, with protruding steel spikes\n\n");
            if (iRet != 0) return iRet;
            break;
        }
    }

    // this involves taking the currently selected weapon out of the character slot
    //  and putting it back into the inventory.

    // of course, this reassignment only happens if the slot is already occupied.
    if ((gstructActStateCharWilda.sSlotB > 0) && (gstructActStateCharWilda.sSlotB < 27))
    {
        short sSlot = gstructActStateCharWilda.sSlotB;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structB.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structB.iNum, &szWorking[1]);

        // if we are in the dungeon.
        if (gstructActStateGlobal.cEnteredDungeon != 0)
        {
            iRet = mdialog_addToDialogWithSrchRep ("#!00# decides that she is going to change over her boots, which isn\'t going to easy given that her feet are submerged in opaque liquid in the middle of a dungeon.\n\n\n[5 minutes later...]\n\n");
            if (iRet != 0) return iRet;

            sprintf (szWorking, "#!00# managed to take off her sopping wet (%s) %s, and put them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        }
        else
        {
            sprintf (szWorking, "#!00# decides that she is going to change over her boots. #!00# takes off her (%s) %s and puts them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        }
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;

        // the inventory slot HAS to be empty (because this is an effective entry, and it can only have a count of 1).
        if (gpstructActStateInventory[sSlot].sCount == 0)
        {
            // copy over the effectiveness data..
            gpstructActStateInventory[sSlot].structEff.iNum = gstructActStateCharWilda.structB.iNum;
            gpstructActStateInventory[sSlot].structEff.fFraction = gstructActStateCharWilda.structB.fFraction;

            // and set the counter to say that the inventory is now occupied.
            gpstructActStateInventory[sSlot].sCount = 1;
        }
    }

    // now clear this entry in the character data
    gstructActStateCharWilda.structB.iNum = 0;
    gstructActStateCharWilda.structB.fFraction = (float)0;
    gstructActStateCharWilda.sSlotB = 0;

    switch (iSubSceneId)
    {
    case 1:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structB.iNum = gpstructActStateInventory[13].structEff.iNum;
        gstructActStateCharWilda.structB.fFraction = gpstructActStateInventory[13].structEff.fFraction;
        gstructActStateCharWilda.sSlotB = 13;

        // clear the inventory slot.
        gpstructActStateInventory[13].structEff.iNum = 0;
        gpstructActStateInventory[13].structEff.fFraction = (float)0;
        gpstructActStateInventory[13].sCount = 0;

        break;

    default:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structB.iNum = gpstructActStateInventory[14].structEff.iNum;
        gstructActStateCharWilda.structB.fFraction = gpstructActStateInventory[14].structEff.fFraction;
        gstructActStateCharWilda.sSlotB = 14;

        // clear the inventory slot.
        gpstructActStateInventory[14].structEff.iNum = 0;
        gpstructActStateInventory[14].structEff.fFraction = (float)0;
        gpstructActStateInventory[14].sCount = 0;

        break;
    }

    sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structB.fFraction);
    sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structB.iNum, &szWorking[1]);

    // if we are in the dungeon.
    if (gstructActStateGlobal.cEnteredDungeon != 0)
    {
        sprintf (szWorking, "#!00# then took her (%s) %s out of her backpack and put them on her feet. They are wet now, but that is going to happen when you are standing in a partially submerged dungeon.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
    }
    else
    {
        sprintf (szWorking, "She then takes her (%s) %s from her backpack and puts them on her feet.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
    }

    iRet = mdialog_addToDialogWithSrchRep (szWorking);
    if (iRet != 0) return iRet;

    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// Swap over the gloves/gauntlets.
//
int gamelogic03_scene1034 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[400];
    char szWorking2[32];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        switch (iSubSceneId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep (">Equip iron demi-gauntlets with leather gloves\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep (">Equip iron demi-gauntlets with chain-mail gloves\n\n");
            if (iRet != 0) return iRet;
            break;
        }
    }

    // this involves taking the currently selected weapon out of the character slot
    //  and putting it back into the inventory.

    // of course, this reassignment only happens if the slot is already occupied.
    if ((gstructActStateCharWilda.sSlotG > 0) && (gstructActStateCharWilda.sSlotG < 27))
    {
        short sSlot = gstructActStateCharWilda.sSlotG;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# decides that she is going to change over her gauntlets. #!00# takes off her ");
        if (iRet != 0) return iRet;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structG.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structG.iNum, &szWorking[1]);
        sprintf (szWorking, "(%s) %s and puts them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;


        // the inventory slot HAS to be empty (because this is an effective entry, and it can only have a count of 1).
        if (gpstructActStateInventory[sSlot].sCount == 0)
        {
            // copy over the effectiveness data..
            gpstructActStateInventory[sSlot].structEff.iNum = gstructActStateCharWilda.structG.iNum;
            gpstructActStateInventory[sSlot].structEff.fFraction = gstructActStateCharWilda.structG.fFraction;

            // and set the counter to say that the inventory is now occupied.
            gpstructActStateInventory[sSlot].sCount = 1;
        }
    }

    // now clear this entry in the character data
    gstructActStateCharWilda.structG.iNum = 0;
    gstructActStateCharWilda.structG.fFraction = (float)0;
    gstructActStateCharWilda.sSlotG = 0;

    switch (iSubSceneId)
    {
    case 1:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structG.iNum = gpstructActStateInventory[17].structEff.iNum;
        gstructActStateCharWilda.structG.fFraction = gpstructActStateInventory[17].structEff.fFraction;
        gstructActStateCharWilda.sSlotG = 17;

        // clear the inventory slot.
        gpstructActStateInventory[17].structEff.iNum = 0;
        gpstructActStateInventory[17].structEff.fFraction = (float)0;
        gpstructActStateInventory[17].sCount = 0;

        break;

    default:
        // copy over the details to the character slot.
        gstructActStateCharWilda.structG.iNum = gpstructActStateInventory[18].structEff.iNum;
        gstructActStateCharWilda.structG.fFraction = gpstructActStateInventory[18].structEff.fFraction;
        gstructActStateCharWilda.sSlotG = 18;

        // clear the inventory slot.
        gpstructActStateInventory[18].structEff.iNum = 0;
        gpstructActStateInventory[18].structEff.fFraction = (float)0;
        gpstructActStateInventory[18].sCount = 0;

        break;
    }

    sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structG.fFraction);
    sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structG.iNum, &szWorking[1]);
    sprintf (szWorking, "She then takes her (%s) %s from her backpack and puts them on her hands.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotG].pszName);
    iRet = mdialog_addToDialogWithSrchRep (szWorking);
    if (iRet != 0) return iRet;

    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// Drink an elixir.
//
int gamelogic03_scene1035 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        iRet = mdialog_addToDialogWithSrchRep (">Drink a stamina elixir\n\n");
        if (iRet != 0) return iRet;
    }

    // Stamina elixir is a multi-entry item in the inventory.
    gpstructActStateInventory[2].sCount--;

    // I need to change the character attribute specifications here.

    // this is the increase of the stamina value
    actionstate_statAddition (&gstructActStateCharWilda.structS, 116.5, (int)(gstructActStateCharWilda.structE.iNum + 2));

    // this is the increase of the lust value
    actionstate_statAddition (&gstructActStateCharWilda.structL, 136.75, (int)(gstructActStateCharWilda.structF.iNum + 3));

    iRet = mdialog_addToDialogWithSrchRep ("#!00# takes a vial of \'Stamina elixir\' from her backpack. She looks at the vial, remembering that this stuff has a real kick. #!00# hopes that she isn\'t going to end up cuming her brains out after this.\n\n#!00# breaks open the seal of the vial, and downs the contents in a single gulp. #!00# tosses aside the spent vial, then waits for the elixir to take effect. #!00# notices that her nipples and clitoris are starting to harden, while her pussy is starting to itch.\n\n\n");
    if (iRet != 0) return iRet;

    // this is the forced masturbation path.
    if (gstructActStateCharWilda.structL.iNum >= gstructActStateCharWilda.structF.iNum)
    {
        float fCompare;

        // decrease Lust
        fCompare = (float)((float)gstructActStateCharWilda.structF.iNum / (float)2.61);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, fCompare, (int)1);

        // decrease Frigidity
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)5.121, (int)50);

        iRet = mdialog_addToDialogWithSrchRep ("[5 minutes later...]\n\nA sigh escapes #!00#, as her arousal finally settles down. She found that she had to finger herself to a climax twice, in the middle of a dungeon, which isn\'t good.\n\nThere isn\'t anyone in the mercenary business who does not know about the side effects of this stuff, but when you have to do it, you really have to do it. At least #!00# is alone here.\n\n");
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("[2 minutes later...]\n\n#!00# takes a couple of deep breaths as the side effects of the elixir finally subside.\n\n");
        if (iRet != 0) return iRet;
    }

    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// Close the backpack.
//
int gamelogic03_scene1036 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        iRet = mdialog_addToDialogWithSrchRep (">Close the backpack\n\n");
        if (iRet != 0) return iRet;
    }

    // if we have not entered the dungeon yet, then go back to the story.
    if (gstructActStateGlobal.cEnteredDungeon != 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# closes up her backpack, and puts it on her back\n\n");
        if (iRet != 0) return iRet;

        iRet = gamelogic01_scene1006 (0, cSubFlag + 1);
    }
    // otherwise, we are in the dungeon, switch back to navigation.
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# closes up her backpack, and puts it back on her back\n\n");
        if (iRet != 0) return iRet;

        iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    }
    return iRet;
}

