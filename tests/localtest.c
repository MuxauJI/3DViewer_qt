#include "parser.h"

int main() {
  int error = 0;
  struct object_s object = {0, 0, 0, 0, 0, 0, NULL, NULL, {0}};
  char* path_to_file = "./obj/skull.obj";

  error = parse_file(path_to_file, &object);
  if (error != 0) {
    printf("%s", view_error(error));
  } else {
    printf("v = %d, f = %d\n", object.vertex_count, object.facets_count);
    print_object(object);
    float* vert = get_vertices(&object);
    // print_vertices(vert, object.vertex_limit);

    unsigned* face = get_facets(&object);
    // print_facets(face, object.facets_limit);

    printf("Vertex limit = %d, Facets limit = %d\n", object.vertex_limit,
           object.facets_limit);

    free_object(&object);
    free(vert);
    free(face);
    printf("All good\n");
  }

  return 0;
}
