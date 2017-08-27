

//////////////////
#define inchmove 300
#define threshold 600
#define kp 12
#define kd 0
#define ki 0
//constants
//* MOTORS *//////////////////////////////////////////////////////////////////////////////////////////////////////
//QTRSensorsAnalog sen((unsigned char[]){0,1,2,3,4,5});
int a[]={6,5,9,10};
int maxs =200;
int avgSpeed = 150;
int mins =0;
int  pwdavg =200;
////////*CONTROL*///////////////////////////////////////////////////////////////////////////////////////////////////
long error=0;
float lineDis=0;
int prevError=0;
int setWal=0;
boolean printv=0;

////////*SENSORS*/////////////////////////////////////////////////////////////////////////////////////////////////////
////////there are 6 SENSORS////////////////////////////////////
//distance between sensors in millimeters from the middle
float sensor[]={0,1,2,3,4,5};
int senVal[6];//receive sensor values
int normaliseVal[6];
int maxVal[]={600,600,600,600,550,700};
int minVal[]={65,63,66,63,59,367}; 
int digitalVal[6];
long q=0;
long setPos=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0;i<4;i++)
  pinMode(a[i],OUTPUT);
  for(int i=0;i<6;i++)
  pinMode(sensor[i],INPUT);

}

void loop()
{
receive();
calculateError();
printVal();
pid();
//if(digitalVal[0]==1&&digitalVal[2]==1)
//{
//  inch();
//  receive();
//  if(q==0){
//  extremeleft();
//delay(4500);
//}
//}
//else pid();}
}
/////////motion functions///
////////***********************/// TOTAL 8 MOTION FUNCTIONS
void inch()
{
   forward();
  delay(inchmove);
 
  //brake();
   //milliinch();
 // delay(100);
  receive();
}
void milliinch()
{
 pid();
 delay(250); 
}
void forward()
{
  analogWrite(a[0],mins);
analogWrite(a[1],maxs);
  analogWrite(a[2],mins);
  analogWrite(a[3],maxs);
}
void stopp()
{
  analogWrite(a[0],mins);
analogWrite(a[1],mins);
  analogWrite(a[2],mins);
  analogWrite(a[3],mins);
}
void brake()
{
  analogWrite(a[0],maxs);
analogWrite(a[1],mins);
  analogWrite(a[2],maxs);
  analogWrite(a[3],mins);
}
void extremeleft()
{
  analogWrite(a[0],mins);
analogWrite(a[1],maxs);
  analogWrite(a[2],maxs);
  analogWrite(a[3],mins);
}
void left()
{
  analogWrite(a[0],mins);
analogWrite(a[1],maxs);
  analogWrite(a[2],mins);
  analogWrite(a[3],mins);
}
void extremeright()
{
  analogWrite(a[0],maxs);
analogWrite(a[1],mins);
  analogWrite(a[2],mins);
  analogWrite(a[3],maxs);
}
void right()
{
  analogWrite(a[0],mins);
analogWrite(a[1],mins);
  analogWrite(a[2],mins);
  analogWrite(a[3],maxs);
}
void pwdright()
{
  analogWrite(a[0],mins);
analogWrite(a[1],pwdavg);
  analogWrite(a[2],mins);
  analogWrite(a[3],maxs);
}
void pwdleft()
{
  analogWrite(a[0],mins);
analogWrite(a[1],maxs);
  analogWrite(a[2],mins);
  analogWrite(a[3],pwdavg);
}
/////////////sensor functions///////////////////////
///* 6 SENSORS //////
void receive()
{
  for(int i=0;i<6;i++){
  senVal[i]=analogRead(sensor[i]);
  normaliseVal[i]= map(senVal[i],maxVal[i],minVal[i],1023,0);
  if(normaliseVal[i]>threshold)
    digitalVal[i]=1;
  else digitalVal[i]=0;
}
//q= ((100000*digitalVal[0])+(10000*digitalVal[1])+(1000*digitalVal[2])+(100*digitalVal[3])+(10*digitalVal[4])+(1*digitalVal[5]));
// if(q==1)
// setPos=5;
//  if(q==11)
// setPos=4;
// if(q==10)
// setPos=3;
// if(q==110)
// setPos=2;
//  if(q==100)
//setPos=1;
//  if(q==1100)
//setPos=0;
//  if(q==1000)
// setPos=-1;
//  if(q==11000)
// setPos=-2;
//  if(q==10000)
// setPos=-3;
// if(q==110000)
// setPos=-4;
//  if(q==100000)
// setPos=-5;
//Serial.print(q);
//Serial.print(',');
}
void calculateError()
{
float num = (-150*(senVal[0]-senVal[5]))+(-91.44*(senVal[1]-senVal[4]))+(-30.48*(senVal[2]-senVal[3]));
 float den = (senVal[0]+senVal[1]+senVal[2]+senVal[3]+senVal[4]+senVal[5]);
lineDis = int((num/den))+2;
 error=-lineDis ;
  Serial.println(lineDis);
 


}
void pid()
{
 // calculateError();
  int  rateofchange= error-prevError;
  int integral=integral + error;
  int correct = (kp*error+ki*integral+kd*prevError);
  prevError= error;
  
 // Serial.print(correct);
  int rightMotor= (avgSpeed+correct);
  if(rightMotor>maxs)
  rightMotor=maxs;  
  int leftMotor =(avgSpeed-correct);
  if(leftMotor>maxs)
  leftMotor=maxs;
  int CRM= rightMotor;
  int CLM = leftMotor;
  if(printv)
  {
 Serial.print(",");
  Serial.print(error);
   Serial.print(",");
  Serial.print(CRM);
  Serial.print(",");
  Serial.print(CLM);
  Serial.println(",");
  }
  analogWrite(a[0],mins);
  analogWrite(a[1],CRM);
  analogWrite(a[2],mins);
  analogWrite(a[3],CLM);
   
}



void printVal()
{
  for(int i=0;i<6;i++)
  {
  Serial.print(senVal[i]);
  Serial.print(",");
  //Serial.print(digitalVal[i]);
  //Serial.print(",");
  }
 Serial.println();
}



