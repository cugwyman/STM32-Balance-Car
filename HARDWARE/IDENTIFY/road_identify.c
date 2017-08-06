#include "EXTI.h"
#include "road_identify.h"

int ph;
int dxwidth[row];
float error_sum;
int ring;//ring 0´ú±í²»ÊÇÔ²£¬1´ú±íÊÇÖĞ¼äÔ²£¬2´ú±íÊÇÖÜ±ßÔ²  3´ú±í×óÖÜ±ßÔ²  4´ú±íÓÒÖÜ±ßÔ²
//****************************************************************************
//  º¯ÊıÃû£SSearchborder(uint8_t n) 
//  ¹¦ÄÜ£ºËÑÑ°×óÓÒ±ß½ç  ²¢¼ÆËãÖĞÏß
//  ËµÃ÷£º´ÓÁ½±ßÏòÖĞ¼äËÑÏß
//*****************************************************************************/ 

void Searchborder(uint8_t n) {
	
static uint8_t j,x,b,c,y,l;
	left[n]=0;
	right[n]=0;
	dxwidth[n]=0;
//	//¶ÔÒ»·ù¹ÂÁ¢µÄºÚµã½øĞĞ¹ıÂË
//	for(j=0;j<=line;j++)
//		for(x=row;x>=0;x--){
//		
//		if(!image[n][x]&&image[n-1][x]&&image[n+1][x]&&image[n][x-1]&&image[n][x+1]){
//		
//		  image[n][x]=!image[n][x];
//		}
//		}
//		//´ÓÒ»±ß¿ªÊ¼ËÑ±ß½ç
//  for(int y=0;y<=line;y++){
//	 if(image[n][y]){
//	   b=y;
//		 break;
//	 }
//	}
//	for(j=b;j<=line;j++){
//	if(image[n][j]&&!image[n][j+1]){
//		left[n]=j+1;
//		break;
//	  }
//	}
//	for(x=left[n];x<=line;x++){
//	 if(!image[n][x]&&image[n][x+1]){
//	 right[n]=x;
//		 break;
//	 }
//	}

	for( y=0;y<=line;y++){
	 if(image[n][y]){
	   b=y;
		 break;
	 }
	}
  for( l=line;l>0;l--){
	 if(image[n][l]){
	   c=l;
		 break;
	 }
	}
	
	for(j=b;j<=line;j++){
	if(image[n][j]&&!image[n][j+1]){
		left[n]=j+1;
		break;
	}
	}
	for(x=c;j>0;x--){
		if(image[n][x]&&!image[n][x-1]){
			right[n]=x-1;
			break;
			}
	}
	bottom[n]=(left[n]+right[n])/2;
	dxwidth[n]=right[n]-left[n];

}
	


//	//ÅĞ¶ÏÊÇ²»ÊÇÖĞ¼äµÄÔ²
//void ismiddlering(){
//static int i;
//for(i=0;i<=row;i++)
//	{
//	  if((dxwidth[i+1]-dxwidth[i])>10&&(dxwidth[i+2]-dxwidth[i])>12&&(dxwidth[i+3]-dxwidth[i+1])>14){
//	    ring=1;	
//		}
//		else ring=0;
//	}
//}

////ÅĞ¶ÏÊÇ²»ÊÇµ¥ÏßÒÔÍâµÄÔ²²
//void isarroudring(uint8_t n){
//static int i=0;
//	int a=0,cnt;
//	for(n=0;n<=15;n++)
//		for (i=0;i<line;i++){
//			if(image[n][i]==!image[n][i+1]){
//				a++;
//				if(a>3){
//				a=0;
//				cnt++;
//					if(cnt>=7){
//					ring=2;
//					cnt=0;
//					}
//			}
//		}
//			else ring=0;
//	}
//	
//}

//void  jugewhichring(uint8_t n){
//	static int i=0,j=0;int ringl[row],ringr[row];
//	int ringwidth[row];
//   if(ring==2){
//	   for(n=0;n<=15;n++)
//				for (i=0;i<line;i++){
//				if(image[n][i]&&!image[n][i+1]){
//				    ringl[n]=i+1;
//				    for(j=ringl[n];j<line;j++){
//							if(!image[n][j]&&image[n][j+1]){
//				       ringr[n]=i+1;
//				 }
//			 }
//		 }
//				ringwidth[n]=ringr[n]-ringl[n]/2;
//		   if(ringwidth[n]-bottom[n]<-0){
//				  ring=3;}
//			 else if (ringwidth[n]-bottom[n]>0){
//				 ring=4;}
//			 else ring=0;
//	  }
// }
//}



////ÇóÇ°Õ°ÉÏÏÂÁùĞĞÓëÖĞÏßµÄÆ«²î
//void  ErrorGet(){
//  error_sum=(6*standard-bottom[ph+3]-bottom[ph+2]-bottom[ph+1]-bottom[ph]-bottom[ph-1]-bottom[ph-2]-bottom[ph-3])/6.0;

//}



