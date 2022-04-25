//
// Created by sunwise on 2021/9/16.
//

#include <stdlib.h>
unsigned int upload_data[3];
unsigned int g_v = 0;

unsigned int addrs1[2] = {
	0x0011,
	0xff00
};
unsigned int addrs2[2] = {
	0xff00,
	0xff01
};
void IOOutSet(unsigned int addr,unsigned int bit);
void IOOutClr(unsigned int addr,unsigned int bit);

void IOOutSet(unsigned int addr,unsigned int bit){
    unsigned int val = *((volatile unsigned int*)addr);
    val |= bit;
    *((volatile unsigned int*)addr) = val;
	for(int i=0;i<2;i++){
		upload_data[i] = g_v;
	}
}
void IOOutClr(unsigned int addr,unsigned int bit){
	unsigned int *endata = upload_data;
    unsigned int val = *((volatile unsigned int*)addr);
    val &= ~bit;
    *((volatile unsigned int*)addr) = val;
    g_v = endata[1];
}

int main()
{
	IOOutSet(addrs1[1],2);
}
void isr()
{
	IOOutClr(addrs2[0],4);
}

