//
// Created by michael on 19.04.2023.
//
#include "parser.h"

char *view_error(int i) {
  char *error = "Unknown error";
  if (i == 1) error = "Error open file";
  if (i == 2) error = "Error parse vertices";
  if (i == 3) error = "Error parse facets";
  if (i == 4) error = "Error calloc";
  return error;
}

void scale_object(float *vert, struct object_s *object, double base_scale,
                  double new_scale) {
  for (unsigned int i = 0; i < object->vertex_limit; i++) {
    vert[i] /= base_scale;
    vert[i] *= new_scale;
  }
}

void move_object(float *vert, struct object_s *object, int value,
                 char direction) {
  switch (direction) {
    case 'x':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        vert[i] += (float)value;
      }
      break;
    case 'y':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        vert[i + 1] += (float)value;
      }
      break;
    case 'z':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        vert[i + 2] += (float)value;
      }
      break;
  }
}

void rotate(float *vert, struct object_s *object, int value, char direction) {
  double angle = (double)value / 180 * M_PI;
  switch (direction) {
    case 'x':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        float y = vert[i + 1];
        float z = vert[i + 2];
        vert[i + 1] = y * cos(angle) - z * sin(angle);
        vert[i + 2] = y * sin(angle) + z * cos(angle);
      }
      break;
    case 'y':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        float x = vert[i];
        float z = vert[i + 2];
        vert[i] = x * cos(angle) + z * sin(angle);
        vert[i + 2] = -x * sin(angle) + z * cos(angle);
      }
      break;
    case 'z':
      for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
        float x = vert[i];
        float y = vert[i + 1];
        vert[i] = x * cos(angle) - y * sin(angle);
        vert[i + 1] = x * sin(angle) + y * cos(angle);
      }
      break;
  }
}

void normalize_vertices(float *vert, struct object_s *object) {
  for (unsigned int i = 0; i < object->vertex_limit; i += 3) {
    float x = 2 * ((vert[i] - object->minMax[0]) /
                   (object->minMax[1] - object->minMax[0])) -
              1;
    float y = 2 * ((vert[i + 1] - object->minMax[2]) /
                   (object->minMax[3] - object->minMax[2])) -
              1;
    float z = 2 * ((vert[i + 2] - object->minMax[4]) /
                   (object->minMax[5] - object->minMax[4])) -
              1;
    vert[i] = x;
    vert[i + 1] = y;
    vert[i + 2] = z;
    minMax(x, y, z, object);
  }
}

float *get_vertices(struct object_s *object) {
  object->vertex_limit = 3 * object->vertex_count;
  float *vertices = (float *)calloc(object->vertex_limit, sizeof(float));
  if (vertices != NULL) {
    for (unsigned int i = 0, j = 0; i < object->vertex_count; i++) {
      vertices[j++] = object->vertices[i].point[0];
      vertices[j++] = object->vertices[i].point[1];
      vertices[j++] = object->vertices[i].point[2];
    }
  }
  return vertices;
}

double max_range(double range_x, double range_y, double range_z) {
  double max = range_x;
  if (range_y > range_x) max = range_y;
  if (range_z > range_y) max = range_z;
  return max;
}

double *get_projection(struct object_s object) {
  double *prjn = (double *)calloc(6, sizeof(double));
  double range = 0.6 * max_range(object.minMax[1] - object.minMax[0],
                                 object.minMax[3] - object.minMax[2],
                                 object.minMax[5] - object.minMax[4]);
  double fov = 60.0 * M_PI / 180;
  double nearest = 3 * (object.minMax[3] / (2.0 * tan((fov / 2.0))));
  double cX = (object.minMax[1] + object.minMax[0]) / 2;
  double cY = (object.minMax[3] + object.minMax[2]) / 2;
  prjn[0] = cX - range;
  prjn[1] = cX + range;
  prjn[2] = cY - range;
  prjn[3] = cY + range;
  prjn[4] = nearest;
  prjn[5] = 3000;
  return prjn;
}

unsigned int *get_facets(struct object_s *object) {
  int limit = 0, k = 0;
  for (unsigned int i = 0; i < object->facets_count; i++) {
    limit += object->facets[i].points_count * 2;
  }
  if (limit != 0) {
    object->facets_limit = limit;
    unsigned int *facets = (unsigned int *)calloc(limit, sizeof(unsigned int));
    if (facets != NULL) {
      for (unsigned int j = 0; j < object->facets_count; j++) {
        for (int l = 0; l < object->facets[j].points_count; l++) {
          facets[k++] = object->facets[j].order[l] - 1;
          if (l + 1 >= object->facets[j].points_count)
            continue;
          else
            facets[k++] = object->facets[j].order[l + 1] - 1;
        }
        facets[k++] = object->facets[j].order[0] - 1;
      }
    }
    return facets;
  }
  return NULL;
}

void print_facets(unsigned int *facets, unsigned int facets_limit) {
  printf("Facets ");
  for (unsigned int i = 0; i < facets_limit; i++) {
    printf("%d, ", facets[i]);
  }
  printf("\n");
}

void print_vertices(float *vertices, unsigned int vertex_limit) {
  printf("Vertices ");
  for (unsigned int i = 0; i < vertex_limit; i++) {
    printf("%f, ", vertices[i]);
  }
  printf("\n");
}

void print_object(struct object_s object) {
  printf("v = %d, f = %d\n", object.vertex_count, object.facets_count);
  printf("Vertices:\n");
  for (unsigned int i = 0; i < object.vertex_count; i++) {
    printf("v[%d] = %f %f %f\n", i, object.vertices[i].point[0],
           object.vertices[i].point[1], object.vertices[i].point[2]);
  }
  printf("Facets:\n");
  for (unsigned int i = 0; i < object.facets_count; i++) {
    printf("f[%d] (count = %d) ", i, object.facets[i].points_count);
    for (int j = 0; j < object.facets[i].points_count; j++) {
      printf("%d ", object.facets[i].order[j]);
    }
    printf("\n");
  }
  printf("Facets: count = %d, amount = %d, limit = %d\n", object.facets_count,
         object.facets_amount, object.facets_limit);
  printf("Vertices: count = %d, amount = %d, limit = %d\n", object.vertex_count,
         object.vertex_amount, object.vertex_limit);
  printf(
      "MinMax vertices: Xmin = %f, Xmax = %f, Ymin = %f, Ymax = %f, Zmin = %f, "
      "Zmax = %f\n",
      object.minMax[0], object.minMax[1], object.minMax[2], object.minMax[3],
      object.minMax[4], object.minMax[5]);
}

int parse_facets(char *line, struct object_s *object) {
  int i;
  int res = 0;
  int space = 0;
  char *p = line;
  while (*p != '\0') {
    if (*p == ' ') {
      space = 1;
      p++;
      continue;
    }
    if (space == 1 && sscanf(p, "%d", &i) == 1) {
      object->facets[object->facets_amount].points_count++;
      space = 0;
    }
    p++;
  }

  int amount = 0;
  int count = object->facets[object->facets_amount].points_count;

  if (count == 0) res = 3;

  if (res == 0) {
    object->facets[object->facets_amount].order = calloc(count, sizeof(unsigned int));

    char *part = s21_strtok(line, " ");
    while (part != NULL) {
      if (sscanf(part, "%d", &i) == 1 && amount < count) {
        object->facets[object->facets_amount].order[amount] = abs(i);
        amount++;
      }
      part = s21_strtok(NULL, " ");
    }
    object->facets_amount++;
  }

  return res;
}

int parse_vertices(char *line, struct object_s *object) {
  int res = 0;
  float x, y, z;
  if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
    int i = object->vertex_amount;
    object->vertices[i].point[0] = x;
    object->vertices[i].point[1] = y;
    object->vertices[i].point[2] = z;
    object->vertex_amount++;
    minMax(x, y, z, object);
  } else {
    res = 2;
  }

  return res;
}

int parse_file(const char *file_path, struct object_s *object) {
  int res = 0;
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  fp = fopen(file_path, "r");
  if (fp != NULL) {
    while ((my_getline(&line, &len, fp)) != -1 && res == 0) {
      if (line[0] == 'v' && line[1] == ' ')
        object->vertex_count++;
      else if (line[0] == 'f' && line[1] == ' ')
        object->facets_count++;
    }
    if (line) {
      free(line);
      line = NULL;
    }
    if (object->vertex_count == 0) res = 2;

  } else {
    res = 1;
  }

  if (res == 0) {
    object->vertices = (struct vertices_s *)calloc(object->vertex_count,
                                                   sizeof(struct vertices_s));
    object->facets = (struct facets_s *)calloc(object->facets_count,
                                               sizeof(struct facets_s));
    if (object->vertices == NULL || object->facets == NULL) res = 4;
    fseek(fp, 0, SEEK_SET);

    while ((my_getline(&line, &len, fp)) != -1 && res == 0) {
      if (line[0] == 'v' && line[1] == ' ') {
        res = parse_vertices(line, object);
      } else if (line[0] == 'f' && line[1] == ' ') {
        res = parse_facets(line, object);
      }
    }
    if (line) free(line);
  }

  fclose(fp);

  return res;
}

void minMax(double x, double y, double z, struct object_s *object) {
  if (x < object->minMax[0]) object->minMax[0] = x;
  if (x > object->minMax[1]) object->minMax[1] = x;
  if (y < object->minMax[2]) object->minMax[2] = y;
  if (y > object->minMax[3]) object->minMax[3] = y;
  if (z < object->minMax[4]) object->minMax[4] = z;
  if (z > object->minMax[5]) object->minMax[5] = z;
}

void free_object(struct object_s *object) {
  for (unsigned int i = 0; i < object->facets_count; i++) {
    free(object->facets[i].order);
  }
  free(object->facets);
  free(object->vertices);
  object->facets_amount = object->facets_count = object->facets_limit = 0;
  object->vertex_amount = object->vertex_count = object->vertex_limit = 0;
  object->minMax[0] = object->minMax[2] = object->minMax[4] = DBL_MAX;
  object->minMax[1] = object->minMax[3] = object->minMax[5] = -DBL_MAX;
  object->facets = NULL;
  object->vertices = NULL;
}

char *s21_strtok(char *str, const char *delim) {
  char *p, *ret;
  const char *q;
  static char *saveptr = NULL;
  if (!str && !saveptr) return NULL;
  if (!saveptr) {
    saveptr = str;
  }
  ret = saveptr;
  for (p = saveptr; *p != '\0'; p++) {
    for (q = delim; *q != '\0'; q++) {
      if (*p == *q) break;
    }
    if (*q == '\0') {
      break;
    }
  }
  if (*p == '\0') {
    saveptr = NULL;
    return NULL;
  }
  ret = p;
  for (; *p != '\0'; p++) {
    for (q = delim; *q != '\0'; q++) {
      if (*p == *q) break;
    }
    if (*q != '\0') {
      *p++ = '\0';
      break;
    }
  }
  saveptr = p;
  return ret;
}

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
  char *bufptr;
  char *p;
  size_t size;
  int c;
  if (!lineptr || !n || !stream) return -1;
  bufptr = *lineptr;
  size = *n;
  c = fgetc(stream);
  if (c == EOF) return -1;
  if (!bufptr) {
    if ((bufptr = (char *)malloc(GETLINE_BUFLEN)) == NULL) return -1;
    size = GETLINE_BUFLEN;
  }
  p = bufptr;
  while (c != EOF) {
    if ((ssize_t)(p - bufptr) > (ssize_t)(size - 1)) {
      size = size + GETLINE_BUFLEN;
      if ((bufptr = (char *)realloc(bufptr, size)) == NULL) return -1;
    }
    *p++ = c;
    if (c == '\n') {
      break;
    }
    c = fgetc(stream);
  }
  *p++ = 0;
  *lineptr = bufptr;
  *n = size;
  return p - bufptr - 1;
}
