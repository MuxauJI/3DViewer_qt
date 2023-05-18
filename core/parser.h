/*!
 * \file
 * \brief Заголовочный файл с описанием классов
 *
 * Данный файл содержит в себе определения основных
 * классов, используемых в демонстрационной программе
 */
#ifndef CORE_PARSER_H_
#define CORE_PARSER_H_
//  #define _GNU_SOURCE // надо добавлять если пользуемся getline но так как её
//  нет под win32 исп. my_getline

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  // для ssize_t
/*!
 * Константа для значения буфера своей функции чтениия по строкам
 */
#define GETLINE_BUFLEN 128

/*!
 * \brief Структура для хранения координат x,y,z - вершины одной точки
 *
 */
struct vertices_s {
  float point[3];
};

/*!
 * \brief Структура для хранения "рёбер"
 *
 */
struct facets_s {
  /** points_count количество вершин в данном "ребре" */
  int points_count;
  /** order массив порядковых номеров вершин для соединения в "ребре" */
  unsigned int *order;
};

/*!
 * \brief Структура для хранения информации об объекте
 *
 */

struct object_s {
  /** vertex_count количество вершин расчитанное при первом проходе файла*/
  unsigned int vertex_count;
  /** facets_count количество ребер расчитанное при первом проходе файла*/
  unsigned int facets_count;
  /** vertex_amount количество вершин фактически добавленных при втором
   * прохождении по файлу */
  unsigned int vertex_amount;
  /** facets_amount количество ребер фактически добавленных при втором
   * прохождении по файлу */
  unsigned int facets_amount;
  /** vertex_limit общее количество значений всех координат вершин (x,y,z) (3 *
   * vertex_amount) */
  unsigned int vertex_limit;
  /** facets_limit общее количество значений порядковых номеров вершин
   * записанных попарно (1,2,2,3,3,1) */
  unsigned int facets_limit;
  /** vertices - стукрутра со всеми вершинами */
  struct vertices_s *vertices;
  /** facets - структура со всеми ребрами */
  struct facets_s *facets;
  /** массив максимальных и минимальных значений среди точек координат вершин */
  double minMax[6];
};

/*!
\brief Получение одномерного массива порядковых номеров вершин записанных
попарно \param[in] object Исходная структура с заполненными значениями из файла
\return[out] unsigned int Одномерный массив значений
*/
unsigned int *get_facets(struct object_s *object);

/*!
\brief Функция печати значений ребер
*/
void print_facets(unsigned int *facets, unsigned int facets_limit);

/*!
\brief Получение одномерного массива координат всех вершин записанных поочередно
\param[in] object Исходная структура с заполненными значениями из файла
\return[out] float Одномерный массив значений
*/
float *get_vertices(struct object_s *object);
/*!
\brief Функция печати значений вершин
*/
void print_vertices(float *vertices, unsigned int vertex_limit);

/*!
\brief Функция освобождения выделенной памяти под структуру объекта
*/
void free_object(struct object_s *object);

/*!
\brief Функция разбиения строки на подстроки
*/
char *s21_strtok(char *str, const char *delim);

/*!
\brief Функция получает и сохраняет в стуктуру номера вершин для каждого ребра
*/
int parse_facets(char *line, struct object_s *);

/*!
\brief Функция получает и сохраняет в стуктуру координаты каждой вершины в
порядке нахождения
*/
int parse_vertices(char *line, struct object_s *);

/*!
\brief Функция печати всех значений объекта
*/
void print_object(struct object_s object);

/*!
\brief Функция вывода строки по коду ошибки
*/
char *view_error(int i);

/*!
\brief Функция запуска парсинга файла и заполнения стуктуры объекта
*/
int parse_file(const char *file_path, struct object_s *object);

/*!
\brief Вспомогательная функция для чтения строки
*/
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

/*!
\brief Функция для нахождения максимального и минимального значения x,y,z
координаты вершины
*/
void minMax(double x, double y, double z, struct object_s *object);

/*!
\brief Функция вычисления значений для построения матрицы проекции объекта
*/
double *get_projection(struct object_s object);

/*!
\brief Вспомогательная функция нахождения максимального числа из трех
*/
double max_range(double, double, double);
/*!
\brief Функция преобразования всех координат соответсвующей оси вершин для
матрицы поворота
*/
void rotate(float *vert, struct object_s *object, int value, char direction);
/*!
\brief Функция преобразования всех координат соответсвующей оси вершин для
управления масштабом
*/
void scale_object(float *vert, struct object_s *object, double base_scale,
                  double new_scale);
/*!
\brief Функция преобразования всех координат соответсвующей оси вершин для
перемещение вдоль осей
*/
void move_object(float *vert, struct object_s *object, int value,
                 char direction);
/*!
\brief Функция приведения всех координат вершин к диапазону от -1 до +1
*/
void normalize_vertices(float *vert, struct object_s *object);
#endif  // CORE_PARSER_H_
