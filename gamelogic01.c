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

    iRet = mutils_addToDialogBuffer ("> Start new game\n\nWilda is resting. She is inside her tiny shack on the outskirts of town. For a mercenary swordswoman such as herself, an extended rest is a luxury. However, after the events of last night, Wilda is going to to be living this life of luxury a bit more often. The light bruising on her left lower leg is still causing her some slight discomfort, however that is nothing compared to what Wilda did to the 5 other guys.\n\nAfter a lack of real jobs from the mercenary guild, Wilda wasn\'t really interested in maintaining her membership. There is real work that pays rather well. But, her guild wasn\'t giving those good assignments to her. Wilda wanted out of the guild. To allow for her departure, the guild-leader wanted a payment and a favor. A \'sexual\' favor. One thing is for certain, the mercenary guild isn\'t going to be sending anymore work her way. The language that the guild-leader used after Wilda\'s right knee came in contact with his testicles was a clear indication. Her actions afterwards ensured that there would be no reprieve.\n\nAt least Wilda didn\'t use her sword and kept to bare fists. She did pay for the damage to tavern. However, the guild-leader\'s teeth were not part of that deal. There is the likelihood of revenge attacks, but that won\'t be for a day at least. The guild-leader\'s 4 companions are barely able to walk.\n\nWilda is surprised... pleasantly surprised... when she hears footsteps outside of her shack. At her home, she does not have to hold back. Wilda grabs her sword and opens the door of the shack.\n\nThe first thing that she sees is a solitary cloaked figure approaching her home. Wilda assesses the that individual is carrying no weapons, long before she identifying that they are a woman.\n\nThe cloaked woman sees Wilda and continues walking towards the open door of Wilda\'s shack. When the woman reaches Wilda, she asks a question \"Have you considered Hedonism?\"\n\n\n[5 minutes later...]\n\nWilda is surprised \"400, up front?\"\n\nThe cloaked nun, Amber, nods her head \"yes, 20 percent in advance\"...\n\nAmber hands a bag of gold to Wilda. Wilda counts it as quickly as she can. It looks like it is all there \"400 gold\"...\n\nWilda cannot believe it, she was sent an actual REAL job by the stupid guild. If 400 is 20 percent... then, final payment is 1600... all for an item retrieval mission. Normally Wilda would check the job with the guild. However, they would normally want their commission for the job referral. After last night, it would be rather \'normal\' for them to assign the job to someone else and demand ALL of the pre-payment. Screw that.\n\nWilda looks at Amber \"Are you fine with the task commencing so late?\"\n\nAmber replies \"It is our fault that we did not come earlier. Your guild gave us your name last week. It took time to acquire the fee\".\n\nWilda is concerned. Clients who have problems in reserving gold for the pre-payment usually cannot make the final payment at the end of the job. She has been caught out by this before. However, Wilda is more than interested because the pre-payment for this mission alone is more than the total for most jobs that she has been recently working. Considering her situation, Wilda decides to take the risk.\n\nThere are two other things that are bothering Wilda. The first is that Amber\'s expression is sort of a constant smile while staring straight ahead. While Amber is a true believer in her religion, whatever it is, she is way too happy. Sometimes it is as if Amber isn\'t looking at Wilda at all. The second is that while Amber has been talking to Wilda the entire time, Amber has been relentlessly rubbing her own clitoris through the fabric of her cloak.\n\n");
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
            iRet = mutils_addToDialogBuffer (">Ignore what Amber is doing\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda decides to ignore the fact that Amber is currently slicking herself in front of Wilda. Wilda decides that she is going to try to concentrate the job, and not on the messenger. Wilda tries asking Amber \"So... will you be able to provide\"...\n\nHowever, Wilda is interrupted by Amber, who seems to be focusing on something else \"Mmmm... that\'s it my lord... fill me up... ravage me\"...\n\nWilda is perplexed. Amber seems to be talking to someone else... but it isn\'t clear as to whom Amber is talking to. Wilda inquiries \"Are you... all right?\"\n\nAmber, still in her temporary dream-trance, is concentrating on something else \"More... I am but a lowly slut who wants her cummies... My lord... Cock... YESSsss\"...\n\nAmber moans loudly and her body shakes. Wilda briefly decides to look around to see if there is anyone else watching Amber\'s lewd show. After finding no one else, Wilda looks at Amber.\n\nAmber\'s eyes are open and she is looking at Wilda again. Amber says to Wilda \"Sorry, but you seem to be distracted\".\n\nWilda thinks about it and decides to just ignore Amber\'s little display \"My apologies... I was just thinking... I am going to need directions\"...\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 1;

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Glance at the Amber\'s crotch, while she is fingering herself\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda\'s gaze wonders down to Amber\'s crotch for a little bit. Wilda then realizes that she is staring at Amber pleasuring herself for too long, so she quickly looks at Amber\'s face.\n\nAmber grins \"Where are you looking?. My cunny is... down there\"...\n\nWilda is surprised by Amber\'s statement \"Eh?\"..\n\nAmber then licks her lips, closes her eyes, and continues stroking herself \"In the name of my lord... Cock... Bless us with your holy milk... Amen\".\n\nAmber then moans and her body shakes. Yet, she still manages to remain standing. Before Amber opens her eyes and looks at Wilda, Wilda glanced down at Amber\'s crotch and notices the dampness spreading from where Amber\'s hand is clearly still pinching her own clitoris through the fabric of her cloak.\n\nWilda looks at Amber\'s face again and Amber opens her eyes. Wilda asks \"Are you... okay?\"\n\nAmber looks at Wilda, with the same smile as before \"Your concerns are unwarranted... as I am but a lowly servant of my lord... Cock\"...\n\nWilda does not have to even look at Amber\'s right hand to know that Amber is pleasuring herself again. Wilda briefly considers the fact that this is wasting time, and Wilda should be getting on with the job.\n\nWilda asks Amber \"Didn\'t you mention something about a map?\"\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 2;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Ask Amber what is she doing\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda sighs and starts to ask \"What in the name of creation are you\"... but is interrupted by Amber.\n\nAmber just blurts out \"My lord... Cock... I am but a lowly cumdump... Thank you for the sperm... Amen\".\n\nAmber then moans and her body shakes. Wilda just stands there dumbfounded, unsure about how to react to Amber\'s last statement. Surprisingly, Amber did not fall down.\n\nAmber opens her eyes, tilts her head a little to the right and talks to Wilda, while still stroking herself \"Is everything okay?\"\n\nWilda quickly glances down at Amber\'s right hand, at the wetness around Amber\'s crotch, then back at Amber\'s face. Wilda responds \"Everything is fine... now... can we cover the details of where I am going?\"\n\n");
        if (iRet != 0) return iRet;

        // set the map id off of this.
        gstructActStateGlobal.sMapId = 3;

        break;

    }

    iRet = mutils_addToDialogBuffer ("\n[2 hours later...]\n\nWilda received a map from Amber, and an armband. Wilda is to equip the armband before entering the dungeon at the destination. The armband is made out of rubber, but apparently it is meant to indicate that Wilda is a \'sanctioned servant\', whatever that means. Apparently there are other nuns still hiding at the site in \'sanctuaries\', who will provide assistance to Wilda. That could be useful.\n\nAmber also gave Wilda something she called a \'holy artifact\', which was inside small long box. Wilda took a look inside the box to see a black rubber dildo. Apparently, it serves some important purpose for the mission, but Amber could not tell Wilda what it was. Wilda asked if Amber could confirm the artifact, but Amber stated that only Wilda was allowed to look at the contents of the box.\n\nAmber then departed from Wilda\'s shack, but not without stopping 3 times, to finger herself to a climax each time she paused. After watching Amber cum her brains out and not fall over for the third time, Wilda decided to ignore Amber and to start preparing for the job.\n\nWilda\'s first stop is the local item store, as she is in need of some equipment upgrades. Wilda is standing outside the door of the shop. \n\nAs much as she would like to shop elsewhere, this is the best place for her to buy stuff. However, the guy who runs it, Popper, is a bit too friendly with Wilda. As much as Wilda would like to go elsewhere, his wares are of genuine exceptional quality, while at a low price.\n\nWilda sighs, takes a breath and opens the door of the shop. Popper immediately calls out \"Wilda-baby... come in... come in\"...\n\nWilda steps into the shop and closes the door behind her. She then turns to look at Popper \"I am after\"...\n\nPopper immediately grabs a steel-platemail under-bust corset off the wall behind him and shows it to Wilda \"What about this Eh?\"..\n\nWilda takes just one glance at it \"HELL No\"...\n\nPopper grins \"You cannot blame an old fart for wanting to have a bit of fun. At 2000 gold, I think this would be a bit too much. Besides, this is a special order, you can\'t have it\".\n\nWilda sighs, as she cannot believe that someone would pay 2000 gold for such an impractical piece of armor.\n\n\n[10 minutes later...]\n\nWilda raises an eyebrow \"Only the one pack of five?\"\n\nPopper puts down the batch of \'stamina elixirs\' and tells Wilda \"There has been a recent run on these lately. Someone, that both of us know, bought the rest... Nice job on his face, by the way\".\n\nWilda responds with a smile \"Oh, really\"...\n\nPopper looks at the clothing items table \"So, which ones do you want?\"\n\nWilda looks around the room and focuses on the swords on the wall \"Do you have something better than my iron-fang?\"\n\nPopper responds \"Expecting to get into fight are we?.. it is not as if the guild is sending you anymore work\".\n\nWilda just looks at Popper and smiles. She has no intention of telling him that she just landed a good job.\n\nPopper sighs \"Well... Ok... if you are not going to consider the Lolita leather babydoll, the Leather underbust corset, or the Kick-ass bronze high-heels, which I went through all of that effort to pick out for you, then I might as well show you a decent blade to consider\".\n\nWilda sighs. Popper\'s tastes sometimes lead to equipment that is horribly impractical.\n\nPopper walks over to the bin of swords by the counter, searches through it, and pulls out a single sword and walks back to the counter with it. Wilda exclaims \"You kept it over there?\"\n\nPopper responds \"If I left the decent stuff out on display, some thief will take a liking to it. What you see up there is ceremonial shit. For show only, no real value as actual weapons. Now this... this is the tempered steel version of your iron-fang\".\n\nWilda inquires \"Don\'t you have any better?\"\n\nPopper replies \"Not for your price range\".\n\nWilda responds \"I didn\'t give an amount\".\n\nPopper puts the sword on the counter and looks at Wilda \"You didn\'t have to. You rejected the steel-plate amour, saying it was too expensive. You are not going to be able to afford an Aredrite blade\".\n\nWilda sighs and looks at the items on the table.\n\n");
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
        sprintf (szWorking, "Wilda has no gold pieces.\n\n");
    else if (gpstructActStateInventory[1].sCount == 1)
        sprintf (szWorking, "Wilda currently has 1 gold piece.\n\n");
    else
        sprintf (szWorking, "Wilda currently has %d gold pieces.\n\n", (int)gpstructActStateInventory[1].sCount);

    iRet = mutils_addToDialogBuffer (szWorking);
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
            iRet = mutils_addToDialogBuffer (">Stamina elixr 5 pack for 50 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda glances at the pack of 5 \'stamina elixirs\', and then at Popper \"I will take those\".\n\nPopper grins, and responds \"The usual 50 gold for one pack of 5 quick orgasms\".\n\nWilda sighs, and holds back from berating Popper about calling them that. She knows what the side effects of the things are like. Wilda counts 50 gold pieces and gives them to Popper. Popper hands over the pack of 5 vials, which Wilda puts inside her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 50;
        gpstructActStateInventory[2].sCount += 5;

        break;

    case 2:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Steel double edged sword for 300 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda carefully looks over the steel sword \"How much for the steel blade?\"\n\nPopper replies \"300\".\n\nWilda nods her head, picks up the sword and looks along either edge. It is a good weight.\n\nPopper adds \"If you want to swing it around, I suggest you step outside\"...\n\nWilda smiles at Popper \"I\'ll take it\", then counts out 300 gold and hands it over to Popper. Popper quickly recounts the gold and nods his head. Wilda puts the sword into her backpack.\n\nPopper adds \"I have another sword that I can stick into your sheath, if you have the time\".\n\nWilda sighs, and responds \"Not today\".\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 300;
        gpstructActStateInventory[4].sCount = 1;
        gpstructActStateInventory[4].structEff.iNum = 127;
        gpstructActStateInventory[4].structEff.fFraction = (float)0.428;

        break;

    case 3:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Iron demi-gauntlets with chain-mail gloves for 180 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda takes interest in the new demi-gauntlets. She picks up the left one with her right hand, and compares it to her existing leather demi-gauntlet on her left hand.\n\nPopper looks at Wilda \"I can get those with satin instead of leather or chain... Just say the word and I can get it done\".\n\nWilda looks at Popper with a raised eyebrow \"Satin?\"\n\nPopper responds \"Sure... And if you model them for me, I will give them to you for the same 180 as those chain ones\".\n\nWilda frowns \"Satin won\'t offer much protection will it!\"\n\nPopper replies \"Heh... it isn\'t about protection... it is about being SEXY... Especially when it is all you are wearing\"...\n\nWilda takes a deep breath, and counts out 180 gold pieces \"I will just have these ones today\".\n\nPopper adds \"Meaning you are interested in the satin ones then?\"\n\nWilda replies \"No\", then hands over the 180 gold pieces.\n\nPopper recounts the 180 gold pieces while Wilda puts the pair of new demi-gauntlets into her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 180;
        gpstructActStateInventory[18].sCount = 1;
        gpstructActStateInventory[18].structEff.iNum = 80;
        gpstructActStateInventory[18].structEff.fFraction = (float)0.852;

        break;

    case 4:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Leather combat boots, with protruding steel spikes for 150 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda looks at the new pair of leather combat boots \"You said 150 gold for these, right?\"\n\nPopper responds \"Yes... Here is a thought\", Wilda looks at Popper while he continues \"Those heels are awfully low, so I was thinking\"...\n\nWilda interjects \"I will take them as they are\", and starts counting 150 gold pieces.\n\nWilda hands the gold to Popper. Popper recounts the gold, then mutters \"Spoilsport\".\n\nWilda puts the pair of new leather boots into her backpack.\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 150;
        gpstructActStateInventory[14].sCount = 1;
        gpstructActStateInventory[14].structEff.iNum = 78;
        gpstructActStateInventory[14].structEff.fFraction = (float)0.216;

        break;

    case 5:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Buy Leather thong leotard, with iron plating for 170 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda looks at the leather leotard with the iron plating \"Didn\'t you say 170 for this?\"\n\nPopper shakes his head \"Really... If you wanted leather, you should have gone with the babydoll, or at least the corset\".\n\nWilda looks at Popper \"Neither of those have actual plating on them\".\n\nPopper responds \"I could have the plating added\".\n\nWilda replies \"Neither of them cover me up properly\".\n\nPopper continues \"That is the best part about both of them... You know\"...\n\nWilda sighs, and starts counting the 170 gold pieces. Wilda looks at Popper and hands over the gold.\n\nPopper recounts the gold, and nods his head \"Okay, but seriously, I could get it done\"...\n\nWilda responds \"Don\'t bother\", puts the iron plated leather outfit inside her backpack, and adds \"This will do\"...\n\n");
        if (iRet != 0) return iRet;

        gpstructActStateInventory[1].sCount -= 170;
        gpstructActStateInventory[7].sCount = 1;
        gpstructActStateInventory[7].structEff.iNum = 65;
        gpstructActStateInventory[7].structEff.fFraction = (float)0.126;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">Buy Chainmail bikini set for 220 gold\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Wilda looks at the chainmail bikini, and sighs.\n\nPopper glances at the bikini and looks at Wilda \"Oh yes... you have class, there are many benefits to this outfit... and many possibilities... with a few alterations\"...\n\nWilda interjects \"How much?\"\n\nPopper continues \"I could make the top a peak-a-boo... and the bottom\".\n\nWilda interjects again \"Give me a price... for it as it is\".\n\nPopper sighs \"220\".\n\nWilda looks over the chainmail outfit again \"220... sold\", and starts counting gold pieces. Wilda hands the gold over to Popper who recounts it.\n\nPopper nods his head \"Done\"... Wilda puts the chainmail outfit into her backpack.\n\n");
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
            iRet = mutils_addToDialogBuffer (">Not interested in anything\n\n");
            if (iRet != 0) return iRet;
        }
        iRet = mutils_addToDialogBuffer ("Popper sighs and looks at Wilda \"Really, you don\'t want to buy anything?.. You are such a tease\".\n\nWilda briefly smirks, then walks out of the item shop.\n\n");
        if (iRet != 0) return iRet;

        break;

    default:
        if (cSubFlag == 0)
        {
            iRet = mutils_addToDialogBuffer (">That is enough for today\n\n");
            if (iRet != 0) return iRet;
        }

        if (gpstructActStateInventory[1].sCount == 407)
        {
            iRet = mutils_addToDialogBuffer ("Popper looks at Wilda \"Thank you for your patronage\".\n\nWilda walks out of the item shop.\n\n");
            if (iRet != 0) return iRet;
        }
        else
        {
            iRet = mutils_addToDialogBuffer ("Popper looks at Wilda \"Thank you, now if you would not mind stripping down to your birthday suit, you can reequip with your purchase\".\n\nWilda does not even bother looking at Popper, and starts to walk out of the item store \"In your dreams\"...\n\nPopper responds \"Thank you for the mental images that I will jerk off to tonight, and take care... It\'s a rough world out there\".\n\n");
            if (iRet != 0) return iRet;
        }

        break;
    }

    iRet = mutils_addToDialogBuffer ("\n[That evening...]\n\nWilda decided to stay at home and rest after visiting the item shop, and prepare for the job. During the that evening, the guild-leader and another two of his lackeys dropped by to visit. Wilda beat the 3 of them up. Wilda was nice enough to give the guild-leader his teeth back, which he gratefully swallowed while Wilda had him in a choke-hold. She let his 2 friends carry his limp body off afterwards.\n\n\n[The next day...]\n\nIn the morning Wilda left her shack, knowing that it would most likely be ransacked by the time that she returns. Oh well, it is about time that she moved. Wilda spent the entire day traveling to the village next to her final destination. She stayed overnight in an inn for 3 gold pieces.\n\n\n[The following day...]\n\nShe arrived at her destination the middle of the next day, checked out the entrance to the temple in the afternoon. Wilda decided to find an inn for an overnight rest before starting the job the next morning. She stayed overnight in an inn for 2 gold pieces.\n\n\n[The following morning...]\n\nWilda woke up in her room in the inn. Wilda decides it would be better to re-equip at the inn, rather than in the dungeon.\n\n");
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

    iRet = mutils_addToDialogBuffer ("\n[30 minutes later...]\n\nWilda returned back to the destroyed temple. Confirmed the map details again. The map is specific, clearly showing the entrance to the temple. Wilda finds it intriguing that the entrance to the temple is so far away from the actual temple itself, but she has seen stranger hiding spots for treasure room entrances. Her hired goal isn\'t what is inside the temple, but its treasure room anyway.\n\nWilda isn\'t here to pray. It is not as if the monsters who destroyed this place were either. Wilda looks inside the dark entrance. No light. Wilda came prepared for that. She extracts a torch from her backpack and lights it.\n\nWilda then casually walks into the entrance of the dungeon. There is a strange smell in the air, but all dungeons smell musky.\n\n\n[1 minute later...]\n\nStairs. Going down. The smell is stronger.\n\n\n[1 minute later...]\n\nAt the bottom of the stairs. No only is the air RANCID, but this place has some kind of water seepage problem. At the end of the stairs, Wilda is standing ankle deep in what appears to be some kind of white opaque liquid. The stairs end at a corner. Wilda turns right and sees a corridor in front of her.\n\n\n[1 minute later...]\n\nAt the end of the corridor, left...\n\n\n[30 seconds later...]\n\nAt the end of a shorter corridor, right...\n\nThe liquid is starting to get higher, as the corridor is sloping downwards.\n\n\n[2 minutes later...]\n\nWilda is approaching what appears to be a T-intersection.\n\nWilda is walking slower now, because she up to her knees in this white opaque liquid. It isn\'t slowing her down too much, but Wilda does have concerns if she has to start swimming in it. It would not be the first time that Wilda has had to turn back from completing a job because the route to the treasure room was completely flooded.\n\nThe air is moist and drops of liquid are occasionally dripping from the ceiling.\n\nWilda continues walking to the center of the T-intersection when she feels something crunch under her foot.\n\nWilda does not have time to find the \'crunch\' strange when she hears stone grinding against stone, back along the corridor \"What was that?\"..\n\nWilda rushes back along the corridor.\n\n\n[1 minute later...]\n\n\"Drat\"...\n\nWilda is staring at a stone slab, which has sealed off the corridor leading out of the dungeon.\n\n\"They had to make it difficult\"...\n\nIt has become obvious that Wilda triggered a submerged switch of some kind back at the T-intersection. Wilda has experienced dungeons with pressure traps in the floors before, and other dungeons that were flooded. It never occurred to Wilda that she would ever come across a flooded dungeon where the floor traps were still active. After all, one of the methods of defeating a floor trap is to flood the dungeon.\n\nWilda sighs, and trudges through the white liquid back towards the T-intersection.\n\n\n[2 minutes later...]\n\nWilda arrives back at the T-intersection. She uses her field compass, which is attached with a chain around her neck, and orients herself.\n\n");
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

    iRet = mutils_addToDialogBuffer ("\n[?? years later...]\n\nA naked pile of human female flesh wakes up in a clearing. For the first time in many years she is able to use her eyes. She looks around, unfamiliar with her surroundings. She vaguely remember the thing called \'the sun\', but her past memories are very distant.\n\nFor as long as she can remember, she has had every orifice of her body violated by tentacles, and now, every single orifice of her body is prolapsed. She is a spent vessel, released from her long servitude now that she has outlived the usefulness of her own womb.\n\nSomehow, the mind broken figure of the warrior who was once known as Wilda, staggers to her feet and starts slowly walking towards a nearby village.\n\n\nIt will not be long before she dies at the hands of other, terrified, humans.\n\n(bad) END.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
}

//
// This is the good ending #1 dialog
//
int gamelogic01_scene1012 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer ("\n[2 years later...]\n\nNatasha is resting inside her tiny shack on the outskirts of town. While she is a mercenary swordswoman, decent jobs have not been as frequent as she hoped recently. It does not help that the mercenary guild is run by a bunch of jerks who really seem to have a thing against female mercs.\n\nEspecially the guild-leader. Natasha\'s nickname for him is \'gummy\'. That asshole is constantly saying that he will give Natasha a preference if she sucked his cock. Someone should just beat that pile of shit up and teach him a lesson.\n\nWhile Natasha is pondering wanton bodily harm to the guild-leader, there is a knock on the door of her shack. Distracted from the idea of breaking both of the guild-leader\'s arms, Natasha stands up and opens the door of her shack.\n\nThe first thing that she sees is a nun wearing a cloak.\n\n\nWilda asks Natasha \"Have you considered Hedonism?\"\n\nEND.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
}

//
// This is the good ending #2 dialog
//
int gamelogic01_scene1013 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer ("\n[1 year later...]\n\nWilda and Daisy have just finished praying in the entrance of one of the sanctuaries. For Daisy, this is the end of a 8 day long prayer session.\n\nDaisy turns to her junior and asks \"Sister Wilda, did anything of note happen while I was praying to our lord and master?\"\n\nWilda nods \"Yes, Sister Daisy. We have a \'sanctioned servant\' resting inside the room of the \'holy mist\'. Her name is Jade\".\n\nDaisy replies \"Oh... Is this the one that Sister Trixie took in?\"\n\nWilda nods \"Yes, Sister Daisy, she is\".\n\nDaisy responds \"Our lord and master will be most pleased. We must continue her indoctrination. Prepare the \'holy juices\' and the butt-plug. I will personally teach her the joys of being an obedient cumdump\".\n\nWilda replies \"Yes, Sister Daisy. I will prepare those items right away\".\n\nAs Wilda saunters off, Daisy watches the junior nun\'s swaying butt. Wilda is turning into a fine nun of the order.\n\nDaisy then lightly massages her swollen belly. It will be about a month before the young master in Daisy\'s belly is born. After that happens she will accompany this latest \'sanctioned servant\' to the next sanctuary, and ensure that Jade\'s guidance as a holy sex slave is fulfilled.\n\nDaisy remembers with joy the times that she was shown by her senior, Crystal, how to educate \'sanctioned servants\'.\n\n\nAnd now... educating \'sanctioned servants\' is Daisy\'s task.\n\nEND.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
}

//
// This is the good ending #3 dialog
//
int gamelogic01_scene1014 (int iSubSceneId, char cSubFlag)
{
    int iRet;

    if (cSubFlag > MAXGAMESCENENESTS)
        return 101;

    iRet = mutils_addToDialogBuffer ("\n[2 months later...]\n\nStacy is a junior nun of \'the order of the holy fuckslave\'. She has been given an important task. Stacy masturbates in anticipation as she carefully approaches the entrance to the holiest of holy places, the royal chamber of her lord and master.\n\nWith great reverence, she climbs the steps out of the holy water, and reaches the chamber door. There is a lantern hanging next to the chamber door, the light of the lantern is a hindrance rather than helpful. This is the first time that she has undertaken this task. She must not mess it up.\n\nShe looks down at her swollen belly. The young lord and master within will protect and guide her.\n\nShe takes a small latex backpack off of her back, and reaches inside. Her latex gloved hand finds a small rectangular box, and she retrieves it from the backpack. Stacy\'s heart is pounding.\n\nStacy puts the backpack back on, while trying not to look at the box. It contains a \'holy artifact\'. It is made in the image of her lord and master, so she dare not look directly upon it.\n\nShe looks away, opens the box, and pulls the \'holy artifact\' out. Stacy\'s breathing intensifies. It feels as if it is throbbing. It feels as if it is alive. Without thinking about it she licks the tip of the \'holy artifact\'.\n\nThe smell... or lack of it... brings her back to her senses. There is no sacred pre-cum. The \'holy artifact\' is merely a hunk of rubber fashioned in the form of her lord and master... but it is not her lord and master.\n\nStacy looks at the hole in the door of the entrance, then away into the distance. She uses her hands to find the hole, line up the \'holy artifact\' and inserts it into the hole.\n\nThere is a large audible click, followed by the sound of stone grinding against stone. The passageway is filled with a pink colored light.\n\nStacy is scared, she turns to look inside the chamber. Wilda greets Stacy \"Hello\"...\n\nStacy is almost scared out of her skin, and starts to fall backwards. Wilda quickly reaches through the door and grabs Stacy\'s right arm. Wilda tells Stacy \"Careful, you might harm our lord and master\"...\n\nWilda helps Stacy to stand on her own feet. Stacy lightly bows to Wilda \"Sorry about that, Sister\"...\n\nWilda replies \"Don\'t be, your rank is higher than mine\"...\n\nStacy looks at Wilda \"Eh... What?\"\n\nA tentacle monster appears next to Wilda\'s side. Wilda sighs \"You are my replacement, you know... I am Wilda\"...\n\nStacy replies with a light laugh \"I am Stacy... well we had better swap before the master in your belly hatches\"...\n\nStacy walks in through the door, and Wilda walks out of the door. From behind her, Stacy can hear Wilda say something as the stone door starts closing. It sounded like \"I hope we meet again some day\", but Stacy is currently oblivious to what her fellow sister said, or anything else.\n\nStacy\'s focus is on what is in front of her. There are 3 of her masters, and many more off in the distance. Stacy is delirious with the thought that she is going to be fucked by all of them, multiple times.\n\n\nFor now, it would not matter if no one comes back to replace her, Stacy would happily die here in the presence of her lord and master, Cock.\n\nEND.\n\n");

    if (iRet != 0) return iRet;

    iRet = mutils_addToCommandList ("Credits", 3, 0);
    if (iRet != 0) return iRet;
    iRet = mutils_addToCommandList ("Main Menu", 0, 0);
    return iRet;
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

    iRet = mutils_addToDialogBuffer ("Wilda continues walking along the corridor following the flow of liquid. The current in the liquid is rather obvious now. Wilda keeps walking till she reaches what appears to be a dead end. But it isn\'t a dead end for the liquid.\n\nThere appears to be a small whirlpool that has formed in the center of the floor, and the liquid is flowing towards it, primarily from the corridor.\n\nWilda looks around the walls to see if there is any evidence of a door, or something like that. There are no depressions in the walls. Wilda sighs and walks towards the whirlpool \"It does not look like I can\"...\n\nSuddenly there is a loud \'cracking\' sound \"What the\"...\n\nBefore Wilda can react, she finds herself almost floating as part of the floor around the whirlpool drops away... with Wilda still standing on that part of the floor.\n\nWilda\'s feet lift up off the floor, only to slam back into it 4 seconds later. The part of the floor that had given way had already started to break up before it fell onto the pool of liquid directly below. The sudden impact caused the pieces of the floor to disintegrate even further.\n\nWilda wasn\'t able to remain standing, because a large body of liquid had followed her descent from the corridor above. A waterfall of white is bearing down on her.\n\nWilda is forced under the surface of the liquid pool below, by the torrent liquid from above. It took her 10 seconds to swim back to the surface of the liquid. Wilda finds that she is rather buoyant in the liquid. However, to her horror, Wilda quickly discovered the reason that she swim so effectively is because both her backpack and sword had detached during, or immediately after, her fall. Neither of them float, and are now completely submerged.\n\nThe torch Wilda was holding was also lost during the decent. When Wilda surfaced and looked around, she was surprised by what she could see... more specifically, because she could see...\n\n\"Where is the light coming from?\"\n\nIt took a few seconds for Wilda to realize that the light was emanating from aquamarine spherical appendages that are attached to the ceiling of the chamber that she landed in. The entire chamber is bathed in an aquamarine light.\n\n\"While that is helpful... I need my stuff\"...\n\n\n[15 minutes later...]\n\nWilda sighs \"This has been a fucking disaster\"...\n\nDespite the light above, it did nothing to penetrate anymore than one inch into the liquid. While swimming in it, the liquid quickly turned from aquamarine to pitch black.\n\nWilda tried blindly searching underneath the liquid, only to find that it wasn\'t working out so well. Wilda\'s apparent buoyancy was working against her, making it difficult for her to actually reach much of a depth beneath the surface, let alone to stay underneath to search with her hands.\n\nWhile the depth of the liquid pool saved Wilda from both death and serious injury, it has resulted in her losing almost everything she had. Her armor is also in a bad state.\n\nWilda crawls up on the one of the few places in the cavern where there is dry ground. Wilda is tired, but her bivouac sack was attached to her backpack. But that wasn\'t all that was in her backpack. All of the gold that Wilda had on her, including her pre-payment for this job, was in her backpack. Wilda looks down into the pool of opaque liquid \"When I complete this job\"...\n\nWilda\'s monologue is interrupted by someone calling out to her \"Have you considered Hedonism?\"\n\nWilda focuses more on who was calling out, and not what they were asking. Wilda looks around the cavern \"Where?\"\n\nThe voice calls out to Wilda \"Over here. We should leave this place... it isn\'t safe here\".\n\nWilda sees a nun holding up some form of lantern. The lantern is emitting an aquamarine light. Wilda looks around and notices that she is going to have to swim to reach the nun \"Can you stay there?.. I will come to you\"...\n\n\n[15 minutes later...]\n\nThe nun\'s name is Bambi. Wilda comes to the conclusion that Bambi is of the same religion as Amber, given that she is constantly smiling, her her focus is mostly somewhere else, and she is also regularly pleasuring herself. Bambi is also heavily pregnant. Like Amber, Bambi is also wearing a cloak, but there is something different about the black cloak that Bambi is wearing.\n\nWilda helped Bambi put the locking bar in place across the heavy metal the door of the small shelter. Bambi called the shelter a \'sanctuary\'. After closing the door, Wilda glanced at Bambi\'s swollen belly. Wilda decides it would not be polite to comment.\n\nBambi notices Wilda looking at her belly, so Bambi rubs her belly through her cloak and states \"This is a holy gift from our lord and master... Cock\"...\n\nWilda looks at the lantern that Bambi was holding, then notices that there is another sitting on a shelf by the wall. Wilda was about to ask how they work.\n\nBambi\'s focus is elsewhere \"I am but an obedient vessel for holding the holy semen... a breeding sack for my lord\'s sacred spawn... More... Violate me more... Lord... Cock... Yes... More\"...\n\nMeanwhile, Bambi is violently fingering her clitoris, while also playing with her nipples through her cloak. Wilda decides that it would not be wise to interrupt... whatever it is... that Bambi is doing.\n\n\n[4 minutes later...]\n\nBambi fingered herself to a climax no less than 12 times, while in a trance state. The floor immediately beneath Bambi is covered with a combination of what appears to be sweat, pussy juices and breast milk. There are no wet spots on the outside of Bambi\'s cloak, because the entire garment is made out of black latex rubber.\n\nThe entire time, Wilda stood next to Bambi, worried that she was going to pass out and fall down. Somehow, Bambi remained standing despite the fact that her body was wracked by a series of orgasms. After recovering from her last climax, Bambi continued to finger herself, but seemed to notice that Wilda was there.\n\nBambi looks at Wilda and asks \"Is... everything okay?... You seem to be distracted\"...\n\nWilda considers making a witty remark, but decides now is not the best time \"I am fine... thank you\"...\n\nBambi shakes her head and points at Wilda, more specifically the armband on Wilda\'s left arm \"You bear the sigil. It is I who should be thanking you\"...\n\nWilda remembers that she put on the armband that Amber gave her. But there was nothing special about the armband. It is just black rubber. Wilda takes a look at the armband again \"What the\"...\n\nThe armband is still black rubber, but now there is some form of symbol showing through the rubber. Wilda looks at Bambi \"It was pure black when I originally received it... and when I put it on later... is this what Amber meant when she said \'sanctioned servant\'?\"\n\nBambi looks over Wilda, then looks at Wilda\'s face \"Were you sent here on a quest?\"\n\nWilda replies \"I was paid to do a job\".\n\nBambi responds \"Then I am to assist you. I have a bed and items for you to select from\".\n\nWilda is concerned \"Sorry... All of the gold that I had was in my luggage... So\"...\n\nBambi interjects \"Payment won\'t be necessary... This is all in the service of our lord and master... Cock... Yes... I am thy faithful fucktoy... An onahole for your service\"...\n\nAs Bambi continues to jill herself off, Wilda thinks to herself that this is the last time she is going to mention anything that is going to remotely suggest the nun\'s servitude.\n\n\n[10 minutes and 29 orgasms later...]\n\nBambi\'s grasp of reality finally included Wilda again, so Bambi showed Wilda the supplies that Wilda could choose from.\n\nBambi states \"You can take any and all, but there is only one of each\".\n\n\n[30 minutes later...]\n\nWilda received from Bambi... a small backpack made out of black latex rubber... a pair of black latex thigh high stockings... a pair of dim-gray rubber shoes that Bambi called \'crocs\'... a black latex/rubber under-bust corset... and a spanking paddle as an improvised weapon.\n\nWilda isn\'t complaining, as everything is free. There were other things as well, but Wilda decided that she had no need for the \'deluxe breast milking harness\', whatever that is, or the mouth-ring gag.\n\nAfter picking out the items from the inventory, Wilda reequips herself. Wilda\'s found that her armor started to really fall apart. Wilda decided to not bother with her broken armor and use what she acquired from Bambi instead.\n\nBambi then showed Wilda to a small room with a single bed. Wilda noted that the room only had one bed, so she asked Bambi was it okay to hog the bed to herself. Bambi replied that she has a comfy chair to sleep in, lightly bows and shuffles away with the lantern.\n\nAs Bambi just wondered off with source of light, Wilda had to grope around in the darkness for the bed, then laid down and went to sleep.\n\n\n[?? amount of time later...]\n\nWilda wakes up. She is feeling rather refreshed. It takes a while for Wilda to remember where she is. She looks around the room. There is a low level of light from somewhere. Wilda stumbles out of the small bed and walks slowly to the door. Outside the door is one of the aquamarine lanterns. Wilda looks at it \"Bambi must\"...\n\nThen Wilda noticed that next to the lantern was a folded up garment. Wilda walks over and picks up both the lantern and the garment up off the floor. The garment is made of black latex rubber.\n\nWilda carries the lantern and the garment into the main room of the sanctuary, wondering where Bambi is. Bambi is nowhere to be seen. There is no sign of the other lantern either.\n\nWilda decides to checkout the garment, so she unfolds it. It is a black latex cloak. Wilda turns it inside out, and notices that there is breast milk residue where the nipples would have been, and more residue where her pussy would have been. This cloak must have been Bambi\'s.\n\nWilda swings around. That is when she noticed that the locking bar is no longer across the door. The locking bar is leaning against the wall next to the door.\n\n\"Shit\"...\n\nWilda opens the door and looks outside of the sanctuary. There is no sign of Bambi and...\n\n\"What is going on?\"\n\nWilda distinctly remembers that the hallway to the sanctuary was from the left. This time the hallway to the sanctuary is straight ahead.\n\nWilda takes a deep breath, steps back inside the sanctuary and closes the door.\n\n\n[10 minutes later...]\n\nFirst, Wilda searched around inside the sanctuary. There was no sign of Bambi, or anyone else. There was only the one lantern that Wilda was holding, with no sign of the other. Wilda found her broken armor where she had left it. Upon closer inspection, Wilda noticed that her old armor was practically of no use now. For extra protection, Wilda decided to also put on the cloak that Bambi left behind.\n\nThe only other thing that Wilda found of interest was another small rectangular box that looks like the one that Amber had originally given Wilda. The box was sitting on a table, in plain view. Inside the box was another \"holy artifact\", a dildo, just like the one that was inside the backpack that Wilda lost. Wilda decided to take the dildo, with the box, and put it inside her new backpack.\n\nThe only conclusion that Wilda has is that Bambi wondered away from the sanctuary. Bambi had told Wilda that she dared not venture away from the sanctuary for too long. Wilda considered for a second that Bambi wasn\'t always mentally stable. Bambi could have gone against that better judgment while she was focusing on her lord or master... whoever or whatever, they or it, is...\n\nThe other possibility is that Bambi was lying. Wilda decides that she can figure out of her companion for the evening was in fact telling the truth later.\n\nWilda steps out of the door of the sanctuary, grabs the handle and pulls the door shut behind her. Without the locking bar being in place, the door won\'t keep much out. But without anyone left inside the sanctuary, there is no way that the locking bar can be put back in place. However, Wilda\'s job is to recover what the nuns hired her for, so that is what she is going to do.\n\nOutside of the sanctuary, there is a pathway that leads south.\n\n");
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

        iRet = mutils_addToDialogBuffer ("Wilda arrives back at the T-intersection where she set-off the trap that sealed her inside this dungeon. Wilda thinks to herself if she could find what she set off she might be able to undo it. She spends a minute walking around the T-intersection trying to find where the switch is, but has no luck. She gives up and decides that she is just wasting time here and should go elsewhere.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda is walking along a hallway, when she can start hearing something. Wilda finds it weird, so she looks around carefully. Wilda cannot see anything that suggests that a monster is advancing towards her. So she takes a gamble, closes her eyes and tries to focus on the sounds that she can hear. It sounds like a voice. Possibly human.\n\nWilda decides to keep walking along the hallway she is in.\n\n\n[1 minute later...]\n\nWilda has made a right hand turn. The sound is starting to get louder.\n\n\n[1 minute later...]\n\nAt a T-intersection. The sounds are coming from... straight ahead and not the left passageway.\n\n\n[1 minute later...]\n\nDrat... That sounds like a person\'s voice... no... two people.\n\n\n[2 minutes later...]\n\nWilda makes a right turn and then... She sees them. Wilda sees the two monsters. And, the monsters are not alone. There are two people here as well. Both of them are human women.\n\nEach monster is paired with each human woman. There are tentacles sliding in and out of every available major orifice. The women\'s bodies are shaking due to the barrage of powerful orgasms that they are experiencing. The monsters are still concentrating on their respective partners, completely oblivious to the fact that Wilda showed up, with a lantern that has illuminated the otherwise dark corridor.\n\nFor a moment, Wilda ponders leaping in and fending off the two monsters. However, her opponents have hostages. Wilda considers calling out to the two women, but realizes that would alert the monsters to her presence sooner, and that would probably be a bad idea.\n\nWilda slowly steps around to see if she can get a better opening, her own clitoris starts to perk up, along with her nipples. She is finding this scene rather erotic. As for her pussy...\n\nWilda suddenly remembers that she left a dildo inside her pussy. That was stupid. It\'s presence is going to affect her movement. Wilda decides that before she is going to charge in, she will have to remove it first. Thankfully, Wilda is horny again, so the dildo is going to be well lubricated. First, Wilda walks, while still knee deep in liquid over to a wall, and hooks the lantern on a rock that is jutting out. Then Wilda gets her spanking paddle ready. Finally, Wilda reaches underneath her cloak and pulls the dildo out.\n\nAt that point the two monsters take notice of Wilda and immediately stop violating both of the women. Wilda is standing there with a spanking paddle in her right hand, and a wet dildo in her left. Wilda tries to think of something that will act as a diversion, then realizes that while she can throw rather well with her right hand, she is has horrible aim with her left. The closest monster pulls it\'s appendages out of the human woman it was fucking and sets her down. Wilda considers it would be a really bad idea to swap weapons between hands now, besides... what other use does a dildo have?\n\nWilda throws the dildo with her left hand at the far wall of the hallway, hoping that the monsters would be distracted either by it hitting the wall or falling into the liquid.\n\nUnexpectedly, the nearest monster scampers off after the dildo. The second monster sets down the human woman it was fucking and follows the first monster.\n\nWilda watches in disbelief as both of the monsters then scamper away, down the hallway. Wilda caught a glimpse of the first monster holding the dildo that she threw in one of it\'s appendages. Wilda looks around the hallway to see if there is any more imminent danger. She then looks at the two human women, who are sitting down in the opaque liquid.\n\n\n[2 minutes later...]\n\nThe first nun, who is wearing what appears to be a latex open cup crop top, latex crotchless pantyhose and elbow-length latex gloves, is busy pleasuring herself. Under her breath, she is muttering obscene derogatory comments about herself and her genitals. She is also heavily pregnant.\n\nThe second nun, who is wearing a black latex cape, a black latex open cup camisole, knee-high black latex socks and wrist length black latex gloves, has finally acknowledged Wilda \"Sister?\"\n\nWilda looks around the hallway again \"Is there somewhere safe for us to go?\"\n\nThe second nun blinks, glances at the first nun, then looks over Wilda again \"Oh, I am sorry\"... The second nun then blurts out \"Have you considered Hedonism?\"\n\nThe first nun chimes in, without looking at Wilda or her companion, while still in her dream trance \"You really should, it feels really good\"... the first nun then slips back into her routine of self pleasure.\n\nWilda just stands there staring at the first nun, dumbfounded. After a few seconds, Wilda looks around the hallway again, then at the second nun.\n\nThe second nun addresses Wilda \"You bear the mark of a \'sanctioned servant\', so you must be on a quest. I am Daisy, and this is my senior sister, Crystal\".\n\nWilda responds \"My name is Wilda, I was hired to do a job, but first\"... Wilda looks around \"I need to get you two somewhere safe\".\n\nDaisy starts to stand up \"We have a sanctuary nearby\".\n\nWilda is about to ask where, when Crystal staggers to her feet, and starts walking along the hallway. Wilda looks at Crystal, both surprised and dumbfounded \"Ahh\"...\n\nDaisy looks at Wilda \"We just need to... follow my senior\".\n\nWilda responds \"Ok\", and wonders over to the wall to collect her lantern.\n\n\n[3 minutes later...]\n\nWilda and Daisy are following Crystal through the passageways. Wilda looks at Daisy \"Does, your senior, know where she is going?\"\n\nDaisy replies, while also fingering her exposed clitoris, \"Every senior nun does. I am still learning... So, why are you wearing a nun\'s cloak?\"\n\nWilda remembers that she grabbed the cloak and the lantern before leaving the sanctuary, which now seems like a bad idea \"Sorry, but it was left behind in the sanctuary that I left earlier. Is this... a problem?\"\n\nDaisy responds without breaking her smile \"Not for me\".\n\nWilda decides that as soon as she gets a chance, she should get rid of the cloak. Wilda decides to change the subject \"Could you tell me... about this armband?\"\n\nDaisy replies \"All I know is that the symbol means a \'sanctioned servant\' of our... Lord\"...\n\nWilda notices that Daisy\'s walk is slowing down and her eyes are starting to glaze over, so she quickly interrupts Daisy\'s line of thought \"Yes, and you are to lend assistance... Am I right?\"\n\nDaisy quickly recovers from her trance thought \"Uhh... Yes... but I don\'t really know much more than that, Because\"...\n\nWilda completes the sentence for Daisy \"Because you are still learning?\"\n\nDaisy responds with a bigger smile \"Yes\".\n\nWilda lightly smiles then almost trips up. Wilda stops walking and looks at Daisy who is calmly walking through the liquid. Then there is Crystal, who is effectively sleepwalking through the liquid as well. Then Wilda considers the fact that she is the only one of the 3 holding a lantern. Wilda quickly rushes to keep up with the two nuns, while wondering how either of them are able to navigate around inside the submerged hallway, in complete darkness.\n\nThe trio turn right into another hallway.\n\n\n[2 minutes later...]\n\nNext to the entrance of the sanctuary, is a lantern hanging on a wall. As the trio approach it, Daisy quickly rushes over, grabs the lantern off the wall, and opens the door of the sanctuary.\n\nCrystal, without breaking her stride, turns towards the door, walks up the steps and through the open door. Wilda follows Crystal inside the sanctuary. Daisy follows Wilda, while closing the door.\n\nInside the sanctuary, Crystal just stands there, in the middle of the entrance room, still fingering herself while in a trance. Wilda looks around the sanctuary and notices that this one appears to be larger than the one she left earlier this morning. Wilda\'s focus is brought back to Crystal who seems to be muttering a little bit louder now \"Ah... Lord... Cock... Violate thy obedient fuckslave, with your all of your turgid might\".\n\nWilda asks Daisy a question \"So, what exactly is your senior doing?\"\n\nDaisy answers \"Praying\".\n\nWilda responds \"Oh... Praying\". Wilda decides to check the locking bar for the front door of the sanctuary. Only to find that there isn\'t one. Not only is there no bar next to the door, there are no hooks on either side of the door to hold the bar. This isn\'t good. Wilda decides to check with Daisy... and... drat.\n\nDaisy is now standing next to Crystal. Both of the nuns are chanting the same phrases out loud, while fingering themselves in unison \"My holy lord and master... Cock... We are but pitiful vessels for your holy seed... Impregnate our sopping wet holes with your baby batter and grant us endless pleasure\"...\n\nWilda decides that she will have to sit down and wait for a while.\n\n\n[4 minutes later...]\n\nWilda has used her spare time to take off the cloak that she borrowed from Bambi and fold it up.\n\nDaisy comes out of her trance state first, while Crystal continues mindlessly reciting quotes about being used as a fucktoy while slicking herself to another orgasm.\n\nWilda snaps her fingers to prove that Daisy is back on the same plane of reality. Daisy looks at Wilda and asks \"Is something the matter?\"\n\nWilda asks in return \"For how long has your senior been praying?\"\n\nDaisy glances at Crystal and looks back at Wilda \"about... two days ago\".\n\nWilda is surprised \"two days?\"\n\nDaisy\'s smile doesn\'t change, but she puts her right hand on her hip when casually responding \"My senior can pray for up to a week, sometimes longer\"... Daisy then regains her posture and goes right back to masturbating.\n\nWilda responds \"A week?... Okay... So, what where you two doing out in the hallways?\"\n\nDaisy replies \"Praying... Of course. We sometimes get help from our lord and master... Cock... to... fill our slutty pussies with their holy semen... to smear our bodies with the divine seed\".\n\nDaisy slips back into her masturbation trance. Wilda looks down at Daisy\'s belly and notices that it is slightly swollen, while Daisy\'s enlarged nipples are a dark shade of brown. Wilda briefly considers the connection between the tentacle monsters and the religion this pair of perverted nuns follow, but swiftly dismisses it as an impossibility.\n\nWilda decides to wait for Daisy to stop \'praying\'.\n\n\n[30 minutes later...]\n\nWhile waiting for either of the nuns to finish \'praying\', Wilda ended up having her own personal indulgence while both Daisy and Crystal were distracted. Wilda decided that it would not be rude to jill herself off, considering that both of the nuns were doing it anyway.\n\nEventually Daisy finished, so Wilda broke off pleasuring herself. Wilda offered Daisy Bambi\'s cloak. Daisy insisted that Wilda take something in return. Wilda followed Daisy to another room, leaving Crystal to continue her \'personal prayer of self degradation\'.\n\nDaisy gleefully rummages through the sanctuary clothing supplies and offers Wilda a harness bra made out of rubber and shoulder length rubber gloves. Wilda considers it impolite to reject either item. The gloves will offer protection. The harness bra won\'t offer anything beyond decoration. Daisy helps Wilda put both of the items on.\n\nDaisy finds a spanking paddle and offers it to Wilda. Wilda shows Daisy the spanking paddle that she already has, so Daisy puts the one that she found away.\n\nDaisy then leads Wilda to the bedroom. Upon entering the room, Wilda can only look in awe at a big \"thing\" covered in black latex rubber. The bed is massive, and round. 6 warriors in armor could easily sleep on it. Wilda is surprised at the scale of the bed. Daisy giggles and suggests that Wilda should have a rest. Wilda thanks Daisy and crawls up on the bed and lays down. Daisy picks up the lantern and walks out of the room, leaving Wilda to quietly slip in to a deep slumber.\n\n\n[?? amount of time later...]\n\nWilda wakes up. She is feeling rather refreshed, as well as rather horny. Wilda licks her lips, as well as her gloved fingers. Whatever is on her fingers, is rather tasty, and somehow familiar.\n\nSomebody nearby talks to Wilda \"Good morning, Have you considered Hedonism?\"\n\nWilda sleepily responds \"Maybe\", then realizes she is talking to someone. Wilda opens her eyes and looks around the room that is lit with an aquamarine color.\n\nWilda\'s eyes finally find Crystal, who introduces herself \"Hello, My name is Crystal\".\n\nWilda props herself up on her elbows. There is a tingling sensation from the butt-plug that is present in her anus. Wilda\'s arousal quickly spikes and settles down a little bit. Wilda desperately wants to finger herself right now, but there are more important formalities to attend to. She talks to Crystal \"My name is Wilda, and we have met before\".\n\nWilda suddenly remembers that there was another nun, and starts looking around the bedroom \"Where is... Daisy?\"\n\nCrystal stands up. Wilda looks over Crystal. Her baby belly is now gone, and she is now wearing an open bust latex garter dress, with suspenders connected to latex stockings. The latex stockings are stirrup-stockings, but, they are mostly obscured by the thigh-high low-heel rubber boots that Crystal is wearing. Crystal is also wearing shoulder length latex gloves. Crystal replies \"Daisy, my former junior, is currently elsewhere, praying\".\n\nInitially, Wilda can only a muster an \"Oh\" response. Wilda thinks about the changes that she can see about Crystal and asks a question \"How long have I been asleep?\"\n\nCrystal ignores the question and picks up one of the aquamarine lanterns \"You are a \'sanctioned servant\', and require assistance with your quest. I shall guide you to the next sanctuary\".\n\n\n[10 minutes later...]\n\nWhile waiting for Crystal to get her equipment together, Wilda patiently waited in the sanctuary entrance room with an aquamarine lantern. Crystal has the other lantern. While waiting there, Wilda is unconsciously fingering herself with her left hand.\n\nCrystal returns to the entrance room, with a latex backpack on her back, a spanking paddle and lantern in her right hand, while also fingering herself with her left. Watching Crystal walk towards her, Wilda becomes fixated on Crystal\'s massive breasts. The way that her dark nipples bounce is rather soothing, almost hypnotic.\n\nCrystal notices that Wilda is staring at her breasts and pronounces \"I have borne many children for my lord and master... Cock... And my udders are heavy with joyous milk... Are you ready to continue your quest?\"\n\nThe question snaps Wilda out of her daze. She replies \"Yes, I will... continue my quest\"...\n\nCrystal opens the door, and the pair depart from the sanctuary.\n\nOutside the sanctuary, Wilda looks to the south. There is a pathway there. Crystal looks at Wilda \"We need not regard that way\".\n\nWilda inquires \"Why?\"\n\nCrystal continues \"That way only leads back up. Your quest... is to the east\"...\n\nWilda asks \"East goes down?\"\n\nCrystal nods her head \"Yes\".\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda arrives back at the entrance to the sanctuary. It is possible that someone has returned, so she walks over to the door and opens it. Wilda looks around inside the entrance room, to see that there is no sign of anyone there. Wilda then pulls the door closed. It is obvious that if there was someone inside they would have put the locking bar across the door anyway. It is clear that there is nobody here.\n\n");
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

    iRet = mutils_addToDialogBuffer ("As Crystal and Wilda exit a hallway into a T-intersection, Crystal looks at a marking on the wall. Wilda asks Crystal \"What is it?\"\n\nCrystal points down the left passageway \"We should... go that way\"...\n\n\n[5 minutes later...]\n\nCrystal and Wilda arrive at a sort-of familiar looking door at the end of a hallway, with stairs leading from the white liquid up to it.\n\nWhile Crystal opens the door of the sanctuary, Wilda wonders if this sanctuary is going to be empty. The moment that the door is open, Wilda can hear murmuring from inside.\n\nCrystal looks inside the door and then back at Wilda \"We should join in\".\n\nWilda follows Crystal into the sanctuary, where she sees another nun, wearing latex suspender-tights with rubber knee-high low-heel boots, wrist length gloves and short sleeved bolero. She is also heavily pregnant. After Wilda finishes looking over the nun, who is muttering \"Fill both of my lower mouths with your hot-dick milk\", Wilda looks at Crystal.\n\nCrystal motions with her open hand to the nun \"This is Eboni, a fellow senior nun\".\n\nWilda responds \"Obviously\", then looks back at Eboni. Wilda then notices that Eboni\'s clitoris and nipples are a lot larger than normal. Eboni\'s breasts are lightly lactating. Wilda is briefly entranced by Eboni\'s swinging breasts, but comes back from it. Wilda is about to ask Crystal more about Eboni... however...\n\nCrystal is now standing next to Eboni, and the two nuns are praying in unison. Wilda sighs... At least Crystal refrained from praying until they got here.\n\nThen Wilda finds herself being drawn to Crystal and Eboni\'s heaving breasts.\n\n\n[20 minutes later...]\n\nWilda is in a daze. Someone says to her \"Have you considered Hedonism?\"\n\nWilda responds \"I really am\"... just as she breaks out of her daze and looks at Eboni, who was asking the question. Wilda is confused then perplexed.\n\nCrystal chimes in and says \"aaand... it feels really good, doesn\'t it?\"\n\nWilda blushes \"Sorry, I am Wilda\".\n\nEboni responds \"And you are on a quest. Come... you must be tired\".\n\n\n[5 minutes later...]\n\nThe trio visit the sanctuary clothing supply storage. Eboni throws Wilda a new butt-plug that is a size larger than the one she currently has. Wilda thanked Eboni for the gracious replacement, then proceeded to swap out her existing butt-plug for the new one, without a second thought. Wilda decides that she does not need anything else, so the trio move onto the bedroom.\n\nBefore arriving at the bedroom, Wilda was wondering what size the bed is going to be. When they got there, Wilda was surprised that there aren\'t any beds in the bedroom. There are four identical and strange looking chairs.\n\nWilda looks at Eboni \"So... This is where I am going to sleep?\"\n\nEboni nods, and her smile briefly turns to a grin \"Yes, you have not seen these before?\"\n\nWilda looks at the nearest gynecologist chair and states \"I cannot say that I have\". Wilda then looks at Eboni apprehensively and asks \"So... how do I... get to sleep in one of these... things?\"\n\n\n[2 minutes later...]\n\nBeing her first time getting into a gynecologist chair ever, it wasn\'t easy, but Eboni and Crystal were a big help. After Wilda sat into the actual seat itself of the gynecologist chair closest to the door, Eboni and Crystal lifted Wilda\'s legs up into the stirrups and strapped them in. Wilda started unconsciously masturbating with her left hand again, while the two nuns continued checking the straps on Wilda\'s legs, then continued to strap Wilda\'s body into the chair.\n\nCrystal looks at Wilda \"This is to make sure you don\'t fall out while you are sleeping\".\n\nWilda responds \"Oh... how thoughtful\".\n\nCrystal grins at Wilda, as she then pulls Wilda\'s left hand away from her crotch and proceeds to strap Wilda\'s left arm into an armrest. Eboni does the same with Wilda\'s right arm.\n\nWilda starts to feel a little bit uneasy, given that she is unable to masturbate \"So... How do\"...\n\nEboni places a finger over Wilda\'s mouth \"Don\'t worry, we will take care of the rest\", and proceeds to start fondling Wilda\'s right breast.\n\nMeanwhile Crystal is sucking on Wilda\'s left nipple, while also fingering Wilda\'s swollen pussy. Wilda lets out a moan of pleasure \"That feels... so fucking good\"...\n\nEboni continues to fondle Wilda\'s right breast with her right hand, while stroking Wilda\'s forehead with her left. Wilda looks at Eboni\'s face. Eboni tells Wilda \"Look at my milk filled udders... at my teats\". Wilda finds that she needs to look at Eboni\'s breasts. The way that Eboni\'s nipples lightly sway is soothing. Eboni continues talking \"That\'s it... go deeper... and deeper\"...\n\nWilda can only mutter a \"Yes... deeper\"...\n\nEboni speaks slowly \"Now... Sleep\"...\n\n\n[?? amount of time later...]\n\nWilda wakes up. She squints her eyes and looks around the room that is illuminated by and aquamarine light. Her entire body is still strapped into a chair. Wilda is still disoriented \"Where... am I?\"\n\nSuddenly Wilda feels something at her crotch. While her clitoris is being stroked, she is asked a question \"Have you considered Hedonism?\"\n\nWilda, still in a daze, answers \"I really want a really good baby-making-fuck\".\n\nThe unfamiliar voice giggles \"Aren\'t you... already preggers?\"\n\nWilda snaps out of her daze, and looks at the woman she is talking to \"Oh... sorry... I am Wilda\".\n\nThe nun introduces herself \"I\'m Felicity, an\' the pleasure is both of ours\".\n\nFelicity then kneels down between Wilda\'s open legs and proceeds to lick and suck Wilda\'s clitoris. Wilda can barely see the top of Felicity\'s head past her own swollen belly. Unknown to Wilda is that her clitoris is a lot larger than before. Wilda just lays there, still strapped into the gynecologist chair, furthest from the door, as Felicity continues to eat her out.\n\n\n[5 minutes later...]\n\nFelicity finally lets Wilda out of her \'bed\'. While Felicity, alone, unstrapped Wilda, Wilda got a better look at Felicity.\n\nFelicity is wearing a body harness made out of rubber strips, wrist length latex gloves, ankle length latex socks, and rubber ballerina flat shoes. Felicity also has a collar around her neck, and her over-sized nipples and clitoris are pierced with over-sized studs. Felicity is also heavily pregnant.\n\nAfter Wilda finally stepped out of the seat, Felicity handed Wilda her backpack and lantern. There is another lantern on the floor, which Felicity picks up.\n\nWilda looks around the room again and asks Felicity \"Is there... anyone else around?\"\n\nFelicity responds \"Jus\' us two now\".\n\nWilda responds \"Oh\"... then looks down at her swollen breasts and belly. The corset belt is now gone. She her aureole are now now larger and slightly darker. Her nipples are now permanently erect and the size of her thumb-tips.\n\nFelicity adds \"or jus\' us four?\"\n\nWilda smiles at Felicity. Wilda has no problems with being pregnant, as she always wanted to be like this. Felicity\'s belly is larger as her pregnancy is clearly more advanced. Wilda unconsciously starts stroking her clitoris again as she asks Felicity \"So, where are Crystal and Eboni?\"\n\nFelicity\'s smile reduces a little bit \"Those missies be praying now, away from here... I must apologize... I can\'t come with you\".\n\nWilda then remembers that she is on a quest. For some reason, Wilda already has a vague idea of where she is going.\n\n\n[2 minutes later...]\n\nFelicity was nice enough to accompany Wilda to the sanctuary entrance. When they reach the doorway, Felicity proclaims \"Jus\' a moment... I have something for you\".\n\nFelicity strides over to a small table and picks up a small rectangular box. Felicity then returns back to Wilda \"Miss \'sanctioned servant\' will need her \'holy artifact\', won\'t she?\"\n\nFelicity hands over the box and Wilda accepts it from Felicity \"Why, thank you\".\n\nWilda hugs Felicity, but Felicity protests. \"Now that won\'t do... I will show you\".\n\nFelicity lightly pushes Wilda away, then starts giving Wilda a sloppy kiss. Wilda decides to reciprocate, and the two pregnant women continue intertwining their tongues while also fondling each other. Felicity finds Wilda\'s pussy and starts fingering it. Wilda starts playing with Felicity\'s left breast, causing breast milk to spray everywhere.\n\n\n[2 minutes later...]\n\nThe two women finally break away from each other. Wilda says to Felicity \"Thank you... again\". Felicity grins back at Wilda.\n\nWilda then opens the \'holy artifact\' box that she was given. Felicity takes one look at the dildo that Wilda took out of the small box, and almost immediately slips into her prayer trance. \"My lord and master... Cock... Use my trashy cunny to your heart\'s content... Yes... More... Fuck up my life an\' my baby factory with your hawt milk\"...\n\nWilda smiles, as she slips the dildo into her wet pussy. At least Felicity is happy praying. Wilda starts to thrust the dildo in and out of her pussy a couple of times, then realizes that her pussy is rather loose. Wilda decides that if she comes across a delightful tentacle monster she can just have them fill her aching pussy. Wilda pulls the wet dildo out of her pussy and puts it back inside it\'s small box. Wilda then puts the small box inside her backpack.\n\nWilda picks up her lantern, opens the door of the sanctuary, walks through and closes the door behind her.\n\nOutside of the sanctuary, there is a pathway that leads south.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive back at the Crystal\'s sanctuary. Wilda looks at Crystal \"Do you think anyone has returned?\"\n\nCrystal replies \"Unlikely... I will check\".\n\nCrystal walks up the stairs to the door and opens it. Crystal looks around inside the entrance of the sanctuary, while Wilda looks to the southern passageway, and considers that someone could have returned while Wilda and Crystal were down the eastern passageway.\n\nCrystal closes the door and looks at Wilda \"There is no one else here\".\n\nWilda responds \"Oh... Okay\"...\n\nCrystal continues \"Even if there was anyone else here, it is unlikely they would have been able to assist you. We should resume your quest\".\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda is walking along a hallway, she reaches an apparent dead-end. However, there is an indentation in the wall, with a symbol painted on it. There are a set of stairs leading up from the liquid to the indentation. Wilda recognizes the symbol, as it matches the one that has shown itself on her armband. Wilda walks up the stairs to get a better look at the indentation.\n\nIn the center of the indentation, just below the symbol, is circular hole in the stone. The hole is just over 2 inches in diameter. Wilda just looks absentmindedly at the hole for a minute, and finally smiles.\n\nWilda takes the backpack off her back, and finds the \'holy artifact\' box within it. As she takes the dildo out of the box, Wilda unconsciously starts to lick the tip of the dildo and then thrusts it into her pussy. Wilda fingers herself to a climax while pistoning the dildo in and out of herself. It takes about half a minute for Wilda to come out of her daze, and to realize that she is still standing in front of the door of her destination.\n\n\"That\'s right... I still need to open this\".\n\nWith relative ease, Wilda slides the dildo out of her pussy and then pushes it all of the way into the hole in the indentation.\n\nThere is a large audible click, followed by the sound of stone grinding against stone as the slab that forms the indentation slides away.\n\nThe passageway is filled with a pink colored light from inside the chamber. Wilda places her aquamarine lantern on a nearby rock \'hook\', as she won\'t be needing it, possibly ever again.\n\nAs Wilda steps into the chamber, 5 tentacle monsters rush towards her with great speed, but quickly stop once they are less than 3 feet away. Wilda lightly pats her swollen belly. Her masters will not harm her while she is accompanied by another master.\n\nWilda surveys the tentacle monster throne room. There is the muffled voices of several human women who are confined to the \'nursery\'. They had failed, but still were able to share the pleasures that her masters can bestow.\n\nYes... they are her masters. They are her lords. Wilda starts to pray.\n\n\"My lord and master... Cock... I am before the to be baptized by your holy sperm... Come... Make make this slutty whore whole\"...\n\nThe 5 tentacle monsters that were originally going to attack Wilda and tear her to shreds, move in on her.\n\nWilda briefly considers that she will be in heaven handling 5 masters at once.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda arrives back at the Felicity\'s sanctuary. Wilda wonders if anyone else has shown up, so she takes a peek inside the door of the sanctuary. Felicity is still there... Praying. Wilda decides to leave Felicity alone and continue on her way.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of a staircase that is made out of wooden planks. There is a gravel ramp up from the liquid to the base of the staircase.");
        if (iRet != 0) return iRet;

        iLinkId = gpstructMapPosStaticCurrent[gstructActStateGlobal.sPosId - 1].sControlLinkId;
        if ((iLinkId > 0) && (iLinkId < (gsMapLinkDynamicCurrentSize + 1)))
        {
            if (gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus == 2)
            {
                gpstructMapLinkDynamicCurrent[iLinkId - 1].cStatus = 1;

                iRet = mutils_addToDialogBuffer (" Wilda is briefly distracted by the sound of stone sliding against stone from the corridor she just walked down.");
                if (iRet != 0) return iRet;

                if (gcDebugFlag != 0)
                {
                    char szWorking[80];

                    sprintf (szWorking, "\n\ndebug: LinkId %d closed", iLinkId);

                    iRet = mutils_addToDialogBuffer (szWorking);
                    if (iRet != 0) return iRet;
                }

                // override the direction, because we don't know which way we are facing now.
                gstructActStateGlobal.cDirect = 0;
            }
        }

        iRet = mutils_addToDialogBuffer ("\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of the wooden plank staircase. There is a gravel ramp from the top of the staircase down into the liquid.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the bottom of the wooden plank staircase. The lowest steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the base of a wooden plank staircase, rising up out of the white opaque liquid.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of the uneven stone staircase. At the top there is a gravel ramp down into the liquid.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of a uneven stone staircase. While there is a gravel ramp up from the liquid to the base of the staircase, there is opaque liquid tricking down the uneven stone stairs.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Following the trickle of opaque liquid, Wilda arrives at the bottom of the uneven stone staircase. The lower steps disappear into the opaque liquid.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the base of an uneven stone staircase, which is rising up out of the opaque liquid. There is opaque liquid trickling down the stone steps.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of the staircase made out of worn stone steps. There is a makeshift wooden ramp at the top of the staircase leading down into the pool of white opaque liquid behind it.\n\n");
    else
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of a staircase made out of smooth stone. The stone steps are rather worn from being used for many years. There is a makeshift wooden ramp rising up out of the opaque liquid to the top of the stairs.\n\n");
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
    iRet = mutils_addToDialogBuffer ("Wilda arrives at the bottom of the staircase made out of worn stone steps. The lower steps disappear into the white opaque liquid.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the top of the staircase made out of black rubber.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at a staircase, that is made out of hard black rubber. It takes a couple of steps up out of the opaque liquid and then proceeds to slope down.\n\n");

        if (gpstructMapPosDynamicCurrent[gstructActStateGlobal.sPosId - 1].sVisitCount < 2)
        {
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("Wilda looks over the staircase and then asks Crystal \"Specially made?\"\n\nCrystal responds \"A gift... from our lord and master... Cock\"...\n\nWilda decides that she is not going to bother asking Crystal exactly where her church got all of the rubber from, to make this.\n\n");

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
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the bottom of the black rubber staircase. The lower steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the base of a staircase, made of black rubber, rising up out of the opaque liquid.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the top of the staircase made out of large smooth stone steps. The staircase crests then has a couple of large steps down into the opaque liquid at the top.\n\n");
    else
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the top of a stone staircase. Each step is a stone block that has been expertly crafted. There are a couple of large steps out of the opaque liquid, then it proceeds to slope down.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the bottom of the staircase made of large smooth stone steps. The lower steps disappear into the white opaque liquid.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda arrives at the top of a stone staircase. Each step is a stone block that has been expertly crafted. There are a couple of large steps out of the opaque liquid, then it proceeds to slope down.\n\n");
    if (iRet != 0) return iRet;

    if (gstructActStateGlobal.sMapId == 2)
        iRet = mutils_addToDialogBuffer ("This is a turn, with an unknown stairway leading down to the south, and an path to the west. However, Wilda is only going to go south.\n\n");
    else
        iRet = mutils_addToDialogBuffer ("This is a hallway, with an unknown stairway leading down to the south, and an path to the north. However, Wilda is only going to go south.\n\n");

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
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the bottom of the stone staircase. The lower steps disappear into the white opaque liquid.\n\n");
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda arrives at the base of a staircase that is rising up out of the opaque liquid. The stone steps are rather large stone blocks that have been expertly crafted.\n\n");
    }
    if (iRet != 0) return iRet;

    switch (gstructActStateGlobal.sMapId)
    {
    case 3:
        iRet = mutils_addToDialogBuffer ("This is a turn, with a known stairway leading up to the north, and a path to the west. However, Wilda is only going to go west.\n\n");
        if (iRet != 0) return iRet;

        iRet = mutils_addToCommandList ("West", 1021, 4);
        if (iRet != 0) return iRet;
        break;

    default: // case 1 & 2:
        iRet = mutils_addToDialogBuffer ("This is a hallway, with a known stairway leading up to the north, and a path to the south. However, Wilda is only going to go south.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda arrives back at the dead-end that used to be a turn. The stone slab is still sealing off the exit out of the dungeon. Wilda briefly contemplates if she can find the switch that will open it. It is also possible that there is another way out.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda arrives back at the T-intersection where she had fought and killed her first monster. It\'s dead body is still here.\n\n");
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
            iRet = mutils_addToDialogBuffer ("Wilda arrives back at what is now a T-intersection. A path south has opened up. Wilda talks to herself \"Oooh... so the traps open things as well as\"...\n\nWilda is then distracted as there is something moving towards her position from the southern corridor. Wilda sighs \"So much for traps that open things being useful\"...\n\nWilda looks over a the wall and notices that there is a torch stand attached to it. So she strides over, puts her torch in the stand, and heads back to the center of the T-intersection, and draws her sword just as a tentacle monster crawls into the T-intersection from the southern corridor.\n\nThe tentacle monster is huge. Wilda is not scared. Wilda smiles \"So how do YOU want to do this?.. Shall\"...\n\nThe tentacle monster interrupts Wilda by spraying her with some goop. Wilda just wipes it off and responds \"Normally you let ladies go first... but the last time I looked, I wasn\'t one... so I am going to let that slide\"...\n\n");
            if (iRet != 0) return iRet;

            // populate the values for this first monster
            gstructActStateOpponent.iConfidence = 999; // high confidence
            gstructActStateOpponent.iRage = 999; // high rage (fight)
            gstructActStateOpponent.iDesire = 999; // high desire (stay)
            gstructActStateOpponent.iHitPoints = 100; // low hit points
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

    iRet = mutils_addToDialogBuffer ("The monster collapses in the T-intersection. Wilda decides that she isn\'t going to take any chances with such a fearsome opponent so she uses her sword to stab the monster\'s body, several times.\n\nAfter stabbing the monster a sixth time, Wilda notices that it is getting harder to thrust her sword into the monster\'s carcass. When she pulls it out, that is when she notices the blade of the sword has partially melted \"You have to be shitting me\"...\n\nWilda then checks her armor and finds that it has also been damaged \"This is the pits, next time I will have to dodge more often... but\"... Wilda then looks down at her legs to see she is still knee deep in opaque white liquid \"So much for that idea\"...\n\nThe monsters clearly have an advantage in this environment.\n\n");
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
                iRet = mutils_addToDialogBuffer ("Wilda reaches what would be the end of a hallway. It would appear to be a dead end, except that there is a depression in the southern wall.");
                break;

            case 2:
                iRet = mutils_addToDialogBuffer ("Wilda reaches a T-intersection. However, there is a rather suspicious depression in the eastern wall.");
                break;

            default: // case 3:
                iRet = mutils_addToDialogBuffer ("Wilda reaches a turn. However, there is a rather suspicious depression in the eastern wall.");
                break;
            }
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer (" Wilda looks over the depression in the wall and notices that it is a different color to the walls inside the dungeon. \"Is this some sort of door... leading ");
            if (iRet != 0) return iRet;

            if (gstructActStateGlobal.sMapId == 1)
                iRet = mutils_addToDialogBuffer ("south");
            else
                iRet = mutils_addToDialogBuffer ("east");

            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer ("?\"\n\nWilda the looks down and notices that there is a miniature whirlpool in the surface of the opaque liquid near the depression. When she nears the depression, Wilda feels that there is a noticeable current below the surface. Checking the depression, she finds that there is a gap underneath the surface of the liquid.\n\nWilda smiles \"That might lead to the stairs\".\n\n");
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
            iRet = mutils_addToDialogBuffer ("Wilda arrives back at what used to be a dead-end. The southern wall is gone, and the liquid is slowly moving through the southern passageway.\n\n");
            break;

        case 2:
            iRet = mutils_addToDialogBuffer ("Wilda arrives back at what used to be a T-intersection. The eastern wall is gone, and the liquid is slowly moving through the eastern passageway.\n\n");
            break;

        case 3:
            iRet = mutils_addToDialogBuffer ("Wilda arrives back at what used to be a turn. The eastern wall is gone, and the liquid is slowly moving through the eastern passageway.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda is walking along the hallway, when she notices the surface of the liquid is starting to ripple towards and not away from her. Wilda reaches for her sword, only to find it isn\'t there.\n\nWilda then remembers that she does not have her sword anymore. She scrambles to get her only weapon, a spanking paddle, just as the tentacles of the monster appear above the surface of the liquid.\n\nWilda quietly curses herself that she hasn\'t had time to put the lantern somewhere, when the monster sprays Wilda with it\'s goop and withdraws.\n\nWhile watching the monster scramble away through the liquid \"That was... unexpected... huh?\"\n\nWilda starts to feel rather horny. Wilda sighs \"Horrible timing... okay\". Wilda wonders over to a wall of the corridor.\n\n\n[2 minutes later...]\n\nAfter successfully fingering herself to a climax while leaning against the wall, Wilda grabs the her lantern from the improvised hook that she had hung it on.\n\n");
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

        iRet = mutils_addToDialogBuffer ("Wilda walks along a hallway, which she steps on something. Initially Wilda thinks that she just set off another trap, but then she feels the tentacles brush against her legs \"Crap\"...\n\nWilda tries to dart away from the tentacles, but it isn\'t any easier for her to move in the liquid. Fortunately for Wilda, she isn\'t the only one caught off-guard. The tentacle monster that she accidentally wondered onto is just as surprised as she is.\n\nThe tentacle monster launches an all out spray attack first. Wilda is hit multiple times. Then the monster scampers off through the liquid.\n\nWilda\'s libido is now skyrocketing. Wilda sighs \"Fingers aren\'t going to do this time\".\n\nWilda staggers over to the wall of the hallway, while starting to search inside her backpack for the \"holy artifact\" that she picked up from the sanctuary.\n\n\n[4 minutes later...]\n\nWilda ended up cuming 5 times while pleasuring herself with the dildo. In the end, she decided that the dildo was turning out to be so useful, that she might as well just leave it where it is.\n\nWith the dildo still lodged in her pussy, Wilda picks up the lantern.\n\n");
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
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the south. Crystal looks along the collapsed southern pathway ");
            break;

        default:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the east. Crystal looks along the collapsed eastern pathway ");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer ("\"Apologies, we cannot go this way\".\n\nWilda replies \"Would it have been faster if we did?\"\n\nCrystal responds \"Yes, we are but lowly servants for our lord and master\".\n\nWilda interjects \"Don\'t worry about it. Is there another way?\"\n\nCrystal replies \"There is\".\n\nWilda continues \"Then we will go around it\".\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 2:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the south.\n\n");
            break;

        default:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the east.\n\n");
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
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the north. Crystal looks along the collapsed northern pathway. ");
            break;

        case 2:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the south. Crystal looks along the collapsed southern pathway. ");
            break;

        default:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the east. Crystal looks along the collapsed eastern pathway. ");
            break;
        }
        if (iRet != 0) return iRet;

        iRet = mutils_addToDialogBuffer ("Wilda asks Crystal \"Another shortcut?\"\n\nCrystal responds \"Not anymore\".\n\nWilda sighs \"Well... there is nothing for us to do but go around it then\".\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        switch (gstructActStateGlobal.sMapId)
        {
        case 1:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the north.\n\n");
            break;

        case 2:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the south.\n\n");
            break;

        default:
            iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the east.\n\n");
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
        iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the north.\n\n");
        break;

    case 82: // map 1 (82)
        iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the south.\n\n");
        break;

    default: // map 1 (73), and map 3 (123 & 164)
        iRet = mutils_addToDialogBuffer ("There is a collapsed pathway to the west.\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda and Crystal do not venture far from the sanctuary when they encounter a lone tentacle monster.\n\nAs Wilda readies her spanking paddle, Crystal glances at Wilda \"Put that away, I will demonstrate how to handle this\". Crystal licks her lips. Wilda is surprised. Crystal is showing absolutely no fear.\n\nCrystal proceeds to put her spanking paddle inside her backpack, so Wilda decides that she will do the same. Wilda looks at Crystal \"So how do we do this?\"\n\nCrystal turns to look at Wilda, and but tells her what to do \"First, breathe in, then out, breathe in, then out\".\n\nWilda finds herself staring at Crystal\'s rising and falling breasts. Wilda does not respond, but starts unconsciously breathing to the same rhythm as Crystal. Crystal is unconsciously fingering herself.\n\nCrystal continues \"That\'s it... just keep breathing... watching... learning\"...\n\nWilda is still captivated by Crystal\'s jiggling nipples. Wilda starts unconsciously fingering herself as well.\n\nCrystal continues \"Good... there is nothing to be afraid of... nothing to harm us here... just pleasure\"...\n\nWilda responds drowsily with a \"Yes\"...\n\nNeither Crystal or Wilda even look at the tentacle monster, which advances on the pair of them. The tentacles then proceed to wrap around both of the women, while penile head tentacles find their respective pussies.\n\nAs a tentacle impales Wilda\'s slit, the only thing that she can immediately think of is how good a real penis feels inside of her.\n\nMeanwhile, Crystal starts praying \"My lord and master... Cock... we are but slutty playthings for your enjoyment... Fill our wet pussies\"...\n\nThe tentacle monster then fills Wilda\'s and Crystal\'s mouthes while humping away. Wilda unconsciously licks and sucks the tentacle that is violating her mouth.\n\n\n[5 minutes later...]\n\nWilda finally snaps out of her daze, to watch the tentacle monster run away. \"Wow... that really worked?\"\n\nCrystal looks at Wilda \"Of course it did\"...\n\nWilda considers how easy it is for both her and Crystal to face and defeat the local tentacle monsters. Wilda thinks back to her first encounter \"The first one I faced, I killed\"...\n\nCrystal looks at Wilda \"Really?\"..\n\nWilda is slightly perplexed, as she cannot recall how or why she would kill a tentacle monster.\n\nCrystal continues \"You must have did well for your first encounter with our master... Lord... Cock... My sopping wet snatch is always ready for your hot jizz\"...\n\nWilda is concerned as Crystal seems to be slipping into her prayers again. However, Crystal quickly comes out of it.\n\nCrystal looks at Wilda \"And now you know for the next time\"...\n\nWilda responds \"Yes\", with the same blank smile that is almost identical to the one that Crystal has.\n\nCrystal looks around the hallway and states \"We should depart... You still have your quest\"...\n\n");
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
        iRet = mutils_addToDialogBuffer ("Wilda returns back to where she originally encountered Ginger. Ginger is no longer here. Wilda looks around \"Where is she?\".\n\nWilda spends about half a minute searching for any sign of Ginger, but decides that she is a grown adult, and she has her baby to keep her company, so it should not be a problem.\n\n");
        if (iRet != 0) return iRet;

        // override the direction, because we don't know which way we are facing now.
        gstructActStateGlobal.cDirect = 0;
    }
    else
    {
        iRet = mutils_addToDialogBuffer ("Wilda can hear a low murmuring in the hallway. Wilda stops and listens. It is clearly a female voice, but she cannot recognize them. Wilda keeps walking.\n\nSuddenly the murmuring is clearer now. Straight ahead.\n\nWilda stops walking and listens. She can hear what the voice is saying \"Ah... Fuck me... Fuck my cumdump pussy harder... Lord... Cock\"...\n\nWilda smiles, as it sounds like a nun who is praying. Wilda licks her lips, in anticipation that the praying nun is not alone.\n\n\n[30 seconds later...]\n\nWilda certainly found a nun, and she is definitely praying. The nun is on all fours, with her lower arms and legs up to her thighs submerged in the white opaque liquid. She seems to be wearing some form of latex catsuit, with a hood. There are holes in her catsuit for her breasts, belly and genitals. Her swollen breasts and belly are dangling in the liquid.\n\nThe expression on the nuns face is one of pure bliss, as her eyes have partially rolled back into her head. The nun is yelling \"That\'s it... punish my pussy... Yes... Lord... Cock... More... Fuck my naughty pussy rough and hard... I am a masochistic sex slave for for you to FUUUCKK\". The nun whips her head back and sits up. Breathing heavily.\n\nWilda looks around. She can see no sign of a delightful monster to fuck, so she is wondering how the nun is able to pray so much. Wilda decides to wonder over to the nun.\n\n\n[1 minute later...]\n\nThe nun finally recovers enough to notice that Wilda is standing there. The nun looks up and down Wilda and asks \"Have you considered Hedonism?\"\n\nWilda automatically replies \"I have. It feels really good\".\n\nThe nun grins even wider \"On a quest?\"\n\nWilda replies \"Yes. I am Wilda\".\n\nThe nun response \"I am Ginger. Sorry, but I cannot offer you help with your quest right now\".\n\nWilda cocks her head \"Not a problem, but why are you here?\"\n\nGinger pats her swollen belly \"This little master will be ready to come out and fuck soon\". Wilda then notices that Ginger\'s belly shuddered. Ginger continues \"Ooooh... He is active again\". Ginger then looks at Wilda\'s belly \"Good luck with your little one\".\n\nWilda replies \"Thank you. Do you need any help?\"\n\nGinger responds \"No, but thank you for the offer. Ooooh... He is starting to... Fuck my pussy from the inside again\". Ginger\'s belly starts convulsing, and Ginger falls back on all fours. \"That\'s it... Punish my obscene fuck hole again\"... \n\nWilda is curious, so she walks around to look at Ginger\'s butt. That is when she sees the small tentacles sliding in and out of Ginger from inside her pussy. Wilda looks on in wonder \"Wow\"...\n\nGinger is starting to get into the sex with her tentacle monster child \"Lord... Cock... Fuck me more and more... Harder... No puny human dick can ever satisfy my ruined pussy... I belong only to YOUuuu\"... Ginger arches her back. Then keeps on having sex with her baby tentacle monster. Some of the small tentacles protruding from Ginger\'s pussy starts assaulting Ginger\'s gaping anus.\n\nWilda pats her own swollen belly while staring at Ginger \"You are so lucky, being fucked by your baby so soon\". Wilda then looks down at her own belly \"I cannot wait till this one is ready to hatch\".\n\nWilda decides that Ginger and her baby are in no immediate danger, so she continues walking past and away from them.\n\n");
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

    iRet = mutils_addToDialogBuffer ("Wilda arrives at the base of a staircase that is rising up out of the opaque liquid. The stone steps are rather large stone blocks that have been expertly crafted. This staircase is somewhat familiar, as Wilda can remember that she came this way with... Crystal... that\'s right... Wilda walked down these stairs with Crystal.\n\nHowever, these stairs lead up. Wilda\'s destination is down, so there is no point in using these stairs to go up.\n\n");
    if (iRet != 0) return iRet;

    iRet = mutils_addToDialogBuffer ("Wilda came from the west, and is facing east. This is a hallway, with known stairs leading up to the west, and a path to the east. However, Wilda is only going to go east.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("As Wilda walks to the end of the passageway, she hears an audible clicking noise, then the sound of stone sliding against stone from behind her. Wilda looks around and wonders to herself \"Did I just... set off another trap?\"\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("As Wilda is walking along the passageway, she hears something that sounds like steel smashing against stone, followed by stone sliding against stone in the distance. Wilda calmly looks around to see if there are any opponents who have suddenly shown up. After about 10 seconds she is satisfied that there is no danger here.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda hears the sound of stone sliding against stone from a nearby wall. Wilda patiently waits, to see if there is any danger that is going to show up. Wilda decides to draw her sword.\n\n\n[1 minute later...]\n\nAfter waiting for a while, Wilda decides that she is wasting time, and she should keep moving. Wilda puts her sword away.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda arrives at a turn in the a passageway, when she notices that the liquid is rippling. Wilda grabs her sword to get ready for another monster encounter when she hears the sound of stone sliding against stone in the distance.\n\n\n[1 minute later...]\n\nWilda puts her sword away. There is no immediate danger here.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Just as Wilda arrives at the end of a passageway, she is startled by the sound of the wind blowing. As Wilda readies her sword for an impending attack, she hears stone thumping against stone in the distance.\n\n\n[1 minute later...]\n\nNo monsters showed themselves, so Wilda puts her sword away.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda hears something that sounds like gurgling from the wall next to her, then the sound of stone sliding against stone in the distance. Wilda looks around to see if there is anything out of place. No monsters appear, so Wilda decides that she should keep moving.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda is walking along the partially submerged passageway, when she she almost trips up on something. Wilda looks around to see if anything is out of place when she hears the sound of sound of stone sliding against stone in the distance.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda reaches a dead-end. Wilda sighs, and is distracted by a popping sound. She readies her paddle, and hears a faint banging sound in the distance.\n\n\n[1 minute later...]\n\nWilda relaxes her posture. A monster did not appear.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda reaches the end of the passageway, which is a dead-end. As she thinks to herself that this path was pointless and that she will have to turn back, she can hear the sound of stone grinding against stone in the distance. She briefly considers readying her paddle, and looks around. The surface of liquid is still and there are no monsters bearing down on her. Wilda decides to keep moving.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda arrives at the end of a corridor, when there is a loud bang. Wilda grabs her paddle and readies herself for another monster when she hears the sound of stone sliding against stone in the distance.\n\n\n[1 minute later...]\n\nNo monsters appeared, so Wilda decides to that maybe she should keep moving.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda stops at the end of the passageway. This isn't a turn, this is a dead-end. Wilda looks around and notices something hanging down the wall. She looks over it and realizes that it is a tentacle hanging out of a small hole in the wall. Startled, Wilda steps back and readies her paddle. As she does, the tentacle quickly pulls back into the hole, and there is a banging sound on the other side of the wall. Wilda remains on alert for the following attack.\n\n\n[1 minute later...]\n\nWilda is still waiting for the monster to attack, but she is staring at what is an empty hole in the wall. Wilda hears the sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\nWilda relaxes her posture. The monster did not attack, and the small hole in the wall is still empty.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda arrives at the end of a passageway, when she hears a loud clapping sound. Wilda readies her paddle for the monster attack as she hears the sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\nAfter waiting for a monster attack that did not happen, Wilda decides to relax. She decides that she should get going.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda arrives at the end of a rather noisy passageway. It sounds like there is a waterfall on the other side of the wall. Intrigued, Wilda checks the wall, when the sound suddenly stops \"That was weird\"...\n\nWilda decides to keep checking the wall.\n\n\n[1 minute later...]\n\nAfter checking the 3 walls of the dead-end, Wilda decides that there isn't anything of interest here, and she should get going.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda arrives at the end of a pathway, which is a dead-end. While looking around to see if there are any monsters hiding in this corner of the dungeon, a large rock falls down behind her and splashes into the liquid. Wilda immediately draws her paddle, ready to face an opponent. While waiting for the monster to attack, Wilda hears stone grinding sounds from the walls around her.\n\nWilda decides that it isn't safe to stay in this corridor.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Just as Wilda arrives at the end of a passageway, there is a shudder from the walls. Wilda draws her paddle expecting an attack.\n\n\n[1 minute later...]\n\nWilda decides to relax, and was about to put the paddle away when walls shudder again. While Wilda contemplates if she should stay and fight or exit from this dead-end, the walls shudder again.\n\nWilda checks around her, and comes to the conclusion that maybe it isn't safe to stay here.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("As Wilda arrives at the end of a passageway, there is a groaning noise in the distance. Startled, Wilda draws her paddle, and readies herself for the attack. While waiting there is a sound of stone grinding against stone in the distance.\n\n\n[1 minute later...]\n\nAfter waiting patiently for a monster to appear, Wilda decides that there is no immediate threat and that she should get going. Wilda puts the paddle away.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            if (gstructActStateGlobal.sMapId == 3)
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the end of a corridor.");
            else
                iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at a turn in the pathway.");
            if (iRet != 0) return iRet;

            iRet = mutils_addToDialogBuffer (" Crystal calls out to Wilda \"Just a moment\".\n\nWilda asks Crystal \"What is it?\", and watches Crystal walk over to a wall, and place her hand on a stone that is jutting out of it.\n\nCrystal looks at Wilda \"Shall I?\"\n\nWilda responds \"Why not?\"\n\nCrystal pushes the stone in, there is an audible clunk followed by a gurgling sound from the wall next to the stone. In the distance there is the sound of stone grinding against stone. Crystal looks at Wilda \"There, a door should be open now\".\n\nWilda thinks to herself that it is handy to have Crystal along.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the end of a corridor. There is a tentacle hanging out of a hole in the wall. Wilda licks her lips, but is then surprised when Crystal just walks past her, over to the tentacle.\n\nCrystal lightly grabs the tip of the tentacle, bends down and kisses it. The tentacle snakes back into the wall, and there is a banging sound from behind the wall. Crystal turns to look at Wilda \"Please wait\".\n\nWilda looks dumbfounded \"For?\"\n\nThere is a grinding sound behind the wall, followed by another grinding sound off in the distance. Crystal looks at the hole in the wall and blows a kiss, then turns to Wilda \"A door should be open now\".\n\nWilda responds \"Thank you, that is rather useful\".\n\nCrystal replies \"No need... This is all part of the service to my lord... Cock\"...\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at a turn in the pathway. While Wilda considers if they should go back the way they came or follow the pathway, she is interrupted by Crystal \"Can I... have your assistance?\"\n\nWilda looks at Crystal \"Sorry?\"\n\nCrystal continues \"I am going to need your help with this\".\n\nWilda responds \"Okay... what you need help with?\"\n\nCrystal replies \"Just follow my lead\", then she walks over to Wilda and kisses her.\n\nWilda is caught up with the moment to not go along with it.\n\n\n[1 minute later...]\n\nWhile Wilda and Crystal are fingering each other, there is an audible click in the walls. Crystal pulls her tongue out of Wilda's mouth, when the sound of stone sliding against stone starts, and asks \"Shall we continue... Or shall we continue?\"\n\nWilda replies \"Both work for me\", then starts kissing Crystal again.\n\n\n[2 minutes later...]\n\nCrystal and Wilda are standing in the middle of the corridor. Crystal looks at Wilda \"Now we can continue\".\n\nWilda replies \"I agree\".\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at a turn in the corridor. Crystal calls out to Wilda \"Shall I?\"\n\nWilda looks at Crystal \"Is there another door?\"\n\nCrystal nods \"Yes\", then walks over to a wall, and clenches her fist and bangs it. A sound somewhere between flatulence and belching fills the corridor.\n\nWilda just stands there waiting for something else to happen. Crystal closes her eyes listens. Crystal breathes in and out, then thumps the wall twice again. There are smacking sound from the other side of the wall, and Crystal opens her eyes.\n\nCrystal looks at Wilda \"We should go now\".\n\nWilda responds \"Okay\", then hears the sound of stone grinding against stone in the distance.\n\n");
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

                iRet = mutils_addToDialogBuffer (szWorking);
                if (iRet != 0) return iRet;
            }

            iRet = mutils_addToDialogBuffer ("Wilda and Crystal arrive at the end of the pathway, which is a dead-end. Wilda sighs, and looks at Crystal \"I guess we need to turn back\".\n\nCrystal saunters past Wilda over to a part of the floor, stops and turns towards Wilda \"Not just yet\".\n\nCrystal closes her eyes and lightly jumps. There is a splash of liquid, not just from Crystal\'s movement, but there are ripples coming from the walls. Wilda looks around as there are a series of loud bangs from the other side of each of the 3 walls of the dead-end.\n\nThe bangs are followed by the sound of stone sliding against stone in the distance. Crystal looks at Wilda again \"There, it is done, we can continue now\".\n\nWilda responds \"Great\".\n\n");
            if (iRet != 0) return iRet;

            // override the direction, because we don't know which way we are facing now.
            gstructActStateGlobal.cDirect = 0;
        }
    }

    return 0;
}


