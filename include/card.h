#ifndef CARD_H
#define CARD_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define CARD_CITY_SIZE 60
#define CARD_CODE_SIZE 3

typedef struct card_args_t card_args_t;
typedef struct card_fields_t card_fields_t;
typedef struct card_namespace_t card_namespace_t;
typedef struct card_t card_t;

typedef uint8_t card_field_t;

struct card_fields_t
{
    card_field_t area;
    card_field_t city;
    card_field_t code;
    card_field_t gpd;
    card_field_t gpd_per_capita;
    card_field_t population;
    card_field_t population_density;
    card_field_t power;
    card_field_t state;
    card_field_t tourist_attractions;
};

struct card_t
{
    float area;
    char city[CARD_CITY_SIZE + 1];
    char code[CARD_CODE_SIZE + 1];
    float gpd;
    unsigned int population;
    char state;
    unsigned int tourist_attractions;
    
    double gpd_per_capita;
    float population_density;
    double power;
};

struct card_args_t
{
    float area;
    char city[CARD_CITY_SIZE + 1];
    char code[CARD_CODE_SIZE + 1];
    float gpd;
    unsigned int population;
    char state;
    unsigned int tourist_attractions;
};

struct card_namespace_t
{
    bool (*check_area)(float area);
    bool (*check_code)(const char *code, char state);
    bool (*check_state)(char state);
    int8_t (*compare)(
        card_field_t field, const card_t *card1, const card_t *card2
    );
    bool (*get_field_formatted)(
        char *buffer, size_t size, card_field_t field, const card_t *card
    );
    const char *(*get_field_name)(card_field_t field);
    bool (*init)(card_t *card, const card_args_t *args);
    void (*print)(const card_t *card);
    card_fields_t *fields;
};

extern const card_namespace_t *Card;

#endif /* CARD_H */