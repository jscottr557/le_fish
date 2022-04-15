#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "discord.h"
#include "include/channel_registry.h"
#include "include/library.h"
#include "include/str_ops.h"
#include "include/sorts.h"
#include "include/generic_bst.h"

//Global constants
word_t *word_list;
int *g_word_count;

bst_node_t *tree;

channel_snowflake_ll_t *channel_registry;

void register_channel(struct discord *client,
                      const struct discord_message *message) {
  channel_registry = append_channel(channel_registry, message->channel_id);
  write_registry(channel_registry, "registry");
}

void unregister_channel(struct discord *client,
                        const struct discord_message *message) {
  channel_registry = remove_channel(channel_registry, message->channel_id);
  write_registry(channel_registry, "registry");
}

void check_message(struct discord *client,
                   const struct discord_message *message) {
  //Take care of noise that shows up sometimes
  if(strcmp(message->content, " ") == 0) return;

  //Always allow registering and unregistering of channels
  if(strncmp(message->content, "!!register", 10) == 0) return;
  if(strncmp(message->content, "!!unregister", 12) == 0) return;

  //Ignore message if not from a specific channel
  if(search_registry(channel_registry, message->channel_id) == 0) {
    return;
  }


  //Get a mutable version of the user's message
  char *mutable_message = malloc(strlen(message->content));
  if(mutable_message == NULL) return;
  strcpy(mutable_message, message->content);

  //Strip punctuation
  for(int i = 0; i < strlen(mutable_message); i++) {
    if(ispunct(mutable_message[i])) {
      for(int j = i; j < strlen(mutable_message); j++) {
        mutable_message[j] = mutable_message[j+1];
      }
    i--;
    }
  }

  #ifdef DEBUG
  printf("stripped message: %s\n", mutable_message);
  #endif

  //Check every word in message for validity
  int valid_word_flag = 1;
  char *word = strtok(mutable_message, "  \0");
  while((valid_word_flag = binary_search(tree, word, &lexi_compare))) {
    word = strtok(NULL, "  \0");
  }


  //if one of the words is invalid delete the message
  if(word != NULL) {
    discord_delete_message(client, message->channel_id, message->id);
  }

  //free up memory
  free(mutable_message);
}

void on_ready(struct discord* client) {

  const struct discord_user *bot = discord_get_self(client);

  log_info("Logged in as %s!", bot->username);
}

int main(void)
{
  word_list = read_library("wordlist");
  int word_count = count_words("wordlist");
  g_word_count = &word_count;

  channel_registry = read_registry("registry");

  merge_sort(word_list, sizeof(word_t), 0, word_count - 1, &lexi_compare);
  tree = build_bst(word_list, sizeof(word_t), 0, word_count - 1);

  struct discord *client = discord_config_init("config.json");

  discord_set_on_ready(client, &on_ready);

  discord_set_on_command(client, "register", &register_channel);
  discord_set_on_command(client, "unregister", &unregister_channel);
  discord_set_on_message_create(client, &check_message);

  discord_run(client);

  discord_cleanup(client);

  return 0;
}

