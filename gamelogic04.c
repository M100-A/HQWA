//
// gamelogic04.c
//
// This is group 4 of scene ids.
//
// Essentially, this is the all of the combat actions of the game.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"

// external linkage to the game variables.
extern  char    gcDebugFlag;

// linkage to the actionstate data.
extern  struct  actionstate_charstats gstructActStateCharWilda;
extern  struct  actionstate_charstats gstructActStateCharCrystal;
extern  struct  actionstate_opponentstats gstructActStateOpponent;
extern  struct  actionstate_globalvars gstructActStateGlobal;

//
// Setup/Continue the Act 1 combat moves.
//
int gamelogic04_scene1040 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToCommandList ("Slash with sword, then block", 1041, 1);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Slash with sword, then pull back", 1041, 2);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Slash with sword, then punch with fist", 1041, 3);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Slash with sword, repeatedly", 1041, 4);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Stab with sword, then block", 1041, 5);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Stab with sword, then pull back", 1041, 6);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Stab with sword, then punch with fist", 1041, 7);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Stab with sword, repeatedly", 1041, 8);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then block", 1041, 9);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then pull back", 1041, 10);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then punch with fist", 1041, 11);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, repeatedly", 1041, 12);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Sword feint attack, then block", 1041, 13);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Sword feint attack, then pull back", 1041, 14);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Sword feint attack, then punch with fist", 1041, 15);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Sword feint attack, then real slash with sword", 1041, 16);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Sword feint attack, then real stab with sword", 1041, 17);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then block", 1041, 18);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then pull back", 1041, 19);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then punch with fist", 1041, 20);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then real slash with sword", 1041, 21);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then real stab with sword", 1041, 22);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then block", 1041, 23);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then pull back", 1041, 24);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then punch with fist", 1041, 25);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then real slash with sword", 1041, 26);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then real stab with sword", 1041, 27);
    if (iRet != 0) return iRet;

    return 0;
}

//
// Execution of the Act 1 combat moves.
//
int gamelogic04_scene1041 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iRndNum;
    int iMonsterAction;
    char cDefensive = 0;
    float fStaDec;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Slash with sword, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a basic offensive/defensive move, by slashing the monster with her sword then readying herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)1.1, (float)0.9, (float)0.75, (float)0.81, (float)0.7);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.63, (float)0.29, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.01, (float)0.81, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.81, (float)0.33, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.94, (float)0.33, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.43, (float)0.22, 300), 1);

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Slash with sword, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda slashes the monster with her sword, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)1.1, (float)0.9, (float)1.25, (float)0.84, (float)0.51);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, K+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.71, (float)0.37, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.15, (float)0.95, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.74, (float)0.26, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.95, (float)0.34, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.13, (float)0.07, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.44, (float)0.23, 300), 1);

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Slash with sword, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a basic offensive combo, by slashing the monster with her sword, then punching it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (4, (float)1.9, (float)1.6, (float)0.85, (float)0.89, (float)1.5);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.82, (float)0.48, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.12, (float)1.72, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.96, (float)0.48, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.92, (float)0.31, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.62, (float)0.21, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.48, (float)0.23, 300), 1);

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Slash with sword, repeatedly\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda goes all out, slashing the monster with her sword multiple times.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)3, (float)2.6, (float)2.1, (float)2.2, (float)0.6);
        if (iRet != 0) return iRet;

        // M+, E+, S---, R++, K-, W---, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.61, (float)0.93, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)3.04, (float)2.44, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.32, (float)0.6, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.92, (float)0.7, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.51, (float)0.33, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)2.84, (float)1.61, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.54, (float)0.09, 300), 1);

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stab with sword, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a harder offensive/defensive move, by stabbing the monster with her sword, then readying herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.95, (float)1.1, (float)0.7, (float)0.84, (float)0.7);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.74, (float)0.4, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.23, (float)1.03, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.83, (float)0.35, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.82, (float)0.21, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.52, (float)0.31, 300), 1);

        break;

    case 6:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stab with sword, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda stabs the monster with her sword, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.95, (float)1.1, (float)1.25, (float)0.87, (float)0.49);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, K+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.76, (float)0.42, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.32, (float)1.12, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.72, (float)0.24, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.83, (float)0.22, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.14, (float)0.08, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.52, (float)0.32, 300), 1);

        break;

    case 7:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stab with sword, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a harder offensive combo, by stabbing the monster with her sword, then punching it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (4, (float)1.8, (float)1.6, (float)0.85, (float)0.82, (float)1.4);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.79, (float)0.45, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.54, (float)2.14, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.94, (float)0.46, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.84, (float)0.23, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.51, (float)0.30, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.71, (float)0.26, 300), 1);

        break;

    case 8:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stab with sword, repeatedly\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda goes all out, stabbing the monster with her sword multiple times.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)2.75, (float)2.6, (float)2.1, (float)2.2, (float)0.5);
        if (iRet != 0) return iRet;

        // M+, E+, S---, R++, K-, W---, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.67, (float)0.99, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)3.08, (float)2.48, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.42, (float)0.7, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.84, (float)0.62, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.52, (float)0.34, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)2.94, (float)1.71, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.54, (float)0.09, 300), 1);

        break;

    case 9:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a weak offensive/defensive move, by kicking the monster with her boot, then readying herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)1.2, (float)1, (float)0.75, (float)0.86, (float)0.5);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, B-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.81, (float)0.47, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.23, (float)1.03, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.8, (float)0.32, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.89, (float)0.28, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.53, (float)0.32, 300), 1);

        break;

    case 10:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda kicks the monster with her boot, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)1.2, (float)1, (float)1.25, (float)0.86, (float)0.5);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, K+, B-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.82, (float)0.48, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.32, (float)1.12, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.79, (float)0.31, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.9, (float)0.29, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.16, (float)0.1, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.56, (float)0.35, 300), 1);

        break;

    case 11:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a weak offensive combo, by kicking the monster with her boot, then punching it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (6, (float)2.1, (float)1, (float)0.8, (float)0.86, (float)0.48);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, B-, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.85, (float)0.51, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.74, (float)2.34, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.94, (float)0.46, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.88, (float)0.27, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.7, (float)0.25, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.54, (float)0.33, 300), 1);

        break;

    case 12:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, repeatedly\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda decides to kick the monster with her boots, multiple times.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)3.3, (float)2.8, (float)1.9, (float)2.3, (float)0.4);
        if (iRet != 0) return iRet;

        // M+, E+, S----, R++, K--, B---
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.73, (float)1.05, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)3.23, (float)2.63, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.46, (float)0.74, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.87, (float)0.65, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.31, (float)0.19, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)3.01, (float)1.78, 300), 1);

        break;

    case 13:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Sword feint attack, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to slash the monster with her sword, then readies herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.3, (float)0.78, (float)1.8, (float)0.3);
        if (iRet != 0) return iRet;

        // S-, R+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.12, (float)0.92, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.9, (float)0.29, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.23, (float)0.11, 300), 1);

        break;

    case 14:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Sword feint attack, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to slash the monster with her sword, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.3, (float)1.28, (float)1.8, (float)0.3);
        if (iRet != 0) return iRet;

        // S-, R+, K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.38, (float)1.18, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.92, (float)0.31, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.15, (float)0.09, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.24, (float)0.12, 300), 1);

        break;

    case 15:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Sword feint attack, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to slash the monster with her sword, then punches the monster with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.2, (float)1.8, (float)0.8, (float)1.6, (float)0.5);
        if (iRet != 0) return iRet;

        // S-, R+, G-
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.42, (float)1.22, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.91, (float)0.30, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.22, (float)0.1, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.78, (float)0.33, 200), 0);

        break;

    case 16:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Sword feint attack, then real slash with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to slash the monster with her sword, then slashes the monster with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.8, (float)2.1, (float)0.8, (float)2.2, (float)1.1);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.45, (float)0.28, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.05, (float)1.65, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.43, (float)0.19, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)2.01, (float)0.79, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.31, (float)0.13, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.53, (float)0.22, 300), 1);

        break;

    case 17:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Sword feint attack, then real stab with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to stab the monster with her sword, then stabs the monster with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.74, (float)2.2, (float)0.75, (float)2.3, (float)1.2);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.47, (float)0.3, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.14, (float)1.74, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.39, (float)0.15, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)2, (float)0.78, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.31, (float)0.13, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.62, (float)0.31, 300), 1);

        break;

    case 18:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to kick the monster with her boot, then readies herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.1, (float)0.75, (float)1.1, (float)0.8);
        if (iRet != 0) return iRet;

        // S-, R+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.12, (float)0.92, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.83, (float)0.22, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.26, (float)0.15, 300), 1);

        break;

    case 19:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to the monster with her boot, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.1, (float)1.25, (float)1.1, (float)0.8);
        if (iRet != 0) return iRet;

        // S-, R+, K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.21, (float)1.01, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.85, (float)0.24, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.14, (float)0.08, 300), 6000);

        break;

    case 20:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to the monster with her boot, then punches it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.1, (float)2.1, (float)0.7, (float)1.95, (float)1.5);
        if (iRet != 0) return iRet;

        // S-, R+, G-
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.32, (float)1.12, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.97, (float)0.36, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.77, (float)0.32, 200), 0);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.32, (float)0.11, 200), 0);

        break;

    case 21:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then real slash with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to the monster with her boot, then slashes it with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.9, (float)2.1, (float)0.8, (float)1.56, (float)1.3);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.42, (float)0.25, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.38, (float)1.98, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.76, (float)0.52, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)2.03, (float)0.81, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.3, (float)0.12, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.53, (float)0.22, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.5, (float)0.05, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.34, (float)0.13, 300), 1);

        break;

    case 22:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then real stab with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to the monster with her boot, then stabs it with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.85, (float)2.2, (float)0.75, (float)1.7, (float)1.5);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.44, (float)0.27, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.43, (float)2.03, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.68, (float)0.44, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)2.06, (float)0.84, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.31, (float)0.13, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.62, (float)0.31, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.49, (float)0.04, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.27, (float)0.06, 300), 1);

        break;

    case 23:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda uses a tactical defensive combo, by pretending to hesitate, then readying herself for the potential attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)0.6, (float)0.6, (float)0.4, (float)0.6);
        if (iRet != 0) return iRet;

        // (no change till the counter, if any)
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.32, (float)0.12, 200), 0);

        break;

    case 24:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to hesitate, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)0.6, (float)1.25, (float)0.4, (float)0.6);
        if (iRet != 0) return iRet;

        // K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.06, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.13, (float)0.07, 300), 6000);

        break;

    case 25:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to hesitate, then punches the monster with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.05, (float)0.95, (float)0.92, (float)1.4, (float)1.2);
        if (iRet != 0) return iRet;

        // M+, S-, R+, G-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.42, (float)0.25, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.9, (float)1.7, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.76, (float)0.52, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.73, (float)0.12, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, actionstate_randomFloatValue ((float)0.81, (float)0.36, 300), 1);

        break;

    case 26:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then real slash with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pauses, then slashes the monster with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.93, (float)2.1, (float)1.7, (float)1.9, (float)2.1);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.38, (float)0.21, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.3, (float)1.1, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.74, (float)0.5, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.71, (float)0.1, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.55, (float)0.24, 300), 1);

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then real stab with sword\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda waits for a better opening, then stabs the monster with her sword.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.85, (float)2.05, (float)1.6, (float)2.3, (float)2.6);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.41, (float)0.24, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.6, (float)1.4, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.81, (float)0.57, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.72, (float)0.11, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.64, (float)0.33, 300), 1);

        break;
    }

    // if the monster has expended all of their hitpoints, and this is the first encounter.
    // this is the end of this first encounter.
    if ((gstructActStateOpponent.iHitPoints < 0) && (gstructActStateGlobal.sAct1Monsters == 0))
    {
        // increment the counter, which triggers the encounter system from now on.
        gstructActStateGlobal.sAct1Monsters++;

        // set the monster to being no longer active.
        gstructActStateOpponent.cActive = 0;

        // need to alter the stats for the PC and their gear.
        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)2.324, (int)6000); // endurance
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)18.673, (int)0); // stamina
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)0.913, (int)6000); // might
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, (float)2.263, (int)1); // karma
        actionstate_statAddition (&gstructActStateCharWilda.structL, (float)74.532, (int)6000); // lust (wilda has been sprayed with goo from the monster)
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)3.162, (int)6000); // reflexes
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)4.261, (int)1); // weapon effectiveness
        actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)2.212, (int)1); // gauntlet effectiveness
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)2.863, (int)1); // boot effectiveness
        actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)3.612, (int)1); // clothing/armor effectiveness

        // call the function to populate the dialog for the end of the fight scene.
        iRet = gamelogic01_event_scene022a (cSubFlag + 1);
        if (iRet != 0) return iRet;

        // switch back to navigation.
        iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
        return iRet;
    }

    //
    // Workout what the monster is going to do.
    //
    iMonsterAction = actionstate_accessAct1MonsterAction ();

    // here is where I apply additional impacts to the PC for the monster action.
    //  0 and 3 have no parameter effect to the PC..
    switch (iMonsterAction)
    {
    case 0: // run away
        if (cDefensive == 2)
            iRet = mutils_addToDialogBuffer ("The tentacle monster briefly hesitates, then runs away.\n\n");
        else if (cDefensive != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster takes advantage of Wilda\'s retreat, and runs away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster runs away.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 1: // monster sprays goo and runs away
        // increase lust for the goo hit.
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)15, (float)9, 400), 6000);

        if (cDefensive == 2)
            iRet = mutils_addToDialogBuffer ("The tentacle monster performs an unconventional retreat, by spraying Wilda with goo, then running away.\n\n");
        else if (cDefensive != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster moves towards Wilda, sprays Wilda with goo, then runs away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with goo, then runs away.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 2: // tentacle smash, then runs away

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)0.5, (float)0.2, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.4, (float)2.4, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            // The stamina impact is less, but the gear impact is higher.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster responds by attacking it with one of its tentacles, then running away.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            // impacts on everything is less.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster weakly attacks Wilda it with one of its tentacles, then runs away.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster performs a tactical retreat, by attacking Wilda with one of its tentacles, then running away.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 3: // cower in fear, then run away

        iRndNum = (int)(rand() % 2);

        if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster appears to hesitate, then runs away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster hesitates, almost as if it is gripped by fear, then it runs away.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 4: // Goo spray, then Tentacle smash.

        // increase lust for the goo hit.
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)22.4, (float)13.1, 500), 6000);
        // note: lust is also expanded to take into account the below.

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.6, (float)2.6, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            // The stamina impact is less, but the gear impact is higher.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with goo, then attacks her with a tentacle.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            // impacts on everything is less.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with its goo, then weakly attacks her with its tentacle.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with goo, then pummels her with a tentacle.\n\n");
        }

        if (iRet != 0) return iRet;

        break;

    case 5: // Cower in fear, then Tentacle smash.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)0.5, (float)0.2, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.6, (float)2.6, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hesitates, as if it is evaluating Wilda\'s defensive stance, then it attacks with one of its tentacles.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hesitates, then it attacks weakly with one of its tentacles.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster seems to be waiting for something, then it strikes hard with one of its tentacles.\n\n");
        }

        if (iRet != 0) return iRet;

        break;

    case 6: // Tentacle smash, then Cower in fear.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1, (float)0.3, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.2, (float)2.2, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.7), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.4), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hits Wilda with a tentacle, then waits. It has no intention of running away.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.7), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.7), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster weakly hits Wilda, then hesitates.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.7), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.7), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.7), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.7), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hits Wilda with a tentacle, but does not do anything else afterwards.\n\n");
        }

        if (iRet != 0) return iRet;

        break;

    case 7: // Tentacle smash x2.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2, (float)0.6, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)7, (float)6.2, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hits Wilda twice in a row with its tentacles.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster weakly hits Wilda with its tentacles, twice.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster takes advantage of the opening, and hits Wilda twice with its tentacles.\n\n");
        }

        if (iRet != 0) return iRet;

        break;

    case 8: // Tentacle smash x3.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)3, (float)0.9, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)10, (float)8, 300);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster launches an all out attack on Wilda with its tentacles flailing.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 4.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 3), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 2.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster rushes at Wilda, hitting her multiple times with its tentacles.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 3.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structG, (float)(fStaDec / 2.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 1.5), 0);

            iRndNum = (int)(rand() % 2);

            if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("The tentacle monster, taking advantage of an opening, pummels Wilda with its tentacles.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("The tentacle monster, goes on the offensive and slams Wilda, multiple times, with its flailing tentacles.\n\n");
        }

        if (iRet != 0) return iRet;

        break;
    }

    iRndNum = (int)(rand() % 3);

    if (iMonsterAction < 4)
    {
        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda watches as the monster splashes through the liquid. Wilda keeps her sword ready in case another monster appears.");
        else if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("As the monster scampers away, Wilda relaxes her posture, but waits to see if the monster returns.");
        else
            iRet = mutils_addToDialogBuffer ("While watching the tentacle monster perform its retreat, Wilda keeps her sword ready.");
        if (iRet != 0) return iRet;

        // pass control over to the exit scene.
        iRet = gamelogic04_scene1042 (0, cSubFlag + 1);
        return iRet;
    }

    if (gstructActStateGlobal.sAct1Monsters < 5)
    {
        if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster is still here, and Wilda has no intention of retreating.\n\n");
        else if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("Wilda decides that it would be a bad idea if she should attempt to flee.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Neither Wilda or the tentacle monster are going anywhere.\n\n");
        if (iRet != 0) return iRet;
    }

    iRet = gamelogic04_scene1040 (0, cSubFlag + 1);
    return iRet;
}

//
// Act 1 combat exit.
//
int gamelogic04_scene1042 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // increment the counter
    if (gstructActStateGlobal.sAct1Monsters < 30)
        gstructActStateGlobal.sAct1Monsters++;

    // set the monster to being no longer active.
    gstructActStateOpponent.cActive = 0;

    // set the array to say that we had an encounter.
    gstructActStateGlobal.caEncounterArray[0] = 1;

    iRet = mutils_addToDialogBuffer ("\n\n\n[1 minute later...]\n\nWilda puts her sword away.\n\n");
    if (iRet != 0) return iRet;

    iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    return iRet;
}

//
// Setup/Continue the Act 2 combat moves.
//
int gamelogic04_scene1050 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToCommandList ("Hit with spanking paddle, then block", 1051, 1);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Hit with spanking paddle, then pull back", 1051, 2);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Hit with spanking paddle, then punch with fist", 1051, 3);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Hit with spanking paddle, repeatedly", 1051, 4);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then block", 1051, 5);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then pull back", 1051, 6);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, then punch with fist", 1051, 7);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Kick with foot, repeatedly", 1051, 8);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Paddle feint attack, then block", 1051, 9);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Paddle feint attack, then pull back", 1051, 10);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Paddle feint attack, then punch with fist", 1051, 11);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Paddle feint attack, then hit with spanking paddle", 1051, 12);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then block", 1051, 13);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then pull back", 1051, 14);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then punch with fist", 1051, 15);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Foot feint attack, then hit with spanking paddle", 1051, 16);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then block", 1051, 17);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then pull back", 1051, 18);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then punch with fist", 1051, 19);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Do nothing, then hit with spanking paddle", 1051, 20);
    if (iRet != 0) return iRet;

    return 0;
}

//
// Execution of the Act 2 combat moves.
//
int gamelogic04_scene1051 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iRndNum;
    int iMonsterAction;
    char cDefensive = 0;
    float fStaDec;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Hit with spanking paddle, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs an improvised offensive/defensive move, by hitting the monster with her paddle then readying herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)1.1, (float)0.9, (float)0.75, (float)0.81, (float)0.7);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.53, (float)0.19, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.08, (float)0.88, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.81, (float)0.33, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.94, (float)0.33, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.123, (float)0.102, 100), 1);

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Hit with spanking paddle, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda hits the monster with her spanking paddle, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)1.1, (float)0.9, (float)1.35, (float)0.84, (float)0.51);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, K+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.54, (float)0.2, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.21, (float)1.01, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.74, (float)0.26, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.95, (float)0.34, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.13, (float)0.07, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.129, (float)0.108, 100), 1);

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Hit with spanking paddle, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a basic offensive combo, by hitting the monster with her spanking paddle, then punching it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (4, (float)1.9, (float)1.6, (float)0.85, (float)0.89, (float)1.5);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.73, (float)0.39, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.31, (float)1.91, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.96, (float)0.48, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.92, (float)0.31, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.132, (float)0.108, 100), 1);

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Hit with spanking paddle, repeatedly\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda goes all out, spanking the monster with her paddle multiple times.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)3, (float)2.6, (float)2.1, (float)2.2, (float)0.6);
        if (iRet != 0) return iRet;

        // M+, E+, S----, R++, K-, W---
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.61, (float)0.93, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)4.42, (float)3.62, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.32, (float)0.6, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.92, (float)0.7, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.51, (float)0.33, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.4, (float)0.3, 100), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.1, (float)0.05, 100), 1);

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a weak offensive/defensive move, by kicking the monster with her rubber shoe, then readying herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)1.2, (float)1, (float)0.75, (float)0.86, (float)0.5);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, B-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.63, (float)0.29, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.14, (float)0.94, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.83, (float)0.35, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.82, (float)0.21, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.2, (float)0.16, 100), 1);

        break;

    case 6:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda kicks the monster with her shoe, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)1.2, (float)1, (float)1.35, (float)0.86, (float)0.5);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, K+, B-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.64, (float)0.3, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.17, (float)0.97, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.72, (float)0.24, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.83, (float)0.22, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.14, (float)0.08, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.21, (float)0.17, 100), 1);

        break;

    case 7:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda performs a weak offensive combo, by kicking the monster with her rubber shoe, then punching it with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (6, (float)2.1, (float)1, (float)0.8, (float)0.86, (float)0.48);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R+, K-, B-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.79, (float)0.45, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.44, (float)2.04, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.94, (float)0.46, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.84, (float)0.23, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.12, (float)0.04, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.205, (float)0.165, 100), 1);

        break;

    case 8:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kick with foot, repeatedly\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda decides to kick the monster with her rubber shoes, multiple times.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (3, (float)3.3, (float)2.8, (float)1.9, (float)2.3, (float)0.4);
        if (iRet != 0) return iRet;

        // M+, E+, S----, R++, K--, B---
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.67, (float)0.99, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)4.31, (float)3.51, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.42, (float)0.7, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.84, (float)0.62, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.52, (float)0.34, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.6, (float)0.4, 100), 1);

        break;

    case 9:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Paddle feint attack, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to hit the monster with her spanking paddle, then readies herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.3, (float)0.78, (float)1.8, (float)0.3);
        if (iRet != 0) return iRet;

        // S-, R+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.23, (float)1.03, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.89, (float)0.28, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.043, (float)0.031, 100), 1);

        break;

    case 10:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Paddle feint attack, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to hit the monster with her paddle, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.3, (float)1.38, (float)1.8, (float)0.3);
        if (iRet != 0) return iRet;

        // S-, R+, K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.32, (float)1.12, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.9, (float)0.29, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.19, (float)0.13, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.046, (float)0.034, 100), 1);

        break;

    case 11:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Paddle feint attack, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to spank the monster with her paddle, then punches the monster with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.2, (float)1.8, (float)0.8, (float)1.6, (float)0.5);
        if (iRet != 0) return iRet;

        // S--, R+
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.28, (float)0.11, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.74, (float)2.34, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.53, (float)0.29, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.88, (float)0.27, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.049, (float)0.037, 100), 1);

        break;

    case 12:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Paddle feint attack, then hit with spanking paddle\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to hit the monster with her spanking paddle, then hits it with her paddle.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.8, (float)2.1, (float)0.8, (float)2.2, (float)1.1);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)1.4, (float)0.72, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)3.23, (float)2.63, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)1.46, (float)0.74, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)1.87, (float)0.65, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.22, (float)0.14, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.14, (float)0.11, 100), 1);

        break;

    case 13:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to kick the monster with her rubber shoe, then readies herself for the potential counter attack.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.1, (float)0.75, (float)1.1, (float)0.8);
        if (iRet != 0) return iRet;

        // S-, R+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.12, (float)0.92, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.9, (float)0.29, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.26, (float)0.15, 300), 1);

        break;

    case 14:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to the monster with her shoe, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)1.1, (float)1.35, (float)1.1, (float)0.8);
        if (iRet != 0) return iRet;

        // S-, R+, K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.38, (float)1.18, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.92, (float)0.31, 300), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.17, (float)0.11, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.09, (float)0.06, 100), 1);

        break;

    case 15:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda threatens to kick the monster with her rubber shoe, then punches the monster with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.1, (float)2.1, (float)0.7, (float)1.95, (float)1.5);
        if (iRet != 0) return iRet;

        // S--, R+
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.35, (float)0.18, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.42, (float)1.22, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.53, (float)0.29, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.91, (float)0.3, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.1, (float)0.07, 100), 1);

        break;

    case 16:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Foot feint attack, then hit with spanking paddle\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda terrorizes to the monster with her rubber shoes, then spanks the monster with her paddle.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.9, (float)2.1, (float)0.8, (float)1.56, (float)1.3);
        if (iRet != 0) return iRet;

        // M+, E+, S--, R++, K-, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.45, (float)0.28, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)2.05, (float)1.65, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.43, (float)0.19, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)2.01, (float)0.79, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)0.18, (float)0.12, 300), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.135, (float)0.105, 100), 1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structB, actionstate_randomFloatValue ((float)0.1, (float)0.07, 100), 1);

        break;

    case 17:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then block\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda pretends to hesitate, then readies herself for the potential attack by the tentacle monster.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 2;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)0.6, (float)0.6, (float)0.4, (float)0.6);
        if (iRet != 0) return iRet;

        // (no change till the counter, if any)
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.32, (float)0.12, 200), 0);

        break;

    case 18:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then pull back\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda hesitates, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDefensive = 1;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (0, (float)1, (float)0.6, (float)1.25, (float)0.4, (float)0.6);
        if (iRet != 0) return iRet;

        // K+
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.06, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.23, (float)0.17, 300), 6000);

        break;

    case 19:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then punch with fist\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda tactically to hesitates, then punches the monster with her fist.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (2, (float)1.05, (float)0.95, (float)0.92, (float)1.4, (float)1.2);
        if (iRet != 0) return iRet;

        // M+, S-, R+
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.23, (float)0.06, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.21, (float)1.01, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.45, (float)0.21, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.75, (float)0.34, 300), 6000);

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then hit with spanking paddle\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda waits, then hits the monster with her spanking paddle.\n\n");
        if (iRet != 0) return iRet;

        // alter the monster variables according to the move settings.
        iRet = actionstate_randomAct1AlterMonsterValues (1, (float)0.93, (float)2.1, (float)1.7, (float)1.9, (float)2.1);
        if (iRet != 0) return iRet;

        // M+, E+, S-, R+, W-
        actionstate_statAddition (&gstructActStateCharWilda.structE, actionstate_randomFloatValue ((float)0.45, (float)0.28, 500), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1.32, (float)1.21, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, actionstate_randomFloatValue ((float)0.39, (float)0.15, 500), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structR, actionstate_randomFloatValue ((float)0.77, (float)0.36, 300), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structW, actionstate_randomFloatValue ((float)0.145, (float)0.115, 100), 1);

        break;
    }

    //
    // Workout what the monster is going to do.
    //
    iMonsterAction = actionstate_accessAct1MonsterAction ();

    // here is where I apply additional impacts to the PC for the monster action.
    //  0 and 3 have no parameter effect to the PC..
    switch (iMonsterAction)
    {
    case 0: // run away
        if (cDefensive == 2)
            iRet = mutils_addToDialogBuffer ("The tentacle monster appears to be hesitant, then it runs away.\n\n");
        else if (cDefensive != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster, taking advantage of the distance Wilda has given it, takes this opportunity to run away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster moves slightly sideways, then runs away.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 1: // monster sprays goo and runs away
        // increase lust for the goo hit.
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)15, (float)9, 400), 6000);

        if (cDefensive == 2)
            iRet = mutils_addToDialogBuffer ("The tentacle monster retreats a little bit, sprays Wilda with goo, then runs away.\n\n");
        else if (cDefensive != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster moves closer to Wilda, sprays Wilda with goo, then runs away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster runs away, while also spraying Wilda with goo.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 2: // tentacle smash, then runs away

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1, (float)0.4, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.4, (float)2.4, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            // The stamina impact is less, but the gear impact is higher.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 3.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster attacks Wilda it with one of its tentacles, then runs away.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            // impacts on everything is less.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 13.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 7.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster makes a weak attack with one of its tentacles, before running away.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 10.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 7.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster hits Wilda with one of its tentacles, then runs away.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 3: // cower in fear, then run away

        iRndNum = (int)(rand() % 2);

        if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster shuffles to the side, seems to hesitate, then runs away.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster does nothing for a while, then slowly starts to move away, stops again, then it quickly runs away.\n\n");
        if (iRet != 0) return iRet;

        break;

    case 4: // Goo spray, then Tentacle smash.
        // increase lust for the goo hit.
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)25, (float)15, 500), 6000);
        // note: lust is also expanded to taken into account the below.

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.6, (float)2.6, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            // The stamina impact is less, but the gear impact is higher.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 3.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster quickly sprays Wilda with goo, then hits her with a tentacle.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            // impacts on everything is less.
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 13.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 7.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with goo, then performs a rather weak attack with a tentacle.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 10.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 7.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda with some goop, then smacks Wilda with one of its tentacles.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 5: // Cower in fear, then Tentacle smash.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1, (float)0.4, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.6, (float)2.6, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 3.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster waits for a while. Then quickly hits Wilda with one of its tentacles.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 13.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 7.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster lurches to the side, then weakly hits Wilda with one of its tentacles.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 10.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 7.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster shuffles to the side, waits, then pounds Wilda with one of its tentacles.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 6: // Tentacle smash, then Cower in fear.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2, (float)1, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)3.2, (float)2.2, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9.6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6.6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.2), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster quickly slams Wilda with a tentacle, shuffles to the side, then stops.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 14.1), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9.6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 8.1), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster weakly hits Wilda with a tentacle, then just stays there.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 11.1), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 8.1), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 5.1), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster pummels Wilda with a tentacle, then does nothing.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 7: // Tentacle smash x2.

        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)3, (float)2, 200), 6000);

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)7, (float)6.2, 400);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 3.6), 0);

            iRet = mutils_addToDialogBuffer ("Wilda is hit twice in a row, by attacking tentacles from the tentacle monster.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 13.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 7.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster attacks Wilda, rather weakly, with two hits from its tentacles.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 10.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 7.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.5), 0);

            iRet = mutils_addToDialogBuffer ("Wilda receives two quick and heavy hits from the tentacle monster.\n\n");
        }
        if (iRet != 0) return iRet;

        break;

    case 8: // Tentacle smash x3.
        // Note: it is unlikely that this move will be used in act2, because this move is only triggered for the first
        //  monster in act1, but I allow for it anyway.

        // base figure..
        // a lot takes a hit for a tentacle smash.
        fStaDec = actionstate_randomFloatValue ((float)10, (float)8, 300);

        // the impacts are different if the PC is defensive, near the monster.
        if (cDefensive == 2)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 6), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 3.6), 0);

            iRet = mutils_addToDialogBuffer ("Wilda is pummeled by a barrage of tentacle attacks.\n\n");
        }
        // the impacts are different if the PC is further back from the monster.
        else if (cDefensive != 0)
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec / 1.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 13.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 9), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 7.5), 0);

            iRet = mutils_addToDialogBuffer ("Wilda receives a weak pummeling from the tentacle monster.\n\n");
        }
        // the PC is near the monster and NOT defensive.
        else
        {
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 1.2), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structW, (float)(fStaDec / 10.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structB, (float)(fStaDec / 7.5), 0);
            actionstate_statSubtraction (&gstructActStateCharWilda.structC, (float)(fStaDec / 4.5), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster rains a series of tentacle strikes down on Wilda.\n\n");
        }
        if (iRet != 0) return iRet;

        break;
    }

    iRndNum = (int)(rand() % 3);

    if (iMonsterAction < 4)
    {
        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("As Wilda watches as the monster scampers away through the liquid, she keeps her paddle ready.");
        else if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("As the monster continues to make its retreat, Wilda waits to see if it decides to return.");
        else
            iRet = mutils_addToDialogBuffer ("Wilda keeps her spanking paddle ready, in case another tentacle monster decides to show up.");
        if (iRet != 0) return iRet;

        // pass control over to the exit scene.
        iRet = gamelogic04_scene1052 (0, cSubFlag + 1);
        return iRet;
    }

    if (gstructActStateGlobal.sAct2Monsters < 5)
    {
        if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("Neither the tentacle monster or Wilda are showing any signs of retreating.\n\n");
        else if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("Wilda decides that she is not going to show her back to this opponent.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda and the tentacle monster are still facing each other.\n\n");
        if (iRet != 0) return iRet;
    }

    iRet = gamelogic04_scene1050 (0, cSubFlag + 1);
    return iRet;
}

//
// Act 2 combat exit.
//
int gamelogic04_scene1052 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // increment the counter
    if (gstructActStateGlobal.sAct2Monsters < 30)
        gstructActStateGlobal.sAct2Monsters++;

    // set the monster to being no longer active.
    gstructActStateOpponent.cActive = 0;

    // set the array to say that we had an encounter.
    gstructActStateGlobal.caEncounterArray[0] = 1;

    iRet = mutils_addToDialogBuffer ("\n\n\n[1 minute later...]\n\nWilda decides to put her paddle away.\n\n");
    if (iRet != 0) return iRet;

    iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    return iRet;
}

//
// Setup/Continue the Act 3 combat moves.
//
int gamelogic04_scene1060 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if ((gstructActStateGlobal.caAct3UnlockArray[0] != 0) && (gstructActStateGlobal.caAct3UnlockArray[1] != 0))
    {
        iRet = mutils_addToCommandList ("Massage breasts, then pull back", 1061, 1);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[1] != 0) && (gstructActStateGlobal.caAct3UnlockArray[2] != 0))
    {
        iRet = mutils_addToCommandList ("Massage breasts, then blow kiss", 1061, 2);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[1] != 0)
    {
        iRet = mutils_addToCommandList ("Massage breasts repeatedly", 1061, 3);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[1] != 0) && (gstructActStateGlobal.caAct3UnlockArray[3] != 0))
    {
        iRet = mutils_addToCommandList ("Massage breasts, then pinch clitoris", 1061, 4);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[1] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Massage breasts, then wiggle butt", 1061, 5);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[1] != 0) && (gstructActStateGlobal.caAct3UnlockArray[7] != 0))
    {
        iRet = mutils_addToCommandList ("Massage breasts, then ask Crystal to join in", 1061, 6);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[6] != 0) && (gstructActStateGlobal.caAct3UnlockArray[2] != 0))
    {
        iRet = mutils_addToCommandList ("Kneel down, then blow kiss", 1061, 7);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[6] != 0) && (gstructActStateGlobal.caAct3UnlockArray[1] != 0))
    {
        iRet = mutils_addToCommandList ("Kneel down, then massage breasts", 1061, 8);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[6] != 0) && (gstructActStateGlobal.caAct3UnlockArray[3] != 0))
    {
        iRet = mutils_addToCommandList ("Kneel down, then pinch clitoris", 1061, 9);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[6] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Kneel down, then wiggle butt", 1061, 10);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[6] != 0) && (gstructActStateGlobal.caAct3UnlockArray[7] != 0))
    {
        iRet = mutils_addToCommandList ("Kneel down, then ask Crystal to join in", 1061, 11);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[4] != 0) && (gstructActStateGlobal.caAct3UnlockArray[0] != 0))
    {
        iRet = mutils_addToCommandList ("Wiggle butt, then pull back", 1061, 12);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[2] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Wiggle butt, then blow kiss", 1061, 13);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[1] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Wiggle butt, then massage breasts", 1061, 14);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[3] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Wiggle butt, then pinch clitoris", 1061, 15);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[4] != 0)
    {
        iRet = mutils_addToCommandList ("Wiggle butt repeatedly", 1061, 16);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[4] != 0) && (gstructActStateGlobal.caAct3UnlockArray[7] != 0))
    {
        iRet = mutils_addToCommandList ("Wiggle butt, then ask Crystal to join in", 1061, 17);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[0] != 0) && (gstructActStateGlobal.caAct3UnlockArray[5] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then pull back", 1061, 18);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[5] != 0) && (gstructActStateGlobal.caAct3UnlockArray[2] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then blow kiss", 1061, 19);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[5] != 0) && (gstructActStateGlobal.caAct3UnlockArray[1] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then massage breasts", 1061, 20);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[5] != 0) && (gstructActStateGlobal.caAct3UnlockArray[3] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then pinch clitoris", 1061, 21);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[5] != 0) && (gstructActStateGlobal.caAct3UnlockArray[4] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then wiggle butt", 1061, 22);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[5] != 0) && (gstructActStateGlobal.caAct3UnlockArray[7] != 0))
    {
        iRet = mutils_addToCommandList ("Finger pussy, then ask Crystal to join in", 1061, 23);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[0] != 0)
    {
        iRet = mutils_addToCommandList ("Do nothing, then pull back", 1061, 24);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[2] != 0)
    {
        iRet = mutils_addToCommandList ("Do nothing, then blow kiss", 1061, 25);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[1] != 0)
    {
        iRet = mutils_addToCommandList ("Do nothing, then massage breasts", 1061, 26);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[3] != 0)
    {
        iRet = mutils_addToCommandList ("Do nothing, then pinch clitoris", 1061, 27);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.caAct3UnlockArray[4] != 0)
    {
        iRet = mutils_addToCommandList ("Do nothing, then wiggle butt", 1061, 28);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.caAct3UnlockArray[7] != 0) && (iSubSceneId == 0))
    {
        iRet = mutils_addToCommandList ("Ask Crystal what to do", 1063, 1);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// Execution of the Act 3 combat moves.
//
int gamelogic04_scene1061 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iRndNum;
    int iMonsterAction;
    float fEndInc;
    float fStaDec;
    float fMigInc;
    float fVagInc;
    float fOraInc;
    float fKarInc;
    float fFriDec;
    float fLusDec;
    char cAction1;
    char cAction2;
    char cDesc = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts, then pull back\n\n");
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer ("Wilda lightly massages her breasts, then pulls back, giving the tentacle monster some more space.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 1; // (massage breasts)
        cAction2 = 5; // (pull back)

        actionstate_hardAlterMonsterValues (-3, -5, actionstate_randomIntValue (2, 1), actionstate_randomIntValue (3, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (1, 1, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.36, (float)0.26, 400), 0);

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // (massage breasts)
        cAction2 = 2; // (blow kiss)

        actionstate_hardAlterMonsterValues (-2, -2, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.34, (float)0.24, 400), 0);

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts repeatedly\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda spends some time throughly massaging her breasts, occasionally shifting from her breasts to her nipples and back again.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda massages her breasts over and over again, pausing a couple of times to play with her nipples.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda massages her breasts then switches to rubbing them together as if she is giving the tentacle monster a tit-fuck. She then lightly drools into the crevice between them.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 1; // (massage breasts)
        cAction2 = 0; // (repeat action 1)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -2, actionstate_randomIntValue (5, 2), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 3, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)1, (float)0.7, 400), 0);

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // (massage breasts)
        cAction2 = 3; // (pinch clitoris)

        actionstate_hardAlterMonsterValues (1, -3, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.82, (float)0.62, 400), 0);

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // (massage breasts)
        cAction2 = 4; // (wiggle butt)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -2, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (5, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.92, (float)0.7, 400), 0);

        break;

    case 6:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Massage breasts, then ask Crystal to join in\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // (massage breasts)
        cAction2 = 6; // (ask for crystal's help)

        actionstate_hardAlterMonsterValues (0, 0, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (2, 0), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 0, 1);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.34, (float)0.24, 400), 0);

        break;

    case 7:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kneel down, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // (kneel down)
        cAction2 = 2; // (blow kiss)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -5, actionstate_randomIntValue (5, 2), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 2, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.21, 400), 0);

        break;

    case 8:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kneel down, then massage breasts\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // (kneel down)
        cAction2 = 1; // (massage breasts)

        actionstate_hardAlterMonsterValues (-2, -5, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.56, (float)0.36, 400), 0);

        break;

    case 9:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kneel down, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // (kneel down)
        cAction2 = 3; // (pinch clitoris)

        actionstate_hardAlterMonsterValues (-2, -5, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.83, (float)0.63, 400), 0);

        break;

    case 10:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kneel down, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // (kneel down)
        cAction2 = 4; // (wiggle butt)

        actionstate_hardAlterMonsterValues (-2, -4, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (2, 0), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 3, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.9, (float)0.68, 400), 0);

        break;

    case 11:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Kneel down, then ask Crystal to join in\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // (kneel down)
        cAction2 = 6; // (ask for crystal's help)

        actionstate_hardAlterMonsterValues (0, 0, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (2, 0), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 1, 1);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.21, 400), 0);

        break;

    case 12:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt, then pull back\n\n");
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer ("Wilda lightly shakes her butt at the tentacle monster, then steps away, increasing her distance from the the monster.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 4; // (wiggle butt)
        cAction2 = 5; // (pull back)

        actionstate_hardAlterMonsterValues (-2, -4, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (2, 0), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (1, 0, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.32, (float)0.22, 400), 0);

        break;

    case 13:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // (wiggle butt)
        cAction2 = 2; // (blow kiss)

        actionstate_hardAlterMonsterValues (-1, 0, actionstate_randomIntValue (4, 2), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 2, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.31, (float)0.21, 400), 0);

        break;

    case 14:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt, then massage breasts\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // (wiggle butt)
        cAction2 = 1; // (massage breasts)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -2, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.65, (float)0.45, 400), 0);

        break;

    case 15:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // (wiggle butt)
        cAction2 = 3; // (pinch clitoris)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (2, -1), 0, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (4, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 3, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.76, (float)0.56, 400), 0);

        break;

    case 16:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt repeatedly\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda turns around, so her butt is facing the tentacle monster, then gyrates her hips over and over again.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda spends a bit of time swaying her hips from side to side, while turning around so that the tentacle monster can get a better view of her ass, then she lightly rocks her butt back and forth.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda spins around then spends some time bucking her hips up and down as if she is riding a horse... or the tentacle of a tentacle monster.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 4; // (wiggle butt)
        cAction2 = 0; // (repeat action 1)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -1, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (2, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 4, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.95, (float)0.65, 400), 0);

        break;

    case 17:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Wiggle butt, then ask Crystal to join in\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // (wiggle butt)
        cAction2 = 6; // (ask for crystal's help)

        actionstate_hardAlterMonsterValues (0, 0, actionstate_randomIntValue (1, 0), actionstate_randomIntValue (2, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 2, 1);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.34, (float)0.24, 400), 0);

        break;

    case 18:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then pull back\n\n");
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer ("Wilda fingers her pussy for a little bit, then moves away from the tentacle monster.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 3; // (finger pussy)
        cAction2 = 5; // (pull back)

        actionstate_hardAlterMonsterValues (-2, -4, actionstate_randomIntValue (1, 0), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (1, 0, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.39, (float)0.29, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 19:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // (finger pussy)
        cAction2 = 2; // (blow kiss)

        actionstate_hardAlterMonsterValues (1, -2, actionstate_randomIntValue (4, 2), actionstate_randomIntValue (6, 2), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 2, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.38, (float)0.28, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 20:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then massage breasts\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // (finger pussy)
        cAction2 = 1; // (massage breasts)

        actionstate_hardAlterMonsterValues (0, -2, actionstate_randomIntValue (4, 0), actionstate_randomIntValue (3, 0), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.59, (float)0.39, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 21:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // (finger pussy)
        cAction2 = 3; // (pinch clitoris)

        actionstate_hardAlterMonsterValues (1, -2, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (4, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 3, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.67, (float)0.47, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 22:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // (finger pussy)
        cAction2 = 4; // (wiggle butt)

        actionstate_hardAlterMonsterValues (-1, -1, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 3, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.63, (float)0.43, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 23:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy, then ask Crystal to join in\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // (finger pussy)
        cAction2 = 6; // (ask for crystal's help)

        actionstate_hardAlterMonsterValues (0, 0, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 2, 1);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.39, (float)0.29, 400), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.04, (float)0.02, 20), 6000);

        break;

    case 24:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then pull back\n\n");
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer ("Wilda waits, then pulls back, allowing the monster a better chance to escape.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have a description for this action already, don't work with the action values below.

        cAction1 = 0; // (do nothing)
        cAction2 = 5; // (pull back)

        actionstate_hardAlterMonsterValues (-4, -4, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (1, 0, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.14, (float)0.04, 400), 0);

        break;

    case 25:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 0; // (do nothing)
        cAction2 = 2; // (blow kiss)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (0, -3), -2, actionstate_randomIntValue (3, 0), actionstate_randomIntValue (4, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 2, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.24, (float)0.14, 400), 0);

        break;

    case 26:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then massage breasts\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 0; // (do nothing)
        cAction2 = 1; // (massage breasts)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (0, -4), -3, actionstate_randomIntValue (3, 1), actionstate_randomIntValue (5, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 1, 0, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.24, (float)0.14, 400), 0);

        break;

    case 27:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 0; // (do nothing)
        cAction2 = 3; // (pinch clitoris)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (0, -3), -2, actionstate_randomIntValue (2, 1), actionstate_randomIntValue (3, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 1, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.27, (float)0.17, 400), 0);

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Do nothing, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 0; // (do nothing)
        cAction2 = 4; // (wiggle butt)

        actionstate_hardAlterMonsterValues (actionstate_randomIntValue (1, -2), -1, actionstate_randomIntValue (2, 0), actionstate_randomIntValue (4, 1), 0);
        iMonsterAction = actionstate_accessAct3MonsterAction (0, 0, 2, 0);

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.24, (float)0.14, 400), 0);

        break;
    }

    //
    // Description logic goes here.
    //
    if (cDesc == 0)
    {
        // Note: I decided to do the random evaluation inside each case evaluation, in case I decide to expand the number
        //  of RNG possibilities for the dialog.

        switch (cAction1)
        {
        case 0: // action 1 = 0 (do nothing)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda waits for a while, to tease the tentacle monster.");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda pauses for a while, watching as the tentacle monster starts to become a little bit more interested.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda waits as the tentacle monster starts to show some more excitement.");

            break;

        case 1: // action 1 = 1 (massage breasts)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda plays with her breasts for a while.");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda rubs her breasts, then plays with her nipples for a little while.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda fondles her own breasts while looking at the tentacle monster.");

            break;

        case 2: // action 1 = 2 (kneel down)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda looks at the tentacle monster, then parts her legs slightly and kneels down in the liquid.");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("While the tentacle monster observes Wilda, she sinks down into the liquid and parts her legs.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda slowly sinks to her knees, into the liquid, in front of the tentacle monster.");

            break;

        case 3: // action 1 = 3 (finger pussy)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda starts to circle her finger around her clitoris a couple of times before shoving 3 fingers inside her pussy.");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("While the tentacle monster watches, Wilda starts playing with her pussy lips, inserts two fingers and pries her pussy open.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda inserts a finger into her pussy a few of times, adding an extra finger every second thrust.");

            break;

        case 4: // action 1 = 4 (wiggle butt)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda lightly gyrates her hips, before switching to shaking her butt up and down.");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda gyrates her butt in a clockwise motion a couple of times, before switching to anti-clockwise for a couple more.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda parts her legs a little bit and shakes her butt from side to side.");

            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer (" Then, ");
        if (iRet != 0) return iRet;

        switch (cAction2)
        {
        // Note: 0 (repeat action 1), is already handled back above..

        case 1: // action 2 = 1 (massage breasts)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda switches to massaging her own breasts, and playing with her nipples.\n\n");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda starts playing with her nipples, circling them with her fingers, before finishing up by rubbing her breasts together.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda changes over to massaging and rubbing her breasts.\n\n");

            break;

        case 2: // action 2 = 2 (blow kiss)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda puckers up her lips and blows a kiss at the tentacle monster.\n\n");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda starts to sensuously suck on her right index finger, and pulls it out of her mouth while also blowing a kiss, causing a string of spittle to fly off the end of her index finger.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda licks her lips, twirls her tongue around inside her mouth, and finishes up with blowing a kiss at the tentacle monster.\n\n");

            break;

        case 3: // action 2 = 3 (pinch clitoris)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda switches to lightly fingering her clitoris, before lightly pinching it and letting out a low moan.\n\n");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda starts to rub her clitoris up and down, then side to side, before pinching her clitoris while lightly bucking her hips.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda changes to repeatedly switching between fingering her clitoris and pinching it, a couple of times.\n\n");

            break;

        case 4: // action 2 = 4 (wiggle butt)
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 2)
                iRet = mutils_addToDialogBuffer ("Wilda starts to lightly rub both of her hands all over both of her ass cheeks.\n\n");
            else if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("Wilda shifts to make a light rocking motion with her ass, escalating to shaking her butt up and down.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda switches to gyrating her hips around and around.\n\n");

            break;

        // Note: 5 (pull back), is already handled back above..

        case 6: // action 2 = 6 (ask for crystal's help)
            iRndNum = (int)(rand() % 4);

            switch (iRndNum)
            {
            case 0:
                iRet = mutils_addToDialogBuffer ("Wilda then looks over at Crystal and asks \"Want to join in?\"\n\nCrystal responds \"I thought you would never ask\".");
                break;

            case 1:
                iRet = mutils_addToDialogBuffer ("Wilda then glances at Crystal and notices that she is fidgeting. Wilda asks Crystal \"I guess I could use a hand here\".\n\nCrystal licks her lips and replies \"You look like you need some assistance\".");
                break;

            case 2:
                iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal, who is observing Wilda's lewd display and starts to ask \"Would you\"...\n\nCrystal just replies \"Yes\".");
                break;

            default:
                iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal with a deviant smile and motions for Crystal to come over with her right index finger.\n\nCrystal\'s smile gets bigger and she nods her head.");
                break;
            }
            if (iRet != 0) return iRet;

            switch (cAction1)
            {
            // action 1 = 0 (do nothing), is not associated with action 2 = 6

            case 1: // action 1 = 1 (massage breasts)
                iRndNum = (int)(rand() % 2);

                if (iRndNum == 0)
                    iRet = mutils_addToDialogBuffer (" Crystal then saunters over to Wilda and joins in massaging her breasts.\n\n");
                else
                    iRet = mutils_addToDialogBuffer (" Crystal then walks over behind Wilda and starts groping Wilda\'s breasts.\n\n");
                break;

            case 2: // action 1 = 2 (kneel down)
                iRet = mutils_addToDialogBuffer (" Crystal then walks over next to Wilda and kneels down next to her.\n\n");
                break;

            case 3: // action 1 = 3 (finger pussy)
                iRndNum = (int)(rand() % 2);

                if (iRndNum == 0)
                    iRet = mutils_addToDialogBuffer (" Crystal moves over next to Wilda, and starts fingering her own pussy as well.\n\n");
                else
                    iRet = mutils_addToDialogBuffer (" Crystal then walks behind Wilda, and starts fingering Wilda's pussy while standing behind Wilda.\n\n");
                break;

            case 4: // action 1 = 4 (wiggle butt)
                iRndNum = (int)(rand() % 2);

                if (iRndNum == 0)
                    iRet = mutils_addToDialogBuffer (" Crystal saunters over next to Wilda, and joins in with the ass shaking.\n\n");
                else
                    iRet = mutils_addToDialogBuffer (" Crystal then walks over next to Wilda, and then starts groping Wilda\'s butt.\n\n");
                break;
            }

            break;
        }
        if (iRet != 0) return iRet;
    }

    // for the monster to just run off like that, with Wilda providing an opening, she is going to be chewed out by Crystal.
    if ((cAction2 == 5) && ((iMonsterAction == 0) || (iMonsterAction == 1)))
    {
        if (iMonsterAction == 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster just runs away.\n\n");
        else
        {
            actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)15, (float)9, 400), gstructActStateCharWilda.structF.iNum);
            actionstate_statAddition (&gstructActStateCharCrystal.structL, actionstate_randomFloatValue ((float)10, (float)4, 400), gstructActStateCharCrystal.structF.iNum);

            iRet = mutils_addToDialogBuffer ("The tentacle monster quickly sprays Wilda and Crystal with goo, then runs away.\n\n");
        }

        iRet = mutils_addToDialogBuffer ("Wilda and Crystal watch as the tentacle monster scampers away, splashing liquid everywhere. Crystal looks at Wilda and asks \"What were you doing?\"\n\nWilda looks at Crystal, and only muster \"That was... a defensive action... maybe\"...\n\nCrystal breathes in, then tells Wilda \"You mustn't back down... Don\'t do that again\"...\n\nWilda responds \"Okay\"...\n\n");
        if (iRet != 0) return iRet;

        actionstate_statAddition (&gstructActStateCharWilda.structK, actionstate_randomFloatValue ((float)3, (float)1, 100), 6000);
        actionstate_statAddition (&gstructActStateCharCrystal.structK, actionstate_randomFloatValue ((float)2, (float)1, 100), 6000);

        // turn off the allow back-away flag.
        gstructActStateGlobal.caAct3UnlockArray[0] = 0;

        // set the monster to being no longer active.
        gstructActStateOpponent.cActive = 0;

        // reset the array to say that we had an encounter (so that we are more likely to run into a monster sooner).
        gstructActStateGlobal.caEncounterArray[0] = 0;

        // switch back to navigation.
        iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
        return iRet;
    }

    // setup the start of the random monster reaction dialog.
    if (iMonsterAction > 1)
    {
        iRndNum = (int)(rand() % 4);

        switch (iRndNum)
        {
        case 0:
            iRet = mutils_addToDialogBuffer ("The tentacle monster moves towards Wilda");
            break;

        case 1:
            iRet = mutils_addToDialogBuffer ("The tentacle monster excitedly advances towards Wilda");
            break;

        case 2:
            iRet = mutils_addToDialogBuffer ("The tentacle monster slowly approaches Wilda");
            break;

        default:
            iRet = mutils_addToDialogBuffer ("The tentacle monster erratically moves towards Wilda");
            break;
        }
        if (iRet != 0) return iRet;

        if (cAction2 == 6)
            iRet = mutils_addToDialogBuffer (" and Crystal.\n\n\n");
        else
            iRet = mutils_addToDialogBuffer (".\n\n\n");
        if (iRet != 0) return iRet;
    }

    switch (iMonsterAction)
    {
    case 0: // just run away
        iRet = mutils_addToDialogBuffer ("The tentacle monster just runs away.\n\n");
        if (iRet != 0) return iRet;

        // set the array to say that we didn't have an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 0;

        break;

    case 1: // spray goo and run away
        iRet = mutils_addToDialogBuffer ("The tentacle monster sprays Wilda and Crystal with goo, then runs away.\n\n");
        if (iRet != 0) return iRet;

        if (gstructActStateGlobal.sAct3Monsters < 4)
        {
            iRet = mutils_addToDialogBuffer ("As the tentacle monster makes its hasty retreat, Crystal looks at Wilda \"Sometimes our masters can be a bit timid, but don\'t worry about it\"...\n\n");
            if (iRet != 0) return iRet;
        }

        // increase lust for the goo hit.
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)15, (float)9, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharCrystal.structL, actionstate_randomFloatValue ((float)10, (float)4, 400), gstructActStateCharCrystal.structF.iNum);

        // set the array to say that we didn't have an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 0;

        break;

    case 2: // quick pussy violation
        fStaDec = actionstate_randomFloatValue ((float)1.15, (float)0.85, 400);
        fEndInc = (float)(fStaDec / 2.5);
        fMigInc = (float)(fStaDec / 4.5);
        fVagInc = (float)(fStaDec / 1.5);
        fKarInc = (float)(fStaDec / 1.5);
        fFriDec = (float)(fStaDec / 5);
        fLusDec = (float)(fStaDec / 11);

        if (fStaDec > (float)1)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        // if crystal is involved, then the stats are spread across Wilda and Crystal
        if (cAction2 == 6)
        {
            // first adjust the values for Wilda
            actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fFriDec * 0.6), 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fLusDec * 0.6), 0);

            // then adjust the values for Crystal
            actionstate_statAddition (&gstructActStateCharCrystal.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharCrystal.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structF, (float)(fFriDec * 0.6), 24);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structL, (float)(fLusDec * 0.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Crystal and Wilda's pussies, pulls its tentacles out them, and moves away from both women.\n\n");
            if (iRet != 0) return iRet;
        }
        // otherwise, it is just Wilda
        else
        {
            actionstate_statAddition (&gstructActStateCharWilda.structE, fEndInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, fMigInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, fVagInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, fKarInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, fFriDec, 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, fLusDec, 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Wilda's pussy, pulls its tentacle out of her, and moves away from Wilda.\n\n");
            if (iRet != 0) return iRet;
        }

        // set the array to say that we had an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 1;

        break;

    case 3: // quick mouth violation
        fStaDec = actionstate_randomFloatValue ((float)1, (float)0.75, 400);
        fEndInc = (float)(fStaDec / 2.5);
        fMigInc = (float)(fStaDec / 4.5);
        fOraInc = (float)(fStaDec / 1.5);
        fKarInc = (float)(fStaDec / 1.5);
        fFriDec = (float)(fStaDec / 5);
        fLusDec = (float)(fStaDec / 11);

        if (fStaDec > (float)0.9)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        // if crystal is involved, then the stats are spread across Wilda and Crystal
        if (cAction2 == 6)
        {
            // first adjust the values for Wilda
            actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fFriDec * 0.6), 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fLusDec * 0.6), 0);

            // then adjust the values for Crystal
            actionstate_statAddition (&gstructActStateCharCrystal.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharCrystal.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structF, (float)(fFriDec * 0.3), 24);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structL, (float)(fLusDec * 0.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Crystal and Wilda's mouthes, pulls its tentacles out of their throats, and moves away from both women.\n\n");
            if (iRet != 0) return iRet;
        }
        // otherwise, it is just Wilda
        else
        {
            actionstate_statAddition (&gstructActStateCharWilda.structE, fEndInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, fMigInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, fOraInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, fKarInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, fFriDec, 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, fLusDec, 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Wilda's mouth, pulls its tentacle out of Wilda, and moves away from her.\n\n");
            if (iRet != 0) return iRet;
        }

        // set the array to say that we had an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 1;

        break;

    case 4: // quick mouth & pussy violation
        fStaDec = actionstate_randomFloatValue ((float)1.6, (float)1.3, 400);
        fEndInc = (float)(fStaDec / 2.5);
        fMigInc = (float)(fStaDec / 4.5);
        fVagInc = (float)(fStaDec / 2);
        fOraInc = (float)(fStaDec / 2);
        fKarInc = (float)(fStaDec / 2);
        fFriDec = (float)(fStaDec / 6);
        fLusDec = (float)(fStaDec / 16);

        if (fStaDec > (float)1.45)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        // if crystal is involved, then the stats are spread across Wilda and Crystal
        if (cAction2 == 6)
        {
            // first adjust the values for Wilda
            actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fFriDec * 0.6), 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fLusDec * 0.6), 0);

            // then adjust the values for Crystal
            actionstate_statAddition (&gstructActStateCharCrystal.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharCrystal.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structF, (float)(fFriDec * 0.3), 24);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structL, (float)(fLusDec * 0.6), 0);

            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Crystal and Wilda's pussies and mouthes, then pulls its tentacles out of them, and moves away from both women.\n\n");
            if (iRet != 0) return iRet;
        }
        // otherwise, it is just Wilda
        else
        {
            actionstate_statAddition (&gstructActStateCharWilda.structE, fEndInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, fMigInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, fVagInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, fOraInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, fKarInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, fFriDec, 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, fLusDec, 0);

            iRndNum = (int)(rand() % 2);

            if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Wilda's mouth and pussy, removes its tentacles from of her, and moves away from Wilda.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("The tentacle monster finishes violating Wilda's pussy and mouth, pulls its tentacles out of Wilda, and moves away from her.\n\n");
            if (iRet != 0) return iRet;
        }

        // set the array to say that we had an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 1;

        break;

    default: // case 5:  // long mouth & pussy violation
        fStaDec = actionstate_randomFloatValue ((float)10, (float)8, 400);
        fEndInc = (float)(fStaDec / 4);
        fMigInc = (float)(fStaDec / 6.5);
        fVagInc = (float)(fStaDec / 6.5);
        fOraInc = (float)(fStaDec / 6.5);
        fKarInc = (float)(fStaDec / 6.5);
        fFriDec = (float)(fStaDec / 30);
        fLusDec = (float)(fStaDec / 100);

        if (fStaDec > (float)9)
            iRet = mutils_addToDialogBuffer ("[11 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[10 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        // if crystal is involved, then the stats are spread across Wilda and Crystal
        if (cAction2 == 6)
        {
            // first adjust the values for Wilda
            actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fFriDec * 0.6), 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fLusDec * 0.6), 0);

            // then adjust the values for Crystal
            actionstate_statAddition (&gstructActStateCharCrystal.structE, (float)(fEndInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)(fStaDec * 0.6), 0);
            actionstate_statAddition (&gstructActStateCharCrystal.structM, (float)(fMigInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structV, (float)(fVagInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structO, (float)(fOraInc * 0.6), 6000);
            actionstate_statAddition (&gstructActStateCharCrystal.structK, (float)(fKarInc * 0.6), 6000);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structF, (float)(fFriDec * 0.3), 24);
            actionstate_statSubtraction (&gstructActStateCharCrystal.structL, (float)(fLusDec * 0.6), 0);

            iRndNum = (int)(rand() % 2);

            if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("After a reasonable fuck-fest, the tentacle monster stops raping the mouthes and pussies of both Wilda and Crystal, pulls its tentacles out of the women, and moves away from both of them.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("The tentacle monster finishes its fuck session with the mouthes and pussies of Crystal and Wilda, sets both of the women down, pulls out its tentacles and moves away from the pair of them.\n\n");
            if (iRet != 0) return iRet;
        }
        // otherwise, it is just Wilda
        else
        {
            actionstate_statAddition (&gstructActStateCharWilda.structE, fEndInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
            actionstate_statAddition (&gstructActStateCharWilda.structM, fMigInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structV, fVagInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structO, fOraInc, 6000);
            actionstate_statAddition (&gstructActStateCharWilda.structK, fKarInc, 6000);
            actionstate_statSubtraction (&gstructActStateCharWilda.structF, fFriDec, 24);
            actionstate_statSubtraction (&gstructActStateCharWilda.structL, fLusDec, 0);

            iRndNum = (int)(rand() % 3);

            if (iRndNum == 1)
                iRet = mutils_addToDialogBuffer ("The tentacle monster finishes up with Wilda\'s pussy and mouth, pulls its tentacles out of her, sets her down and starts to stagger away from her.\n\n");
            else if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("Wilda finally is finally set down by the tentacle monster after it had finished with her mouth and pussy. The tentacles retreat from Wilda, and then the monster itself starts to shamble away through the liquid.\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda's mouth and pussy are finally vacated by the tentacles, as the tentacle monster sets her down and starts to move away from her.\n\n");
            if (iRet != 0) return iRet;
        }

        // set the array to say that we had an encounter.
        gstructActStateGlobal.caEncounterArray[0] = 1;

        break;
    }

    if (iMonsterAction > 1)
    {
        if (cAction2 == 6)
        {
            iRndNum = (int)(rand() % 2);

            if (iRndNum == 0)
            {
                if (iMonsterAction == 1)
                    iRet = mutils_addToDialogBuffer ("Wilda watches as the monster starts to retreat quickly, then looks at Crystal. Crystal's smile is slightly larger.");
                else
                    iRet = mutils_addToDialogBuffer ("Wilda watches as the monster starts to scamper away from Wilda and Crystal. Wilda then looks at Crystal to see that Crystal's smile is slightly larger than before, as goop slowly leaks out of Crystal's mouth.");
            }
            else
            {
                iRet = mutils_addToDialogBuffer ("Wilda then watches as the tentacle monster starts to move away from Crystal and her quickly.");
            }

            if (iRet != 0) return iRet;

            if (iMonsterAction == 5)
                iRet = mutils_addToDialogBuffer ("\n\n\n[2 minutes later...]\n\n");
            else
                iRet = mutils_addToDialogBuffer ("\n\n\n[1 minute later...]\n\n");

            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("Wilda and Crystal finally recover enough to continue.\n\n");
        }
        else
        {
            iRndNum = (int)(rand() % 3);

            if (iRndNum == 1)
                iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal, who just continues stare and smile at the tentacle monster, while still fingering herself. Wilda is then distracted by the tentacle monster as it speeds up its departure from the two women.");
            else if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("Wilda then staggers to remain standing as the tentacle monster starts to increase its speed and run away from the two women.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda considers following the tentacle monster, to have more fun with it, when the tentacle monster starts to retreat from the two women faster.");

            if (iRet != 0) return iRet;

            if (iMonsterAction == 5)
                iRet = mutils_addToDialogBuffer ("\n\n\n[2 minutes later...]\n\n");
            else
                iRet = mutils_addToDialogBuffer ("\n\n\n[1 minute later...]\n\n");

            if (iRet != 0) return iRet;

            iRndNum = (int)(rand() % 4);

            if (iRndNum == 1)
                iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and asks \"Are you okay?\"\n\nWilda responds \"Yes... We should get going\".\n\n");
            else if (iRndNum == 0)
                iRet = mutils_addToDialogBuffer ("Wilda takes a deep breath, stands up and tells Crystal \"We should continue\".\n\nCrystal, without looking at Wilda, and still masturbating, responds \"Yes, we should... for everything is according to the will of our lord and master... Cock\".\n\nCrystal stops talking and looks at Wilda. Wilda replies \"Okay then\"...\n\n");
            else
                iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal, who is still masturbating, and tells Crystal \"I should be good to go\".\n\nCrystal just looks at Wilda and nods.\n\n");
        }
        if (iRet != 0) return iRet;
    }

    // increment the counter
    if (gstructActStateGlobal.sAct3Monsters < 40)
        gstructActStateGlobal.sAct3Monsters++;

    // set the monster to being no longer active.
    gstructActStateOpponent.cActive = 0;

    iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    return iRet;
}

//
// Act 3 Ask Crystal.
//
int gamelogic04_scene1063 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iCount = 0;
    int iOffset;
    int iRndValue;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        iRet = mutils_addToDialogBuffer (">Ask Crystal what to do\n\n");
        if (iRet != 0) return iRet;
    }

    // hard alter the current monster values, while waiting around and talking to Crystal.
    actionstate_hardAlterMonsterValues (-2, -2, 2, 2, 0);

    // load in the array data.
    for (iOffset = 1; iOffset < 7; iOffset++)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[iOffset] != 0)
        {
            iCount++;
        }
    }

    // if the counter is beyond a certain value, just let the drop through (zero entry) handle it.
    if (iCount >= 5)
    {
        iOffset = 1;
    }
    else
    {
        // attempt at randomizing things..
        iRndValue = (int)(rand() % 6);
        iOffset = iRndValue + 1;

        // if the random selection is already enabled, set the offset to 1, and let the march through take care of it.
        if (gstructActStateGlobal.caAct3UnlockArray[iOffset] == 1)
            iOffset = 1;
        // selecting 5 (Finger Pussy) without anything else selected WILL result in a fault (no menu items available) if offset 0 is already off.
        else if ((iOffset == 5) && (iCount < 1))
        // I am not going to bother checking offset 0, because it can be turned off later, causing the crash anyway.
        {
            // so to avoid this, I am going to set the offset to 3.
            iOffset = 3;
            // if 5 is selected later, great, it works with other items, but cannot work by itself.
        }
    }

    // this is the zero entry lock (march through)..
    if (iOffset == 1)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[1] == 1)
            iOffset = 2;
    }
    if (iOffset == 2)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[2] == 1)
            iOffset = 3;
    }
    if (iOffset == 3)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[3] == 1)
            iOffset = 4;
    }
    if (iOffset == 4)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[4] == 1)
            iOffset = 5;
    }
    if (iOffset == 5)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[5] == 1)
            iOffset = 6;
    }
    if (iOffset == 6)
    {
        if (gstructActStateGlobal.caAct3UnlockArray[6] == 1)
        {
            // to have reached this point, means that the PC already knows all of the potential moves.. time to turn Crystal's involvement off.
            gstructActStateGlobal.caAct3UnlockArray[7] = 0;

            iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"Is there\"...\n\nCrystal quietly interjects \"You are more than capable of handling this yourself\", then continues masturbating.\n\nWilda considers the fact that Crystal does not want to provide anymore assistance, and responds \"Oh... Okay\". Wilda then looks at the tentacle monster again.\n\n");
            if (iRet != 0) return iRet;

            // wrap back around to the combat setup, but with a subscene id of 1, so that the "Ask Crystal what to do" option is no longer there.
            iRet = gamelogic04_scene1060 (1, cSubFlag + 1);
            return iRet;
        }
    }

    switch (iCount)
    {
    case 1:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"I am not exactly sure what I should be doing here... I mean\"...\n\n");
        if (iRet != 0) return iRet;
        break;

    case 2:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"Sorry to ask for your help, but I feel I should be doing something... differently\".\n\n");
        if (iRet != 0) return iRet;
        break;

    case 3:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"How should I handle this one?\"\n\n");
        if (iRet != 0) return iRet;
        break;

    case 4:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"Anymore ideas would be appreciated\".\n\n");
        if (iRet != 0) return iRet;
        break;

    case 5:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"Teacher, could you graciously provide this student with more of your knowledge\".\n\n");
        if (iRet != 0) return iRet;
        break;

    case 6:
        iRet = mutils_addToDialogBuffer ("Wilda looks at Crystal \"Do you have anymore\"...\n\nCrystal quietly interjects, while not looking at Wilda \"There is one more thing I can tell you\", then continues masturbating by herself for about half a minute.\n\nThat pause felt like an eternity to Wilda.\n\nEventually, ");
        if (iRet != 0) return iRet;
        break;
    }

    switch (iOffset)
    {
    case 1: // massage breasts
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Play your cow udders\", then makes quickly demonstrates massaging her own breasts with her hands..\n\nWilda looks back at the tentacle monster \"Okay... Sure\"...\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[1] = 1;
        break;

    case 2: // blow a kiss
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Tease with your mouth\".\n\nWilda asks \"Tease?\"\n\nCrystal puckers up, and blows a kiss.\n\nWilda looks back at the tentacle monster, as she was expecting Crystal to do something like suck on her finger, but a kiss she can do.\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[2] = 1;
        break;

    case 3: // pinch clitoris
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Play with your girl cock\".\n\nWilda responds with a dumbfounded \"Eh?\"\n\nCrystal sighs and tells Wilda \"Look at what I am about to do with my girl cock\". Wilda looks down at Crystal\'s pussy, and Crystal switches from fingering her clitoris, to pinching it. Crystal continues \"Like that\".\n\nWilda looks back at the tentacle monster, and smiles \"I should be able to manage that\".\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[3] = 1;
        break;

    case 4: // wiggle butt
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Shake your booty\".\n\nWilda asks \"Booty?\"\n\nCrystal then gyrates her hips, and responds \"Like this\".\n\nWilda looks back at the tentacle monster, and says \"Shake my booty, sure... I could do that\".\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[4] = 1;
        break;

    case 5: // finger pussy
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Ready your lower orifice\".\n\nWilda looks at Crystal, and tries to make sense of what she means.\n\nCrystal adds \"Observe... my cunny\". Wilda looks down and watches as Crystal switches from fingering her clitoris to sliding her fingers in and out of her pussy.\n\nWilda responds \"Oh... Like that\", looks back at the tentacle monster, and continues \"That I can do\".\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[5] = 1;
        break;

    default: // 6, kneel down
        iRet = mutils_addToDialogBuffer ("Crystal looks at Wilda and says \"Prostrate yourself before your Master\".\n\nWilda asks \"Prostrate?\"\n\nCrystal continues \"On your knees\".\n\nWilda looks back at the tentacle monster, and considers that she should be kneeling before it.\n\n");
        if (iRet != 0) return iRet;

        gstructActStateGlobal.caAct3UnlockArray[6] = 1;
        break;
    }

    // wrap back around to the combat setup, but with a subscene id of 1, so that the "Ask Crystal what to do" option is no longer there.
    iRet = gamelogic04_scene1060 (1, cSubFlag + 1);
    return iRet;
}

//
// Setup/Continue the Act 4 combat moves.
//
int gamelogic04_scene1070 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Play with nipples, then do nothing", 1071, 1);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.sAct4Monsters < 6) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Play with nipples, then blow kiss", 1071, 2);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Play with nipples, then pinch them", 1071, 3);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Play with nipples, then pinch clitoris", 1071, 4);
    if (iRet != 0) return iRet;
    if (gstructActStateGlobal.sAct4Monsters >= 2)
    {
        iRet = mutils_addToCommandList ("Play with nipples, then wiggle butt", 1071, 5);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Spread legs, then do nothing", 1071, 6);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.sAct4Monsters < 6) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Spread legs, then blow kiss", 1071, 7);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Spread legs, then pinch nipples", 1071, 8);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Spread legs, then pinch clitoris", 1071, 9);
    if (iRet != 0) return iRet;
    if (gstructActStateGlobal.sAct4Monsters >= 2)
    {
        iRet = mutils_addToCommandList ("Spread legs, then wiggle butt", 1071, 10);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Spank own butt, then do nothing", 1071, 11);
        if (iRet != 0) return iRet;
    }
    if (((gstructActStateGlobal.sAct4Monsters >= 2) && (gstructActStateGlobal.sAct4Monsters < 6)) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Spank own butt, then blow kiss", 1071, 12);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 2)
    {
        iRet = mutils_addToCommandList ("Spank own butt, then pinch nipples", 1071, 13);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Spank own butt, then pinch clitoris", 1071, 14);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Spank own butt, then wiggle it", 1071, 15);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Finger pussy and anus, then do nothing", 1071, 16);
        if (iRet != 0) return iRet;
    }
    if (((gstructActStateGlobal.sAct4Monsters >= 4) && (gstructActStateGlobal.sAct4Monsters < 6)) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Finger pussy and anus, then blow kiss", 1071, 17);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 4)
    {
        iRet = mutils_addToCommandList ("Finger pussy and anus, then pinch nipples", 1071, 18);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Finger pussy and anus, then pinch clitoris", 1071, 19);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Finger pussy and anus, then wiggle butt", 1071, 20);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Stroke clitoris, then do nothing", 1071, 21);
        if (iRet != 0) return iRet;
    }
    if (((gstructActStateGlobal.sAct4Monsters >= 3) && (gstructActStateGlobal.sAct4Monsters < 6)) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Stroke clitoris, then blow kiss", 1071, 22);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 3)
    {
        iRet = mutils_addToCommandList ("Stroke clitoris, then pinch nipples", 1071, 23);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Stroke clitoris, then pinch it", 1071, 24);
        if (iRet != 0) return iRet;
        iRet = mutils_addToCommandList ("Stroke clitoris, then wiggle butt", 1071, 25);
        if (iRet != 0) return iRet;
    }
    if (gstructActStateGlobal.sAct4Monsters >= 6)
    {
        iRet = mutils_addToCommandList ("Lick lips, then do nothing", 1071, 26);
        if (iRet != 0) return iRet;
    }
    if ((gstructActStateGlobal.sAct4Monsters < 6) || (gstructActStateGlobal.sAct4Monsters > 25))
    {
        iRet = mutils_addToCommandList ("Lick lips, then blow kiss", 1071, 27);
        if (iRet != 0) return iRet;
    }
    iRet = mutils_addToCommandList ("Lick lips, then pinch nipples", 1071, 28);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Lick lips, then pinch clitoris", 1071, 29);
    if (iRet != 0) return iRet;
    if (gstructActStateGlobal.sAct4Monsters >= 2)
    {
        iRet = mutils_addToCommandList ("Lick lips, then wiggle butt", 1071, 30);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// Execution of the Act 4 combat moves.
//
int gamelogic04_scene1071 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iRndNum;
    int iMonsterAction;
    float fStaDec;
    char cAction1;
    char cAction2;
    char cDesc = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Play with nipples, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // Play with nipples
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.1, (float)0.04, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2, (float)1.5, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 1, 0, 0);

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Play with nipples, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // Play with nipples
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.12, (float)0.07, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.5, (float)1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 2, 0, 0);

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Play with nipples, then pinch them\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda starts by teasing the tips of her own nipples, moving to lightly massaging her breasts, then switching back to tweaking her nipples.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda starts with rubbing both of her nipples up and down, raising her arousal, then lets out a light moan as she lightly pinches both of her nipples.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("While looking at the tentacle monster, Wilda starts with lightly tweaking and rubbing her nipples, then switches to tweaking and pinching them.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have already set a description here..
        cAction1 = 1; // Play with nipples
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.15, (float)0.1, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.75, (float)1.25, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 2, 0, 0);

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Play with nipples, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // Play with nipples
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.16, (float)0.11, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.85, (float)1.35, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 0);

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Play with nipples, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 1; // Play with nipples
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.18, (float)0.13, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.6, (float)1.1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 0, 1);

        break;

    case 6:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spread legs, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // Spread legs
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.12, (float)0.07, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.1, (float)1.6, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 0, 1, 1);

        break;

    case 7:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spread legs, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // Spread legs
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.14, (float)0.09, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.6, (float)1.1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 1);

        break;

    case 8:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spread legs, then pinch nipples\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // Spread legs
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.17, (float)0.12, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.85, (float)1.35, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 1);

        break;

    case 9:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spread legs, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda steps out with her right leg, and starts rubbing and pinching her clitoris while lightly rocking her butt back and forth.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda steps out with her left leg, and starts tweaking and playing her clitoris as she lightly moans.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda looks at the tentacle monster, as she half steps out with her left foot, then half steps out with her right foot, squats a little bit, then starts lightly toying with her own clitoris.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have already set a description here..
        cAction1 = 2; // Spread legs
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.18, (float)0.13, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.95, (float)1.45, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 2, 1);

        break;

    case 10:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spread legs, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 2; // Spread legs
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.2, (float)0.15, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.2, (float)1.7, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 1, 2);

        break;

    case 11:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spank own butt, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // Spank own butt
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.22, (float)0.17, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.5, (float)1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 0, 0, 1);

        break;

    case 12:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spank own butt, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // Spank own butt
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.24, (float)0.19, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1, (float)0.5, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 0, 1);

        break;

    case 13:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spank own butt, then pinch nipples\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // Spank own butt
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.25, (float)0.2, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.25, (float)0.75, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 0, 1);

        break;

    case 14:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spank own butt, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 3; // Spank own butt
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.21, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.35, (float)0.85, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 1, 1);

        break;

    case 15:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Spank own butt, then wiggle it\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda spins around, showing her anus to the tentacle monster, bends over, spanks her ass, then starts shaking her butt.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda turns to the side, bends over, starts groping and lightly spanking her own butt, then gyrates her hips.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda alternates between spanking her butt and shaking it up and down.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have already set a description here..
        cAction1 = 3; // Spank own butt
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.28, (float)0.23, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.1, (float)0.6, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 0, 2);

        break;

    case 16:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy and anus, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // Finger pussy and anus
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.3, (float)0.25, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.5, (float)2, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.21, (float)0.13, 200), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, actionstate_randomFloatValue ((float)0.21, (float)0.13, 200), 6000);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 0, 1, 1);

        break;

    case 17:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy and anus, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // Finger pussy and anus
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.32, (float)0.27, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2, (float)1.5, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 1);

        break;

    case 18:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy and anus, then pinch nipples\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // Finger pussy and anus
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.35, (float)0.3, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.25, (float)1.75, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 1);

        break;

    case 19:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy and anus, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // Finger pussy and anus
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.36, (float)0.31, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.35, (float)1.85, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, actionstate_randomFloatValue ((float)0.12, (float)0.06, 200), 6000);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 2, 1);

        break;

    case 20:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Finger pussy and anus, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 4; // Finger pussy and anus
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.38, (float)0.33, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2.1, (float)1.6, 400), gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharWilda.structV, actionstate_randomFloatValue ((float)0.18, (float)0.1, 200), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, actionstate_randomFloatValue ((float)0.18, (float)0.1, 200), 6000);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 1, 2);

        break;

    case 21:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stroke clitoris, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 5; // Stroke clitoris
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.2, (float)0.15, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)2, (float)1.5, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 0, 1, 0);

        break;

    case 22:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stroke clitoris, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 5; // Stroke clitoris
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.22, (float)0.17, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.5, (float)1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 0);

        break;

    case 23:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stroke clitoris, then pinch nipples\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 5; // Stroke clitoris
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.25, (float)0.2, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.75, (float)1.25, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 0);

        break;

    case 24:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stroke clitoris, then pinch it\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("Wilda starts by lightly parting her legs, stroking her clitoris, then lightly pinching it.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("While looking at the tentacle monster, Wilda increases the her petting of her own clitoris, to the point that she is erratically rubbing it, then lightly pinches it. Light moans escape Wilda\'s mouth.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda alternates between rubbing, tweaking, and lightly pinching her clitoris.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have already set a description here..
        cAction1 = 5; // Stroke clitoris
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.26, (float)0.21, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.85, (float)1.35, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 2, 0);

        break;

    case 25:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Stroke clitoris, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 5; // Stroke clitoris
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.28, (float)0.23, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.6, (float)1.1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 0, 1, 1);

        break;

    case 26:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Lick lips, then do nothing\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 6; // Lick lips
        cAction2 = 0; // then do nothing

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.08, (float)0.03, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.5, (float)1, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (1, 1, 0, 0);

        break;

    case 27:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Lick lips, then blow kiss\n\n");
            if (iRet != 0) return iRet;
        }

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 2)
            iRet = mutils_addToDialogBuffer ("While looking directly at the tentacle monster, starts to lick her lips, then starts erotically sucking on her index finger, then switches to blowing a kiss.\n\n");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda puckers up her lips, starts licking them, pretends that she is sucking a tentacle with her lips and tongue, then finishes up by blowing a kiss.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda bites her lower lip then starts licking along her top lip, then blows a sloppy kiss in the direction of the tentacle monster.\n\n");
        if (iRet != 0) return iRet;

        cDesc = 1; // we have already set a description here..
        cAction1 = 6; // Lick lips
        cAction2 = 1; // then blow kiss

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.1, (float)0.05, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1, (float)0.5, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 2, 0, 0);

        break;

    case 28:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Lick lips, then pinch nipples\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 6; // Lick lips
        cAction2 = 2; // then pinch nipples

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.13, (float)0.08, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.25, (float)0.75, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 2, 0, 0);

        break;

    case 29:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Lick lips, then pinch clitoris\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 6; // Lick lips
        cAction2 = 3; // then pinch clitoris

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.14, (float)0.09, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.35, (float)0.85, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 1, 0);

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Lick lips, then wiggle butt\n\n");
            if (iRet != 0) return iRet;
        }

        cAction1 = 6; // Lick lips
        cAction2 = 4; // then wiggle butt

        actionstate_statSubtraction (&gstructActStateCharWilda.structS, actionstate_randomFloatValue ((float)0.16, (float)0.11, 200), 0);
        actionstate_statAddition (&gstructActStateCharWilda.structL, actionstate_randomFloatValue ((float)1.1, (float)0.6, 400), gstructActStateCharWilda.structF.iNum);

        iMonsterAction = actionstate_accessAct4MonsterAction (0, 1, 0, 1);

        break;
    }

    //
    // Description logic goes here.
    //
    if (cDesc == 0)
    {
        // Note: I decided to do the random evaluation inside each case evaluation, in case I decide to expand the number
        //  of RNG possibilities for the dialog.

        iRet = mutils_addToDialogBuffer ("Wilda starts with ");
        if (iRet != 0) return iRet;

        switch (cAction1)
        {
        case 1: // action 1 = 1 (Play with nipples)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("stroking the tips of her nipples");
            else
                iRet = mutils_addToDialogBuffer ("playing with her nipples");

            break;

        case 2: // action 1 = 2 (Spread legs)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("spreading her legs");
            else
                iRet = mutils_addToDialogBuffer ("sliding her legs apart");

            break;

        case 3: // action 1 = 3 (Spank own butt)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("massaging and spanking her own ass");
            else
                iRet = mutils_addToDialogBuffer ("lightly spanking her own butt");

            break;

        case 4: // action 1 = 4 (Finger pussy and anus)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("lightly fingering her pussy with her left hand, while reaching around to her anus with her right hand");
            else
                iRet = mutils_addToDialogBuffer ("fingering her pussy with her left hand, while fingering her anus with her right hand at the same time");

            break;

        case 5: // action 1 = 5 (Stroke clitoris)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("lightly stroking her erect clitoris");
            else
                iRet = mutils_addToDialogBuffer ("playing with her erect clitoris");

            break;

        default: // case 6: // action 1 = 6 (Lick lips)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("seductively licking her lips with her tongue");
            else
                iRet = mutils_addToDialogBuffer ("pursing her lips and licking her lips");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer (", then ");
        if (iRet != 0) return iRet;

        switch (cAction2)
        {
        case 0: // action 2 = 0 (do nothing)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("does nothing else, to tease the tentacle monster");
            else
                iRet = mutils_addToDialogBuffer ("pauses, to further excite the tentacle monster");

            break;

        case 1: // action 2 = 1 (then blow kiss)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("puckering her lips and blowing a kiss at the tentacle monster");
            else
                iRet = mutils_addToDialogBuffer ("blowing a kiss towards the tentacle monster");

            break;

        case 2: // action 2 = 2 (then pinch nipples)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("lightly pinching both of her nipples");
            else
                iRet = mutils_addToDialogBuffer ("circling and pinching her nipples with her fingers");

            break;

        case 3: // action 2 = 3 (then pinch clitoris)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("lightly pinching her clitoris");
            else
                iRet = mutils_addToDialogBuffer ("rubbing her clitoris, and then pinching it");

            break;

        case 4: // action 2 = 4 (then wiggle butt)
            iRndNum = (int)(rand() % 2);

            if (iRndNum != 0)
                iRet = mutils_addToDialogBuffer ("she faces her butt at the tentacle monster and starts gyrating her hips");
            else
                iRet = mutils_addToDialogBuffer ("she starts shaking her butt up and down, then around");

            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer (".\n\n");
        if (iRet != 0) return iRet;
    }

    iRet = mutils_addToDialogBuffer ("\n");
    if (iRet != 0) return iRet;

    switch (iMonsterAction)
    {
    case 0: // Quick violation of pussy

        fStaDec = actionstate_randomFloatValue ((float)1.35, (float)1, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fStaDec / 3), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 10), 1);

        if (fStaDec > (float)1.18)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster finally pulls its tentacle out of Wilda\'s pussy, leaving rivers of goop dribbling down between her thighs.");
        else
            iRet = mutils_addToDialogBuffer ("Wilda has been enjoying the attention her pussy alone has had from the tentacle monster for a while now. She is rather unhappy when the tentacle monster finally pulls its tentacle out of her.");
        if (iRet != 0) return iRet;

        break;

    case 1: // Quick violation of mouth

        fStaDec = actionstate_randomFloatValue ((float)1.4, (float)1.05, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fStaDec / 3), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 10), 1);

        if (fStaDec > (float)1.2)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("The tentacle monster, satisfied with Wilda\'s oral skills, pulls its tentacle out of her mouth.");
        else
            iRet = mutils_addToDialogBuffer ("Wilda has been throughly sucking on the tentacle that the tentacle monster thrusting in and out of Wilda\'s mouth. Suddenly the tentacle decides that it has had enough so it pulls its tentacle out of Wilda.");
        if (iRet != 0) return iRet;

        break;

    case 2: // Quick violation of ass

        fStaDec = actionstate_randomFloatValue ((float)1.45, (float)1.1, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, (float)(fStaDec / 3), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 10), 1);

        if (fStaDec > (float)1.25)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("After Wilda\'s anus had been throughly explored by a tentacle from the tentacle monster, the tentacle pulls out of her, much to Wilda\'s disapproval.");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster has been concentrating on fucking only Wilda\'s butt for a while. Finally, the tentacle monster pulls its tentacle out of Wilda.");
        if (iRet != 0) return iRet;

        break;

    case 3: // Quick violation of pussy and mouth

        fStaDec = actionstate_randomFloatValue ((float)1.65, (float)1.3, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4.2), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5.2), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 10.5), 1);

        if (fStaDec > (float)1.37)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("After accommodating tentacles in her pussy and mouth for a little while now, Wilda finds that the tentacle monster removes both of those tentacles from her.");
        else
            iRet = mutils_addToDialogBuffer ("Wilda has been spending some time sucking on a tentacle that is thrusting in and out of her mouth, while another has been pistoning in and out of her pussy. The tentacles shake a little bit, then finally retract from her.");
        if (iRet != 0) return iRet;

        break;

    case 4: // Quick violation of pussy and ass

        fStaDec = actionstate_randomFloatValue ((float)1.7, (float)1.35, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4.2), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, (float)(fStaDec / 3.5), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5.5), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 11), 1);

        if (fStaDec > (float)1.42)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda has has had her pussy, and her anus, penetrated by two separate tentacles, at the same time. The tentacle monster has been alternate thrusting in and out of Wilda\'s pussy and anus. Finally, the tentacle monster pulls out both of its tentacles.");
        else
            iRet = mutils_addToDialogBuffer ("Both of Wilda\'s lower orifices have been accommodating some rather lively tentacles from the tentacle monster. The tentacle suddenly stops humping Wilda\'s pussy and butt, and pulls its tentacles out of her.");
        if (iRet != 0) return iRet;

        break;

    case 5: // Quick violation of mouth and ass

        fStaDec = actionstate_randomFloatValue ((float)1.75, (float)1.4, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4.2), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, (float)(fStaDec / 3.5), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 5.5), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 11), 1);

        if (fStaDec > (float)1.57)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 2);

        if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda has been skewered by the tentacles fucking both her mouth, and her anus, at the same time. Finally, the tentacle monster helps Wilda back onto her feet, and pulls its tentacles out of her.");
        else
            iRet = mutils_addToDialogBuffer ("For a little while now, Wilda has been sucking on a tentacle in her mouth, while another has been exploring her rectum. The tentacle monster stops fucking Wilda\'s mouth and anus, and pulls its tentacles out of her.");
        if (iRet != 0) return iRet;

        break;

    case 6: // Quick violation of pussy, ass and mouth

        fStaDec = actionstate_randomFloatValue ((float)2.1, (float)1.75, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 2.5), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 4.5), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fStaDec / 4), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, (float)(fStaDec / 3.5), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 3), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 6), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 12), 1);

        if (fStaDec > (float)1.87)
            iRet = mutils_addToDialogBuffer ("[4 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[3 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 1)
            iRet = mutils_addToDialogBuffer ("The tentacle monster has been busy for a little while, fucking Wilda\'s mouth, pussy and anus. The tentacle monster holds Wilda up, as it pulls its three tentacles out of her.");
        else if (iRndNum != 0)
            iRet = mutils_addToDialogBuffer ("Wilda\'s pussy, butt and mouth have all been getting some recent attention from the tentacle monster. Suddenly, the tentacle monster pulls its tentacles out of Wilda at the same time.");
        else
            iRet = mutils_addToDialogBuffer ("After having her pussy and ass fucked, while also sucking a third tentacle for a while, Wilda finds that the tentacle monster starts pulling its tentacles out of her.");
        if (iRet != 0) return iRet;

        break;

    default: // case 7: long violation of the pussy, ass and mouth.

        fStaDec = actionstate_randomFloatValue ((float)16, (float)14, 400);

        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)(fStaDec / 7), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, 0);
        actionstate_statAddition (&gstructActStateCharWilda.structM, (float)(fStaDec / 16), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structO, (float)(fStaDec / 10), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)(fStaDec / 10), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structA, (float)(fStaDec / 8), 6000);
        actionstate_statAddition (&gstructActStateCharWilda.structK, (float)(fStaDec / 10), 6000);
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)(fStaDec / 20), 24);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, (float)(fStaDec / 40), 1);

        if (fStaDec > (float)15)
            iRet = mutils_addToDialogBuffer ("[11 minutes later...]\n\n");
        else
            iRet = mutils_addToDialogBuffer ("[10 minutes later...]\n\n");
        if (iRet != 0) return iRet;

        iRndNum = (int)(rand() % 3);

        if (iRndNum == 1)
            iRet = mutils_addToDialogBuffer ("After throughly fucking Wilda\'s mouth, pussy and anus, the tentacle monster sets Wilda down, and pulls its tentacles out of her.");
        else if (iRndNum == 0)
            iRet = mutils_addToDialogBuffer ("After a enduring an extended violation of her 3 primary orifices, Wilda finds that her mouth, pussy and anus are now vacant, and has been set down by her tentacled lover.");
        else
            iRet = mutils_addToDialogBuffer ("The tentacle monster finishes up giving Wilda\'s anus, pussy and mouth some rather through attention, and retracts its tentacles from her.");
        if (iRet != 0) return iRet;

        break;
    }

    iRndNum = (int)(rand() % 3);

    if (iRndNum == 1)
        iRet = mutils_addToDialogBuffer (" The tentacle monster then leaves Wilda, and starts scampering off down a passageway.");
    else if (iRndNum == 0)
        iRet = mutils_addToDialogBuffer (" The tentacle monster departs, and leaves Wilda to recover by herself.");
    else
        iRet = mutils_addToDialogBuffer (" The tentacle monster splashes some liquid, as it rushes away from Wilda.");
    if (iRet != 0) return iRet;

    if (iMonsterAction == 7)
        iRet = mutils_addToDialogBuffer ("\n\n\n[2 minutes later...]\n\n");
    else
        iRet = mutils_addToDialogBuffer ("\n\n\n[1 minute later...]\n\n");
    if (iRet != 0) return iRet;

    iRndNum = (int)(rand() % 3);

    if (iRndNum == 1)
        iRet = mutils_addToDialogBuffer ("Wilda talks to herself \"I guess it is about time I got going\".\n\n");
    else if (iRndNum == 0)
        iRet = mutils_addToDialogBuffer ("Wilda decides that she has had enough rest and it is time to start moving again.\n\n");
    else
        iRet = mutils_addToDialogBuffer ("After waiting for a while, and finding that the tentacle monster didn\'t return, Wilda decides that it is about time to keep going. Wilda still has her quest to complete.\n\n");
    if (iRet != 0) return iRet;

    // increment the counter
    if (gstructActStateGlobal.sAct4Monsters < 60)
        gstructActStateGlobal.sAct4Monsters++;

    // set the monster to being no longer active.
    gstructActStateOpponent.cActive = 0;

    // set the array to say that we had an encounter.
    gstructActStateGlobal.caEncounterArray[0] = 1;

    // return back to navigation.
    iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    return iRet;
}

