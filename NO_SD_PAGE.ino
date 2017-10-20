//Function for sending HTM page if SD isn't available
void internalHTMLsend(EthernetClient cl){
  cl.println(F("<!DOCTYPE html>"));
  cl.println(F("<html>"));
  cl.println(F("<head>")); 
  cl.println(F("<title>Danik's Game</title>"));
  cl.println(F("<body>"));
  cl.println(pl_num);
  cl.println();
  cl.println(main_state);
  for (byte i = 0; i < MAX_PLAYERS; i++) {
    cl.println(i);
    cl.println(buttons_time_stamps[i]);
  }
  cl.println(F("</body>"));
  cl.println(F("</html>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));
//  cl.println(F("<head>"));     
}
