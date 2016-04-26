#ifndef __OPCOUNT_H_
#define __OPCOUNT_H_

#include <inttypes.h>

// Trigger operation count 
// #TODO Split operations types

#define OP_COUNT_NONE 0      // Counts nothing
#define OP_COUNT_ALL 1       // Counts all

#ifndef OP_COUNT
#define OP_COUNT OP_COUNT_ALL
#endif

void __count_op(uint64_t* op_count);

#if OP_COUNT > OP_COUNT_NONE
#define __COUNT_OP(op_count) \
    __count_op(op_count)
#else
#define __COUNT_OP(op_count)
#endif

#endif
