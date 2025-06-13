#ifndef PROMPT_H
#define PROMPT_H

#include <card.h>

bool ask_for_card_args(card_args_t *args);
void print_card_comparison(card_field_t field, card_t *card1, card_t *card2);
void print_cards(card_t *card1, card_t *card2, card_field_t field);
card_field_t print_comparison_menu();

#endif /* PROMPT_H */