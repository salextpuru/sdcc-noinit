COPTS+=-D__SDCC_STACK_AUTO=1

ifeq ($(SFS_FLOAT),y)
OBJS+=_fsadd_sfs.rel
else
OBJS+=_fsadd.rel
endif
