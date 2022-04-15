#include <stdio.h>
#include <stdlib.h>

#include "../discord.h"
#include "../include/channel_registry.h"

#define DEBUG

//Append a new linked list node to the end of the list specified by head, with
//channel_id as its payload. Returns the head of the linked list
channel_snowflake_ll_t *append_channel(channel_snowflake_ll_t *head,
                                    u64_snowflake_t channel_id){
  channel_snowflake_ll_t *new_node = malloc(sizeof(channel_snowflake_ll_t));
  if(new_node == NULL) return NULL;

  new_node->channel_id = channel_id;
  new_node->next = NULL;

  if(head == NULL) return new_node;

  channel_snowflake_ll_t *node = head;

  while(node->next != NULL){
    node = node->next;
  }
  node->next = new_node;

  return head;
}

//Remove node in linked list specified by channel_id, if list is empty or
//becomes empty, returns NULL, else returns head of new linked list
channel_snowflake_ll_t *remove_channel(channel_snowflake_ll_t *head,
                                       u64_snowflake_t channel_id) {
  if(head == NULL) return NULL;

  channel_snowflake_ll_t *node = head;

  if(head->channel_id == channel_id) {
    node = head->next;
    free(head);
    head = NULL;
    return node;
  }

  while(node->next != NULL) {
    if(node->next->channel_id == channel_id) {
      channel_snowflake_ll_t *remove = node->next;
      node->next = node->next->next;
      free(remove);
      remove = NULL;
    }
  }

  return head;
}

channel_snowflake_ll_t *read_registry(char *filename) {
  if(filename == NULL) return NULL;

  FILE *registry_fp = fopen(filename, "r");
  if(registry_fp == NULL) return NULL;

  u64_snowflake_t channel_buffer;
  channel_snowflake_ll_t *head = NULL;
  while(fread(&channel_buffer, sizeof(u64_snowflake_t), 1, registry_fp) == 1) {
    #ifdef DEBUG
    printf("read registered channel: %ld\n", channel_buffer);
    #endif
    head = append_channel(head, channel_buffer);
  }

  fclose(registry_fp);

  return head;
}

void write_registry(channel_snowflake_ll_t *head, char *filename) {
  if(filename == NULL) return;

  FILE *registry_fp = fopen(filename, "w");
  if(registry_fp == NULL) return;

  while(head != NULL) {
    fwrite(&(head->channel_id), sizeof(u64_snowflake_t), 1, registry_fp);
    head = head->next;
  }

  fclose(registry_fp);
}

int search_registry(channel_snowflake_ll_t *head, u64_snowflake_t needle) {

  while(head != NULL) {
    if(head->channel_id == needle) return 1;
    head = head->next;
    printf("test\n");
  }

  return 0;
}

u64_snowflake_t get_channel(channel_snowflake_ll_t *head, int index) {
  if(head == NULL) return 0;
  if(index < 0) return 0;

  for(int i = 0; i < index; i++) {
    head = head->next;
    if(head == NULL) return 0;
  }

  return head->channel_id;
}
