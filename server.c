/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmerzak <rmerzak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:50:48 by rmerzak           #+#    #+#             */
/*   Updated: 2022/06/04 19:51:03 by rmerzak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Serveur sockets TCP
* affichage de ce qui arrive sur la socket
*    socket_server port (port > 1024 sauf root)
*/

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char** argv )
{
  char datas[] = "hello\n";
  int    sockfd,newsockfd,clilen;
  char c;
  struct sockaddr_in cli_addr,serv_addr;
  
  if (argc!=2)
  {
    printf ("usage: socket_server port\n");
    exit(0);
  }
  printf ("server starting...\n");

  /* ouverture du socket */
  sockfd = socket (AF_INET,SOCK_STREAM,0);
  if (sockfd<0)
  {
    printf ("impossible d'ouvrir le socket\n");
    exit(0);
  }
  /* initialisation des parametres */
  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family       = AF_INET;
  serv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
  serv_addr.sin_port         = htons(atoi(argv[1]));

  /* effectue le bind */
  if (bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
  {
    printf ("impossible de faire le bind\n");
    exit(0);
  }
 /* ecoute */
 listen(sockfd,1);

 /* attente de connection d'un client */
 clilen = sizeof (cli_addr);
 newsockfd = accept (sockfd,(struct sockaddr*) &cli_addr, &clilen);
 if (newsockfd<0)
 {
   printf ("accept error\n");
   exit(0);
  }
 printf ("connection accepted\n");
 while (1)
  {
    while (read(newsockfd,&c,1)!=1);
    printf("%c",c); 
  }

  /*  attention il s'agit d'une boucle infinie 
   *  la socket n'est jamais ferme !
   */

  return 1;
}


