/*
 * tinychat.c - [Starting code for] a web-based chat server.
 *
 * Based on:
 *  tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *      GET method to serve static and dynamic content.
 *   Tiny Web server
 *   Dave O'Hallaron
 *   Carnegie Mellon University
 */

// CS4400 Lab 7 Written by Tim Dorny u0829896

#include "csapp.h"
#include "dictionary.h"
#include "more_string.h"
#include <semaphore.h>

void doit(int fd, dictionary_t * convos, sem_t * s);
void *go_doit(void *coonfdp);
dictionary_t *read_requesthdrs(rio_t *rp);
void read_postquery(rio_t *rp, dictionary_t *headers, dictionary_t *d);
void parse_query(const char *uri, dictionary_t *d);
void serve_home_form(int fd, const char *pre_content);
void serve_form(int fd, const char *pre_content, dictionary_t *query, dictionary_t * convos, int url);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);
static void print_stringdictionary(dictionary_t *d);
static char *ok_header(size_t len, const char *content_type);
// Struct to pass into threads
typedef struct {
  int * connfdp;
  dictionary_t * convos;
  sem_t * s;
} convo_struct;


int main(int argc, char **argv)
{
  int listenfd, connfd;
  char hostname[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  /* Check command line args */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);

  /* Don't kill the server if there's an error, because
     we want to survive errors due to a client. But we
     do want to report errors. */
  exit_on_error(0);

  /* Also, don't stop on broken connections: */
  Signal(SIGPIPE, SIG_IGN);

  // Create dictionary struct,dictionary not case sensitive
  convo_struct cs;
  sem_t sem;
  cs.convos = make_dictionary(1, free);
  // Setup semaphore
  sem_init(&sem, 0, 1);
  // set sem to struct
  cs.s = &sem;

  while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    if (connfd >= 0) {
      Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE,
                  port, MAXLINE, 0);
      printf("Accepted connection from (%s, %s)\n", hostname, port);

      pthread_t th;
      // add connfdp to struct to pass to thread
      cs.connfdp = malloc(sizeof(int));
      *cs.connfdp = connfd;
      // Threading
      Pthread_create(&th, NULL, go_doit, (void *)&cs);
      Pthread_detach(th);
    }
  }
  free_dictionary(cs.convos);
}

void * go_doit(void * cs){
  // Get pointer to struct to pass to doit
  convo_struct * cs2 = (convo_struct *)cs;
  int connfd = *(int *)cs2->connfdp;
  free(cs2->connfdp);
  // DOIT
  doit(connfd, cs2->convos, cs2->s);
  Close(connfd);
  return NULL;
}

/*
 * doit - handle one HTTP request/response transaction
 */
void doit(int fd, dictionary_t * convos, sem_t * s)
{
  char buf[MAXLINE], *method, *uri, *version;
  rio_t rio;
  dictionary_t *headers, *query;
  int url = 0;

  /* Read request line and headers */
  Rio_readinitb(&rio, fd);
  if (Rio_readlineb(&rio, buf, MAXLINE) <= 0)
    return;
  printf("%s", buf);

  if (!parse_request_line(buf, &method, &uri, &version)) {
    clienterror(fd, method, "400", "Bad Request",
                "TinyChat did not recognize the request");
  } else {
    if (strcasecmp(version, "HTTP/1.0")
        && strcasecmp(version, "HTTP/1.1")) {
      clienterror(fd, version, "501", "Not Implemented",
                  "TinyChat does not implement that version");
    } else if (strcasecmp(method, "GET")
               && strcasecmp(method, "POST")) {
      clienterror(fd, method, "501", "Not Implemented",
                  "TinyChat does not implement that method");
    } else {
      headers = read_requesthdrs(&rio);

      /* Parse all query arguments into a dictionary */
      query = make_dictionary(COMPARE_CASE_SENS, free);
      parse_uriquery(uri, query);
      if (!strcasecmp(method, "POST"))
        read_postquery(&rio, headers, query);

      /* For debugging, print the dictionary */
      print_stringdictionary(query);

      // INPUT FROM STANDARD PROCESS
      char * username = dictionary_get(query, "content_name");
      char * chat = dictionary_get(query, "content_chat");
      char * conv_name = dictionary_get(query, "content_conv");

      // INPUT FROM URL
      char * urlname = dictionary_get(query, "user");
      char * urlconv = dictionary_get(query, "topic");
      char * urlchat = dictionary_get(query, "content");
      char * urlhost = dictionary_get(query, "host");

      // LOCK DICTIONARY
      sem_wait(s);

      // URL INPUT HANDLING ---------------------------------------------------------------

      // Add content to convo from urlchat (say?)
      if (urlname != NULL && urlconv != NULL){
        // If convo does not exist
        if (dictionary_get(convos, urlconv) == NULL) {
          char * tmp;
          if (urlchat == NULL){
            tmp = append_strings("", ": ", urlchat, "\r\n", NULL);
          }
          else{
            tmp = append_strings(urlname, ": ", urlchat, "\r\n", NULL);
          }
          char * concat = (char *) malloc(strlen(tmp) + 10);
          strcpy(concat, tmp);
          dictionary_set(convos, urlconv, concat);

        }
        // (if current convo does exist)
        else {
          char * tmp;
          if (urlchat == NULL){
            tmp = append_strings((char *)dictionary_get(convos, urlconv), urlname, ": ", "", "\r\n", NULL);
          }
          else{
            tmp = append_strings((char *)dictionary_get(convos, urlconv), urlname, ": ", urlchat, "\r\n", NULL);
          }
          char * concat = (char *) malloc(strlen(tmp) + 10);
          strcpy(concat, tmp);
          dictionary_set(convos, urlconv, concat);
        }
        url = 1;
        serve_form(fd, "lel", query, convos, url);
        // UNLOCK DICTIONARY
        sem_post(s);
        return;
      }


      // Content clone from server to server (import?)
      else if (urlconv != NULL && urlhost != NULL){
        // TODO: IMPLEMENT IMPORT (IT'S HARD D:)
      }
      // Return convo as plain text. (converstion?)
      else if (urlconv != NULL){
        char * chattext = (char *)dictionary_get(convos, urlconv);
        size_t len;
        //Send response headers to client
        // Make sure empty string is passed in case of NULL text
        if (chattext == NULL){
          chattext = "";
        }
        len = strlen(chattext);
        char * header = ok_header(len, "text/plain; charset=utf-8");
        Rio_writen(fd, header, strlen(header));
        printf("Response headers:\n");
        printf("%s", header);
        free(header);
        /* Send response body to client */
        Rio_writen(fd, chattext, len);
        // UNLOCK DICTIONARY
        sem_post(s);
        return;
      }

      // END URL INPUT HANDLING -------------------------------------------------------------

      // If chat was entered, add it to the dictionary
      // (if current convo does not exist)
      if (chat != NULL && username != NULL && conv_name != NULL){
        if (dictionary_get(convos, conv_name) == NULL && strlen(chat) > 0) {
          char * tmp = append_strings(username, ": ", chat, "\r\n", NULL);
          char * concat = (char *) malloc(strlen(tmp) + 10);
          strcpy(concat, tmp);
          dictionary_set(convos, conv_name, concat);

        }
        // (if current convo does exist)
        else if (strlen(chat) > 0) {
          char * tmp = append_strings((char *)dictionary_get(convos, conv_name), username, ": ", chat, "\r\n", NULL);
          char * concat = (char *) malloc(strlen(tmp) + 10);
          strcpy(concat, tmp);
          dictionary_set(convos, conv_name, concat);
        }
      }
      /* If name has not been given, go to home page */
      if (username == NULL && urlname == NULL){
        serve_home_form(fd, "Welcome to TinyChat");
      }
      // Otherwise send the main conversation form
      else {
        serve_form(fd, "lel", query, convos, url);
      }

      // UNLOCK DICTIONARY
      sem_post(s);

      /* Clean up */
      free_dictionary(query);
      free_dictionary(headers);
    }

    /* Clean up status line */
    free(method);
    free(uri);
    free(version);
  }
}

/*
 * read_requesthdrs - read HTTP request headers
 */
dictionary_t *read_requesthdrs(rio_t *rp)
{
  char buf[MAXLINE];
  dictionary_t *d = make_dictionary(COMPARE_CASE_INSENS, free);

  Rio_readlineb(rp, buf, MAXLINE);
  printf("%s", buf);
  while(strcmp(buf, "\r\n")) {
    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
    parse_header_line(buf, d);
  }
  return d;
}

void read_postquery(rio_t *rp, dictionary_t *headers, dictionary_t *dest)
{
  char *len_str, *type, *buffer;
  int len;
  len_str = dictionary_get(headers, "Content-Length");
  len = (len_str ? atoi(len_str) : 0);

  type = dictionary_get(headers, "Content-Type");
  buffer = malloc(len+1);
  Rio_readnb(rp, buffer, len);
  buffer[len] = 0;

  if (!strcasecmp(type, "application/x-www-form-urlencoded")) {
    parse_query(buffer, dest);
  }

  free(buffer);
}

static char *ok_header(size_t len, const char *content_type) {
  char *len_str, *header;
  header = append_strings("HTTP/1.0 200 OK\r\n",
                          "Server: TinyChat Web Server\r\n",
                          "Connection: close\r\n",
                          "Content-length: ", len_str = to_string(len), "\r\n",
                          "Content-type: ", content_type, "\r\n\r\n",
                          NULL);
  free(len_str);

  return header;
}
// Server home page for name and conversation ENTERING.....
void serve_home_form(int fd, const char *pre_content)
{
  size_t len;
  char *body, *header;

  body = append_strings("<html><body>\r\n",
                        "<p>Welcome to TinyChat friend!</p>",
                        "\r\n<form action=\"convo\" method=\"post\"",
                        " enctype=\"application/x-www-form-urlencoded\"",
                        " accept-charset=\"UTF-8\">\r\n",
                        "<p>Name: \n</p>",
                        "<input type=\"text\" name=\"content_name\">\r\n",
                        "<p>Desired Conversation: \n</p>",
                        "<input type=\"text\" name=\"content_conv\">\r\n",
                        "<p>\n</p>",
                        "<input type=\"submit\" value=\"Enter Chatroom\">\r\n",
                        "</form></body></html>\r\n",
                        NULL);

  len = strlen(body);

  /* Send response headers to client */
  header = ok_header(len, "text/html; charset=utf-8");
  Rio_writen(fd, header, strlen(header));
  printf("Response headers:\n");
  printf("%s", header);

  free(header);

  /* Send response body to client */
  Rio_writen(fd, body, len);

  free(body);
}

/*
 * serve_form - sends a form to a client
 */
void serve_form(int fd, const char *pre_content, dictionary_t *query, dictionary_t * convos, int url)
{
  size_t len;
  char *body, *header, *name, *conv, *nameenc, *convenc, *chat, *chatenc;
  // Naming issues, if names come from url they must be handled differently
  if (url == 0){
    name = dictionary_get(query, "content_name");
    conv = dictionary_get(query, "content_conv");
    // Encode text so it doesnt hurt the html
    nameenc = entity_encode(name);
    convenc = entity_encode(conv);
  }
  else {
    name = dictionary_get(query, "user");
    conv = dictionary_get(query, "topic");
    // encode
    nameenc = entity_encode(name);
    convenc = entity_encode(conv);
  }
  chat = dictionary_get(convos, conv);
  // If chat exists we can put it into html
  if (chat != NULL){
    // encode chat
    chatenc = entity_encode(chat);
    body = append_strings("<html><body>\r\n",
                        "<p>Welcome to TinyChat friend!</p>",
                        "\r\n<form action=\"convo\" method=\"post\"",
                        " enctype=\"application/x-www-form-urlencoded\"",
                        " accept-charset=\"UTF-8\">\r\n",
                        "<p>Logged in as: ", nameenc, "\n</p>",
                        "<p>Current Conversation: ", convenc, "\n</p>",
                        "<input type=\"text\" name=\"content_chat\">\r\n",
                        "<p>\n</p>",
                        "<input type=\"submit\" value=\"Send Message\">\r\n",
                        "<p> ---------- Chat ----------\n</p>",
                          "<PRE>", chatenc, "</PRE>",
                        "<input type=\"hidden\" name=\"content_name\" value=\"", nameenc, "\">\r\n",
                        "<input type=\"hidden\" name=\"content_conv\" value=\"", convenc, "\">\r\n",
                        "</form></body></html>\r\n",
                        NULL);
  }
  // if chat doesnt exist yet, send to blank conversation
  else {
    body = append_strings("<html><body>\r\n",
                        "<p>Welcome to TinyChat friend!</p>",
                        "\r\n<form action=\"convo\" method=\"post\"",
                        " enctype=\"application/x-www-form-urlencoded\"",
                        " accept-charset=\"UTF-8\">\r\n",
                        "<p>Logged in as: ", nameenc, "\n</p>",
                        "<p>Current Conversation: ", convenc, "\n</p>",
                        "<input type=\"text\" name=\"content_chat\">\r\n",
                        "<p>\n</p>",
                        "<input type=\"submit\" value=\"Send Message\">\r\n",
                        "<p> ---------- Chat ----------\n</p>",
                        "<input type=\"hidden\" name=\"content_name\" value=\"", nameenc, "\">\r\n",
                        "<input type=\"hidden\" name=\"content_conv\" value=\"", convenc, "\">\r\n",
                        "</form></body></html>\r\n",
                        NULL);
  }
  // cleanup
  len = strlen(body);

  /* Send response headers to client */
  header = ok_header(len, "text/html; charset=utf-8");
  Rio_writen(fd, header, strlen(header));
  printf("Response headers:\n");
  printf("%s", header);

  free(header);

  /* Send response body to client */
  Rio_writen(fd, body, len);

  free(body);
}

/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum,
         char *shortmsg, char *longmsg)
{
  size_t len;
  char *header, *body, *len_str;

  body = append_strings("<html><title>Tiny Error</title>",
                        "<body bgcolor=""ffffff"">\r\n",
                        errnum, " ", shortmsg,
                        "<p>", longmsg, ": ", cause,
                        "<hr><em>The Tiny Web server</em>\r\n",
                        NULL);
  len = strlen(body);

  /* Print the HTTP response */
  header = append_strings("HTTP/1.0 ", errnum, " ", shortmsg,
                          "Content-type: text/html; charset=utf-8\r\n",
                          "Content-length: ", len_str = to_string(len), "\r\n\r\n",
                          NULL);
  free(len_str);

  Rio_writen(fd, header, strlen(header));
  Rio_writen(fd, body, len);

  free(header);
  free(body);
}

static void print_stringdictionary(dictionary_t *d)
{
  int i, count;

  count = dictionary_count(d);
  for (i = 0; i < count; i++) {
    printf("%s=%s\n",
           dictionary_key(d, i),
           (const char *)dictionary_value(d, i));
  }
  printf("\n");
}
