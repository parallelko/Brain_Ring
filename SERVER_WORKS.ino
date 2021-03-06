byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte my_IP[] = {192,168,1,27};
IPAddress ip(my_IP);//РЎРІРѕР№ IP
#define SERVER_PORT 80
EthernetServer server(SERVER_PORT);
#define REQ_BUF_SIZE 128
char HTTP_req[REQ_BUF_SIZE] = {0}; // null terminated string
int reqIndex = 0;
#define MAX_LEN_STRING  128
#define MAX_LEN_REQUEST 256 // 512
String request = "";
#define GET           "GET /"
#define INDEX_STR     "index"
#define HTM_EXT       ".HTM"

void serverINIT() {
    Ethernet.begin(mac, ip);
    server.begin();
    delay(200);
}

void StrClear(char *str, char length) {
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

char StrContains(char *str, char *sfind) {
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);
  if (strlen(sfind) > len) {return 0;}
  
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {return 1;}
    } else {
        found = 0;
      }
    index++;
  }
  return 0;
}

// server answers
String makeAnswer(String content) {
  String s = "";
  s += F("HTTP/1.1 200 OK\n");
  s += F("Content-Type: ");
  s += content;
  s += F("\n");
  s += F("Connnection: close\n"); // "Connection: keep-alive\n"
  return s;
}

void sendHtmlAnswer(EthernetClient cl) {
  cl.println(makeAnswer(F("text/html")));
}

void sendErrorAnswer(char mess[], EthernetClient cl) {
  cl.print(mess);
  cl.println(F(" ERROR"));
  cl.println(F("Connnection: close"));
  cl.println();
}
 
 void parseRequest(EthernetClient cl) {
  // index request
  if (StrContains(HTTP_req, "GET / ") || StrContains(HTTP_req, "GET /index.htm")) {
       sendHtmlAnswer(cl);
       internalHTMLsend(cl);
    }
    else if (StrContains(HTTP_req, GET)) {
        if      (StrContains(HTTP_req, ".htm")) {
        }
    }
} // parseRequest ( )

void serverWorks2(EthernetClient sclient) {
  String strRequest = "";
  if (sclient) {
    boolean currentLineIsBlank = true;
    while (sclient.connected()) {      
      if (sclient.available()) {   // client data available to read
        char c = sclient.read();   // read 1 byte (character) from client

        /* limit the size of the stored received HTTP request
           buffer first part of HTTP request in HTTP_req array (string)
           leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1) */

        // make request (array)
        if (reqIndex < (REQ_BUF_SIZE - 1)) {
          HTTP_req[reqIndex] = c; // save HTTP request character
          reqIndex++;
        }
        
        // make request (String)
        /*
        if (request.length() < MAX_LEN_REQUEST) {
          if (c == '\n') {row++;}
          if (row != 2 && row != 3 && row != 4 && row != 5 && row != 6) {
            request += c;
          }
        }
        */

        if (strRequest.length() < MAX_LEN_STRING) {
          strRequest += c;
        }
        if (c == '\n' || strRequest.length() >= MAX_LEN_STRING) {
          if (strRequest.indexOf(F("GET")) == 0) {
            request += strRequest;
            strRequest = "";
          }
          else if (strRequest.indexOf(F("Authorization")) == 0) {
            request += strRequest;
            strRequest = "";
          }
          else {
            strRequest = "";
          }
        }

        /* last line of client request is blank and ends with \n
           respond to client only after last line received */

        if (c == '\n' && currentLineIsBlank) {
          //if (authMode == AUTH_OFF || (authMode == AUTH_ON && request.lastIndexOf(AUTH_HASH) > -1)) {     Authorization
            parseRequest(sclient); 
           //responseSend(sclient);
           // Reset buffer index and all buffer elements to 0
            reqIndex = 0;
            StrClear(HTTP_req, REQ_BUF_SIZE);
            request = "";
     
         /* Authorization 
          } 
          else { // if (authMode == AUTH_OFF || (authMode == AUTH_ON && request.lastIndexOf(AUTH_HASH) > -1))
              request = "";
              sclient.println(F("HTTP/1.0 401 Unauthorized"));
              sclient.println(F("WWW-Authenticate: Basic realm=\"Arduino Mega Server\""));
            }
          */ 
          break;
        }
        
        // every line of text received from the client ends with \r\n
        if (c == '\n') {
          
          /* last character on line of received text starting new line with next character read */
          currentLineIsBlank = true;
        } else if (c != '\r') {
            // a text character was received from client
            currentLineIsBlank = false;
          }
      } // if (client.available())
    } // while (client.connected())  
    delay(5); // give the web browser time to receive the data
    sclient.stop(); // close the connection
  } // if (client)  
} // serverWorks2( )

void serverWorks() { //РћР±СЂР°Р±РѕС‚РєР° СЃРѕРѕР±С‰РµРЅРёР№ Ethernet
  for (int sock = 0; sock < MAX_SOCK_NUM - 1; sock++) {
    EthernetClient sclient = server.available_(sock);
    serverWorks2(sclient);
  }
}

