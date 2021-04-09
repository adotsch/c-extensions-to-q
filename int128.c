//
// Simple q binding for GCC's __int128, stored as guid.
//
// q) i128:(`int128 2:(`api;1))`
// q) i128.str i128.mul[i128.parse "42";i128.cast 0Wj]
// q) i128.str (i128.mul/) i128.cast 1+til 33
// q) i128.str i128.parse 38#"9"
// q) i128.str i128.parse "-",38#"9"
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
#define kU_(x) ((__int128*)kU(x))
#define kU0(x) (*kU_(x))
#define ku_(v) ({__int128 _=(v);ku(*(U*)&_);})

K1(parse)
{
	if(!xt)R krr("nyi");
	if(xt-KC)R krr("type");
	__int128 v =0;I s=1,i=0;
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
		R ku_(v*s);
	}
	else
		R krr("format");
}

K case0(K x,K(*f)(K))
{
	K r=ktn(0,0);
	for(J i=0;i<xn;i++)
	{
		K ri = f(kK(x)[i]);
		if(ri->t==-128)
		{
			r0(r);r=ri;break;
		}
		jk(&r,ri);
	}
	R r;
}

K1(cast)
{
	__int128 v;
	switch(xt)
	{
		//atom
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
		
		case -UU: R r1(x); break;
		
		//vector
		case KB:
		case KC:
		case KG:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kG(x)[i];R r;}break;
		case KH:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kH(x)[i];R r;}break;
		case KM:
		case KD:
		case KI:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kI(x)[i];R r;}break;
		case KP:
		case KN:
		case KJ:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kJ(x)[i];R r;}break;
		case KE:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kE(x)[i];R r;}break;
		case KZ:
		case KF:{K r=ktn(UU,xn);for(J i=0;i<xn;i++)kU_(r)[i]=kF(x)[i];R r;}break;
		
		case UU: R r1(x); break;
		
		//list
		case 0: R case0(x,cast); break;
		
		default:R krr("type");
	}
	R ku_(v);
}

K1(low) 
{
	switch(xt)
	{
		case -UU: R kj(kJ(x)[0]);
		case  UU:{ K r = ktn(KJ,xn); for(J i=0;i<xn;i++)kJ(r)[i]=kJ(x)[2*i]; R r;}
		case   0: R case0(x,low);
		default : R krr("type");
	}
}
K1(high) 
{
	switch(xt)
	{
		case -UU: R kj(kJ(x)[1]);
		case  UU:{ K r = ktn(KJ,xn); for(J i=0;i<xn;i++)kJ(r)[i]=kJ(x)[2*i]; R r;}
		case   0: R case0(x,high);
		default : R krr("type");
	}
}

#define OP(fn,ctor,op) K2(fn) {if((xt+UU)||(yt+UU))R krr("type");R ctor(kU0(x) op kU0(y));}
OP(add,ku_,+)
OP(sub,ku_,-)
OP(mul,ku_,*)
OP(div,ku_,/)
OP(mod,ku_,%)
OP(lt ,kb ,<)

K str0(__int128 v)
{
	C d[100],s='0';I i=0,j=0;
	if(v<0){s='-';v=-v;j++;};while(v>0){d[i++]='0'+v%10;v=v/10;};
	K r=ktn(KC,(s=='-')+(i?i:1));kC(r)[0]=s;while(i)kC(r)[j++]=d[--i];
	R r;
}

K1(str)
{
	K r;
	switch(xt)
	{		
		case -UU: r=str0(kU0(x)); break;
		case  UU:
		{
			r=ktn(0,0);
			for(J i=0;i<xn;i++)
				jk(&r,str0(kU_(x)[i]));
		}
		break;
		case 0: r=case0(x,str); break;
		default:r=krr("type");
	}
	R r;
}

K1(api)
{
	K n = ktn(KS,11);
	kS(n)[ 0]=ss("cast");
	kS(n)[ 1]=ss("parse");
	kS(n)[ 2]=ss("low");
	kS(n)[ 3]=ss("high");
	kS(n)[ 4]=ss("add");
	kS(n)[ 5]=ss("sub");
	kS(n)[ 6]=ss("mul");
	kS(n)[ 7]=ss("div");
	kS(n)[ 8]=ss("mod");
	kS(n)[ 9]=ss("lt");
	kS(n)[10]=ss("str");
	R xD(n,knk(11,
		dl(cast,1),
		dl(parse,1),
		dl(low,1),
		dl(high,1),
		dl(add,2),
		dl(sub,2),
		dl(mul,2),
		dl(div,2),
		dl(mod,2),
		dl(lt,2),
		dl(str,1)
	));
}

#ifdef __cplusplus
}
#endif