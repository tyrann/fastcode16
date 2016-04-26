#include "opcount.h"

void __count_op(uint64_t* op_count, uint16_t incr)
{
	*op_count+=incr;
}
	
