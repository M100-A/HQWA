//
// gamelogic.h
//

//
// define for the maximum number of sub-recursions..
//
#define MAXGAMESCENENESTS 20
// this is used in the scene functions to figure out if the program is stuck in a potentially infinite scene link loop, and to bail out.


// definition for the scene list array
struct  main_scenelist
{
    int     iSceneId;                               // scene id
    int     (*vFunc)(int iSubSceneId, char cSubFlag); // call function.
};

// definition for the scene list array
struct  gamelogic02_eventscenes
{
    char    cSpecialSceneId;            // scene id
    int     (*vFunc)(char cSubFlag);    // call function.
};


//
// These ALL of the scene id functions (gamelogicxx.c).
//
// These need to be defined so that they can be referenced by the lookup array, without dumping EVERY single function into the one sourcecode listing.
//

// 00.c, menu elements
int gamelogic00_scene0000 (int iSubSceneId, char cSubFlag);
int gamelogic00_scene0001 (int iSubSceneId, char cSubFlag);
int gamelogic00_scene0002 (int iSubSceneId, char cSubFlag);
int gamelogic00_scene0003 (int iSubSceneId, char cSubFlag);
int gamelogic00_scene0004 (int iSubSceneId, char cSubFlag);
int gamelogic00_scene0009 (int iSubSceneId, char cSubFlag);

// 01.c, main dialog (main scenes)
int gamelogic01_scene1001 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1002 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1003 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1004 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1005 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1006 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1011 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1012 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1013 (int iSubSceneId, char cSubFlag);
int gamelogic01_scene1014 (int iSubSceneId, char cSubFlag);

// 01.c, main dialog continued (trigger events)
int gamelogic01_event_scene001 (char cSubFlag);
int gamelogic01_event_scene002 (char cSubFlag);
int gamelogic01_event_scene003 (char cSubFlag);
int gamelogic01_event_scene004 (char cSubFlag);
int gamelogic01_event_scene005 (char cSubFlag);
int gamelogic01_event_scene006 (char cSubFlag);
int gamelogic01_event_scene007 (char cSubFlag);
int gamelogic01_event_scene008 (char cSubFlag);
int gamelogic01_event_scene009 (char cSubFlag);
int gamelogic01_event_scene010 (char cSubFlag);
int gamelogic01_event_scene011 (char cSubFlag);
int gamelogic01_event_scene012 (char cSubFlag);
int gamelogic01_event_scene013 (char cSubFlag);
int gamelogic01_event_scene014 (char cSubFlag);
int gamelogic01_event_scene015 (char cSubFlag);
int gamelogic01_event_scene016 (char cSubFlag);
int gamelogic01_event_scene017 (char cSubFlag);
int gamelogic01_event_scene018 (char cSubFlag);
int gamelogic01_event_scene019 (char cSubFlag);
int gamelogic01_event_scene020 (char cSubFlag);
int gamelogic01_event_scene021 (char cSubFlag);
int gamelogic01_event_scene022 (char cSubFlag);
int gamelogic01_event_scene022a (char cSubFlag); // this one isn't in the lookup array.
int gamelogic01_event_scene023 (char cSubFlag);
int gamelogic01_event_scene024 (char cSubFlag);
int gamelogic01_event_scene025 (char cSubFlag);
int gamelogic01_event_scene026 (char cSubFlag);
int gamelogic01_event_scene027 (char cSubFlag);
int gamelogic01_event_scene028 (char cSubFlag);
int gamelogic01_event_scene029 (char cSubFlag);
int gamelogic01_event_scene030 (char cSubFlag);
int gamelogic01_event_scene031 (char cSubFlag);
int gamelogic01_event_scene050 (char cSubFlag);
int gamelogic01_event_scene051 (char cSubFlag);
int gamelogic01_event_scene052 (char cSubFlag);
int gamelogic01_event_scene053 (char cSubFlag);
int gamelogic01_event_scene054 (char cSubFlag);
int gamelogic01_event_scene055 (char cSubFlag);
int gamelogic01_event_scene056 (char cSubFlag);
int gamelogic01_event_scene061 (char cSubFlag);
int gamelogic01_event_scene062 (char cSubFlag);
int gamelogic01_event_scene063 (char cSubFlag);
int gamelogic01_event_scene064 (char cSubFlag);
int gamelogic01_event_scene065 (char cSubFlag);
int gamelogic01_event_scene066 (char cSubFlag);
int gamelogic01_event_scene067 (char cSubFlag);
int gamelogic01_event_scene068 (char cSubFlag);
int gamelogic01_event_scene069 (char cSubFlag);
int gamelogic01_event_scene071 (char cSubFlag);
int gamelogic01_event_scene072 (char cSubFlag);
int gamelogic01_event_scene073 (char cSubFlag);
int gamelogic01_event_scene074 (char cSubFlag);
int gamelogic01_event_scene075 (char cSubFlag);

// 02.c, movement/navigation
int gamelogic02_scene1020 (int iSubSceneId, char cSubFlag);
int gamelogic02_scene1021 (int iSubSceneId, char cSubFlag);
int gamelogic02_scene1022 (int iSubSceneId, char cSubFlag);

// 03.c, inventory/status
int gamelogic03_scene1030 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1031 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1032 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1033 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1034 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1035 (int iSubSceneId, char cSubFlag);
int gamelogic03_scene1036 (int iSubSceneId, char cSubFlag);

// 04.c, combat (broken up by acts 1, 2, 3 & 4)
int gamelogic04_scene1040 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1041 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1042 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1050 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1051 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1052 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1060 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1061 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1063 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1070 (int iSubSceneId, char cSubFlag);
int gamelogic04_scene1071 (int iSubSceneId, char cSubFlag);

