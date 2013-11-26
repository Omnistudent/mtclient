/*
 Minetest-c55
 Copyright (C) 2011 celeron55, Perttu Ahola <celeron55@gmail.com>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "irrlichttypes_extrabloated.h"

//#include "chat.h"
//#include "client.h"
#include "chat.h"
//#include "clientmap.h"
//#include "environment.h"
#include "util/string.h"
//#include "game.h"
//#include "util/directiontables.h"
//#include "nodedef.h"
//#include "camera.h"


//class Brainaction;

class Brainaction{
public:
	//Brain2();
        v3f destinationCoords;
        v3f actionCoords;

	Brainaction(std::string);
	Brainaction();
        std::string brainDO;
        bool jump;
        std::string actiondescription;
        float waited_time;
        float activatedtime;
        float lasttime;
        float waittime;
        float destinationYaw;
        float destinationPitch;
        std::string botmessage;
        bool inserted;
        bool just_inserted;
        int intnumber; 
        //bool just_emptied_craftinv;


	
	//Client* clientobj;
	//std::list<ChatLine> currentchatlist;
	//void step();
        int num;
        float destinationTolerance;
        std::list<Brainaction*> subacts;
        Brainaction* actionowner;
        //std::list<int> subacts;
//	std::list<ChatLine> currentchatlist;
        float lastdistance;


bool finished;




	
v3f getDestinationCoords();
int setDestinationCoords(v3f);
v3f getActionCoords();
int setActionCoords(v3f);
int setDestinationYaw(float);
int setDestinationPitch(float);
float getDestinationYaw();
float getDestinationPitch();
std::string getBrainAction();
std::string setBrainAction(std::string);
float getDestinationTolerance();
int setDestinationTolerance(float);
int setWaitedTime(float time);
Brainaction* getParent();
void setParent(Brainaction* par);
std::string getActionDescription();
void setActionDescription(std::string desc);



};







