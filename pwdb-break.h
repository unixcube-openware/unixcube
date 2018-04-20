

#ifdef __cplusplus 
extern "C" {
#endif

#include <unixcube/op_cbase.h>
#include <unixcube/op_fio.h>

typedef struct t_csz_ll
{
    _uc* sz;
    _ul szlen;
    _ul nod_indx;
    _ul nod_state;
    struct t_csz_ll* nex;
}csz_ll;

_ul count_delineors(_uc* sz, _uc deln)
{
    _uc* cp = sz;
    _ul lineors=0;
    for( lineos=0; *cp; ++cp)
        if( *cp = deln )
            lineors++;;
    return(lineors;
}

_ul get_segment_len( _uc* flat, _ul seg_beg, _uc rep)
{
    _ul i0=seg_beg+1;
    for( ; ; ){
        if(flat[i0] == rep)
            break;
        i0++;
    }
    return(i0);
}

csz_ll* szll_from_flatform( _uc* flat, _ul seg_beg, _uc rep, _uc deln)
{
    csz_ll* node = (csz_ll*)malloc(sizeof(csz_ll));
    node->szlen = get_segment_len(flat, seg_beg, rep);
    node->sz = (_uc*)malloc((sizeof(_uc) * node->szlen) + 1);
 
    _uc* szp0 = flat[seg_beg];
    _uc* szp1 = node->sz[0];
    for( ; ; ){
        *szp1 = *szp0;
        szp0++;
        if( *szp1 == rep ){
            *szp1 = deln;
            break;
        }
        szp1++;
    }
    
    node->nod_indx=0;
    node->nod_state=1;

    node->nex=0;
    return(node);
}

csz_ll* break_string(_uc* chvc, _uc delineor, _uc rep )
{
    _ul i0;
    _i nlc=0;
    _uc* inbuf = chvc;
    _uc* pwf_out=0;
    _ul insize = strlen((_cc*)inbuf);

    csz_ll* szll = szll_from_flatfrom(chvc, 0, rep, delineor);
    szll->nod_indx=0;
    csz_ll* llcp = szll;

    _ul delineor_count = count_delineors(chvc, delineor);
    _ul* seg_vecz=(_ul*)malloc( (sizeof(_uc) * delineor_count) + 1 );

    for(i0 = 0; i0 <= insize-1; ++i0){
        if(*inbuf == delineor){
            seg_vecz[nlc]=i0;
            *inbuf = rep;
            nlc++;
        }
        inbuf++;
    }
    
    for(i0=0; i0 <= nlc-1; ++i0){
        llcp->nex = szll_from_flatfrom(chvc, seg_vecz[i0]+1, rep, delineor);
        llcp = llcp->nex;      
        llcp->nod_indx = i0+1;  
    }
    szll->nod_state = nlc;
    return(szll);
}

_i main( _i argc, _c** argv)
{                                           // in <<- filename     -d;          -rL .. (where L is too common to actually be used
    static csz_ll* codestack = break_string(fget_data(argv[1]), argv[2][2], argv[3][2]); //as a delineor, so lets designate that to
                                                                                       //annotate a \n newline return K :) 

    printf("apparently, we constructed %u substrings.\n", (_ul)codestack->nod_state);
    return(0);
}

#ifdef __cplusplus 
}
#endif








