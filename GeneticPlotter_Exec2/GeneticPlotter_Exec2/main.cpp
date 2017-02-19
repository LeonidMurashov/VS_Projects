#include <Windows.h>
#include <fstream>
#include <Python.h>

using namespace std;

void compute()
{
	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs;
	double result = 0.0;
	Py_Initialize();
	pName = PyUnicode_FromString("main");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, "draw");
		if (pFunc && PyCallable_Check(pFunc))
		{
			pArgs = PyTuple_New(0);
			PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	Py_Finalize();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int)
{
	compute();
	return 0;
}