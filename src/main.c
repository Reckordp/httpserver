#include "httpserver.h"

int bergulir;

void memulai_wsa() {
  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,2), &wsaData);
}

void sudahi_wsa() {
  WSACleanup();
}

WINBOOL kendali_signal(DWORD jenisCtrl) {
  if (jenisCtrl == CTRL_C_EVENT) {
    // Event lebih spesifik
    ExitProcess(0);
  }
  bergulir = 0;
}

int main(int argc, char const *argv[]) {
  keterangan_rutinitas *ketrut = malloc(sizeof(keterangan_rutinitas));
  memset(ketrut, 0, sizeof(keterangan_rutinitas));
  memulai_wsa();
  SOCKET socketServer = buat_socket_server();

  bergulir = 1;
  ketrut->hantar = socketServer;
  ketrut->terbesar = socketServer;
  SetConsoleCtrlHandler(kendali_signal, TRUE);

  while(bergulir) {
    rutinitas_server(ketrut);
  }

  sudahi_wsa();
  free(ketrut);
  return 0;
}
