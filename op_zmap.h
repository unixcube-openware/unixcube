
#include <unixcube/op_types.h>
#include "thc4_main.h"

_v mpz_write_zmap(_c* fnam, mpz_t* mpzn);
_v mpz_read_zmap(_c* fnam, mpz_t* mpzn);
_v zmap_only_in(_c* file, _c* zmap);
_v zmap_only_out(_c* file, _c* zmap);
_v zmap_file(_c* file, _c* zmap, _i method);
_v zmap_out();

static _i fd_zmap;
static _ul nodelen;
static _uc* nodeset;

static  mpz_t* mN0;
static  mpz_t* mN1;

static _i zmap_state;

_v mpz_write_zmap(_c* fnam, mpz_t* mpzn)
{
    FILE* fp_mpz = fopen(fnam, "w");
    mpz_out_str(fp_mpz, 60, mpzn);
   // fprintf(fp_mpz, "shit, bitch\nsuckmeoff" );
    fclose(fp_mpz);
}

_v mpz_read_zmap(_c* fnam, mpz_t* mpzn)
{
    FILE* fp_mpz = fopen(fnam, "r");
    mpz_inp_str(mpzn, fp_mpz, 60);
   // fprintf(fp_mpz, "shit, bitch\nsuckmeoff" ); 
    fclose(fp_mpz);
}

_v zmap_extract(_c* file, _c* zmap)
{


}

_v zmap_replace(_c* file, _c* zmap)
{

}

_v zmap_restore(_c* file, _c* zmap)
{

}

_v zmap_file(_c* file, _c* zmap, _i method)
{
    off_t i0;
    fd_zmap = open(file, O_RDWR );
    struct stat sb;
    fstat(fd_zmap, &sb);

    nodelen = (_ul)sb.st_size;
 
    mN0 = (mpz_t*)malloc(sizeof(mpz_t) );
    nodeset = (_uc*)malloc(sizeof(_uc) * nodelen );

    mpz_init(mN0);
    mpz_set_ui(mN0, 0);
   
    nodeset=(_uc*)mmap(0, nodelen, PROT_READ | PROT_WRITE, MAP_SHARED, fd_zmap, 0);
    //_______________________now ^^this, is a crucial fucking variable! must be file legth in bytes...

    if(method == 1){
        for(i0=0; i0 <= nodelen-1; ++i0){
            if(nodeset[i0] == '\0'){
                mpz_setbit(mN0, i0);
                nodeset[i0]='Z';
            }else{
                mpz_clrbit(mN0, i0);
            }
            printf("%u-",(_ul)i0);
        }
        
        mpz_write_zmap(zmap, mN0);
     
    }else if(method == 2){
        mpz_read_zmap(zmap, mN0);
        for(i0=0; i0 <= (off_t)nodelen-1; ++i0){
            if(mpz_tstbit(mN0, i0)){
                nodeset[i0] = '\0';
            }
        }
    }
   
    zmap_state = 1;   
}

_v zmap_out()
{
    msync(nodeset, sizeof(nodeset), MS_SYNC );
    munmap(nodeset, nodelen);
    close(fd_zmap);

   // free(nodeset);
}

/*---ss-----------___--__--_--__-__--_--end of zmap functionality

_i main(_i argc, _c** argv)
{
    _i zmethod=0;
    if(argc >= 3){
        if(argv[3][0] == 'm')
            zmethod=1;
        if(argv[3][0] == 'u')
            zmethod=2;

        zmap_file(argv[1], argv[2], zmethod);

        printf("did all that shit!\n");

    }else{
        printf("not enough args: zmap file_main <file_zmap> [method::-m/-u]\n");
        exit(1);
    }

    zmap_out();
    printf("closed operal file.\n");

    return(0);
}*/