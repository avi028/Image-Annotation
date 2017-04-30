#include "vec_io.c"
int hvec_read(const char *file_in, uint16_t **data, int *n);

int hvecs_read(const char *file_in, uint16_t **data, int *n, int *m);

int hvec_write(const char *file_in, const uint16_t *data, const int n);

int hvecs_write(const char *file_in, const uint16_t *data, const int n, const int m);

int hvec32_read(const char *file_in, uint32_t **data, int *n);

int hvecs32_read(const char *file_in, uint32_t **data, int *n, int *m);

int hvec32_write(const char *file_in, const uint32_t *data, const int n);

int hvecs32_write(const char *file_in, const uint32_t *data, const int n, const int m);

int fvec_read(const char *file_in, float **data, int *n, int *m);

int fvec_write(const char *file_in, const float *data, const int n, const int m);