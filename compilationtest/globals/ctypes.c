#include "Python.h"
#include "globalmethod.c"
//gcc -I/usr/include/python2.7/ ctypes.c 
static double (*quadpack_ctypes_function)(double) = NULL;


typedef double (*_sp_double_func)(double);

typedef struct {
    PyObject_HEAD
    char *b_ptr;
} _sp_cfuncptr_object;

typedef enum {
  Error=-3, 
  Not_Callable=-2,
  Invalid_Ctype=-1,
  /* Acceptable returns below */
  Callable=1,
  Valid_Ctype=2
} FuncType;


static _sp_double_func get_ctypes_function_pointer(PyObject *obj) {
    return (*((void **)(((_sp_cfuncptr_object *)(obj))->b_ptr)));
}


static int init_ctypes_func(PyObject *fun) {
    quadpack_ctypes_function = get_ctypes_function_pointer(fun);
}
//Assume it's a valid ctypes fn pointer BAD
