//
// gamelogic01.c
//
// This is group 1 of scene ids.
//
// Essentially, this is the all of the main story dialog of the game.
//
// I also put all of the "special scenes" (map atomic elements) in here as well.
//

#include "common.h"
#include "gamelogic.h"
#include "actionstate.h"
#include "mapdata.h"

// external linkage to the game variables.
extern  char    gcDebugFlag;

// linkage to the actionstate data.
extern  struct  actionstate_invdescription gstructInventoryDescription[];
extern  struct  actionstate_inventory *gpstructActStateInventory;
extern  short   gsActStateInventorySize;
extern  struct  actionstate_charstats gstructActStateCharWilda;
extern  struct  actionstate_charstats gstructActStateCharCrystal;
extern  struct  actionstate_opponentstats gstructActStateOpponent;
extern  struct  actionstate_globalvars gstructActStateGlobal;

// linkage to the mapdata.
extern  struct  mapdata_posdatastatic *gpstructMapPosStaticCurrent;
extern  struct  mapdata_posdatadynamic *gpstructMapPosDynamicCurrent;
extern  struct  mapdata_linkdatadynamic *gpstructMapLinkDynamicCurrent;
extern  short   gsMapLinkDynamicCurrentSize;

//
// Game Start function.
//
int gamelogic01_scene1001 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    short sOffset1;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // init the global vars.
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cEnteredDungeon = 0;
    gstructActStateGlobal.cGingerEncounter = 0;
    gstructActStateGlobal.sAct1Monsters = 0;
    gstructActStateGlobal.sAct2Monsters = 0;
    gstructActStateGlobal.sAct3Monsters = 0;
    gstructActStateGlobal.sAct4Monsters = 0;

    // temporarily set the map and act
    gstructActStateGlobal.sActId = 1;
    gstructActStateGlobal.sMapId = 1;
    gstructActStateGlobal.sPosId = 2; // this is the starting pos when entering the dungeon.

    // this is the init/reset of the encounter array
    for (sOffset1 = 0; sOffset1 < 50; sOffset1++)
    {
        if (sOffset1 % 3)
            gstructActStateGlobal.caEncounterArray[sOffset1] = 0;
        else
            gstructActStateGlobal.caEncounterArray[sOffset1] = 1;
    }

    // setup the unlock array for act 3
    gstructActStateGlobal.caAct3UnlockArray[0] = 1; // pull back
    gstructActStateGlobal.caAct3UnlockArray[1] = 0; // massage breasts
    gstructActStateGlobal.caAct3UnlockArray[2] = 0; // blow kiss
    gstructActStateGlobal.caAct3UnlockArray[3] = 0; // pinch clitoris
    gstructActStateGlobal.caAct3UnlockArray[4] = 0; // wiggle butt
    gstructActStateGlobal.caAct3UnlockArray[5] = 0; // finger pussy
    gstructActStateGlobal.caAct3UnlockArray[6] = 0; // kneel down
    gstructActStateGlobal.caAct3UnlockArray[7] = 1; // crystal help
    gstructActStateGlobal.caAct3UnlockArray[8] = 0;
    gstructActStateGlobal.caAct3UnlockArray[9] = 0;

    //
    // this is the init of the inventory.
    //

    // first reset everything to 0.
    for (sOffset1 = 0; (gsActStateInventorySize + 1) > sOffset1; sOffset1++)
    {
        gpstructActStateInventory[sOffset1].sCount = 0;
        gpstructActStateInventory[sOffset1].structEff.iNum = 0;
        gpstructActStateInventory[sOffset1].structEff.fFraction = (float)0;
    }

    // gold, Wilda starts with 57 gold of her own, and receives 400 gold from amber.
    gpstructActStateInventory[1].sCount = 457;

    // Wilda has 2 vials of stamina elixir already.
    gpstructActStateInventory[2].sCount = 2;

    // The leather backpack itself counts as an inventory item.
    gpstructActStateInventory[20].sCount = 1;

    // Wilda already has 3 torches in her inventory.
    gpstructActStateInventory[22].sCount = 3;

    // Wilda has a yo-yo in her inventory, which is a childhood keepsake.
    gpstructActStateInventory[24].sCount = 1;

    // Wilda has a Bivouac sack.
    gpstructActStateInventory[25].sCount = 1;

    // And the holy artifact from Amber.
    gpstructActStateInventory[26].sCount = 1;

    //
    // init the starting stats for Wilda
    //

    // Endurance (HP max)
    gstructActStateCharWilda.structE.iNum = 250;
    gstructActStateCharWilda.structE.fFraction = (float)0.292;

    // Stamina (HP current)
    gstructActStateCharWilda.structS.iNum = 248;
    gstructActStateCharWilda.structS.fFraction = (float)0.763;

    // Might (Strength)
    gstructActStateCharWilda.structM.iNum = 124;
    gstructActStateCharWilda.structM.fFraction = (float)0.126;

    // Karma (Luck/Fate)
    gstructActStateCharWilda.structK.iNum = 24;
    gstructActStateCharWilda.structK.fFraction = (float)0.311;

    // Frigidity (Lust max)
    gstructActStateCharWilda.structF.iNum = 231;
    gstructActStateCharWilda.structF.fFraction = (float)0.232;

    // Lust (Arousal)
    gstructActStateCharWilda.structL.iNum = 3;
    gstructActStateCharWilda.structL.fFraction = (float)0.129;

    // Reflexes (Combat Experience)
    gstructActStateCharWilda.structR.iNum = 102;
    gstructActStateCharWilda.structR.fFraction = (float)0.428;

    // Oral experience
    gstructActStateCharWilda.structO.iNum = 1;
    gstructActStateCharWilda.structO.fFraction = (float)0.172;

    // Vaginal experience
    gstructActStateCharWilda.structV.iNum = 11;
    gstructActStateCharWilda.structV.fFraction = (float)0.283;

    // Anal experience
    gstructActStateCharWilda.structA.iNum = 2;
    gstructActStateCharWilda.structA.fFraction = (float)0.428;

    // Weapon effectiveness: Iron double edged sword
    gstructActStateCharWilda.structW.iNum = 60;
    gstructActStateCharWilda.structW.fFraction = (float)0.509;
    gstructActStateCharWilda.sSlotW = 3;

    // Gauntlet/Gloves effectiveness: Iron demi-gauntlets with leather gloves
    gstructActStateCharWilda.structG.iNum = 33;
    gstructActStateCharWilda.structG.fFraction = (float)0.537;
    gstructActStateCharWilda.sSlotG = 17;

    // Boots/Shoes effectiveness: Iron capped leather combat boots
    gstructActStateCharWilda.structB.iNum = 29;
    gstructActStateCharWilda.structB.fFraction = (float)0.474;
    gstructActStateCharWilda.sSlotB = 13;

    // Clothing/Armor effectiveness: Leather boy cut sleeveless body suit with, with bronze plating
    gstructActStateCharWilda.structC.iNum = 24;
    gstructActStateCharWilda.structC.fFraction = (float)0.523;
    gstructActStateCharWilda.sSlotC = 6;

    iRet = mdialog_addToDialogWithSrchRep ("> Start new game\n\n#!00# is resting. She is inside her tiny shack on the outskirts of town. For a mercenary swordswoman, such as herself, an extended rest is a luxury. However, after the events of last night, #!00# is going to to be living this life of luxury a bit more often. The light bruising on her left lower leg is still causing her some slight discomfort, however that is nothing compared to what #!00# did to the 5 other guys.\n\nAfter a lack of real jobs from the mercenary guild, #!00# wasn\'t really interested in maintaining her membership. There is real work that pays rather well. But, her guild wasn\'t giving those good assignments to her. #!00# wanted out of the guild. To allow for her departure, the guild-leader wanted a payment and a favor. A \'sexual\' favor. One thing is for certain, the mercenary guild isn\'t going to be sending anymore work her way. The language that the guild-leader used after #!00#\'s right knee came in contact with his testicles was a clear indication. Her actions afterwards ensured that there would be no reprieve.\n\nAt least #!00# didn\'t use her sword and kept to bare fists. She did pay for the damage to tavern. However, the guild-leader\'s teeth were not part of that deal. There is the likelihood of revenge attacks, but that won\'t be for a day at least. The guild-leader\'s 4 companions are barely able to walk.\n\n#!00# is surprised... pleasantly surprised... when she hears footsteps outside of her shack. At her home, she does not have to hold back. #!00# grabs her sword and opens the door of the shack.\n\nThe first thing that she sees is a solitary cloaked figure approaching her home. #!00# assesses the that individual is carrying no weapons, long before she identifies that they are a woman.\n\nThe cloaked woman sees #!00# and continues walking towards the open door of #!00#\'s shack. When the woman reaches #!00#, she asks a question \"Have you considered Hedonism?\"\n\n\n[5 minutes later...]\n\n#!00# is surprised \"400, up front?\"\n\nThe cloaked nun, #!01#, nods her head \"yes, 20 percent in advance\"...\n\n#!01# hands a bag of gold to #!00#. #!00# counts it as quickly as she can. It looks like it is all there \"400 gold\"...\n\n#!00# cannot believe it, she was sent an actual REAL job by the stupid guild. If 400 is 20 percent... then, final payment is 1600... all for an item retrieval mission. Normally #!00# would check the job with the guild. However, they would normally want their commission for the job referral. After last night, it would be rather \'normal\' for them to assign the job to someone else and demand ALL of the pre-payment. Screw that.\n\n#!00# looks at #!01# \"Are you fine with the task commencing so late?\"\n\n#!01# replies \"It is our fault that we did not come earlier. Your guild gave us your name last week. It took time to acquire the fee\".\n\n#!00# is concerned. Clients who have problems in reserving gold for the pre-payment usually cannot make the final payment at the end of the job. She has been caught out by this before. However, #!00# is more than interested because the pre-payment for this mission alone is more than the total for most jobs that she has been recently working. Considering her situation, #!00# decides to take the risk.\n\nThere are two other things that are bothering #!00#. The first is that #!01#\'s expression is sort of a constant smile while staring straight ahead. While #!01# is a true believer in her religion, whatever it is, she is way too happy. Sometimes it is as if #!01# isn\'t looking at #!00# at all. The second is that while #!01# has been talking to #!00# the entire time, #!01# has been relentlessly rubbing her own clitoris through the fabric of her cloak.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("Ignore what Amber is doing (easy)", 1002, 1);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Glance at the Amber\'s crotch, while she is fingering herself (medium)", 1002, 2);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Ask Amber what is she doing (hard)", 1002, 3);
    if (iRet != 0) return iRet;

    return 0;
}

//
// Interact with Amber (selects the map group).
//
int gamelogic01_scene1002 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Ignore what #!01# is doing\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# decides to ignore the fact that #!01# is openly slicking herself, to concentrate the job, and not on the messenger. #!00# tries asking #!01# \"So... will you be able to provide\"...\n\nHowever, #!00# is interrupted by #!01#, who seems to be focusing on something else \"Mmmm... that\'s it my lord... fill me up... ravage me\"...\n\n#!00# is perplexed. #!01# seems to be talking to someone else... but it isn\'t clear as to whom #!01# is talking to. #!00# inquiries \"Are you... all right?\"\n\n#!01#, still in her temporary dream-trance, is concentrating on something else \"More... I am but a lowly slut who wants her cummies... My lord... Cock... YESSsss\"...\n\n#!01# moans loudly and her body shakes. #!00# briefly decides to look around to see if there is anyone else watching #!01#\'s lewd show. After finding no one else, #!00# looks at #!01#.\n\n#!01#\'s eyes are open and she is looking at #!00# again. #!01# says to #!00# \"Sorry, but you seem to be distracted\".\n\n#!00# thinks about it and decides to just ignore #!01#\'s little display \"My apologies... I was just thinking... I am going to need directions\"...\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 1;

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Glance at the #!01#\'s crotch, while she is fingering herself\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00#\'s gaze wonders down to #!01#\'s crotch for a little bit. #!00# then realizes that she is staring at #!01# pleasuring herself for too long, so she quickly looks up at #!01#\'s face.\n\n#!01# grins \"Where are you looking?. My cunny is... down there\"...\n\n#!00# is surprised by #!01#\'s statement \"Eh?\"..\n\n#!01# then licks her lips, closes her eyes, and continues stroking herself \"In the name of my lord... Cock... Bless us with your holy milk... Amen\".\n\n#!01# then moans and her body shakes. Yet, she still manages to remain standing. Before #!01# opens her eyes and looks at #!00#, #!00# glanced down at #!01#\'s crotch and notices the dampness spreading from where #!01#\'s hand is clearly still pinching her own clitoris through the fabric of her cloak.\n\n#!00# looks at #!01#\'s face again and #!01# opens her eyes. #!00# asks \"Are you... okay?\"\n\n#!01# looks at #!00#, with the same smile as before \"Your concerns are unwarranted... as I am but a lowly servant of my lord... Cock\"...\n\n#!00# does not have to even look at #!01#\'s right hand to know that #!01# is pleasuring herself again. #!00# briefly considers the fact that this is wasting time, and #!00# should be getting on with the job.\n\n#!00# asks #!01# \"Didn\'t you mention something about a map?\"\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 2;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Ask #!01# what is she doing\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# sighs and starts to ask \"What in the name of creation are you\"... but is interrupted by #!01#.\n\n#!01# blurts out \"My lord... Cock... I am but a lowly cumdump... Thank you for the sperm... Amen\".\n\n#!01# then moans and her body shakes. #!00# just stands there, dumbfounded, unsure about how to react to #!01#\'s last statement. Surprisingly, #!01# did not fall down.\n\n#!01# opens her eyes, tilts her head a little to the right and talks to #!00#, while still stroking herself \"Is everything okay?\"\n\n#!00# quickly glances down at #!01#\'s right hand, at the wetness around #!01#\'s crotch, then back at #!01#\'s face. #!00# responds \"Everything is fine... now... can we cover the details of where I am going?\"\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 3;

        break;

    }

    iRet = mdialog_addToDialogWithSrchRep ("\n[2 hours later...]\n\n#!00# received a map from #!01#, and an armband. #!00# is to equip the armband before entering the dungeon at the destination. The armband is made out of rubber, and is meant to indicate that #!00# is a \'sanctioned servant\', whatever that means. There are other nuns still at the site, in \'sanctuaries\', who will provide assistance to #!00#. That could be useful.\n\n#!01# also gave #!00# something she called a \'holy artifact\', which was inside small long box. #!00# took a look inside the box to see a black rubber dildo. It serves some important purpose for the mission, but #!01# could not tell #!00# what the importance is. #!00# asked if #!01# could confirm the artifact, but #!01# stated that only #!00# was allowed to look at the contents of the box.\n\n#!01# then departed from #!00#\'s shack, but not without stopping 3 times, to finger herself to a climax each time she paused. After watching #!01# cum her brains out and not fall over for the third time, #!00# decided to ignore #!01# and to start preparing for the job.\n\n#!00#\'s first stop is the local item store, as she is in need of some equipment upgrades. #!00# is standing outside the door of the shop. \n\nAs much as she would like to shop elsewhere, this is the best place for her to buy stuff. However, the guy who runs it, #!12#, is a bit too friendly with #!00#. As much as #!00# would like to go elsewhere, his wares are of genuine exceptional quality, while at a low price.\n\n#!00# sighs, takes a breath and opens the door of the shop. #!12# immediately calls out \"#!00#-baby... come in... come in\"...\n\n#!00# steps into the shop and closes the door behind her. She then turns to look at #!12# \"I am after\"...\n\n#!12# immediately grabs a steel-platemail under-bust corset off the wall behind him and shows it to #!00# \"What about this Eh?\"..\n\n#!00# takes just one glance at it \"HELL No\"...\n\n#!12# grins \"You cannot blame an old fart for wanting to have a bit of fun. At 2000 gold, I think this would be a bit too much. Besides, this is a special order, you can\'t have it\".\n\n#!00# sighs, as she cannot believe that someone would pay 2000 gold for such an impractical piece of armor.\n\n\n[10 minutes later...]\n\n#!00# raises an eyebrow \"Only the one pack of five?\"\n\n#!12# puts down the batch of \'stamina elixirs\' and tells #!00# \"There has been a recent run on these lately. Someone, that both of us know, bought the rest... Nice job on his face, by the way\".\n\n#!00# responds with a smile \"Oh, really\"...\n\n#!12# looks at the clothing items table \"So, which ones do you want?\"\n\n#!00# looks around the room and focuses on the swords on the wall \"Do you have something better than my iron-fang?\"\n\n#!12# responds \"Expecting to get into fight are we?.. it is not as if the guild is sending you anymore work\".\n\n#!00# just looks at #!12# and smiles. She has no intention of telling him that she just landed a good job.\n\n#!12# sighs \"Well... Ok... if you are not going to consider the Lolita leather babydoll, the Leather underbust corset, or the Kick-ass bronze high-heels, which I went through all of that effort to pick out for you, then I might as well show you a decent blade to consider\".\n\n#!00# sighs. #!12#\'s tastes sometimes lead to equipment that is horribly impractical.\n\n#!12# walks over to the bin of swords by the counter, searches through it, and pulls out a single sword and walks back to the counter with it. #!00# exclaims \"You kept it over there?\"\n\n#!12# responds \"If I left the decent stuff out on display, some thief will take a liking to it. What you see up there is ceremonial shit... for show only... no real value as actual weapons. Now this... this is the tempered steel version of your iron-fang\".\n\n#!00# inquires \"Don\'t you have any better?\"\n\n#!12# replies \"Not for your price range\".\n\n#!00# responds \"I didn\'t give an amount\".\n\n#!12# puts the sword on the counter and looks at #!00# \"You didn\'t have to. You rejected the steel-plate amour, saying it was too expensive. You are not going to be able to afford an Aredrite blade\".\n\n#!00# sighs and looks at the items on the table.\n\n");
    if (iRet != 0) return iRet;

    iRet = gamelogic01_scene1003 (0, cSubFlag + 1);
    return iRet;
}

//
// Setup/Continue the encounter with Popper (populate the menu).
//
int gamelogic01_scene1003 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorking[200];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gpstructActStateInventory[1].sCount < 1)
        sprintf (szWorking, "#!00# has no gold pieces.\n\n");
    else if (gpstructActStateInventory[1].sCount == 1)
        sprintf (szWorking, "#!00# currently has 1 gold piece.\n\n");
    else
        sprintf (szWorking, "#!00# currently has %d gold pieces.\n\n", (int)gpstructActStateInventory[1].sCount);

    iRet = mdialog_addToDialogWithSrchRep (szWorking);
    if (iRet != 0) return iRet;

    if ((gpstructActStateInventory[2].sCount == 2) && (gpstructActStateInventory[1].sCount >= 50))
    {
        iRet = mutils_addToCommandList ("Stamina elixr 5 pack for 50 gold", 1004, 1);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[4].sCount == 0) && (gpstructActStateInventory[1].sCount >= 300))
    {
        iRet = mutils_addToCommandList ("Steel double edged sword for 300 gold", 1004, 2);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[18].sCount == 0) && (gpstructActStateInventory[1].sCount >= 180))
    {
        iRet = mutils_addToCommandList ("Iron demi-gauntlets with chain-mail gloves for 180 gold", 1004, 3);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[14].sCount == 0) && (gpstructActStateInventory[1].sCount >= 150))
    {
        iRet = mutils_addToCommandList ("Leather combat boots, with protruding steel spikes for 150 gold", 1004, 4);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[7].sCount == 0) && (gpstructActStateInventory[1].sCount >= 170))
    {
        iRet = mutils_addToCommandList ("Leather thong leotard, with iron plating for 170 gold", 1004, 5);
        if (iRet != 0) return iRet;
    }
    if ((gpstructActStateInventory[8].sCount == 0) && (gpstructActStateInventory[1].sCount >= 220))
    {
        iRet = mutils_addToCommandList ("Chainmail bikini set for 220 gold", 1004, 6);
        if (iRet != 0) return iRet;
    }

    if (iSubSceneId == 0)
    {
        iRet = mutils_addToCommandList ("Not interested in anything", 1005, 1);
        if (iRet != 0) return iRet;
    }
    else
    {
        iRet = mutils_addToCommandList ("That is enough for today", 1005, 2);
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// This is the item purchase results.
//
int gamelogic01_scene1004 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Stamina elixr 5 pack for 50 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# glances at the pack of 5 \'stamina elixirs\', and then at #!12# \"I will take those\".\n\n#!12# grins, and responds \"The usual 50 gold for one pack of 5 quick orgasms\".\n\n#!00# sighs, and holds back from berating #!12# about calling them that. She knows what the side effects of the things are like. #!00# counts 50 gold pieces and gives them to #!12#. #!12# hands over the pack of 5 vials, which #!00# puts inside her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 50;
        gpstructActStateInventory[2].sCount += 5;

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Steel double edged sword for 300 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# carefully looks over the steel sword \"How much for the steel blade?\"\n\n#!12# replies \"300\".\n\n#!00# nods her head, picks up the sword and looks along either edge. It is a good weight.\n\n#!12# adds \"If you want to swing it around, I suggest you step outside\"...\n\n#!00# smiles at #!12# \"I\'ll take it\", then counts out 300 gold and hands it over to #!12#. #!12# quickly recounts the gold and nods his head. #!00# puts the sword into her backpack.\n\n#!12# adds \"I have another sword that I can stick into your sheath, if you have the time\".\n\n#!00# sighs, and responds \"Not today\".\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 300;
        gpstructActStateInventory[4].sCount = 1;
        gpstructActStateInventory[4].structEff.iNum = 127;
        gpstructActStateInventory[4].structEff.fFraction = (float)0.428;

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Iron demi-gauntlets with chain-mail gloves for 180 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# takes interest in the new demi-gauntlets. She picks up the left one with her right hand, and compares it to her existing leather demi-gauntlet on her left hand.\n\n#!12# looks at #!00# \"I can get those with satin instead of leather or chain... Just say the word... I can get it done\".\n\n#!00# looks at #!12# with a raised eyebrow \"Satin?\"\n\n#!12# responds \"Sure... And if you model them for me, I will give them to you for the same 180 as those chain ones\".\n\n#!00# frowns \"Satin won\'t offer much protection will it!\"\n\n#!12# replies \"Heh... it isn\'t about protection... it is about being SEXY... Especially when it is all you are wearing\"...\n\n#!00# takes a deep breath, and counts out 180 gold pieces \"I will just have these ones today\".\n\n#!12# adds \"Meaning you are interested in the satin ones then?\"\n\n#!00# replies \"No\", then hands over the 180 gold pieces.\n\n#!12# recounts the 180 gold pieces while #!00# puts the pair of new demi-gauntlets into her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 180;
        gpstructActStateInventory[18].sCount = 1;
        gpstructActStateInventory[18].structEff.iNum = 80;
        gpstructActStateInventory[18].structEff.fFraction = (float)0.852;

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Leather combat boots, with protruding steel spikes for 150 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# looks at the new pair of leather combat boots \"You said 150 gold for these, right?\"\n\n#!12# responds \"Yes... Here is a thought\", #!00# looks at #!12# while he continues \"Those heels are awfully low, so I was thinking\"...\n\n#!00# interjects \"I will take them as they are\", and starts counting 150 gold pieces.\n\n#!00# hands the gold to #!12#. #!12# recounts the gold, then mutters \"Spoilsport\".\n\n#!00# puts the pair of new leather boots into her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 150;
        gpstructActStateInventory[14].sCount = 1;
        gpstructActStateInventory[14].structEff.iNum = 78;
        gpstructActStateInventory[14].structEff.fFraction = (float)0.216;

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Buy Leather thong leotard, with iron plating for 170 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# looks at the leather leotard with the iron plating \"Didn\'t you say 170 for this?\"\n\n#!12# shakes his head \"Really... If you wanted leather, you should have gone with the babydoll, or at least the corset\".\n\n#!00# looks at #!12# \"Neither of those have actual plating on them\".\n\n#!12# responds \"I could have the plating added\".\n\n#!00# replies \"Neither of them cover me up properly\".\n\n#!12# continues \"That is the best part about both of them... You know\"...\n\n#!00# sighs, and starts counting the 170 gold pieces. #!00# looks at #!12# and hands over the gold.\n\n#!12# recounts the gold, and nods his head \"Okay, but seriously, I could get it done\"...\n\n#!00# responds \"Don\'t bother\", puts the iron plated leather outfit inside her backpack, and adds \"This will do\"...\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 170;
        gpstructActStateInventory[7].sCount = 1;
        gpstructActStateInventory[7].structEff.iNum = 65;
        gpstructActStateInventory[7].structEff.fFraction = (float)0.126;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Buy Chainmail bikini set for 220 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!00# looks at the chainmail bikini, and sighs.\n\n#!12# glances at the bikini and looks at #!00# \"Oh yes... you have class, there are many benefits to this outfit... and many possibilities... with a few alterations\"...\n\n#!00# interjects \"How much?\"\n\n#!12# continues \"I could make the top a peak-a-boo... and the bottom\".\n\n#!00# interjects again \"Give me a price... for it as it is\".\n\n#!12# sighs \"220\".\n\n#!00# looks over the chainmail outfit again \"220... sold\", and starts counting gold pieces. #!00# hands the gold over to #!12# who recounts it.\n\n#!12# nods his head \"Done\"... #!00# puts the chainmail outfit into her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 220;
        gpstructActStateInventory[8].sCount = 1;
        gpstructActStateInventory[8].structEff.iNum = 108;
        gpstructActStateInventory[8].structEff.fFraction = (float)0.344;

        break;
    }

    // pass back control to the setup function (above) to repopulate the menu.
    iRet = gamelogic01_scene1003 (1, cSubFlag + 1);
    return iRet;
}

//
// This is the exit from the item shop, and all of the events leading up to the first entrance into the dungeon
//
int gamelogic01_scene1005 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (iSubSceneId)
    {
    case 1:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">Not interested in anything\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mdialog_addToDialogWithSrchRep ("#!12# sighs and looks at #!00# \"Really, you don\'t want to buy anything?.. You are such a tease\".\n\n#!00# briefly smirks, then walks out of the item shop.\n\n");
        if (iRet != 0) return iRet;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mdialog_addToDialogWithSrchRep (">That is enough for today\n\n");
            if (iRet != 0) return iRet;
        }

        if (gpstructActStateInventory[1].sCount == 407)
        {
            iRet = mdialog_addToDialogWithSrchRep ("#!12# looks at #!00# \"Thank you for your patronage\".\n\n#!00# walks out of the item shop.\n\n");
            if (iRet != 0) return iRet;
        }
        else
        {
            iRet = mdialog_addToDialogWithSrchRep ("#!12# looks at #!00# \"Thank you, now if you would not mind stripping down to your birthday suit, you can reequip with your purchase\".\n\n#!00# does not even bother looking at #!12#, and starts to walk out of the item store \"In your dreams\"...\n\n#!12# responds \"Thank you for the mental images that I will jerk off to tonight, and take care... It\'s a rough world out there\".\n\n");
            if (iRet != 0) return iRet;
        }

        break;
    }

    iRet = mdialog_addToDialogWithSrchRep ("\n[That evening...]\n\n#!00# decided to stay at home and rest after visiting the item shop, and prepare for the job. During the that evening, the guild-leader and another two of his lackeys dropped by to visit. #!00# beat the 3 of them up. #!00# was nice enough to give the guild-leader his teeth back, which he gratefully swallowed while #!00# had him in a choke-hold. She let his 2 friends carry his limp body off afterwards.\n\n\n[The next day...]\n\nIn the morning #!00# left her shack, knowing that it would most likely be ransacked by the time that she returns. Oh well, it is about time that she moved. #!00# spent the entire day traveling to the village next to her final destination. She stayed overnight in an inn for 3 gold pieces.\n\n\n[The following day...]\n\nShe arrived at her destination the middle of the next day, checked out the entrance to the temple in the afternoon. #!00# decided to find an inn for an overnight rest before starting the job the next morning. She stayed overnight in an inn for 2 gold pieces.\n\n\n[The following morning...]\n\n#!00# woke up in her room in the inn. #!00# decides it would be better to re-equip at the inn, rather than in the dungeon.\n\n");
    if (iRet != 0) return iRet;

    // make sure that we have set the flag that we have not entered the dungeon to return back here.
    gstructActStateGlobal.cEnteredDungeon = 0;

    // decrement the gold by 5 (but only if there are 5).
    for (iRet = 0; iRet < 5; iRet++)
    {
        if (gpstructActStateInventory[1].sCount < 1)
            break;

        gpstructActStateInventory[1].sCount--;
    }
    // Note: there might be a difference between what is happening here and the dialog. But that is
    //  relatively unimportant in the overall scheme of things. If anyone reads this comment,
    //  Wilda might have done "something illegal" to get the extra gold to stay at the inn for
    //  the two nights. There, the potential plot hole is fixed... moving along...

    // pass control over to inventory setup
    iRet = gamelogic03_scene1030 (0, cSubFlag + 1);
    return iRet;
}

//
// This is the start of Act 1
//
int gamelogic01_scene1006 (int iSubSceneId, char cSubFlag)
{
    int iRet;
    char szWorkString[20];

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("\n[30 minutes later...]\n\n#!00# returned back to the destroyed temple. Confirmed the map details again. The map is specific, clearly showing the entrance to the temple. #!00# finds it intriguing that the entrance to the temple is so far away from the actual temple itself, but she has seen stranger hiding spots for treasure room entrances. Her hired goal isn\'t what is inside the temple, but its treasure room anyway.\n\n#!00# isn\'t here to pray. It is not as if the monsters who destroyed this place were either. #!00# looks inside the dark entrance. No light. #!00# came prepared for that. She extracts a torch from her backpack and lights it.\n\n#!00# then casually walks into the entrance of the dungeon. There is a strange smell in the air, but all dungeons smell musky.\n\n\n[1 minute later...]\n\nStairs. Going down. The smell is stronger.\n\n\n[1 minute later...]\n\nAt the bottom of the stairs. Not only is the air RANCID, but this place has some kind of water seepage problem. At the end of the stairs, #!00# is standing ankle deep in what appears to be some kind of white opaque liquid. The stairs end at a corner. #!00# turns right and sees a corridor in front of her.\n\n\n[1 minute later...]\n\nAt the end of the corridor, left...\n\n\n[30 seconds later...]\n\nAt the end of a shorter corridor, right...\n\nThe liquid is starting to get higher, as the corridor is sloping downwards.\n\n\n[2 minutes later...]\n\n#!00# is approaching what appears to be a T-intersection.\n\n#!00# is walking slower now, because she up to her knees in this white opaque liquid. It isn\'t slowing her down too much, but #!00# does have concerns if she has to start swimming in it. It would not be the first time that #!00# has had to turn back from completing a job because the route to the treasure room was completely flooded.\n\nThe air is moist and drops of liquid are occasionally dripping from the ceiling.\n\n#!00# continues walking to the center of the T-intersection when she feels something crunch under her foot.\n\n#!00# does not have time to find the \'crunch\' strange when she hears stone grinding against stone, back along the corridor \"What was that?\"..\n\n#!00# rushes back along the corridor.\n\n\n[1 minute later...]\n\n\"Drat\"...\n\n#!00# is staring at a stone slab, which has sealed off the corridor leading out of the dungeon.\n\n\"They had to make it difficult\"...\n\nIt has become obvious that #!00# triggered a submerged switch of some kind back at the T-intersection. #!00# has experienced dungeons with pressure traps in the floors before, and other dungeons that were flooded. It never occurred to #!00# that she would ever come across a flooded dungeon where the floor traps were still active. After all, one of the easiest methods to defeat a floor trap is to flood the dungeon.\n\n#!00# sighs, and trudges through the white liquid back towards the T-intersection.\n\n\n[2 minutes later...]\n\n#!00# arrives back at the T-intersection. She uses her field compass, which is attached with a chain around her neck, and orients herself.\n\n");
    if (iRet != 0) return iRet;

    // we are definitely act 1
    gstructActStateGlobal.sActId = 1;
    gstructActStateGlobal.sAct1Monsters = 0;

    // PosId 2 is the start.
    gstructActStateGlobal.sPosId = 2;

    // init the map
    sprintf (szWorkString, "Map%dAct%d", gstructActStateGlobal.sMapId, gstructActStateGlobal.sActId);

    // now init (and allocate) the map data.
    iRet = mapdata_selectAndInitMapData (szWorkString);
    if (iRet != 0) return 1;

    // seed random data in the map values.
    mapdata_seedRandomMapValues ();

    // this is the specific setup according to the act and map selected.

    // set the direction to unknown.. let the navigation code do the rest.
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;

    // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
    gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2
    gpstructMapPosDynamicCurrent[2].sVisitCount = 2; // PosId 3
    gpstructMapLinkDynamicCurrent[1].sVisitCount = 3; // LinkId 2 (between PosIds 2 & 3)

    // NOW we have entered the dungeon.
    gstructActStateGlobal.cEnteredDungeon = 1;

    // this is the increase of the lust value
    actionstate_statAddition (&gstructActStateCharWilda.structL, (float)3.45, (int)(gstructActStateCharWilda.structF.iNum + 3));

    // this is the decrease of the stamina value
    actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)6.634, (int)0);

    // remove a torch from the backpack, as Wilda is now holding 1 of them.
    gpstructActStateInventory[22].sCount--;

    // pass control over to the navigation setup
    iRet = gamelogic02_scene1020 (0, cSubFlag + 1);
    return iRet;
}

//
// This is the bad ending dialog
//
int gamelogic01_scene1011 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("\n[?? years later...]\n\nA naked pile of human female flesh wakes up in a clearing. For the first time in many years she is able to use her eyes. She looks around, unfamiliar with her surroundings. She vaguely remember the thing called \'the sun\', but her past memories are very distant.\n\nFor as long as she can remember, she has had every orifice of her body violated by tentacles, and now, every single orifice of her body is prolapsed. She is a spent vessel, released from her long servitude now that she has outlived the usefulness of her own womb.\n\nSomehow, the mind broken figure of the warrior who was once known as #!00#, staggers to her feet and starts slowly walking towards a nearby village.\n\n\nIt will not be long before she dies at the hands of other, terrified, humans.\n\n(bad) END.\n\n");
    if (iRet != 0) return iRet;

#ifdef INTERFACE_CURSES
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
#else
    return 0;
#endif // INTERFACE_CURSES
}

//
// This is the good ending #1 dialog
//
int gamelogic01_scene1012 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("\n[2 years later...]\n\n#!08# is resting inside her tiny shack on the outskirts of town. While she is a mercenary swordswoman, decent jobs have not been as frequent as she hoped recently. It does not help that the mercenary guild is run by a bunch of jerks who really seem to have a thing against female mercs.\n\nEspecially the guild-leader. #!08#\'s nickname for him is \'Gummy\'. That asshole is constantly saying that he will give #!08# a preference if she sucked his cock. Someone should just beat that pile of shit up and teach him a lesson.\n\nWhile #!08# is pondering wanton bodily harm to the guild-leader, there is a knock on the door of her shack. Distracted from the idea of breaking both of the guild-leader\'s arms, #!08# stands up and opens the door of her shack.\n\nThe first thing that she sees is a nun wearing a cloak.\n\n\n#!00# asks #!08# \"Have you considered Hedonism?\"\n\nEND.\n\n");
    if (iRet != 0) return iRet;

#ifdef INTERFACE_CURSES
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
#else
    return 0;
#endif // INTERFACE_CURSES
}

//
// This is the good ending #2 dialog
//
int gamelogic01_scene1013 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("\n[1 year later...]\n\n#!00# and #!04# have just finished praying in the entrance of one of the sanctuaries. For #!04#, this is the end of a 8 day long prayer session.\n\n#!04# turns to her junior and asks \"Sister #!00#, did anything of note happen while I was praying to our lord and master?\"\n\n#!00# nods \"Yes, Sister #!04#. We have a \'sanctioned servant\' resting inside the room of the \'holy mist\'. Her name is #!09#\".\n\n#!04# replies \"Oh... Is this the one that Sister #!10# took in?\"\n\n#!00# nods \"Yes, Sister #!04#, she is\".\n\n#!04# responds \"Our lord and master will be most pleased. We must continue her indoctrination. Prepare the \'holy juices\' and the butt-plug. I will personally teach her the joys of being an obedient cumdump\".\n\n#!00# replies \"Yes, Sister #!04#. I will prepare those items right away\".\n\nAs #!00# saunters off, #!04# watches the junior nun\'s swaying butt. #!00# is turning into a fine nun of the order.\n\n#!04# then lightly massages her swollen belly. It will be about a month before the young master in #!04#\'s belly is born. After that happens she will accompany this latest \'sanctioned servant\' to the next sanctuary, and ensure that #!09#\'s guidance as a holy sex slave is fulfilled.\n\n#!04# remembers with joy the times that she was shown by her senior, #!03#, how to educate \'sanctioned servants\'.\n\n\nAnd now... educating \'sanctioned servants\' is #!04#\'s task.\n\nEND.\n\n");
    if (iRet != 0) return iRet;

#ifdef INTERFACE_CURSES
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
#else
    return 0;
#endif // INTERFACE_CURSES
}

//
// This is the good ending #3 dialog
//
int gamelogic01_scene1014 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("\n[2 months later...]\n\n#!11# is a junior nun of \'the order of the holy fuckslave\'. She has been given an important task. #!11# masturbates in anticipation as she carefully approaches the entrance to the holiest of holy places, the royal chamber of her lord and master.\n\nWith great reverence, she climbs the steps out of the holy water, and reaches the chamber door. There is a lantern hanging next to the chamber door, the light of the lantern is a hindrance rather than helpful. This is the first time that she has undertaken this task. She must not mess it up.\n\nShe looks down at her swollen belly. The young lord and master within will protect and guide her.\n\nShe takes a small latex backpack off of her back, and reaches inside. Her latex gloved hand finds a small rectangular box, and she retrieves it from the backpack. #!11#\'s heart is pounding.\n\n#!11# puts the backpack back on, while trying not to look at the box. It contains a \'holy artifact\'. It is made in the image of her lord and master, so she dares not look directly upon it.\n\nShe looks away, opens the box, and pulls the \'holy artifact\' out. #!11#\'s breathing intensifies. It feels as if it is throbbing. It feels as if it is alive. Without thinking about it she licks the tip of the \'holy artifact\'.\n\nThe smell... or lack of it... brings her back to her senses. There is no sacred pre-cum. The \'holy artifact\' is merely a hunk of rubber fashioned in the form of her lord and master... but it is not her lord and master.\n\n#!11# looks at the hole in the door of the entrance, then away into the distance. She uses her hands to find the hole, line up the \'holy artifact\' and inserts it into the hole.\n\nThere is a large audible click, followed by the sound of stone grinding against stone. The passageway is filled with a pink colored light.\n\n#!11# is scared, she turns to look inside the chamber. #!00# greets #!11# \"Hello\"...\n\n#!11# is almost scared out of her skin, and starts to fall backwards. #!00# quickly reaches through the door and grabs #!11#\'s right arm. #!00# tells #!11# \"Careful, you might harm our lord and master\"...\n\n#!00# helps #!11# to stand on her own feet. #!11# lightly bows to #!00# \"Sorry about that, Sister\"...\n\n#!00# replies \"Don\'t be, your rank is higher than mine\"...\n\n#!11# looks at #!00# \"Eh... What?\"\n\nA tentacle monster appears next to #!00#\'s side. #!00# sighs \"You are my replacement, you know... I am #!00#\"...\n\n#!11# replies with a light laugh \"I am #!11#... well we had better swap before the master in your belly hatches\"...\n\n#!11# walks in through the door, and #!00# walks out of the door. From behind her, #!11# can hear #!00# say something as the stone door starts closing. It sounded like \"I hope we meet again some day\", but #!11# is currently oblivious to what her fellow sister said, or anything else.\n\n#!11#\'s focus is on what is in front of her. There are 3 of her masters, and many more off in the distance. #!11# is delirious with the thought that she is going to be fucked by all of them, multiple times.\n\n\nFor now, it would not matter if no one comes back to replace her, #!11# would happily die here in the presence of her lord and master, Cock.\n\nEND.\n\n");

    if (iRet != 0) return iRet;

#ifdef INTERFACE_CURSES
    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
#else
    return 0;
#endif // INTERFACE_CURSES
}

//
// act 1 end (Act 1 -> Act 2 transition)
//
int gamelogic01_event_scene001 (char cSubFlag)
{
    int iRet;
    char szWorkString[20];
    short sOffset1;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# continues walking along the corridor following the flow of liquid. The current in the liquid is rather obvious now. #!00# keeps walking till she reaches what appears to be a dead end. But it isn\'t a dead end for the liquid.\n\nThere appears to be a small whirlpool that has formed in the center of the floor, and the liquid is flowing towards it, primarily from the corridor.\n\n#!00# looks around the walls to see if there is any evidence of a door, or something like that. There are no depressions in the walls. #!00# sighs and walks towards the whirlpool \"It does not look like I can\"...\n\nSuddenly there is a loud \'cracking\' sound \"What the\"...\n\nBefore #!00# can react, she finds herself almost floating as part of the floor around the whirlpool drops away... with #!00# still standing on that part of the floor.\n\n#!00#\'s feet lift up off the floor, only to slam back into it 4 seconds later. The part of the floor that had given way had already started to break up before it fell onto the pool of liquid directly below. The sudden impact caused the pieces of the floor to disintegrate even further.\n\n#!00# wasn\'t able to remain standing, because a large body of liquid had followed her descent from the corridor above. A waterfall of white is bearing down on her.\n\n#!00# is forced under the surface of the liquid pool below, by the torrent liquid from above. It took her 10 seconds to swim back to the surface of the liquid. #!00# finds that she is rather buoyant in the liquid. However, to her horror, #!00# quickly discovered the reason that she swim so effectively is because both her backpack and her sword had detached during, or immediately after, her fall. Neither of them float, and both are now completely submerged.\n\nThe torch #!00# was holding was also lost during the decent. When #!00# surfaced and looked around, she was surprised by what she could see... more specifically, because she could see...\n\n\"Where is the light coming from?\"\n\nIt took a few seconds for #!00# to realize that the light was emanating from aquamarine spherical appendages that are attached to the ceiling of the chamber that she landed in. The entire chamber is bathed in an aquamarine light.\n\n\"While that is helpful... I need my stuff\"...\n\n\n[15 minutes later...]\n\n#!00# sighs \"This has been a fucking disaster\"...\n\nDespite the light above, it did nothing to penetrate anymore than one inch into the liquid. While swimming in it, the liquid quickly turned from aquamarine to pitch black.\n\n#!00# tried blindly searching underneath the liquid, only to find that it wasn\'t working out so well. #!00#\'s apparent buoyancy was working against her, making it difficult for her to actually reach much of a depth beneath the surface, let alone to stay underneath to search with her hands.\n\nWhile the depth of the liquid pool saved #!00# from both death and serious injury, it has resulted in her losing almost everything she had. Her armor is also in a bad state.\n\n#!00# crawls up on the one of the few places in the cavern where there is dry ground. #!00# is tired, but her bivouac sack was attached to her backpack. But that wasn\'t all that was in her backpack. All of the gold that #!00# had on her, including her pre-payment for this job, was in her backpack. #!00# looks down into the pool of opaque liquid \"When I complete this job\"...\n\n#!00#\'s monologue is interrupted by someone calling out to her \"Have you considered Hedonism?\"\n\n#!00# focuses more on who was calling out, and not what they were asking. #!00# looks around the cavern \"Where?\"\n\nThe voice calls out to #!00# \"Over here. We should leave this place... it isn\'t safe here\".\n\n#!00# sees a nun holding up some form of lantern. The lantern is emitting an aquamarine light. #!00# looks around and notices that she is going to have to swim to reach the nun \"Can you stay there?.. I will come to you\"...\n\n\n[15 minutes later...]\n\nThe nun\'s name is #!02#. #!00# comes to the conclusion that #!02# is of the same religion as #!01#, given that she is constantly smiling, her her focus is mostly somewhere else, and she is also regularly pleasuring herself. #!02# is also heavily pregnant. Like #!01#, #!02# is also wearing a cloak, but there is something different about the black cloak that #!02# is wearing.\n\n#!00# helped #!02# put the locking bar in place across the heavy metal the door of the small shelter. #!02# called the shelter a \'sanctuary\'. After closing the door, #!00# glanced at #!02#\'s swollen belly. #!00# decides it would not be polite to comment.\n\n#!02# notices #!00# looking at her belly, so #!02# rubs her belly through her cloak and states \"This is a holy gift from our lord and master... Cock\"...\n\n#!00# looks at the lantern that #!02# was holding, then notices that there is another sitting on a shelf by the wall. #!00# was about to ask how they work.\n\n#!02#\'s focus is elsewhere \"I am but an obedient vessel for holding the holy semen... a breeding sack for my lord\'s sacred spawn... More... Violate me more... Lord... Cock... Yes... More\"...\n\nMeanwhile, #!02# is violently fingering her clitoris, while also playing with her nipples through her cloak. #!00# decides that it would not be wise to interrupt... whatever it is... that #!02# is doing.\n\n\n[4 minutes later...]\n\n#!02# fingered herself to a climax no less than 12 times, while in a trance state. The floor immediately beneath #!02# is covered with a combination of what appears to be sweat, pussy juices and breast milk. There are no wet spots on the outside of #!02#\'s cloak, because the entire garment is made out of black latex rubber.\n\nThe entire time, #!00# stood next to #!02#, worried that she was going to pass out and fall down. Somehow, #!02# remained standing despite the fact that her body was wracked by a series of orgasms. After recovering from her last climax, #!02# continued to finger herself, but seemed to notice that #!00# was there.\n\n#!02# looks at #!00# and asks \"Is... everything okay?... You seem to be distracted\"...\n\n#!00# considers making a witty remark, but decides now is not the best time \"I am fine... thank you\"...\n\n#!02# shakes her head and points at #!00#, more specifically the armband on #!00#\'s left arm \"You bear the sigil. It is I who should be thanking you\"...\n\n#!00# remembers that she put on the armband that #!01# gave her. But there was nothing special about the armband. It is just black rubber. #!00# takes a look at the armband again \"What the\"...\n\nThe armband is still black rubber, but now there is some form of symbol showing through the rubber. #!00# looks at #!02# \"It was pure black when I originally received it... and when I put it on later... is this what #!01# meant when she said \'sanctioned servant\'?\"\n\n#!02# looks over #!00#, then looks at #!00#\'s face \"Were you sent here on a quest?\"\n\n#!00# replies \"I was paid to do a job\".\n\n#!02# responds \"Then I am to assist you. I have a bed and items for you to select from\".\n\n#!00# is concerned \"Sorry... All of the gold that I had was in my luggage... So\"...\n\n#!02# interjects \"Payment won\'t be necessary... This is all in the service of our lord and master... Cock... Yes... I am thy faithful fucktoy... An onahole for your service\"...\n\nAs #!02# continues to jill herself off, #!00# thinks to herself that this is the last time she is going to mention anything that is going to remotely suggest the nun\'s servitude.\n\n\n[10 minutes and 29 orgasms later...]\n\n#!02#\'s grasp of reality finally included #!00# again, so #!02# showed #!00# the supplies that #!00# could choose from.\n\n#!02# states \"You can take any and all, but there is only one of each\".\n\n\n[30 minutes later...]\n\n#!00# received from #!02#... a small backpack made out of black latex rubber... a pair of black latex thigh high stockings... a pair of dim-gray rubber shoes that #!02# called \'Crocs\'... a black latex/rubber under-bust corset... and a spanking paddle as an improvised weapon.\n\n#!00# isn\'t complaining, as everything is free. There were other things as well, but #!00# decided that she had no need for the \'deluxe breast milking harness\', whatever that is, or the mouth-ring gag.\n\nAfter picking out the items from the inventory, #!00# reequips herself. #!00#\'s found that her armor started to really fall apart. #!00# decided to not bother with her broken armor and use what she acquired from #!02# instead.\n\n#!02# then showed #!00# to a small room with a single bed. #!00# noted that the room only had one bed, so she asked #!02# was it okay to hog the bed to herself. #!02# replied that she has a comfy chair to sleep in, lightly bows and shuffles away with the lantern.\n\nAs #!02# just wondered off with source of light, #!00# had to grope around in the darkness for the bed, then laid down and went to sleep.\n\n\n[?? amount of time later...]\n\n#!00# wakes up. She is feeling rather refreshed. It takes a while for #!00# to remember where she is. She looks around the room. There is a low level of light from somewhere. #!00# stumbles out of the small bed and walks slowly to the door. Outside the door is one of the aquamarine lanterns. #!00# looks at it \"#!02# must\"...\n\nThen #!00# noticed that next to the lantern was a folded up garment. #!00# walks over and picks up both the lantern and the garment up off the floor. The garment is made of black latex rubber.\n\n#!00# carries the lantern and the garment into the main room of the sanctuary, wondering where #!02# is. #!02# is nowhere to be seen. There is no sign of the other lantern either.\n\n#!00# decides to checkout the garment, so she unfolds it. It is a black latex cloak. #!00# turns it inside out, and notices that there is breast milk residue where the nipples would have been, and more residue near were someone's pussy would have been. This cloak must have been #!02#\'s.\n\n#!00# swings around. That is when she noticed that the locking bar is no longer across the door. The locking bar is leaning against the wall next to the door.\n\n\"Shit\"...\n\n#!00# opens the door and looks outside of the sanctuary. There is no sign of #!02# and...\n\n\"What is going on?\"\n\n#!00# distinctly remembers that the hallway to the sanctuary was from the left. This time the hallway to the sanctuary is straight ahead.\n\n#!00# takes a deep breath, steps back inside the sanctuary and closes the door.\n\n\n[10 minutes later...]\n\nFirst, #!00# searched around inside the sanctuary. There was no sign of #!02#, or anyone else. There was only the one lantern that #!00# was holding, and no sign of the other. #!00# found her broken armor where she had left it. Upon closer inspection, #!00# noticed that her old armor was practically of no use now. For extra protection, #!00# decided to also put on the cloak that #!02# left behind.\n\nThe only other thing that #!00# found of interest was another small rectangular box that looks like the one that #!01# had originally given #!00#. The box was sitting on a table, in plain view. Inside the box was another \"holy artifact\", a dildo, just like the one that was inside the backpack that #!00# lost. #!00# decided to take the dildo, with the box, and put it inside her new backpack.\n\nThe only conclusion that #!00# has is that #!02# wondered away from the sanctuary. #!02# had told #!00# that she dared not venture away from the sanctuary for too long. #!00# considered for a second that #!02# wasn\'t always mentally stable. #!02# could have gone against that better judgment while she was focusing on her lord or master... whoever or whatever, they or it, is...\n\nThe other possibility is that #!02# was lying. #!00# decides that she can figure out of her companion for the evening was in fact telling the truth later.\n\n#!00# steps out of the door of the sanctuary, grabs the handle and pulls the door shut behind her. Without the locking bar being in place, the door won\'t keep much out. Without anyone left inside the sanctuary, there is no way that the locking bar can be put back in place. However, #!00#\'s job is to recover what the nuns hired her for, so that is what she is going to do.\n\nOutside of the sanctuary, there is a pathway that leads south.\n\n");
    if (iRet != 0) return iRet;

    // this is the init/reset of the encounter array
    for (sOffset1 = 0; sOffset1 < 50; sOffset1++)
    {
        if (sOffset1 % 3)
            gstructActStateGlobal.caEncounterArray[sOffset1] = 0;
        else
            gstructActStateGlobal.caEncounterArray[sOffset1] = 1;
    }

    // we are definitely act 2
    gstructActStateGlobal.sActId = 2;
    gstructActStateGlobal.sAct2Monsters = 0;

    // PosId 2 is the start.
    gstructActStateGlobal.sPosId = 2;

    // init the map
    sprintf (szWorkString, "Map%dAct%d", gstructActStateGlobal.sMapId, gstructActStateGlobal.sActId);

    // now init (and allocate) the map data.
    iRet = mapdata_selectAndInitMapData (szWorkString);
    if (iRet != 0) return 1;

    // seed random data in the map values.
    mapdata_seedRandomMapValues ();

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;

    // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
    gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2

    //
    // We also need to change around the inventory..
    //

    // first, reset the entire inventory to 0.
    for (sOffset1 = 0; (gsActStateInventorySize + 1) > sOffset1; sOffset1++)
    {
        gpstructActStateInventory[sOffset1].sCount = 0;
        gpstructActStateInventory[sOffset1].structEff.iNum = 0;
        gpstructActStateInventory[sOffset1].structEff.fFraction = (float)0;
    }

    // The latex backpack itself counts as an inventory item.
    gpstructActStateInventory[21].sCount = 1;

    // And the holy artifact which was left behind for Wilda to find.
    gpstructActStateInventory[26].sCount = 1;

    //
    // .. and the character stats..
    //

    // this is the increase of the endurance value
    actionstate_statAddition (&gstructActStateCharWilda.structE, (float)50.212, (int)6000);

    // make stamina equal endurance.. then..
    gstructActStateCharWilda.structS.iNum = gstructActStateCharWilda.structE.iNum;
    gstructActStateCharWilda.structS.fFraction = gstructActStateCharWilda.structE.fFraction;
    // ..decrease of the stamina value (from where it started with Endurance)
    actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)0.126, (int)10);

    // increase might
    actionstate_statAddition (&gstructActStateCharWilda.structM, (float)24.753, (int)6000);

    // increase karma
    actionstate_statAddition (&gstructActStateCharWilda.structK, (float)5.821, (int)6000);

    // reduce frigidity by about half
    actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)((float)gstructActStateCharWilda.structF.iNum / (float)1.95), (int)24);

    // set lust to an arbitrary starting value
    gstructActStateCharWilda.structL.iNum = 10;
    gstructActStateCharWilda.structL.fFraction = (float)0.327;

    // decrease reflexes
    actionstate_statSubtraction (&gstructActStateCharWilda.structR, (float)12.832, (int)10);

    // increase Oral experience
    actionstate_statAddition (&gstructActStateCharWilda.structO, (float)8.902, (int)6000);

    // increase Vaginal experience
    actionstate_statAddition (&gstructActStateCharWilda.structV, (float)12.271, (int)6000);

    // increase Anal experience
    actionstate_statAddition (&gstructActStateCharWilda.structA, (float)0.123, (int)6000);

    // Weapon effectiveness: Spanking paddle
    gstructActStateCharWilda.structW.iNum = 11;
    gstructActStateCharWilda.structW.fFraction = (float)0.757;
    gstructActStateCharWilda.sSlotW = 5;

    // Gauntlet/Gloves effectiveness: empty
    gstructActStateCharWilda.structG.iNum = 0;
    gstructActStateCharWilda.structG.fFraction = (float)0;
    gstructActStateCharWilda.sSlotG = 0;

    // Boots/Shoes effectiveness: Latex thigh-high stockings and croc rubber shoes
    gstructActStateCharWilda.structB.iNum = 14;
    gstructActStateCharWilda.structB.fFraction = (float)0.972;
    gstructActStateCharWilda.sSlotB = 15;

    // Clothing/Armor effectiveness: Latex cloak and Rubber underbust corset
    gstructActStateCharWilda.structC.iNum = 20;
    gstructActStateCharWilda.structC.fFraction = (float)0.723;
    gstructActStateCharWilda.sSlotC = 9;

    // rather than tell the caller to not call navigation, I am going
    //  to let the caller call navigation, because navigation is what
    //  I want at the end of this transition.
    return 0;
}

//
// act 1 start point
//
int gamelogic01_event_scene002 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gpstructMapPosDynamicCurrent[1].sVisitCount == 3)
    {
        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at the T-intersection where she had set-off the trap that sealed her inside this dungeon. #!00# thinks to herself if she could find what she set off she might be able to undo it. She spends a minute walking around the T-intersection trying to find where the switch is, but has no luck. She gives up and decides that she is just wasting time here and should go elsewhere.\n\n");
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// act 2 end (Act 2 -> Act 3 transition)
//
int gamelogic01_event_scene003 (char cSubFlag)
{
    int iRet;
    char szWorkString[20];
    short sOffset1;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# is walking along a hallway. It as if she can hear something. #!00# finds it weird, so she looks around carefully. #!00# cannot see anything that suggests that a monster is advancing towards her. So she takes a gamble, closes her eyes and tries to focus on the sounds that she can hear. It sounds like a voice. Possibly human.\n\n#!00# decides to keep walking along the hallway she is in.\n\n\n[1 minute later...]\n\n#!00# has made a right hand turn. The sound is starting to get louder.\n\n\n[1 minute later...]\n\nAt a T-intersection. The sounds are coming from... straight ahead and not the left passageway.\n\n\n[1 minute later...]\n\nDrat... That sounds like a person\'s voice... no... two people.\n\n\n[2 minutes later...]\n\n#!00# makes a right turn and then... She sees them. #!00# sees the two monsters. And, the monsters are not alone. There are two people here as well. Both of them are human women.\n\nEach monster is paired with each human woman. There are tentacles sliding in and out of every available major orifice. The women\'s bodies are shaking due to the barrage of powerful orgasms that they are experiencing. The monsters are still concentrating on their respective partners, completely oblivious to the fact that #!00# showed up, with a lantern that has illuminated the otherwise dark corridor.\n\nFor a moment, #!00# ponders leaping in and fending off the two monsters. However, her opponents have hostages. #!00# considers calling out to the two women, but realizes that would alert the monsters to her presence sooner, and that would probably be a bad idea.\n\n#!00# slowly steps around to see if she can get a better opening, her own clitoris starts to perk up, along with her nipples. She is finding this scene rather erotic. As for her pussy...\n\n#!00# suddenly remembers that she left a dildo inside her pussy. That was stupid. It\'s presence is going to affect her movement. #!00# decides that before she is going to charge in, she will have to remove it first. Thankfully, #!00# is horny again, so the dildo is going to be well lubricated. First, #!00# walks, while still knee deep in liquid over to a wall, and hooks the lantern on a rock that is jutting out. Then #!00# gets her spanking paddle ready. Finally, #!00# reaches underneath her cloak and pulls the dildo out.\n\nAt that point the two monsters take notice of #!00# and immediately stop violating both of the women. #!00# is standing there with a spanking paddle in her right hand, and a wet dildo in her left. #!00# tries to think of something that will act as a diversion, then realizes that while she can throw rather well with her right hand, she is has horrible aim with her left. The closest monster pulls it\'s appendages out of the human woman it was fucking and sets her down. #!00# considers it would be a really bad idea to swap weapons between hands now, besides... what other use does a dildo have?\n\n#!00# throws the dildo with her left hand at the far wall of the hallway, hoping that the monsters would be distracted either by it hitting the wall or falling into the liquid.\n\nUnexpectedly, the nearest monster scampers off after the dildo. The second monster sets down the human woman it was fucking and follows the first monster.\n\n#!00# watches in disbelief as both of the monsters then scamper away, down the hallway. #!00# caught a glimpse of the first monster holding the dildo that she threw in one of it\'s appendages. #!00# looks around the hallway to see if there is any more imminent danger. She then looks at the two human women, who are sitting down in the opaque liquid.\n\n\n[2 minutes later...]\n\nThe first nun, who is wearing what appears to be a latex open cup crop top, latex crotchless pantyhose and elbow-length latex gloves, is busy pleasuring herself. Under her breath, she is muttering obscene derogatory comments about herself and her genitals. She is also heavily pregnant.\n\nThe second nun, who is wearing a black latex cape, a black latex open cup camisole, knee-high black latex socks and wrist length black latex gloves, has finally acknowledged #!00# \"Sister?\"\n\n#!00# looks around the hallway again \"Is there somewhere safe for us to go?\"\n\nThe second nun blinks, glances at the first nun, then looks over #!00# again \"Oh, I am sorry\"... The second nun then blurts out \"Have you considered Hedonism?\"\n\nThe first nun chimes in, without looking at #!00# or her companion, while still in her dream trance \"You really should, it feels really good\"... the first nun then slips back into her routine of self pleasure.\n\n#!00# just stands there staring at the first nun, dumbfounded. After a few seconds, #!00# looks around the hallway again, then at the second nun.\n\nThe second nun addresses #!00# \"You bear the mark of a \'sanctioned servant\', so you must be on a quest. I am #!04#, and this is my senior sister, #!03#\".\n\n#!00# responds \"My name is #!00#, I was hired to do a job, but first\"... #!00# looks around \"I need to get you two somewhere safe\".\n\n#!04# starts to stand up \"We have a sanctuary nearby\".\n\n#!00# is about to ask where, when #!03# staggers to her feet, and starts walking along the hallway. #!00# looks at #!03#, both surprised and dumbfounded \"Ahh\"...\n\n#!04# looks at #!00# \"We just need to... follow my senior\".\n\n#!00# responds \"Ok\", and wonders over to the wall to collect her lantern.\n\n\n[3 minutes later...]\n\n#!00# and #!04# are following #!03# through the passageways. #!00# looks at #!04# \"Does, your senior, know where she is going?\"\n\n#!04# replies, while also fingering her exposed clitoris, \"Every senior nun does. I am still learning... So, why are you wearing a nun\'s cloak?\"\n\n#!00# remembers that she grabbed the cloak and the lantern before leaving the sanctuary, which now seems like a bad idea \"Sorry, but it was left behind in the sanctuary that I left earlier. Is this... a problem?\"\n\n#!04# responds without breaking her smile \"Not for me\".\n\n#!00# decides that as soon as she gets a chance, she should get rid of the cloak. #!00# decides to change the subject \"Could you tell me... about this armband?\"\n\n#!04# replies \"All I know is that the symbol means a \'sanctioned servant\' of our... Lord\"...\n\n#!00# notices that #!04#\'s walk is slowing down and her eyes are starting to glaze over, so she quickly interrupts #!04#\'s line of thought \"Yes, and you are to lend assistance... Am I right?\"\n\n#!04# quickly recovers from her trance thought \"Uhh... Yes... but I don\'t really know much more than that, Because\"...\n\n#!00# completes the sentence for #!04# \"Because you are still learning?\"\n\n#!04# responds with a bigger smile \"Yes\".\n\n#!00# lightly smiles then almost trips up. #!00# stops walking and looks at #!04# who is calmly walking through the liquid. Then there is #!03#, who is effectively sleepwalking through the liquid as well. Then #!00# considers the fact that she is the only one of the 3 holding a lantern. #!00# quickly rushes to keep up with the two nuns, while wondering how either of them are able to navigate around inside the submerged hallway, in complete darkness.\n\nThe trio turn right into another hallway.\n\n\n[2 minutes later...]\n\nNext to the entrance of the sanctuary, is a lantern hanging on a wall. As the trio approach it, #!04# quickly rushes over, grabs the lantern off the wall, and opens the door of the sanctuary.\n\n#!03#, without breaking her stride, turns towards the door, walks up the steps and through the open door. #!00# follows #!03# inside the sanctuary. #!04# follows #!00#, while closing the door.\n\nInside the sanctuary, #!03# just stands there, in the middle of the entrance room, still fingering herself while in a trance. #!00# looks around the sanctuary and notices that this one appears to be larger than the one she left earlier this morning. #!00#\'s focus is brought back to #!03# who seems to be muttering a little bit louder now \"Ah... Lord... Cock... Violate thy obedient fuckslave, with your all of your turgid might\".\n\n#!00# asks #!04# a question \"So, what exactly is your senior doing?\"\n\n#!04# answers \"Praying\".\n\n#!00# responds \"Oh... Praying\". #!00# decides to check the locking bar for the front door of the sanctuary. Only to find that there isn\'t one. Not only is there no bar next to the door, there are no hooks on either side of the door to hold the bar. This isn\'t good. #!00# decides to check with #!04#... and... drat.\n\n#!04# is now standing next to #!03#. Both of the nuns are chanting the same phrases out loud, while fingering themselves in unison \"My holy lord and master... Cock... We are but pitiful vessels for your holy seed... Impregnate our sopping wet holes with your baby batter and grant us endless pleasure\"...\n\n#!00# decides that she will have to sit down and wait for a while.\n\n\n[4 minutes later...]\n\n#!00# has used her spare time to take off the cloak that she borrowed from #!02# and fold it up.\n\n#!04# comes out of her trance state first, while #!03# continues mindlessly reciting quotes about being used as a fucktoy while slicking herself to another orgasm.\n\n#!00# snaps her fingers to prove that #!04# is back on the same plane of reality. #!04# looks at #!00# and asks \"Is something the matter?\"\n\n#!00# asks in return \"For how long has your senior been praying?\"\n\n#!04# glances at #!03# and looks back at #!00# \"about... two days ago\".\n\n#!00# is surprised \"two days?\"\n\n#!04#\'s smile doesn\'t change, but she puts her right hand on her hip when casually responding \"My senior can pray for up to a week, sometimes longer\"... #!04# then regains her posture and goes right back to masturbating.\n\n#!00# responds \"A week?... Okay... So, what where you two doing out in the hallways?\"\n\n#!04# replies \"Praying... Of course. We sometimes get help from our lord and master... Cock... to... fill our slutty pussies with their holy semen... to smear our bodies with the divine seed\".\n\n#!04# slips back into her masturbation trance. #!00# looks down at #!04#\'s belly and notices that it is slightly swollen, while #!04#\'s enlarged nipples are a dark shade of brown. #!00# briefly considers the connection between the tentacle monsters and the religion this pair of perverted nuns follow, but swiftly dismisses it as an impossibility.\n\n#!00# decides to wait for #!04# to stop \'praying\'.\n\n\n[30 minutes later...]\n\nWhile waiting for either of the nuns to finish \'praying\', #!00# ended up having her own personal indulgence while both #!04# and #!03# were distracted. #!00# decided that it would not be rude to jill herself off, considering that both of the nuns were doing it anyway.\n\nEventually #!04# finished, so #!00# broke off pleasuring herself. #!00# offered #!04# #!02#\'s cloak. #!04# insisted that #!00# take something in return. #!00# followed #!04# to another room, leaving #!03# to continue her \'personal prayer of self degradation\'.\n\n#!04# gleefully rummages through the sanctuary clothing supplies and offers #!00# a harness bra made out of rubber and shoulder length rubber gloves. #!00# considers it impolite to reject either item. The gloves will offer protection. The harness bra won\'t offer anything beyond decoration. #!04# helps #!00# put both of the items on.\n\n#!04# finds a spanking paddle and offers it to #!00#. #!00# shows #!04# the spanking paddle that she already has, so #!04# puts the one that she found away.\n\n#!04# then leads #!00# to the bedroom. Upon entering the room, #!00# can only look in awe at a big \"thing\" covered in black latex rubber. The bed is massive, and round. 6 warriors in armor could easily sleep on it. #!00# is surprised at the scale of the bed. #!04# giggles and suggests that #!00# should have a rest. #!00# thanks #!04# and crawls up on the bed and lays down. #!04# picks up the lantern and walks out of the room, leaving #!00# to quietly slip in to a deep slumber.\n\n\n[?? amount of time later...]\n\n#!00# wakes up. She is feeling rather refreshed, as well as rather horny. #!00# licks her lips, as well as her gloved fingers. Whatever is on her fingers, is rather tasty, and somehow familiar.\n\nSomebody nearby talks to #!00# \"Good morning, Have you considered Hedonism?\"\n\n#!00# sleepily responds \"Maybe\", then realizes she is talking to someone. #!00# opens her eyes and looks around the room that is lit with an aquamarine color.\n\n#!00#\'s eyes finally find #!03#, who introduces herself \"Hello, My name is #!03#\".\n\n#!00# props herself up on her elbows. There is a tingling sensation from the butt-plug that is present in her anus. #!00#\'s arousal quickly spikes and settles down a little bit. #!00# desperately wants to finger herself right now, but there are more important formalities to attend to. She talks to #!03# \"My name is #!00#, and we have met before\".\n\n#!00# suddenly remembers that there was another nun, and starts looking around the bedroom \"Where is... #!04#?\"\n\n#!03# stands up. #!00# looks over #!03#. Her baby belly is now gone, and she is now wearing an open bust latex garter dress, with suspenders connected to latex stockings. The latex stockings are stirrup-stockings, but, they are mostly obscured by the thigh-high low-heel rubber boots that #!03# is wearing. #!03# is also wearing shoulder length latex gloves. #!03# replies \"#!04#, my former junior, is currently elsewhere, praying\".\n\nInitially, #!00# can only a muster an \"Oh\" response. #!00# thinks about the changes that she can see about #!03# and asks a question \"How long have I been asleep?\"\n\n#!03# ignores the question and picks up one of the aquamarine lanterns \"You are a \'sanctioned servant\', and require assistance with your quest. I shall guide you to the next sanctuary\".\n\n\n[10 minutes later...]\n\nWhile waiting for #!03# to get her equipment together, #!00# patiently waited in the sanctuary entrance room with an aquamarine lantern. #!03# has the other lantern. While waiting there, #!00# is unconsciously fingering herself with her left hand.\n\n#!03# returns to the entrance room, with a latex backpack on her back, a spanking paddle and lantern in her right hand, while also fingering herself with her left. Watching #!03# walk towards her, #!00# becomes fixated on #!03#\'s massive breasts. The way that her dark nipples bounce is rather soothing, almost hypnotic.\n\n#!03# notices that #!00# is staring at her breasts and pronounces \"I have borne many children for my lord and master... Cock... And my udders are heavy with joyous milk... Are you ready to continue your quest?\"\n\nThe question snaps #!00# out of her daze. She replies \"Yes, I will... continue my quest\"...\n\n#!03# opens the door, and the pair depart from the sanctuary.\n\nOutside the sanctuary, #!00# looks to the south. There is a pathway there. #!03# looks at #!00# \"We need not regard that way\".\n\n#!00# inquires \"Why?\"\n\n#!03# continues \"That way only leads back up. Your quest... is to the east\"...\n\n#!00# asks \"East goes down?\"\n\n#!03# nods her head \"Yes\".\n\n");
    if (iRet != 0) return iRet;

    // this is the init/reset of the encounter array
    for (sOffset1 = 0; sOffset1 < 50; sOffset1++)
    {
        if (sOffset1 % 3)
            gstructActStateGlobal.caEncounterArray[sOffset1] = 0;
        else
            gstructActStateGlobal.caEncounterArray[sOffset1] = 1;
    }

    // setup the unlock array for act 3
    gstructActStateGlobal.caAct3UnlockArray[0] = 1; // pull back
    gstructActStateGlobal.caAct3UnlockArray[1] = 0; // massage breasts
    gstructActStateGlobal.caAct3UnlockArray[2] = 0; // blow kiss
    gstructActStateGlobal.caAct3UnlockArray[3] = 0; // pinch clitoris
    gstructActStateGlobal.caAct3UnlockArray[4] = 0; // wiggle butt
    gstructActStateGlobal.caAct3UnlockArray[5] = 0; // finger pussy
    gstructActStateGlobal.caAct3UnlockArray[6] = 0; // kneel down
    gstructActStateGlobal.caAct3UnlockArray[7] = 1; // crystal help
    gstructActStateGlobal.caAct3UnlockArray[8] = 0;
    gstructActStateGlobal.caAct3UnlockArray[9] = 0;

    // we are definitely act 3
    gstructActStateGlobal.sActId = 3;
    gstructActStateGlobal.sAct3Monsters = 0;

    // PosId 2 is the start.
    gstructActStateGlobal.sPosId = 2;

    // init the map
    sprintf (szWorkString, "Map%dAct%d", gstructActStateGlobal.sMapId, gstructActStateGlobal.sActId);

    // now init (and allocate) the map data.
    iRet = mapdata_selectAndInitMapData (szWorkString);
    if (iRet != 0) return 1;

    // seed random data in the map values.
    mapdata_seedRandomMapValues ();

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;

    // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
    gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2

    //
    // Now to init Crystal's values
    //

    // Endurance (HP max)
    gstructActStateCharCrystal.structE.iNum = 2123;
    gstructActStateCharCrystal.structE.fFraction = (float)0.426;

    // Stamina (HP current)
    gstructActStateCharCrystal.structS.iNum = 2094;
    gstructActStateCharCrystal.structS.fFraction = (float)0.638;

    // Might (Strength)
    gstructActStateCharCrystal.structM.iNum = 420;
    gstructActStateCharCrystal.structM.fFraction = (float)0.421;

    // Karma (Luck/Fate)
    gstructActStateCharCrystal.structK.iNum = 3203;
    gstructActStateCharCrystal.structK.fFraction = (float)0.535;

    // Frigidity (Lust max)
    gstructActStateCharCrystal.structF.iNum = 90;
    gstructActStateCharCrystal.structF.fFraction = (float)0.504;

    // Lust (Arousal)
    gstructActStateCharCrystal.structL.iNum = 40;
    gstructActStateCharCrystal.structL.fFraction = (float)0.713;

    // Reflexes (Combat Experience)
    gstructActStateCharCrystal.structR.iNum = 453;
    gstructActStateCharCrystal.structR.fFraction = (float)0.642;

    // Oral experience
    gstructActStateCharCrystal.structO.iNum = 2304;
    gstructActStateCharCrystal.structO.fFraction = (float)0.668;

    // Vaginal experience
    gstructActStateCharCrystal.structV.iNum = 2613;
    gstructActStateCharCrystal.structV.fFraction = (float)0.415;

    // Anal experience
    gstructActStateCharCrystal.structA.iNum = 2432;
    gstructActStateCharCrystal.structA.fFraction = (float)0.504;

    // Weapon effectiveness: Spanking paddle
    gstructActStateCharCrystal.structW.iNum = 10;
    gstructActStateCharCrystal.structW.fFraction = (float)0.521;
    gstructActStateCharCrystal.sSlotW = 5;

    // Gauntlet/Gloves effectiveness: Shoulder length latex gloves
    gstructActStateCharCrystal.structG.iNum = 4;
    gstructActStateCharCrystal.structG.fFraction = (float)0.538;
    gstructActStateCharCrystal.sSlotG = 19;

    // Boots/Shoes effectiveness: Latex thigh-high stirrup-stockings and thigh-high low-heel rubber boots
    gstructActStateCharCrystal.structB.iNum = 41;
    gstructActStateCharCrystal.structB.fFraction = (float)0.624;
    gstructActStateCharCrystal.sSlotB = 16;

    // Clothing/Armor effectiveness: Open bust latex garter dress with suspenders
    gstructActStateCharCrystal.structC.iNum = 13;
    gstructActStateCharCrystal.structC.fFraction = (float)0.235;
    gstructActStateCharCrystal.sSlotC = 10;

    //
    // And change Wilda's values
    //

    // The holy artifact was lost, so it is no longer in Wilda's inventory.
    gpstructActStateInventory[26].sCount = 0;
    // Note: this is removed by other storyline elements anyway.. this is just making sure that it still is not there..

    // this is the increase of the endurance value
    actionstate_statAddition (&gstructActStateCharWilda.structE, (float)72.326, (int)6000);

    // make stamina equal endurance.. then..
    gstructActStateCharWilda.structS.iNum = gstructActStateCharWilda.structE.iNum;
    gstructActStateCharWilda.structS.fFraction = gstructActStateCharWilda.structE.fFraction;
    // ..decrease of the stamina value (from where it started with Endurance)
    actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)1.273, (int)10);

    // increase might
    actionstate_statAddition (&gstructActStateCharWilda.structM, (float)41.273, (int)6000);

    // increase karma
    actionstate_statAddition (&gstructActStateCharWilda.structK, (float)21.273, (int)6000);

    // reduce frigidity by about half, again
    actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)((float)gstructActStateCharWilda.structF.iNum / (float)1.91), (int)24);

    // set lust to an arbitrary starting value
    gstructActStateCharWilda.structL.iNum = 21;
    gstructActStateCharWilda.structL.fFraction = (float)0.261;

    // decrease reflexes
    actionstate_statSubtraction (&gstructActStateCharWilda.structR, (float)18.123, (int)10);

    // increase Oral experience
    actionstate_statAddition (&gstructActStateCharWilda.structO, (float)15.171, (int)6000);

    // increase Vaginal experience
    actionstate_statAddition (&gstructActStateCharWilda.structV, (float)42.146, (int)6000);

    // increase Anal experience
    actionstate_statAddition (&gstructActStateCharWilda.structA, (float)145.210, (int)6000);

    // Weapon effectiveness: Spanking paddle (increase it if it is depleted)
    if (gstructActStateCharWilda.structW.iNum < 3)
        actionstate_statAddition (&gstructActStateCharWilda.structW, (float)7.237, (int)6000);

    // Gauntlet/Gloves effectiveness: Shoulder length latex gloves
    gstructActStateCharWilda.structG.iNum = 4;
    gstructActStateCharWilda.structG.fFraction = (float)0.53;
    gstructActStateCharWilda.sSlotG = 19;

    // Boots/Shoes effectiveness: Latex thigh-high stockings and croc rubber shoes (increase it if it is depleted)
    if (gstructActStateCharWilda.structB.iNum < 3)
        actionstate_statAddition (&gstructActStateCharWilda.structB, (float)6.135, (int)6000);

    // Clothing/Armor effectiveness: Rubber underbust corset and Rubber harness bra
    gstructActStateCharWilda.structC.iNum = 14;
    gstructActStateCharWilda.structC.fFraction = (float)0.281;
    gstructActStateCharWilda.sSlotC = 11;

    // rather than tell the caller to not call navigation, I am going
    //  to let the caller call navigation, because navigation is what
    //  I want at the end of this transition.
    return 0;
}

//
// act 2 start point
//
int gamelogic01_event_scene004 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at the entrance to the sanctuary. It is possible that someone has returned, so she walks over to the door and opens it. #!00# looks around inside the entrance room, to see that there is no sign of anyone there. #!00# then pulls the door closed. It is obvious that if there was someone inside they would have put the locking bar across the door anyway. It is clear that there is nobody here.\n\n");
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 3 end (Act 3 -> Act 4 transition)
//
int gamelogic01_event_scene005 (char cSubFlag)
{
    int iRet;
    char szWorkString[20];
    short sOffset1;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("As #!03# and #!00# exit a hallway into a T-intersection, #!03# looks at a marking on the wall. #!00# asks #!03# \"What is it?\"\n\n#!03# points down the left passageway \"We should... go that way\"...\n\n\n[5 minutes later...]\n\n#!03# and #!00# arrive at a sort-of familiar looking door at the end of a hallway, with stairs leading from the white liquid up to it.\n\nWhile #!03# opens the door of the sanctuary, #!00# wonders if this sanctuary is going to be empty. The moment that the door is open, #!00# can hear murmuring from inside.\n\n#!03# looks inside the door and then back at #!00# \"We should join in\".\n\n#!00# follows #!03# into the sanctuary, where she sees another nun, wearing latex suspender-tights with rubber knee-high low-heel boots, wrist length gloves and short sleeved bolero. She is also heavily pregnant. After #!00# finishes looking over the nun, who is muttering \"Fill both of my lower mouths with your hot-dick milk\", #!00# looks at #!03#.\n\n#!03# motions with her open hand to the nun \"This is #!05#, a fellow senior nun\".\n\n#!00# responds \"Obviously\", then looks back at #!05#. #!00# then notices that #!05#\'s clitoris and nipples are a lot larger than normal. #!05#\'s breasts are lightly lactating. #!00# is briefly entranced by #!05#\'s swinging breasts, but comes back from it. #!00# is about to ask #!03# more about #!05#... however...\n\n#!03# is now standing next to #!05#, and the two nuns are praying in unison. #!00# sighs... At least #!03# refrained from praying until they got here.\n\nThen #!00# finds herself being drawn to #!03# and #!05#\'s heaving breasts.\n\n\n[20 minutes later...]\n\n#!00# is in a daze. Someone says to her \"Have you considered Hedonism?\"\n\n#!00# responds \"I really am\"... just as she breaks out of her daze and looks at #!05#, who was asking the question. #!00# is confused then perplexed.\n\n#!03# chimes in and says \"aaand... it feels really good, doesn\'t it?\"\n\n#!00# blushes \"Sorry, I am #!00#\".\n\n#!05# responds \"And you are on a quest. Come... you must be tired\".\n\n\n[5 minutes later...]\n\nThe trio visit the sanctuary clothing supply storage. #!05# throws #!00# a new butt-plug that is a size larger than the one she currently has. #!00# thanked #!05# for the gracious replacement, then proceeded to swap out her existing butt-plug for the new one, without a second thought. #!00# decides that she does not need anything else, so the trio move onto the bedroom.\n\nBefore arriving at the bedroom, #!00# was wondering what size the bed is going to be. When they got there, #!00# was surprised that there aren\'t any beds in the bedroom. There are four identical and strange looking chairs.\n\n#!00# looks at #!05# \"So... This is where I am going to sleep?\"\n\n#!05# nods, and her smile briefly turns to a grin \"Yes, you have not seen these before?\"\n\n#!00# looks at the nearest gynecologist chair and states \"I cannot say that I have\". #!00# then looks at #!05# apprehensively and asks \"So... how do I... get to sleep in one of these... things?\"\n\n\n[2 minutes later...]\n\nBeing #!00#\'s first time getting into a gynecologist chair ever, it wasn\'t easy, but #!05# and #!03# were a big help. After #!00# sat into the actual seat itself of the gynecologist chair closest to the door, #!05# and #!03# lifted #!00#\'s legs up into the stirrups and strapped them in. #!00# started unconsciously masturbating with her left hand again, while the two nuns continued checking the straps on #!00#\'s legs, then continued to strap #!00#\'s body into the chair.\n\n#!03# looks at #!00# \"This is to make sure you don\'t fall out while you are sleeping\".\n\n#!00# responds \"Oh... how thoughtful\".\n\n#!03# grins at #!00#, as she then pulls #!00#\'s left hand away from her crotch and proceeds to strap #!00#\'s left arm into an armrest. #!05# does the same with #!00#\'s right arm.\n\n#!00# starts to feel a little bit uneasy, given that she is unable to masturbate \"So... How do\"...\n\n#!05# places a finger over #!00#\'s mouth \"Don\'t worry, we will take care of the rest\", and proceeds to start fondling #!00#\'s right breast.\n\nMeanwhile #!03# is sucking on #!00#\'s left nipple, while also fingering #!00#\'s swollen pussy. #!00# lets out a moan of pleasure \"That feels... so fucking good\"...\n\n#!05# continues to fondle #!00#\'s right breast with her right hand, while stroking #!00#\'s forehead with her left. #!00# looks at #!05#\'s face. #!05# tells #!00# \"Look at my milk filled udders... at my teats\". #!00# finds that she needs to look at #!05#\'s breasts. The way that #!05#\'s nipples lightly sway is soothing. #!05# continues talking \"That\'s it... go deeper... and deeper\"...\n\n#!00# can only mutter a \"Yes... deeper\"...\n\n#!05# speaks slowly \"Now... Sleep\"...\n\n\n[?? amount of time later...]\n\n#!00# wakes up. She squints her eyes and looks around the room that is illuminated by and aquamarine light. Her entire body is still strapped into a chair. #!00# is still disoriented \"Where... am I?\"\n\nSuddenly #!00# feels something at her crotch. While her clitoris is being stroked, she is asked a question \"Have you considered Hedonism?\"\n\n#!00#, still in a daze, answers \"I really want a really good baby-making-fuck\".\n\nThe unfamiliar voice giggles \"Aren\'t you... already preggers?\"\n\n#!00# snaps out of her daze, and looks at the woman she is talking to \"Oh... sorry... I am #!00#\".\n\nThe nun introduces herself \"I\'m #!06#, an\' the pleasure is both of ours\".\n\n#!06# then kneels down between #!00#\'s open legs and proceeds to lick and suck #!00#\'s clitoris. #!00# can barely see the top of #!06#\'s head past her own swollen belly. Unknown to #!00# is that her clitoris is a lot larger than before. #!00# just lays there, still strapped into the gynecologist chair, furthest from the door, as #!06# continues to eat her out.\n\n\n[5 minutes later...]\n\n#!06# finally lets #!00# out of her \'bed\'. While #!06#, alone, unstrapped #!00#, #!00# got a better look at #!06#.\n\n#!06# is wearing a body harness made out of rubber strips, wrist length latex gloves, ankle length latex socks, and rubber ballerina flat shoes. #!06# also has a collar around her neck, and her over-sized nipples and clitoris are pierced with over-sized studs. #!06# is also heavily pregnant.\n\nAfter #!00# finally stepped out of the seat, #!06# handed #!00# her backpack and lantern. There is another lantern on the floor, which #!06# picks up.\n\n#!00# looks around the room again, and asks #!06# \"Is there... anyone else around?\"\n\n#!06# responds \"Jus\' us two now\".\n\n#!00# responds \"Oh\"... then looks down at her swollen breasts and belly. The corset belt is now gone. #!00#\'s aureole are now now larger and slightly darker. #!00#\'s nipples are now permanently erect and the size of her thumb-tips.\n\n#!06# adds \"or jus\' us four?\"\n\n#!00# smiles at #!06#. #!00# has no problems with being pregnant. For as long as she can remember, #!00# always wanted to be like this. #!06#\'s belly is larger as her pregnancy is clearly more advanced. #!00# unconsciously starts stroking her clitoris again as she asks #!06# \"So, where are #!03# and #!05#?\"\n\n#!06#\'s smile reduces a little bit \"Those missies be praying now, away from here... I must apologize... I can\'t come with you\".\n\n#!00# then remembers that she is on a quest. For some reason, #!00# already has a vague idea of where she is going.\n\n\n[2 minutes later...]\n\n#!06# was nice enough to accompany #!00# to the sanctuary entrance. When they reach the doorway, #!06# proclaims \"Jus\' a moment... I have something for you\".\n\n#!06# strides over to a small table and picks up a small rectangular box. #!06# then returns back to #!00# \"Miss \'sanctioned servant\' will need her \'holy artifact\', won\'t she?\"\n\n#!06# hands over the box and #!00# accepts it from #!06# \"Why, thank you\".\n\n#!00# hugs #!06#, but #!06# protests. \"Now that won\'t do... I will show you\".\n\n#!06# lightly pushes #!00# away, then starts giving #!00# a sloppy kiss. #!00# decides to reciprocate, and the two pregnant women continue intertwining their tongues while also fondling each other. #!06# finds #!00#\'s pussy and starts fingering it. #!00# starts playing with #!06#\'s left breast, causing breast milk to spray everywhere.\n\n\n[2 minutes later...]\n\nThe two women finally break away from each other. #!00# says to #!06# \"Thank you... again\". #!06# grins back at #!00#.\n\n#!00# then opens the \'holy artifact\' box that she was given. #!06# takes one look at the dildo that #!00# took out of the small box, and almost immediately slips into her prayer trance. \"My lord and master... Cock... Use my trashy cunny to your heart\'s content... Yes... More... Fuck up my life an\' my baby factory with your hawt milk\"...\n\n#!00# smiles, as she slips the dildo into her wet pussy. At least #!06# is happy praying. #!00# starts to thrust the dildo in and out of her pussy a couple of times, then realizes that her pussy is rather loose. #!00# decides that if she comes across a delightful tentacle monster she can just have them fill her aching pussy. #!00# pulls the wet dildo out of her pussy and puts it back inside it\'s small box. #!00# then puts the small box inside her backpack.\n\n#!00# picks up her lantern, opens the door of the sanctuary, walks through and closes the door behind her.\n\nOutside of the sanctuary, there is a pathway that leads south.\n\n");
    if (iRet != 0) return iRet;

    // this is the init/reset of the encounter array
    for (sOffset1 = 0; sOffset1 < 50; sOffset1++)
    {
        if (sOffset1 % 4)
            gstructActStateGlobal.caEncounterArray[sOffset1] = 0;
        else
            gstructActStateGlobal.caEncounterArray[sOffset1] = 1;
    }

    // we are definitely act 4
    gstructActStateGlobal.sActId = 4;
    gstructActStateGlobal.sAct4Monsters = 0;

    // PosId 2 is the start.
    gstructActStateGlobal.sPosId = 2;

    // init the map
    sprintf (szWorkString, "Map%dAct%d", gstructActStateGlobal.sMapId, gstructActStateGlobal.sActId);

    // now init (and allocate) the map data.
    iRet = mapdata_selectAndInitMapData (szWorkString);
    if (iRet != 0) return 1;

    // seed random data in the map values.
    mapdata_seedRandomMapValues ();

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;
    gstructActStateGlobal.cStairDirect = 0;
    gstructActStateGlobal.cStairUpDown = 0;

    // this is the specific setup according to the act and map selected.
    switch (gstructActStateGlobal.sMapId)
    {
    case 1: // override the default VisitCount values for map 1, act 3.
        // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
        gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2
        gpstructMapPosDynamicCurrent[2].sVisitCount = 1; // PosId 3
        gpstructMapPosDynamicCurrent[3].sVisitCount = 1; // PosId 4
        gpstructMapPosDynamicCurrent[4].sVisitCount = 1; // PosId 5
        gpstructMapPosDynamicCurrent[6].sVisitCount = 1; // PosId 7
        gpstructMapPosDynamicCurrent[7].sVisitCount = 1; // PosId 8

        gpstructMapLinkDynamicCurrent[1].sVisitCount = 1; // LinkId 2 (between PosIds 2 & 3)
        gpstructMapLinkDynamicCurrent[4].sVisitCount = 1; // LinkId 5 (between PosIds 3 & 4)
        gpstructMapLinkDynamicCurrent[5].sVisitCount = 1; // LinkId 6 (between PosIds 4 & 5)
        gpstructMapLinkDynamicCurrent[7].sVisitCount = 1; // LinkId 8 (between PosIds 5 & 7)
        gpstructMapLinkDynamicCurrent[10].sVisitCount = 1; // LinkId 11 (between PosIds 7 & 8)
        break;

    case 2: // override the default VisitCount values for map 2, act 3.
        // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
        gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2
        gpstructMapPosDynamicCurrent[2].sVisitCount = 1; // PosId 3
        gpstructMapPosDynamicCurrent[3].sVisitCount = 1; // PosId 4
        gpstructMapPosDynamicCurrent[4].sVisitCount = 1; // PosId 5
        gpstructMapPosDynamicCurrent[5].sVisitCount = 1; // PosId 6
        gpstructMapPosDynamicCurrent[7].sVisitCount = 1; // PosId 8
        gpstructMapPosDynamicCurrent[8].sVisitCount = 1; // PosId 9

        gpstructMapLinkDynamicCurrent[1].sVisitCount = 1; // LinkId 2 (between PosIds 2 & 3)
        gpstructMapLinkDynamicCurrent[2].sVisitCount = 1; // LinkId 3 (between PosIds 3 & 4)
        gpstructMapLinkDynamicCurrent[3].sVisitCount = 1; // LinkId 4 (between PosIds 4 & 5)
        gpstructMapLinkDynamicCurrent[5].sVisitCount = 1; // LinkId 6 (between PosIds 5 & 6)
        gpstructMapLinkDynamicCurrent[7].sVisitCount = 1; // LinkId 8 (between PosIds 6 & 8)
        gpstructMapLinkDynamicCurrent[9].sVisitCount = 1; // LinkId 10 (between PosIds 8 & 9)
        break;

    case 3: // override the default VisitCount values for map 3, act 3.
        // Note: both for both gpstructMapPosDynamicCurrent and gpstructMapLinkDynamicCurrent, 1 = 0..
        gpstructMapPosDynamicCurrent[1].sVisitCount = 2; // PosId 2
        gpstructMapPosDynamicCurrent[2].sVisitCount = 1; // PosId 3
        gpstructMapPosDynamicCurrent[3].sVisitCount = 1; // PosId 4
        gpstructMapPosDynamicCurrent[20].sVisitCount = 1; // PosId 21
        gpstructMapPosDynamicCurrent[18].sVisitCount = 1; // PosId 19
        gpstructMapPosDynamicCurrent[19].sVisitCount = 1; // PosId 20

        gpstructMapLinkDynamicCurrent[1].sVisitCount = 1; // LinkId 2 (between PosIds 2 & 3)
        gpstructMapLinkDynamicCurrent[3].sVisitCount = 1; // LinkId 4 (between PosIds 3 & 4)
        gpstructMapLinkDynamicCurrent[5].sVisitCount = 1; // LinkId 6 (between PosIds 4 & 21)
        gpstructMapLinkDynamicCurrent[25].sVisitCount = 1; // LinkId 26 (between PosIds 21 & 19)
        gpstructMapLinkDynamicCurrent[26].sVisitCount = 1; // LinkId 27 (between PosIds 19 & 20)
        break;
    }

    //
    // And change Wilda's values
    //

    // The holy artifact from Felicity (is now back in the inventory).
    gpstructActStateInventory[26].sCount = 1;

    // this is the increase of the endurance value
    actionstate_statAddition (&gstructActStateCharWilda.structE, (float)88.271, (int)6000);

    // make stamina equal endurance.. then..
    gstructActStateCharWilda.structS.iNum = gstructActStateCharWilda.structE.iNum;
    gstructActStateCharWilda.structS.fFraction = gstructActStateCharWilda.structE.fFraction;
    // ..decrease of the stamina value (from where it started with Endurance)
    actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)10.271, (int)10);

    // increase might
    actionstate_statAddition (&gstructActStateCharWilda.structM, (float)64.162, (int)6000);

    // increase karma
    actionstate_statAddition (&gstructActStateCharWilda.structK, (float)45.272, (int)6000);

    // reduce frigidity by about 1/3rd
    actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)((float)gstructActStateCharWilda.structF.iNum / (float)2.9), (int)24);

    // set lust to an arbitrary starting value
    gstructActStateCharWilda.structL.iNum = 5;
    gstructActStateCharWilda.structL.fFraction = (float)0.023;

    // decrease reflexes
    actionstate_statSubtraction (&gstructActStateCharWilda.structR, (float)26.261, (int)10);

    // increase Oral experience
    actionstate_statAddition (&gstructActStateCharWilda.structO, (float)18.271, (int)6000);

    // increase Vaginal experience
    actionstate_statAddition (&gstructActStateCharWilda.structV, (float)37.421, (int)6000);

    // increase Anal experience
    actionstate_statAddition (&gstructActStateCharWilda.structA, (float)262.162, (int)6000);

    // don't bother changing any of the other elements.

    // Weapon effectiveness: empty (leave it that way)

    // Gauntlet/Gloves effectiveness: Shoulder length latex gloves
    if (gstructActStateCharWilda.structG.iNum < 3)
        actionstate_statAddition (&gstructActStateCharWilda.structG, (float)1.723, (int)6000);

    // Boots/Shoes effectiveness: Latex thigh-high stockings and croc rubber shoes (increase it if it is depleted)
    if (gstructActStateCharWilda.structB.iNum < 3)
        actionstate_statAddition (&gstructActStateCharWilda.structB, (float)8.301, (int)6000);

    // Clothing/Armor effectiveness: Rubber harness bra
    gstructActStateCharWilda.structC.iNum = 5;
    gstructActStateCharWilda.structC.fFraction = (float)0.852;
    gstructActStateCharWilda.sSlotC = 12;

    // Put the holy artifact back into Wilda's inventory.
    gpstructActStateInventory[26].sCount = 1;

    // rather than tell the caller to not call navigation, I am going
    //  to LET the caller call navigation, because navigation is what
    //  I want at the end of this transition.
    return 0;
}

//
// act 3 start point
//
int gamelogic01_event_scene006 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive back at the #!03#\'s sanctuary. #!00# looks at #!03# \"Do you think anyone has returned?\"\n\n#!03# replies \"Unlikely... I will check\".\n\n#!03# walks up the stairs to the door and opens it. #!03# looks around inside the entrance of the sanctuary, while #!00# looks to the southern passageway, and considers that someone could have returned while #!00# and #!03# were down the eastern passageway.\n\n#!03# closes the door and looks at #!00# \"There is no one else here\".\n\n#!00# responds \"Oh... Okay\"...\n\n#!03# continues \"Even if there was anyone else here, it is unlikely they would have been able to assist you. We should resume your quest\".\n\n");
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 4 end (Act 4 -> End transition)
//
int gamelogic01_event_scene007 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# is walking along a hallway, she reaches an apparent dead-end. However, there is an indentation in the wall, with a symbol painted on it. There are a set of stairs leading up from the liquid to the indentation. #!00# recognizes the symbol, as it matches the one that has shown itself on her armband. #!00# walks up the stairs to get a better look at the indentation.\n\nIn the center of the indentation, just below the symbol, is circular hole in the stone. The hole is just over 2 inches in diameter. #!00# just looks absentmindedly at the hole for a minute, and finally smiles.\n\n#!00# takes the backpack off her back, and finds the \'holy artifact\' box within it. As she takes the dildo out of the box, #!00# unconsciously starts to lick the tip of the dildo and then thrusts it into her pussy. #!00# fingers herself to a climax while pistoning the dildo in and out of herself. It takes about half a minute for #!00# to come out of her daze, and to realize that she is still standing in front of the door of her destination.\n\n\"That\'s right... I still need to open this\".\n\nWith relative ease, #!00# slides the dildo out of her pussy and then pushes it all of the way into the hole in the indentation.\n\nThere is a large audible click, followed by the sound of stone grinding against stone as the slab that forms the indentation slides away.\n\nThe passageway is filled with a pink colored light from inside the chamber. #!00# places her aquamarine lantern on a nearby rock \'hook\', as she won\'t be needing it, possibly ever again.\n\nAs #!00# steps into the chamber, 5 tentacle monsters rush towards her with great speed, but quickly stop once they are less than 3 feet away. #!00# lightly pats her swollen belly. Her masters will not harm her while she is accompanied by another master.\n\n#!00# surveys the tentacle monster throne room. There is the muffled voices of several human women who are confined to the \'nursery\'. They had failed, but still were able to share the pleasures that her masters can bestow.\n\nYes... they are her masters. They are her lords. #!00# starts to pray.\n\n\"My lord and master... Cock... I am before the to be baptized by your holy sperm... Come... Make make this slutty whore whole\"...\n\nThe 5 tentacle monsters that were originally going to attack #!00# and tear her to shreds, move in on her.\n\n#!00# briefly considers that she will be in heaven handling 5 masters at once.\n\n");
    if (iRet != 0) return iRet;

    // reset things
    gstructActStateGlobal.cEnteredDungeon = 0;

    // the holy artifact is no longer in the inventory.
    gpstructActStateInventory[26].sCount = 0;

    // pass control over to one of the good ending dialog outputs
    if (gstructActStateGlobal.sMapId == 1)
        iRet = gamelogic01_scene1012 (0, cSubFlag + 1);
    else if (gstructActStateGlobal.sMapId == 2)
        iRet = gamelogic01_scene1013 (0, cSubFlag + 1);
    else
        iRet = gamelogic01_scene1014 (0, cSubFlag + 1);
    if (iRet != 0) return iRet;

    // this return code is an instruction to gamelogic02_scene1021() to not return to navigation
    return -1;

    // the command structure is already setup by 1012, 1013 & 1014
}

//
// act 4 start point
//
int gamelogic01_event_scene008 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at the #!06#\'s sanctuary. #!00# wonders if anyone else has shown up, so she takes a peek inside the door of the sanctuary. #!06# is still there... Praying. #!00# decides to leave #!06# alone and continue on her way.\n\n");
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 1 stairdown1
//
int gamelogic01_event_scene009 (char cSubFlag)
{
    int iRet;
    int iLinkId;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        if (gstructActStateGlobal.cDirect == 4)
            cArriveTop = 1;
        break;

    default:
        if (gstructActStateGlobal.cDirect == 3)
            cArriveTop = 1;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of a staircase that is made out of wooden planks. There is a gravel ramp up from the liquid to the base of the staircase.");
        if (iRet != 0) return iRet;

        iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
        if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
        {
            if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 2)
            {
                gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 1;

                iRet = mdialog_addToDialogWithSrchRep (" #!00# is briefly distracted by the sound of stone sliding against stone from the corridor she just walked down.");
                if (iRet != 0) return iRet;

                if (gcDebugFlag != 0)
                {
                    char szWorking[80];

                    sprintf (szWorking, "\n\ndebug: LinkId %d closed", iLinkId);

                    iRet = mdialog_addToDialogWithSrchRep (szWorking);
                    if (iRet != 0) return iRet;
                }

                // override the direction, because we don't know which way we are facing now.
                gstructActStateGlobal.cDirect = 0;
            }
        }

        iRet = mdialog_addToDialogWithSrchRep ("\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of the wooden plank staircase. There is a gravel ramp from the top of the staircase down into the liquid.\n\n");
    }
    if (iRet != 0) return iRet;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;

    // set the direction
    if (gstructActStateGlobal.sMapId == 2)
    {
        gstructActStateGlobal.cStairDirect = 3; // south
    }
    else
    {
        gstructActStateGlobal.cStairDirect = 4; // west
    }

    return 0;
}

//
// act 1 stairup1
//
int gamelogic01_event_scene010 (char cSubFlag)
{
    int iRet;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    switch (gstructActStateGlobal.sMapId)
    {
    case 2:
        if (gstructActStateGlobal.cDirect == 3)
            cArriveTop = 1;
        break;

    default:
        if (gstructActStateGlobal.cDirect == 4)
            cArriveTop = 1;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the bottom of the wooden plank staircase. The lowest steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the base of a wooden plank staircase, rising up out of the white opaque liquid.\n\n");
    }
    if (iRet != 0) return iRet;

    // these are stairs up..
    gstructActStateGlobal.cStairUpDown = 1;

    // set the direction
    if (gstructActStateGlobal.sMapId == 2)
    {
        gstructActStateGlobal.cStairDirect = 1; // north
    }
    else
    {
        gstructActStateGlobal.cStairDirect = 2; // east
    }

    return 0;
}

//
// act 2 stairdown1
//
int gamelogic01_event_scene011 (char cSubFlag)
{
    int iRet;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;

    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        gstructActStateGlobal.cStairDirect = 1; // north

        if (gstructActStateGlobal.cDirect == 3)
            cArriveTop = 1;
        break;

    case 2:
        gstructActStateGlobal.cStairDirect = 4; // west

        if (gstructActStateGlobal.cDirect == 2)
            cArriveTop = 1;
        break;

    default: // case 3:
        gstructActStateGlobal.cStairDirect = 3; // south

        if (gstructActStateGlobal.cDirect == 1)
            cArriveTop = 1;
        break;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of the uneven stone staircase. At the top there is a gravel ramp down into the liquid.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of a uneven stone staircase. While there is a gravel ramp up from the liquid to the base of the staircase, there is opaque liquid tricking down the uneven stone stairs.\n\n");
    }
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 2 stairup1
//
int gamelogic01_event_scene012 (char cSubFlag)
{
    int iRet;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // these are stairs up..
    gstructActStateGlobal.cStairUpDown = 1;

    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        gstructActStateGlobal.cStairDirect = 3; // south

        if (gstructActStateGlobal.cDirect == 1)
            cArriveTop = 1;
        break;

    case 2:
        gstructActStateGlobal.cStairDirect = 2; // east

        if (gstructActStateGlobal.cDirect == 4)
            cArriveTop = 1;
        break;

    default: // case 3:
        gstructActStateGlobal.cStairDirect = 1; // north

        if (gstructActStateGlobal.cDirect == 3)
            cArriveTop = 1;
        break;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("Following the trickle of opaque liquid, #!00# arrives at the bottom of the uneven stone staircase. The lower steps disappear into the opaque liquid.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the base of an uneven stone staircase, which is rising up out of the opaque liquid. There is opaque liquid trickling down the stone steps.\n\n");
    }
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 2 stairdown2
//
int gamelogic01_event_scene013 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.cDirect == 1)
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of the staircase made out of worn stone steps. There is a makeshift wooden ramp at the top of the staircase leading down into the pool of white opaque liquid behind it.\n\n");
    else
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of a staircase made out of smooth stone. The stone steps are rather worn from being used for many years. There is a makeshift wooden ramp rising up out of the opaque liquid to the top of the stairs.\n\n");
    if (iRet != 0) return iRet;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;
    gstructActStateGlobal.cStairDirect = 3; // south

    return 0;
}

//
// act 2 stairup2
//
int gamelogic01_event_scene014 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // Note: It isn't possible but to approach this point from the south.
    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the bottom of the staircase made out of worn stone steps. The lower steps disappear into the white opaque liquid.\n\n");
    if (iRet != 0) return iRet;

    // these are stairs up..
    gstructActStateGlobal.cStairUpDown = 1;
    gstructActStateGlobal.cStairDirect = 1; // north

    return 0;
}

//
// act 3 stairdown1
//
int gamelogic01_event_scene015 (char cSubFlag)
{
    int iRet;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;

    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        gstructActStateGlobal.cStairDirect = 1; // north

        if (gstructActStateGlobal.cDirect == 3)
            cArriveTop = 1;
        break;

    case 2:
        gstructActStateGlobal.cStairDirect = 4; // west

        if (gstructActStateGlobal.cDirect == 2)
            cArriveTop = 1;
        break;

    default: // case 3:
        gstructActStateGlobal.cStairDirect = 2; // east

        if (gstructActStateGlobal.cDirect == 4)
            cArriveTop = 1;
        break;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the top of the staircase made out of black rubber.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at a staircase, that is made out of hard black rubber. It takes a couple of steps up out of the opaque liquid and then proceeds to slope down.\n\n");

        if (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount < 2)
        {
            if (iRet != 0) return iRet;

            iRet = mdialog_addToDialogWithSrchRep ("#!00# looks over the staircase and then asks #!03# \"Specially made?\"\n\n#!03# responds \"A gift... from our lord and master... Cock\"...\n\n#!00# decides that she is not going to bother asking #!03# exactly where her church got all of the rubber from to make this.\n\n");

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 3 stairup1
//
int gamelogic01_event_scene016 (char cSubFlag)
{
    int iRet;
    char cArriveTop = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // these are stairs up..
    gstructActStateGlobal.cStairUpDown = 1;

    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        gstructActStateGlobal.cStairDirect = 3; // south

        if (gstructActStateGlobal.cDirect == 1)
            cArriveTop = 1;
        break;

    case 2:
        gstructActStateGlobal.cStairDirect = 2; // east

        if (gstructActStateGlobal.cDirect == 4)
            cArriveTop = 1;
        break;

    default: // case 3:
        gstructActStateGlobal.cStairDirect = 4; // west

        if (gstructActStateGlobal.cDirect == 2)
            cArriveTop = 1;
        break;
    }

    if (cArriveTop == 1)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the bottom of the black rubber staircase. The lower steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the base of a staircase, made of black rubber, rising up out of the opaque liquid.\n\n");
    }
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 3 stairdown2
//
int gamelogic01_event_scene017 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.cDirect == 4)
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the top of the staircase made out of large smooth stone steps. The staircase crests then has a couple of large steps down into the opaque liquid at the top.\n\n");
    else
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the top of a stone staircase. Each step is a stone block that has been expertly crafted. There are a couple of large steps out of the opaque liquid, then it proceeds to slope down.\n\n");
    if (iRet != 0) return iRet;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;
    gstructActStateGlobal.cStairDirect = 2; // east

    return 0;
}

//
// act 3 stairup2
//
int gamelogic01_event_scene018 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // note: I don't need to take into consideration travel from the west, because it won't happen.

    iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the bottom of the staircase made of large smooth stone steps. The lower steps disappear into the white opaque liquid.\n\n");
    if (iRet != 0) return iRet;

    // these are stairs up..
    gstructActStateGlobal.cStairUpDown = 1;
    gstructActStateGlobal.cStairDirect = 4; // west

    return 0;
}

//
// act 4 stairdown1
//
int gamelogic01_event_scene019 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the top of a stone staircase. Each step is a stone block that has been expertly crafted. There are a couple of large steps out of the opaque liquid, then it proceeds to slope down.\n\n");
    if (iRet != 0) return iRet;

    if (gstructActStateGlobal.sMapId == 2)
        iRet = mdialog_addToDialogWithSrchRep ("This is a turn, with an unknown stairway leading down to the south, and an path to the west. However, #!00# is only going to go south.\n\n");
    else
        iRet = mdialog_addToDialogWithSrchRep ("This is a hallway, with an unknown stairway leading down to the south, and an path to the north. However, #!00# is only going to go south.\n\n");

    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("South stairs down", 1021, 3);
    if (iRet != 0) return iRet;

    // these are stairs down..
    gstructActStateGlobal.cStairUpDown = 2;
    gstructActStateGlobal.cStairDirect = 3; // south
    // I populate these values so that gamelogic02_scene1021() can figure out the resulting action correctly.

    // don't let the caller setup navigation, instead use what this has set.
    return -1;
}

//
// act 4 stairup1
//
int gamelogic01_event_scene020 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.cDirect == 3)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the bottom of the stone staircase. The lower steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the base of a staircase that is rising up out of the opaque liquid. The stone steps are rather large stone blocks that have been expertly crafted.\n\n");
    }
    if (iRet != 0) return iRet;

    switch (gstructActStateGlobal.sMapId)
    {
    case 3:
        iRet = mdialog_addToDialogWithSrchRep ("This is a turn, with a known stairway leading up to the north, and a path to the west. However, #!00# is only going to go west.\n\n");
        if (iRet != 0) return iRet;

        iRet = mutils_addToCommandList ("West", 1021, 4);
        if (iRet != 0) return iRet;
        break;

    default: // case 1 & 2:
        iRet = mdialog_addToDialogWithSrchRep ("This is a hallway, with a known stairway leading up to the north, and a path to the south. However, #!00# is only going to go south.\n\n");
        if (iRet != 0) return iRet;

        iRet = mutils_addToCommandList ("South", 1021, 3);
        if (iRet != 0) return iRet;
        break;
    }

    return -1;
    // The plan with this one is to override the navigation settings so
    //  that it isn't possible to walk back up the stairs.
}

//
// act 1 blocked entrance
//
int gamelogic01_event_scene021 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at the dead-end that used to be a turn. The stone slab is still sealing off the exit out of the dungeon. #!00# briefly contemplates if she can find the switch that will open it. It is also possible that there is another way out.\n\n");
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 1 first monster t-intersection
//
int gamelogic01_event_scene022 (char cSubFlag)
{
    int iRet;
    short sLinkId = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // if we have already had our first encounter, change the dialog
    if (gstructActStateGlobal.sAct1Monsters != 0)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at the T-intersection where she had fought and killed her first monster. It\'s dead body is still here.\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;

        return 0;
    }

    // otherwise we have not had our first dialog, get the link id.

    // this is the specific check
    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        sLinkId = 11;
        break;

    case 2:
        sLinkId = 12;
        break;

    case 3:
        sLinkId = 15;
        break;
    }

    if (sLinkId != 0)
    {
        if (gpstructMapLinkDynamicCurrent[sLinkId - 1].cStatus > 1)
        {
            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at what is now a T-intersection. A path south has opened up. #!00# talks to herself \"Oooh... so the traps open things as well as\"...\n\n#!00# is then distracted as there is something moving towards her position from the southern corridor. #!00# sighs \"So much for traps that open things being useful\"...\n\n#!00# looks over a the wall and notices that there is a torch stand attached to it. So she strides over, puts her torch in the stand, and heads back to the center of the T-intersection, and draws her sword just as a tentacle monster crawls into the T-intersection from the southern corridor.\n\nThe tentacle monster is huge. #!00# is not scared. #!00# smiles \"So how do YOU want to do this?.. Shall\"...\n\nThe tentacle monster interrupts #!00# by spraying her with some goop. #!00# just wipes it off and responds \"Normally you let ladies go first... but the last time I looked, I wasn\'t one... so I am going to let that slide\"...\n\n");
            if (iRet != 0) return iRet;

            // populate the values for this first monster
            gstructActStateOpponent.iConfidence = 999; // high confidence
            gstructActStateOpponent.iRage = 999; // high rage (fight)
            gstructActStateOpponent.iDesire = 999; // high desire (stay)
            gstructActStateOpponent.iHitPoints = 120; // low hit points
            gstructActStateOpponent.iFear = 0; // absolutely no fear
            gstructActStateOpponent.cActive = 1; // and the monster is active.

            // call the setup for the combat encounter actions.
            iRet = gamelogic04_scene1040 (0, cSubFlag + 1);
            if (iRet != 0) return iRet;

            // the intention is for combat mode to be forced, so don't let the caller
            //  populate navigation menu items.
            return -1;
        }
    }

    return 0;
}

//
// This is the ending dialog for the first monster encounter
//
// This function is not in the lookup array, and is meant to be called directly by the combat functions.
//
int gamelogic01_event_scene022a (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("The monster collapses in the T-intersection. #!00# decides that she isn\'t going to take any chances with such a fearsome opponent so she uses her sword to stab the monster\'s body, several times.\n\nAfter stabbing the monster a sixth time, #!00# notices that it is getting harder to thrust her sword into the monster\'s carcass. When she pulls it out, that is when she notices the blade of the sword has partially melted \"You have to be shitting me\"...\n\n#!00# then checks her armor and finds that it has also been damaged \"This is the pits, next time I will have to dodge more often... but\"... #!00# then looks down at her legs to see she is still knee deep in opaque white liquid \"So much for that idea\"...\n\nThe monsters clearly have an advantage in this environment.\n\n");
    if (iRet != 0) return iRet;

    // override the direction, because we don't know which way we are facing now.
    gstructActStateGlobal.cDirect = 0;

    return 0;
}

//
// act 1 blocked exit
//
int gamelogic01_event_scene023 (char cSubFlag)
{
    int iRet;
    short sLinkId = 0;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // this is the specific check
    switch (gstructActStateGlobal.sMapId)
    {
    case 1:
        sLinkId = 81;
        break;

    case 2:
        sLinkId = 83;
        break;

    case 3:
        sLinkId = 157;
        break;
    }

    // do NOT go any further if the LinkId is 0..
    if (sLinkId == 0)
        return 0;

    if (gpstructMapLinkDynamicCurrent[sLinkId - 1].cStatus == 1)
    {
        if (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount < 2)
        {
            switch (gstructActStateGlobal.sMapId)
            {
            case 1:
                iRet = mdialog_addToDialogWithSrchRep ("#!00# reaches what would be the end of a hallway. It would appear to be a dead end, except that there is a depression in the southern wall.");
                break;

            case 2:
                iRet = mdialog_addToDialogWithSrchRep ("#!00# reaches a T-intersection. However, there is a rather suspicious depression in the eastern wall.");
                break;

            default: // case 3:
                iRet = mdialog_addToDialogWithSrchRep ("#!00# reaches a turn. However, there is a rather suspicious depression in the eastern wall.");
                break;
            }
            if (iRet != 0) return iRet;

            iRet = mdialog_addToDialogWithSrchRep (" #!00# looks over the depression in the wall and notices that it is a different color to the walls inside the dungeon. \"Is this some sort of door... leading ");
            if (iRet != 0) return iRet;

            if (gstructActStateGlobal.sMapId == 1)
                iRet = mdialog_addToDialogWithSrchRep ("south");
            else
                iRet = mdialog_addToDialogWithSrchRep ("east");

            if (iRet != 0) return iRet;

            iRet = mdialog_addToDialogWithSrchRep ("?\"\n\n#!00# the looks down and notices that there is a miniature whirlpool in the surface of the opaque liquid near the depression. When she nears the depression, #!00# feels that there is a noticeable current below the surface. Checking the depression, she finds that there is a gap underneath the surface of the liquid.\n\n#!00# smiles \"That might lead to the stairs\".\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }
    else if ((gpstructMapLinkDynamicCurrent[sLinkId - 1].sVisitCount == 0) && (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount > 1))
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at what used to be a dead-end. The southern wall is gone, and the liquid is slowly moving through the southern passageway.\n\n");
            break;

        case 2:
            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at what used to be a T-intersection. The eastern wall is gone, and the liquid is slowly moving through the eastern passageway.\n\n");
            break;

        case 3:
            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives back at what used to be a turn. The eastern wall is gone, and the liquid is slowly moving through the eastern passageway.\n\n");
            break;
        }
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }

    return 0;
}

//
// act 2 first monster point
//
int gamelogic01_event_scene024 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.sAct2Monsters == 0)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# is walking along the hallway, when she notices the surface of the liquid is starting to ripple towards and not away from her. #!00# reaches for her sword, only to find it isn\'t there.\n\n#!00# then remembers that she does not have her sword anymore. She scrambles to get her only weapon, a spanking paddle, just as the tentacles of the monster appear above the surface of the liquid.\n\n#!00# quietly curses herself that she hasn\'t had time to put the lantern somewhere, when the monster sprays #!00# with it\'s goop and withdraws.\n\nWhile watching the monster scramble away through the liquid \"That was... unexpected... huh?\"\n\n#!00# starts to feel rather horny. #!00# sighs \"Horrible timing... okay\". #!00# wonders over to a wall of the corridor.\n\n\n[2 minutes later...]\n\nAfter successfully fingering herself to a climax while leaning against the wall, #!00# grabs the her lantern from the improvised hook that she had hung it on.\n\n");
        if (iRet != 0) return iRet;

        // increment the counter, this enables further encounters for act 2
        gstructActStateGlobal.sAct2Monsters++;

        // decrease Frigidity
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)3.431, (int)50);

        // set lust to an arbitrary starting value
        gstructActStateCharWilda.structL.iNum = 5;
        gstructActStateCharWilda.structL.fFraction = (float)0.194;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }

    return 0;
}

//
// act 2 monster step point
//
int gamelogic01_event_scene025 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gpstructActStateInventory[26].sCount != 0)
    {
        float fCompare;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# walks along a hallway, and notices that she has stepped on something that moved. Initially #!00# thinks that she just set off another trap, but then she feels the tentacles brush against her legs \"Crap\"...\n\n#!00# tries to dart away from the tentacles, but it isn\'t any easier for her to move in the liquid. Fortunately for #!00#, she isn\'t the only one caught off-guard. The tentacle monster that she accidentally wondered onto is just as surprised as she is.\n\nThe tentacle monster launches an all out spray attack first. #!00# is hit multiple times. Then the monster scampers off through the liquid.\n\n#!00#\'s libido is now skyrocketing. #!00# sighs \"Fingers aren\'t going to do this time\".\n\n#!00# staggers over to the wall of the hallway, while starting to search inside her backpack for the \"holy artifact\" that she picked up from the sanctuary.\n\n\n[4 minutes later...]\n\n#!00# ended up cuming 5 times while pleasuring herself with the dildo. In the end, she decided that the dildo was turning out to be so useful, that she might as well just leave it where it is.\n\nWith the dildo still lodged in her pussy, #!00# picks up the lantern.\n\n");
        if (iRet != 0) return iRet;

        // I don't bother incrementing the counter for an encounter here, but
        //  I do have to remove the "holy artifact" from the inventory, because
        //  Wilda is now using it.
        gpstructActStateInventory[26].sCount = 0;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;

        // first, rocket the lust sky high.
        actionstate_statAddition (&gstructActStateCharWilda.structL, (float)5000, gstructActStateCharWilda.structF.iNum + 1);

        // now decrease the lust hit..
        fCompare = (float)((float)gstructActStateCharWilda.structF.iNum / (float)2.1);
        actionstate_statSubtraction (&gstructActStateCharWilda.structL, fCompare, (int)1);

        // decrease Frigidity
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)4.762, (int)50);

        // decrease Stamina
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)2.381, (int)0);
    }
    // I don't need an alternative to this dialog.

    return 0;
}

//
// act 3 elbow with collapse
//
int gamelogic01_event_scene026 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount < 2)
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 2:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the south. #!03# looks along the collapsed southern pathway ");
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the east. #!03# looks along the collapsed eastern pathway ");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mdialog_addToDialogWithSrchRep ("\"Apologies, we cannot go this way\".\n\n#!00# replies \"Would it have been faster if we did?\"\n\n#!03# responds \"Yes, we are but lowly servants for our lord and master\".\n\n#!00# interjects \"Don\'t worry about it. Is there another way?\"\n\n#!03# replies \"There is\".\n\n#!00# continues \"Then we will go around it\".\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 2:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the south.\n\n");
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the east.\n\n");
            break;
        }
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// act 3 t-intersect with collapse
//
int gamelogic01_event_scene027 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount < 2)
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the north. #!03# looks along the collapsed northern pathway. ");
            break;

        case 2:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the south. #!03# looks along the collapsed southern pathway. ");
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the east. #!03# looks along the collapsed eastern pathway. ");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mdialog_addToDialogWithSrchRep ("#!00# asks #!03# \"Another shortcut?\"\n\n#!03# responds \"Not anymore\".\n\n#!00# sighs \"Well... there is nothing for us to do but go around it then\".\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 1:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the north.\n\n");
            break;

        case 2:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the south.\n\n");
            break;

        default:
            iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the east.\n\n");
            break;
        }
        if (iRet != 0) return iRet;
    }

    return 0;
}

//
// act 3 t-intersect with collapse2
//
int gamelogic01_event_scene028 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    // this is merely a comment, Crystal and Wilda are not going to have a conversation about this.

    switch (gstructActStateGlobal.sPosId)
    {
    case 62: // map 2 (62)
    case 69: // map 2 (69)
        iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the north.\n\n");
        break;

    case 82: // map 1 (82)
        iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the south.\n\n");
        break;

    default: // map 1 (73), and map 3 (123 & 164)
        iRet = mdialog_addToDialogWithSrchRep ("There is a collapsed pathway to the west.\n\n");
        break;
    }
    if (iRet != 0) return iRet;

    return 0;
}

//
// act 3 first monster point
//
int gamelogic01_event_scene029 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.sAct3Monsters == 0)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# do not venture far from the sanctuary when they encounter a lone tentacle monster.\n\nAs #!00# readies her spanking paddle, #!03# glances at #!00# \"Put that away, I will demonstrate how to handle this\". #!03# licks her lips. #!00# is surprised. #!03# is showing absolutely no fear.\n\n#!03# proceeds to put her spanking paddle inside her backpack, so #!00# decides that she will do the same. #!00# looks at #!03# \"So how do we do this?\"\n\n#!03# turns to look at #!00#, and tells #!00# what to do \"First, breathe in, then out, breathe in, then out\".\n\n#!00# finds herself staring at #!03#\'s rising and falling breasts. #!00# does not respond, but starts unconsciously breathing to the same rhythm as #!03#. #!03# is unconsciously fingering herself.\n\n#!03# continues \"That\'s it... just keep breathing... watching... learning\"...\n\n#!00# is still captivated by #!03#\'s jiggling nipples. #!00# starts unconsciously fingering herself as well.\n\n#!03# continues \"Good... there is nothing to be afraid of... nothing to harm us here... just pleasure\"...\n\n#!00# responds drowsily with a \"Yes\"...\n\nNeither #!03# or #!00# even look at the tentacle monster, which advances on the pair of them. The tentacles then proceed to wrap around both of the women, while penile head tentacles find their respective pussies.\n\nAs a tentacle impales #!00#\'s slit, the only thing that she can immediately think of is how good a real penis feels inside of her.\n\nMeanwhile, #!03# starts praying \"My lord and master... Cock... we are but slutty playthings for your enjoyment... Fill our wet pussies\"...\n\nThe tentacle monster then fills #!00#\'s and #!03#\'s mouthes, while humping away at their pussies. #!00# unconsciously licks and sucks the tentacle that is violating her mouth.\n\n\n[5 minutes later...]\n\n#!00# finally snaps out of her daze, to watch the tentacle monster run away. \"Wow... that really worked?\"\n\n#!03# looks at #!00# \"Of course it did\"...\n\n#!00# considers how easy it is for both her and #!03# to face and defeat the local tentacle monsters. #!00# thinks back to her first encounter \"The first one I faced, I killed\"...\n\n#!03# looks at #!00# \"Really?\"..\n\n#!00# is slightly perplexed, as she cannot recall how or why she would kill a tentacle monster.\n\n#!03# continues \"You must have did well for your first encounter with our master... Lord... Cock... My sopping wet snatch is always ready for your hot jizz\"...\n\n#!00# is concerned as #!03# seems to be slipping into her prayers again. However, #!03# quickly comes out of it.\n\n#!03# looks at #!00# \"And now you know for the next time\"...\n\n#!00# responds \"Yes\", with the same blank smile that is almost identical to the one that #!03# has.\n\n#!03# looks around the hallway and states \"We should depart... You still have your quest\"...\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;

        // increment the counter, this enables further encounters for act 3
        gstructActStateGlobal.sAct3Monsters++;

        // The other thing that happens is that Crystal and Wilda put away their weapons.
        // Crystal's weapon is just removed.
        gstructActStateCharCrystal.structW.iNum = 0;
        gstructActStateCharCrystal.structW.fFraction = (float)0;
        gstructActStateCharCrystal.sSlotW = 0;

        // Wilda has her's in her inventory
        // transfer the detail about the weapon to the inventory (it is definitely offset 5).
        gpstructActStateInventory[5].structEff.iNum = gstructActStateCharWilda.structW.iNum;
        gpstructActStateInventory[5].structEff.fFraction = gstructActStateCharWilda.structW.fFraction;
        gpstructActStateInventory[5].sCount = 1;

        // Then wipe out the item slot on Wilda
        gstructActStateCharWilda.structW.iNum = 0;
        gstructActStateCharWilda.structW.fFraction = (float)0;
        gstructActStateCharWilda.sSlotW = 0;

        // decrease Stamina
        actionstate_statSubtraction (&gstructActStateCharWilda.structS, (float)2.381, (int)0);
        actionstate_statSubtraction (&gstructActStateCharCrystal.structS, (float)1.752, (int)0);

        // increase Endurance
        actionstate_statAddition (&gstructActStateCharWilda.structE, (float)0.162, (int)6000);
        actionstate_statAddition (&gstructActStateCharCrystal.structE, (float)0.141, (int)6000);

        // increase the experience attributes
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)1.221, (int)6000);
        actionstate_statAddition (&gstructActStateCharWilda.structV, (float)0.916, (int)6000);
        actionstate_statAddition (&gstructActStateCharCrystal.structO, (float)1.176, (int)6000);
        actionstate_statAddition (&gstructActStateCharCrystal.structO, (float)0.943, (int)6000);

        // decrease Frigidity (slightly)
        actionstate_statSubtraction (&gstructActStateCharWilda.structF, (float)0.062, (int)24);
        actionstate_statSubtraction (&gstructActStateCharCrystal.structF, (float)0.052, (int)24);

        // increase Lust (slightly)
        actionstate_statAddition (&gstructActStateCharWilda.structL, (float)0.042, (int)gstructActStateCharWilda.structF.iNum);
        actionstate_statAddition (&gstructActStateCharCrystal.structL, (float)0.021, (int)gstructActStateCharCrystal.structF.iNum);
    }

    return 0;
}

//
// act 4 ginger encounter
//
int gamelogic01_event_scene030 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    if (gstructActStateGlobal.cGingerEncounter != 0)
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# returns back to where she originally encountered #!07#. #!07# is no longer here. #!00# looks around \"Where is she?\".\n\n#!00# spends about half a minute searching for any sign of #!07#, but decides that she is a grown adult, and she has her baby to keep her company, so it should not be a problem.\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        iRet = mdialog_addToDialogWithSrchRep ("#!00# can hear a low murmuring in the hallway. #!00# stops and listens. It is clearly a female voice, but she cannot recognize them. #!00# keeps walking.\n\nSuddenly the murmuring is clearer now. Straight ahead.\n\n#!00# stops walking and listens. She can hear what the voice is saying \"Ah... Fuck me... Fuck my cumdump pussy harder... Lord... Cock\"...\n\n#!00# smiles, as it sounds like a nun who is praying. #!00# licks her lips, in anticipation that the praying nun is not alone.\n\n\n[30 seconds later...]\n\n#!00# certainly found a nun, and she is definitely praying. The nun is on all fours, with her forearms and legs up to her thighs submerged in the white opaque liquid. She seems to be wearing some form of latex catsuit, with a hood. There are holes in her catsuit for her breasts, belly and genitals. Her swollen breasts and belly are dangling in the liquid.\n\nThe expression on the nuns face is one of pure bliss, as her eyes have partially rolled back into her head. The nun is yelling \"That\'s it... punish my pussy... Yes... Lord... Cock... More... Fuck my naughty pussy rough and hard... I am a masochistic sex slave for for you to FUUUCKKk\". The nun whips her head back and sits up. Breathing heavily.\n\n#!00# looks around. She can see no sign of a delightful monster to fuck, so she is wondering how the nun is able to pray so much. #!00# decides to wonder over to the nun.\n\n\n[1 minute later...]\n\nThe nun finally recovers enough to notice that #!00# is standing there. The nun looks up and down #!00# and asks \"Have you considered Hedonism?\"\n\n#!00# automatically replies \"I have. It feels really good\".\n\nThe nun grins even wider \"On a quest?\"\n\n#!00# replies \"Yes. I am #!00#\".\n\nThe nun response \"I am #!07#. Sorry, but I cannot offer you help with your quest right now\".\n\n#!00# cocks her head \"Not a problem, but why are you here?\"\n\n#!07# pats her swollen belly \"This little master will be ready to come out and fuck soon\". #!00# then notices that #!07#\'s belly shuddered. #!07# continues \"Ooooh... He is active again\". #!07# then looks at #!00#\'s belly \"Good luck with your little one\".\n\n#!00# replies \"Thank you. Do you need any help?\"\n\n#!07# responds \"No, but thank you for the offer. Ooooh... He is starting to... Fuck my pussy from the inside again\". #!07#\'s belly starts convulsing, and #!07# falls back on all fours. \"That\'s it... Punish my obscene fuck hole again\"... \n\n#!00# is curious, so she walks around to look at #!07#\'s butt. That is when she sees the small tentacles sliding in and out of #!07# from inside her pussy. #!00# looks on in wonder \"Wow\"...\n\n#!07# is starting to get into the sex with her tentacle monster child \"Lord... Cock... Fuck me more and more... Harder... No puny human dick can ever satisfy my ruined pussy... I belong only to YOUuuu\"... #!07# arches her back. Then keeps on having sex with her baby tentacle monster. Some of the small tentacles protruding from #!07#\'s pussy starts assaulting #!07#\'s gaping anus.\n\n#!00# pats her own swollen belly while staring at #!07# \"You are so lucky, being fucked by your baby so soon\". #!00# then looks down at her own belly \"I cannot wait till this one is ready to hatch\".\n\n#!00# decides that #!07# and her baby are in no immediate danger, so she continues walking past and away from them.\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;

        gstructActStateGlobal.cGingerEncounter = 1;
    }

    return 0;
}

//
// act 4 stairs back up to act 3
//
int gamelogic01_event_scene031 (char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the base of a staircase that is rising up out of the opaque liquid. The stone steps are rather large stone blocks that have been expertly crafted. This staircase is somewhat familiar, as #!00# can remember that she came this way with... #!03#... that\'s right... #!00# walked down these stairs with #!03#.\n\nHowever, these stairs lead up. #!00#\'s destination is down, so there is no point in using these stairs to go up.\n\n");
    if (iRet != 0) return iRet;

    iRet = mdialog_addToDialogWithSrchRep ("#!00# came from the west, and is facing east. This is a hallway, with known stairs leading up to the west, and a path to the east. However, #!00# is only going to go east.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("East", 1021, 2);
    if (iRet != 0) return iRet;

    // don't let the caller setup navigation, instead use what this has set.
    return -1;
}

//
// act 1 blocked exit (trigger7)
//
int gamelogic01_event_scene050 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("As #!00# walks to the end of the passageway, she hears an audible clicking noise, then the sound of stone sliding against stone from behind her. #!00# looks around and wonders to herself \"Did I just... set off another trap?\"\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger2
// Map1: de
// Map2: el
// Map3: de
//
int gamelogic01_event_scene051 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("As #!00# is walking along the passageway, she hears something that sounds like steel smashing against stone, followed by stone sliding against stone in the distance. #!00# calmly looks around to see if there are any opponents who have suddenly shown up. After about 10 seconds, #!00# is satisfied that there is no danger here.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger3
// Map1: de
// Map2: el
// Map3: de
//
int gamelogic01_event_scene052 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# hears the sound of stone sliding against stone from a nearby wall. #!00# patiently waits, to see if there is any danger that is going to show up. #!00# decides to draw her sword.\n\n\n[1 minute later...]\n\nAfter waiting for a while, #!00# decides that she is wasting time, and she should keep moving. #!00# puts her sword away.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger4
// Map1: el
// Map2: el
// Map3: el
//
int gamelogic01_event_scene053 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at a turn in the a passageway, when she notices that the liquid is rippling. #!00# grabs her sword to get ready for another monster encounter when she hears the sound of stone sliding against stone in the distance.\n\n\n[1 minute later...]\n\n#!00# puts her sword away. There is no immediate danger here.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger5
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene054 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("Just as #!00# arrives at the end of a passageway, she is startled by the sound of the wind blowing. As #!00# readies her sword for an impending attack, she hears stone thumping against stone in the distance.\n\n\n[1 minute later...]\n\nNo monsters showed themselves, so #!00# puts her sword away.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger6
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene055 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# hears something that sounds like gurgling from the wall next to her, then the sound of stone sliding against stone in the distance. #!00# looks around to see if there is anything out of place. No monsters appear, so #!00# decides that she should keep moving.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 1 trigger7
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene056 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# is walking along the partially submerged passageway, when she she almost trips up on something. #!00# looks around to see if anything is out of place when she hears the sound of sound of stone sliding against stone in the distance.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger1
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene061 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# reaches a dead-end. #!00# sighs, and is distracted by a popping sound. She readies her paddle, and hears a faint banging sound in the distance.\n\n\n[1 minute later...]\n\n#!00# relaxes her posture. A monster did not appear.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger2
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene062 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# reaches the end of the passageway, which is a dead-end. As she thinks to herself that this path was pointless and that she will have to turn back, she can hear the sound of stone grinding against stone in the distance. She briefly considers readying her paddle, and looks around. The surface of liquid is still and there are no monsters bearing down on her. #!00# decides to keep moving.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger3
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene063 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the end of a corridor, when there is a loud bang. #!00# grabs her paddle and readies herself for another monster when she hears the sound of stone sliding against stone in the distance.\n\n\n[1 minute later...]\n\nNo monsters appeared, so #!00# decides to that maybe she should keep moving.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger4
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene064 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# stops at the end of the passageway. This isn't a turn, this is a dead-end. #!00# looks around and notices something hanging down the wall. She looks over it and realizes that it is a tentacle hanging out of a small hole in the wall. Startled, #!00# steps back and readies her paddle. As she does, the tentacle quickly pulls back into the hole, and there is a banging sound on the other side of the wall. #!00# remains on alert for the following attack.\n\n\n[1 minute later...]\n\n#!00# is still waiting for the monster to attack, but she is staring at what is an empty hole in the wall. #!00# hears the sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\n#!00# relaxes her posture. The monster did not attack, and the small hole in the wall is still empty.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger5
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene065 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the end of a passageway, when she hears a loud clapping sound. #!00# readies her paddle for the monster attack as she hears the sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\nAfter waiting for a monster attack that did not happen, #!00# decides to relax. She decides that she should get going.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger6
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene066 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the end of a rather noisy passageway. It sounds like there is a waterfall on the other side of the wall. Intrigued, #!00# checks the wall, when the sound suddenly stops \"That was weird\"...\n\n#!00# decides to keep checking the wall.\n\n\n[1 minute later...]\n\nAfter checking the 3 walls of the dead-end, #!00# decides that there isn't anything of interest here, and she should get going.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger7
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene067 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# arrives at the end of a pathway, which is a dead-end. While looking around to see if there are any monsters hiding in this corner of the dungeon, a large rock falls down behind her and splashes into the liquid. #!00# immediately draws her paddle, ready to face an opponent. While waiting for the monster to attack, #!00# hears stone grinding sounds from the walls around her.\n\n#!00# decides that it isn't safe to stay in this corridor.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger8
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene068 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("Just as #!00# arrives at the end of a passageway, there is a shudder from the walls. #!00# draws her paddle expecting an attack.\n\n\n[1 minute later...]\n\n#!00# decides to relax, and was about to put the paddle away when walls shudder again. While #!00# contemplates if she should stay and fight or exit from this dead-end, the walls shudder again.\n\n#!00# checks around her, and comes to the conclusion that maybe it isn't safe to stay here.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 2 trigger9
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene069 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("As #!00# arrives at the end of a passageway, there is a groaning noise in the distance. Startled, #!00# draws her paddle, and readies herself for the attack. While waiting there is a sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\nAfter waiting patiently for a monster to appear, #!00# decides that there is no immediate threat and that she should get going. #!00# puts the paddle away.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 3 trigger1
// Map1: el
// Map2: el
// Map3: de
//
int gamelogic01_event_scene071 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            if (gstructActStateGlobal.sMapId == 3)
                iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the end of a corridor.");
            else
                iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at a turn in the pathway.");
            if (iRet != 0) return iRet;

            iRet = mdialog_addToDialogWithSrchRep (" #!03# calls out to #!00# \"Just a moment\".\n\n#!00# asks #!03# \"What is it?\", and watches #!03# walk over to a wall, and place her hand on a stone that is jutting out of it.\n\n#!03# looks at #!00# \"Shall I?\"\n\n#!00# responds \"Why not?\"\n\n#!03# pushes the stone in, there is an audible clunk followed by a gurgling sound from the wall next to the stone. In the distance there is the sound of stone grinding against stone. #!03# looks at #!00# \"There, a door should be open now\".\n\n#!00# thinks to herself that it is handy to have #!03# along.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 3 trigger2
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene072 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the end of a corridor. There is a tentacle hanging out of a hole in the wall. #!00# licks her lips, but is then surprised when #!03# just walks past her, over to the tentacle.\n\n#!03# lightly grabs the tip of the tentacle, bends down and kisses it. The tentacle snakes back into the wall, and there is a banging sound from behind the wall. #!03# turns to look at #!00# \"Please wait\".\n\n#!00# looks dumbfounded \"For?\"\n\nThere is a grinding sound behind the wall, followed by another grinding sound off in the distance. #!03# looks at the hole in the wall and blows a kiss, then turns to #!00# \"A door should be open now\".\n\n#!00# responds \"Thank you, that is rather useful\".\n\n#!03# replies \"No need... This is all part of the service to my lord... Cock\"...\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 3 trigger3
// Map1: el
// Map2: el
// Map3: el
//
int gamelogic01_event_scene073 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at a turn in the pathway. While #!00# considers if they should go back the way they came or follow the pathway, she is interrupted by #!03# \"Can I... have your assistance?\"\n\n#!00# looks at #!03# \"Sorry?\"\n\n#!03# continues \"I am going to need your help with this\".\n\n#!00# responds \"Okay... what you need help with?\"\n\n#!03# replies \"Just follow my lead\", then she walks over to #!00# and kisses her.\n\n#!00# is caught up with the moment to not go along with it.\n\n\n[1 minute later...]\n\nWhile #!00# and #!03# are fingering each other, there is an audible click in the walls. #!03# pulls her tongue out of #!00#'s mouth, when the sound of stone sliding against stone starts, and asks \"Shall we continue... Or, shall we continue?\"\n\n#!00# replies \"Both work for me\", then starts kissing #!03# again.\n\n\n[2 minutes later...]\n\n#!03# and #!00# are standing in the middle of the corridor. #!03# looks at #!00# \"Now we can continue\".\n\n#!00# replies \"I agree\".\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 3 trigger4
// Map1: el
// Map2: el
// Map3: el
//
int gamelogic01_event_scene074 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at a turn in the corridor. #!03# calls out to #!00# \"Shall I?\"\n\n#!00# looks at #!03# \"Is there another door?\"\n\n#!03# nods \"Yes\", then walks over to a wall, and clenches her fist and bangs it. A sound somewhere between flatulence and belching fills the corridor.\n\n#!00# just stands there waiting for something else to happen. #!03# closes her eyes listens. #!03# breathes in and out, then thumps the wall twice again. There are smacking sound from the other side of the wall, and #!03# opens her eyes.\n\n#!03# looks at #!00# \"We should go now\".\n\n#!00# responds \"Okay\", then hears the sound of stone grinding against stone in the distance.\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}

//
// act 3 trigger5
// Map1: de
// Map2: de
// Map3: de
//
int gamelogic01_event_scene075 (char cSubFlag)
{
    int iRet;
    int iLinkId;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
    if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
    {
        if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 1)
        {
            gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 2;

            if (gcDebugFlag != 0)
            {
                char szWorking[80];

                sprintf (szWorking, "debug: LinkId %d opened\n\n", iLinkId);

                iRet = mdialog_addToDialogWithSrchRep (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mdialog_addToDialogWithSrchRep ("#!00# and #!03# arrive at the end of the pathway, which is a dead-end. #!00# sighs, and looks at #!03# \"I guess we need to turn back\".\n\n#!03# saunters past #!00# over to a part of the floor, stops and turns towards #!00# \"Not just yet\".\n\n#!03# closes her eyes and lightly jumps. There is a splash of liquid, not just from #!03#\'s movement, but there are ripples coming from the walls. #!00# looks around as there are a series of loud bangs from the other side of each of the 3 walls of the dead-end.\n\nThe bangs are followed by the sound of stone sliding against stone in the distance. #!03# looks at #!00# again \"There, it is done, we can continue now\".\n\n#!00# responds \"Great\".\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}


