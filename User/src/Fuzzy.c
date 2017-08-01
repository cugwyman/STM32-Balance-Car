#include "Fuzzy.h"
#include "math.h" 

/*
 *  Finally, not used
*/

/*量化因子要根据经验确定一个大致的值*/
/*调整ke,kec相当于kp,kd.至于ku的整定则可以和速度相关联*/
//float Ke=20.0;
//float Kec=0.2;
//float Ku=3.0;
float reFuzzy;
/*输入量P语言值特征点*/ 
int PFF[4]={0,2,4,6};//??????????????
/*输入量D语言值特征点*/ 
int DFF[4]={0,2,4,6};//????????????????
/*输入量U语言值特征点*/
int UFF[7]={0,2,4,6,8,10,12};//0,2,4,6,8,10,12
 
/*根据效果和仿真来调整*/
int rule[7][7]={ 
//误差变化率 -3,-2,-1, 0, 1, 2, 3    // 误差    
            {-6,-6,-6,-5,-5,-5,-4,}, //  -3   
            {-5,-4,-4,-3,-2,-2,-1,}, //  -2 
            {-4,-3,-2,-1, 0, 1, 2,}, //  -1 
            {-4,-3,-1, 0, 1, 3, 4,}, //   0 
            {-2,-1, 0, 1, 2, 3, 4,}, //   1 
            { 1, 2, 2, 3, 4, 4, 5,}, //   2 
            { 4, 5, 5, 5, 6, 6, 6}}; //   3

/**********************************************************/
float   Fuzzy(float P,float D)   /*模糊运算引擎*/ 
{ 
    float  U;                   /*偏差，偏差微分以及输出值的精确量*/ 
    float  PF[2],DF[2],UF[4];   /*??,?????????????*/ 
    int    Pn,Dn,Un[4]; 
    float  temp1,temp2;       
    
    /*??????*/ 
    /*??PD?????????????*/ 
    if(P>-PFF[3] && P<PFF[3])
    { 
        if(P<=-PFF[2])     
        {
        Pn=-2;
        PF[0]=(float)((-PFF[2]-P)/(PFF[3]-PFF[2]));
        } 
        else if(P<=-PFF[1])   
        {
            Pn=-1;
            PF[0]=(float)((-PFF[1]-P)/(PFF[2]-PFF[1]));
        } 
        else if(P<=PFF[0])   
        {
            Pn=0;
            PF[0]=(float)((-PFF[0]-P)/(PFF[1]-PFF[0]));
        } 
        else if(P<=PFF[1])   
        {
            Pn=1; PF[0]=(float)((PFF[1]-P)/(PFF[1]-PFF[0]));
        } 
        else if(P<=PFF[2]) 
        {
            Pn=2; PF[0]=(float)((PFF[2]-P)/(PFF[2]-PFF[1]));
        } 
        else if(P<=PFF[3])   
        {
            Pn=3; PF[0]=(float)((PFF[3]-P)/(PFF[3]-PFF[2]));
        }                  
    } 
    else if(P<=-PFF[3])   
    {
        Pn=-2;   PF[0]=1;
    } 
    else if(P>=PFF[3])   
    {
        Pn=3;   PF[0]=0;
    } 
    PF[1]=1-PF[0];  
    
    
    if(D>-DFF[3] && D<DFF[3])
    { 
        if(D<=-DFF[2])     
        {
            Dn=-2;DF[0]=(float)((-DFF[2]-D)/(DFF[3]-DFF[2]));
        } 
        else if(D<=-DFF[1])   
        {
            Dn=-1;
            DF[0]=(float)((-DFF[1]-D)/(DFF[2]-DFF[1]));
        } 
        else if(D<=DFF[0])   
        {
            Dn=0; 
            DF[0]=(float)((-DFF[0]-D)/(DFF[1]-DFF[0]));
        } 
        else if(D<=DFF[1])   
        {
            Dn=1;
            DF[0]=(float)((DFF[1]-D)/(DFF[1]-DFF[0]));
        } 
        else if(D<=DFF[2])   
        {
            Dn=2; DF[0]=(float)((DFF[2]-D)/(DFF[2]-DFF[1]));
        } 
        else if(D<=DFF[3])   
        {
            Dn=3; DF[0]=(float)((DFF[3]-D)/(DFF[3]-DFF[2]));
        }   
    } 
    else if(D<=-DFF[3])   
    {
        Dn=-2; 
        DF[0]=1;
    } 
    else if(D>=DFF[3])   
    {
        Dn=3;
        DF[0]=0;
    } 
    DF[1]=1-DF[0];
    /*?????????????rule[7][7]*/ 
    /*?????13?????,????UFF[7]??*/ 
    /*??????????*/ 
    Un[0]=rule[Pn-1+3][Dn-1+3]; 
    Un[1]=rule[Pn+3][Dn-1+3]; 
    Un[2]=rule[Pn-1+3][Dn+3];   
    Un[3]=rule[Pn+3][Dn+3]; 
    if(PF[0]<=DF[0])
        UF[0]=PF[0];
    else 
        UF[0]=DF[0]; 
    if(PF[1]<=DF[0])
        UF[1]=PF[1];
    else 
        UF[1]=DF[0]; 
    if(PF[0]<=DF[1])
        UF[2]=PF[0]; 
    else 
        UF[2]=DF[1]; 
    if(PF[1]<=DF[1])
        UF[3]=PF[1]; 
    else 
        UF[3]=DF[1];
    /*????????????*/ 
    
    if(Un[0]==Un[1])
    {
        if(UF[0]>UF[1])
            UF[1]=0;
        else 
            UF[0]=0;
    } 
    if(Un[0]==Un[2])
    {
        if(UF[0]>UF[2])
            UF[2]=0;
        else 
            UF[0]=0;
    } 
    if(Un[0]==Un[3])
    {
        if(UF[0]>UF[3])
            UF[3]=0;
        else
            UF[0]=0;
    } 
    if(Un[1]==Un[2])
    {
        if(UF[1]>UF[2])
            UF[2]=0;
        else
            UF[1]=0;
    } 
    if(Un[1]==Un[3])
    {
        if(UF[1]>UF[3])
            UF[3]=0;
        else 
            UF[1]=0;
    } 
    if(Un[2]==Un[3])
    {
        if(UF[2]>UF[3])
            UF[3]=0;
        else 
            UF[2]=0;
    } 
    
    /*??????*/ 
    /*Un[]???????????,????????*/ 
    if(Un[0]>=0)
        Un[0]=UFF[Un[0]];
    else 
        Un[0]=-UFF[-Un[0]]; 
    if(Un[1]>=0)
        Un[1]=UFF[Un[1]];
    else 
        Un[1]=-UFF[-Un[1]]; 
    if(Un[2]>=0)
        Un[2]=UFF[Un[2]];
    else
        Un[2]=-UFF[-Un[2]]; 
    if(Un[3]>=0)
        Un[3]=UFF[Un[3]];
    else 
        Un[3]=-UFF[-Un[3]]; 
    
    temp1=UF[0]*Un[0]+UF[1]*Un[1]+UF[2]*Un[2]+UF[3]*Un[3]; 
    temp2=UF[0]+UF[1]+UF[2]+UF[3]; 
    U=temp1/temp2;
    return U; 
}



//int32_t FUZZY_pid(int E,int EC)
//{
////    return  Ku* MODE.VC_Set *(Fuzzy(Ke*MODE.VC_Set*E,Kec*EC));
//     reFuzzy = (Fuzzy(MODE.Ke*E,MODE.Kec*EC));
//    #ifdef DC
//    return  MODE.Ku* MODE.VC_Set * reFuzzy;
//    #endif

//}
