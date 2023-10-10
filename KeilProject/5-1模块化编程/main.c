#include <REGX52.H>
#include "Delay1.h"
#include "Nixie.h"
/*
"" 这个文件是在自己的写的文件中寻找，但是<>这是在系统的安装目录中寻找
*/
void main()
{
   while(1)
	 {
		 Nixie(1,1);
		 Nixie(2,2);
		 Nixie(3,3);
	 }
}
