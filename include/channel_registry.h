#ifndef CHANNEL_REGISTRY_H
#define CHANNEL_REGISTRY

typedef struct channel_snowflake_linked_list {
  u64_snowflake_t channel_id;
  struct channel_snowflake_linked_list *next;
} channel_snowflake_ll_t;


channel_snowflake_ll_t *append_channel(channel_snowflake_ll_t *head,
                                    u64_snowflake_t channel_id);

channel_snowflake_ll_t *remove_channel(channel_snowflake_ll_t *head,
                                    u64_snowflake_t channel_id);

channel_snowflake_ll_t *read_registry(char *filename);

void write_registry(channel_snowflake_ll_t *head, char *filename);

u64_snowflake_t get_channel(channel_snowflake_ll_t *head, int index);

int search_registry(channel_snowflake_ll_t *head, u64_snowflake_t needle);

#endif
