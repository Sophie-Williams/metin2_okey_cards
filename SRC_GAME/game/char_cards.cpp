#include "stdafx.h"
#include "char.h"
#include "utils.h"
#include "log.h"
#include "db.h"
#include "dev_log.h"
#include "locale_service.h"
#include <stdlib.h>
#include <sstream>
#include "config.h"
#include "desc.h"
#include "desc_manager.h"
#include "char_manager.h"
#include "item.h"
#include "item_manager.h"
#include "buffer_manager.h"
#include "packet.h"
#include "questmanager.h"
#include "monarch.h"
#include "mob_manager.h"
#include "desc_client.h"
#include "group_text_parse_tree.h"
#include <boost/algorithm/string/predicate.hpp>
#include <cctype>
#include "p2p.h"
#include "entity.h"
#include "sectree_manager.h"

void CHARACTER::Cards_open(DWORD safemode)
{
	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("´Ů¸Ą °Ĺ·ˇÁß(Ă˘°í,±łČŻ,»óÁˇ)żˇ´Â »çżëÇŇ Ľö ľř˝Ŕ´Ď´Ů."));
		return;
	}
	if (character_cards.cards_left <= 0) 
	{
		if (GetGold() < 5000000) // set how many yang you want from the player to start the game // ustaw ile chcesz yangow od gracza zeby zaczal gre //
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You dont have enough money. // Nie masz wystarczajacej liczby yangow."));
			return;
		}
		if (CountSpecifyItem(79506) < 1) // set how many cardsets you want from the player to start the game (should be 1) // ustaw ile talii kart chcesz od gracza aby zaczal gre //
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You dont have any cardsets. // Nie masz wystarczajacej ilosci talii kart."));
			return;
		}
		PointChange(POINT_GOLD, -5000000, true); // set how many yang you want from the player to start the game // ustaw ile chcesz yangow od gracza zeby zaczal gre //
		RemoveSpecifyItem(79506, 1); // set how many cardsets you want from the player to start the game (should be 1) // ustaw ile talii kart chcesz od gracza aby zaczal gre //
		Cards_clean_list();
		character_cards.cards_left = 24;
	}
	ChatPacket(CHAT_TYPE_COMMAND, "cards open %d", safemode);
	SendUpdatedInformations();
}

void CHARACTER::Cards_clean_list()
{
	memset(&character_cards, 0, sizeof(character_cards));
	memset(&randomized_cards, 0, sizeof(randomized_cards));
}

DWORD CHARACTER::GetEmptySpaceInHand()
{
	for (int i=0; i<MAX_CARDS_IN_HAND; ++i)
	{
		if (character_cards.cards_in_hand[i].type == 0)
			return i;
	}
	return -1;
}

void CHARACTER::Cards_pullout()
{
	DWORD empty_space = GetEmptySpaceInHand();
	if (empty_space == -1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You dont have space in hands. // Nie masz miejsca na rece."));
		return;
	}
	if (character_cards.cards_left < 1)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You dont have cards. // Nie masz kart."));
		return;
	}
	if (GetAllCardsCount() >= 5)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You dont have space on table. // Nie masz miejsca na stole."));
		return;
	}
	RandomizeCards();
	SendUpdatedInformations();
}

void CHARACTER::RandomizeCards()
{
	DWORD card_type = number(1, 3);
	DWORD card_value = number(1, 8);
	if (CardWasRandomized(card_type, card_value) != false)
	{
		RandomizeCards();
	}
	else
	{
		DWORD empty_space = GetEmptySpaceInHand();
		character_cards.cards_in_hand[empty_space].type = card_type;
		character_cards.cards_in_hand[empty_space].value = card_value;
		character_cards.cards_left -= 1;
	}
}

bool CHARACTER::CardWasRandomized(DWORD type, DWORD value)
{
	for (int i=0; i<24; ++i)
	{
		if (randomized_cards[i].type == type && randomized_cards[i].value == value)
		{
			return true;
		}
	}
	for (int i=0; i<24; ++i)
	{
		if (randomized_cards[i].type == 0)
		{
			randomized_cards[i].type = type;
			randomized_cards[i].value = value;
			return false;
		}
	}
	return false;
}

void CHARACTER::SendUpdatedInformations()
{
	ChatPacket(CHAT_TYPE_COMMAND, "cards info %d %d %d %d %d %d %d %d %d %d %d %d", character_cards.cards_in_hand[0].type, character_cards.cards_in_hand[0].value, 
																		character_cards.cards_in_hand[1].type, character_cards.cards_in_hand[1].value, character_cards.cards_in_hand[2].type,
																		character_cards.cards_in_hand[2].value, character_cards.cards_in_hand[3].type, character_cards.cards_in_hand[3].value,
																		character_cards.cards_in_hand[4].type, character_cards.cards_in_hand[4].value,
																		character_cards.cards_left, character_cards.points);
																		
	ChatPacket(CHAT_TYPE_COMMAND, "cards finfo %d %d %d %d %d %d %d", character_cards.cards_in_field[0].type, character_cards.cards_in_field[0].value, character_cards.cards_in_field[1].type,
																		character_cards.cards_in_field[1].value, character_cards.cards_in_field[2].type, character_cards.cards_in_field[2].value,
																		character_cards.field_points);
}

void CHARACTER::SendReward()
{
	ChatPacket(CHAT_TYPE_COMMAND, "cards reward %d %d %d %d %d %d %d", character_cards.cards_in_field[0].type, character_cards.cards_in_field[0].value, character_cards.cards_in_field[1].type,
																		character_cards.cards_in_field[1].value, character_cards.cards_in_field[2].type, character_cards.cards_in_field[2].value,
																		character_cards.field_points);
}

void CHARACTER::CardsDestroy(DWORD reject_index)
{
	if (reject_index + 1 > MAX_CARDS_IN_HAND)
		return;
	if (character_cards.cards_in_hand[reject_index].type == 0)
		return;
	character_cards.cards_in_hand[reject_index].type = 0;
	character_cards.cards_in_hand[reject_index].value = 0;
	SendUpdatedInformations();
}

void CHARACTER::CardsAccept(DWORD accept_index)
{
	if (accept_index + 1 > MAX_CARDS_IN_HAND)
		return;
	if (character_cards.cards_in_hand[accept_index].type == 0)
		return;
	DWORD empty_space = GetEmptySpaceInField();
	if (empty_space != -1)
	{
		character_cards.cards_in_field[empty_space].type = character_cards.cards_in_hand[accept_index].type;
		character_cards.cards_in_field[empty_space].value = character_cards.cards_in_hand[accept_index].value;
		character_cards.cards_in_hand[accept_index].type = 0;
		character_cards.cards_in_hand[accept_index].value = 0;
	}
	if (GetEmptySpaceInField() == -1)
	{
		if (CheckReward())
		{
			SendReward();
			ResetField();
		}
		else
		{
			RestoreField();
		}
	}
	SendUpdatedInformations();
}

void CHARACTER::CardsRestore(DWORD restore_index)
{
	if (restore_index + 1 > MAX_CARDS_IN_FIELD)
		return;
	if (character_cards.cards_in_field[restore_index].type == 0)
		return;
	DWORD empty_space = GetEmptySpaceInHand();
	character_cards.cards_in_hand[empty_space].type = character_cards.cards_in_field[restore_index].type;
	character_cards.cards_in_hand[empty_space].value = character_cards.cards_in_field[restore_index].value;
	character_cards.cards_in_field[restore_index].type = 0;
	character_cards.cards_in_field[restore_index].value = 0;
	SendUpdatedInformations();
}

DWORD CHARACTER::GetEmptySpaceInField()
{
	for (int i=0; i<MAX_CARDS_IN_FIELD; ++i)
	{
		if (character_cards.cards_in_field[i].type == 0)
			return i;
	}
	return -1;
}

DWORD CHARACTER::GetAllCardsCount()
{
	DWORD count = 0;
	for (int i=0; i<MAX_CARDS_IN_HAND; ++i)
	{
		if (character_cards.cards_in_hand[i].type != 0)
			count += 1;
	}
	for (int i=0; i<MAX_CARDS_IN_FIELD; ++i)
	{
		if (character_cards.cards_in_field[i].type != 0)
			count += 1;
	}
	return count;
}
bool CHARACTER::TypesAreSame()
{
	if (character_cards.cards_in_field[0].type == character_cards.cards_in_field[1].type && character_cards.cards_in_field[1].type == character_cards.cards_in_field[2].type)
		return true;
	return false;
}

bool CHARACTER::ValuesAreSame()
{
	if (character_cards.cards_in_field[0].value == character_cards.cards_in_field[1].value && character_cards.cards_in_field[1].value == character_cards.cards_in_field[2].value)
		return true;
	return false;
}

bool CHARACTER::CardsMatch()
{
	// cards matching function do not touch
	if (character_cards.cards_in_field[0].value == character_cards.cards_in_field[1].value - 1 && character_cards.cards_in_field[1].value == character_cards.cards_in_field[2].value -1)
		return true;
	else if (character_cards.cards_in_field[0].value == character_cards.cards_in_field[2].value - 1 && character_cards.cards_in_field[2].value == character_cards.cards_in_field[1].value -1)
		return true;
	else if (character_cards.cards_in_field[1].value == character_cards.cards_in_field[0].value - 1 && character_cards.cards_in_field[0].value == character_cards.cards_in_field[2].value -1)
		return true;
	else if (character_cards.cards_in_field[0].value == character_cards.cards_in_field[1].value - 1 && character_cards.cards_in_field[2].value == character_cards.cards_in_field[0].value -1)
		return true;
	else if (character_cards.cards_in_field[1].value == character_cards.cards_in_field[0].value - 1 && character_cards.cards_in_field[2].value == character_cards.cards_in_field[1].value -1)
		return true;
	else if (character_cards.cards_in_field[1].value == character_cards.cards_in_field[2].value - 1 && character_cards.cards_in_field[2].value == character_cards.cards_in_field[0].value -1)
		return true;
	else
		return false;
}

DWORD CHARACTER::GetLowestCard()
{
	return MIN(character_cards.cards_in_field[0].value, MIN(character_cards.cards_in_field[1].value, character_cards.cards_in_field[2].value));
}

bool CHARACTER::CheckReward()
{
    if (TypesAreSame() && ValuesAreSame())
    {
        character_cards.field_points = 0;    // nie mozna miec takich samych kart wiec zapsuty if  // you cant get same cards - broken if 
        character_cards.points += 0;         // nie mozna miec takich samych kart wiec zapsuty if  // you cant get same cards - broken if 
        return true; // niech zwróci true zeby nie zcrashowalo sie okno gry jezeli ktos bedzie cos odwalac w cheatengine lub kodzie gry. // let system return true to avoid game window crash
    }
    else if (TypesAreSame() && CardsMatch())
    {
		if (GetLowestCard() == 1)
		{
			character_cards.field_points = 50;     //1-1-1
			character_cards.points += 50;          //1-1-1
		}
		else if (GetLowestCard() == 2)
		{
			character_cards.field_points = 75;     //2
			character_cards.points += 75;          //2
		}
		else if (GetLowestCard() == 3)
		{
			character_cards.field_points = 100;     //3
			character_cards.points += 100;          //3
		}
		else if (GetLowestCard() == 4)
		{
			character_cards.field_points = 125;     //4
			character_cards.points += 125;          //4
		}
		else if (GetLowestCard() == 5)
		{
			character_cards.field_points = 150;     //5
			character_cards.points += 150;          //5
		}
		else if (GetLowestCard() == 6)
		{
			character_cards.field_points = 200;     //6
			character_cards.points += 200;          //6
		}
		else
		{
			character_cards.field_points = 100;    //czerwony/niebieski/zolty 6-7-8    red/blue/yellow
			character_cards.points += 100;         //czerwony/niebieski/zolty 6-7-8    red/blue/yellow
		}
        return true;
    }
    else if (ValuesAreSame())
    {
		if (GetLowestCard() == 1)
		{
			character_cards.field_points = 15;     //1-1-1
			character_cards.points += 15;          //1-1-1
		}
		else if (GetLowestCard() == 2)
		{
			character_cards.field_points = 30;     //2-2-2
			character_cards.points += 30;          //2-2-2
		}
		else if (GetLowestCard() == 3)
		{
			character_cards.field_points = 45;     //3-3-3
			character_cards.points += 45;          //3-3-3
		}
		else if (GetLowestCard() == 4)
		{
			character_cards.field_points = 60;     //4-4-4
			character_cards.points += 60;          //4-4-4
		}
		else if (GetLowestCard() == 5)
		{
			character_cards.field_points = 80;     //5-5-5
			character_cards.points += 80;          //5-5-5
		}
		else if (GetLowestCard() == 6)
		{
			character_cards.field_points = 100;     //6-6-6
			character_cards.points += 100;          //6-6-6
		}
		else if (GetLowestCard() == 7)
		{
			character_cards.field_points = 120;     //7-7-7
			character_cards.points += 120;          //7-7-7
		}
		else if (GetLowestCard() == 8)
		{
			character_cards.field_points = 150;     //8-8-8
			character_cards.points += 150;          //8-8-8
		}
		else
		{
			character_cards.field_points = GetLowestCard()*10+10;     //1-1-1
			character_cards.points += GetLowestCard()*10+10;          //1-1-1
		}
        return true;
    }
    else if (CardsMatch())
    {
        character_cards.field_points = GetLowestCard()*10;      // 6-7-8 rozny kolor//different color
        character_cards.points += GetLowestCard()*10;           // 6-7-8 rozny kolor//different color
        return true;
    }
    else
    {
        RestoreField();
        return false;
    }
}


void CHARACTER::RestoreField()
{
	for (int i=0; i<MAX_CARDS_IN_FIELD; ++i)
	{
		DWORD empty_space = GetEmptySpaceInHand();
		character_cards.cards_in_hand[empty_space].type = character_cards.cards_in_field[i].type;
		character_cards.cards_in_hand[empty_space].value = character_cards.cards_in_field[i].value;
		character_cards.cards_in_field[i].type = 0;
		character_cards.cards_in_field[i].value = 0;
		SendUpdatedInformations();
	}
}

void CHARACTER::ResetField()
{
	for (int i=0; i<MAX_CARDS_IN_FIELD; ++i)
	{
		character_cards.cards_in_field[i].type = 0;
		character_cards.cards_in_field[i].value = 0;
	}
}

void CHARACTER::CardsEnd()
{
	if (character_cards.points > 750) // points required to get diamond chest
		AutoGiveItem(71198); // diamond chest id | 750+ pts
	else if (character_cards.points < 750 && character_cards.points >= 600) // points required to get diamond chest - 600-750
		AutoGiveItem(71197); // platinum chest id | 600 - 750 pts
	else if (character_cards.points < 600 && character_cards.points >= 500)  // points required to get diamond chest - 500-600
		AutoGiveItem(71194); // gold chest id | 500 - 600 pts
	else if (character_cards.points < 500 && character_cards.points >= 300) // points required to get diamond chest - 300-500
		AutoGiveItem(71195); // silver chest id | 300 - 500 pts
	else if (character_cards.points > 0) // points required to get diamond chest - less than 300, but more than 0
		AutoGiveItem(71196); // bronze chest id | 0 - 300 pts
	LogManager::instance().OkayEventLog(GetPlayerID(), GetName(), character_cards.points); // remove(or just comment) if youre not using log's in okey cards
	Cards_clean_list();
	SendUpdatedInformations();
}

void CHARACTER::GetGlobalRank(char * buffer, size_t buflen)
{
	// db func for pc.get_okay_global_rank
	std::auto_ptr<SQLMsg> pMsg(DBManager::Instance().DirectQuery("SELECT name, SUM(points) as spoints FROM log.okay_event GROUP BY pid ORDER BY spoints DESC LIMIT 10"));
	if (pMsg->Get()->uiNumRows == 0)
	{
		return;
	}

	MYSQL_ROW row;
	int pos = 1;
	int len = 0, len2;
	*buffer = '\0';
	while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
	{
		int points = 0;
		str_to_number(points, row[1]);
		len2 = snprintf(buffer + len, buflen - len, "[ENTER]");

		if (len2 < 0 || len2 >= (int) buflen - len)
			len += (buflen - len) - 1;
		else
			len += len2;

		len2 = snprintf(buffer + len, buflen - len, "%d. Miejsce - %s - %d pkt.",  // %d (1/2/3.) Place - %s (char name) - %d Points // 1. Place - TAKE - 777 Points
				pos,
				row[0],
				points);
		++pos;
		if (len2 < 0 || len2 >= (int) buflen - len)
			len += (buflen - len) - 1;
		else
			len += len2;
	}
}

void CHARACTER::GetRundRank(char * buffer, size_t buflen)
{
	// db func for pc.get_okay_rund_rank
	std::auto_ptr<SQLMsg> pMsg(DBManager::Instance().DirectQuery("SELECT name, points FROM log.okay_event ORDER BY points DESC LIMIT 10"));
	if (pMsg->Get()->uiNumRows == 0)
	{
		return;
	}

	MYSQL_ROW row;
	int pos = 1;
	int len = 0, len2;
	*buffer = '\0';
	while (NULL != (row = mysql_fetch_row(pMsg->Get()->pSQLResult)))
	{
		int points = 0;
		str_to_number(points, row[1]);
		len2 = snprintf(buffer + len, buflen - len, "[ENTER]");

		if (len2 < 0 || len2 >= (int) buflen - len)
			len += (buflen - len) - 1;
		else
			len += len2;

		len2 = snprintf(buffer + len, buflen - len, "%d. Miejsce - %s - %d pkt.",  // %d (1/2/3.) Place - %s (char name) - %d Points // 1. Place - TAKE - 777 Points
				pos,
				row[0],
				points);
		++pos;
		if (len2 < 0 || len2 >= (int) buflen - len)
			len += (buflen - len) - 1;
		else
			len += len2;
	}
}
