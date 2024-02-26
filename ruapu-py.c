#define PY_SSIZE_T_CLEAN
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

static PyObject *ruapu_supports_py(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = {"isa", NULL};
    const char *isa;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", kwlist, &isa))
        return NULL;
    if (ruapu_supports(isa))
        Py_RETURN_TRUE;
    Py_RETURN_FALSE;
}

static PyMethodDef ruapu_methods[] = {
    {"init", ruapu_init_py, METH_VARARGS, "Initialize ruapu library"},
    {"supports", ruapu_supports_py, METH_VARARGS | METH_KEYWORDS, "Check if the CPU supports an instruction set"},
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
