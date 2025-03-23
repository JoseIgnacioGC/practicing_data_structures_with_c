#include "./string.c"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  DataType_I32,
  DataType_String,
} DataType;

typedef struct Node {
  struct Node *next;
  struct Node *prev;
  void *data;
  DataType data_type;
} Node;

typedef struct {
  Node *tail;
  Node *head;
  size_t length;
} LinkedList;

Node *node_init(const DataType data_type, const size_t sizeof_data) {
  Node *new_node = malloc(sizeof(Node));
  void *data_ptr = malloc(sizeof_data);

  if (new_node != NULL && data_ptr != NULL) {
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->data = data_ptr;
    new_node->data_type = data_type;
  }

  return new_node;
}

Node *node_init_with(const DataType data_type, void *data) {
  Node *node_ptr;

  switch (data_type) {
  case DataType_I32:
    node_ptr = node_init(data_type, sizeof(int));
    *(int *)node_ptr->data = *(int *)&data;
    break;
  case DataType_String:
    node_ptr = node_init(data_type, sizeof(String));
    node_ptr->data = data;
    break;
  default:
    return NULL;
  }

  return node_ptr;
}

void node_print(Node *node) {
  switch (node->data_type) {
  case DataType_String:
    print_string(node->data);
    break;
  case DataType_I32:
    printf("%i", *(int *)node->data);
    break;
  default: // TODO
    printf("%i", *(int *)node->data);
    break;
  }
}

void node_free(Node *node) {
  switch (node->data_type) {
  case DataType_String:
    string_free(node->data);
    break;
  case DataType_I32:
    free(node->data);
    break;
  }
}

LinkedList *list_init(void) {
  LinkedList *list = malloc(sizeof(LinkedList));

  if (list != NULL) {
    String *dummy_msg_1 = string_from("*dummy_node* tail");
    String *dummy_msg_2 = string_from("*dummy_node* head");

    list->head = node_init(DataType_String, sizeof(String));
    list->tail = node_init(DataType_String, sizeof(String));
    list->length = 0;

    list->head->prev = list->tail;
    list->tail->next = list->head;

    list->head->data = dummy_msg_2;
    list->tail->data = dummy_msg_1;
  }

  return list;
}

void list_push_head(LinkedList *list, Node *node) {
  list->length++;
  Node *real_head = list->head->prev;
  Node *dummy_head = list->head;

  node->prev = real_head;
  node->next = dummy_head;

  real_head->next = node;
  dummy_head->prev = node;
}

void list_remove_node(LinkedList *list, Node *node) {
  list->length--;
  Node *prev_node = node->prev;
  Node *next_node = node->next;

  if (prev_node != NULL) {
    prev_node->next = next_node;
  }
  if (next_node != NULL) {
    next_node->prev = prev_node;
  }

  free(node);
}

int8_t list_remove_index(LinkedList *list, size_t i) {
  if (list->length == 0 || list->length <= i) {
    return -1;
  }

  Node *current_node = list->tail->next;
  size_t current_i = 0;

  while (true) {
    if (i == current_i) {
      list_remove_node(list, current_node);
      return 0;
    }

    current_i++;
    current_node = current_node->next;
  }
}

void list_print(LinkedList *list) {
  Node *current_node = list->tail;
  size_t i = 0;

  printf("LinkedList {\n");
  printf("  length: %zu\n", list->length);
  do {
    printf("  %zu: ", i);
    node_print(current_node);
    printf(",\n");

    i++;
    current_node = current_node->next;
  } while (current_node != NULL);
  printf("}\n");
}

void list_free(LinkedList *list) {
  Node *current_node = list->tail;
  Node *next_node;

  do {
    next_node = current_node->next;
    node_free(current_node);
    free(current_node);
    current_node = next_node;
  } while (current_node != NULL);

  free(list);
}
