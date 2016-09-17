//
// actionstate.h
//
// Header file for action/state structures and definitions for HQWA.
//

//----------------------------------------------------------------------
//
// structure for a stat element..
//

struct  actionstate_stat
{
    int     iNum;                   // whole number.
    float   fFraction;              // fraction.
};

//----------------------------------------------------------------------
//
// structure for PC stats..
//

struct  actionstate_charstats
{
    struct  actionstate_stat structE;   // Endurance (HP max)
    struct  actionstate_stat structS;   // Stamina (HP current)
    struct  actionstate_stat structM;   // Might (Strength)
    struct  actionstate_stat structK;   // Karma (Luck/Fate)
    struct  actionstate_stat structF;   // Frigidity (Lust max)
    struct  actionstate_stat structL;   // Lust (Arousal)
    struct  actionstate_stat structR;   // Reflexes (Combat Experience)
    struct  actionstate_stat structO;   // Oral experience
    struct  actionstate_stat structV;   // Vaginal experience
    struct  actionstate_stat structA;   // Anal experience
    struct  actionstate_stat structW;   // Weapon effectiveness
    struct  actionstate_stat structG;   // Glove (Gauntlet) effectiveness
    struct  actionstate_stat structB;   // Boots (Shoes) effectiveness
    struct  actionstate_stat structC;   // Clothing (Armor) effectiveness
    short   sSlotW;                     // Weapon slot
    short   sSlotG;                     // Glove slot
    short   sSlotB;                     // Boots slot
    short   sSlotC;                     // Clothing slot
};

//----------------------------------------------------------------------
//
// structure for opponent stats..
//

struct  actionstate_opponentstats
{
    char    cActive;        // flag to indicate if these stats are active (combat situation)
    int     iRage;          // rage value.
    int     iFear;          // fear value (likelihood of running away).
    int     iConfidence;    // confidence value
    int     iDesire;        // desire (for sex) value.
    int     iHitPoints;     // hit points
};

//----------------------------------------------------------------------
//
// structure for inventory..
//

struct  actionstate_inventory
{
    short   sCount;                     // for some items, this is allowed to be greater than 1
    struct  actionstate_stat structEff; // effectiveness (of a single item only).
};

//----------------------------------------------------------------------
//
// structure for inventory descriptions..
//

struct  actionstate_invdescription
{
    char    cMultiFlag;                 // can be more than one.
    char    cEffectivenessFlag;         // can have an effectiveness value.
    char    *pszName;                   // name of this inventory entry
};

//----------------------------------------------------------------------
//
// structure for game global variables..
//

struct  actionstate_globalvars
{
    short   sMapId;                     // current map group
    short   sActId;                     // current act
            // Note: the parameters for Crystal are only active for Act3.
    short   sPosId;                     // position in map
    char    cDirect;                    // direction of last travel
    char    cStairUpDown;               // stair up/down flag
    char    cStairDirect;               // stair direction value
    char    cEnteredDungeon;            // flag to indicate that the dungeon has been entered
            // Note: this flag indicates if the map data has been initialized.
    short   sAct1Monsters;              // monster encounters (act 1)
    short   sAct2Monsters;              // monster encounters (act 2)
    short   sAct3Monsters;              // monster encounters (act 3)
    short   sAct4Monsters;              // monster encounters (act 4)
    char    cGingerEncounter;           // encounter with Ginger (act 4)

    char    caEncounterArray[51];       // the encounter array.
    char    caAct3UnlockArray[10];      // action unlock array for Act 3.
};

//
// These are the map data functions (actionstate.c).
//

int actionstate_initInventoryPlusVars ();

void actionstate_statAddition (struct actionstate_stat *pstructStat, float fValue, int iMax);

void actionstate_statSubtraction (struct actionstate_stat *pstructStat, float fValue, int iMin);

void actionstate_shiftEncounterArray ();

float actionstate_randomFloatValue (float fMax, float fMin, int iIncrement);

int actionstate_randomIntValue (int iMax, int iMin);

float actionstate_convertStatToFloat (struct actionstate_stat *pstructStat);

void actionstate_hardAlterMonsterValues (int iRage, int iFear, int iConfidence, int iDesire, int iHitPoints);

int actionstate_randomAct1AlterMonsterValues (char cAffectHP, float fValHP, float fValFear, float fValDesire, float fValConfidence, float fValRage);

int actionstate_accessAct1MonsterAction ();

int actionstate_accessAct3MonsterAction (int iBackaway, int iFavorMouth, int iFavorPussy, int iCrystalPresence);

int actionstate_accessAct4MonsterAction (int iTease, int iFavorMouth, int iFavorPussy, int iFavorAnus);

