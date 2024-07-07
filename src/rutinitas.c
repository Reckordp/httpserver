#include "httpserver.h"
#include <stdio.h>

// NILAI KEMBALI
// 0 : Server tidak dapat accept
// 1 : Server dapat accept
// 2 : Error
int tunggu_membaca(keterangan_rutinitas* ket, FD_SET *membaca) {
  FD_ZERO(membaca);
  FD_SET(ket->hantar, membaca);

  int jumlah = ket->deret.fd_count >= 64 ? 63 : ket->deret.fd_count;
  for (size_t i = 0; i < jumlah; i++) {
    FD_SET(ket->deret.fd_array[i], membaca);
  }
  
  if (select(ket->terbesar + 1, membaca, NULL, NULL, NULL) < 0) return 2;
  return FD_ISSET(ket->hantar, membaca);
}

void pantau_client(keterangan_rutinitas* ket, FD_SET *membaca) {
  size_t jumlah = ket->deret.fd_count;
  if (!jumlah) return;
  for (size_t i = 0; i < jumlah; i++) {
    SOCKET client = ket->deret.fd_array[i];
    if (!FD_ISSET(client, membaca)) continue;

    u_long panjang;
    ioctlsocket(client, FIONREAD, &panjang);
    if (panjang < 1) continue;

    char *terima = malloc(panjang + 1);
    terima[0] = 0;
    size_t dibaca = recv(client, terima, panjang, 0);
    terima[dibaca] = 0;

    printf("%s\n", terima);
    send(client, "<h3>Welcome</h3>", 16, 0);

    closesocket(client);
    for (size_t j = i; j < jumlah; j++) {
      ket->deret.fd_array[j] = ket->deret.fd_array[j + 1];
    }
    ket->deret.fd_count--;
  }
  
}

void rutinitas_server(keterangan_rutinitas* ket) {
  FD_SET membaca;
  int baru = tunggu_membaca(ket, &membaca);
  if (baru != 2) pantau_client(ket, &membaca);
  if (baru != 1) return;
  
  struct sockaddr_in clientAddr;
  int ukuran = sizeof(struct sockaddr_in);
  SOCKET hantar = ket->hantar;
  int client = accept(hantar, (struct sockaddr*)&clientAddr, &ukuran);
  size_t tunjuk = ket->deret.fd_count;
  ket->deret.fd_array[tunjuk] = client;
  ket->deret.fd_count++;
  ket->terbesar = client;
}