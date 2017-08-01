#ifndef _IMGPROC_H
#define _IMGPROC_H

#include "root.h"

void ImgProcInit(void);

#ifdef USE_BMP
void SetImgBufAsBitMap(int16_t row, int16_t col);
void ClrImgBufAsBitMap(int16_t row, int16_t col);
bool TstImgBufAsBitMap(int16_t row, int16_t col);
extern byte imgBuf[IMG_ROW][1 + IMG_COL / 8];
#else
#define TstImgBufAsBitMap(row, col) (imgBuf[row][col])
extern byte imgBuf[IMG_ROW][IMG_COL];
#endif

#define IsWhite(row, col) (!TstImgBufAsBitMap(row, col))
#define IsBlack(row, col) (TstImgBufAsBitMap(row, col))

extern int16_t dirError;
extern bool direction_control_on;
extern img_proc_struct resultSet;
extern bool onRamp;
extern int32_t rampDistance;

#endif
