//
// gamelogic02.c
//
// This is group 2 of scene ids.
//
// Essentially, this is the all of the navigation actions of the game.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"
#include "mapdata.h"

// external linkage to the game variables.
extern  char    gcDebugFlag;

// linkage to the actionstate data.
extern  struct  actionstate_charstats gstructActStateCharWilda;
extern  struct  actionstate_charstats gstructActStateCharCrystal;
extern  struct  actionstate_opponentstats gstructActStateOpponent;
extern  struct  actionstate_globalvars gstructActStateGlobal;

// linkage to the mapdata.
extern  char    gszMapName[];
extern  struct  mapdata_posdatastatic *gpstructMapPosStaticCurrent;
extern  struct  mapdata_posdatadynamic *gpstructMapPosDynamicCurrent;
extern  struct  mapdata_linkdatadynamic *gpstructMapLinkDynamicCurrent;

// this is the array table for the special scenes..
struct  gamelogic02_eventscenes gstructEventSceneList[] =
{
    {    1, gamelogic01_event_scene001 },
    {    2, gamelogic01_event_scene002 },
    {    3, gamelogic01_event_scene003 },
    {    4, gamelogic01_event_scene004 },
    {    5, gamelogic01_event_scene005 },
    {    6, gamelogic01_event_scene006 },
    {    7, gamelogic01_event_scene007 },
    {    8, gamelogic01_event_scene008 },
    {    9, gamelogic01_event_scene009 },
    {   10, gamelogic01_event_scene010 },
    {   11, gamelogic01_event_scene011 },
    {   12, gamelogic01_event_scene012 },
    {   13, gamelogic01_event_scene013 },
    {   14, gamelogic01_event_scene014 },
    {   15, gamelogic01_event_scene015 },
    {   16, gamelogic01_event_scene016 },
    {   17, gamelogic01_event_scene017 },
    {   18, gamelogic01_event_scene018 },
    {   19, gamelogic01_event_scene019 },
    {   20, gamelogic01_event_scene020 },
    {   21, gamelogic01_event_scene021 },
    {   22, gamelogic01_event_scene022 },
    {   23, gamelogic01_event_scene023 },
    {   24, gamelogic01_event_scene024 },
    {   25, gamelogic01_event_scene025 },
    {   26, gamelogic01_event_scene026 },
    {   27, gamelogic01_event_scene027 },
    {   28, gamelogic01_event_scene028 },
    {   29, gamelogic01_event_scene029 },
    {   30, gamelogic01_event_scene030 },
    {   31, gamelogic01_event_scene031 },
    {   50, gamelogic01_event_scene050 },
    {   51, gamelogic01_event_scene051 },
    {   52, gamelogic01_event_scene052 },
    {   53, gamelogic01_event_scene053 },
    {   54, gamelogic01_event_scene054 },
    {   55, gamelogic01_event_scene055 },
    {   56, gamelogic01_event_scene056 },
    {   61, gamelogic01_event_scene061 },
    {   62, gamelogic01_event_scene062 },
    {   63, gamelogic01_event_scene063 },
    {   64, gamelogic01_event_scene064 },
    {   65, gamelogic01_event_scene065 },
    {   66, gamelogic01_event_scene066 },
    {   67, gamelogic01_event_scene067 },
    {   68, gamelogic01_event_scene068 },
    {   69, gamelogic01_event_scene069 },
    {   71, gamelogic01_event_scene071 },
    {   72, gamelogic01_event_scene072 },
    {   73, gamelogic01_event_scene073 },
    {   74, gamelogic01_event_scene074 },
    {   75, gamelogic01_event_scene075 },
    {   -1, NULL                       }
};
//
// this array is here, because it is only used by gamelogic02_scene1021() below.
//
// All of the functions it is referring to is over in gamelogic01.c.
//
// I called them event scenes, but they are extensions of the navigation to
// trigger things, as well as drop out of navigation if we have come to the
// end of the map.
//

//
// Setup/Continue the navigation.
//
int gamelogic02_scene1020 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    int iRoomType;
    struct mapdata_posmovevalues structMapDataMove;
    char cMasturbateAvail = 0;
    char cFeelingTired = 0;
    int iCount = 0;
    short sVisitVal;
    char cVal1;
    char cVal2;
    char cSep1 = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gcDebugFlag != 0)
    {
        char szWorking[80];

        sprintf (szWorking, "debug: %s PosId %d\n\n", gszMapName, gstructActStateGlobal.sPosId);

        iRet = mutils_addToDialogBuffer (szWorking);
        if (iRet != 0) return iRet;
    }

    // if Wilda's stamina has red-lined.. that is it, game over..
    if (gstructActStateCharWilda.structS.iNum <= 0)
    {
        switch (gstructActStateGlobal.sActId)
        {
        case 1:
            iRet = mutils_addToDialogBuffer ("Wilda collapses in the hallway, due to exhaustion. As she struggles to keep her eyes open, Wilda curses herself for coming ill-equipped AND accepting such a difficult job.\n\n\n[15 minutes later...]\n\nWilda is briefly woken up both something smothering her, then she passes out.\n\n");
            if (iRet != 0) return iRet;
            break;

        case 2:
            iRet = mutils_addToDialogBuffer ("Wilda collapses in the hallway, due to exhaustion. As she struggles to keep her eyes open, Wilda curses herself for losing her backpack and sword back in the liquid pool. She would have made it further if she had her equipment. Wilda starts to doze off.\n\n\n[5 minutes later...]\n\nWilda thinks that she can see a tentacle monster, but for some reason it backs away.\n\n\n[5 minutes later...]\n\nNot one, but 3 tentacle monsters returned. Wilda starts to panic, but the tentacle monsters jump on her, pinning her down. After a brief struggle, Wilda blacks out.\n\n");
            if (iRet != 0) return iRet;
            break;

        case 3:
            iRet = mutils_addToDialogBuffer ("Wilda collapses in the hallway, due to exhaustion \"I am just... too tired\"...\n\nCrystal stands over Wilda \"Do you want to get some rest for a while?\"\n\nWilda groggily responds \"Yes, thank you\".\n\nCrystal replies \"Rest... And I will watch over you\".\n\nWilda closes her eyes.\n\nCrystal continues \"Yes... Rest... For in the realm of our lord and master... Cock... even failure is rewarded\"...\n\n");
            if (iRet != 0) return iRet;
            break;

        default: // case 4:
            iRet = mutils_addToDialogBuffer ("Exhausted, Wilda collapses in the hallway \"just... having a quick nap\"...\n\nAs Wilda drifts off to sleep, she shows no concern as she isn\'t alone. The baby in her belly will keep her company.\n\n");
            if (iRet != 0) return iRet;
            break;
        }

        iRet = gamelogic01_scene1011 (0, cSubFlag + 1);
        return iRet;
    }

    iRoomType = mapdata_workoutPosIdNavigation (gstructActStateGlobal.sPosId, &structMapDataMove);
    if (iRoomType == 10) return iRoomType;

    if (gstructActStateCharWilda.structS.iNum < 30)
    {
        cFeelingTired = 1;
    }

    // for acts 1 and 2, consider the masturbate flag
    if ((gstructActStateGlobal.sActId < 3) && (iSubSceneId != 1))
    {
        int iCompare;

        // increase Lust
        actionstate_statAddition (&gstructActStateCharWilda.structL, (float)0.081, (int)6000);

        if (gstructActStateCharWilda.structL.iNum >= gstructActStateCharWilda.structF.iNum)
        {
            // pass control over to the masturbation function.
            iRet = gamelogic02_scene1022 (1, cSubFlag + 1);
            return iRet;
        }

        iCompare = (int)(gstructActStateCharWilda.structF.iNum / 3);

        if (gstructActStateCharWilda.structL.iNum >= iCompare)
        {
            if (cFeelingTired != 0)
                iRet = mutils_addToDialogBuffer ("Wilda is feeling both horny AND tired.\n\n");
            else
            {
                if (((gstructActStateCharWilda.structL.iNum * 3) / 2) > gstructActStateCharWilda.structF.iNum)
                    iRet = mutils_addToDialogBuffer ("Wilda is feeling rather horny.\n\n");
                else
                    iRet = mutils_addToDialogBuffer ("Wilda is starting to feel horny.\n\n");
            }

            if (iRet != 0) return iRet;

            cMasturbateAvail = 1;
            cFeelingTired = 0;
        }
    }
    // for acts 3 & 4, Wilda is walking around while masturbating, so her rising lust will be
    //  (sort of) kept in check.

    if (cFeelingTired != 0)
    {
        if (gstructActStateCharWilda.structS.iNum < 15)
            iRet = mutils_addToDialogBuffer ("Wilda is feeling VERY tired.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda is starting to feel tired.\n\n");
        if (iRet != 0) return iRet;
    }

    if ((iSubSceneId == 2) && (gstructActStateGlobal.cDirect != 0))
    {
        if (gstructActStateGlobal.sActId != 3)
        {
            switch (gstructActStateGlobal.cDirect)
            {
            case 1: // came from the south, facing north
                iRet = mutils_addToDialogBuffer ("Wilda came from the south, and is facing north. ");
                break;

            case 2: // came from the west, facing east
                iRet = mutils_addToDialogBuffer ("Wilda came from the west, and is facing east. ");
                break;

            case 3: // came from the north, facing south
                iRet = mutils_addToDialogBuffer ("Wilda came from the north, and is facing south. ");
                break;

            case 4: // came from the east, facing west
                iRet = mutils_addToDialogBuffer ("Wilda came from the east, and is facing west. ");
                break;
            }
        }
        else
        {
            switch (gstructActStateGlobal.cDirect)
            {
            case 1: // came from the south, facing north
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal came from the south, and are facing north. ");
                break;

            case 2: // came from the west, facing east
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal came from the west, and are facing east. ");
                break;

            case 3: // came from the north, facing south
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal came from the north, and are facing south. ");
                break;

            case 4: // came from the east, facing west
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal came from the east, and are facing west. ");
                break;
            }
        }
        if (iRet != 0) return iRet;
    }

    // catch code, to make sure that the Stair Direction and Up/down values are both populated.
    if (gstructActStateGlobal.cStairDirect == 0)
        gstructActStateGlobal.cStairUpDown = 0;
    else if (gstructActStateGlobal.cStairUpDown == 0)
        gstructActStateGlobal.cStairDirect = 0;

    iRet = mutils_addToDialogBuffer ("This is ");

    sVisitVal = gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount;
    cVal1 = gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].cRand1;
    cVal2 = gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].cRand2;

    switch (cVal1)
    {
    case 0:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("an unexciting and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and unexciting");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("an unexciting and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and unexciting");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("an unexciting and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and unexciting");
                break;
        }
        break;

    case 1:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a boring and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and boring");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a boring and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and boring");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a boring and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and boring");
                break;
        }
        break;

    case 2:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dismal and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and dismal");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dismal and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and dismal");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dismal and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and dismal");
                break;
        }
        break;

    case 3:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a gloomy and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and gloomy");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a gloomy and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and gloomy");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a gloomy and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and gloomy");
                break;
        }
        break;

    case 4:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dull and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and dull");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dull and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and dull");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a dull and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and dull");
                break;
        }
        break;

    case 5:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a mundane and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and mundane");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a mundane and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and mundane");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a mundane and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and mundane");
                break;
        }
        break;

    default:
        switch (sVisitVal)
        {
            case 0:
            case 1:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a drab and unfamiliar");
                else
                    iRet = mutils_addToDialogBuffer ("an unfamiliar and drab");
                break;

            case 2:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a drab and familiar");
                else
                    iRet = mutils_addToDialogBuffer ("a familiar and drab");
                break;

            default:
                if (cVal2 != 0)
                    iRet = mutils_addToDialogBuffer ("a drab and well-known");
                else
                    iRet = mutils_addToDialogBuffer ("a well-known and drab");
                break;
        }
        break;
    }
    if (iRet != 0) return iRet;

    // start populating the dialog for the room type.
    switch (iRoomType)
    {
    case 1: // dead-end
        iRet = mutils_addToDialogBuffer (" dead-end, with only ");
        iCount = 1;
        break;

    case 2: // elbow turn
        iRet = mutils_addToDialogBuffer (" turn");
        iCount = 2;
        break;

    case 3: // hallway
        iRet = mutils_addToDialogBuffer (" hallway");
        iCount = 2;
        break;

    case 4: // t-intersection
        iRet = mutils_addToDialogBuffer (" T-intersection");
        iCount = 3;
        break;

    default: // cross-intersection
        iRet = mutils_addToDialogBuffer (" cross-intersection");
        iCount = 4;
        break;
    }
    if (iRet != 0) return iRet;

    cSep1 = 0;

    if (iRoomType != 1)
    {
        iRet = mutils_addToDialogBuffer (", with ");
        if (iRet != 0) return iRet;

        // if there are stairs
        if (gstructActStateGlobal.cStairUpDown != 0)
        {
            short sVisit;
            char *pcDirect;

            cSep1 = 1;

            switch (gstructActStateGlobal.cStairDirect)
            {
            case 1: // north
                pcDirect = "north";
                sVisit = structMapDataMove.sVisitNorth;
                break;

            case 2: // east
                pcDirect = "east";
                sVisit = structMapDataMove.sVisitEast;
                break;

            case 3: // south
                pcDirect = "south";
                sVisit = structMapDataMove.sVisitSouth;
                break;

            default: // west
                pcDirect = "west";
                sVisit = structMapDataMove.sVisitWest;
                break;
            }
            if (iRet != 0) return iRet;

            iRet = mapdata_printLinkVisitValue (sVisit);
            if (iRet != 0) return iRet;

            // leading up
            if (gstructActStateGlobal.cStairUpDown == 1)
            {
                iRet = mutils_addToDialogBuffer ("stairway leading up to the ");
            }
            // leading down
            else
            {
                iRet = mutils_addToDialogBuffer ("stairway leading down to the ");
            }
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer (pcDirect);
            if (iRet != 0) return iRet;

            // decrement the counter by 1, so that the code below matches up.
            iCount--;
        }
        if (iRet != 0) return iRet;
    }

    if ((structMapDataMove.cAllowNorth == 0) || (structMapDataMove.cAllowNorth == 2))
    {
        if (gstructActStateGlobal.cStairDirect != 1)
        {
            iRet = mutils_addToCommandList ("North", 1021, 1);
            if (iRet != 0) return iRet;

            if (iRoomType != 1)
            {
                if (cSep1 != 0)
                {
                    iRet = mutils_addToDialogBuffer (", ");
                    if (iRet != 0) return iRet;
                }

                if (iCount == 1)
                {
                    iRet = mutils_addToDialogBuffer ("and ");
                    if (iRet != 0) return iRet;
                }

                cSep1 = 1;
            }

            iRet = mapdata_printLinkVisitValue (structMapDataMove.sVisitNorth);
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("path to the north");
            if (iRet != 0) return iRet;

            if (iCount)
            {
                iCount--;
            }
        }
        // stairs leading up
        else if (gstructActStateGlobal.cStairUpDown == 1)
        {
            iRet = mutils_addToCommandList ("North stairs up", 1021, 1);
            if (iRet != 0) return iRet;
        }
        // stairs leading down
        else
        {
            iRet = mutils_addToCommandList ("North stairs down", 1021, 1);
            if (iRet != 0) return iRet;
        }
    }
    if ((structMapDataMove.cAllowEast == 0) || (structMapDataMove.cAllowEast == 2))
    {
        if (gstructActStateGlobal.cStairDirect != 2)
        {
            iRet = mutils_addToCommandList ("East", 1021, 2);
            if (iRet != 0) return iRet;

            if (iRoomType != 1)
            {
                if (cSep1 != 0)
                {
                    iRet = mutils_addToDialogBuffer (", ");
                    if (iRet != 0) return iRet;
                }

                if (iCount == 1)
                {
                    iRet = mutils_addToDialogBuffer ("and ");
                    if (iRet != 0) return iRet;
                }

                cSep1 = 1;
            }

            iRet = mapdata_printLinkVisitValue (structMapDataMove.sVisitEast);
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("path to the east");
            if (iRet != 0) return iRet;

            if (iCount)
            {
                iCount--;
            }
        }
        // stairs leading up
        else if (gstructActStateGlobal.cStairUpDown == 1)
        {
            iRet = mutils_addToCommandList ("East stairs up", 1021, 2);
            if (iRet != 0) return iRet;
        }
        // stairs leading down
        else
        {
            iRet = mutils_addToCommandList ("East stairs down", 1021, 2);
            if (iRet != 0) return iRet;
        }
    }
    if ((structMapDataMove.cAllowSouth == 0) || (structMapDataMove.cAllowSouth == 2))
    {
        if (gstructActStateGlobal.cStairDirect != 3)
        {
            iRet = mutils_addToCommandList ("South", 1021, 3);
            if (iRet != 0) return iRet;

            if (iRoomType != 1)
            {
                if (cSep1 != 0)
                {
                    iRet = mutils_addToDialogBuffer (", ");
                    if (iRet != 0) return iRet;
                }

                if (iCount == 1)
                {
                    iRet = mutils_addToDialogBuffer ("and ");
                    if (iRet != 0) return iRet;
                }

                cSep1 = 1;
            }

            iRet = mapdata_printLinkVisitValue (structMapDataMove.sVisitSouth);
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("path to the south");
            if (iRet != 0) return iRet;

            if (iCount)
            {
                iCount--;
            }
        }
        // stairs leading up
        else if (gstructActStateGlobal.cStairUpDown == 1)
        {
            iRet = mutils_addToCommandList ("South stairs up", 1021, 3);
            if (iRet != 0) return iRet;
        }
        // stairs leading down
        else
        {
            iRet = mutils_addToCommandList ("South stairs down", 1021, 3);
            if (iRet != 0) return iRet;
        }
    }
    if ((structMapDataMove.cAllowWest == 0) || (structMapDataMove.cAllowWest == 2))
    {
        if (gstructActStateGlobal.cStairDirect != 4)
        {
            iRet = mutils_addToCommandList ("West", 1021, 4);
            if (iRet != 0) return iRet;

            if (iRoomType != 1)
            {
                if (cSep1 != 0)
                {
                    iRet = mutils_addToDialogBuffer (", ");
                    if (iRet != 0) return iRet;
                }

                if (iCount == 1)
                {
                    iRet = mutils_addToDialogBuffer ("and ");
                    if (iRet != 0) return iRet;
                }

                cSep1 = 1;
            }

            iRet = mapdata_printLinkVisitValue (structMapDataMove.sVisitWest);
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("path to the west");
            if (iRet != 0) return iRet;

            if (iCount)
            {
                iCount--;
            }
        }
        // stairs leading up
        else if (gstructActStateGlobal.cStairUpDown == 1)
        {
            iRet = mutils_addToCommandList ("West stairs up", 1021, 4);
            if (iRet != 0) return iRet;
        }
        // stairs leading down
        else
        {
            iRet = mutils_addToCommandList ("West stairs down", 1021, 4);
            if (iRet != 0) return iRet;
        }
    }

    iRet = mutils_addToDialogBuffer (".\n\n");
    if (iRet != 0) return iRet;

    if ((gstructActStateGlobal.sActId == 1) && (gstructActStateGlobal.sPosId == 3))
    {
        iRet = mutils_addToDialogBuffer ("Wilda knows that there is a passageway behind the northern wall, but cannot do anything about it right now.\n\n");
        if (iRet != 0) return iRet;
    }

    if ((gstructActStateGlobal.sActId == 2) && (gstructActStateGlobal.sPosId == 2))
    {
        iRet = mutils_addToDialogBuffer ("Wilda suspects that there is a passageway behind the eastern wall.\n\n");
        if (iRet != 0) return iRet;
    }

    if ((gstructActStateGlobal.sActId == 3) && (gstructActStateGlobal.sPosId == 2))
    {
        iRet = mutils_addToDialogBuffer ("There is also a familiar path to the south, but Crystal told Wilda not to go that way.\n\n");
        if (iRet != 0) return iRet;
    }

    // give the player a hand if this is map id 1.
    if (gstructActStateGlobal.sMapId == 1)
    {
        if (structMapDataMove.cAllowNorth == 1)
        {
            iRet = mutils_addToDialogBuffer ("There is something strange about the northern wall.\n\n");
            if (iRet != 0) return iRet;
        }

        if (structMapDataMove.cAllowEast == 1)
        {
            iRet = mutils_addToDialogBuffer ("There is something strange about the eastern wall.\n\n");
            if (iRet != 0) return iRet;
        }

        if (structMapDataMove.cAllowSouth == 1)
        {
            iRet = mutils_addToDialogBuffer ("There is something strange about the southern wall.\n\n");
            if (iRet != 0) return iRet;
        }

        if (structMapDataMove.cAllowWest == 1)
        {
            iRet = mutils_addToDialogBuffer ("There is something strange about the western wall.\n\n");
            if (iRet != 0) return iRet;
        }
    }

    if (cMasturbateAvail != 0)
    {
        iRet = mutils_addToCommandList ("Masturbate", 1022, 0);
        if (iRet != 0) return iRet;
    }

    iRet = mutils_addToCommandList ("Inventory and status", 1030, 0);
    if (iRet != 0) return iRet;

    return 0;
}

//
// basic movement navigation (N, E, S, W)
//
int gamelogic02_scene1021 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    short sRet;
    int iRndNum;
    short sLinkId;
    short sNewPosId;
    char cSpecialId;
    char cAllowMonsterTrigger = 1;
    float fStaDec;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1: // north
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">North");
            if (iRet != 0) return iRet;
        }
        gstructActStateGlobal.cDirect = 1;
        sLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sLinkIdNorth;
        sNewPosId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sPosIdNorth;
        break;

    case 2: // east
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">East");
            if (iRet != 0) return iRet;
        }
        gstructActStateGlobal.cDirect = 2;
        sLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sLinkIdEast;
        sNewPosId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sPosIdEast;
        break;

    case 3: // south
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">South");
            if (iRet != 0) return iRet;
        }
        gstructActStateGlobal.cDirect = 3;
        sLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sLinkIdSouth;
        sNewPosId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sPosIdSouth;
        break;

    default: // let's assume this is west
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">West");
            if (iRet != 0) return iRet;
        }
        gstructActStateGlobal.cDirect = 4;
        sLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sLinkIdWest;
        sNewPosId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sPosIdWest;
        break;
    }

    if ((gstructActStateGlobal.cStairUpDown != 0) && (gstructActStateGlobal.cStairDirect == gstructActStateGlobal.cDirect))
    {
        if (cSubFlag == 0)
        {
            // leading up
            if (gstructActStateGlobal.cStairUpDown == 1)
            {
                iRet = mutils_addToDialogBuffer (" stairs up\n\n");
            }
            // leading down
            else
            {
                iRet = mutils_addToDialogBuffer (" stairs down\n\n");
            }
            if (iRet != 0) return iRet;
        }

        if (gstructActStateGlobal.sActId == 3)
        {
            iRet = mutils_addToDialogBuffer ("Wilda and Crystal ");
            if (iRet != 0) return iRet;

            // leading up
            if (gstructActStateGlobal.cStairUpDown == 1)
                iRet = mutils_addToDialogBuffer ("ascend the ");
            else
                iRet = mutils_addToDialogBuffer ("descend the ");
            if (iRet != 0) return iRet;

        }
        else
        {
            iRet = mutils_addToDialogBuffer ("Wilda walks ");
            if (iRet != 0) return iRet;

            // leading up
            if (gstructActStateGlobal.cStairUpDown == 1)
                iRet = mutils_addToDialogBuffer ("up the ");
            else
                iRet = mutils_addToDialogBuffer ("down the ");
            if (iRet != 0) return iRet;
        }

        switch (iSubSceneId)
        {
        case 1: // north
            iRet = mutils_addToDialogBuffer ("northern");
            break;

        case 2: // east
            iRet = mutils_addToDialogBuffer ("eastern");
            break;

        case 3: // south
            iRet = mutils_addToDialogBuffer ("southern");
            break;

        default: // let's assume this is west
            iRet = mutils_addToDialogBuffer ("western");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer (" stairway.\n\n");
        if (iRet != 0) return iRet;
    }
    else
    {
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer ("\n\n");
            if (iRet != 0) return iRet;
        }

        if (gstructActStateGlobal.sActId == 3)
        {
            iRet = mutils_addToDialogBuffer ("Wilda and Crystal ");
            if (iRet != 0) return iRet;

            switch (gpstructMapLinkDynamicCurrent[sLinkId - 1].cRand2)
            {
            case 0:
                iRet = mutils_addToDialogBuffer ("trudge along");
                break;

            case 1:
                iRet = mutils_addToDialogBuffer ("wonder along");
                break;

            case 2:
                iRet = mutils_addToDialogBuffer ("traverse");
                break;

            case 3:
                iRet = mutils_addToDialogBuffer ("navigate");
                break;

            default:
                iRet = mutils_addToDialogBuffer ("pass through");
                break;
            }
            if (iRet != 0) return iRet;
        }
        else
        {
            iRet = mutils_addToDialogBuffer ("Wilda ");
            if (iRet != 0) return iRet;

            switch (gpstructMapLinkDynamicCurrent[sLinkId - 1].cRand2)
            {
            case 0:
                iRet = mutils_addToDialogBuffer ("trudges along");
                break;

            case 1:
                iRet = mutils_addToDialogBuffer ("wonders along");
                break;

            case 2:
                iRet = mutils_addToDialogBuffer ("traverses");
                break;

            case 3:
                iRet = mutils_addToDialogBuffer ("navigates");
                break;

            default:
                iRet = mutils_addToDialogBuffer ("passes through");
                break;
            }
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer (" the ");
        if (iRet != 0) return iRet;

        switch (iSubSceneId)
        {
        case 1: // north
            iRet = mutils_addToDialogBuffer ("northern");
            break;

        case 2: // east
            iRet = mutils_addToDialogBuffer ("eastern");
            break;

        case 3: // south
            iRet = mutils_addToDialogBuffer ("southern");
            break;

        default: // let's assume this is west
            iRet = mutils_addToDialogBuffer ("western");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer (" pathway.\n\n");
        if (iRet != 0) return iRet;
    }

    //
    // Increment the usage counts on the new position and the link id we used.
    //
    sRet = mapdata_incrementPosUsage (sNewPosId);
    if (sRet == -1) return 10;

    // reset the stair values.
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;
    // If the position we have navigated to is a set of stairs (top or base), these values will be set correctly
    //  by the called event function anyway.

    // set the position to what we are after.
    gstructActStateGlobal.sPosId = sNewPosId;

    // if the monsters have been unleashed.. shift the encounter array.
    if (gstructActStateGlobal.sAct1Monsters != 0)
    {
        actionstate_shiftEncounterArray ();
    }

    // always take away some stamina for a navigation action.
    switch (gstructActStateGlobal.sActId)
    {
    case 1:
        // during Act 1, Wilda is carrying some heavy equipment.
        fStaDec = actionstate_randomFloatValue ((float)0.08, (float)0.045, 200);
        break;

    case 2:
        // during Act 2, Wilda isn't as heavily weighed down.
        fStaDec = actionstate_randomFloatValue ((float)0.06, (float)0.025, 200);
        break;

    case 3:
        // Wilda and Crystal are both masturbating while walking around
        fStaDec = actionstate_randomFloatValue ((float)0.065, (float)0.03, 200);
        break;

    default: // case 4:
        // Wilda is walking around while pregnant
        fStaDec = actionstate_randomFloatValue ((float)0.1, (float)0.08, 200);
        break;
    }

    // increment the stamina decrement according to the terrain.
    switch (gpstructMapLinkDynamicCurrent[sLinkId - 1].cRand1)
    {
    case 0:
        fStaDec = (float)(fStaDec * 1.1);
        break;

    case 1:
        fStaDec = (float)(fStaDec * 1.3);
        break;

    case 2:
        fStaDec = (float)(fStaDec * 1.5);
        break;

    case 3:
        fStaDec = (float)(fStaDec * 1.7);
        break;

    default: // case 4:
        fStaDec = (float)(fStaDec * 1.9);
        break;
    }

    if (gstructActStateGlobal.sActId == 3)
    {
        // Crystal already knows the terrain rather well, so her stamina isn't hit as hard when they traverse it.
        actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)(fStaDec / 2), (int)0);
    }

    // now change the increment again depending upon how well the PC knows the terrain.
    switch (gpstructMapLinkDynamicCurrent[sLinkId - 1].cRand1)
    {
    case 0:
        fStaDec = (float)(fStaDec * 1.5);
        break;

    case 1:
        fStaDec = (float)(fStaDec * 1.2);
        break;

    case 2:
        fStaDec = (float)(fStaDec * 0.9);
        break;

    case 3:
        fStaDec = (float)(fStaDec * 0.6);
        break;
    }

    // now to apply the corrected stamina hit (to Wilda).
    actionstate_statSubtraction (&gstructActStateCharWilda.structS, fStaDec, (int)0);

    // now increment the usage of the pathway.
    mapdata_incrementLinkUsage (sLinkId);

    // turn off the allow monster trigger for the specific set out conditions.
    if ((gstructActStateGlobal.sActId == 1) && (gstructActStateGlobal.sAct1Monsters == 0))
        cAllowMonsterTrigger = 0;
    else if ((gstructActStateGlobal.sActId == 2) && (gstructActStateGlobal.sAct2Monsters == 0))
        cAllowMonsterTrigger = 0;
    else if ((gstructActStateGlobal.sActId == 3) && (gstructActStateGlobal.sAct3Monsters == 0))
        cAllowMonsterTrigger = 0;

    //
    // Now for the event scene stuff.
    //
    cSpecialId = gpstructMapPosStaticCurrent[sNewPosId - 1].cSpecialId;

    if (cSpecialId != 0)
    {
        char cLockError = 0;
        int iOffset = 0;

        while (1)
        {
            if (gstructEventSceneList[iOffset].cSpecialSceneId == -1)
            {
                cLockError = 1;
                break;
            }

            if (gstructEventSceneList[iOffset].cSpecialSceneId == cSpecialId)
                break;

            iOffset++;
        }

        if (cLockError == 1)
        {
            char szWorking[80];

            sprintf (szWorking, "ERROR: could not lookup event id %d\n\n", (int)cSpecialId);

            iRet = mutils_addToDialogBuffer (szWorking);
            if (iRet != 0) return iRet;
        }
        else
        {
            iRet = gstructEventSceneList[iOffset].vFunc (cSubFlag + 1);

            // a -1 return means that the scene function is going somewhere else other than
            //  navigation.
            if (iRet == -1)
                return 0;

            if (iRet != 0) return iRet;
        }
    }
    else if (cAllowMonsterTrigger != 0) // with no event being triggered, we should search to see if there is an encounter about to happen.
    {
        int     iMapPercentage;

        iMapPercentage = (int)gpstructMapPosStaticCurrent[sNewPosId - 1].cPcentEnc;

        if (iMapPercentage > 1)
        {
            int     iPastPercentage = 0;
            short   sOffset1;

            for (sOffset1 = 0; sOffset1 < 50; sOffset1++)
            {
                if (gstructActStateGlobal.caEncounterArray[sOffset1] != 0)
                    iPastPercentage += 2;
            }

            // the reason for the complexity is that past percentage acts as a limit on the encounter happening.
            //  The idea is if the map says 10%, the code is not looking at a RNG first, it is looking at the
            //  past 50 encounters to figure out if it is 10%. If the past encounters is lower than what the
            //  map says, then the code considers the RNG. If the PC wonders out of a high encounter area into
            //  a low encounter area, it means that they are less likely to have another encounter straight away.
            if (iPastPercentage <= iMapPercentage)
            {
                int     iRndPercentage;

                // the idea is to bring in the likelihood of a match when the entry aperture
                //  (iPastPercentage verses iMapPercentage) is rather low. So I decrease the RNG selection
                //  down when the map percentage is below 50%.
                if (iMapPercentage < 49)
                    iRndPercentage = (int)(rand() % (int)(iMapPercentage + 50)); // this narrows in the range a little bit.
                else
                    iRndPercentage = (int)(rand() % 100);

                if (iRndPercentage <= iMapPercentage)
                {
                    if (gcDebugFlag != 0)
                    {
                        char szWorking[90];

                        sprintf (szWorking, "debug: ENCOUNTER triggered PosId %d, %d pct <= %d rnd, %d past enc.\n\n", (int)sNewPosId, iMapPercentage, iRndPercentage, iPastPercentage);

                        iRet = mutils_addToDialogBuffer (szWorking);
                        if (iRet != 0) return iRet;
                    }

                    // override the direction, because we don't know which way we are facing now.
                    gstructActStateGlobal.cDirect = 0;

                    switch (gstructActStateGlobal.sActId)
                    {
                    case 1: // act 1
                        iRndNum = (int)(rand() % 3);

                        if (iRndNum == 2)
                            iRet = mutils_addToDialogBuffer ("As Wilda reaches the end of the pathway, a tentacle monster approaches. Wilda readies her sword.\n\n");
                        else if (iRndNum != 0)
                            iRet = mutils_addToDialogBuffer ("When Wilda arrives at the end of the pathway, a tentacle monster drops from above, into the liquid. Wilda quickly draws her sword.\n\n");
                        else
                            iRet = mutils_addToDialogBuffer ("As Wilda arrives at the end of the pathway, she hears a splashing sound from behind her. She turns around to see that a tentacle monster has followed her along the pathway. Wilda draws her sword.\n\n");
                        if (iRet != 0) return iRet;

                        // setup our monster parameters
                        gstructActStateOpponent.iConfidence = actionstate_randomIntValue (40, 5);
                        gstructActStateOpponent.iRage = actionstate_randomIntValue (42, 2);
                        gstructActStateOpponent.iDesire = actionstate_randomIntValue (50, 15);
                        gstructActStateOpponent.iHitPoints = 5000;
                        gstructActStateOpponent.iFear = actionstate_randomIntValue (38, 5);
                        gstructActStateOpponent.cActive = 1;

                        if (gcDebugFlag != 0)
                        {
                            char szWorking[180];

                            sprintf (szWorking, "debug: monster starting values C:%d R:%d D:%d F:%d\n\n",
                                    gstructActStateOpponent.iConfidence,
                                    gstructActStateOpponent.iRage,
                                    gstructActStateOpponent.iDesire,
                                    gstructActStateOpponent.iFear);

                            iRet = mutils_addToDialogBuffer (szWorking);
                            if (iRet != 0) return iRet;
                        }

                        // pass control over for the Act1 combat encounter actions.
                        iRet = gamelogic04_scene1040 (0, cSubFlag + 1);
                        return iRet;

                    case 2: // act 2
                        iRndNum = (int)(rand() % 3);

                        if (iRndNum == 2)
                            iRet = mutils_addToDialogBuffer ("While walking along the pathway, Wilda had a feeling that she is being watched. Wilda readies her spanking paddle, and a tentacle monster appears.\n\n");
                        else if (iRndNum != 0)
                            iRet = mutils_addToDialogBuffer ("As Wilda arrives at the end of the pathway, she can see a tentacle monster, which is attached to a wall, starting to stir. Wilda readies her spanking paddle.\n\n");
                        else
                            iRet = mutils_addToDialogBuffer ("For some time now, Wilda has been hearing splashing of liquid from ahead of her. Wilda does not back down from a fight, so she has readied her spanking paddle and continued walking. At the end of the pathway, a tentacle monster falls from the ceiling in front of Wilda.\n\n");
                        if (iRet != 0) return iRet;

                        // setup our monster parameters
                        gstructActStateOpponent.iConfidence = actionstate_randomIntValue (40, 5);
                        gstructActStateOpponent.iRage = actionstate_randomIntValue (42, 2);
                        gstructActStateOpponent.iDesire = actionstate_randomIntValue (50, 15);
                        gstructActStateOpponent.iHitPoints = 5000;
                        gstructActStateOpponent.iFear = actionstate_randomIntValue (38, 5);
                        gstructActStateOpponent.cActive = 1;

                        if (gcDebugFlag != 0)
                        {
                            char szWorking[180];

                            sprintf (szWorking, "debug: monster starting values C:%d R:%d D:%d F:%d\n\n",
                                    gstructActStateOpponent.iConfidence,
                                    gstructActStateOpponent.iRage,
                                    gstructActStateOpponent.iDesire,
                                    gstructActStateOpponent.iFear);

                            iRet = mutils_addToDialogBuffer (szWorking);
                            if (iRet != 0) return iRet;
                        }

                        // pass control over for the Act2 combat encounter actions.
                        iRet = gamelogic04_scene1050 (0, cSubFlag + 1);
                        return iRet;

                    case 3: // act 3
                        iRndNum = (int)(rand() % 3);

                        if (iRndNum == 2)
                            iRet = mutils_addToDialogBuffer ("Wilda and Crystal are walking along a pathway, when a tentacle monster drops from the ceiling in front of them. Wilda glances at Crystal, who just nods her head. Wilda smiles and looks at the tentacle monster.\n\n");
                        else if (iRndNum != 0)
                            iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the end of a pathway, when a tentacle monster rises up out of the liquid in front of Wilda. Wilda smiles, as she is ready.\n\n");
                        else
                            iRet = mutils_addToDialogBuffer ("After arriving at the end of a pathway, a tentacle monster appears. Crystal steps back, giving both Wilda and the tentacle monster space.\n\n");
                        if (iRet != 0) return iRet;

                        // setup our monster parameters
                        gstructActStateOpponent.iConfidence = actionstate_randomIntValue (40, 5);
                        gstructActStateOpponent.iRage = actionstate_randomIntValue (42, 2);
                        gstructActStateOpponent.iDesire = actionstate_randomIntValue (50, 15);
                        gstructActStateOpponent.iHitPoints = 5000;
                        gstructActStateOpponent.iFear = actionstate_randomIntValue (38, 5);
                        gstructActStateOpponent.cActive = 1;

                        if (gcDebugFlag != 0)
                        {
                            char szWorking[180];

                            sprintf (szWorking, "debug: monster starting values C:%d R:%d D:%d F:%d\n\n",
                                    gstructActStateOpponent.iConfidence,
                                    gstructActStateOpponent.iRage,
                                    gstructActStateOpponent.iDesire,
                                    gstructActStateOpponent.iFear);

                            iRet = mutils_addToDialogBuffer (szWorking);
                            if (iRet != 0) return iRet;
                        }

                        // pass control over for the Act3 combat encounter actions.
                        iRet = gamelogic04_scene1060 (0, cSubFlag + 1);
                        return iRet;

                    default: // act 4
                        iRndNum = (int)(rand() % 4);

                        if (iRndNum == 3)
                            iRet = mutils_addToDialogBuffer ("Wilda arrives at the end of a pathway, and notices ripples in the liquid that are not from her. Wilda waits with anticipation as a tentacle monster appears.\n\n");
                        else if (iRndNum == 2)
                            iRet = mutils_addToDialogBuffer ("As she arrives at the end of a pathway, Wilda notices a tentacle monster that is clinging to a wall. Wilda smiles and walks over to it.\n\n");
                        else if (iRndNum != 0)
                            iRet = mutils_addToDialogBuffer ("When Wilda arrives at the end of a pathway, she is greeted by a tentacle monster that drops from the ceiling. Wilda licks her lips in anticipation as she approaches it.\n\n");
                        else
                            iRet = mutils_addToDialogBuffer ("As she is walking along a pathway, Wilda hears something moving behind her. Wilda decides to keep walking to the end of the pathway, and allow her stalker to catch up. Wilda did not have to wait long for the tentacle monster to arrive.\n\n");
                        if (iRet != 0) return iRet;

                        // setup our monster parameters
                        gstructActStateOpponent.iConfidence = actionstate_randomIntValue (40, 5);
                        gstructActStateOpponent.iRage = actionstate_randomIntValue (42, 2);
                        gstructActStateOpponent.iDesire = actionstate_randomIntValue (50, 15);
                        gstructActStateOpponent.iHitPoints = 5000;
                        gstructActStateOpponent.iFear = actionstate_randomIntValue (38, 5);
                        gstructActStateOpponent.cActive = 1;

                        if (gcDebugFlag != 0)
                        {
                            char szWorking[180];

                            sprintf (szWorking, "debug: monster starting values C:%d R:%d D:%d F:%d\n\n",
                                    gstructActStateOpponent.iConfidence,
                                    gstructActStateOpponent.iRage,
                                    gstructActStateOpponent.iDesire,
                                    gstructActStateOpponent.iFear);

                            iRet = mutils_addToDialogBuffer (szWorking);
                            if (iRet != 0) return iRet;
                        }

                        // pass control over for the Act4 combat encounter actions.
                        iRet = gamelogic04_scene1070 (0, cSubFlag + 1);
                        return iRet;
                    }
                }
                else
                {
                    if (gcDebugFlag != 0)
                    {
                        char szWorking[80];

                        sprintf (szWorking, "debug: Enc PosId %d, %d pct > %d rnd, %d past enc.\n\n", (int)sNewPosId, iMapPercentage, iRndPercentage, iPastPercentage);

                        iRet = mutils_addToDialogBuffer (szWorking);
                        if (iRet != 0) return iRet;
                    }
                }
            }
            else
            {
                if (gcDebugFlag != 0)
                {
                    char szWorking[80];

                    sprintf (szWorking, "debug: Enc PosId %d, %d pct < %d past enc.\n\n", (int)sNewPosId, iMapPercentage, iPastPercentage);

                    iRet = mutils_addToDialogBuffer (szWorking);
                    if (iRet != 0) return iRet;
                }
            }
        }
        else
        {
            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: Enc PosId %d, default no encounter.\n\n", (int)sNewPosId);

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }
        }
    }

    // need to use a sub-scene id of 2 when calling back to navigation, so that masturbation is potentially available, and the code knows to show the direction.
    iRet = gamelogic02_scene1020 (2, cSubFlag + 1);
    return iRet;
}

//
// masturbation action
//
int gamelogic02_scene1022 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    short sVisit;
    float fCompare;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (cSubFlag == 0)
    {
        iRet = mutils_addToDialogBuffer (">Masturbate\n\n");
        if (iRet != 0) return iRet;
    }

    // get the visit count, and increment it while we are at it.
    sVisit = mapdata_incrementPosUsage (gstructActStateGlobal.sPosId);

    if (iSubSceneId != 0)
    {
        iRet = mutils_addToDialogBuffer ("Wilda finds that she can no longer hold out. She desperately needs to satisfy her urges.\n\n\n[4 minutes later...]\n\nWilda takes a deep breath and sighs. She ended up masturbating twice in a row.\n\nWilda decides that now that her private time is over, and she needs to get moving again.\n\n");
        if (iRet != 0) return iRet;

        // decrease Lust
        fCompare = (float)((float)gstructActStateCharWilda.structF.iNum / (float)2.83);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, fCompare, (int)1);

        // decrease Frigidity
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)4.762, (int)50);

        // decrease Stamina
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)2.381, (int)0);
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda finds it strange that her arousal is");
        if (iRet != 0) return iRet;

        if (gstructActStateGlobal.sActId != 1)
        {
            iRet = mutils_addToDialogBuffer (" still");
            if (iRet != 0) return iRet;
        }

        iRet = mutils_addToDialogBuffer (" growing, but decides to take care of her urges now, rather than wait till later.\n\n\n[2 minutes later...]\n\nIt was only once, but once was enough. Wilda looks around. She is still alone inside this dungeon.\n\n");
        if (iRet != 0) return iRet;

        // decrease Lust
        fCompare = (float)((float)gstructActStateCharWilda.structF.iNum / (float)3.98);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, fCompare, (int)1);

        // decrease Frigidity
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)2.172, (int)50);

        // decrease Stamina
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)1.066, (int)0);

        if (sVisit > 2)
            iRet = mutils_addToDialogBuffer ("Wilda decides it is time to leave, as this place is starting to get boring.\n\n");
        else
            iRet = mutils_addToDialogBuffer ("Wilda decides that she should keep moving.\n\n");
        if (iRet != 0) return iRet;
    }

    // I set the sub-scene id to one, so that the nav menu does not consider masturbation, this way
    //  the PC isn't allowed to masturbate multiple times in a row at the one location.
    iRet = gamelogic02_scene1020 (1, cSubFlag + 1);
    return iRet;
    // It means that the PC needs to navigate to clear the lust, however there IS a way around it
    //  (and I don't intend to fix this).
    // The player can enter the inventory/status, when they exit inventory/status, nav is called
    //  with subid 0, and masturbation is available again. If the player is willing to enter and
    //  exit the inventory multiple times in a row, in order to masturbate and reduce lust, fine.
    // I have no problem with that, because lust is being trickle added to by the main nav function anyway.
}

