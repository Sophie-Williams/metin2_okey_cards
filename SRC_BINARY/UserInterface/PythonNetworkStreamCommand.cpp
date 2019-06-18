// FIND // ZNAJDŹ //

else if (!strcmpi(szCmd, "ObserverTeamInfo"))
    {    
    }
    

// ADD UNDER // DODAJ POD //

else if (!strcmpi(szCmd, "cards"))
    {
        if (TokenVector.size() < 2)
        {
            TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
            return;
        }
        if ("open" == TokenVector[1])
        {
            DWORD safemode = atoi(TokenVector[2].c_str());
            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Cards_Open", Py_BuildValue("(i)", safemode));
        }
        else if ("info" == TokenVector[1])
        {
            if (14 != TokenVector.size())
            {
                TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
                return;
            }
            DWORD card_in_hand_1 = atoi(TokenVector[2].c_str());
            DWORD card_in_hand_1_v = atoi(TokenVector[3].c_str());
            DWORD card_in_hand_2 = atoi(TokenVector[4].c_str());
            DWORD card_in_hand_2_v = atoi(TokenVector[5].c_str());
            DWORD card_in_hand_3 = atoi(TokenVector[6].c_str());
            DWORD card_in_hand_3_v = atoi(TokenVector[7].c_str());
            DWORD card_in_hand_4 = atoi(TokenVector[8].c_str());
            DWORD card_in_hand_4_v = atoi(TokenVector[9].c_str());
            DWORD card_in_hand_5 = atoi(TokenVector[10].c_str());
            DWORD card_in_hand_5_v = atoi(TokenVector[11].c_str());
            DWORD cards_left = atoi(TokenVector[12].c_str());
            DWORD points = atoi(TokenVector[13].c_str());
            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Cards_UpdateInfo", Py_BuildValue("(iiiiiiiiiiii)", card_in_hand_1, card_in_hand_1_v, card_in_hand_2, card_in_hand_2_v,
                                                                                                card_in_hand_3, card_in_hand_3_v, card_in_hand_4, card_in_hand_4_v, card_in_hand_5, card_in_hand_5_v,
                                                                                                cards_left, points));
        }
        else if ("finfo" == TokenVector[1])
        {
            if (9 != TokenVector.size())
            {
                TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
                return;
            }
            DWORD hand_1 = atoi(TokenVector[2].c_str());
            DWORD hand_1_v = atoi(TokenVector[3].c_str());
            DWORD hand_2 = atoi(TokenVector[4].c_str());
            DWORD hand_2_v = atoi(TokenVector[5].c_str());
            DWORD hand_3 = atoi(TokenVector[6].c_str());
            DWORD hand_3_v = atoi(TokenVector[7].c_str());
            DWORD points = atoi(TokenVector[8].c_str());
            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Cards_FieldUpdateInfo", Py_BuildValue("(iiiiiii)", hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points));
        }
        else if ("reward" == TokenVector[1])
        {
            if (9 != TokenVector.size())
            {
                TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
                return;
            }
            DWORD hand_1 = atoi(TokenVector[2].c_str());
            DWORD hand_1_v = atoi(TokenVector[3].c_str());
            DWORD hand_2 = atoi(TokenVector[4].c_str());
            DWORD hand_2_v = atoi(TokenVector[5].c_str());
            DWORD hand_3 = atoi(TokenVector[6].c_str());
            DWORD hand_3_v = atoi(TokenVector[7].c_str());
            DWORD points = atoi(TokenVector[8].c_str());
            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Cards_PutReward", Py_BuildValue("(iiiiiii)", hand_1, hand_1_v, hand_2, hand_2_v, hand_3, hand_3_v, points));
        }
        else if ("icon" == TokenVector[1])
        {
            if (2 != TokenVector.size())
            {
                TraceError("CPythonNetworkStream::ServerCommand(c_szCommand=%s) - Strange Parameter Count : %s", c_szCommand);
                return;
            }
            PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_Cards_ShowIcon", Py_BuildValue("()"));
        }
    }
