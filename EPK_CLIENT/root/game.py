// FIND // ZNAJDŹ //

def BINARY_Highlight_Item(self, inven_type, inven_pos): arat


// ADD UNDER // DODAJ POD //

def BINARY_Cards_UpdateInfo(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, hand_4, hand_4_v, hand_5, hand_5_v, cards_left, points):
  self.interface.UpdateCardsInfo(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, hand_4, hand_4_v, hand_5, hand_5_v, cards_left, points)

def BINARY_Cards_FieldUpdateInfo(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points):
    self.interface.UpdateCardsFieldInfo(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points)

def BINARY_Cards_PutReward(self, hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points):
    self.interface.CardsPutReward(hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points)

def BINARY_Cards_ShowIcon(self):
    self.interface.CardsShowIcon()

def BINARY_Cards_Open(self, safemode):
    self.interface.OpenCardsWindow(safemode)
