#include <winsock2.h>
#include <windows.h>

#define PORTHTTP 80
#define BATAS_CLIENT FD_SETSIZE

typedef struct {
  SOCKET hantar;
  FD_SET deret;
  int terbesar;
} keterangan_rutinitas;

SOCKET buat_socket_server();
void rutinitas_server(keterangan_rutinitas*);