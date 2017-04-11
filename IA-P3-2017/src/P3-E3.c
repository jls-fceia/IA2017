/*
 * P3-E3.c
 *
 *  Created on: 10 abr. 2017
 *      Author: jose
 */
//https://www3.cs.stonybrook.edu/~skiena/392/programs/bignum.c
//http://www.dcc.fc.up.pt/~pribeiro/estagio2008/usaco/4_3_Big_Numbers.htm

#include "P3.h"

#define PLUS	1		/* positive sign bit */
#define MINUS	-1		/* negative sign bit */

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

typedef struct {
	char sign;
	unsigned char num_bytes;
	unsigned char * bytes;
} APint;

void initbignum(APint * i1, char s,unsigned char n){
	i1=(APint*)malloc(sizeof(APint));
	i1->sign=s;
	i1->bytes=(unsigned char*)calloc(n,sizeof(unsigned char));
}

void zero_justify(APint  *n) {
	unsigned char lastdigit;
	lastdigit= (8*n->num_bytes)-1;

	while ((lastdigit > 0) && (n->bytes[lastdigit] == 0))
		lastdigit --;

	if ((lastdigit == 0) && (n->bytes[0] == 0))
		n->sign = PLUS;	/* hack to avoid -0 */
}

//cual es mayor
int compare_bignum(APint  *a, APint *b)
{
	int i;				/* counter */
	unsigned char lda,ldb;

	lda=(8*a->num_bytes)-1;
	ldb=(8*b->num_bytes)-1;

	if ((a->sign == MINUS) && (b->sign == PLUS))
		return(PLUS);
	if ((a->sign == PLUS) && (b->sign == MINUS))
		return(MINUS);

	//si signo de a es + y signo de b es + o
	//si signo de a es – y signo de b  es –
	//o sea tienen signos iguales
	if (ldb > lda)
		return (PLUS * a->sign);
	if (lda > ldb)
		return (MINUS * a->sign);
	for (i = lda; i>=0; i--) {
		if (a->bytes[i] > b->bytes[i])
			return(MINUS * a->sign);
		if (b->bytes[i] > a->bytes[i])
			return(PLUS * a->sign);
	}

	return(0);
}
APint * suma_APint( APint * a, APint * b);//adelanto declaración
APint * resta_APint(APint *a, APint *b)
{
	unsigned char borrow;			/* has anything been borrowed? */
	unsigned char v;				/* placeholder digit */
	unsigned char i;				/* counter */
	unsigned char lastdigit,lda,ldb;/* index of high-order digit */
	APint *c;
	if ((a->sign == MINUS) || (b->sign == MINUS)) {
		b->sign = -1 * b->sign;
		c=suma_APint(a,b);
		b->sign = -1 * b->sign;
		return c;
	}
	//a y b son nros positivos
	if (compare_bignum(a,b) == PLUS) {//si b >a, resto y cambio el signo a la resta
		c=resta_APint(b,a);
		c->sign = MINUS;
		return c;
	}
	//a y b>0 y a>=b
	lda=(8*a->num_bytes)-1;
	ldb=(8*b->num_bytes)-1;
	lastdigit = max(lda,ldb);
	borrow = 0;//lo que “pido”
	if(c->sign!=MINUS)
		c->sign=PLUS;
	initbignum(c,c->sign,lastdigit+1);
	for (i=0; i<=(lastdigit); i++) {
		v = (a->bytes[i] - borrow - b->bytes[i]);
		if (a->bytes[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}
		c->bytes[i] = v % 10;
	}
	zero_justify(c);
}


APint * suma_APint( APint * a, APint * b)
{
	unsigned char carry;			/* carry digit */
	int i;				/* counter */
	unsigned char lastdigit,lda,ldb;/* index of high-order digit */
	char signo;
	APint *c;
	if(a->sign==b->sign)//no tengo en cuenta el cero con signo 0, sino poner un OR, supongo que el otro tiene signo +
		signo=a->sign;
	else{
		if (a->sign == MINUS) {
			a->sign = PLUS;
			c= resta_APint(b,a);
			a->sign = MINUS;
		} else {
			b->sign = PLUS;
			c= resta_APint (a,b);
			b->sign = MINUS;
		}
		return c;
	}
	lda=(8*a->num_bytes)-1;
	ldb=(8*b->num_bytes)-1;
	lastdigit=max(lda,ldb)+1;
	initbignum(c,signo,lastdigit+1);
	carry = 0;
	for(i=0;i<=lastdigit;i++){
		c->bytes[i]=(carry+a->bytes[i]+c->bytes[i])%10;
		carry=(carry+a->bytes[i]+c->bytes[i])/10;
	}

	return c;
}

void E3_main(){

}


