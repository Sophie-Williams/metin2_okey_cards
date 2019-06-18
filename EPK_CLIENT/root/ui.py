// FIND // ZNAJDŹ //

def SetSlotCountNew(self, slotNumber, grade, count):
        wndMgr.SetSlotCountNew(self.hWnd, slotNumber, grade, count)
        

// ADD UNDER // DODAJ POD //

def SetCardSlot(self, renderingSlotNumber, CardIndex, cardIcon, diffuseColor = (1.0, 1.0, 1.0, 1.0)):
    if 0 == CardIndex or None == CardIndex:
        wndMgr.ClearSlot(self.hWnd, renderingSlotNumber)
        return


===============================================================
    

// FIND // ZNAJDŹ //
    
class AniImageBox(Window):


// ADD UNDER // DODAJ POD //

class AniImageBox(Window):
    def __init__(self, layer = "UI"):
        Window.__init__(self, layer)
        self.eventEndFrame = None


    def __del__(self):
        Window.__del__(self)
        self.eventEndFrame = None


    def RegisterWindow(self, layer):
        self.hWnd = wndMgr.RegisterAniImageBox(self, layer)


    def SetDelay(self, delay):
        wndMgr.SetDelay(self.hWnd, delay)


    def AppendImage(self, filename):
        wndMgr.AppendImage(self.hWnd, filename)


    def SetPercentage(self, curValue, maxValue):
        wndMgr.SetRenderingRect(self.hWnd, 0.0, 0.0, -1.0 + float(curValue) / float(maxValue), 0.0)
     
    def ResetFrame(self):
        wndMgr.ResetFrame(self.hWnd)
     
    def SetOnEndFrame(self, event):
        self.eventEndFrame = event


    def OnEndFrame(self):
        if self.eventEndFrame:
            self.eventEndFrame()
