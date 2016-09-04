/*All values are in meters*/

#include<graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#define EARTH_GRAVITY 9.81
#define PI 3.14159265359
#define FRAME_RATE 60
#define FRAME_DURATION 1.0/(float)FRAME_RATE
#define UPWARD 0
#define DOWNWARD 1
using namespace std;
int max_height;
int height;
int trial=0;

class Ball
{
public:
  /* Ball properties*/
  float radius;
  float mass;
  
  /*Ball position in metres*/
  float x,y,z;
  
  /*Velocity components*/
  float vx,vy,vz;
  /*Acceleration components*/
  float ax,ay,az;
  /*Launch angle w.r.t axes*/
  float lax,lay,laz;
  
  
  /*Force components*/
      /*Wind*/
      float wind_x,wind_y,wind_z;
      
           /* Wind velocity components*/
	   float wVel_x,wVel_y,wVel_z;
      /*Air resistance*/
      float ar_x,ar_y,ar_z;
  
  /*Environmental parameters*/
  float cd,area,density,gravity,k;
  
  /*Simulation limits*/
  float y_base;
  int i;
  int motion;
  
public:
  Ball()
  {
    i=1;
    y_base=1.0;
    y=y_base+0.1;
    x=z=0;
    vx=vy=vz=0;
    ax=ay=az=0;
    wind_x=wind_y=wind_z=0;
    ar_x=ar_y=ar_z=0;
    
    mass=0.2;
    radius=0.1;
    area= 4.0 * PI * radius * radius * 0.5; //0.5 bcoz only one half faces moving air
    cd=0.3; //for golf ball
    density=1.225; //for air
    gravity=EARTH_GRAVITY * -1;	//Initially g decellerates the y motion
    motion=UPWARD;
    k=0.2;
  }
  
  int move()	/*Runs the main simulation logic; called once for every frame*/
  {
    //cout<<"\n\nFrame "<<i<<endl<<mass<<" "<<radius<<" "<<area<<" "<<cd<<" "<<density<<" "<<gravity<<" "<<endl;
    i++;
    /*********** FORCES *************/
    /*Find air resistance components*/
    ar_x=0.5*density*cd*area* vx*vx * -1;
    ar_y=0.5*density*cd*area* vy*vy * -1;
    ar_z=0.5*density*cd*area* vz*vz * -1;
    //cout<<"AR: "<<setprecision(3)<<ar_x<<"\t"<<ar_y<<"\t"<<ar_z<<"\t";
    //printf("%2f\t%2f\t%2f\t",ar_x,ar_y,ar_z);
    
    /*Wind components*/			
    wind_x=0.5*density*cd*area* wVel_x*wVel_x;		//Increases the velocity along the respective axis
    wind_y=0.5*density*cd*area* wVel_y*wVel_y;
    wind_z=0.5*density*cd*area* wVel_z*wVel_z;
    //cout<<"w: "<<setprecision(3)<<wind_x<<"\t"<<wind_y<<"\t"<<wind_z<<"\t";
    
    /********** Accelerations **********/
    ax=(ar_x + wind_x)/mass;   
    ay=(ar_y + wind_y)/mass+gravity;
    az=(ar_z + wind_z)/mass;
    //cout<<"Ac: "<<setprecision(3)<<ax<<"\t"<<ay<<"\t"<<ay<<"\t";
    //cout<<"Vel: "<<setprecision(3)<<vx<<"\t"<<vy<<"\t"<<vz<<"\t";
    
    /********** Ball position **********/
    x = x + vx * FRAME_DURATION;
    
    float temp;
    if((temp=y + vy * FRAME_DURATION) > y_base)
       y = temp;
    else
    {
       y = y_base;
       cout<<"boo";
       //return 0;       		//Actually ball should bounce. Remove this for bounce to occur.
       vy = -(k * vy);		// Multiplying by restitution factor and negating vy
    }
    
    z = z + vz * FRAME_DURATION;
      
    //cout<<"pos: "<<x<<"\t"<<y<<"\t"<<z;
    cout<<setprecision(3)<<x<<"\t"<<y<<"\t"<<z;
	//float height=getmaxy(); 
	
	if(trial==0)   
		putpixel(10*x,(height-10*y),WHITE);
	/*else if(trial==1)
		putpixel(10*x,(height-10*y),RED);
	else if(trial==2)
		putpixel(10*x,(height-10*y),BLUE);
	else if(trial==3)
		putpixel(10*x,(height-10*y),GREEN);	*/

	delay(7);
    /********** Prepare for next frame ********/
    vx = vx + ax * FRAME_DURATION;
    vy = vy + ay * FRAME_DURATION;
    vz = vz + az * FRAME_DURATION;
    if(vy<0.5&&motion==UPWARD)
    {  
      cout<<"down";
      vy=0.3;
      motion=DOWNWARD;
      //gravity = -gravity;
    }
    cout<<"\n";
    if(i==1000)
        return 0;
    return 1;
  }
  
  void setWind(float wx,float wy,float wz)
  {
    wVel_x=wx;
    wVel_y=wy;
    wVel_z=wz;
  }
  void setLaunchVelocity(float v,float theta_x,float theta_y, float theta_z)
  {
    
    /* Fs = |F| * cos(Θs), where s= x,y,z*/
    vx = v * cos(degreeToRadians(theta_x));
    vy = v * cos(degreeToRadians(theta_y));
    /*Set theta_z =90 for 2D simulation (only X and Y) */
    if(theta_z==90)
    {
      vz=0;
      return;
    }
    vz = v * cos(degreeToRadians(theta_z));
    
  }
  
  float degreeToRadians(float angle)
  {
      return (angle*PI/180.0);
  }
};

int main()
{
	
   cout<<FRAME_DURATION<<endl;
   Ball b1,b2,b3,b4,b5;
	float vel,thx,thy,thz;
	printf("enter the velocity : ");
	scanf("%f",&vel);
	printf("x-axis angle : ");
	scanf("%f",&thx);
	printf("y-axis angle : ");
	scanf("%f",&thy);
	printf("z-axis angle : ");
	scanf("%f",&thz);
	
        printf("Do you want to see the wind effect (NOTE : FIRST OBSERVE WITHOUT WIND AND RECORD THE ORIGINAL TRAJECTORY, THEN EXAMINE THE WIND EFFECTS\n\nIF YOU HAVE OBSERVED THE EFFECT WITHOUT WIND THEN PRESS 1 ,ELSE IF YOU ARE OBSERVING FOR THE FIRST TIME PRESS 2\n\n");
        int a,a1,a2;
        scanf("%d",&a);
	if(a==1)
	{
		printf("\nenter x and y components of wind velocity\n");
		scanf("%d %d",&a1,&a2);
 		a1=a1/3;
		a2=a2/3;
		b1.setWind(a1,a2,0);
	}
	        

  int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	//initwindow(1000,1000);
	//printf("x : %d y : %d ",getmaxx(),getmaxy());
	//exit(0);
	height=getmaxy();	
   
	
trial=0;
	b1.setLaunchVelocity(vel,thx,thy,thz);
   while(b1.move());

	/*trial=1;
	b2.setLaunchVelocity(85,30,60,90);
   while(b2.move());

	trial=2;
	b3.setLaunchVelocity(75,45,45,90);
   while(b3.move());

	trial=3;
	b4.setLaunchVelocity(65,60,30,90);
   while(b4.move());*/

   getch();
   getch(); 
   
   closegraph();
	
printf(".....................................carry : %f ........................",b1.x+185.29);	   
return 0;
   //cout<<"Finished"<<endl;
}
