#include <stdio.h>
#include <string.h>

#include <card.h>


static bool card_check_area(float area);
static bool card_check_code(const char *code, char state);
static bool card_check_state(char state);
static int8_t card_compare(
    card_field_t field, const card_t *card1, const card_t *card2
);
static bool card_get_field_formatted(
    char *buffer, size_t size, card_field_t field, const card_t *card
);
static const char *card_get_field_name(card_field_t field);
static bool card_init(card_t* card, const card_args_t *args);
static void card_print(const card_t *card);


typedef enum
{
    area,
    city,
    code,
    gpd,
    gpd_per_capita,
    population,
    population_density,
    power,
    state,
    tourist_attractions

} _card_field_t;

const card_namespace_t *Card = &(card_namespace_t)
{
    .init = card_init,
    .print = card_print,
    .check_area = card_check_area,
    .check_code = card_check_code,
    .check_state = card_check_state,
    .compare = card_compare,
    .get_field_formatted = card_get_field_formatted,
    .get_field_name = card_get_field_name,
    .fields = &(card_fields_t)
    {
        .area = area,
        .city = city,
        .code = code,
        .gpd = gpd,
        .gpd_per_capita = gpd_per_capita,
        .population = population,
        .population_density = population_density,
        .power = power,
        .state = state,
        .tourist_attractions = tourist_attractions
    }
};

static const char *card_get_field_name(card_field_t field)
{
    switch (field)
    {
        case area: return "Área";
        case city: return "Cidade";
        case code: return "Código";
        case gpd: return "PIB";
        case gpd_per_capita: return "PIB per capita";
        case population: return "População";
        case population_density: return "Densidade Populacional";
        case power: return "Super Poder";
        case state: return "Estado";
        case tourist_attractions: return "Pontos Turísticos";
        default: return "Campo Inválido";
    }
}

static bool card_get_field_formatted(
    char *buffer, size_t size, card_field_t field, const card_t *card
) {
    if (buffer == NULL || card == NULL || size <= CARD_CITY_SIZE)
        return false;

    memset(buffer, 0, size);

    switch (field)
    {
        case area:
            sprintf(buffer, "%.2f km²", card->area);
            break;
        case city:
            sprintf(buffer, "%s", card->city);
            break;
        case code:
            sprintf(buffer, "%s", card->code);
            break;
        case gpd:
            sprintf(buffer, "%.2f bilhões de reais", card->gpd);
            break;
        case gpd_per_capita:
            sprintf(buffer, "%.2f reais", card->gpd_per_capita);
            break;
        case population:
            sprintf(buffer, "%u", card->population);
            break;
        case population_density:
            sprintf(buffer, "%.2f hab/km²", card->population_density);
            break;
        case power:
            sprintf(buffer, "%.2f", card->power);
            break;
        case state:
            sprintf(buffer, "%c", card->state);
            break;
        case tourist_attractions:
            sprintf(buffer, "%u", card->tourist_attractions);
            break;
    }

    return true;
}

static bool card_check_area(float area)
{
    return area > 0;
}

static bool card_check_code(const char *code, char state)
{
    if (code == NULL || strlen(code) != 3)
        return false;

    if (code[0] != state || code[1] != '0' || code[2] < '1' || code[2] > '4')
        return false;

    return true;
}

static bool card_check_state(char state)
{
    if (state < 'A' || state > 'H')
        return false;

    return true;
}

static bool card_init(card_t *card, const card_args_t *args)
{
    bool args_are_valid = card != NULL
                       && args != NULL
                       && Card->check_state(args->state)
                       && Card->check_code(args->code, args->state)
                       && Card->check_area(args->area);

    if (!args_are_valid)
        return false;

    memset(card, 0, sizeof(card_t));

    card->state = args->state;
    card->population = args->population;
    card->area = args->area;
    card->gpd = args->gpd;
    card->tourist_attractions = args->tourist_attractions;

    strcpy(card->code, args->code);
    strcpy(card->city, args->city);

    card->gpd_per_capita = card->population > 0
                         ? card->gpd * 1000000000 / card->population
                         : 0;

    card->population_density = card->population / card->area;

    card->power = card->area
                + card->gpd
                + card->gpd_per_capita
                + card->population
                + card->tourist_attractions
                - card->population_density;

    return true;
}

static int8_t card_compare(
    card_field_t field, const card_t *card1, const card_t *card2
) {
    if (card1 == NULL || card2 == NULL)
        return -2;

    switch (field)
    {
        case area:
            return card1->area > card2->area ? 1
                 : card1->area < card2->area ? -1
                 : 0;

        case gpd:
            return card1->gpd > card2->gpd ? 1
                 : card1->gpd < card2->area ? -1
                 : 0;

        case population:
            return card1->population > card2->population ? 1
                 : card1->population < card2->population ? -1
                 : 0;

        case tourist_attractions:
            return card1->tourist_attractions > card2->tourist_attractions ? 1
                 : card1->tourist_attractions < card2->tourist_attractions ? -1
                 : 0;

        case gpd_per_capita:
            return card1->gpd_per_capita > card2->gpd_per_capita ? 1
                 : card1->gpd_per_capita < card2->gpd_per_capita ? -1
                 : 0;

        case population_density:
            return card1->population_density < card2->population_density ? 1
                 : card1->population_density > card2->population_density ? -1
                 : 0;

        case power:
        default:
            return card1->power > card2->power ? 1
                 : card1->power < card2->power ? -1
                 : 0;
    }

    return -2;
}

static void card_print(const card_t *card)
{
    if (card == NULL)
        return;

    printf("Estado: %c\n", card->state);
    printf("Código: %s\n", card->code);
    printf("Nome da Cidade: %s\n", card->city);
    printf("População: %d\n", card->population);
    printf("Área: %.2f km²\n", card->area);
    printf("PIB: %.2f bilhões de reais\n", card->gpd);
    printf("Número de Pontos Turísticos: %d\n", card->tourist_attractions);
    printf("Densidade Populacional: %.2f hab/km²\n", card->population_density);
    printf("PIB per Capita: %.2f reais\n", card->gpd_per_capita);
    printf("Super Poder: %.2f\n", card->power);
}