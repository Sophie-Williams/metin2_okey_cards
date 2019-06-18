// FIND // ZNAJDŹ //

ACMD(do_cube)
{
...
}


// ADD UNDER THIS FUNCTION // DODAJ POD TĄ FUNKCJĄ //

ACMD(do_cards)
{
    const char *line;


    char arg1[256], arg2[256];


    line = two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
    switch (LOWER(arg1[0]))
    {
        case 'o':    // open
            if (isdigit(*arg2))
            {
                DWORD safemode;
                str_to_number(safemode, arg2);
                ch->Cards_open(safemode);
            }
            break;
        case 'p':    // open
            ch->Cards_pullout();
            break;
        case 'e':    // open
            ch->CardsEnd();
            break;
        case 'd':    // open
            if (isdigit(*arg2))
            {
                DWORD destroy_index;
                str_to_number(destroy_index, arg2);
                ch->CardsDestroy(destroy_index);
            }
            break;
        case 'a':    // open
            if (isdigit(*arg2))
            {
                DWORD accpet_index;
                str_to_number(accpet_index, arg2);
                ch->CardsAccept(accpet_index);
            }
            break;
        case 'r':    // open
            if (isdigit(*arg2))
            {
                DWORD restore_index;
                str_to_number(restore_index, arg2);
                ch->CardsRestore(restore_index);
            }
            break;
        default:
            return;
    }
}
