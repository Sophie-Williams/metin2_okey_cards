// FIND // ZNAJDŹ //

void LogManager::ItemLog(DWORD dwPID, DWORD x, DWORD y, DWORD dwItemID, const char * c_pszText, const char * c_pszHint, const char * c_pszIP, DWORD dwVnum)
{
    m_sql.EscapeString(__escape_hint, sizeof(__escape_hint), c_pszHint, strlen(c_pszHint));


    Query("INSERT DELAYED INTO log%s (type, time, who, x, y, what, how, hint, ip, vnum) VALUES('ITEM', NOW(), %u, %u, %u, %u, '%s', '%s', '%s', %u)",
            get_table_postfix(), dwPID, x, y, dwItemID, c_pszText, __escape_hint, c_pszIP, dwVnum);
}


// ADD UNDER // DODAJ POD //

void LogManager::OkayEventLog(int dwPID, const char * c_pszText, int points)
{
    Query("INSERT INTO okay_event%s (pid, name, points) VALUES(%d, '%s', %d)",
            get_table_postfix(), dwPID, c_pszText, points);
        
}
