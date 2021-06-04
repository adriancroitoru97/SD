#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "utils.h"

#define MAX_STRING_SIZE		256

struct InfoImobil {
	char adresa[MAX_STRING_SIZE];
	char locatar[MAX_STRING_SIZE];
	int an_cumparare;
	int nr_animale_companie;
};

struct InfoOras {
	char adresa[MAX_STRING_SIZE];
	char oras[MAX_STRING_SIZE];
};

void
ht_put2(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	unsigned int index = ht->hash_function(key) % ht->hmax;
	linked_list_t *bucket = ht->buckets[index];

	struct info info;
	info.value = malloc(value_size);
	DIE(info.value == NULL, "malloc failed");
	info.key = malloc(key_size);
	DIE(info.key == NULL, "malloc failed");
	memcpy(info.value, value, value_size);
	memcpy(info.key, key, key_size);

	ll_add_nth_node(bucket, 0, &info);

	ht->size++;
}

int
main()
{
	hashtable_t *ht_imobile, *ht_orase;
	struct InfoImobil informatii_imobile[5];
	struct InfoOras informatii_orase[5];
	struct InfoImobil *p_infoImobil;

	/* task (a) */
	strcpy(informatii_imobile[0].adresa, "Str. Independentei nr.6, Focsani");
	strcpy(informatii_imobile[0].locatar, "George Ion");
	informatii_imobile[0].an_cumparare = 2005;
	informatii_imobile[0].nr_animale_companie = 1;

	strcpy(informatii_imobile[1].adresa, "Str. Unirii nr.24, Brasov");
	strcpy(informatii_imobile[1].locatar, "Vasile Petrescu");
	informatii_imobile[1].an_cumparare = 2012;
	informatii_imobile[1].nr_animale_companie = 6;

	strcpy(informatii_imobile[2].adresa, "Str. Aurului nr.1, Bucuresti");
	strcpy(informatii_imobile[2].locatar, "Adrian Minune");
	informatii_imobile[2].an_cumparare = 1995;
	informatii_imobile[2].nr_animale_companie = 3;

	strcpy(informatii_imobile[3].adresa, "Str. Bucegi nr.13, Pitesti");
	strcpy(informatii_imobile[3].locatar, "Felicia Barbulescu");
	informatii_imobile[3].an_cumparare = 2005;
	informatii_imobile[3].nr_animale_companie = 4;

	strcpy(informatii_imobile[4].adresa, "Str. Pisicilor nr.18, Bucuresti");
	strcpy(informatii_imobile[4].locatar, "Andrei Pisicescu");
	informatii_imobile[4].an_cumparare = 2018;
	informatii_imobile[4].nr_animale_companie = 18;

	ht_imobile = ht_create(100, hash_function_string,
				compare_function_strings);
	ht_put(ht_imobile, informatii_imobile[0].adresa,
		strlen(informatii_imobile[0].adresa) + 1, &informatii_imobile[0],
		sizeof(informatii_imobile[0]));
	ht_put(ht_imobile, informatii_imobile[1].adresa,
		strlen(informatii_imobile[1].adresa) + 1, &informatii_imobile[1],
		sizeof(informatii_imobile[1]));
	ht_put(ht_imobile, informatii_imobile[2].adresa,
		strlen(informatii_imobile[2].adresa) + 1, &informatii_imobile[2],
		sizeof(informatii_imobile[2]));
	ht_put(ht_imobile, informatii_imobile[3].adresa,
		strlen(informatii_imobile[3].adresa) + 1, &informatii_imobile[3],
		sizeof(informatii_imobile[3]));
	ht_put(ht_imobile, informatii_imobile[4].adresa,
		strlen(informatii_imobile[4].adresa) + 1, &informatii_imobile[4],
		sizeof(informatii_imobile[4]));

	/* task (b) */
	char dream_house1[] = "Str. Independentei nr.6, Craiova";
	char dream_house2[] = "Str. Bucegi nr.13, Pitesti";
	if (ht_has_key(ht_imobile, dream_house1))
		printf("Your dream house is no longer available\n");
	else
		printf("Omg! You can move in right now!\n");
	if (ht_has_key(ht_imobile, dream_house2))
		printf("Your dream house is no longer available\n");
	else
		printf("Omg! You can move in right now!\n");

	printf("\n");

	/* task (c) */
	char *token;
	char adresa_completa[MAX_STRING_SIZE];
	char *search = ",";

	strcpy(adresa_completa, informatii_imobile[0].adresa);
	token = strtok(adresa_completa, search);
	strcpy(informatii_orase[0].adresa, token);
	token = strtok(NULL, search);
	strcpy(informatii_orase[0].oras, token + 1);

	strcpy(adresa_completa, informatii_imobile[1].adresa);
	token = strtok(adresa_completa, search);
	strcpy(informatii_orase[1].adresa, token);
	token = strtok(NULL, search);
	strcpy(informatii_orase[1].oras, token + 1);

	strcpy(adresa_completa, informatii_imobile[2].adresa);
	token = strtok(adresa_completa, search);
	strcpy(informatii_orase[2].adresa, token);
	token = strtok(NULL, search);
	strcpy(informatii_orase[2].oras, token + 1);

	strcpy(adresa_completa, informatii_imobile[3].adresa);
	token = strtok(adresa_completa, search);
	strcpy(informatii_orase[3].adresa, token);
	token = strtok(NULL, search);
	strcpy(informatii_orase[3].oras, token + 1);

	strcpy(adresa_completa, informatii_imobile[4].adresa);
	token = strtok(adresa_completa, search);
	strcpy(informatii_orase[4].adresa, token);
	token = strtok(NULL, search);
	strcpy(informatii_orase[4].oras, token + 1);

	ht_orase = ht_create(100, hash_function_string,
				compare_function_strings);
	ht_put2(ht_orase, informatii_orase[0].oras,
		strlen(informatii_orase[0].oras) + 1, &informatii_orase[0],
		sizeof(informatii_orase[0]));
	ht_put2(ht_orase, informatii_orase[1].oras,
		strlen(informatii_orase[1].oras) + 1, &informatii_orase[1],
		sizeof(informatii_orase[1]));
	ht_put2(ht_orase, informatii_orase[2].oras,
		strlen(informatii_orase[2].oras) + 1, &informatii_orase[2],
		sizeof(informatii_orase[2]));
	ht_put2(ht_orase, informatii_orase[3].oras,
		strlen(informatii_orase[3].oras) + 1, &informatii_orase[3],
		sizeof(informatii_orase[3]));
	ht_put2(ht_orase, informatii_orase[4].oras,
		strlen(informatii_orase[4].oras) + 1, &informatii_orase[4],
		sizeof(informatii_orase[4]));

	char oras_cautat[] = "Bucuresti";
	unsigned int index = ht_orase->hash_function(oras_cautat) % ht_orase->hmax;
	linked_list_t *bucket = ht_orase->buckets[index];
	ll_node_t *current = bucket->head;
	while(current != NULL)
	{
		struct info* info = (struct info*)current->data;
		if(ht_orase->compare_function(oras_cautat, info->key) == 0)
		{
			printf("%s\n",info->value);
		}
		current = current->next;
	}

	printf("\n");

	/* task (d) */
	for (int i = 0; i < 5; i++) {
		if (informatii_imobile[i].nr_animale_companie > 5) {
			ht_remove_entry(ht_imobile, informatii_imobile[i].adresa);
		}
	}
	p_infoImobil = ht_get(ht_imobile, "Str. Unirii nr.24, Brasov");
	printf("%s\n", p_infoImobil->adresa);
	p_infoImobil = ht_get(ht_imobile, "Str. Aurului nr.1, Bucuresti");
	printf("%s\n", p_infoImobil->adresa);

	ht_free(ht_imobile);
	ht_free(ht_orase);

	return 0;
}
