
#include "brain.h"

Brain::Brain(Client* c,Camera* k,std::string mastername)                         
{

    //Manager for inventory
    myInvManager=new Myinv(c);

    //factory for making complex actions
    actionFac=new ActionFactory(c);

    // usused ai vars
    time_last_move=-1;
    time_last_dig=-1;
    time_last_extend=-1;

    
    happiness=100;

    // control
    LeftB = false;
    rightbutton=false;
    forwardstate=false;
    backstate=false;
    leftstate=false;
    rightstate=false;
    jumpstate=false;
    specialstate=false;
    sneakstate=false;
   
    // for insert action 
    inserted=false;
    acted=false;

    GetRightClicked=false;
    GetLeftClicked=false;
  
    // last positions 
    lastposition=v3f(0,0,0); 
    lastyaw=10000; 
    //lastdistance=-1; 
    last_materialsx.reserve(3);
    
    //printf("init");
    // Set main container
    brainact=new Brainaction("MAIN_CONTAINER"); 
    brainact->setActionDescription("main_container");
    brainact->actiondescription="the main container maincontrol";
    
    // Declare current act
    currentact=brainact;

    // used by the wait function
    lasttime=-1;

    botYaw=0.0;
    botPitch=0;

    // counts number of step taken by brain
    number_of_steps=1;
    reacted_to_chat=false;

    clientobj=c;
    kamera=k;
    master=mastername;
}

// Functions called from other objects
const bool Brain::getDigStatus() 
{ return LeftB; }

const bool Brain::getRightButtonState()
{ return rightbutton; }

const f32 Brain::getBotYaw() 
{ return botYaw; }

const f32 Brain::getBotPitch() 
{ return botPitch; }

void Brain::setDigStatus(bool dig) 
{ LeftB=dig; }

void Brain::addMessline(ChatLine linnne)
{ currentchatlist.push_back(linnne); }

void Brain::clearMessline()
{ currentchatlist.clear(); }

bool Brain::getForwardState()
{ return forwardstate; }

bool Brain::getBackState()
{ return backstate; }

bool Brain::getLeftState()
{ return leftstate; }

bool Brain::getRightState()
{ return false; }

bool Brain::getJumpState()
{ return jumpstate; }

bool Brain::getSpecialState()
{ return specialstate; }

bool Brain::getSneakState()
{ return sneakstate; }

bool Brain::getRightClicked()
{ return GetRightClicked; }
	
void Brain::resetRightClicked()
{ GetRightClicked=false; }

bool Brain::getLeftClicked()
{ return GetLeftClicked; }
	
void Brain::resetLeftClicked()
{ GetLeftClicked=false; }

// Checkaction

bool Brain::checkAction(LocalPlayer *player,Brainaction *ba, ClientEnvironment *env)
{

    v3f destinationposition=ba->getDestinationCoords();
    v3f playerposition=player->getPosition();
    v3f playerposition_noY=v3f(playerposition.X,ba->getDestinationCoords().Y-0.01,playerposition.Z);

    std::string act=ba->getBrainAction();

    v3f destinationposition_playerlevel=v3f(destinationposition.X,playerposition.Y,destinationposition.Z);
    float distance=playerposition.getDistanceFrom(destinationposition_playerlevel);

    // sample structure for checkactions
    if (act.compare("STOP_SNEAK")==0)
        {
            return false;
        }

    if (act.compare("GET_HOTBAR")==0)
        {
            int slot=atoi((ba->botmessage).c_str());

	    //InventoryLocation playerinventoryloc;
	    //playerinventoryloc.setCurrentPlayer();
            //Inventory *playerinv=clientobj->getInventory(playerinventoryloc);

            //InventoryList *playermlist = playerinv->getList("main");
            //removed check if mlist was null
            //ItemStack playeritem = playermlist->getItem(slot);
            std::string thingInHotBarSlot=myInvManager->getInventoryItem(clientobj,slot,"main");
            printf("item in hotbarslot %i was %s\n",slot,thingInHotBarSlot.c_str());
            //int invpicknum=myInvManager->getLowestInvNumber(clientobj,kind,"main");
            
            if(thingInHotBarSlot.compare("")==0)
            {
                printf("hotbarslot is empty\n");
                return false;
            }
            else
            {
                // is maininventory full?






            int emptyMainInvSlot=myInvManager->getLowestEmptyNonhotbar(clientobj);

            // check that we have space in main inv to put stuff in 
            if (emptyMainInvSlot==-9)
            {
                // no free space in main inventory, throw away stuff
                printf("EMPTY_INV has no space in main INV, inserting THROW_AWAY\n"); 
                Brainaction *insertorder=new Brainaction("THROW_AWAY");
                insertorder->botmessage="nonhotbar";
                insertorder->actiondescription="throwing away";
                
                currentact=preinsertOrder(insertorder,ba);
            return true;
            }




            return false;
            }
            return false;
        }

    if (act.compare("DIG")==0)
        {
            std::string current_equipped=myInvManager->getEquipped();
            if (current_equipped.compare("default:pick_stone")!=0)
            {
                printf("current item %s\n",current_equipped.c_str());
                printf("pickaxe not equipped, equipping\n");
                    Brainaction *insertorder=new Brainaction("EQUIP_ITEM");
                    insertorder->actiondescription="equip pickaxe from dig checkaction";
                    insertorder->botmessage="default:pick_stone";

                    currentact=preinsertOrder(insertorder,ba);
            }
            return false;
        }
    if (act.compare("EQUIP_ITEM")==0)
    {
        std::string itemToEquip=ba->botmessage;
            printf("wish to equip   %s\n",itemToEquip.c_str());

        int itemnum=myInvManager->getLowestInvNumber(clientobj,itemToEquip,"main","all");

            std::string current_equipped=myInvManager->getEquipped();
            printf("equipeed ites is  %s\n",current_equipped.c_str());

            if (current_equipped.compare(itemToEquip)==0)
            {
                printf("corrct item equipped\n");
                return false;
            }
            else if (itemnum==-9)
            {

                printf("do not have %s\n",itemToEquip.c_str());
                if (myInvManager->canCraftSomeHow(clientobj,itemToEquip,"nonhotbar"))
                    {
                    Brainaction *insertorder=new Brainaction("CRAFT");
                    insertorder->actiondescription="inserted craft";
                    insertorder->botmessage=itemToEquip;

                    currentact=preinsertOrder(insertorder,ba);
//                    currentact=insertorder;
                    }
                else
                    {
                        printf("did not have material to make %s\n",itemToEquip.c_str());
                    std::wstring botms_wide=narrow_to_wide("did not have materasls");
        // chat
                    clientobj->typeChatMessage(botms_wide);
                    }

            return true;
            }
            else
            {
                int hotBarSlot=getDesignatedHotbarSlot(itemToEquip);
                myInvManager->moveInventories(clientobj, "main" ,itemnum ,"main", hotBarSlot ,0);
                clientobj->selectPlayerItem(hotBarSlot);
            // we has item
            }
            return false;
        }


    if (act.compare("CRAFT")==0)
    {
        std::string thingToCraft=ba->botmessage;
        // First of all,do we even need the object?
        int itemnum=myInvManager->getLowestInvNumber(clientobj,thingToCraft,"main","nonhotbar");
        if (!(itemnum!=-9))
        {
            bool correctcraft=myInvManager->craftInvOK(clientobj, thingToCraft);

            if (!(correctcraft))
            {
                bool craftInventoryEmpty=myInvManager->getIsInventoryEmpty(clientobj,"craft");
                // is craft inv empty?
                if (!(craftInventoryEmpty))
                {
                    Brainaction *insertorder=new Brainaction("EMPTY_INV");
                    insertorder->actiondescription="testing insert";
                
                    currentact=preinsertOrder(insertorder,ba);
                    return true;
                }
            }

            else if (!(myInvManager->hasMaterialsToCraft(clientobj,thingToCraft,"nonhotbar")))
            {
                std::string whatToMake=myInvManager->missingMaterials(clientobj,thingToCraft,"nonhotbar");

                if (whatToMake.compare("-a")==0)
                {
                    printf("mad because of lack of %s\n materials",thingToCraft.c_str());
                    return false;
                }
                // try to make materials
                else
                {
                    Brainaction *insertorder=new Brainaction("CRAFT");
                    insertorder->actiondescription="inserted craft";
                    insertorder->botmessage=thingToCraft;

                    currentact=preinsertOrder(insertorder,ba);
                    //insert craftthing
                return true;
                }
            }

        }
        return false;
    }

    if (act.compare("EMPTY_INV")==0)
    {
        int emptyMainInvSlot=myInvManager->getFirstEmptyInvSpot(clientobj,"main");
        // check that we have space in main inv to put stuff in 
        if (emptyMainInvSlot==-9)
        {
            // no free space in main inventory, throw away stuff
            printf("EMPTY_INV has no space in main INV, inserting THROW_AWAY\n"); 
            Brainaction *insertorder=new Brainaction("THROW_AWAY");
                insertorder->botmessage="nonhotbar";
            insertorder->actiondescription="throwing away";

            //insertorder->inserted=true;

            //ba->subacts.push_front(insertorder);
            //insertorder->setParent(currentact);
            //insertorder->just_inserted=true;
            
                    currentact=preinsertOrder(insertorder,ba);
            //currentact=insertorder;
        return true;
            //preinsertOrder(insertorder,ba);
        }
        return false;
    }

    else if (act.compare("MOVE_TO_POSITION_BACKWARD")==0)
    {
        printf("fine whatever\n");
        return false;
    }

    else if (act.compare("MOVE_TO_POSITION_FORWARD")==0)
    
    // Move to position but dont jump
    {
    printf("did for\n");
        std::string turned000=getDirectionMaterial(player,env,0, 0, 0);
        std::string turned0_10=getDirectionMaterial(player,env,0, -1, 0);
        std::string turned0_20=getDirectionMaterial(player,env,0, -2, 0);

        if(!(isStandable(turned0_10)))
        {
            printf("almost jumped into shit in forward ==============================================================\n");
            ba->finished=true;
            return false;
        }

        if(!(isStandable(turned0_10)) and !(isStandable(turned000)))
        {
            if(!(isStandable(turned0_20))) 
            {
                    printf("almost jumped into shit===================MOVE_TO_POSITION_FORWARD_JUMP===========================================\n");
                    ba->finished=true;
                    return false;
                }
            }
            float player_yaw=player->getYaw();
            float yaw_to_destination=getYawToPosition(playerposition,ba->getDestinationCoords());
            float angledifference=getNormalizedDegreeDifference(player_yaw, yaw_to_destination);
            if (angledifference>15)
            {
                printf("FORWARD: walking AWAY from target?========================================================\n");
                ba->finished=true;
            }
                    return false;
    }
    else if (act.compare("MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK")==0)
        // Move to position but dont jump
        {
        printf("destpos %f %f %f playerpos %f %f %f\n",destinationposition.X,destinationposition.Y,destinationposition.Z,playerposition.X,playerposition.Y,playerposition.Z);
    v3f destinationposition=ba->getDestinationCoords();
    v3f playerposition=player->getPosition();
            //printf("distance %f lastdistacne %f\n",distance,ba->lastdistance);
            if (distance<ba->lastdistance && ba->lastdistance!=-9) 
            { printf("running wrong way?\n"); }
            std::string turned0_10=getDirectionMaterial(player,env,0, -1, 0);
            //if(!(isStandable(turned0_10)))
            //{
                        //printf("almost jumped into shit but ignored it====== in NO ENV CHECK========================================================\n");
                        //ba->finished=true;
            //}

            float player_yaw=player->getYaw();
            float yaw_to_destination=getYawToPosition(playerposition,ba->getDestinationCoords());
            float angledifference=getNormalizedDegreeDifference(player_yaw, yaw_to_destination);
            if (angledifference>15)
            {
                printf("walking AWAY from target?================= in no ENV CHECK=======================================\n");
                ba->finished=true;
            }
                    return false;
    }

    else if (act.compare("MOVE_TO_POSITION_FORWARD_JUMP")==0)
        {
            // Check positions for possible jump
            std::string turned000=getDirectionMaterial(player,env,0, 0, 0);
            std::string turned010=getDirectionMaterial(player,env,0, 1, 0);
            std::string turned020=getDirectionMaterial(player,env,0, 2, 0);
            std::string abs020=getAsoluteMaterial(player,env,0, 2, 0);
            std::string turned0_10=getDirectionMaterial(player,env,0, -1, 0);
            std::string turned0_20=getDirectionMaterial(player,env,0, -2, 0);

            jumpstate=false;

            // if front is not air, but others are
            // jump up one step
            if (isStandable(turned000)&& !isStandable(turned010) && !isStandable(turned020) && !isStandable(abs020))
            {
                printf("should have jumped!!!!!!!!\n");
                jumpstate=true;
            }

            // -1 is air or water, stop
            if(!(isStandable(turned0_10)) and !(isStandable(turned000)))
            {
                if(!(isStandable(turned0_20))) 
                {
                    printf("almost jumped into shit===================MOVE_TO_POSITION_FORWARD_JUMP===========================================\n");
                    ba->finished=true;
                }
            }

            float player_yaw=player->getYaw();
            float yaw_to_destination=getYawToPosition(playerposition,ba->getDestinationCoords());
            float angledifference=getNormalizedDegreeDifference(player_yaw, yaw_to_destination);
            if (angledifference>15)
            {
                printf("walking AWAY from target?========================================================\n");
                ba->finished=true;
            }
        }
        return false;

}
// End of checkaction


// Checkfinished
bool Brain::checkFinished(LocalPlayer *player,Brainaction *ba, ClientEnvironment *env)
{
    v3f destinationposition=ba->getDestinationCoords();
    v3f playerposition=player->getPosition();
    v3f destinationposition_playerlevel=v3f(destinationposition.X,playerposition.Y,destinationposition.Z);

    float distance=playerposition.getDistanceFrom(destinationposition_playerlevel);
    float mindist=ba->getDestinationTolerance();
    
    bool myfinished=false;
    std::string act=ba->getBrainAction();
    std::string checkfinished_act=ba->getBrainAction();

// It this is true, why not just return false 
        //if (ba->just_inserted==true)
       // { return false;}

    if (checkfinished_act.compare("MOVE_TO_POSITION_FORWARD")==0 || checkfinished_act.compare("MOVE_TO_POSITION_FORWARD_JUMP")==0)
        {
            ((distance<=mindist) || (ba->finished==true))?myfinished=true:myfinished=false;
        }

    if (checkfinished_act.compare("MOVE_TO_POSITION_BACKWARD")==0 || checkfinished_act.compare("MOVE_TO_POSITION_BACKWARD_JUMP")==0)
        {
            ((distance<=mindist) || (ba->finished==true))?myfinished=true:myfinished=false;
        }

    if (checkfinished_act.compare("MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK")==0)
    {
        printf("distance %f mindist %f\n",distance,mindist);
        ((distance<=mindist) || (ba->finished==true))?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("TURNYAW_TO")==0)
    // not used
    {
        float player_yaw=player->getYaw();
        float yaw_to_destination=getYawToPosition(playerposition,ba->getDestinationCoords());
        float angledifference=getNormalizedDegreeDifference(player_yaw, yaw_to_destination);
        (angledifference<0.5)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("TURNYAW_DEGREES")==0)
    {
        float angledifference=abs(ba->getDestinationYaw()-player->getYaw());
        (angledifference<0.5)?myfinished=true:myfinished=false;
    }

    else if (checkfinished_act.compare("CRAFT")==0)
    {
        std::string itemToCraft=ba->botmessage;
        int itemnum=myInvManager->getLowestInvNumber(clientobj,itemToCraft,"main","nonhotbar");
        printf("itemnumber is,  %s at %i\n",itemToCraft.c_str(),itemnum);
        if (itemnum!=-9)
        { 

printf("craft is finished, there is a %s at %i\n",itemToCraft.c_str(),itemnum);
myfinished=true; 

}
        else
        {
        // I guess craft is also finished if we already have the item in question in desired amounts
        //(ba->finished==true) ?myfinished=true:myfinished=false;
        printf("checking stranger craft finished opetion\n");
        myfinished=false;
        //((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
        }
    }

    else if (checkfinished_act.compare("EMPTY_INV")==0)
    {
        if (ba->just_inserted==true)
        { ba->finished=false; }
        else
        {
            int emptyMainInvSlot=myInvManager->getFirstNonEmptyInvSpot(clientobj,"craft");
            if (emptyMainInvSlot==-9)
            {
                myfinished=true;
            }
            else
            {
                myfinished=false;
            }
        }

    }

    else if (checkfinished_act.compare("THROW_AWAY")==0)
    {
        if (ba->just_inserted==true)
        { ba->finished=false; }
        else
        {
            int emptyMainInvSlot=-9;
                if (ba->botmessage.compare("nonhotbar")==0)
            {
            emptyMainInvSlot=myInvManager->getLowestEmptyNonhotbar(clientobj);
            }
            else
            {
                emptyMainInvSlot=myInvManager->getFirstEmptyInvSpot(clientobj,"main");
            }
            if (emptyMainInvSlot==-9)
            {
                myfinished=false;
            }
            else
            {
                myfinished=true;
            }
        }
    }

    else if (checkfinished_act.compare("TURNPITCH_TO")==0)
    {
        if (ba->finished==true)
        { myfinished=true; }
        else
        { myfinished=false; }
    
    }
    else if (checkfinished_act.compare("TURNPITCH_DEGREES")==0)
    {
        float player_yaw=player->getPitch();
        float yaw_to_destination=ba->getDestinationPitch();
        float pitchangledifference=getNormalizedDegreeDifference(player_yaw, yaw_to_destination);
        (pitchangledifference<0.5)?myfinished=true:myfinished=false;
        if (ba->finished==true)
        { myfinished=true; }
        else
        { myfinished=false; }
    
    }
    else if (checkfinished_act.compare("WAIT")==0)
    {
        (ba->waited_time>ba->waittime)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("STOP")==0)
    {
        (   forwardstate==false && LeftB==false && backstate==false && 
            rightbutton==false && leftstate==false && rightstate==false && 
            jumpstate==false&& specialstate==false)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("GET_HOTBAR")==0)
    {
        if (ba->finished==true)
        { myfinished=true; }
        else
        {
            int slot=atoi((ba->botmessage).c_str());

	    InventoryLocation playerinventoryloc;
	    playerinventoryloc.setCurrentPlayer();
            Inventory *playerinv=clientobj->getInventory(playerinventoryloc);

            InventoryList *playermlist = playerinv->getList("main");
            //removed check if mlist was null
            ItemStack playeritem = playermlist->getItem(slot);
            
            if(playeritem.name.compare("")==0)
            { myfinished=true; }
            else
            { myfinished=false; }
        }
    }

    else if (checkfinished_act.compare("GO_CHEST")==0)
    {
        ((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("CENTER")==0)
    {
        // typical for self-filling containers
        ((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
    }

    else if (checkfinished_act.compare("CHAT")==0)
    {
        (ba->finished==true) ?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("START_SNEAK")==0)
    {
        (ba->finished==true) ?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("STOP_SNEAK")==0)
    {
        (ba->finished==true) ?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("REAL_RIGHT_CLICK")==0)
    {
        (ba->finished==true)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("RELEASE_RIGHT_CLICK")==0)
    {
        (ba->finished==true)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("GO_EDGE")==0)
    {
        ((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("DIG")==0)
    {

        last_materialsx.clear();
        int arrsizex=3;
        for (int x=0; x<arrsizex; x++)
        {
            last_materialsx.push_back(getAsoluteMaterial(player,env,BS*(x-1),0,0));
            //last_materialsx[x]= getAsoluteMaterial(player,env,BS*(x-1),0,0);
        }
        for (int x=0; x<arrsizex; x++)
        {
            printf("mat %i %s\n",x,last_materialsx[x].c_str());
            //last_materialsx[x]= getAsoluteMaterial(player,env,BS*(x-1),0,0);
        }
        // clumpsy, asulutemtaerial takes integers
        int abx=int(ba->getDestinationCoords().X/10);
        int aby=int(ba->getDestinationCoords().Y/10);
        int abz=int(ba->getDestinationCoords().Z/10);

        std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
        v3f dig_position=playerposition+v3f(0,-0.5*BS,0)+v3f(ba->getDestinationCoords().X,ba->getDestinationCoords().Y,ba->getDestinationCoords().Z);

        if (!isDiggable(currentmat))
        { myfinished=true; }
        else
        { myfinished=false; }
    }
    else if (checkfinished_act.compare("DIGACT")==0)
    {
        ((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
        // It makes him happy to complete dig acts
        ((ba->finished==true) and (ba->subacts.size()<1))?happiness+=1:happiness+=0;
    }
    else if (checkfinished_act.compare("CONTAINER")==0)
    {
        (ba->subacts.size()<1)?myfinished=true:myfinished=false;
    }
    else if (checkfinished_act.compare("FOLLOW_MASTER")==0)
    {
        ((ba->finished==true) and (ba->subacts.size()<1))?myfinished=true:myfinished=false;
        // It makes him happy to follow master 
        ((ba->finished==true) and (ba->subacts.size()<1))?happiness+=1:happiness+=0;
    }

    else if (checkfinished_act.compare("GET_FROM_CHEST")==0)
    {
        ((ba->finished==true))?myfinished=true:myfinished=false;
    }

    else if (checkfinished_act.compare("EQUIP_ITEM")==0)
    {
        if (ba->just_inserted==true)
        { ba->finished=false; }
        else
        {
            std::string kind=ba->botmessage;
   
            std::string current_equipped=myInvManager->getEquipped();
            {
                printf("equipped item is %s\n",current_equipped.c_str());
                }
            if (kind.compare(current_equipped)==0)
            {
                 myfinished=true; 
            }
            else
            {
            
             myfinished=false; 
            }
        }
    }

    else if (checkfinished_act.compare("MAIN_CONTAINER")==0)
    {
        ((ba->subacts.size()<1) || (ba->finished==true))?myfinished=true:myfinished=false;
    }

    // set some variables at end of checkfinished
    // should be set in step?
    lastposition=playerposition; 
    float jawtoposition=getYawToPosition(playerposition,ba->getDestinationCoords());
    lastyaw=jawtoposition; 
    ba->lastdistance=distance; 

    if (myfinished==true)
    { return true; }
    else
    { return false; }
}
// End of checkfinished

bool Brain::performAction(LocalPlayer *player,Brainaction *ba, ClientEnvironment *env)
{
    v3f destinationposition=ba->getDestinationCoords();

    v3f playerposition=player->getPosition();

    v3f playerposition_noY=v3f(playerposition.X,destinationposition.Y,playerposition.Z);

    forwardstate=false;

    std::string performAct=ba->getBrainAction();

    if (performAct.compare("TURNYAW_TO")==0)
    {
        float myyaw=getYawToPosition(playerposition_noY,destinationposition);
        botYaw=myyaw; 
        return true;
    }

    if (performAct.compare("GET_HOTBAR")==0)
    {            
        int slot=atoi((ba->botmessage).c_str() );

        InventoryLocation playerinventoryloc;
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=clientobj->getInventory(playerinventoryloc);

        InventoryList *playermlist = playerinv->getList("main");
        int lowemp=myInvManager->getLowestEmptyNonhotbar(clientobj);

        if (lowemp==-9)
        //no empty positions
        {
            int throwslot=myInvManager->getLowestInvNumberThrow(clientobj,"");
            if (throwslot!=-9)
            {
                IDropAction *ba = new IDropAction();
                ba->count = 0;
                ba->from_inv.setCurrentPlayer();
                ba->from_list = "main";
                ba->from_i = throwslot;
                clientobj->inventoryAction(ba);

                ItemStack playeritemstack = playermlist->getItem(slot);
        
                IMoveAction *a = new IMoveAction();
                a->count = playeritemstack.count;
                a->from_inv = playerinventoryloc;
                a->from_list = "main";
                a->from_i = slot;
                a->to_inv.setCurrentPlayer();
                a->to_list = "main";
                a->to_i = throwslot;
            clientobj->inventoryAction(a);
            }
        }
        else
        {
            // switch it is empty, move itme slot to switch
            ItemStack playeritemstack = playermlist->getItem(slot);

            IMoveAction *a = new IMoveAction();
            a->count = playeritemstack.count;
            a->from_inv = playerinventoryloc;
            a->from_list = "main";
            a->from_i = slot;
            a->to_inv.setCurrentPlayer();
            a->to_list = "main";
            a->to_i = lowemp;
            clientobj->inventoryAction(a);
        }
        return true;
    }

    else if (performAct=="TURNYAW_DEGREES")
    {
        float myyaw2=ba->getDestinationYaw();
        botYaw=myyaw2; 
        return true;
    }
    else if (performAct=="CRAFT")
    {
        printf("trying to craft\n");
        bool result2=myInvManager->moveMaterialsToCraft(clientobj,ba->botmessage);
        InventoryLocation playerinventoryloc2;  
        playerinventoryloc2.setCurrentPlayer();
        Inventory *playerinv2=clientobj->getInventory(playerinventoryloc2);
        InventoryList *craftlist = playerinv2->getList("craftresult");


    if(craftlist != NULL)
    {
        int movetonumber=myInvManager->getLowestEmptyNonhotbar(clientobj);

        if (movetonumber==-9)
        { 
            printf("could not move craft items to main inv\n");
        }
        else
        {
            printf("performing craftaction\n");
            ICraftAction *a = new ICraftAction();
            a->count = 0;
            a->craft_inv = playerinventoryloc2;
            clientobj->inventoryAction(a);
        
            IMoveAction *av = new IMoveAction();
            av->count = 0;
            av->from_inv = playerinventoryloc2;
            av->from_list = "craftresult";
            av->from_i = 0;
            av->to_inv.setCurrentPlayer();
            av->to_list = "main";
            av->to_i = movetonumber;
            clientobj->inventoryAction(av);

        //bool result2=myInvManager->moveMaterialsToCraft(clientobj,ba->botmessage);
            ba->finished=true;
        }
    }    return true;
    }
    else if (performAct=="TURNPITCH_TO")
    {
        float mypitch=getPitchToPosition(player,ba->getDestinationCoords().X,ba->getDestinationCoords().Y,ba->getDestinationCoords().Z,env);
        botPitch=mypitch; 
        ba->finished=true;
        return true;
    }
    else if (performAct=="TURNPITCH_DEGREES")
    {
        float mypitch=ba->getDestinationPitch();
        botPitch=mypitch; 
        ba->finished=true;
        return true;
        
    }

    else if (performAct=="EMPTY_INV")
    {

        if (ba->just_inserted==true)
        {
        // skip all test here, assume its not finished
        }
        else
        {






        //std::string myinfstuff=myInvManager->getThrowAway(clientobj,"main","nonhotbar");
        //printf("should throw %s\n",myinfstuff.c_str());
        //int slotr=myInvManager->getSlotToThrow(clientobj,"main","nonhotbar");
        //std::string mat="default:torch";
        //std::pair <int,int> num=myInvManager->getSlotToPutBack(clientobj,mat,"main","nonhotbar");
        //if (num.first!=-9)
        //{

        //printf("first slot for %s pos %i had %i free slots\n",mat.c_str(),num.first,num.second);


        //}
        //else
        //{
        //printf("coubld not find %s\n",mat.c_str());
        //}





            int invnum=myInvManager->getFirstNonEmptyInvSpot(clientobj,"craft");
            if (invnum!=-9)
            // -9 would mean that no filled slot is found
            {
                // -9 would mean that no empty slot is found in main
                {
                    int moveamnt=-9;
                    int putinslot=-9;
                    int amount=myInvManager->getInventoryCount(clientobj,invnum ,"craft");
                    std::string matkind=myInvManager->getInventoryItem(clientobj,invnum,"craft");

                
                    std::pair <int,int> num=myInvManager->getSlotToPutBack(clientobj,matkind,"main","nonhotbar");
                    // returns slot, number free

                    if (num.first!=-9)
                    {
                    printf("first slot for %s pos %i had %i free slots\n",matkind.c_str(),num.first,num.second);

                    num.second>=amount?moveamnt=amount:moveamnt=num.second;
                    putinslot=num.first;

                    }
                    else
                    {
                            int emptyMainInvSlot=myInvManager->getFirstEmptyInvSpot(clientobj,"main");
                            if (emptyMainInvSlot!=-9)
                            {
                                putinslot=emptyMainInvSlot;
                                moveamnt=amount;
                            }
                            else
                            {
                                printf("could not find emtpy spot in main inv\n");
                            }

                    }

                    myInvManager->moveInventories(clientobj, "craft" ,invnum ,"main", putinslot ,moveamnt);
                    return true;
                }
            }
        }
    
}
    else if (performAct=="THROW_AWAY")
    {
                //insertorder->botmessage="nonhotbar";
        if (ba->just_inserted==true)
        {
            printf("skipping THROW AWAY action for now %i\n",ba->just_inserted);
            // skip all test here, assume its not finished
        }
        else
        {
            int throwslot=-9;
                if (ba->botmessage.compare("nonhotbar")==0)
            {

            throwslot=myInvManager->getSlotToThrow(clientobj,"main","nonhotbar");
                
            }
            else
            {
            throwslot=myInvManager->getSlotToThrow(clientobj,"main","all");
            //throwslot=myInvManager->getLowestInvNumberThrow(clientobj,"all");
            }
            if (throwslot==-9)
            {
                printf("did not get slot to throw away\n");
            }
            else
            {

                bool throwfrominvresult=myInvManager->throwfrominv(clientobj, "main" ,throwslot ,1);
                if (throwfrominvresult==false)
                {
                    printf("could not perform THROW_AWAY\n");
                    ba->finished=false;
                }
                else
                {
                    printf("throw away successsful\n");
                }
            return true;
            }
           return false; 
        }
    }
    else if (performAct=="MOVE_TO_POSITION_FORWARD")
        {
        forwardstate=true;
        leftstate=false;
        rightstate=false;
        backstate=false;
        }
    else if (performAct=="MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK"){
        forwardstate=true;
        leftstate=false;
        rightstate=false;
        backstate=false;
        }
    else if (performAct=="MOVE_TO_POSITION_BACKWARD"){
        forwardstate=false;
        leftstate=false;
        rightstate=false;
        backstate=true;
        }
    else if (performAct=="MOVE_TO_POSITION_FORWARD_JUMP")
        {
        forwardstate=true;
        leftstate=false;
        rightstate=false;
        backstate=false;
        }
        
    else if (performAct=="WAIT")
    {
        if (ba->waited_time==-1)
        { ba->setWaitedTime(0.0); }
        if (ba->lasttime==-1)
        { ba->lasttime=env->getTimeOfDayF();}
        if (ba->activatedtime==-1){
        ba->activatedtime=env->getTimeOfDayF();}

        float passedtime=env->getTimeOfDayF()-ba->lasttime;

        ba->waited_time=ba->waited_time+passedtime;
        ba->lasttime=env->getTimeOfDayF();

        return true;
        }

    else if (performAct=="CONTAINER")
    {
        currentact=ba->subacts.front();
    }

    else if (performAct=="DIG")
    {
        int abx=int(ba->getDestinationCoords().X/10);
        int aby=int(ba->getDestinationCoords().Y/10);
        int abz=int(ba->getDestinationCoords().Z/10);

        std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
        if (isDiggable(currentmat))
        { LeftB = true; }
        else
        {ba->finished=true;}
    }
    else if (performAct=="DIGACT")
    {
        // 10 Z is north
        v3f dcords=ba->getDestinationCoords();

        // for 3x3
        float poslist0[][3]={{0,10,0},{0,0,0},{0,20,0},     {dcords.Z,10,dcords.X},{dcords.Z,0,dcords.X},{dcords.Z,20,dcords.X},{-1*dcords.Z,10,-1*dcords.X},{-1*dcords.Z,0,-1*dcords.X},{-1*dcords.Z,20,-1*dcords.X}};
        
        // attempt to make stairs
                                // own pos and up                           //  one side and up                                     // other side and up
        float poslistdum0[][3]={{0,10,0},{0,0,0},{0,20,0},     {dcords.Z,10,dcords.X},{dcords.Z,0,dcords.X},{dcords.Z,20,dcords.X},{-1*dcords.Z,10,-1*dcords.X},{-1*dcords.Z,0,-1*dcords.X},{-1*dcords.Z,20,-1*dcords.X}, {dcords.Z,-10,dcords.X},{-1*dcords.Z,-10,-1*dcords.X},{0,-10,0}};

        unsigned int poslist0_size=sizeof(poslist0)/sizeof(poslist0[0]);

    if (ba->subacts.size()<1)
    {   // container was empty, so fill it
        
        v3f midpos=getMiddlePlayer(player);
        v3f midposPlayerLev=v3f(midpos.X,player->getPosition().Y,midpos.Z);

        v3f m_playerposition=player->getPosition();

        float m_distance=m_playerposition.getDistanceFrom(midposPlayerLev);
        if (m_distance>2.5)
        {
            Brainaction *center=actionFac->makeCenterContainer3(v3f(0,0,0), "machine made",0.00001,0.1,2.5,env,player,"FORWARD");
            //Brainaction *center=makeCenterContainer(v3f(0,0,0), "machine made",0.00001,0.1,2.5,env,player,"FORWARD");
            if(center)
            {
                center->setParent(ba);
                ba->subacts.push_back(center);
            }
        }

        if (!allisair(player,env,poslist0,9))
        {
            printf("ALL was NOT AIR in 0 pos \n");
            for (unsigned int i=0; i<poslist0_size; i++)
            {  
                int abx=int(poslist0[i][0]/10);
                int aby=int(poslist0[i][1]/10);
                int abz=int(poslist0[i][2]/10);

                std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);

                if (isDiggable(currentmat))
                {
                    Brainaction *digs=actionFac->makeDigContainer(v3f(poslist0[i][0],poslist0[i][1],poslist0[i][2]),"dig",0.0001 ,5,5,env,player,false);
                    digs->setParent(ba);
                    ba->subacts.push_back(digs);
                }
            }
        }           
        else //position 1 was all air
        {
            printf("ALL WAS AIR in 0 pos \n");

            v3f digdir= dcords;
 
            // Make coords for next position
            float newposlist1[][3]= {{poslist0[0][0]+digdir.X,poslist0[0][1]+digdir.Y,poslist0[0][2]+digdir.Z},
            {poslist0[1][0]+digdir.X,poslist0[1][1]+digdir.Y,poslist0[1][2]+digdir.Z},
            {poslist0[2][0]+digdir.X,poslist0[2][1]+digdir.Y,poslist0[2][2]+digdir.Z},
            {poslist0[3][0]+digdir.X,poslist0[3][1]+digdir.Y,poslist0[3][2]+digdir.Z},

            {poslist0[4][0]+digdir.X,poslist0[4][1]+digdir.Y,poslist0[4][2]+digdir.Z},
            {poslist0[5][0]+digdir.X,poslist0[5][1]+digdir.Y,poslist0[5][2]+digdir.Z},
            {poslist0[6][0]+digdir.X,poslist0[6][1]+digdir.Y,poslist0[6][2]+digdir.Z},
            {poslist0[7][0]+digdir.X,poslist0[7][1]+digdir.Y,poslist0[7][2]+digdir.Z},
            {poslist0[8][0]+digdir.X,poslist0[8][1]+digdir.Y,poslist0[8][2]+digdir.Z},
};

                // is position 2 free?
                unsigned int newposlist1_size=sizeof(newposlist1)/sizeof(newposlist1[0]);
                if (!allisair(player,env,newposlist1,9))
                {
                    printf("all was NOT air in second poss\n");
                    for (unsigned int i=0; i<newposlist1_size; i++)
                    {  
                        int abx=int(newposlist1[i][0]/10);
                        int aby=int(newposlist1[i][1]/10);
                        int abz=int(newposlist1[i][2]/10);

                        std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
                        if (isDiggable(currentmat))
                        {
                            // not all is air at position 2 so we make dig container 
                            Brainaction *digs=actionFac->makeDigContainer(v3f(newposlist1[i][0],newposlist1[i][1],newposlist1[i][2]),"dig",0.0001 ,5,4,env,player,false);
                            digs->setParent(ba);
                            ba->subacts.push_back(digs);
                        }

                    }
                }           

                else // not all was air in second pos
                {
                    printf("ALL WAS AIR in second pos \n");

                    // check side positions
                    // Make underposition list. It is one in size now
                    float under_position_list[][3]={{dcords.Z,-10,dcords.X},{-dcords.Z,-10,-dcords.X}};
                    unsigned int under_position_list_size=sizeof(under_position_list)/sizeof(under_position_list[0]);

                        if (!all_is_solid(player,env,under_position_list,under_position_list_size))
                        {
                            // not all positions were covered
                            printf("all was NOT solid to the SIDES\n");
                            for (unsigned int i=0; i<under_position_list_size; i++)
                                {
                                    int abx=int((under_position_list[i][0]/10));
                                    int aby=int((under_position_list[i][1]/10));
                                    int abz=int((under_position_list[i][2]/10));

                                    std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
                                    if (!isStandable(currentmat))
                                    {
                                        v3f extdir=v3f(under_position_list[i][0],under_position_list[i][1],under_position_list[i][2]);
                                        Brainaction *extend_container_here=actionFac->makeExtendContainer(extdir, "machine made",0.00001,1.5,2.5,env,player,"FORWARD");
                                        extend_container_here->setParent(ba);
                                        ba->subacts.push_back(extend_container_here);
                                    }
                                }
                        }
                        else
                        {
                            printf("all was solid to the sides\n");
                            int abx=int((digdir.X/10));
                            int aby=int((digdir.Y/10));
                            int abz=int((digdir.Z/10));

                            // is all solid in front?
                            std::string frontmat=getAsoluteMaterial(player,env,0+abx,-1+aby,0+abz);

                            if (isStandable(frontmat))
                            {
                                v3f middleplayer=getMiddlePlayer(player)+v3f(0*BS,1*BS,0);

                                // Move to front
                                v3f extdir=digdir;

                                Brainaction *startsneak=new Brainaction("START_SNEAK");
                                startsneak->setParent(ba);
                                ba->subacts.push_back(startsneak);

                                Brainaction *movestep_container_clear_forward=actionFac->makeMoveContainerFromTo(middleplayer, middleplayer+extdir, "container for moving formward after dig",0.0000001,1.0,5.0,env,player,"FORWARD");
                                movestep_container_clear_forward->setParent(ba);
                                ba->subacts.push_back(movestep_container_clear_forward);
                                            
                                Brainaction *stopsneak=new Brainaction("STOP_SNEAK");
                                stopsneak->setParent(ba);
                                ba->subacts.push_back(stopsneak);
                                
                                // Check for torch
                                v3f torch_destination=getNearestByType(player,env,10,"default:torch"); 
                                u8 player_light_level=player->light;
                                //printf("light level: -%u- \n",player_light_level);
                                
                                float torch_distance=(player->getPosition()).getDistanceFrom(torch_destination);
                                //if(torch_distance>80)
                                if(player_light_level<80)
                                {
                                    // Add torch
                                    printf("no torch, placing torch\n");
                                    Brainaction *torch_container_here=actionFac->makeTorchContainer(-1*digdir, "machine made",0.00001,1.5,2.5,env,player,"FORWARD");
                                    torch_container_here->setParent(ba);
                                    ba->subacts.push_back(torch_container_here);
                                }
                            } 
                            else
                            {
                                    printf("place was not standable\n");
                                    // make extend
                                    Brainaction *extend_container_here=actionFac->makeExtendContainer(v3f(0,-BS,0)+digdir, "machine made",0.00001,1.5,2.5,env,player,"FORWARD");
                                    extend_container_here->setParent(ba);
                                    ba->subacts.push_back(extend_container_here);
                            }
                    }
                }
                //end of  if (!allisair(player,env,poslist1,4))
            }
            // end of if (!allisair(player,env,poslist0,4))


        // make the first action active (leaving this container)
        currentact=ba->subacts.front();
        ba->finished=true; 
        }
        // End of subacts size <0

        else
        {
            currentact=ba->subacts.front();
            ba->finished=true; 
        }
    }

    else if (performAct.compare("REAL_RIGHT_CLICK")==0)
    {
        GetRightClicked=true;
        ba->finished=true; 
    }

    else if (performAct.compare("RELEASE_RIGHT_CLICK")==0)
    {
        GetRightClicked=false;
        ba->finished=true; 
    }

    else if (performAct.compare("START_SNEAK")==0)
    {
        sneakstate=true;
        ba->finished=true; 
        printf("started sneaking\n");
    }
    else if (performAct.compare("STOP_SNEAK")==0)
    {
        sneakstate=false;
        ba->finished=true; 
        printf("stopped sneaking\n");
    }
    else if (performAct.compare("CHAT")==0)
    {





        //std::string myinfstuff=myInvManager->getThrowAway(clientobj,"main","nonhotbar");
        //printf("should throw %s\n",myinfstuff.c_str());
        //int slotr=myInvManager->getSlotToThrow(clientobj,"main","nonhotbar");
        //std::string mat="default:torch";
        //std::pair <int,int> num=myInvManager->getSlotToPutBack(clientobj,mat,"main","nonhotbar");
        //if (num.first!=-9)
        //{

        //printf("first slot for %s pos %i had %i free slots\n",mat.c_str(),num.first,num.second);


        //}
        //else
        //{
        //printf("coubld not find %s\n",mat.c_str());
        //}




            int invnum=myInvManager->getFirstNonEmptyInvSpot(clientobj,"craft");
            if (invnum!=-9)
            // -9 would mean that no filled slot is found
            {
                // -9 would mean that no empty slot is found in main
                {
                    int moveamnt=-9;
                    int putinslot=-9;
                    int amount=myInvManager->getInventoryCount(clientobj,invnum ,"craft");
                    std::string matkind=myInvManager->getInventoryItem(clientobj,invnum,"craft");

                
                    std::pair <int,int> num=myInvManager->getSlotToPutBack(clientobj,matkind,"main","nonhotbar");
                    // returns slot, number free

                    if (num.first!=-9)
                    {
                    printf("first slot for %s pos %i had %i free slots\n",matkind.c_str(),num.first,num.second);

                    num.second>=amount?moveamnt=amount:moveamnt=num.second;
                    putinslot=num.first;

                    }
                    else
                    {
                            int emptyMainInvSlot=myInvManager->getFirstEmptyInvSpot(clientobj,"main");
                            if (emptyMainInvSlot!=-9)
                            {
                                putinslot=emptyMainInvSlot;
                                moveamnt=amount;
                            }
                            else
                            {
                                printf("could not find emtpy spot in main inv\n");
                            }

                    }

                    myInvManager->moveInventories(clientobj, "craft" ,invnum ,"main", putinslot ,moveamnt);
                    return true;
                }
            }



	srand( (unsigned int) time(0) );
	
	//create data set reader and load data file
	dataReader d;
	d.loadDataFile("/Users/security/mt17nov/minetest/src/ai/letter-recognition-2.csv",16,3);
	d.setCreationApproach( STATIC, 10 );	

	//create neural network
	neuralNetwork nn(16,10,3);

	//create neural network trainer
	neuralNetworkTrainer nT( &nn );
	nT.setTrainingParameters(0.001, 0.9, false);
	nT.setStoppingConditions(150, 90);
	nT.enableLogging("/Users/security/mt17nov/minetest/src/ai/log.csv", 5);
	
	//train neural network on data sets
	for (int i=0; i < d.getNumTrainingSets(); i++ )
	{
		nT.trainNetwork( d.getTrainingDataSet() );
	}	

	//save the weights
	nn.saveWeights("/Users/security/mt17nov/minetest/src/ai/weights.csv");
printf("done\n");
int nInput=17;
double *inputNeurons = new( double[nInput] );
	for ( int i=0; i < nInput; i++ ) inputNeurons[i] = 0;
        //double val[]={0.1,0.2};
        int *n=nn.feedForwardPattern(inputNeurons);

        printf("result was %d\n",n[0]);
        printf("result was %d\n",n[1]);
        printf("result was %d\n",n[2]);


        std::string botms=ba->botmessage;
        std::wstring botms_wide=narrow_to_wide(botms);
        // chat
        clientobj->typeChatMessage(botms_wide);
        ba->finished=true; 
    }
    else if (performAct.compare("CENTER")==0)
    {
        if (ba->subacts.size()<1)
        {
            v3f midpos=getMiddlePlayer(player);
            v3f midposPlayerLev=v3f(midpos.X,player->getPosition().Y,midpos.Z);
            v3f m_playerposition=player->getPosition();

            float m_distance=m_playerposition.getDistanceFrom(midposPlayerLev);
            if (m_distance>2.5)
            {
                clientobj->typeChatMessage(L"centering");

                Brainaction *center_container_made=actionFac->makeCenterContainer3(v3f(0,0,0), "machine made",0.00001,0.1,2.5,env,player,"FORWARD");
                center_container_made->setParent(ba);
                ba->subacts.push_back(center_container_made);
            }
            currentact=ba->subacts.front();
            ba->finished=true; 
        }
        else
        {
            currentact=ba->subacts.front();
            ba->finished=true; 
        }

    }
    else if (performAct.compare("GO_CHEST")==0)
    {
        if (ba->subacts.size()<1)
        {
            float searchdistance=9;
            v3f chest_destination=getNearestByType(player,env,searchdistance,"default:chest"); 

            if (chest_destination==v3f(-666,-666,-666))
            // did not find a chest
            {
                printf("Failed to find chest within distance %f\n",searchdistance);
            }
            else
            // found a chest 
            {
            v3f mods=get_nswe_offset(playerposition,chest_destination);
            v3f chest_new_position=chest_destination+mods;

            // Make move container for moving to chest
            Brainaction *movestep_container_made=actionFac->makeMoveContainer(chest_new_position, "machine made",0.00001,1.0,5.0,env,player,"JUMP");
            movestep_container_made->setParent(ba);
            ba->subacts.push_back(movestep_container_made);

            currentact=ba->subacts.front();
            ba->finished=true; 
            }
        }
        else
        {
            currentact=ba->subacts.front();
            ba->finished=true; 
        }
    }
    else if (performAct=="GO_EDGE")
    {
        v3f middleplayer=getMiddlePlayer(player);
        std::string middleplayermat=player->getBlocktype(middleplayer,env->getMap());
        printf("player middle position %f %f %f %s\n",middleplayer.X,middleplayer.Y,middleplayer.Z,middleplayermat.c_str());
        
        std::string mat000=getAsoluteMaterial(player,env,0, 0, 0);
        printf("0 0 0 %s\n",mat000.c_str());

        std::string mat001=getAsoluteMaterial(player,env,0, 0, 1);
        printf("0 0 1 %s\n",mat001.c_str());

        std::string mat002=getAsoluteMaterial(player,env,0, 0, 2);
        printf("0 0 2 %s\n",mat002.c_str());

        std::string mat0_10=getAsoluteMaterial(player,env,0, -1, 0);
        printf("0 -1 0 %s\n",mat0_10.c_str());

        std::string mat0_20=getAsoluteMaterial(player,env,0, -2, 0);
        printf("0 -2 0 %s\n",mat0_20.c_str());

        std::string mat00_1=getAsoluteMaterial(player,env,0, 0, -1);
        printf("0 0 -1 %s\n",mat00_1.c_str());
//////////////////
        std::string turned001=getDirectionMaterial(player,env,0, 0, 0);
        printf("direction 0 0 0 %s\n",turned001.c_str());

        std::string turned101=getDirectionMaterial(player,env,0, 0, 1);
        printf("direction 0 0 1 %s\n",turned101.c_str());

        std::string turned_101=getDirectionMaterial(player,env,0, 0, -1);
        printf("direction 0 0 -1 %s\n",turned_101.c_str());

        std::string turned011=getDirectionMaterial(player,env,1,0, 0);
        printf("direction 1 0 0 %s\n",turned011.c_str());

        std::string turned021=getAsoluteMaterial(player,env,0, 2, 0);
        printf("direction 0 2 1 %s\n",turned021.c_str());
    }

    else if (performAct.compare("FOLLOW_MASTER")==0)
    {
        if (ba->subacts.size()<1)
        {
            v3f masterposition=getYawToMaster_pos(player,env,master);

            if (masterposition.X==-666666 and masterposition.Y ==-666666 and masterposition.Z==-666666)
            {
                printf("COULD NOT GET MASTERPOSITION!\n");
            }

            v3f mastermiddle=v3f(get_middle_pos(masterposition.X),get_middle_pos(masterposition.Y-0.01),get_middle_pos(masterposition.Z));

            //v3f mods=get_nswe_offset(playerposition,mastermiddle);
            // go to action position or middle
            //v3f masterposition2=masterposition;
            v3f masterposition2=mastermiddle;

            v3f playerposition=player->getPosition();
            v3f masterposition_players_level=v3f(masterposition2.X,playerposition.Y,masterposition2.Z);

            // Make movestep container
            Brainaction *movestep_container=actionFac->makeMoveContainer(masterposition_players_level, "follow_master_container",0.00001,1.0,6.0,env,player,"JUMP");

            movestep_container->setParent(ba);
            ba->subacts.push_back(movestep_container);

            currentact=ba->subacts.front();
            ba->finished=true;
        }
        else
        {
            currentact=ba->subacts.front();
            ba->finished=true;
        }
    }

    else if (performAct.compare("MAIN_CONTAINER")==0)
    {
        currentact=ba->subacts.front();
    }

    else if (performAct=="STOP")
    {
        LeftB = false;
        rightbutton=false;
        forwardstate=false;
        backstate=false;
        leftstate=false;
        rightstate=false;
        jumpstate=false;
        specialstate=false;
        //sneakstate=false;
    }
    else if (performAct.compare("EQUIP_ITEM")==0)
    {
        // Equip item
        std::string kind=ba->botmessage;

        int hotBarSlot=getDesignatedHotbarSlot(kind);
        
        if (hotBarSlot==-9)
        {
            printf("could not get hotbarslot for %s\n",kind.c_str());
        }
        else 
        {
            int invpicknum=myInvManager->getLowestInvNumber(clientobj,kind,"main","all");
            if (invpicknum==-9)
            {
            // trying to modify inv crashes server if -9
            printf("could not get item %s\n",kind.c_str());
            }
            else
            {
                int hotbarplace=getDesignatedHotbarSlot(kind);
                myInvManager->moveInventories(clientobj, "main" ,invpicknum ,"main", hotbarplace ,0);

                clientobj->selectPlayerItem(hotbarplace);
            }
        }

        //forwardstate=false;
        jumpstate=false;
    }

    else if (performAct.compare("GET_FROM_CHEST")==0)
    {

        std::string desired_object=ba->botmessage;//"default:pick";

        float getfromchest_searchdistance=9;
        v3f chest_destination=getNearestByType(player,env,getfromchest_searchdistance,"default:chest");
        //underd=v3s16(0,-1,0);

        if (chest_destination==v3f(-666,-666,-666))
        {
            printf("failed to find chest at searchdistance %f\n", getfromchest_searchdistance);
        }
        printf("Found chest at pos %f %f %f\n",chest_destination.X,chest_destination.Y,chest_destination.Z);

        v3s16 unders=v3s16(chest_destination.X/10,chest_destination.Y/10,chest_destination.Z/10);
        //ClientMap &map3 = env->getClientMap();

        InventoryLocation inventoryloc;
        inventoryloc.setNodeMeta(unders);
        Inventory *innn=clientobj->getInventory(inventoryloc);
        InventoryList *mlist = innn->getList("main");
        ItemStack playeritem;

        forwardstate=false;

        int emptyplace=myInvManager->getEmptyInventoryNum(clientobj);

        if (emptyplace!=-999)
        {
            if(mlist != NULL)
            {
                int listsize = mlist->getSize(); 
                for (int var=0;var<listsize;var++)
                {
                ItemStack playeritem = mlist->getItem(var);
                //printf("item in chest %i %s\n",var,playeritem.name.c_str());                                                
                std::string myitemname=(playeritem.name.substr(0,12));
                if (myitemname.compare(desired_object)==0)
                {
                    printf("found %s here, at %i\n",desired_object.c_str(),var);
                    clientobj->selectPlayerItem(var);

                    IMoveAction *a = new IMoveAction();
                    a->count = 1;
                    a->from_inv = inventoryloc;
                    a->from_list = "main";
                    a->from_i = var;
                    a->to_inv.setCurrentPlayer();
                    a->to_list = "main";
                    a->to_i = emptyplace;
                    clientobj->inventoryAction(a);
                    break;

                }
            }

            //u32 test=mlist->getFreeSlots();
        }
        else
        {
            printf("mlist was null\n");
        }
    }
    else
    {
        printf("could not get an emtpy inventory slot\n");
    }

        //forwardstate=false;
        jumpstate=false;
        ba->finished=true;
    }
    //performaction
    return true;
}

void Brain::step(float tim)
//STEP
{
    reacted_to_chat=false;
    bool in_main=false;
   
    // Check if we have any actions 
    if (currentact->getBrainAction()=="MAIN_CONTAINER" and currentact->subacts.size()<1)
    {
        in_main=true;
    }
    else
    {
     //   printf("step: %i ------------------------------------------------\n",number_of_steps);
        printcontainerInfo(currentact);
    }
    
    number_of_steps++;
    
    LocalPlayer* player = clientobj->getEnv().getLocalPlayer();

    ClientEnvironment* env= &clientobj->getEnv();


    std::list<std::wstring> commm=check_chat(currentchatlist , player, env);

    check_commands(player,commm,brainact);

    if (currentact->just_inserted==false)
    {
        bool checkActionInserted=checkAction(player,currentact,env);
        // a new action may have been inserted after this

        if (checkActionInserted==false)
        {
            // check if action is finished
            bool actionIsFinished=checkFinished(player,currentact,env);
       
            if (actionIsFinished)
            {
                if (currentact->getBrainAction()!="MAIN_CONTAINER")
                {
                    printf("popping front %s--------%s\n",currentact->getBrainAction().c_str(),currentact->actiondescription.c_str());

                    Brainaction *parentact=currentact->getParent();

                    if (!(parentact==NULL))
                    {
                        parentact->subacts.pop_front();
                    }
                    else // PARENT not found
                    {   
                        printf("current act %s:%s had no parent\n",currentact->getBrainAction().c_str(),currentact->actiondescription.c_str());
                    }
                    currentact=currentact->getParent();
                }// we were not in main container
            }
            else
            {
                // action was not finished
                bool performSuccess=performAction(player,currentact,env);
            }
        }
        else
        {
            printf("action was just inserted by checkaction\n");
            currentact->just_inserted=false;
        }
    }
    else
    {
        currentact->just_inserted=false;
        printf("set currentact just_inserted to false for %s\n",currentact->getBrainAction().c_str());
    }
    
    // Boredom
    // this value barely keeps him happy while digging all the time
    //happiness-=0.01;

    happiness-=0.001;
    if (happiness<10)
    {
        printf("unhappy\n");
    }
    //printf("happiness %f\n",happiness);
    
    // for keeping track of chat messages
    lastdtime=tim;

}//end of step



//////////////////////////////////////////////////////////
//
// Functions
//
//////////////////////////////////////////////////////////


v3f Brain::getYawToMaster_pos(LocalPlayer *player,ClientEnvironment *m_env,std::string mastername)
{
        //std::string mastername="uuu";
        std::vector<DistanceSortedActiveObject> objects1;


        //LocalPlayerplayer *master=m_env->getPlayer(mastername);
        //v3f pos1 = master->getPosition();
        m_env->getActiveObjects(player->getPosition(), 400.0, objects1);
	for(u32 i=0; i<objects1.size(); i++)
	{
            ClientActiveObject *obj1 = objects1[i].obj;
            v3f pos1 = obj1->getPosition();
            //bool cl = obj1->isPlayer();
            std::string cli = obj1->pname();
            if (cli.compare(mastername) == 0)
            {
                return pos1;
            }
	}
        printf("getYawToMaster_pos returned nothing\n");
        return v3f(-666666,-666666,-666666);
        //return pos1;
}

f32 Brain::getPitchToPosition(LocalPlayer *player,float posx, float posy, float posz ,ClientEnvironment *m_env)
{
    v3f desired_position = v3f(posx,posy,posz);


    v3f ownpos=player->getEyePosition();

    f32 ownx=ownpos.X;
    f32 owny=ownpos.Y;
    f32 ownz=ownpos.Z;

    f32 xdif=posx-ownx;
    f32 ydif=(posy-0.5*BS)-owny;
    f32 zdif=posz-ownz;
    f32 hyp=sqrt((xdif*xdif)+(zdif*zdif));
    //printf("xdif %f ydif %f zdif %f hyp %f\n",xdif, ydif,zdif,hyp);  

    (xdif==0)?xdif=0.00001:xdif=xdif;
    (hyp==0)?hyp=0.00001:hyp=hyp;

    f32 ang=(-atan2(ydif,hyp)*180/3.141592);
    //printf("returning %f\n",ang);
    return ang;
}

f32 Brain::getYawToPosition(v3f playerpos,v3f masterpos)
{
    f32 masterx=masterpos.X;
    f32 masterz=masterpos.Z;

    f32 ownx=playerpos.X;
    f32 ownz=playerpos.Z;

    f32 xdif=masterx-ownx;
    f32 zdif=masterz-ownz;
    
    (xdif==0)?xdif=0.00001:xdif=xdif;
    (zdif==0)?zdif=0.00001:zdif=zdif;

    f32 ang=-90+atan2(zdif,xdif)*180/3.141592;

    return ang+360.0;
}


float Brain::get_middle_pos(float num)
{
    float t;
    t= (BS*round((num)/BS));
    return t;
}

bool Brain::allisair(LocalPlayer *player,ClientEnvironment *env,float poslist[][3],int le)
{
    int arrsize=le;
    for (int i=0; i<arrsize; i++)
    {
        int abx=int(poslist[i][0]/10);
        int aby=int(poslist[i][1]/10);
        int abz=int(poslist[i][2]/10);
        std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
        if (isDiggable(currentmat))
        {
            //printf("all is air returned false for %i %i %i\n",abx,aby,abz);
            return false;
        }
    }
    return true;
}

bool Brain::all_is_solid(LocalPlayer *player,ClientEnvironment *env,float poslist[][3],int le)
{
    int arrsize=le;
    for (int i=0; i<arrsize; i++)
    {
        int abx=int(poslist[i][0]/10);
        int aby=int(poslist[i][1]/10);
        int abz=int(poslist[i][2]/10);
        std::string currentmat=getAsoluteMaterial(player,env,abx,aby,abz);
        if (!isStandable(currentmat))
        {
            return false;
        }
    }
    return true;
}

v3f Brain::getNearestByType(LocalPlayer *player,ClientEnvironment *env,int scanrange, std::string type) 
{
    v3f middleplayer=getMiddlePlayer(player);

    v3f nearestposition=v3f(-666,-666,-666);
    float curd=9999999;

    for (int zd=(-scanrange)+1;zd<scanrange;zd++)//height
        {
        for (int xd=(-scanrange)+1;xd<scanrange;xd++)
        {
            for (int yd=(-scanrange)+1;yd<scanrange;yd++)
            {
                std::string nodetype=player->getBlocktype(middleplayer+ v3f(xd*BS,zd*BS,yd*BS),env->getMap());
                std::string nodet=nodetype.c_str();
                if (nodet.compare(type)==0)
                {
                    v3f po=middleplayer+ v3f(xd*BS,zd*BS,yd*BS);
                    float myd= po.getDistanceFrom(middleplayer);
                    if (myd<curd)
                    {
                        nearestposition=po;
                        curd=myd;
                    }
                }
            }

        }
    }
    return nearestposition;
}

std::list<std::wstring> Brain::check_chat(std::list<ChatLine> currentchatlist ,LocalPlayer* player, ClientEnvironment* env)
{
    std::wstring botowner=L"uuu";

    // Go through chat 
    std::list<ChatLine>::iterator it;
    for (it=currentchatlist.begin(); it!=currentchatlist.end(); it++)
    {
        f32 message_age=it->age;

        if (message_age<=lastdtime)
        {
            std::wstring chatsender=it->name;
            // If sender is owner
            if (chatsender.compare(botowner)==0)
            {
                int spacesearch=0; 
                // Tokenize chat message
                std::list<std::wstring> tokenizedchat;
                std::wstring textmessage=it->text;

                while (spacesearch!=-1)
                {
                    spacesearch=textmessage.find(L" ");
                    if (spacesearch!=-1)
                    {
                        tokenizedchat.push_back(textmessage.substr(0,spacesearch));
                        textmessage=textmessage.substr(spacesearch+1,textmessage.size());
                    }
                    else
                    {
                        tokenizedchat.push_back(textmessage);
                    }
                }

                // Look for bot command
                std::wstring commdword=tokenizedchat.front();
                tokenizedchat.pop_front();
                if (commdword==L"bot")
                {
                    // if anything left after bot
                    if (!tokenizedchat.empty())
                    {
                        currentchatlist.clear();
                        return tokenizedchat;
                    }
                    else
                    {
                        printf("no command after bot\n");
                        std::list<std::wstring> falseretlist;
                        std::wstring falseret=L"-a";
                        falseretlist.push_back(falseret);
                        currentchatlist.clear();
                        return falseretlist; 
                    }
                }
                else //not bot
                {
                    printf("not bot command\n");
                    std::list<std::wstring> falseretlist;
                    std::wstring falseret=L"-a";
                    falseretlist.push_back(falseret);
                    currentchatlist.clear();
                    return falseretlist; 
                }
            }//end of owner check
        }// end of message age check
    } // end of chatcommands loop

    std::list<std::wstring> falseretlist;
    std::wstring falseret=L"-a";
    falseretlist.push_back(falseret);
    currentchatlist.clear();
    return falseretlist;
}

bool Brain::check_commands(LocalPlayer *player, std::list<std::wstring> thecommandlist ,Brainaction *action)
{
    Brainaction *orders;

    int numcommands=thecommandlist.size();
    //printf("nom commands: %i\n",numcommands);
    if (numcommands<2)
    {
        return true;
    }
    printf("command: %s\n",(wide_to_narrow(thecommandlist.front())).c_str());
    std::wstring bot_number=thecommandlist.front();
    if ((wide_to_narrow(bot_number)).compare("-a")==0)
    {
        printf("bot number got nothing1\n");
        return true;
    }
    thecommandlist.pop_front();
    printf("to bot number %s\n",(wide_to_narrow(bot_number)).c_str());

    std::wstring thecommand=thecommandlist.front();

    std::string commandstring=wide_to_narrow(thecommand);

    if ((wide_to_narrow(thecommand)).compare("-a")==0)
    {
        return true;
    }
    printf("playername=%s\n",(player->getName()));
    
    std::string playername=player->getName();

    std::string numtobot="-b";
    
    if ((wide_to_narrow(bot_number)).compare("1")==0)
    { 
        numtobot="osmondc";
    }

    if ((wide_to_narrow(bot_number)).compare("2")==0)
    { 
        numtobot="bot";
    }

    if (!(numtobot.compare(playername)==0))
    {
        return true;
    }

    if (thecommand==L"act" and reacted_to_chat==false )
    {
        orders=new Brainaction("FOLLOW_MASTER");
        orders->actiondescription="move with decision";

        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }

    if (thecommand==L"chat" and reacted_to_chat==false )
    {
        orders=new Brainaction("CHAT");
        orders->actiondescription="say somthing";

        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }

    if (thecommand==L"craft" and reacted_to_chat==false )
    {
        orders=new Brainaction("CRAFT");
        orders->actiondescription="craft somthing";
        orders->botmessage=("default:torch");

        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }

    if (thecommand==L"get" and reacted_to_chat==false)
    {
        orders=new Brainaction("GO_CHEST");
        orders->actiondescription="move to nearest chest";
        Brainaction *getp=new Brainaction("GET_FROM_CHEST");
        orders->botmessage="default:pick";
        getp->actiondescription="get pickaxe";
        getp->setParent(action);
        orders->setParent(action);

        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }
    if (thecommand==L"eqv" and reacted_to_chat==false)
    {
        orders=new Brainaction("EQUIP_ITEM");
        
        orders->botmessage="default:pick_stone";
        orders->actiondescription="start digging";
        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }
    if (thecommand==L"scan" and reacted_to_chat==false)
    {
        orders=new Brainaction("GO_EDGE");
        orders->actiondescription="scan surroundings";
        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }
    if (thecommand==L"center" and reacted_to_chat==false)
    {
        orders=new Brainaction("CENTER");
        orders->actiondescription="center";
        orders->setParent(action);
        action->subacts.push_back(orders);
        reacted_to_chat=true;
    }
    if (thecommand==L"dig" and reacted_to_chat==false)
    {
        Brainaction *dig_container=new Brainaction("CONTAINER");
        dig_container->setActionDescription("container for dig command");
        dig_container->actiondescription="container made to house digacts.";
        
        //int numcommands=thecommandlist.size();
        printf("thecommandlist size%zd\n",thecommandlist.size());
        if (numcommands>1)

        std::wstring secondword=thecommandlist.front();
        thecommandlist.pop_front();
        std::wstring word3=thecommandlist.front();
        std::string word3s=wide_to_narrow(word3);
    
        thecommandlist.pop_front();
        std::wstring word4=thecommandlist.front();
        std::string word4s=wide_to_narrow(word4);
        unsigned int times = atoi(word4s.c_str());

        v3f destcC;
        if (word3s.compare("w")==0)
        {
            destcC=v3f(-10,0,0);
        }
        if (word3s.compare("e")==0)
        {
            destcC=v3f(10,0,0);
        }
        if (word3s.compare("n")==0)
        {
            destcC=v3f(0,0,10);
        }
        if (word3s.compare("s")==0)
        {
            destcC=v3f(0,0,-10);
        }

        for (unsigned int i=0; i<times; i++)
        {
            Brainaction *orders2=new Brainaction("DIGACT");
            orders2->setParent(dig_container);
            orders2->setDestinationCoords(destcC);
            dig_container->subacts.push_back(orders2);
        } 
        dig_container->setParent(action);
        action->subacts.push_back(dig_container);
        reacted_to_chat=true;
    }
    return true;
}


void Brain::printcontainerInfo(Brainaction *ba)
{
    std::string actismain=ba->getBrainAction();
    bool minmain=false;
    bool list_subacts=true;
    if (actismain.compare("MAIN_CONTAINER")==0)
    {
        minmain=true;
    }
    // bogus last value
    (!minmain)?printf("current act %s %s",ba->getBrainAction().c_str(),ba->actiondescription.c_str()):list_subacts=list_subacts; 
    (!minmain)?printf("subacts: "):list_subacts=list_subacts; 
    if (list_subacts)
    {
        std::list<Brainaction*> sb=ba->subacts;
        std::list<Brainaction*>::iterator printaction_;
        for (printaction_=sb.begin(); printaction_!=sb.end(); printaction_++)
        {
            printf(" %s %s",(*printaction_)->getBrainAction().c_str(),(*printaction_)->actiondescription.c_str());
        }
    }
    printf("\n");
}

v3f Brain::get_nswe_offset(v3f playerposition,v3f chest_destination){
    float dx=playerposition.X-chest_destination.X; 
    float dy=playerposition.Z-chest_destination.Z; 
    v3f mods=v3f(-100,-100,-100);

    if (dx==0)
    dx=0.00000001;
    float dif=dy/dx;
    
    if (-1<dif<1)
    {
        if (dy>0)
        { mods=v3f(0,0,BS); }
        else
        { mods=v3f(0,0,-BS); }
    }
    else 
    {
        if (dx>0)
        { mods=v3f(BS,0,0); }
        else
        { mods=v3f(-BS,0,0); }
    }
    return mods;
}


std::string Brain::getAsoluteMaterial(LocalPlayer *player,ClientEnvironment *env,int x, int y, int z)
{
    v3f middleplayer=getMiddlePlayer(player);
    v3f place001=v3f(0,BS,0)+middleplayer+v3f(x*BS,y*BS,z*BS);
    std::string place001_mat=player->getBlocktype(place001,env->getMap());
    return place001_mat; 
}

std::string Brain::getDirectionMaterial(LocalPlayer *player,ClientEnvironment *env,int x, int y, int z)
{
    v3f unit_north = v3f(0,0,0.5*BS);
    unit_north.rotateXZBy(player->getYaw());
    // adding 0.5 makes it the players foot cube?
    v3f place001=v3f(0,0.5*BS,0)+player->getPosition()+unit_north+v3f(x*BS,y*BS,z*BS);
    std::string place001_mat=player->getBlocktype(place001,env->getMap());
    return place001_mat; 
}

bool Brain::isDiggable(std::string mat)
{
    if ((mat.compare("air")==0) ||
        (mat.compare("default:torch")==0)||
        (mat.compare("default:water_flowing")==0)||
        (mat.compare("default:water_source")==0))

        {
            return false;
        }

        else
        {
            return true;
        }
}

bool Brain::isStandable(std::string mat)
{
    if ((mat.compare("air")==0) ||
    (mat.compare("default_torch")==0)||
    (mat.compare("default:water_flowing")==0)||
    (mat.compare("default:water_source")==0))

    {
        return false;
    }
    return true;
}


v3f Brain::getMiddlePlayer(LocalPlayer *player)
{
    v3f middleplayer=v3f(get_middle_pos(player->getPosition().X),get_middle_pos(player->getPosition().Y-0.01),get_middle_pos(player->getPosition().Z));
    return middleplayer;
}

float Brain::degrees_to_plusmin360(float inangle)
{
    float realang=inangle;
    int rotations=floor(abs(inangle)/360);
    if (inangle>360)
    {
            realang=inangle-(rotations*360);
    }

    if (inangle<0)
    {
            realang=inangle+(rotations*360);
    }

    return realang;
}

float Brain::getNormalizedDegreeDifference(float ang1, float ang2)
{
        float normal_ang1=degrees_to_plusmin360(ang1);
        float normal_ang2=degrees_to_plusmin360(ang2);
        float angledif=abs(normal_ang1-normal_ang2);
        if (angledif>180)
        {angledif=360-angledif;}
        return angledif;
}

int Brain::getDesignatedHotbarSlot(std::string kind){
    int plac=-9;
    if (kind.compare("default:pick_stone")==0)
    { plac=0; }
    else if (kind.compare("default:torch")==0)
    { plac=1; }
    else if (kind.compare("default:cobble")==0)
    { plac=2; }
    return plac;
}

Brainaction*  Brain::preinsertOrder(Brainaction *insertorder,Brainaction *originalorder)
{
                    insertorder->just_inserted=true;
                    originalorder->subacts.push_front(insertorder);
                    insertorder->setParent(originalorder);
    return insertorder;
}
