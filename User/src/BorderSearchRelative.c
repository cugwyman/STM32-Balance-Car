#include "BorderSearchRelative.h"
#include "PatternMatch.h"
#include "ImgProc.h"
#include "gpio.h"
char ring,leftring,rightring,middlering;
int dxwidth[IMG_ROW],right[IMG_ROW];
//��������Ҳ����� ��һ���ѵ��İ�������Ϊ��߽� ���Դ��м����������� �ɺ�������Ϊ�ұ߽�
void Bordersearch(int16_t row){
static int i,j;
//	for(i=IMG_ROW;i>=0;i--)//����һ��ͼ�еĹ������
//	for(j=0;j<=IMG_COL;j++)
//	{
//		
//		if(IsBlack(i,j)&&IsWhite(i+1,j)&&IsWhite(i-1,j)&&IsWhite(i,j+1)&&IsWhite(i,j-1)){
//		       
//			   IsBlack(i,j)=IsWhite(i,j);
//		}
//	}
	//��һ������������
//		for(j=0;j<=IMG_COL;j++){
//    if(imgBuf[row][j]&&!imgBuf[row][j+1]){
//      resultSet.leftBorder[row] = j;
//	   	break ;}
//		}
//			
//    for(i=resultSet.leftBorder[row];i<=IMG_COL;i++) {
//			  if(imgBuf[row][i]&&!imgBuf[row][i+1]){
//				  resultSet.rightBorder[row] = j;
//					break;
//				}
// }            
//     
   
  //�������м�����
	for(j=50;j<=IMG_COL-50;j++){
    if(imgBuf[row][j]&&!imgBuf[row][j+1]){
      resultSet.leftBorder[row] = j;
		   break ;}
	}
   for(i=224-50;i>50;i--) {
			  if(imgBuf[row][i]&&!imgBuf[row][i-1]){
				  resultSet.rightBorder[row] = i-1;
					break;
     }
	 }            
      
	resultSet.middleLine[row] = (resultSet.leftBorder[row] + resultSet.rightBorder[row]) / 2;//��������
	dxwidth[row]=(resultSet.rightBorder[row] + resultSet.leftBorder[row]);
} 
  
//bool isring(){  //not fix
//    static int16_t i;
//    int16_t toggleCnt = 0;
//    int16_t patternRowCnt = 0;
//    for(i= 0; i < 10 ; i++) {
//        for(int16_t j = IMG_COL / 2; j >= 0; --j) {
//			if((dxwidth[i+1]-dxwidth[i])>10&&(dxwidth[i+2]-dxwidth[i])>12&&(dxwidth[i+3]-dxwidth[i+1])>14){
//                if(TstImgBufAsBitMap(i, j) != TstImgBufAsBitMap(i, j+1)) {  
//                                ++toggleCnt;
//                    if(toggleCnt > 3) {
//                        toggleCnt = 0;
//                        ++patternRowCnt;
//                        if(patternRowCnt > 6) 
//                            return true;
//                        else
//                            break;
//                    }
//                }
//			}
//        }
//    }
//    return false;
//}

//char whichring(int16_t row){
//    if(isring()){
//		if((dxwidth[row]/2-resultSet.middleLine[row])<0){
//		    return ring=leftring;
//		}
//        else if((dxwidth[row]/2-resultSet.middleLine[row])>0){
//		    return ring=rightring;
//		}
//        else 
//            return ring=middlering;
//    }
//		else 
//            return ring=0;
//}






