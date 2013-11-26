#include "brainaction.h"
#include "util/string.h"


//v3f destinationCoords;


    Brainaction::Brainaction()                         // constructor; initialize the list to be empty
    {
    num=1; 
    brainDO="NOTHING"; 
    jump=false;
    destinationTolerance=5.0;
    finished=false;
    }

    Brainaction::Brainaction(std::string domess)                         // constructor; initialize the list to be empty
    {
    num=1; 
    brainDO=domess; 
    destinationTolerance=3.0;
    waited_time=-1;
    activatedtime=-1;
    lasttime=-1;
    finished=false;
    actiondescription="unset";
    actionowner=NULL;
    destinationCoords=v3f(0,0,0);
    actionCoords=v3f(0,0,0);
    waittime=3.0;
    destinationYaw=-9999999;
    destinationPitch=-9999999;
    lastdistance=-9;

    botmessage="no bot message";

    inserted=false;
    just_inserted=false;
    //just_emptied_craftinv=false;
    intnumber=-9; 



    


    }

/*
	Check if a node is pointable
*/
v3f Brainaction::getDestinationCoords(){
    return Brainaction::destinationCoords;
}
int Brainaction::setDestinationCoords(v3f dest){
    destinationCoords=dest;
}
v3f Brainaction::getActionCoords(){
    return Brainaction::actionCoords;
}
int Brainaction::setActionCoords(v3f dest){
    actionCoords=dest;
}

std::string Brainaction::getBrainAction(){
    return brainDO;

}
std::string Brainaction::setBrainAction(std::string ord){

    brainDO=ord;

}

float Brainaction::getDestinationTolerance(){


    return destinationTolerance;
}

int Brainaction::setDestinationTolerance(float tol){


    destinationTolerance=tol;
}

int Brainaction::setDestinationYaw(float a)
{
    destinationYaw=a;
}
int Brainaction::setDestinationPitch(float a)
{
    destinationPitch=a;
}
float Brainaction::getDestinationYaw()
{
    return destinationYaw;
}
float Brainaction::getDestinationPitch()
{
    return destinationPitch;
}


int Brainaction::setWaitedTime(float time){

    waited_time=time;
}

void Brainaction::setParent(Brainaction* par){

    actionowner=par;
}

Brainaction* Brainaction::getParent(){
    return actionowner;
}
std::string Brainaction::getActionDescription(){
    return actiondescription;
}
void Brainaction::setActionDescription(std::string desc){
    actiondescription=desc;
}
	

