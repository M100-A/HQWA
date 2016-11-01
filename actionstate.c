//
// actionstate.c
//
// character status storage.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"

// external linkage to the game variables.
extern  char    gcDebugFlag;

//
// This is the types of inventory items that can be equipped or stored..
//
struct  actionstate_invdescription gstructInventoryDescription[] =
{
    { 0, 0, "Nothing" }, // 00 (nothing, this is useful as the id for an empty clothing slot)..
    { 1, 0, "gold" }, // 01
    { 1, 0, "stamina elixir" }, // 02
    { 0, 1, "iron double edged sword" }, // 03
    { 0, 1, "steel double edged sword" }, // 04
    { 0, 1, "spanking paddle" }, // 05
    { 0, 1, "leather boy cut sleeveless body suit, with bronze plating" }, // 06
    { 0, 1, "leather thong leotard, with iron plating" }, // 07
    { 0, 1, "chainmail bikini" }, // 08
    { 0, 1, "latex cloak and rubber underbust corset" }, // 09
    { 0, 1, "open bust latex garter dress with suspenders" }, // 10 ** Crystal
    { 0, 1, "rubber underbust corset and rubber harness bra" }, // 11
    { 0, 1, "rubber harness bra" }, // 12
    { 0, 1, "iron capped leather combat boots" }, // 13
    { 0, 1, "leather combat boots, with protruding steel spikes" }, // 14
    { 0, 1, "latex thigh-high stockings and croc rubber shoes" }, // 15
    { 0, 1, "latex thigh-high stirrup-stockings and thigh-high low-heel rubber boots" }, // 16 ** Crystal
    { 0, 1, "iron demi-gauntlets with leather gloves" }, // 17
    { 0, 1, "iron demi-gauntlets with chain-mail gloves" }, // 18
    { 0, 1, "shoulder length latex gloves" }, // 19
    { 0, 0, "leather backpack" }, // 20
    { 0, 0, "latex backpack" }, // 21
    { 1, 0, "torch" }, // 22
    { 0, 0, "aquamarine lantern" }, // 23
    { 0, 0, "yo-yo" }, // 24
    { 0, 0, "bivouac sack" }, // 25
    { 0, 0, "holy artifact in a box" }, // 26
    { -1, -1, NULL }
};

//
// Inventory dynamic data
//
struct  actionstate_inventory *gpstructActStateInventory = NULL;
short   gsActStateInventorySize = 0;

//
// Character data
//
struct  actionstate_charstats gstructActStateCharWilda;
struct  actionstate_charstats gstructActStateCharCrystal;
struct  actionstate_opponentstats gstructActStateOpponent;
struct  actionstate_globalvars gstructActStateGlobal;

//
// Function to init the inventory storage (it also sets it to start game state)
//
int actionstate_initInventoryPlusVars ()
{
    short   sOffset1;
#ifdef INTERFACE_CURSES
    int     iRet;
#endif

    sOffset1 = 0;

    // rather than hard-code the size of the inventory storage,
    //   I simply make the code figure out how big the structure
    //   should be by counting the number of entries in the
    //   description list.

    while (1)
    {
        if (gstructInventoryDescription[sOffset1].cMultiFlag == -1)
            break;

        sOffset1++;
    }

    // allocate the memory
    gpstructActStateInventory = (struct actionstate_inventory *)malloc ((size_t)sizeof (struct actionstate_inventory) * (size_t)((size_t)sOffset1 + (size_t)2));

    // if there was a problem with the malloc, return 1.
    if (gpstructActStateInventory == NULL)
        return 1;

    gsActStateInventorySize = sOffset1;

    //
    // note: unlike mapdata, 1 = 1. Position 0 isn't used
    //

    // this is sort of a sanity check.. because if the expectation is off, then the hard set below is going to potentially be out of bounds.
    if (gsActStateInventorySize != 27)
    {
#ifdef INTERFACE_CURSES
        iRet = mutils_addToDialogBuffer ("Inventory: allocation not as expected!\n");
        if (iRet != 0) return iRet;
#endif

        return 6;
    }

    // first reset everything to 0.
    for (sOffset1 = 0; (gsActStateInventorySize + 1) > sOffset1; sOffset1++)
    {
        gpstructActStateInventory[sOffset1].sCount = 0;
        gpstructActStateInventory[sOffset1].structEff.iNum = 0;
        gpstructActStateInventory[sOffset1].structEff.fFraction = (float)0;
    }

    //
    // init the starting stats for Wilda
    //

    // Endurance (HP max)
    gstructActStateCharWilda.structE.iNum = 250;
    gstructActStateCharWilda.structE.fFraction = (float)0.2;

    // Stamina (HP current)
    gstructActStateCharWilda.structS.iNum = 248;
    gstructActStateCharWilda.structS.fFraction = (float)0.7;

    // Might (Strength)
    gstructActStateCharWilda.structM.iNum = 124;
    gstructActStateCharWilda.structM.fFraction = (float)0.12;

    // Karma (Luck/Fate)
    gstructActStateCharWilda.structK.iNum = 24;
    gstructActStateCharWilda.structK.fFraction = (float)0.31;

    // Frigidity (Lust max)
    gstructActStateCharWilda.structF.iNum = 231;
    gstructActStateCharWilda.structF.fFraction = (float)0.23;

    // Lust (Arousal)
    gstructActStateCharWilda.structL.iNum = 3;
    gstructActStateCharWilda.structL.fFraction = (float)0.1;

    // Reflexes (Combat Experience)
    gstructActStateCharWilda.structR.iNum = 102;
    gstructActStateCharWilda.structR.fFraction = (float)0.4;

    // Oral experience
    gstructActStateCharWilda.structO.iNum = 1;
    gstructActStateCharWilda.structO.fFraction = (float)0.1;

    // Vaginal experience
    gstructActStateCharWilda.structV.iNum = 11;
    gstructActStateCharWilda.structV.fFraction = (float)0.2;

    // Anal experience
    gstructActStateCharWilda.structA.iNum = 2;
    gstructActStateCharWilda.structA.fFraction = (float)0.4;

    // Weapon effectiveness: Iron double edged sword
    gstructActStateCharWilda.structW.iNum = 60;
    gstructActStateCharWilda.structW.fFraction = (float)0.5;
    gstructActStateCharWilda.sSlotW = 3;

    // Gauntlet/Gloves effectiveness: Iron demi-gauntlets with leather gloves
    gstructActStateCharWilda.structG.iNum = 33;
    gstructActStateCharWilda.structG.fFraction = (float)0.5;
    gstructActStateCharWilda.sSlotG = 16;

    // Boots/Shoes effectiveness: Iron capped leather combat boots
    gstructActStateCharWilda.structB.iNum = 29;
    gstructActStateCharWilda.structB.fFraction = (float)0.4;
    gstructActStateCharWilda.sSlotB = 12;

    // Clothing/Armor effectiveness: Leather boy cut sleeveless body suit with, with bronze plating
    gstructActStateCharWilda.structC.iNum = 24;
    gstructActStateCharWilda.structC.fFraction = (float)0.5;
    gstructActStateCharWilda.sSlotC = 6;

    //
    // init the starting stats for Crystal
    //

    // Endurance (HP max)
    gstructActStateCharCrystal.structE.iNum = 1223;
    gstructActStateCharCrystal.structE.fFraction = (float)0.4;

    // Stamina (HP current)
    gstructActStateCharCrystal.structS.iNum = 1194;
    gstructActStateCharCrystal.structS.fFraction = (float)0.63;

    // Might (Strength)
    gstructActStateCharCrystal.structM.iNum = 420;
    gstructActStateCharCrystal.structM.fFraction = (float)0.42;

    // Karma (Luck/Fate)
    gstructActStateCharCrystal.structK.iNum = 3203;
    gstructActStateCharCrystal.structK.fFraction = (float)0.5;

    // Frigidity (Lust max)
    gstructActStateCharCrystal.structF.iNum = 90;
    gstructActStateCharCrystal.structF.fFraction = (float)0.5;

    // Lust (Arousal)
    gstructActStateCharCrystal.structL.iNum = 40;
    gstructActStateCharCrystal.structL.fFraction = (float)0.7;

    // Reflexes (Combat Experience)
    gstructActStateCharCrystal.structR.iNum = 453;
    gstructActStateCharCrystal.structR.fFraction = (float)0.6;

    // Oral experience
    gstructActStateCharCrystal.structO.iNum = 2304;
    gstructActStateCharCrystal.structO.fFraction = (float)0.6;

    // Vaginal experience
    gstructActStateCharCrystal.structV.iNum = 2613;
    gstructActStateCharCrystal.structV.fFraction = (float)0.4;

    // Anal experience
    gstructActStateCharCrystal.structA.iNum = 2432;
    gstructActStateCharCrystal.structA.fFraction = (float)0.54;

    // Weapon effectiveness: Spanking paddle
    gstructActStateCharCrystal.structW.iNum = 10;
    gstructActStateCharCrystal.structW.fFraction = (float)0.5;
    gstructActStateCharCrystal.sSlotW = 5;

    // Gauntlet/Gloves effectiveness: Shoulder length latex gloves
    gstructActStateCharCrystal.structG.iNum = 4;
    gstructActStateCharCrystal.structG.fFraction = (float)0.53;
    gstructActStateCharCrystal.sSlotG = 18;

    // Boots/Shoes effectiveness: Latex thigh-high stirrup-stockings and thigh-high low-heel rubber boots
    gstructActStateCharCrystal.structB.iNum = 41;
    gstructActStateCharCrystal.structB.fFraction = (float)0.64;
    gstructActStateCharCrystal.sSlotB = 15;

    // Clothing/Armor effectiveness: Open bust latex garter dress with suspenders
    gstructActStateCharCrystal.structC.iNum = 13;
    gstructActStateCharCrystal.structC.fFraction = (float)0.5;
    gstructActStateCharCrystal.sSlotC = 10;

    //
    // init the stats for the opponent monster
    //
    gstructActStateOpponent.cActive = 0;
    gstructActStateOpponent.iRage = 0;
    gstructActStateOpponent.iFear = 0;
    gstructActStateOpponent.iConfidence = 0;
    gstructActStateOpponent.iDesire = 0;
    gstructActStateOpponent.iHitPoints = 0;

    //
    // init the global vars
    //
    gstructActStateGlobal.sMapId = 1;
    gstructActStateGlobal.sActId = 1;
    gstructActStateGlobal.sPosId = 2;
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cEnteredDungeon = 0;
    gstructActStateGlobal.sAct1Monsters = 0;
    gstructActStateGlobal.sAct2Monsters = 0;
    gstructActStateGlobal.sAct3Monsters = 0;
    gstructActStateGlobal.sAct4Monsters = 0;
    gstructActStateGlobal.cGingerEncounter = 0;

#ifdef INTERFACE_CURSES
    iRet = mutils_addToDialogBuffer ("Inventory: 26 dynamic entries + init of game vars.\n");
    if (iRet != 0) return iRet;
#endif

    return 0;
}

//
// Function to add to a stat.
//
void actionstate_statAddition (struct actionstate_stat *pstructStat, float fValue, int iMax)
{
    float fRedo;

    // first, take care of the whole numbers.
    while (fValue >= 1)
    {
        pstructStat->iNum++;
        fValue--;
    }

    // if what we have has exceeded or equaled the maximum.
    if (pstructStat->iNum >= iMax)
    {
        // set the stat to the maximum value
        pstructStat->iNum = iMax;
        pstructStat->fFraction = (float)0;

        return;
    }

    // dump the remainder into the float fraction and to round it to 3 decimal places.
#ifdef WIN32
    // this is the workaround for WIN32, which does not have a roundf
    fRedo = (float)floorf ((((float)pstructStat->fFraction + (float)fValue) * (float)1000) + (float)0.5) / (float)1000;
#else
    fRedo = (float)roundf (((float)pstructStat->fFraction + (float)fValue) * (float)1000) / (float)1000;
#endif // WIN32

    // take care of the overflow
    while (fRedo >= 1)
    {
        pstructStat->iNum++;
        fRedo--;
    }

    // if what we have has exceeded or equaled the maximum.
    if (pstructStat->iNum >= iMax)
    {
        // set the stat to the maximum value
        pstructStat->iNum = iMax;
        pstructStat->fFraction = 0;

        return;
    }

    pstructStat->fFraction = fRedo;
}

//
// Function to subtract from a stat.
//
void actionstate_statSubtraction (struct actionstate_stat *pstructStat, float fValue, int iMin)
{
    float fRedo;

    // first, take care of the whole numbers.
    while (fValue >= 1)
    {
        pstructStat->iNum--;
        fValue--;
    }

    // if the remainder is greater than the fraction.
    if (pstructStat->fFraction < fValue)
    {
        // move some stuff around, so that the fraction is big enough.
        pstructStat->iNum--;
        pstructStat->fFraction++;
    }

    // if what we have is less than the minimum.
    if (pstructStat->iNum < iMin)
    {
        // set the stat to the minimum value
        pstructStat->iNum = iMin;
        pstructStat->fFraction = 0;

        return;
    }

    // dump the remainder into the float fraction and to round it to 3 decimal places.
#ifdef WIN32
    // this is the workaround for WIN32, which does not have a roundf
    fRedo = (float)floorf ((((float)pstructStat->fFraction - (float)fValue) * (float)1000) + (float)0.5) / (float)1000;
#else
    fRedo = (float)roundf (((float)pstructStat->fFraction - (float)fValue) * (float)1000) / (float)1000;
#endif // WIN32

    // take care of the overflow (this should not happen, but you never know).
    while (fRedo >= 1)
    {
        pstructStat->iNum++;
        fRedo--;
    }

    pstructStat->fFraction = fRedo;
}

//
// Function to right shift the encounter array by one.
//
void actionstate_shiftEncounterArray ()
{
    short   sOffset = 49;

    while (sOffset > 0)
    {
        gstructActStateGlobal.caEncounterArray[sOffset] = gstructActStateGlobal.caEncounterArray[sOffset - 1];
        sOffset--;
    }

    gstructActStateGlobal.caEncounterArray[0] = 0;
}

//
// Function to perform a random calculation for a floating point value between two values
//
float actionstate_randomFloatValue (float fMax, float fMin, int iIncrement)
{
    int     iRndValue;
    float   fValue;
    float   fIntermediate;

    iRndValue = (int)(rand() % iIncrement);

    fMax -= (float)fMin;

    fIntermediate = (float)((float)iRndValue / (float)iIncrement) * (float)fMax;

    fValue = (float)fMin + (float)fIntermediate;

    return fValue;
}

//
// Function to perform a random calculation for a integer value between two values
//
int actionstate_randomIntValue (int iMax, int iMin)
{
    int     iRndValue;
    int     iValue;

    iMax -= iMin;

    iRndValue = (int)(rand() % iMax);

    iValue = iMin + iRndValue;

    return iValue;
}

//
// Function to convert a structure value into a floating point value
//
float actionstate_convertStatToFloat (struct actionstate_stat *pstructStat)
{
    float   fValue;

    fValue = (float)pstructStat->iNum;
    fValue += (float)pstructStat->fFraction;

    // Note: at this stage, I do not care about the precision loss..

    return fValue;
}

//
// Function to hard change the values for a monster opponent
//
void actionstate_hardAlterMonsterValues (int iRage, int iFear, int iConfidence, int iDesire, int iHitPoints)
{
    gstructActStateOpponent.iRage += iRage;
    gstructActStateOpponent.iFear += iFear;
    gstructActStateOpponent.iConfidence += iConfidence;
    gstructActStateOpponent.iDesire += iDesire;
    gstructActStateOpponent.iHitPoints += iHitPoints;
}

//
// Function to hard change the values for a monster opponent
//
int actionstate_randomAct1AlterMonsterValues (char cAffectHP, float fValHP, float fValFear, float fValDesire, float fValConfidence, float fValRage)
{
    float fStrValM;
    float fStrValK;
    float fStrValF;
    float fStrValL;
    float fStrValR;
    float fStrValW;
    float fStrValG;
    float fStrValB;
    float fStrValC;

    float fVal1Pwr;
    float fVal1Val;
    float fVal1Con;

    int iVal1HitHP;
    int iVal1HitFear;
    int iVal1HitDesire;
    int iVal1HitConfidence;
    int iVal1HitRage;
    int iRndValue;

    fStrValM = actionstate_convertStatToFloat (&gstructActStateCharWilda.structM);
    fStrValK = actionstate_convertStatToFloat (&gstructActStateCharWilda.structK);
    fStrValF = actionstate_convertStatToFloat (&gstructActStateCharWilda.structF);
    fStrValL = actionstate_convertStatToFloat (&gstructActStateCharWilda.structL);
    fStrValR = actionstate_convertStatToFloat (&gstructActStateCharWilda.structR);
    fStrValW = actionstate_convertStatToFloat (&gstructActStateCharWilda.structW);
    fStrValG = actionstate_convertStatToFloat (&gstructActStateCharWilda.structG);
    fStrValB = actionstate_convertStatToFloat (&gstructActStateCharWilda.structB);
    fStrValC = actionstate_convertStatToFloat (&gstructActStateCharWilda.structC);

    if (cAffectHP != 0)
    {
        float fAdjust;
        float fStrValS;

        fStrValS = actionstate_convertStatToFloat (&gstructActStateCharWilda.structS);

        // some randomness for adjusting the concentration
        iRndValue = (int)(rand() % 2000);

        fAdjust = (float)((float)iRndValue / (float)1000) - 1;
        fAdjust /= (float)20;

        fVal1Con = (float)1.21 - (float)((float)(fStrValL / 2) / (float)fStrValF);
        fVal1Con += fAdjust;

        if (fVal1Con > 1)
            fVal1Con = 1;

        // power is from Might, but capped by Stamina.
        fVal1Val = fStrValM;
        if (fStrValS < fStrValM)
            fVal1Val = fStrValS;

        // and adjusted by concentration.
        fVal1Pwr = fVal1Val * fVal1Con;

        switch (cAffectHP)
        {
        case 1: // weapon alone..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + fStrValW);
            break;

        case 2: // gauntlets alone..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + fStrValG);
            break;

        case 3: // boots alone..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + fStrValB);
            break;

        case 4: // weapon + gauntlets..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + (fStrValW / 2) + (fStrValG / 2));
            break;

        case 5: // weapon + boots..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + (fStrValW / 2) + (fStrValB / 2));
            break;

        default: // gauntlets + boots..
            iRndValue = (int)(rand() % 800) + (int)(fStrValK + fStrValR + fStrValM + fStrValS + (fStrValG / 2) + (fStrValB / 2));
            break;
        }

        iVal1HitHP = (int)floorf(((((float)((float)iRndValue / (float)80) + 0.1) * fVal1Pwr) / 100) * fValHP);

        if (gcDebugFlag != 0)
        {
            char szWorking[100];
            int iRet;

            sprintf (szWorking, "debug: -HP %d (c: %0.3f, p: %0.3f) \n", iVal1HitHP, fVal1Con, fVal1Pwr);

            iRet = mdialog_addToDialogWithSrchRep (szWorking);
            if (iRet != 0) return iRet;
        }

        gstructActStateOpponent.iHitPoints -= iVal1HitHP;
    }

    // some randomness for adjusting the fear
    iRndValue = (int)(rand() % 500) + (int)(fStrValK + fStrValR + fStrValM);

    iVal1HitFear = (int)floorf((float)(((float)iRndValue / (float)50) + 0.1) * fValFear);

    // some randomness for adjusting the desire
    iRndValue = (int)(rand() % 200) + (int)(fStrValK * 2) - (int)((fStrValL / fStrValF) * 80);

    iVal1HitDesire = (int)floorf((float)(((float)iRndValue / (float)20) + 0.1) * fValDesire);

    // some randomness for adjusting the confidence
    iRndValue = (int)(rand() % 500) + (int)(fStrValK + fStrValW + fStrValB + fStrValC + fStrValG);

    iVal1HitConfidence = (int)floorf((float)(((float)iRndValue / (float)50) + 0.1) * fValConfidence);

    // some randomness for adjusting the rage
    iRndValue = (int)(rand() % 500) + (int)(fStrValK + fStrValR);

    iVal1HitRage = (int)floorf((float)(((float)iRndValue / (float)50) + 0.1) * fValRage);

    if (gcDebugFlag != 0)
    {
        char szWorking[100];
        int iRet;

        sprintf (szWorking, "debug: +Fear %d, -Des %d, -Conf %d, -Rage %d\n\n", iVal1HitFear, iVal1HitDesire, iVal1HitConfidence, iVal1HitRage);

        iRet = mdialog_addToDialogWithSrchRep (szWorking);
        if (iRet != 0) return iRet;
    }

    gstructActStateOpponent.iRage -= iVal1HitRage;
    gstructActStateOpponent.iFear += iVal1HitFear;
    gstructActStateOpponent.iDesire -= iVal1HitDesire;
    gstructActStateOpponent.iConfidence -= iVal1HitConfidence;

    return 0;
}

//
// Function to workout what the monsters are going to do during Act1 (and Act2)
//
// returns 0 for Just Runaway.
// returns 1 for Goo spray, then runaway.
// returns 2 for Tentacle smash, then runaway.
// returns 3 for Cower in fear, then runaway.
// returns 4 for Goo spray, then Tentacle smash.
// returns 5 for Cower in fear, then Tentacle smash.
// returns 6 for Tentacle smash, then Cower in fear.
// returns 7 for Tentacle smash x2.
// returns 8 for Tentacle smash x3.
//
int actionstate_accessAct1MonsterAction ()
{
    char    cSprayGoo = 0;
    char    cRunaway = 0;
    char    cAttack = 0;
    int     iRndValue;

    // if the monster rage and confidence is rather high, return tentacle smash x3.
    if ((gstructActStateOpponent.iRage > 300) && (gstructActStateOpponent.iConfidence > 300))
    {
        iRndValue = (int)(rand() % 4);

        // 25% chance of using the goo spray and tentacle smash.
        if (iRndValue == 0)
            return 4;
        // verses going outright tentacle smash.
        else
            return 8;
    }

    // figure out if this monster is going to spray something.
    if (gstructActStateOpponent.iDesire > 40)
        cSprayGoo = 1;
    else if (gstructActStateOpponent.iDesire < 10)
        cSprayGoo = 0;
    else
    {
        iRndValue = (int)(rand() % 30);

        if (gstructActStateOpponent.iDesire > (iRndValue + 10))
            cSprayGoo = 1;
        else
            cSprayGoo = 0;
    }

    // the monster just just run away when the hit points are exceptionally low.
    if (gstructActStateOpponent.iHitPoints < 60)
    {
        if (cSprayGoo == 1)
            return 1;
        else
            return 0;
    }

    // figure out if this monster is going to runaway.
    if (gstructActStateOpponent.iFear > 40)
        cRunaway = 1;
    else if (gstructActStateOpponent.iFear < 10)
        cRunaway = 0;
    else
    {
        iRndValue = (int)(rand() % 30);

        if (gstructActStateOpponent.iFear > (iRndValue + 10))
            cRunaway = 1;
        else
            cRunaway = 0;
    }

    // figure out if this monster is going to attack.
    if (gstructActStateOpponent.iRage > 40)
        cAttack = 1;
    else if (gstructActStateOpponent.iRage < 10)
        cAttack = 0;
    else
    {
        iRndValue = (int)(rand() % 30);

        if (gstructActStateOpponent.iRage > (iRndValue + 10))
            cAttack = 1;
        else
            cAttack = 0;
    }

    // if this monster is running away..
    if (cRunaway == 1)
    {
        if (cSprayGoo == 1)
        {
            // too much fear, just runaway..
            if ((gstructActStateOpponent.iFear > 30) && (gstructActStateOpponent.iConfidence < 10))
                return 0;
            else
                return 1; // otherwise, spray goo then runaway.
        }

        if (cAttack == 1)
        {
            // too much fear, just runaway..
            if ((gstructActStateOpponent.iFear > 30) && (gstructActStateOpponent.iConfidence < 10))
                return 0;
            else
                return 2; // otherwise, attack then runaway.
        }

        if (gstructActStateOpponent.iConfidence > 20)
            return 3; // cower for a bit, then runaway

        return 0;
    }

    // if the monster has rather high confidence
    if ((gstructActStateOpponent.iConfidence > 20) && (gstructActStateOpponent.iDesire > 19))
    {
        // and attacking, then attack..
        if (cAttack == 1)
            return 7; // attack twice..
        else
            return 6; // attack once, then cower..
    }

    // if set to spray goo, then spray goo..
    if (cSprayGoo == 1)
        return 4;

    // to add in some randomness, 1 of 3 default drop through
    //  actions is going to be goo spray, then attack..
    iRndValue = (int)(rand() % 3);
    if (iRndValue == 0)
    {
        return 4;
    }

    // otherwise, cower, then attack..
    return 5;
}

//
// Function to workout what the monsters are going to do during Act3
//
// returns 0 for Just Runaway.
// returns 1 for Goo spray, then runaway.
// returns 2 for Quick violation of pussy.
// returns 3 for Quick violation of mouth.
// returns 4 for Quick violation of pussy and mouth.
// returns 5 for Long violation of pussy and mouth.
//
int actionstate_accessAct3MonsterAction (int iBackaway, int iFavorMouth, int iFavorPussy, int iCrystalPresence)
{
    int iCalcRage;
    int iCalcFear;
    int iCalcConfidence;
    int iCalcDesire;
    int iRndValue;
    char cAttack;

    // if the PC backs away, it is sort of indicating to the monster that they should escape
    // this provides the monster with only 2 options.
    if (iBackaway != 0)
    {
        char    cSprayGoo = 0;

        // figure out if this monster is going to spray something.
        if (gstructActStateOpponent.iFear > 40)
            cSprayGoo = 0;
        else if (gstructActStateOpponent.iFear < 10)
            cSprayGoo = 1;
        else
        {
            iRndValue = (int)(rand() % 30);

            if (gstructActStateOpponent.iFear < (iRndValue + 10))
                cSprayGoo = 1;
            else
                cSprayGoo = 0;
        }

        if (cSprayGoo == 1)
            return 1;
        else
            return 0;
    }

    // calculate the fear value.
    if (iCrystalPresence != 0)
        iCalcFear = gstructActStateOpponent.iFear / 2;
    else if (gstructActStateGlobal.sAct3Monsters > 4)
        iCalcFear = gstructActStateOpponent.iFear - (((int)gstructActStateGlobal.sAct3Monsters - 2) * 2);
    else
        iCalcFear = gstructActStateOpponent.iFear;

    // calculate the desire value
    if (iCrystalPresence != 0)
        iCalcDesire = gstructActStateOpponent.iDesire + (gstructActStateOpponent.iDesire / 2);
    else if (gstructActStateGlobal.sAct3Monsters > 3)
        iCalcDesire = gstructActStateOpponent.iDesire + ((int)gstructActStateGlobal.sAct3Monsters - 3);
    else
        iCalcDesire = gstructActStateOpponent.iDesire;

    // increase the desire value by what has been presented by the PC.
    iCalcDesire += iFavorMouth + (iFavorPussy * 2);

    // calculate the desire value
    if (iCrystalPresence != 0)
        iCalcConfidence = gstructActStateOpponent.iConfidence + (gstructActStateOpponent.iConfidence / 2);
    else if (gstructActStateGlobal.sAct3Monsters > 3)
        iCalcConfidence = gstructActStateOpponent.iConfidence + ((int)gstructActStateGlobal.sAct3Monsters - 3);
    else
        iCalcConfidence = gstructActStateOpponent.iConfidence;

    // increase the desire value by what has been presented by the PC.
    iCalcConfidence += (iFavorMouth * 2) + iFavorPussy;

    // calculate the rage value
    if (iCrystalPresence != 0)
        iCalcRage = gstructActStateOpponent.iRage / 2;
    else if (gstructActStateGlobal.sAct3Monsters > 3)
        iCalcRage = gstructActStateOpponent.iRage - ((int)gstructActStateGlobal.sAct3Monsters - 3);
    else
        iCalcRage = gstructActStateOpponent.iRage;

    // figure out if this monster is going for a long all out attack.
    cAttack = 0;

    if (iCalcRage > 40)
        cAttack = 1;
    else if ((iCalcConfidence > 35) && (iCalcDesire > 35))
        cAttack = 1;
    else if (iCalcRage < 10)
        cAttack = 0;
    else if ((iCalcConfidence > 10) && (iCalcDesire > 10))
    {
        iRndValue = (int)(rand() % 30);

        if (iCalcRage > (iRndValue + 10))
            cAttack = 1;
        else
            cAttack = 0;
    }

    if (cAttack == 1)
        return 5;

    // figure out if this monster is going to run away scared.
    if (iCalcFear >= 10)
    {
        char cEscape = 0;

        if (iCalcFear > 40)
            cEscape = 1;
        else
        {
            iRndValue = (int)(rand() % 30);

            if (iCalcFear > (iRndValue + 10))
                cEscape = 1;
            else
                cEscape = 0;
        }

        if (cEscape == 1)
            return 1;
    }

    // figure out if this monster is going for a short all out attack.
    cAttack = 0;

    if (iCalcDesire > 40)
        cAttack = 1;
    else if ((iCalcConfidence > 40) && (iCalcDesire > 20))
        cAttack = 1;
    else if (iCalcDesire < 10)
        cAttack = 0;
    else if (iCalcConfidence > 10)
    {
        iRndValue = (int)(rand() % 30);

        if (iCalcDesire > (iRndValue + 10))
            cAttack = 1;
        else
            cAttack = 0;
    }

    if (cAttack == 1)
        return 4;

    // otherwise, make this a rather simple encounter..
    if (iFavorMouth > iFavorPussy)
    {
        return 3;
    }
    else if (iFavorMouth < iFavorPussy)
    {
        return 2;
    }
    // cannot decide.. take the default of both..
    return 4;
}

//
// Function to workout what the monsters are going to do during Act4
//
// returns 0 for Quick violation of pussy.
// returns 1 for Quick violation of mouth.
// returns 2 for Quick violation of ass.
// returns 3 for Quick violation of pussy and mouth.
// returns 4 for Quick violation of pussy and ass.
// returns 5 for Quick violation of mouth and ass.
// returns 6 for Quick violation of pussy, ass and mouth.
// returns 7 for Long violation of pussy, ass and mouth.
//
int actionstate_accessAct4MonsterAction (int iTease, int iFavorMouth, int iFavorPussy, int iFavorAnus)
{
    int iCalcRage;
    int iCalcFear;
    int iCalcConfidence;
    int iCalcDesire;
    int iValue;
    int iGreatest;

    iCalcFear = gstructActStateOpponent.iFear - (int)(gstructActStateGlobal.sAct4Monsters / 2);
    iCalcRage = gstructActStateOpponent.iRage;
    iCalcConfidence = gstructActStateOpponent.iConfidence;
    iCalcDesire = gstructActStateOpponent.iDesire;
    if (iTease != 0)
    {
        iValue = (int)(rand() % 4);
        iCalcRage += iValue + 2;
        iCalcFear -= 2;
        iCalcConfidence += iValue;
        iCalcDesire += (iValue / 2);
    }
    else
    {
        if (gstructActStateGlobal.sAct4Monsters > 6)
            iCalcRage -= (gstructActStateGlobal.sAct4Monsters / 2);
        else
            iCalcRage -= 3;
    }
    iCalcDesire += iFavorMouth + iFavorPussy + iFavorAnus + (gstructActStateCharWilda.structL.iNum / 2);
    iCalcConfidence += (gstructActStateCharWilda.structL.iNum / 2);

    // now I am going to find which of the 4 values is the largest.
    iGreatest = 0;
    iValue = iCalcRage;

    if (iCalcFear > iValue)
    {
        iValue = iCalcFear;
        iGreatest = 1;
    }

    if (iCalcConfidence > iValue)
    {
        iValue = iCalcConfidence;
        iGreatest = 2;
    }

    if (iCalcDesire > iValue)
    {
        iValue = iCalcDesire;
        iGreatest = 3;
    }

    if (iGreatest == 0) // the winner is rage..
    {
        return 6; // go all out for a short while..
    }

    if (iGreatest == 3) // the winner is desire..
    {
        return 7; // go all out for a long while..
    }

    if (iGreatest == 1) // the winner is fear..
    {
        // the monster will limit themselves to just one thing.

        // first, find which specific value is above the rest..

        if ((iFavorMouth > iFavorPussy) && (iFavorMouth > iFavorAnus))
            return 1;

        if ((iFavorPussy > iFavorMouth) && (iFavorPussy > iFavorAnus))
            return 0;

        if ((iFavorAnus > iFavorMouth) && (iFavorAnus > iFavorPussy))
            return 2;

        // try looking for which option that the PC has not given precedence to

        if ((iFavorMouth < iFavorPussy) && (iFavorMouth < iFavorAnus))
        {
            // it is not the mouth, so we are choosing between pussy and anus.

            iValue = (int)(rand() % 2);
            if (iValue != 0)
                return 0;
            else
                return 2;
        }

        if ((iFavorPussy < iFavorMouth) && (iFavorPussy < iFavorAnus))
        {
            // it is not the pussy, so we are choosing between mouth and anus.

            iValue = (int)(rand() % 2);
            if (iValue != 0)
                return 1;
            else
                return 2;
        }

        if ((iFavorAnus < iFavorMouth) && (iFavorAnus < iFavorPussy))
        {
            // it is not the anus, so we are choosing between the mouth and pussy.

            iValue = (int)(rand() % 2);
            if (iValue != 0)
                return 0;
            else
                return 1;
        }

        // to have reached here, means that all 3 are effectively equal.
        iValue = (int)(rand() % 3);

        if (iValue == 0)
            return 0;
        else if (iValue == 1)
            return 1;
        else
            return 2;
    }

    // otherwise the winner is confidence.

    // the monster is going to attack 2 of 3 orifices at once.

    // first look for what the PC did not favor.

    if ((iFavorMouth < iFavorPussy) && (iFavorMouth < iFavorAnus))
    {
        // it is not the mouth, so it must be the pussy and anus.
        return 4;
    }

    if ((iFavorPussy < iFavorMouth) && (iFavorPussy < iFavorAnus))
    {
        // it is not the pussy, so it must be the mouth and anus.
        return 5;
    }

    if ((iFavorAnus < iFavorMouth) && (iFavorAnus < iFavorPussy))
    {
        // it is not the anus, so it must be the pussy and mouth.
        return 3;
    }

    // then look for what the PC favored above everything else..

    if ((iFavorMouth > iFavorPussy) && (iFavorMouth > iFavorAnus))
    {
        // mouth is the primary..

        iValue = (int)(rand() % 2);
        if (iValue != 0)
            return 3; // mouth and pussy
        else
            return 5; // mouth and anus
    }

    if ((iFavorPussy > iFavorMouth) && (iFavorPussy > iFavorAnus))
    {
        // pussy is the primary..

        iValue = (int)(rand() % 2);
        if (iValue != 0)
            return 3; // pussy and mouth
        else
            return 4; // pussy and anus
    }

    if ((iFavorAnus > iFavorMouth) && (iFavorAnus > iFavorPussy))
    {
        // anus is the primary..

        iValue = (int)(rand() % 2);
        if (iValue != 0)
            return 4; // anus and pussy
        else
            return 5; // anus and mouth
    }

    // to have reached here, means that all 3 are effectively equal.
    iValue = (int)(rand() % 3);

    if (iValue == 0)
        return 3;
    else if (iValue == 1)
        return 4;
    else
        return 5;
}


