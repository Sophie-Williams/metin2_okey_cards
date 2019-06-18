// FIND // ZNAJDŹ //

void CSlotWindow::SetSlot(DWORD dwIndex, DWORD dwVirtualNumber, BYTE byWidth, BYTE byHeight, CGraphicImage * pImage, D3DXCOLOR& diffuseColor)
{
    TSlot * pSlot;
    if (!GetSlotPointer(dwIndex, &pSlot))
        return;


    if (pSlot->isItem)
    if (pSlot->dwItemIndex == dwVirtualNumber)
    {
        pSlot->dwState = 0;
        pSlot->isItem = TRUE;
        if (pImage && pSlot->pInstance)
        {
            pSlot->pInstance->SetImagePointer(pImage);
        }
        return;
    }


    ClearSlot(pSlot);
    pSlot->dwState = 0;
    pSlot->isItem = TRUE;
    pSlot->dwItemIndex = dwVirtualNumber;


    if (pImage)
    {
        assert(NULL == pSlot->pInstance);
        pSlot->pInstance = CGraphicImageInstance::New();
        pSlot->pInstance->SetDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
        pSlot->pInstance->SetImagePointer(pImage);
    }


    pSlot->byxPlacedItemSize = byWidth;
    pSlot->byyPlacedItemSize = byHeight;


    if (pSlot->pCoverButton)
    {
        pSlot->pCoverButton->Show();
    }
}


// ADD UNDER // DODAJ POD //

void CSlotWindow::SetCardSlot(DWORD dwIndex, DWORD dwVirtualNumber, BYTE byWidth, BYTE byHeight, const char * c_szFileName, D3DXCOLOR& diffuseColor)
{
    CGraphicImage * pImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(c_szFileName);
    TSlot * pSlot;
    if (!GetSlotPointer(dwIndex, &pSlot))
        return;


    if (pSlot->isItem)
    if (pSlot->dwItemIndex == dwVirtualNumber)
    {
        pSlot->dwState = 0;
        pSlot->isItem = TRUE;
        if (pImage && pSlot->pInstance)
        {
            pSlot->pInstance->SetImagePointer(pImage);
        }
        return;
    }


    ClearSlot(pSlot);
    pSlot->dwState = 0;
    pSlot->isItem = TRUE;
    pSlot->dwItemIndex = dwVirtualNumber;


    if (pImage)
    {
        assert(NULL == pSlot->pInstance);
        pSlot->pInstance = CGraphicImageInstance::New();
        pSlot->pInstance->SetImagePointer(pImage);
        pSlot->pInstance->SetDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
    }


    pSlot->byxPlacedItemSize = byWidth;
    pSlot->byyPlacedItemSize = byHeight;


    if (pSlot->pCoverButton)
    {
        pSlot->pCoverButton->Show();
    }
}
