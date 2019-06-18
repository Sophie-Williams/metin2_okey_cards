// FIND // ZNAJDŹ //

 int pc_has_master_skill(lua_State* L)
    {
        LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
        bool bHasMasterSkill = false;
        for (int i=0; i< SKILL_MAX_NUM; i++)
            if (ch->GetSkillMasterType(i) >= SKILL_MASTER && ch->GetSkillLevel(i) >= 21)
            {
                bHasMasterSkill = true;
                break;
            }


        lua_pushboolean(L, bHasMasterSkill);
        return 1;
    }
    
 
// ADD UNDER // DODAJ POD //

int pc_get_okay_global_rank(lua_State* L)
    {
        LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
        if (!ch)
            return 0;
    


        char szBuf[4096+1];
        ch->GetGlobalRank(szBuf, sizeof(szBuf));
        lua_pushstring(L, szBuf);
        return 1;
    }


    int pc_get_okay_rund_rank(lua_State* L)
    {
        LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
        if (!ch)
            return 0;
    


        char szBuf[4096+1];
        ch->GetRundRank(szBuf, sizeof(szBuf));
        lua_pushstring(L, szBuf);
        return 1;
    }


===============================================================
    

// FIND // ZNAJDŹ //
    
{ "has_master_skill",    pc_has_master_skill    }
 

// ADD UNDER // DODAJ POD //

{ "get_okay_global_rank",    pc_get_okay_global_rank    },
{ "get_okay_rund_rank",    pc_get_okay_rund_rank    },
