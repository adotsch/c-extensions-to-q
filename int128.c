//
// Simple q binding for GCC's __int128, stored as guid.
//
// q) i128:(`int128 2:(`api;1))`
// q) i128.str i128.mul[i128.cast "42";i128.cast 0Wj]
//
// compile with
// gcc -shared -m64 -DKXVER=3 -O2 int128.c -o int128.so -fPIC
// or
// g++ -shared -m64 -DKXVER=3 -O2 int128.cpp -o int128.so -fPIC
// 

#include"k.h"
#ifdef __cplusplus
extern"C"{
#endif

#define yt y->t
#define kU_(x) (*(__int128*)kU(x))
#define ku_(v) ({__int128 _=(v);ku(*(U*)&_);})

K1(cast)
{
	__int128 v;
	switch(xt)
	{
		case -KB:
		case -KC:
		case -KG: v=x->g; break;
		case -KH: v=x->h; break;
		case -KM:
		case -KD:
		case -KI: v=x->i; break;
		case -KP:
		case -KN:
		case -KJ: v=x->j; break;
		case -KE: v=x->e; break;
		case -KZ:
		case -KF: v=x->f; break;
		case KC:
			v=0;I s=1,i=0;
			if(xn)
			{
				if(kC(x)[0]=='-'){s=-1;i++;};
				for(;i<xn;i++)
				{
					C d = kC(x)[i];
					if(('0'<=d)&&(d<='9'))
						v = v*10+(d-'0');
					else
						R krr("format");
				}
				v*=s;
			}
			else
				R krr("format");
		break;
		default:R krr("type");
	}
	R ku_(v);
}

K1(low) {if(xt+UU)R krr("type");R kj(kJ(x)[0]);}
K1(high){if(xt+UU)R krr("type");R kj(kJ(x)[1]);}
K2(add) {if((xt+UU)||(yt+UU))R krr("type");R ku_(kU_(x)+kU_(y));}
K2(sub) {if((xt+UU)||(yt+UU))R krr("type");R ku_(kU_(x)-kU_(y));}
K2(mul) {if((xt+UU)||(yt+UU))R krr("type");R ku_(kU_(x)*kU_(y));}
K2(div) {if((xt+UU)||(yt+UU))R krr("type");R ku_(kU_(x)/kU_(y));}
K2(mod) {if((xt+UU)||(yt+UU))R krr("type");R ku_(kU_(x)%kU_(y));}

K1(str)
{
	if(xt+UU)R krr("type");
	C d[100],s='+';I i=0,j=0;
	__int128 v = kU_(x);
	if(v<0){s='-';v=-v;};
	while(v>0){d[i++]=(C)(((I)'0')+v%10);v=v/10;};
	K r=ktn(KC,(s=='-')+(i?i:1));
	kC(r)[0]='0';
	if(s=='-')kC(r)[j++]='-';
	while(i)kC(r)[j++]=d[--i];
	R r;
}

K1(api)
{
	K n = ktn(KS,9);
	kS(n)[0]=ss("cast");
	kS(n)[1]=ss("low");
	kS(n)[2]=ss("high");
	kS(n)[3]=ss("add");
	kS(n)[4]=ss("sub");
	kS(n)[5]=ss("mul");
	kS(n)[6]=ss("div");
	kS(n)[7]=ss("mod");
	kS(n)[8]=ss("str");
	R xD(n,knk(9,
		dl(cast,1),
		dl(low,1),
		dl(high,1),
		dl(add,2),
		dl(sub,2),
		dl(mul,2),
		dl(div,2),
		dl(mod,2),
		dl(str,1)
	));
}

#ifdef __cplusplus
}
#endif