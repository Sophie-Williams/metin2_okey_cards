// FIND // ZNAJDŹ //

PyObject * eventGetVisibleStartLine(PyObject * poSelf, PyObject * poArgs)
{
    int iIndex;
    if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
        return Py_BuildException();


    return Py_BuildValue("i", CPythonEventManager::Instance().GetVisibleStartLine(iIndex));
}


// ADD UNDER // DODAJ POD //

PyObject * eventSetVisibleLineCount(PyObject * poSelf, PyObject * poArgs)
{
    int iIndex;
    if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
        return Py_BuildException();


    int iVisibletLine;
    if (!PyTuple_GetInteger(poArgs, 1, &iVisibletLine))
        return Py_BuildException();


    CPythonEventManager::Instance().SetVisibleLineCount(iIndex, iVisibletLine);
    return Py_BuildNone();
}


===============================================================
    

// FIND // ZNAJDŹ //
    
{ "GetVisibleStartLine",        eventGetVisibleStartLine,            METH_VARARGS },


// ADD UNDER // DODAJ POD //

{ "SetVisibleLineCount",        eventSetVisibleLineCount,            METH_VARARGS },
