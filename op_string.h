
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unixcube/op_types.h>
#include <unixcube/op_fio.h>



static const char* apnd_cmd = " > ./cmd.out.put";
static unsigned int apnd_szlen;

_ul countch(_c* s0, _c ch);
_c* str2splice(_c* s0, _c* s1, _c delim);
_c* cmdxsplice(_i vN, _c** szV, _c delim);
_c* strxsplice_endi(_i vN, _c** szV, _c delim);
_c* strchain(_i argc, _c** argv);
_c* scatlines(_c* s0, _c excl);
_c* scatlines2(_c* s0, _c* s1);
_c* srepllines(_c* s0, _c excl, _c repl);


_ul countch(_c* s0, _c ch)
{
  _ul lin;
  _c* sP = s0;
  for(lin=0, sP=s0; *sP; ++sP){
    if(*sP == ch)
      lin++;
  }
  return(lin);
}

_c* str2splice(_c* s0, _c* s1, _c delim)
{
    _ul i0, i1;
    _ul dmlen = (delim)?1:0;
    _ul s0len = strlen((_cc*)s0);
    _ul s1len = strlen((_cc*)s1);
    _ul sXlen = ((s0len + s1len )+ dmlen) + 1;

    _c* sz = (_c*)malloc((sizeof(_c*) * sXlen) );

    for(i0=0; i0 <= s0len-1; ++i0){ sz[i0] = s0[i0]; }

    if(delim)
        sz[i0++] = delim;

    for(i1=0; i1 <= s1len-1; ++i0, ++i1){ sz[i0] = s1[i1]; }
    sz[i0++] = '\0';

    return(sz);
}

_c* cmdxsplice(_i vN, _c** szV, _c delim)
{
    _ul i0, i1;
    _c* szX = 0;
    //_c* szT = str2splice(szV[0], szV[1], delim);
    _c* szT = str2splice(szV[1], szV[2], delim);
    for(i0=3; i0 <= vN-1; ++i0){
       // szX = str2splice(szV[i0], szT, delim);
        szX = str2splice(szT, szV[i0], delim);
        free(szT);
        szT = szX;
    }
    return(szX);
}

_c* strxsplice_endi(_i vN, _c** szV, _c delim)
{
    _ul i0, i1;
    _c* szX = 0;
    //_c* szT = str2splice(szV[0], szV[1], delim);
    _c* szT = str2splice(szV[1], szV[0], delim);
    for(i0=2; i0 <= vN-1; ++i0){
        szX = str2splice(szV[i0], szT, delim);
       // szX = str2splice(szT, szV[i0], delim);
        free(szT);
        szT = szX;
    }
    return(szX);
}


_c* strchain(_i argc, _c** argv)
{
    _i szc = argc-1;
    _c delm = argv[argc-1][0] != '0'? argv[argc-1][0]: 0;
    if(delm == 'S')
        delm = ' ';
    if(delm == '0')
        delm = 0;
    if(delm == 'N')
        delm = '\n';
    
    _c* r = cmdxsplice(szc, argv, delm);
    //_c* r_lendi = strxsplice_endi(argc, argv, delm);
    //printf("%s\n", r);
    //printf("%s\n\n", r_lendi);
    return(r);
    //free(r_lendi);
}

_c* scatlines(_c* s0, _c excl)
{
  _ul i0;
  _ul n_excl = countch(s0, excl);
  _ul szlen = (_ul)( ( sizeof(_c)*(strlen((_cc*)s0) ) - n_excl) + 1);
  _c* szr = (_c*)malloc( sizeof(_c) * szlen );
  _c* sX = szr;
  _c* sP = s0;
  
  memset(szr, 0, szlen);
  
  for(i0=0; *sP; ++sP){
    if( *sP != excl ){
      *sX = *sP;
      sX++;
    }
  }
  return(szr);  
}

_c* scatlines2(_c* s0, _c* s1)
{
  _c* sP = 0;
  _ul i0, i1, i2;
  _ul s0len = strlen( (_cc*) s0);
  _ul s1len = strlen( (_cc*) s1);
  _ul veclen = ( s0len + s1len ) - 
    (countch( s0, '\n' ) + countch( s1, '\n' ) );
  
  _c* r = (_c*)malloc( ( sizeof(_c) * ( veclen ) ) + 1 );
  
  for(i0 = 0, sP=s0; *sP; ++sP)
    { if(*sP != '\n') { r[ i0 ] = *sP; i0++; } }
  
  for(i1 = i0, sP=s1; *sP; ++sP)
    { if(*sP != '\n') { r[ i1 ] = *sP; i1++; } }
    
  r[i1++] = '\0';
  
  return(r);
}

_c* srepllines(_c* s0, _c excl, _c repl)
{
  _ul i0;
  _ul n_excl = countch(s0, excl);
  _ul szlen = (_ul)( ( sizeof(_c)*(strlen((_cc*)s0) ) - n_excl) + 1);
  _c* szr = (_c*)malloc( sizeof(_c) * szlen );
  _c* sX = szr;
  _c* sP = s0;
  
  memset(szr, 0, szlen);
  
  for(i0=0; *sP; ++sP){
    if( *sP != excl )
      *sX = *sP;
    else
      *sX = repl;
    
    sX++;
  }
  return(szr);
  
}


_ul getbufsize_allfiles(_c** flist, _ul fcount, _ul fstart, _c excl)
block_
  _ul i0;
  _c* sz0;
  _ul r=0;
  for(i0=fstart; i0 <= fcount; ++i0) block_
    sz0= fget_data(flist _a(i0) );
    r += ( ( sizeof(_c)*(strlen((_cc*)sz0) ) - countch(sz0, excl)) + 1);
    free(sz0);
  _block
  rt(r);
_block

_ul scat(_i argc, _c** argv)
block_

  _ul i0, i1, i2;
  _c* sz0, szX;

  for(i0=1; i0 <= argc-1; ++i0){
    sz0= fget_data(argv[i0]);
  
    printf("%s", scatlines(sz0, '\n') );
       
    free(sz0);
  }
  printf("\n");
  return(0);
_block

//--------___--___--___--__---__---_----__--_EndOfFile----