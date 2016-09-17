//
// mapdata.h
//
// Header file for map data structures and definitions for HQWA.
//
// I made this separate so that the listings that need to access this structs/defs can,
// but it is not necessary to include this header in all of the C listings of the program
// (however, it is likely that it will be anyway).
//

//----------------------------------------------------------------------
//
// structure for static position data list..
//

struct  mapdata_posdatastatic
{
    short   sPosId;
    short   sPosIdNorth;
    short   sLinkIdNorth;
    short   sPosIdEast;
    short   sLinkIdEast;
    short   sPosIdSouth;
    short   sLinkIdSouth;
    short   sPosIdWest;
    short   sLinkIdWest;
    char    cPcentEnc;
    char    cSpecialId;
    short   sControlLinkId;
};

//----------------------------------------------------------------------
//
// structure for dynamic position data list..
//

struct  mapdata_posdatadynamic
{
    short   sVisitCount;
    char    cRand1;
    char    cRand2;
};

//----------------------------------------------------------------------
//
// structure for dynamic link data list..
//

struct  mapdata_linkdatadynamic
{
    short   sVisitCount;
    char    cStatus;
    char    cRand1;
    char    cRand2;
};

//----------------------------------------------------------------------
//
// structure for move results processing..
//

struct  mapdata_posmovevalues
{
    char    cAllowNorth;
    char    cAllowEast;
    char    cAllowSouth;
    char    cAllowWest;
    short   sLinkIdNorth;
    short   sLinkIdEast;
    short   sLinkIdSouth;
    short   sLinkIdWest;
    short   sVisitNorth;
    short   sVisitEast;
    short   sVisitSouth;
    short   sVisitWest;
};

//
// These are the map data functions (mapdata.c).
//

int mapdata_checkAllMapData ();
int mapdata_selectAndInitMapData (char *pszMapName);
void mapdata_seedRandomMapValues ();
int mapdata_workoutPosIdNavigation (int sPosId, struct mapdata_posmovevalues *pstructMapDataMove);
short mapdata_incrementPosUsage (short sPosId);
void mapdata_incrementLinkUsage (short sLinkId);
int mapdata_printLinkVisitValue (short sVisitVal);

