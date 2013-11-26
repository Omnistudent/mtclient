/*
 *  myinv.cpp
 *  minetest
 *
 *  Created by security on 11/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "myinv.h"
Myinv::Myinv(Client* c)
{
        clientobj=c;
    

}

std::string Myinv::getEquipped()
{
            int current_equipped=clientobj->getPlayerItem();

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=clientobj->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList("main");

            if(invList != NULL){
                ItemStack playeritem = invList->getItem(current_equipped);
                std::string itemname=playeritem.name;
                return itemname;
            }

            else
            {
                printf("could not get playeritem\n");
                return "-a";
            }
        }
        else
        {
            printf("could not get playerinv\n");
                return "-a";
        }
                return "-a";

   //         ItemStack playeritem5 = result->getItem(tylu);
}


bool Myinv::getIsInventoryEmpty(Client *myclient,std::string invkind){

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=myclient->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList(invkind);

            if(invList != NULL)
            {

                int invlistsize=invList->getSize();

                for (int i=0;i<invlistsize;i++)
                {
                    std::string myitemname=getInventoryItem(myclient,i,invkind);

                    if (!(myitemname.compare("-a")==0))
                    {
                        if (myitemname.compare("")!=0)
                        {
                            bool retval=false;
                            return retval;
                        }
                    }
                    else
                    {
                         printf("could not get invslot in getIsInventoryEmpty\n");
                        return false;
                    }
                }
                bool retval=true;
                return retval;
            }

        }
        else
        {
            printf("could not get playerinvin getIsInventoryEmpty\n");
            return NULL;
        }
    return NULL;

}
int Myinv::getFirstNonEmptyInvSpot(Client *myclient,std::string invkind){
// Returns the name of the item at position in invkind (main,craft, etc)

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=myclient->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList(invkind);

            if(invList != NULL)
            {

                int invlistsize=invList->getSize();

                for (int i=0;i<invlistsize;i++)
                {
                    std::string myitemname=getInventoryItem(myclient,i,invkind);
                    printf("for num %i, %s\n",i,myitemname.c_str());

                    if (!(myitemname.compare("-a")==0))
                    {
                        if (myitemname.compare("")!=0)
                        {
                            return i;
                        }
                    }
                    else
                    {
                         printf("could not get invslot in getFirstNonEmptyInvSpot\n");
                        return -9; 
                    }
                }
                return -9;
            }

        }
        else
        {
            return -9;
        }
    return -9;

}
int Myinv::getFirstEmptyInvSpot(Client *myclient,std::string invkind){

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=myclient->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList(invkind);

            if(invList != NULL)
            {

                int invlistsize=invList->getSize();

                for (int i=0;i<invlistsize;i++)
                {
                    std::string myitemname=getInventoryItem(myclient,i,invkind);

                    if (!(myitemname.compare("-a")==0))
                    {
                        if (myitemname.compare("")==0)
                        {
                            printf("found empty place %i\n",i);
                            return i;
                        }
                    }
                    else
                    {
                         //printf("could not get invslot in getFirstEmptyInvSpot\n");
                        return -9; 
                    }
                }
                return -9;
            }

        }
        else
        {
            return -9;
        }
    return -9;

}


int Myinv::getInventoryCount(Client *myclient,int position ,std::string invkind){
// Returns the count of the item at position in invkind (main,craft, etc)

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=myclient->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList(invkind);

            if(invList != NULL){
                ItemStack playeritem = invList->getItem(position);
                std::string itemname=playeritem.name;
                int itemnumber=playeritem.count;
                printf("got item numer %i\n",itemnumber);
                printf("countitem %i ,00%s00 \n",position,itemname.c_str());
                return itemnumber;
            }

            else
            {
                printf("could not get playeritem\n");
                return -9;
            }
        }
        else
        {
            printf("could not get playerinv\n");
                return -9;
        }
                return -9;

   //         ItemStack playeritem5 = result->getItem(tylu);

}

std::string Myinv::getInventoryItem(Client *myclient,int position ,std::string invkind){
// Returns the name of the item at position in invkind (main,craft, etc)

        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        Inventory *playerinv=myclient->getInventory(playerinventoryloc);

        if(playerinv != NULL)
        {

            InventoryList *invList = playerinv->getList(invkind);

            if(invList != NULL){
                ItemStack playeritem = invList->getItem(position);
                std::string itemname=playeritem.name;
                int itemnumber=playeritem.count;
                //printf("got item numer %i\n",itemnumber);
                //printf("getinvitem %i ,00%s00 \n",position,itemname.c_str());
                return itemname;
            }

            else
            {
                printf("could not get playeritem\n");
                return "-a";
            }
        }
        else
        {
            printf("could not get playerinv\n");
                return "-a";
        }
                return "-a";

   //         ItemStack playeritem5 = result->getItem(tylu);

}

bool Myinv::moveInventories(Client *myclient, std::string frominv ,int posfrom ,std::string toinv, int posto ,int amnt)
{
        InventoryLocation playerinventoryloc;  
        playerinventoryloc.setCurrentPlayer();
        //Inventory *playerinv2=clientobj->getInventory(playerinventoryloc2);
        //ItemStack playeritemagain;

        //InventoryList *playermlist2 = playerinv2->getList("craft");
        printf("moving inventories % i from %s to %i from %s\n",posfrom,frominv.c_str(),posto,toinv.c_str());
                IMoveAction *av = new IMoveAction();
                av->count = amnt;
                av->from_inv = playerinventoryloc;
                av->from_list = frominv;
                av->from_i = posfrom;
                av->to_inv.setCurrentPlayer();
                av->to_list = toinv;
                av->to_i = posto;
                clientobj->inventoryAction(av);   
}


bool Myinv::throwfrominv(Client *myclient, std::string frominv ,int posfrom ,int amnt)
{

            printf("no empty positions, throwing away\n");
            
            //int throwslot=getLowestInvNumberThrow(clientobj,"");
            if (posfrom!=-9)
            {
            IDropAction *ba = new IDropAction();
            ba->count = 0;
            ba->from_inv.setCurrentPlayer();
            ba->from_list = "main";
            ba->from_i = posfrom;
            clientobj->inventoryAction(ba);
            printf("throwing away from performaction THROWAWAY\n");
            return true;
            }
            else
            {
                printf("could not get empty throwslot\n");
            }
                return false;
}

bool Myinv::craftInvOK(Client *myclient, std::string item)
{
    if (item.compare("default:torch")==0)
    {
        std::string coal=getInventoryItem(clientobj,1 ,"craft");
        std::string stick=getInventoryItem(clientobj,4 ,"craft");

        if ((coal.compare("default:coal_lump")==0) and (stick.compare("default:stick")==0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (item.compare("default:pick_stone")==0)
    {
        std::string cob1=getInventoryItem(clientobj,0 ,"craft");
        std::string cob2=getInventoryItem(clientobj,1 ,"craft");
        std::string cob3=getInventoryItem(clientobj,2 ,"craft");
        std::string stick1=getInventoryItem(clientobj,4 ,"craft");
        std::string stick2=getInventoryItem(clientobj,7 ,"craft");

        if ((cob1.compare("default:cobble")==0) and 
        (cob2.compare("default:cobble")==0) and 
        (cob3.compare("default:cobble")==0) and 
        (stick1.compare("default:stick")==0)and (stick2.compare("default:stick")==0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Myinv::moveMaterialsToCraft(Client *clientobj, std::string thing)
{
        if (thing.compare("default:torch")==0)
        {
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","all");
            int coalnum=getLowestInvNumber(clientobj,"default:coal_lump","main","all");
            if (sticknum!=-9)
            {
            moveInventories(clientobj, "main" ,sticknum ,"craft", 4 ,1);
            }
            if (coalnum!=-9)
            {
            moveInventories(clientobj, "main" ,coalnum ,"craft", 1 ,1);
            }
        }

        if (thing.compare("default:stick")==0)
        {
            int woodnum=getLowestInvNumber(clientobj,"default:wood","main","all");
            if (woodnum!=-9)
            {
            moveInventories(clientobj, "main" ,woodnum ,"craft", 4 ,1);
            }
        }

        if (thing.compare("default:wood")==0)
        {
            int treenum=getLowestInvNumber(clientobj,"default:tree","main","all");
            if (treenum!=-9)
            {
            moveInventories(clientobj, "main" ,treenum ,"craft", 4 ,1);
            }
        }
        else if (thing.compare("default:pick_stone")==0)
        {
        printf("trying to make stone pickx\n");
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","all");
            if (sticknum==-9)
            {
                printf("could not make pickaxe due to lack of sticks\n");
                return false;
            }
        printf("trying to make stone pickx\n");
            int cobblenum=getLowestInvNumber(clientobj,"default:cobble","main","all");
            if (cobblenum==-9)
            {
                printf("could not make pickaxe due to lack of cobble\n");
                return false;
            }
        printf("trying to make stone pickx\n");
            int stickcount=getInventoryCount(clientobj,sticknum ,"main");
        printf("trying to make stone pickx\n");
// Returns the count of the item at position in invkind (main,craft, etc)
            printf("stikcnum=%i cobble=%i\n",sticknum,cobblenum);
            printf("stikcamnt=%i \n",stickcount);
            if (sticknum!=-9)
            {
            moveInventories(clientobj, "main" ,sticknum ,"craft", 4 ,1);
            moveInventories(clientobj, "main" ,sticknum ,"craft", 7 ,1);
            }
            if (cobblenum!=-9)
            {
            moveInventories(clientobj, "main" ,cobblenum ,"craft", 0 ,1);
            moveInventories(clientobj, "main" ,cobblenum ,"craft", 1 ,1);
            moveInventories(clientobj, "main" ,cobblenum ,"craft", 2 ,1);
            }
        }

    printf("making %s\n",thing.c_str());
    return true;

}

bool Myinv::isUsableMaterial(std::string item)
{

            if (   !(item.compare("default:pick_stone")==0) && 
                    !(item.compare("default:torch")==0) && 
                    !(item.compare("default:coal_lump")==0) && 
                    !(item.compare("default:iron_lump")==0) && 
                    !(item.compare("default:tree")==0) && 
                    !(item.compare("default:wood")==0) && 
                    !(item.compare("default:stick")==0) && 
                    !(item.compare("default:cobble")==0))
            {
                return false;
            }
    return true;
}

int Myinv::getLowestEmptyHotbar(Client *myclient,std::string toolkind)
{  
    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=myclient->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    InventoryList *playermlist = playerinv->getList("main");
    int foundplace=-9;
    if(playermlist != NULL)
    {
        //int listsize = playermlist->getSize();
        for (int tylu=0;tylu<9;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);

                std::string myitemname=(playeritem4.name.substr(0,12));

                if (playeritem4.name.compare("")==0)
                {
                    foundplace=tylu;
                    break;
                }
            } 
        }

        return foundplace;
}








int Myinv::getLowestEmptyNonhotbar(Client *myclient)
{  
    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=myclient->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    InventoryList *playermlist = playerinv->getList("main");
    int foundplace=-9;
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        for (int tylu=8;tylu<listsize;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);

            std::string myitemname=(playeritem4.name.substr(0,12));

            if (playeritem4.name.compare("")==0)
            {
                foundplace=tylu;
                break;
            }
        } 
    }
    return foundplace;
}

int Myinv::getLowestInvNumberThrow(Client *myclient,std::string toolkind)
{  
    InventoryLocation playerinventoryloc;
    // Equip pickaxe
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=myclient->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    InventoryList *playermlist = playerinv->getList("main");
    int foundplace=-9;
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        for (int tylu=8;tylu<listsize;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);

            std::string myitemname=(playeritem4.name.substr(0,12));

// NOTHING NAMED PICK THROW AWAY
            if ((!(myitemname.compare("default:pick")==0)) && !(playeritem4.name.compare("default:torch")==0) && !(playeritem4.name.compare("default:coal_lump")==0) && !(playeritem4.name.compare("default:cobble")==0))

            {
                foundplace=tylu;
                break;
            }
        } 
    }
        return foundplace;
}

int Myinv::getLowestInvNumber(Client *myclient,std::string toolkind,std::string invplace,std::string how)
{  
    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=myclient->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    InventoryList *playermlist = playerinv->getList(invplace);
    int foundplace=-9;
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        for (int tylu=0;tylu<listsize;tylu++)
        {
            ItemStack playeritem = playermlist->getItem(tylu);
            if (playeritem.name.compare(toolkind)==0)
            {
                foundplace=tylu;
                break;
            }
        } 
    }
    return foundplace;
}


int Myinv::getEmptyInventoryNum(Client *utt)
{
    InventoryLocation playerinventoryloc;
    // Equip pickaxe
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=utt->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    InventoryList *playermlist = playerinv->getList("main");
    //int co=0;
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        for (int tylu=0;tylu<listsize;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);
            std::string myitemname=(playeritem4.name);
            if (myitemname=="")
            {
                return tylu;
            }
        }
    }
    return -999;
}

int Myinv::getSlotToThrow(Client *cli,std::string where,std::string how)
{
    int returnint=-9;
    std::string throwmat=getThrowAway(clientobj,"main",how);
    if (throwmat.compare("-a")!=0)
    {
    returnint=getSlotWithMostOfMaterial(clientobj,throwmat,"main",how);
    }
    else
    {
        if (how.compare("nonhotbar")==0)
        {
             return rand()%24+8;
        }
        else
        {
             return rand()%32;
        }
    }
    return returnint;
}

int Myinv::getSlotWithMostOfMaterial(Client *cli,std::string material,std::string where,std::string how)
{
    int bestplace=-9;
    int bestcount=-9;

    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();

    Inventory *playerinv=cli->getInventory(playerinventoryloc);
    ItemStack playeritemagain;

    //typedef std::map< std::string, int > Dict;
    //typedef Dict::const_iterator It;
   //Dict d;

    InventoryList *playermlist = playerinv->getList(where);
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        int startnum=0;
        if (how.compare("nonhotbar")==0)
        {
        startnum=8;
        }
        for (int tylu=startnum;tylu<listsize;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);
            std::string myitemname=(playeritem4.name);

            if (myitemname.compare(material)==0)
            {
            if (getInventoryCount(clientobj,tylu ,"main")>bestcount)
                {
                    bestplace=tylu;
                    bestcount=getInventoryCount(clientobj,tylu ,"main");
                }
            }
        }
    }
    return bestplace;
}
std::string Myinv::getThrowAway(Client *cli,std::string where,std::string how)
{
    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=cli->getInventory(playerinventoryloc);
    ItemStack playeritemagain;
    typedef std::map< std::string, int > Dict;
    typedef Dict::const_iterator It;
   Dict d;

    InventoryList *playermlist = playerinv->getList(where);
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        int startnum=0;
        if (how.compare("nonhotbar")==0)
        {
        startnum=8;
        }
        for (int tylu=startnum;tylu<listsize;tylu++)
        {
            ItemStack playeritem4 = playermlist->getItem(tylu);
            std::string myitemname=(playeritem4.name);
            if (d.count(myitemname))
            {
            d[myitemname]+=getInventoryCount(clientobj,tylu ,"main");
            }
            else
            {
            d[myitemname]=getInventoryCount(clientobj,tylu ,"main");
            }
        }
            
            std::string kindtothrow="-a";
            for(std::map<std::string, int>::const_iterator it = d.begin(); it != d.end(); it++)
            {
                    std::string key = it->first;
                    int value = it->second;
                    printf("string was %s %i\n",key.c_str(),value);
                    if (key.compare("")==0)
                    {
                        continue;
                    }
                    if (isUsableMaterial(key))
                    {
                        kindtothrow=key;
                        printf("good material\n");
                    }
                    else
                    {
                        kindtothrow=key;
                        return kindtothrow;
                    }
            }
                if (kindtothrow.compare("-a")==0)
                {
    return "-a";
                }
        

}
    return "-a";
}
bool Myinv::hasMaterialsToCraft(Client *cli,std::string what,std::string how)
{

        if (what.compare("default:torch")==0)
        {
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","nonhotbar");
            int coalnum=getLowestInvNumber(clientobj,"default:coal_lump","main","nonhotbar");
            if (sticknum==-9)
            {
                return false;
            }
            if (coalnum==-9)
            {
                return false;
            }
            return true;
}
        else if (what.compare("default:pick_stone")==0)
        {
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","nonhotbar");
            if (sticknum==-9)
            {
                printf("could not make pickaxe due to lack of sticks\n");
                return false;
            }
            int cobblenum=getLowestInvNumber(clientobj,"default:cobble","main","nonhotbar");
            if (cobblenum==-9)
            {
                printf("could not make pickaxe due to lack of cobble\n");
                return false;
            }
            int stickcount=getInventoryCount(clientobj,sticknum ,"main");
// Returns the count of the item at position in invkind (main,craft, etc)
            printf("stikcnum=%i cobble=%i\n",sticknum,cobblenum);
            printf("stikcamnt=%i \n",stickcount);
            if (sticknum!=-9)
            {
                printf("coubld not get sticknum\n");
            }
            return true;
}
    return false;
}


std::pair <int,int>  Myinv::getSlotToPutBack(Client *myclient,std::string toolkind,std::string invplace,std::string how)
{
    int firstslot= getLowestInvNumber(clientobj,toolkind,invplace,how);
    int firstcount=getInventoryCount(clientobj,firstslot ,invplace);
    IItemDefManager* myitm=myclient->getItemDefManager();

    InventoryLocation playerinventoryloc;
    playerinventoryloc.setCurrentPlayer();
    Inventory *playerinv=myclient->getInventory(playerinventoryloc);

    InventoryList *playermlist = playerinv->getList(invplace);
    if(playermlist != NULL)
    {
        int listsize = playermlist->getSize();
        int startnum=0;
        if (how.compare("nonhotbar")==0)
        {
        startnum=8;
        }
        for (int tylu=startnum;tylu<listsize;tylu++)
        {
            ItemStack playeritem = playermlist->getItem(tylu);
            std::string myitemname=(playeritem.name);
            if (myitemname.compare(toolkind)==0)
            {
                int amt=playeritem.count;
                s16 max = myitm->get(myitemname).stack_max;
                int sparespace=max-amt;
                if (sparespace>0)
                {
                    return std::make_pair (tylu,sparespace); 
                }
            }
        }
    } 
    return std::make_pair(-9,-9);
}

std::string Myinv::missingMaterials(Client *clientobj,std::string thingToCraft,std::string how)
{

        if (thingToCraft.compare("default:torch")==0)
        {
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","nonhotbar");
            int coalnum=getLowestInvNumber(clientobj,"default:coal_lump","main","nonhotbar");
            if (sticknum==-9)
            {
                return "default:stick";
            }
            if (coalnum==-9)
            {
                return "default:coal_lump";
            }
        }
        else if (thingToCraft.compare("default:stick")==0)
        {
            int woodnum=getLowestInvNumber(clientobj,"default:wood","main","nonhotbar");
            if (woodnum==-9)
            {
                return "default:wood";
            }
        }
        else if (thingToCraft.compare("default:wood")==0)
        {
            int woodnum=getLowestInvNumber(clientobj,"default:tree","main","nonhotbar");
            if (woodnum==-9)
            {
                return "default:tree";
            }
        }
        else if (thingToCraft.compare("default:pick_stone")==0)
        {
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","nonhotbar");
            if (sticknum==-9)
            {
               // printf("could not make pickaxe due to lack of sticks\n");
                return "default:stick";
                //return false;
            }
            int cobblenum=getLowestInvNumber(clientobj,"default:cobble","main","nonhotbar");
            if (cobblenum==-9)
            {
                //printf("could not make pickaxe due to lack of cobble\n");
                return "default:cobble";
                //return false;
            }
            int stickcount=getInventoryCount(clientobj,sticknum ,"main");
// Returns the count of the item at position in invkind (main,craft, etc)
            printf("stikcnum=%i cobble=%i\n",sticknum,cobblenum);
            printf("stikcamnt=%i \n",stickcount);
            if (stickcount<2)
            {
                return "default:stick";
                //printf("coubld not get sticknum\n");
            }
            int cobblecount=getInventoryCount(clientobj,cobblenum ,"main");
            if (cobblecount<3)
            {
                return "default:cobble";
                //printf("coubld not get sticknum\n");
            }
        }
    return "-a";
    }


bool Myinv::canCraftSomeHow(Client *clientobj,std::string thingToCraft,std::string how)
{

        if (thingToCraft.compare("default:pick_stone")==0)
        {
        bool needcobble=false;
        bool needstick=false;
            int sticknum=getLowestInvNumber(clientobj,"default:stick","main","nonhotbar");
            if (sticknum==-9)
            {
               // printf("could not make pickaxe due to lack of sticks\n");
                needstick=true;
                //return false;
            }
            int cobblenum=getLowestInvNumber(clientobj,"default:cobble","main","nonhotbar");
            if (cobblenum==-9)
            {
                //printf("could not make pickaxe due to lack of cobble\n");
                needcobble=true;
                //return false;
            }
            int stickcount=getInventoryCount(clientobj,sticknum ,"main");
// Returns the count of the item at position in invkind (main,craft, etc)
            printf("stikcnum=%i cobble=%i\n",sticknum,cobblenum);
            printf("stikcamnt=%i \n",stickcount);
            if (stickcount<2)
            {
                needstick=true;
                //printf("coubld not get sticknum\n");
            }
            int cobblecount=getInventoryCount(clientobj,cobblenum ,"main");
            if (cobblecount<3)
            {
                needcobble=true;
                //printf("coubld not get sticknum\n");
            }

        if (needcobble==true)
        {
            return false;
        }
        if (needcobble==false && needstick==false)
        {
            return true;
        }
        if (needcobble==false && needstick==true)
        {
            int woodnum=getLowestInvNumber(clientobj,"default:wood","main","nonhotbar");
            int treenum=getLowestInvNumber(clientobj,"default:tree","main","nonhotbar");
            if (woodnum!=-9 || treenum!=-9)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;

       } 
    if (thingToCraft.compare("default:stick")==0)
    {
            int woodnum=getLowestInvNumber(clientobj,"default:wood","main","nonhotbar");
            int treenum=getLowestInvNumber(clientobj,"default:tree","main","nonhotbar");
            if (woodnum!=-9 || treenum!=-9)
            {
                return true;
            }
            else
            {
                return false;
            }
    }
    if (thingToCraft.compare("default:wood")==0)
    {
            int treenum=getLowestInvNumber(clientobj,"default:tree","main","nonhotbar");
            if (treenum!=-9)
            {
                return true;
            }
            else
            {
                return false;
            }
    }



}

