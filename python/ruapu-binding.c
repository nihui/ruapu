#define RUAPU_IMPLEMENTATION
#include "../ruapu.h"

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

static PyObject *get_isa_items_py(PyObject *self, PyObject *Py_UNUSED(args))
{
    const char* const* isa_supported = ruapu_rua();
    const char* const* old_ptr = isa_supported;
    int total = 0;
    while(*isa_supported)
    {
        total++;
        isa_supported++;
    }

    PyObject* supported_isa_py = PyTuple_New(total);
    if(supported_isa_py==NULL)
    {
        return PyErr_NoMemory();
    }
    
    Py_ssize_t tuple_idx = 0;
    while(*old_ptr)
    {
        PyTuple_SetItem(supported_isa_py, tuple_idx++, PyUnicode_FromString(*old_ptr));
        old_ptr++;
    }

    return supported_isa_py;
}

static PyMethodDef ruapu_methods[] =
{
    {"supports", (PyCFunction)ruapu_supports_py, METH_VARARGS | METH_KEYWORDS, PyDoc_STR("Check if the CPU supports an instruction set")},
    {"rua", (PyCFunction)get_isa_items_py, METH_NOARGS, PyDoc_STR("Get the instruction sets supported by the current CPU")},
    {NULL, NULL, 0, NULL}
};

static int
ruapu_exec(PyObject *mod)
{
    ruapu_init();
    return 0;
}

static PyModuleDef_Slot ruapu_slots[] = {
        {Py_mod_exec, ruapu_exec},
        {0, NULL}
};
/* PEP 489 – Multi-phase extension module */
static struct PyModuleDef ruapu_module =
{
    PyModuleDef_HEAD_INIT,
    "ruapu",
    PyDoc_STR("ruapu module"),
    0,
    ruapu_methods,
    ruapu_slots
};

PyMODINIT_FUNC PyInit_ruapu(void)
{
    return PyModuleDef_Init(&ruapu_module);
}
