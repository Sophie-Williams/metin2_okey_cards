// FIND // ZNAJDŹ //

PyObject * wndMgrSetSlot(PyObject * poSelf, PyObject * poArgs)
{
    UI::CWindow * pWin;
    if (!PyTuple_GetWindow(poArgs, 0, &pWin))
        return Py_BuildException();


    int iSlotIndex;
    if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
        return Py_BuildException();


    int iItemIndex;
    if (!PyTuple_GetInteger(poArgs, 2, &iItemIndex))
        return Py_BuildException();


    int iWidth;
    if (!PyTuple_GetInteger(poArgs, 3, &iWidth))
        return Py_BuildException();


    int iHeight;
    if (!PyTuple_GetInteger(poArgs, 4, &iHeight))
        return Py_BuildException();


    int iImageHandle;
    if (!PyTuple_GetInteger(poArgs, 5, &iImageHandle))
        return Py_BuildException();


    D3DXCOLOR diffuseColor;
    PyObject* pTuple;
    if (!PyTuple_GetObject(poArgs, 6, &pTuple))
    {
        diffuseColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
        //return Py_BuildException();
    }
    else
    // get diffuse color from pTuple
    {
        if (PyTuple_Size(pTuple) != 4)
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 0, &diffuseColor.r))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 1, &diffuseColor.g))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 2, &diffuseColor.b))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 3, &diffuseColor.a))
            return Py_BuildException();
    }


    if (!pWin->IsType(UI::CSlotWindow::Type()))
        return Py_BuildException();


    UI::CSlotWindow * pSlotWin = (UI::CSlotWindow *)pWin;
    pSlotWin->SetSlot(iSlotIndex, iItemIndex, iWidth, iHeight, (CGraphicImage *)iImageHandle, diffuseColor);


    return Py_BuildNone();
}


// ADD UNDER // DODAJ POD //

PyObject * wndMgrSetCardSlot(PyObject * poSelf, PyObject * poArgs)
{
    UI::CWindow * pWin;
    if (!PyTuple_GetWindow(poArgs, 0, &pWin))
        return Py_BuildException();


    int iSlotIndex;
    if (!PyTuple_GetInteger(poArgs, 1, &iSlotIndex))
        return Py_BuildException();


    int iItemIndex;
    if (!PyTuple_GetInteger(poArgs, 2, &iItemIndex))
        return Py_BuildException();


    int iWidth;
    if (!PyTuple_GetInteger(poArgs, 3, &iWidth))
        return Py_BuildException();


    int iHeight;
    if (!PyTuple_GetInteger(poArgs, 4, &iHeight))
        return Py_BuildException();


    char * c_szFileName;
    if (!PyTuple_GetString(poArgs, 5, &c_szFileName))
        return Py_BuildException();


    D3DXCOLOR diffuseColor;
    PyObject* pTuple;
    if (!PyTuple_GetObject(poArgs, 6, &pTuple))
    {
        diffuseColor = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
        //return Py_BuildException();
    }
    else
    // get diffuse color from pTuple
    {
        if (PyTuple_Size(pTuple) != 4)
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 0, &diffuseColor.r))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 1, &diffuseColor.g))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 2, &diffuseColor.b))
            return Py_BuildException();
        if (!PyTuple_GetFloat(pTuple, 3, &diffuseColor.a))
            return Py_BuildException();
    }


    if (!pWin->IsType(UI::CSlotWindow::Type()))
        return Py_BuildException();


    UI::CSlotWindow * pSlotWin = (UI::CSlotWindow *)pWin;
    pSlotWin->SetCardSlot(iSlotIndex, iItemIndex, iWidth, iHeight, c_szFileName, diffuseColor);


    return Py_BuildNone();
}
