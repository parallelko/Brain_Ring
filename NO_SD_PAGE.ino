//Function for sending HTM page if SD isn't available
void internalHTMLsend(EthernetClient cl){
  cl.println(F("<!DOCTYPE html>"));
  cl.println(F("<html>"));                                                  
  cl.println(F("<head>")); 
  cl.println(F("<title>Brain-Ring </title>"));
  cl.println(F("<meta http-equiv='refresh' content='2'>"));
  cl.println(F("<meta charset='utf-8'>"));
  cl.println(F("<style type='text/css'>"));
  cl.println(F(".a {"));
  cl.println(F("width: 17%;"));
  cl.println(F("padding: 5px;"));
  cl.println(F("float: left;"));
  cl.println(F("height: 35px;"));
  cl.println(F("margin: 3px;"));
  cl.println(F("background-color: RGB(5, 46, 98);}"));
  cl.println(F(".na {"));
  cl.println(F("width: 17%;"));
  cl.println(F("padding: 5px;"));
  cl.println(F("float: left;"));
  cl.println(F("height: 35px;"));
  cl.println(F("margin: 3px;"));
  cl.println(F("background-color: RGB(255, 0, 0);}"));
  cl.println(F("color: white;}"));
  cl.println(F(".nav {"));
  cl.println(F("height: 150px; }"));
  cl.println(F("</style>"));
  cl.println(F("</head>"));
  cl.println(F("<body>"));
  cl.println(F("<div class='nav' align='center'>"));
  if (main_state == PREPARE){
    cl.println(F("<h1>Подготовка</h1>"));
  } else if (main_state == NORMAL_STATE){
    cl.println(F("<h1>ВНИМАНИЕ ВОПРОС</h1>"));
  } else if (main_state == WAIT_FOR_ANSWER) {
    cl.println(F("<h1>можно отвечать</h1>"));
  } else if (main_state == ANSWER){
    cl.print(F("<h1>Отвечает Игрок:"));
    cl.print(pl_num);
    cl.println(F("</h1>"));
  }
   cl.print(F("<div class='"));
   if (buttonsStates[0] == UNPRESS) {
     cl.print(F("na"));
   } else {
     cl.print('a');
   }
   cl.println(F("' align='center'>Игрок 1</div>"));
   cl.print(F("<div class='"));
   if (buttonsStates[1] == UNPRESS) {
     cl.print(F("na"));
   } else {
     cl.print('a');
   }
   cl.println(F("' align='center'>Игрок 2</div>"));
   cl.print(F("<div class='"));
   if (buttonsStates[2] == UNPRESS) {
     cl.print(F("na"));
   } else {
     cl.print('a');
   }
   cl.println(F("' align='center'>Игрок 3</div>"));
   cl.print(F("<div class='"));
   if (buttonsStates[3] == UNPRESS) {
     cl.print(F("na"));
   } else {
     cl.print('a');
   }
   cl.println(F("' align='center'>Игрок 4</div>"));
   cl.print(F("<div class='"));
   if (buttonsStates[4] == UNPRESS) {
     cl.print(F("na"));
   } else {
     cl.print('a');
   }
   cl.println(F("' align='center'>Игрок 5</div>"));
   cl.println(F("</body>"));
   cl.println(F("</html>"));
}  
