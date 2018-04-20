

//#include "op_baseXZ.h"
#include <unixcube/op_types.h>
#include <unixcube/op_cbase.h>

static _ui n_digz;
static _uc convbuf[1024];

static _uc baseX_table[10] = {'0', '1', '2', '3', '4','5','6','7','8','9'};

static _uc baseX_table_61[] = {'0', '1', '2', '3', '4','5','6','7','8','9',
                               'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                               's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A',
                               'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                               'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                               'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '~', '!',
                               '@', '#', '$', '%', '^', '&', '*', '(', ')',
                               '_', '+', '-', '=', '`', '[', ']', ' ', ';',
                               '"', ',', '.', '/', '{', '}', '|', ':', '"',
                               '<', '>', '?'}; 
#define baseX_ch(X)   baseX_table_64[X]
#define baseX_table_64    baseX_table_61
                               
_ui baseX_digit(_uc c, _i base)
{
	_ui num;
	for(num=0; num <= base; ++num){
		if(c == baseX_table_64[num])
		    break;
	}
	return(num);
}

_ul baseX_sz(_uc* n_sz, _i base)
{
    _ui dig;
	_ul num;
	_ui i0[2];
	_ui nsz_len = strlen((_cc*)n_sz);

	for(i0[0] = 0, dig=0, num=0; i0[0] <= nsz_len-1; ++i0[0]){
		dig = (_ul)baseX_digit(n_sz[i0[0]], base);
		num *= base;
		num += dig;
	}
	return(num);
}

_ul baseX_sum_peelback(_ul sum, _ui base)
{
    _i i0=0;
    _ul finl=0;
    for( finl = sum; finl >= base ; finl -= base)
        i0++;

    return(finl);
}

_c* reverseZ(char * str )
{ 
    int i, len ;
      
    // calculating length of the string
    len = strlen(str);
    _c* re = (_c*)malloc((sizeof(_c) * len)+1);
      
    for( i=len ; i>=0 ; i--)
        re[i] = *(str+i);
    
    return(re);
}

_uc* baseX_digitsum(_ul num, _ui base)
{
    _ui ops;
	_ui count = 0;
	_ul num_tmp;
	_ul num_tot = num;
	_ul num_prev = num_tot;
    _uc* strrep = 0;

    num_tmp = (_ul)baseX_sum_peelback(num_tot, base);

    convbuf[count] = baseX_table_64[num_tmp];
  
	for(ops = 1, count = 1; num_tot >= base; ++ops, ++count){
	        
		num_tot /= base;
	    num_tmp = (_ul)baseX_sum_peelback(num_tot, base);
        convbuf[count] = baseX_table_64[ (_ui)num_tmp];
    }

    n_digz = ops;
    
    strrep = (_uc*)malloc(sizeof(_uc) * (n_digz + 1));
    
    for(_i i0=0, i1=n_digz-1; i0 <= n_digz; ++i0){
        strrep[i0] = convbuf[i1];
        i1--;
    }
    strrep[n_digz] = '\0';
    reverseZ(strrep);
	return((_uc*)reverseZ((_uc*)strrep));
}

//00000000000000000000000000000000000000000000000000000000000000000000000000000000000