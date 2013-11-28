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


//#include "irrlichttypes_extrabloated.h"
//#include "chat.h"
#include "client.h"
#include "chat.h"
#include "clientmap.h"
#include "environment.h"
#include "util/string.h"
#include "game.h"
#include "util/directiontables.h"
#include "nodedef.h"
#include "camera.h"
#include "string.h"
//#include "brainaction.h"
#include "ai/myinv.h"
#include "ai/actionFactory.h"

#include "ai/brain_utilities.h"

//standard libraries
#include <iostream>
#include <ctime>

//custom includes
#include "ai/neuralNetwork.h"
#include "ai/neuralNetworkTrainer.h"


//class Brain;

//class Brain 
class Brain : public InputHandler
{

public:


	Brain(Client* c,Camera* k,std::string mastername);

	virtual bool isKeyDown(const KeyPress &keyCode);
	virtual bool wasKeyDown(const KeyPress &keyCode);
	virtual v2s32 getMousePos();
	virtual void setMousePos(s32 x, s32 y);
	virtual bool getLeftState();
	virtual bool getRightState();
	virtual bool getLeftClicked();
	virtual bool getRightClicked();
	virtual void resetLeftClicked();
	virtual void resetRightClicked();
	virtual bool getLeftReleased();
	virtual bool getRightReleased();
	virtual void resetLeftReleased();
	virtual void resetRightReleased();

	virtual s32 getMouseWheel();

	void step(float tim);
        void clearMessline();
private:

	//Brain2();
	
	Client* clientobj;
        Myinv* myInvManager;
        ActionFactory* actionFac; 
	std::list<ChatLine> currentchatlist;
	std::list<ChatLine> formerchatlist;

        std::string master;
	
	void addMessline(ChatLine linnne);
    const bool getDigStatus();

    //MyInvManager* invManager;


    Brainaction* brainact;
    Brainaction* currentact;
    std::list<Brainaction*> brainacts;
    std::list<Brainaction*> currentlist;

    float lastdtime;


    bool inserted;
    bool acted;


    float time_last_move;
    float time_last_dig;
    float time_last_extend;
    
    float happiness;


    const bool getRightButtonState();
    const f32 getBotYaw(); 
    const f32 getBotPitch(); 
    void setDigStatus(bool dig); 
    //void addMessline(ChatLine linnne);
    bool LeftB;
    bool rightbutton;
    bool forwardstate;
    bool backstate;
    bool leftstate;
    bool rightstate;
    bool jumpstate;
    bool specialstate;
    bool sneakstate;
    bool waited;
    bool GetRightClicked;
    bool GetLeftClicked;



	KeyList keydown;
	v2s32 mousepos;
	v2s32 mousespeed;
	bool leftdown;
	bool rightdown;
	bool leftclicked;
	bool rightclicked;
	bool leftreleased;
	bool rightreleased;




    // list of materials, in the x range:-1, 0, 1
    std::vector<std::string> last_materialsx;
    // list of materials in the z range -1 0 1
    //std::vector<std::vector> last_materialsz;
    // list of materials in the z range -1 0 1
    //std::vector<std::vector> last_materialsy;


    std::string botcommand;
    bool dig;
    bool follow;
    float lasttime;
    bool waiting;
    int number_of_steps;
    bool reacted_to_chat;
    std::list<ChatLine> lastchatlist;
	
    f32 botYaw;
    f32 botPitch;
    v3f bot_desired_position;


    v3f lastposition;
    float lastyaw;
    float lastdistance;

    Client* utt;
    Camera* kamera;
    Inventory* chestinventory;
	
	
    bool getForwardState();
    bool getBackState();
   // bool getLeftState();
    //bool getRightState();
    bool getJumpState();
    bool getSpecialState();
    bool getSneakState();
    void setChestInventory(Inventory *chestenv); 
    //void resetRightClicked();
    //void resetLeftClicked();
    //v2s32 getMousePos();



 
    //bool getRightClicked();
    //bool getLeftClicked();

    std::string getYawToMaster_string(LocalPlayer *player,ClientEnvironment *m_env);
    v3f getYawToMaster_pos(LocalPlayer *player,ClientEnvironment *m_env,std::string master);
    f32 getYawToMaster_yaw(LocalPlayer *player,v3f masterpos);
    f32 getDistToMaster(LocalPlayer *player,v3f masterpos);

    //PointedThing getPointedThing(Client *client, v3f player_position, v3f camera_direction, v3f camera_position, core::line3d<f32> shootline, f32 d,
//								 bool liquids_pointable, bool look_for_object, std::vector<aabb3f> &hilightboxes, ClientActiveObject *&selected_object);
    //inline bool isPointableNode(const MapNode& n, Client *client, bool liquids_pointable);
 //   PointedThing pointed;
  //  PointedThing getPointed();
   // ClientActiveObject* getSelected();
    //ClientActiveObject* selected_object;
    f32 getYawToPosition(LocalPlayer *player,float x,float y,float z,ClientEnvironment *env);
    f32 getPitchToPosition(LocalPlayer *player,float x,float y,float z,ClientEnvironment *env);
    f32 getDistToPosition(LocalPlayer *player,v3f position);
    //std::string getPointedType(LocalPlayer *player, Camera *kamera,ClientEnvironment *env);
    bool allisair(LocalPlayer *player,ClientEnvironment *env,float poslist[][3] ,int le);
    bool all_is_solid(LocalPlayer *player,ClientEnvironment *env,float poslist[][3],int le);
    v3f desired_dig_position;
    //f32 getDistToPosition_v3f(LocalPlayer *player,v3f desired_position ,ClientEnvironment *m_env);
    f32 getDistToPosition_v3f(LocalPlayer *player,v3f desired_position);
    f32 getYawToPosition_v3f(LocalPlayer *player,v3f desired_position);
    float get_middle_pos(float num);

    bool checkFinished(LocalPlayer *player, Brainaction *ba,ClientEnvironment *env);
    bool checkAction(LocalPlayer *player, Brainaction *ba,ClientEnvironment *env);
    bool performAction(LocalPlayer *player,Brainaction *ba,ClientEnvironment *env);

    bool checkJump(LocalPlayer *player,Brainaction *ba, ClientEnvironment *env);
    v3f getNearestByType(LocalPlayer *player,ClientEnvironment *env, int scanrange, std::string type);
    
//    Brainaction* makeMoveContainer(v3f destinationposition, std::string actiondescription,float waittime,ClientEnvironment *env,LocalPlayer *player);
//
//    Brainaction* makeMoveContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
//    Brainaction* makeMoveContainerFromTo(v3f startposition,v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
//    Brainaction* makeExtendContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
//    Brainaction* makeTorchContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
//    Brainaction* makeDigContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,bool makejumpactions);
//    //Brainaction* makeCenterContainer(v3f destinationposition, std::string actiondescription,float waittime ,float movedistance,float mindist,ClientEnvironment *env,LocalPlayer *player,std::string makejumpactions);
v3f getMiddlePlayer(LocalPlayer *player);




// Prints info about the current action, for debugging
void printcontainerInfo(Brainaction *ba);


std::list<std::wstring> check_chat(std::list<ChatLine> currentchatlist ,LocalPlayer* player, ClientEnvironment* env);
//std::wstring check_chat(std::list<ChatLine> currentchatlist ,LocalPlayer* player, ClientEnvironment* env);
//bool check_commands(std::wstring thecommand, Brainaction* action);
bool check_commands(LocalPlayer *player, std::list<std::wstring> thecommandlist, Brainaction* action);

    
f32 getYawToPosition(v3f playerpos,v3f masterpos);

v3f get_nswe_offset(v3f playerposition,v3f chest_destination);

// get an empty number to place stuff in
//int getEmptyInventoryNum(Client *utt);
std::string getAsoluteMaterial(LocalPlayer *player,ClientEnvironment *env,int x, int y, int z);
std::string getDirectionMaterial(LocalPlayer *player,ClientEnvironment *env,int x, int y, int z);
//std::string getDirectionMaterial2(LocalPlayer *player,ClientEnvironment *env,int x, int y, int z);


bool isDiggable(std::string mat);
bool isStandable(std::string mat);
//int getLowestInvNumber(Client *myclient,std::string toolkind);
//int getLowestInvNumberThrow(Client *myclient,std::string toolkind);
//int getLowestEmptyNonhotbar(Client *myclient,std::string toolkind);
//int getLowestEmptyHotbar(Client *myclient,std::string toolkind);
//int getInvPickNumberFromInv(Client *myclient,std::string toolkind);

float degrees_to_plusmin360(float inangle);
float getNormalizedDegreeDifference(float ang1, float ang2);

//bool craftItem();
//std::string getInventoryItem(Client *myclient,int position ,std::string invkind);
//bool getIsInventoryEmpty(Client *myclient,std::string invkind);
//int getLowestInvNumber(Client *myclient,std::string toolkind,std::string invplace);
//int getFirstEmptyInvSpot(Client *myclient,std::string invkind);
//int getFirstNonEmptyInvSpot(Client *myclient,std::string invkind);
//bool moveInventories(Client *myclient, std::string frominv ,int posfrom ,std::string toinv, int posto ,int amnt);
//bool throwfrominv(Client *myclient, std::string frominv ,int posfrom ,int amnt);
//int getInventoryCount(Client *myclient,int position ,std::string invkind);






//bool craftInvOK(Client *myclient, std::string item);
//bool moveMaterialsToCraft(Client *myclient, std::string thing);
//bool isUsableMaterial(std::string item);

// Returns the hotbar slot designated for a tool/item
int getDesignatedHotbarSlot(std::string kind);





Brainaction*  preinsertOrder(Brainaction *insertorder,Brainaction *originalorder);


};





