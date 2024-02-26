
#include <Python.h>

#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

static PyObject *ruapu_init_py(PyObject *self, PyObject *args)
{
    static int initialized = 0;
    if (!initialized)
        ruapu_init();
    Py_RETURN_NONE;
}

static PyObject *ruapu_supports_py(PyObject *self, PyObject *args)
{
    const char *isa;
    if (!PyArg_ParseTuple(args, "s", &isa))
        return NULL;
    return Py_BuildValue("i", ruapu_supports(isa));
}

static PyMethodDef ruapu_methods[] = {
    {"init", ruapu_init_py, METH_VARARGS, "Initialize ruapu library"},
    {"supports", ruapu_supports_py, METH_VARARGS, "Check if the CPU supports an instruction set"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef ruapu_module =
{
    PyModuleDef_HEAD_INIT,
    "ruapu",
    "ruapu module",
    -1,
    ruapu_methods
};

PyMODINIT_FUNC PyInit_ruapu(void)
{
    return PyModule_Create(&ruapu_module);
}
