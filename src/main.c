#include <stdio.h>

#include <prompt.h>


int main()
{
    card_t card1;
    card_t card2;
    card_args_t args;
    card_field_t option = -1;
    card_t *cards[] = {&card1, &card2};

    for (uint8_t i = 0; i < sizeof(cards) / sizeof(card_t *); i++)
    {
        if (ask_for_card_args(&args) && Card->init(cards[i], &args))
            Card->print(cards[i]);
        else
        {
            printf("Erro ao criar carta");
            return 1;
        }
    }

    while (true)
    {
        option = print_comparison_menu();

        if (option != Card->fields->city)
            break;

        print_cards(&card1, &card2, Card->fields->power);
    }

    print_card_comparison(option, &card1, &card2);

    return 0;
}