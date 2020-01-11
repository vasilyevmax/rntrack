/*
 *  Suppress warning about unused parameter.  Written by Paul Edwards and
 *  released to the public domain.  Modified by Andrew Clarke.
 */

#ifndef unused
#if defined(PACIFIC)
#define unused(x) while(0){if(x){};}
#elif defined(__HIGHC__) || defined(__WATCOMC__)
#define unused(x) ((x) = (x))
#else
#define unused(x) ((void)(x))
#endif
#endif
