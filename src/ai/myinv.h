/*
 *  myinv.h
 *  minetest
 *
 *  Created by security on 11/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "client.h"
#include "chat.h"
#include "clientmap.h"
#include "environment.h"
#include "util/string.h"
//#include "game.h"
#include "util/directiontables.h"
#include "nodedef.h"
#include "camera.h"
#include "string.h"

class Myinv{
public:
        Client* clientobj;
	//Brain2();
	Myinv(Client* c);
        bool getIsInventoryEmpty(Client *myclient,std::string invkind);
        int getFirstNonEmptyInvSpot(Client *myclient,std::string invkind);
        int getFirstEmptyInvSpot(Client *myclient,std::string invkind);
        int getInventoryCount(Client *myclient,int position ,std::string invkind);
        std::string getInventoryItem(Client *myclient,int position ,std::string invkind);
        bool moveInventories(Client *myclient, std::string frominv ,int posfrom ,std::string toinv, int posto ,int amnt);
        bool throwfrominv(Client *myclient, std::string frominv ,int posfrom ,int amnt);
        bool craftInvOK(Client *myclient, std::string item);
        bool moveMaterialsToCraft(Client *clientobj, std::string thing);
        bool isUsableMaterial(std::string item);

        //int getInvPickNumberFromInv(Client *myclient,std::string toolkind,std::string how);

        // get the number of first item in inv
        int getLowestInvNumber(Client *myclient,std::string toolkind,std::string invplace,std::string how);

        int getLowestInvNumberThrow(Client *myclient,std::string toolkind);
        int getLowestEmptyNonhotbar(Client *myclient);
        int getLowestEmptyHotbar(Client *myclient,std::string toolkind);
        int getEmptyInventoryNum(Client *utt);
        std::string getEquipped();
        
        //get the slot containing the most of a certain material
        int getSlotWithMostOfMaterial(Client *cli,std::string material,std::string where,std::string how);
        // returns a slot that seems good to throw from 
        int getSlotToThrow(Client *cli,std::string where,std::string how);
        


        //get an item to throw away
        std::string getThrowAway(Client *cli,std::string where,std::string how);

        // check if we have the materials neccessary to craft an item
        bool hasMaterialsToCraft(Client *cli,std::string what,std::string how);

        // attempt to max up the slots, returns place and amnt of spare space for tookind
        std::pair <int,int> getSlotToPutBack(Client *myclient,std::string toolkind,std::string invplace,std::string how);

        std::string missingMaterials(Client *clientobj,std::string thingToCraft,std::string how);

        bool canCraftSomeHow(Client *clientobj,std::string thingToCraft,std::string how);





    





        







};
