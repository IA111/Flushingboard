#ifndef __NIXIE_H__
#define __NIXIE_H__

//上面是固定的模板
//这个时候还需要进行声明需要引用的函数名
void Nixie_Scan(unsigned int Location,unsigned char Number);
 void Nixie_Loop(void);
 void Nixie_SetBuf(unsigned char Location,Number);
 #endif