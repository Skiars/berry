#ifndef __BE_VM_H
#define __BE_VM_H

#include "be_object.h"

typedef struct bglobaldesc {
    bmap *idxtab; /* global variable index table */
    struct bvector *gvalist; /* global variable list */
    int nglobal; /* global variable count */
} bglobaldesc;

typedef struct {
    bvalue *func; /* function register pointer */
    bvalue *top; /* top register pointer */
    bvalue *reg; /* base register pointer */
    binstruction *ip; /* instruction pointer (only berry-function) */
    int status;
} bcallframe;

struct bvm {
    bstringtable *strtab;
    bgc *gc;
    bvalue *global; /* global variable vector */
    bvalue *stack; /* stack space */
    bupval *upvalist; /* open upvalue list */
    struct bvector *callstack; /* function call stack */
    bglobaldesc gbldesc; /* global description */
    bcallframe *cf; /* function call frame */
    bvalue *reg;
    bvalue *top;
};

#define NONE_FLAG           0
#define BASE_FRAME          (1 << 0)
#define PRIM_FUNC           (1 << 1)

#define topreg(_vm)         ((vm)->top)
#define var2cl(_v)          cast(bclosure*, var_toobj(_v))
#define curcl(_vm)          var2cl((_vm)->cf->func)

void be_exec(bvm *vm);
void be_dofunc(bvm *vm, bclosure *cl, int argc);
void be_dontvfunc(bvm *vm, bntvfunc *f, int argc);
void be_dofuncvar(bvm *vm, bvalue *v, int argc);

#endif
