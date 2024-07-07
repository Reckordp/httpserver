#include "httpserver.h"
#include <stdio.h>

struct in_addr* cari_alamat_ip() {
  char nama[1024];
  gethostname(nama, sizeof(nama));
  struct hostent* deret = gethostbyname(nama);
  return (struct in_addr*)(deret->h_addr);
}

SOCKET buat_socket() {
  return socket(AF_INET, SOCK_STREAM, 0);
}

void properti_socket(SOCKET hantar, struct in_addr* ip) {
  struct sockaddr_in lembar;
  ZeroMemory(&lembar, sizeof(lembar));
  lembar.sin_family = AF_INET;
  lembar.sin_addr.s_addr = ip->s_addr;
  lembar.sin_port = htons(PORTHTTP);
  
  u_long val = 1;
  bind(hantar, (const struct sockaddr*)&lembar, sizeof(lembar));
  ioctlsocket(hantar, FIONBIO, &val); // (Optional)Non-Blocking
  listen(hantar, BATAS_CLIENT);
  printf("Listen %s:%d\n", inet_ntoa(*ip), PORTHTTP);
}

SOCKET buat_socket_server() {
  struct in_addr* ip = cari_alamat_ip();
  SOCKET hantar = buat_socket();
  properti_socket(hantar, ip);
  return hantar;
}