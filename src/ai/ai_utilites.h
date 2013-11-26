/*
 *  ai_utilites.h
 *  minetest
 *
 *  Created by security on 11/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
//#include "util/string.h"
//#include "string.h"
#include "client.h"
//#include "chat.h"
//#include "clientmap.h"
#include "environment.h"
//#include "util/string.h"
//#include "game.h"
//#include "util/directiontables.h"
//#include "nodedef.h"
//#include "camera.h"
//#include "string.h"

float test444()
{
    return 0.5;
}
float get_middle_pos2(float num)
{
    float t;
    t= (BS*round((num)/BS));
    return t;
}

v3f getMiddlePlayer2(LocalPlayer *player)
{
    v3f middleplayer=v3f(get_middle_pos2(player->getPosition().X),get_middle_pos2(player->getPosition().Y-0.01),get_middle_pos2(player->getPosition().Z));
    return middleplayer;
}

f32 getYawToPosition(v3f playerpos,v3f masterpos)
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


