// ADD IN import BLOCK // DODAJ W SEKCJI import //

import uiCube
import uiCards


===============================================================
    

// FIND // ZNAJDŹ //
    
def __MakeCubeResultWindow(self):


// ADD UNDER THIS FUNCTION // DODAJ POD TĄ FUNKCJĄ //

def __MakeCardsInfoWindow(self):
    self.wndCardsInfo = uiCards.CardsInfoWindow()
    self.wndCardsInfo.LoadWindow()
    self.wndCardsInfo.Hide()

def __MakeCardsWindow(self):
    self.wndCards = uiCards.CardsWindow()
    self.wndCards.LoadWindow()
    self.wndCards.Hide()

def __MakeCardsIconWindow(self):
    self.wndCardsIcon = uiCards.IngameWindow()
    self.wndCardsIcon.LoadWindow()
    self.wndCardsIcon.Hide()


===============================================================
    

// FIND // ZNAJDŹ //
    
self.__MakeCubeResultWindow()


// ADD UNDER // DODAJ POD //

self.__MakeCardsInfoWindow()
self.__MakeCardsWindow()
self.__MakeCardsIconWindow()


===============================================================
    

// FIND // ZNAJDŹ //
    
def CloseWbWindow(self):
    self.wndWeb.Close()
    

// ADD UNDER // DODAJ POD //

def OpenCardsInfoWindow(self):
    self.wndCardsInfo.Open()

def OpenCardsWindow(self, safemode):
    self.wndCards.Open(safemode)

def UpdateCardsInfo(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, hand_4, hand_4_v, hand_5, hand_5_v, cards_left, points):
    self.wndCards.UpdateCardsInfo(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, hand_4, hand_4_v, hand_5, hand_5_v, cards_left, points)

def UpdateCardsFieldInfo(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points):
    self.wndCards.UpdateCardsFieldInfo(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points)

def CardsPutReward(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points):
    self.wndCards.CardsPutReward(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points)

def CardsShowIcon(self):
    self.wndCardsIcon.Show()


===============================================================
    

// FIND // ZNAJDŹ //
    
del self.wndHelp


// ADD UNDER // DODAJ POD //

del self.wndCardsInfo
del self.wndCards
del self.wndCardsIcon


===============================================================
    

// FIND // ZNAJDŹ //
    
if self.wndHelp:
    self.wndHelp.Destroy()


// ADD UNDER // DODAJ POD //

if self.wndCardsInfo:
    self.wndCardsInfo.Destroy()


if self.wndCards:
    self.wndCards.Destroy()


if self.wndCardsIcon:
    self.wndCardsIcon.Destroy()
