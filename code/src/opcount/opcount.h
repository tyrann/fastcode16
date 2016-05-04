#ifndef __OPCOUNT_H_
#define __OPCOUNT_H_

#include <inttypes.h>

// Trigger operation count 
// #TODO Split operations types

#define OP_COUNT_NONE 0      // Counts nothing
#define OP_COUNT_OP 1       // Counts all
#define OP_COUNT_ALL 2

#ifndef OP_COUNT
#define OP_COUNT OP_COUNT_ALL
#endif

void __count_op(uint64_t* op_count, const uint16_t incr);

#if OP_COUNT > OP_COUNT_NONE
#define __COUNT_OP(op_count, incr) \
    __count_op(op_count, incr)
#else
#define __COUNT_OP(op_count, incr)
#endif

#if OP_COUNT > OP_COUNT_INDEX
#define __COUNT_INDEX(op_count, incr) \
    __count_op(op_count, incr)
#else
#define __COUNT_INDEX(op_count, incr)
#endif

#endif
