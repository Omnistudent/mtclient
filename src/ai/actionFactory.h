/*
 *  actionFactory.h
 *  minetest
 *
 *  Created by security on 11/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

//#include "ai/ai_utilites.h"
#include "brainaction.h"
//#include "client.h"
//#include "chat.h"
#include "clientmap.h"
#include "environment.h"
#include "util/string.h"
//#include "game.h"
#include "util/directiontables.h"
#include "nodedef.h"
#include "camera.h"
#include "string.h"




class ActionFactory{
public:
        Client* clientobj;
	//Brain2();
	ActionFactory(Client* c);
 //       brainaction::Brainaction* brainact;

        Brainaction* makeCenterContainer2(float mindist);
        Brainaction* makeCenterContainer3(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
        Brainaction* makeMoveContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);

Brainaction* makeExtendContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);

Brainaction* makeDigContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,bool makejumpactions);

Brainaction* makeMoveContainerFromTo(v3f startposition,v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);

Brainaction* makeTorchContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);






};

