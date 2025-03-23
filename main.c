#include "./src/linked_list.c"

int main(void) {
  LinkedList *list = list_init();

  list_push_head(list, node_init_with(DataType_I32, (void *)20));
  list_push_head(list, node_init_with(DataType_I32, (void *)3040));
  Node *x_node = node_init_with(DataType_String,
                                (void *)string_from("const char *init_string"));
  list_push_head(list, x_node);
  list_print(list);

  list_remove_node(list, x_node);
  list_print(list);

  list_remove_index(list, 1);
  list_remove_index(list, 4930);
  list_print(list);

  list_push_head(list, node_init_with(DataType_I32, (void *)true));
  list_push_head(list, node_init_with(DataType_I32, (void *)8293));
  list_print(list);

  list_free(list);
  return 0;
}
