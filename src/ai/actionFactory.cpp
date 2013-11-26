/*
 *  actionFactory.cpp
 *  minetest
 *
 *  Created by security on 11/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#include "actionFactory.h"

#include "ai/ai_utilites.h"
ActionFactory::ActionFactory(Client* c)
{
        clientobj=c;
    

}

//int ActionFactory::makeCenterContainer2(float mindist)
//{
 //   return 2;
//}


Brainaction* ActionFactory::makeCenterContainer3(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions)
{
    float m_mindist=mindist;

    v3f midpos=getMiddlePlayer2(player);
    v3f midposPlayerLev=v3f(midpos.X,player->getPosition().Y,midpos.Z);

    float orginialYaw=player->getYaw();

    v3f m_playerposition=player->getPosition();

    float m_jawtoposition=getYawToPosition(m_playerposition,midposPlayerLev);

    float m_distance=m_playerposition.getDistanceFrom(midposPlayerLev);
    if (m_distance>=m_mindist)
    {
        Brainaction *m_movestep_container=new Brainaction("CONTAINER");
        m_movestep_container->actiondescription=actiondescription;
        m_movestep_container->setDestinationTolerance(mindist);

        // make turn action
        Brainaction *m_container_turn=new Brainaction("TURNYAW_DEGREES");
        m_container_turn->setDestinationTolerance(mindist);
        m_container_turn->setDestinationYaw(m_jawtoposition);

        m_container_turn->actiondescription="turn action, machine made";

        // make move action
        Brainaction *m_movestep=NULL;

        // decide move action
        m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK"); 

        m_movestep->actiondescription="machine made movestep";
        m_movestep->setDestinationTolerance(mindist);
        
        Brainaction *m_movestep2=new Brainaction("STOP");
        
        // set destination coords
        m_movestep->setDestinationCoords(midposPlayerLev);

        Brainaction *m_wait=new Brainaction("WAIT");
        m_wait->waittime=waittime;
        m_wait->actiondescription="machine made waiting for turn";

        Brainaction *m_wait2=new Brainaction("WAIT");
        m_wait2->waittime=waittime;
        m_wait2->actiondescription="machine made waiting for move";

        Brainaction *startsneak=new Brainaction("START_SNEAK");
        startsneak->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(startsneak);

        // add actions to movestep container
        m_wait->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(m_wait);

        m_container_turn->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(m_container_turn);

        m_wait2->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(m_wait2);

        m_movestep->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(m_movestep);

        m_movestep2->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(m_movestep2);

        Brainaction *stopsneak=new Brainaction("STOP_SNEAK");
        stopsneak->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(stopsneak);

        Brainaction *turn_back=new Brainaction("TURNYAW_DEGREES");
        turn_back->setDestinationTolerance(mindist);
        turn_back->setDestinationYaw(orginialYaw);
        turn_back->actiondescription="turn action, machine made";

        turn_back->setParent(m_movestep_container);
        m_movestep_container->subacts.push_back(turn_back);

        return m_movestep_container; 
    }
    return NULL;

}

Brainaction* ActionFactory::makeMoveContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions)
{
    float m_mindist=mindist;
    v3f m_playerposition=player->getPosition();
    float m_jawtoposition=getYawToPosition(m_playerposition,destinationposition);

    v3f destinationposition_playerlevel=v3f(destinationposition.X,m_playerposition.Y,destinationposition.Z);

    float m_distance=m_playerposition.getDistanceFrom(destinationposition_playerlevel);

    Brainaction *m_movestep_container=new Brainaction("CONTAINER");
    m_movestep_container->actiondescription=actiondescription;
    m_movestep_container->setDestinationTolerance(mindist);

    // make turn action
    Brainaction *m_container_turn=new Brainaction("TURNYAW_DEGREES");
    m_container_turn->setDestinationTolerance(mindist);
    m_container_turn->setDestinationYaw(m_jawtoposition);
    m_container_turn->setDestinationCoords(destinationposition_playerlevel);
    m_container_turn->actiondescription=actiondescription;

    // make move action
    Brainaction *m_movestep=NULL;

    // decide move action
    if (m_distance>=m_mindist)
    {
        if (makejumpactions.compare("JUMP")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD_JUMP");
        }
        else if (makejumpactions.compare("FORWARD")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD");
        }
        else if (makejumpactions.compare("NOCHECK")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK");
        }
    }
    else
    {
        m_movestep=new Brainaction("STOP");
    }

    m_movestep->actiondescription="machine made movestep";
    m_movestep->setDestinationTolerance(mindist);
    
    Brainaction *m_movestep2=new Brainaction("STOP");
    
    // set destination coords
    m_movestep->setDestinationCoords(destinationposition_playerlevel);

    Brainaction *m_wait=new Brainaction("WAIT");
    m_wait->waittime=waittime;
    m_wait->actiondescription=actiondescription;

    Brainaction *m_wait2=new Brainaction("WAIT");
    m_wait2->waittime=waittime;
    m_wait2->actiondescription=actiondescription;


    // add actions to movestep container
    m_wait->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_wait);

    m_container_turn->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_container_turn);

    m_wait2->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_wait2);

    m_movestep->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_movestep);

    m_movestep2->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_movestep2);

    return m_movestep_container; 
}
Brainaction* ActionFactory::makeExtendContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions)
{

    Brainaction *m_extend_container=new Brainaction("CONTAINER");
    m_extend_container->actiondescription=actiondescription;
    m_extend_container->setDestinationTolerance(mindist);

    v3f middleplayer=v3f(0,1*BS,0)+getMiddlePlayer2(player);

    v3f extrarange=v3f(0,0.5*BS,0)+destinationposition;
    v3f edgepos=middleplayer+extrarange;
    //printf("edgepos in extend %f %f %f\n",edgepos.X,edgepos.Y,edgepos.Z);

    Brainaction *gethotbar=new Brainaction("GET_HOTBAR");
    gethotbar->actiondescription="getting empty hotbar slot";
    gethotbar->botmessage="2";
    gethotbar->setParent(m_extend_container);
    m_extend_container->subacts.push_back(gethotbar);

    Brainaction *q=new Brainaction("EQUIP_ITEM");
    q->botmessage="default:cobble";
    q->actiondescription="get cobblestone";
    q->setParent(m_extend_container);
    m_extend_container->subacts.push_back(q);

    Brainaction *startsneak=new Brainaction("START_SNEAK");
    startsneak->setParent(m_extend_container);
    m_extend_container->subacts.push_back(startsneak);

    Brainaction *movestep_container_made=makeMoveContainer(edgepos, "machine made",0.00001,1.0,3.0,env,player,"NOCHECK");

    movestep_container_made->setParent(m_extend_container);
    m_extend_container->subacts.push_back(movestep_container_made);

    Brainaction *turn=new Brainaction("TURNYAW_DEGREES");
    turn->setDestinationYaw(getYawToPosition(edgepos,middleplayer));
    turn->actiondescription="xtendturn";

    turn->setParent(m_extend_container);
    m_extend_container->subacts.push_back(turn);

    v3f guessed=middleplayer+0.5*destinationposition;
    //printf("guessed sidepos in extend %f %f %f\n",guessed.X,guessed.Y,guessed.Z);

    Brainaction *pitch=new Brainaction("TURNPITCH_TO");
    //Brainaction *pitch=new Brainaction("TURNPITCH_DEGREES");
    pitch->setDestinationPitch(80.0);
    pitch->setDestinationCoords(guessed);

    v3f blocksidepos=v3f(middleplayer.X,middleplayer.Y,middleplayer.Z)+v3f(0.5*destinationposition.X,0.5*destinationposition.Y,0.5*destinationposition.Z);
    pitch->setParent(m_extend_container);
    m_extend_container->subacts.push_back(pitch);
    Brainaction *waiter=new Brainaction("WAIT");
    waiter->waittime=0.0000001;
    waiter->setParent(m_extend_container);
    m_extend_container->subacts.push_back(waiter);

    Brainaction *rrc=new Brainaction("REAL_RIGHT_CLICK");

    rrc->setParent(m_extend_container);
    m_extend_container->subacts.push_back(rrc);

    //    Brainaction *waiter=new Brainaction("WAIT");
     //       waiter->waittime=0.00000000001;
    //waiter->setParent(m_extend_container);
    //m_extend_container->subacts.push_back(waiter);

    Brainaction *relrc=new Brainaction("RELEASE_RIGHT_CLICK");
    relrc->setParent(m_extend_container);
    m_extend_container->subacts.push_back(relrc);

   Brainaction *goback=makeMoveContainerFromTo(edgepos,middleplayer, "return trip",0.00000001,1.0,3.0,env,player,"NOCHECK");
    goback->setParent(m_extend_container);
    m_extend_container->subacts.push_back(goback);

    Brainaction *stop=new Brainaction("STOP");
    stop->setParent(m_extend_container);
    m_extend_container->subacts.push_back(stop);

    Brainaction *stopsneak=new Brainaction("STOP_SNEAK");
    stopsneak->setParent(m_extend_container);
    m_extend_container->subacts.push_back(stopsneak);

    return m_extend_container; 
}
Brainaction* ActionFactory::makeDigContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,bool makejumpactions)
{
    v3f m_playerposition=player->getPosition();

    Brainaction *m_digstep_container=new Brainaction("CONTAINER");
    m_digstep_container->actiondescription=actiondescription;

    Brainaction *waiter=new Brainaction("WAIT");
    waiter->waittime=waittime;

    Brainaction *stopper=new Brainaction("STOP");

    Brainaction *turn=new Brainaction("TURNYAW_DEGREES");
    turn->setDestinationYaw(getYawToPosition(m_playerposition,m_playerposition+destinationposition));
    turn->actiondescription="magedigturn";


    v3f middleplayer=getMiddlePlayer2(player);
    Brainaction *pitch=new Brainaction("TURNPITCH_TO");
    pitch->setDestinationCoords(destinationposition+middleplayer+v3f(0,1.5*BS,0));

    Brainaction *waiter_dig=new Brainaction("WAIT");
    waiter_dig->waittime=0.000001;
    // old working

    //Brainaction *pitch=new Brainaction("TURNPITCH_DEGREES");

    //v3f dig_position_pitch=m_playerposition+v3f(destinationposition.X,destinationposition.Y,destinationposition.Z);

    //v3f actual_block_pos=v3f(0,BS,0)+v3f(get_middle_pos(dig_position_pitch.X),get_middle_pos(dig_position_pitch.Y-0.01),get_middle_pos(dig_position_pitch.Z));

    //pitch->setDestinationPitch(getPitchToPosition(player,actual_block_pos.X,actual_block_pos.Y,actual_block_pos.Z,env));

    //printf("makedig destination %f %f %f\n",destinationposition.X,destinationposition.Y,destinationposition.Z);

    pitch->actiondescription="pitch";

    Brainaction *gethotbar=new Brainaction("GET_HOTBAR");
    gethotbar->actiondescription="getting empty hotbar slot";
    gethotbar->botmessage="0";

    Brainaction *q=new Brainaction("EQUIP_ITEM");
    q->botmessage="default:pick_stone";
    q->actiondescription="digging";

    Brainaction *m_container_dig=new Brainaction("DIG");
    m_container_dig->setDestinationCoords(destinationposition);
    m_container_dig->actiondescription="dig action, machine made";

    turn->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(turn);

    pitch->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(pitch);

    waiter_dig->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(waiter_dig);

    gethotbar->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(gethotbar);

    q->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(q);

    m_container_dig->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(m_container_dig);

    waiter->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(waiter);

    stopper->setParent(m_digstep_container);
    m_digstep_container->subacts.push_back(stopper);

    return m_digstep_container; 
}
Brainaction* ActionFactory::makeMoveContainerFromTo(v3f startposition,v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions)
{
    float m_move_distance=movedistance;
    float m_mindist=mindist;
    v3f m_move_direction = v3f(0,0,m_move_distance*BS);
    v3f m_playerposition=startposition;

    float m_jawtoposition=getYawToPosition(m_playerposition,destinationposition);
    v3f destinationposition_playerlevel=v3f(destinationposition.X,m_playerposition.Y,destinationposition.Z);
    float m_distance=m_playerposition.getDistanceFrom(destinationposition_playerlevel);

    Brainaction *m_movestep_container=new Brainaction("CONTAINER");
    m_movestep_container->actiondescription=actiondescription;
    m_movestep_container->setDestinationTolerance(mindist);

    // make turn action
    Brainaction *m_container_turn=new Brainaction("TURNYAW_DEGREES");
    m_container_turn->setDestinationTolerance(mindist);
    m_container_turn->setDestinationYaw(m_jawtoposition);

    m_container_turn->setDestinationCoords(destinationposition_playerlevel);
    m_container_turn->actiondescription=actiondescription;

    // make move action
    Brainaction *m_movestep=NULL;

    // decide move action
    if (m_distance>=m_mindist)
    {
        if (makejumpactions.compare("JUMP")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD_JUMP");
        }
        else if (makejumpactions.compare("FORWARD")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD");
        }
        else if (makejumpactions.compare("NOCHECK")==0)
        {
            m_movestep=new Brainaction("MOVE_TO_POSITION_FORWARD_NO_ENV_CHECK");
        }

    }
    else
    {
        m_movestep=new Brainaction("STOP");
    }
    m_movestep->actiondescription="machine made movestep";
    m_movestep->setDestinationTolerance(mindist);
    
    Brainaction *m_movestep2=new Brainaction("STOP");
    
    // set destination coords
    m_movestep->setDestinationCoords(destinationposition_playerlevel);

    Brainaction *m_wait=new Brainaction("WAIT");
    m_wait->waittime=waittime;
    m_wait->actiondescription=actiondescription;

    Brainaction *m_wait2=new Brainaction("WAIT");
    m_wait2->waittime=waittime;
    m_wait2->actiondescription=actiondescription;

    // add actions to movestep container
    m_wait->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_wait);

    m_container_turn->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_container_turn);

    m_wait2->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_wait2);

    m_movestep->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_movestep);

    m_movestep2->setParent(m_movestep_container);
    m_movestep_container->subacts.push_back(m_movestep2);

    return m_movestep_container; 
}   

Brainaction* ActionFactory::makeTorchContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions)
{
    v3f m_playerposition=player->getPosition();

    v3f destinationposition_playerlevel=v3f(destinationposition.X,m_playerposition.Y,destinationposition.Z);

    Brainaction *m_extend_container=new Brainaction("CONTAINER");
    m_extend_container->actiondescription=actiondescription;
    m_extend_container->setDestinationTolerance(mindist);

    v3f middleplayer=v3f(0,1*BS,0)+getMiddlePlayer2(player);
    
    v3f extrarange=v3f(0,0.5*BS,0)+destinationposition;
    v3f edgepos=middleplayer+extrarange;

    Brainaction *turn=new Brainaction("TURNYAW_DEGREES");
    turn->setDestinationYaw(getYawToPosition(edgepos,middleplayer));
    turn->actiondescription="torchturn";

    turn->setParent(m_extend_container);
    m_extend_container->subacts.push_back(turn);

    Brainaction *pitch=new Brainaction("TURNPITCH_DEGREES");
    pitch->setDestinationPitch(80.0);

    pitch->setParent(m_extend_container);
    m_extend_container->subacts.push_back(pitch);
    
    Brainaction *gethotbar=new Brainaction("GET_HOTBAR");
    gethotbar->botmessage="1";
    gethotbar->actiondescription="getting empty hotbar slot";

    //printf("making position 1 empty in hotbar\n");

    gethotbar->setParent(m_extend_container);
    m_extend_container->subacts.push_back(gethotbar);

    Brainaction *q2=new Brainaction("EQUIP_ITEM");
    q2->actiondescription="digging";
    q2->botmessage="default:torch";

    q2->setParent(m_extend_container);
    m_extend_container->subacts.push_back(q2);

    Brainaction *waiter=new Brainaction("WAIT");
    waiter->waittime=0000000.1;
    //waiter->setParent(m_extend_container);
    //m_extend_container->subacts.push_back(waiter);

    Brainaction *rrc=new Brainaction("REAL_RIGHT_CLICK");

    rrc->setParent(m_extend_container);
    m_extend_container->subacts.push_back(rrc);
        //    Brainaction *waiter=new Brainaction("WAIT");
         //       waiter->waittime=0.00000000001;
            //waiter->setParent(m_extend_container);
            //m_extend_container->subacts.push_back(waiter);
    Brainaction *relrc=new Brainaction("RELEASE_RIGHT_CLICK");

    relrc->setParent(m_extend_container);
    m_extend_container->subacts.push_back(relrc);

    Brainaction *stop=new Brainaction("STOP");
    stop->setParent(m_extend_container);
    m_extend_container->subacts.push_back(stop);

    return m_extend_container; 
}



