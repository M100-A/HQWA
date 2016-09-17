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
        iRet = mutils_addToDialogBuffer (">Inventory and status\n\n");
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer ("Wilda opens her backpack and checks the contents.\n\n");
        if (iRet != 0) return iRet;
    }

    if (gstructActStateGlobal.sActId == 1)
    {
        iRet = mutils_addToDialogBuffer ("In her leather backpack, Wilda currently has:\n");
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[1].sCount == 1)
            iRet = mutils_addToDialogBuffer ("1 gold piece.\n");
        else
        {
            sprintf (szWorking, "%d gold pieces.\n", (int) gpstructActStateInventory[1].sCount);
            iRet = mutils_addToDialogBuffer (szWorking);
        }
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[2].sCount != 0)
        {
            if (gpstructActStateInventory[2].sCount == 1)
                iRet = mutils_addToDialogBuffer ("1 stamina elixir.\n");
            else
            {
                sprintf (szWorking, "%d stamina elixirs.\n", (int) gpstructActStateInventory[2].sCount);
                iRet = mutils_addToDialogBuffer (szWorking);
            }
            if (iRet != 0) return iRet;
        }

        sprintf (szWorking, "%d torches.\n", (int) gpstructActStateInventory[22].sCount);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer ("1 yo-yo (childhood keepsake).\n1 \'holy artifact\' from Amber, that looks like a dildo, in a box.\n");
        if (iRet != 0) return iRet;
    }
    else if (gstructActStateGlobal.sActId == 2)
    {
        iRet = mutils_addToDialogBuffer ("In her latex backpack, Wilda currently has:\n0 gold pieces (there will be more when the job is done).\n0 yo-yos (that was from Wilda\'s uncle, damnit).\n");
        if (iRet != 0) return iRet;

        if (gpstructActStateInventory[26].sCount != 0)
        {
            iRet = mutils_addToDialogBuffer ("1 \'holy artifact\', that looks like a dildo, in a box.\n");
            if (iRet != 0) return iRet;
        }
    }
    else if (gstructActStateGlobal.sActId == 3)
    {
        iRet = mutils_addToDialogBuffer ("In her latex backpack, Wilda currently has:\n0 gold pieces (which isn\'t a big deal right now).\n");
        if (iRet != 0) return iRet;
    }
    else // actid = 4
    {
        iRet = mutils_addToDialogBuffer ("In her latex backpack, Wilda currently has:\n0 gold pieces (but, who cares about that).\n1 \'holy artifact\' from Felicity, a dildo in a box.\n");
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
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    // and one final thing for act 1.
    if (gstructActStateGlobal.sActId == 1)
    {
        iRet = mutils_addToDialogBuffer ("And, 1 leather bivouac sack, attached to the outside of the backpack.\n");
        if (iRet != 0) return iRet;
    }

    iRet = mutils_addToDialogBuffer ("\nWilda also is currently:\n");
    if (iRet != 0) return iRet;

    if (gstructActStateCharWilda.sSlotW != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structW.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structW.iNum, &szWorking[1]);
        if (gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName[0] == 'i')
            sprintf (szWorking, "Holding an (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName);
        else
            sprintf (szWorking, "Holding a (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotW].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateGlobal.sActId == 1)
    {
        if (gstructActStateGlobal.cEnteredDungeon != 0)
        {
            iRet = mutils_addToDialogBuffer ("Holding a lit torch.\n");
            if (iRet != 0) return iRet;
        }
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Holding an aquamarine lantern.\n");
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
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateCharWilda.sSlotB != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structB.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structB.iNum, &szWorking[1]);
        sprintf (szWorking, "Wearing a pair of (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    if (gstructActStateCharWilda.sSlotG != 0)
    {
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structG.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structG.iNum, &szWorking[1]);
        sprintf (szWorking, "Wearing a pair of (%s) %s.\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotG].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    // now for the character statistics
    if (gstructActStateGlobal.sActId == 3)
    {
        iRet = mutils_addToDialogBuffer ("\nStatistics:    Wilda:  Crystal:\n");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        sprintf (szWorking, "Endurance   %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structE.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structE.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        sprintf (szWorking, "Stamina     %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structS.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structS.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        sprintf (szWorking, "Might       %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structM.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structM.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        sprintf (szWorking, "Karma       %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structK.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structK.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        sprintf (szWorking, "Frigidity   %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structF.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structF.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        sprintf (szWorking, "Lust        %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structL.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structL.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        sprintf (szWorking, "Reflexes    %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structR.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structR.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        sprintf (szWorking, "Oral Exp    %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structO.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structO.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        sprintf (szWorking, "Vaginal Exp %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structV.fFraction);
        sprintf (szWorking2, " %5d%4s\n", gstructActStateCharCrystal.structV.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        sprintf (szWorking, "Anal Exp    %9s", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharCrystal.structA.fFraction);
        sprintf (szWorking2, " %5d%4s\n\n", gstructActStateCharCrystal.structA.iNum, &szWorking[1]);
        iRet = mutils_addToDialogBuffer (szWorking2);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("\nStatistics:    Wilda:\n");
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structE.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structE.iNum, &szWorking[1]);
        sprintf (szWorking, "Endurance   %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structS.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structS.iNum, &szWorking[1]);
        sprintf (szWorking, "Stamina     %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structM.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structM.iNum, &szWorking[1]);
        sprintf (szWorking, "Might       %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structK.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structK.iNum, &szWorking[1]);
        sprintf (szWorking, "Karma       %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structF.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structF.iNum, &szWorking[1]);
        sprintf (szWorking, "Frigidity   %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structL.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structL.iNum, &szWorking[1]);
        sprintf (szWorking, "Lust        %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structR.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structR.iNum, &szWorking[1]);
        sprintf (szWorking, "Reflexes    %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structO.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structO.iNum, &szWorking[1]);
        sprintf (szWorking, "Oral Exp    %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structV.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structV.iNum, &szWorking[1]);
        sprintf (szWorking, "Vaginal Exp %9s\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structA.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structA.iNum, &szWorking[1]);
        sprintf (szWorking, "Anal Exp    %9s\n\n", szWorking2);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

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
            iRet = mutils_addToDialogBuffer (">Wield iron double edged sword\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mutils_addToDialogBuffer (">Wield steel double edged sword\n\n");
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

        iRet = mutils_addToDialogBuffer ("Wilda decides that she is going to change over her primary weapon. First, she puts away the ");
        if (iRet != 0) return iRet;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structW.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structW.iNum, &szWorking[1]);
        sprintf (szWorking, "(%s) %s.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
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
    iRet = mutils_addToDialogBuffer (szWorking);
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
            iRet = mutils_addToDialogBuffer (">Wear leather boy cut sleeveless body suit, with bronze plating\n\n");
            if (iRet != 0) return iRet;
            break;

        case 2:
            iRet = mutils_addToDialogBuffer (">Wear leather thong leotard, with iron plating\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mutils_addToDialogBuffer (">Wear chainmail bikini\n\n");
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
        sprintf (szWorking, "Wilda decides that she is going to change her outfit. Wilda takes off her (%s) %s and puts it inside her backpack, despite the fact that she is ", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;

        // if we are in the dungeon.
        if (gstructActStateGlobal.cEnteredDungeon != 0)
        {
            iRet = mutils_addToDialogBuffer ("standing inside a dungeon. It is not as if she is going to encounter anyone else in here anytime soon.\n\n");
        }
        // otherwise we are still inside the inn
        else
        {
            iRet = mutils_addToDialogBuffer ("inside an inn room with an open window. It is not as if some pervert is hiding in the outside the window. Besides, if there is a pervert hiding out there, she can hunt them down and make them forget that they ever saw her, with her fist.\n\n");
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
    sprintf (szWorking, "Wilda takes the (%s) %s out of her backpack, and puts it on.", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotC].pszName);
    iRet = mutils_addToDialogBuffer (szWorking);
    if (iRet != 0) return iRet;

    if (gstructActStateCharWilda.sSlotC == 8)
    {
        iRet = mutils_addToDialogBuffer (" In the process she accidentally wedgies herself with the chainmail bikini bottom \"Ergh.. whoever designed these things was thinking more with their dick than with their head.\"\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("\n\n");
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
            iRet = mutils_addToDialogBuffer (">Put on iron capped leather combat boots\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mutils_addToDialogBuffer (">Put on leather combat boots, with protruding steel spikes\n\n");
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
            iRet = mutils_addToDialogBuffer ("Wilda decides that she is going to change over her boots, which isn\'t going to easy given that her feet are submerged in opaque liquid in the middle of a dungeon.\n\n\n[5 minutes later...]\n\n");
            if (iRet != 0) return iRet;

            sprintf (szWorking, "Wilda managed to take off her sopping wet (%s) %s, and put them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        }
        else
        {
            sprintf (szWorking, "Wilda decides that she is going to change over her boots. Wilda takes off her (%s) %s and puts them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        }
        iRet = mutils_addToDialogBuffer (szWorking);
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
        sprintf (szWorking, "Wilda then took her (%s) %s out of her backpack and put them on her feet. They are wet now, but that is going to happen when you are standing in a partially submerged dungeon.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
    }
    else
    {
        sprintf (szWorking, "She then takes her (%s) %s from her backpack and puts them on her feet.\n\n", szWorking2, gstructInventoryDescription[gstructActStateCharWilda.sSlotB].pszName);
    }

    iRet = mutils_addToDialogBuffer (szWorking);
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
            iRet = mutils_addToDialogBuffer (">Equip iron demi-gauntlets with leather gloves\n\n");
            if (iRet != 0) return iRet;
            break;

        default:
            iRet = mutils_addToDialogBuffer (">Equip iron demi-gauntlets with chain-mail gloves\n\n");
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

        iRet = mutils_addToDialogBuffer ("Wilda decides that she is going to change over her gauntlets. Wilda takes off her ");
        if (iRet != 0) return iRet;

        sprintf (szWorking, "%0.3f", (double)gstructActStateCharWilda.structG.fFraction);
        sprintf (szWorking2, "%d%s", gstructActStateCharWilda.structG.iNum, &szWorking[1]);
        sprintf (szWorking, "(%s) %s and puts them inside her backpack.\n\n", szWorking2, gstructInventoryDescription[sSlot].pszName);
        iRet = mutils_addToDialogBuffer (szWorking);
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
    iRet = mutils_addToDialogBuffer (szWorking);
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
        iRet = mutils_addToDialogBuffer (">Drink a stamina elixir\n\n");
        if (iRet != 0) return iRet;
    }

    // Stamina elixir is a multi-entry item in the inventory.
    gpstructActStateInventory[2].sCount--;

    // I need to change the character attribute specifications here.

    // this is the increase of the stamina value
    actionstate_statAddition (&gstructActStateCharWilda.structS, 116.5, (int)(gstructActStateCharWilda.structE.iNum + 2));

    // this is the increase of the lust value
    actionstate_statAddition (&gstructActStateCharWilda.structL, 136.75, (int)(gstructActStateCharWilda.structF.iNum + 3));

    iRet = mutils_addToDialogBuffer ("Wilda takes a vial of \'Stamina elixir\' from her backpack. She looks at the vial, remembering that this stuff has a real kick. Wilda hopes that she isn\'t going to end up cuming her brains out after this.\n\nWilda breaks open the seal of the vial, and downs the contents in a single gulp. Wilda tosses aside the spent vial, then waits for the elixir to take effect. Wilda notices that her nipples and clitoris are starting to harden, while her pussy is starting to itch.\n\n\n");
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

        iRet = mutils_addToDialogBuffer ("[5 minutes later...]\n\nA sigh escapes Wilda, as her arousal finally settles down. She found that she had to finger herself to a climax twice, in the middle of a dungeon, which isn\'t good.\n\nThere isn\'t anyone in the mercenary business who does not know about the side effects of this stuff, but when you have to go, you really have to go. At least Wilda is alone here.\n\n");
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("[2 minutes later...]\n\nWilda takes a couple of deep breaths as the side effects of the elixir finally subside.\n\n");
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
        iRet = mutils_addToDialogBuffer (">Close the backpack\n\n");
        if (iRet != 0) return iRet;
    }

    // if we have not entered the dungeon yet, then go back to the story.
    if (gstructActStateGlobal.cEnteredDungeon != 1)
    {
        iRet = mutils_addToDialogBuffer ("Wilda closes up her backpack, and puts it on her back\n\n");
        if (iRet != 0) return iRet;

        iRet = gamelogic01_scene1006 (0, cSubFlag + 1);
    }
    // otherwise, we are in the dungeon, switch back to navigation.
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda closes up her backpack, and puts it back on her back\n\n");
        if (iRet != 0) return iRet;

        iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    }
    return iRet;
}

