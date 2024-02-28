#if defined(PYTHON_BINDING) || defined(RUST_BINDING)
#define RUAPU_IMPLEMENTATION
#include "ruapu.h"
#endif

#ifdef PYTHON_BINDING
#define PY_SSIZE_T_CLEAN
#include <Python.h>

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

static PyMethodDef ruapu_methods[] =
{
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
    ruapu_init();
    return PyModule_Create(&ruapu_module);
}

#endif
