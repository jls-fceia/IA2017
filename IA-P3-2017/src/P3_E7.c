/*
 * P3_E7.c
 *
 *  Created on: 10 abr. 2017
 *      Author: jose
 */
#include "P3.h"

typedef union byte{
	short int si;
	unsigned char bytes[2];
} Bytes;

void E7_main()
{
	char buffer[17];
	short int intCor = 29813; // Entero corto 16 bits.
	Bytes b;
	int i;

	itoa(intCor,buffer,16);
	printf("%s\n",buffer);
	itoa(intCor,buffer,2);
	printf("%s\n",buffer);

	b.si=intCor;
	printf("La direccion de la union es: %p\n",&b);
	for(i=0;i<2;i++){
		printf("Byte %d: %x\n",i,b.bytes[i]);
		printf("Offset of 'bytes[%d] is %u\n", i, offsetof( Bytes, bytes[i]));
	}
	return;
}


