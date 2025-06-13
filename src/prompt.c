#include <stdio.h>
#include <string.h>

#include <prompt.h>


#define BUFFER_SIZE 80

static void flush_stdin();

bool ask_for_card_state(card_args_t *args);
bool ask_for_card_code(card_args_t *args);
bool ask_for_card_area(card_args_t *args);
bool ask_for_card_city(card_args_t *args);
bool ask_for_card_population(card_args_t *args);
bool ask_for_card_gpd(card_args_t *args);
bool ask_for_card_tourist_attractions(card_args_t *args);
bool ask_for_card_args(card_args_t *args);

bool format_comparison_result(
    char *buffer, size_t size, int8_t result, card_t *card1, card_t *card2
);
void print_card_comparison(card_field_t field, card_t *card1, card_t *card2);
void print_cards(card_t *card1, card_t *card2, card_field_t field);
card_field_t print_comparison_menu();


static void flush_stdin()
{
    int c = 0;

    do c = getchar(); while (c != '\n' && c != EOF);
}

bool ask_for_card_state(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    while (true)
    {
        printf("\nDigite o estado da carta (A-H):\n> ");
        scanf(" %c%c", &args->state, &char_after_input);

        if (char_after_input == '\n' && Card->check_state(args->state))
            break;

        if (char_after_input != '\n')
            flush_stdin();

        printf("Estado inválido\n\n");
    }

    return true;
}

bool ask_for_card_code(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;
    char code = 0;

    while (true)
    {
        printf("\nDigite um número para o código da carta (1-4):\n> ");
        scanf(" %c%c", &code, &char_after_input);

        sprintf(args->code, "%c0%c", args->state, code);

        if (char_after_input == '\n' && Card->check_code(args->code, args->state))
            break;

        if (char_after_input != '\n')
            flush_stdin();

        printf("Número inválido\n\n");
    }

    return true;
}

bool ask_for_card_area(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    while (true)
    {
        printf("\nDigite o area da cidade (em km²):\n> ");
        scanf(" %f%c", &args->area, &char_after_input);

        if (char_after_input != '\n')
            flush_stdin();

        if (Card->check_area(args->area))
            break;

        printf("Área inválida");
    }

    return true;
}

bool ask_for_card_city(card_args_t *args)
{
    if (args == NULL)
        return false;

    printf("\nDigite o nome da cidade:\n> ");
    fgets(args->city, sizeof(args->city), stdin);

    args->city[strlen(args->city) - 1] = 0;

    return true;
}

bool ask_for_card_population(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite a população da cidade:\n> ");
    scanf(" %ui%c", &args->population, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_gpd(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite o PIB da cidade (em bilhões de reais):\n> ");
    scanf(" %f%c", &args->gpd, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_tourist_attractions(card_args_t *args)
{
    if (args == NULL)
        return false;

    char char_after_input = 0;

    printf("\nDigite o numero de pontos turisticos da cidade:\n> ");
    scanf(" %ui%c", &args->tourist_attractions, &char_after_input);

    if (char_after_input != '\n')
        flush_stdin();

    return true;
}

bool ask_for_card_args(card_args_t *args)
{
    if (args == NULL)
        return false;

    memset(args, 0, sizeof(card_args_t));

    bool status = ask_for_card_state(args)
               && ask_for_card_code(args)
               && ask_for_card_city(args)
               && ask_for_card_area(args)
               && ask_for_card_population(args)
               && ask_for_card_gpd(args)
               && ask_for_card_tourist_attractions(args);

    return status;
}

bool format_comparison_result(
    char *buffer, size_t size, int8_t result, card_t *card1, card_t *card2
) {
    if (buffer == NULL || card1 == NULL || card2 == NULL || size < (CARD_CITY_SIZE + 20))
        return false;

    memset(buffer, 0, size);

    if (result == 1)
        sprintf(buffer, "Carta 1 (%s) venceu!", card1->city);

    else if (result == -1)
        sprintf(buffer, "Carta 2 (%s) venceu!", card2->city);

    else if (result == 0)
        strcpy(buffer, "Empate!");

    else
        strcpy(buffer, "Erro ao comparar cartas");

    return true;
}

void print_card_comparison(card_field_t field, card_t *card1, card_t *card2)
{
    char buffer[BUFFER_SIZE];

    int8_t result = Card->compare(field, card1, card2);

    printf(
        "\nComparação de Cartas (Atributo: %s):\n\n", Card->get_field_name(field)
    );

    print_cards(card1, card2, field);

    if (format_comparison_result(buffer, BUFFER_SIZE, result, card1, card2))
        printf("\nResultado: %s\n", buffer);
}

void print_cards(card_t *card1, card_t *card2, card_field_t field)
{
    if (card1 == NULL || card2 == NULL)
        return;

    char buffer[BUFFER_SIZE];

    if (Card->get_field_formatted(buffer, BUFFER_SIZE, field, card1))
        printf("Carta 1 - %s (%c): %s\n", card1->city, card1->state, buffer);

    if (Card->get_field_formatted(buffer, BUFFER_SIZE, field, card2))
        printf("Carta 2 - %s (%c): %s\n", card2->city, card2->state, buffer);
}

card_field_t print_comparison_menu()
{
    card_field_t options_to_compare[] =
    {
        Card->fields->city,
        Card->fields->population,
        Card->fields->area,
        Card->fields->gpd,
        Card->fields->gpd_per_capita,
        Card->fields->tourist_attractions,
        Card->fields->population_density,
        Card->fields->power
    };
    uint8_t options_length = sizeof(options_to_compare) / sizeof(card_field_t);
    char char_after_input = 0;
    uint8_t option = -1;

    while (true)
    {
        printf("\nSelecione uma opção para comparar:\n");
        printf(
            " [%i]: Exibir %s\n", 0, Card->get_field_name(options_to_compare[0])
        );
        
        for (uint8_t i = 1; i < options_length; i++)
        {
            printf(
                " [%i]: Comparar %s\n",
                i,
                Card->get_field_name(options_to_compare[i])
            );
        }

        printf("> ");

        scanf(" %hhu%c", &option, &char_after_input);

        if (char_after_input != '\n' || option < 0 || option >= options_length)
            printf("Opção inválida\n\n");
        else
            break;

        if (char_after_input != '\n')
            flush_stdin();
    }

    return options_to_compare[option];
}