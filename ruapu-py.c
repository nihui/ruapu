#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define RUAPU_IMPLEMENTATION
#include "ruapu.h"

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

static PyObject *get_isa_items_py(PyObject *self, PyObject *args, PyObject *kwargs)
{
    int total = 0;
    for (size_t i = 0; i < sizeof(g_ruapu_isa_map) / sizeof(g_ruapu_isa_map[0]); i++)
    {
        if (g_ruapu_isa_map[i].capable)
        {
            total ++;
        }
    }

    PyObject* supported_isa = PyTuple_New(total);

    int tuple_idx = 0;
    for (size_t i = 0; i < sizeof(g_ruapu_isa_map) / sizeof(g_ruapu_isa_map[0]); i++)
    {
        if (g_ruapu_isa_map[i].capable)
        {
            PyTuple_SetItem(supported_isa, tuple_idx++, PyUnicode_FromString(g_ruapu_isa_map[i].isa));
        }
    }

    return supported_isa;
}

static PyMethodDef ruapu_methods[] =
{
    {"supports", ruapu_supports_py, METH_VARARGS | METH_KEYWORDS, "Check if the CPU supports an instruction set"},
    {"rua", get_isa_items_py, METH_VARARGS | METH_KEYWORDS, "Get the instruction sets supported by the current CPU"},
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
