LIBNAME=libz80.lib

COPTS+=-D__SDCC_STACK_AUTO=1

ifeq ($(SFS_FLOAT),y)
OBJS=_fsadd_sfs.rel
else
OBJS=_fsadd.rel
endif

OBJS+=abs.rel divmixed.rel divsigned.rel divunsigned.rel heap.rel
OBJS+=memmove.rel modmixed.rel modsigned.rel modunsigned.rel mulchar.rel
OBJS+=mul.rel __sdcc_call_hl.rel __sdcc_call_iy.rel
OBJS+=setjmp.rel strcpy.rel strlen.rel crtenter.rel
OBJS+=acosf.rel aligned_alloc.rel asincosf.rel asinf.rel assert.rel
OBJS+=atan2f.rel atanf.rel _atof.rel atoi.rel atol.rel atoll.rel
OBJS+=c16rtomb.rel c32rtomb.rel
OBJS+=calloc.rel ceilf.rel cosf.rel coshf.rel cotf.rel
OBJS+=_divsint.rel _divslong.rel _divslonglong.rel
OBJS+=_divuint.rel _divulong.rel _divulonglong.rel errno.rel expf.rel
OBJS+=fabsf.rel floorf.rel free.rel frexpf.rel _fs2schar.rel _fs2sint.rel
OBJS+=_fs2slong.rel _fs2uchar.rel _fs2uint.rel _fs2ulong.rel
OBJS+=_fscmp.rel _fsdiv.rel _fseq.rel _fsget1arg.rel _fsget2args.rel
OBJS+=_fsgt.rel _fslt.rel _fsmul.rel _fsneq.rel _fsnormalize.rel
OBJS+=_fsreturnval.rel _fsrshift.rel _fssub.rel _fsswapargs.rel gets.rel
OBJS+=isalnum.rel
OBJS+=isalpha.rel isblank.rel iscntrl.rel isdigit.rel isgraph.rel islower.rel
OBJS+=isprint.rel ispunct.rel isspace.rel isupper.rel isxdigit.rel _itoa.rel
OBJS+=labs.rel ldexpf.rel log10f.rel _logexpf.rel logf.rel _ltoa.rel
OBJS+=malloc.rel mblen.rel
OBJS+=mbsinit.rel mbtowc.rel _memchr.rel _memcmp.rel _memcpy.rel
OBJS+=_memset.rel modff.rel _modsint.rel
OBJS+=_modslong.rel _modslonglong.rel _moduint.rel _modulong.rel _modulonglong.rel
OBJS+=_mulint.rel _mullong.rel _mullonglong.rel powf.rel
OBJS+=printf_large.rel
OBJS+=puts.rel rand.rel realloc.rel _rlslonglong.rel _rlulonglong.rel
OBJS+=_rrslonglong.rel _rrulonglong.rel _schar2fs.rel
OBJS+=sincosf.rel sincoshf.rel
OBJS+=sinf.rel sinhf.rel _sint2fs.rel _slong2fs.rel sprintf.rel
OBJS+=sqrtf.rel _startup.rel _strcat.rel _strchr.rel _strcmp.rel
OBJS+=_strcspn.rel _strncat.rel _strncmp.rel _strncpy.rel
OBJS+=_strpbrk.rel _strrchr.rel _strspn.rel _strstr.rel _strtok.rel
OBJS+=strxfrm.rel tancotf.rel tanf.rel tanhf.rel time.rel tolower.rel
OBJS+=toupper.rel _uchar2fs.rel _uint2fs.rel _ulong2fs.rel vprintf.rel
OBJS+=wcrtomb.rel wctomb.rel

$(LIBDIR)/$(LIBNAME): $(LIBNAME)
	install -m 0666 -D $(LIBNAME) $(LIBDIR)/$(LIBNAME)

$(LIBNAME): $(HSFILES)  $(OBJS)
	$(CCLIB) a $(LIBNAME) *.rel

main.rel:
	$(CC) -c $(COPTS) main.c

%.rel:%.c
	$(CC) -c $(COPTS) $<



%.rel:%.s
	$(AS) -g -l -s -o $@ $<

clean: 
	rm -f *.lib *.lst *.sym *.exp *.bin *.map *.mem *.lnk *.ihx *.rel *.rst *.asm *.bin crt0.s *.rel *.hS *.\$$C
