#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "mngMem.h"

ESP8266WebServer sv(80);
String data;
/* WiFi ESP truy cap.
const char *ssid_home = "VAN THU";
const char *pass_home = "vanthutruongchinh";
*/
// WiFi ESP phat'

const char *ssid = "bo thi nghiem roi tu do";
const char *pass = "12345678";

const char webpage[] PROGMEM = R"=====(
)=====";
// DIA. CHI IP ESP

IPAddress local_IP(192,168,1,3);
IPAddress gateway(192,168,1,2);
IPAddress subnet(255,255,255,0);
IPAddress DNS1(8, 8, 8, 8);
IPAddress DNS2(8, 8, 4, 4);
void setup()
{
  // tao. ra tram. phat' WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  // ket' noi' toi' WiFi
 /* WiFi.begin(ssid_home, pass_home);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
    delay(100);
  WiFi.config(local_IP, gateway, subnet, DNS1, DNS2);*/
  Serial.begin(115200);
  delay(100);
  sv.on("/index", []
        { sv.send(200, "text/html", readData("index.html")); });
// DOC. GIA; TRI. CAM BIEN'  
  sv.on("/d0.html", []
        { sv.send(200, "text/html", String(digitalRead(D0))); });
  sv.on("/d1.html", []
        { sv.send(200, "text/html", String(digitalRead(D1))); });
// NAP. FILE         
  sv.on(
      "/transFile", HTTP_ANY, []
      { sv.send(200, "text/html", ""
                                  "<meta charset='utf-8  '>"
                                  "<html>"
                                  "<head>"
                                  "<title>"
                                  "Truyền file HTML"
                                  "</title>"
                                  "</head>"
                                  "<body>"
                                  "trang web truyền FiLe"
                                  "<form method='POST' action='/transFile' enctype='multipart/form-data'>"
                                  "<input type='file' name='chon File'>"
                                  "<input type='submit' value='gui file'>"
                                  "</form>"
                                  "</body>"
                                  "</html>"); },
      []
      {
        HTTPUpload &file = sv.upload();
        if (file.status == UPLOAD_FILE_START)
        {
          clearData("index.html");
        }
        else if (file.status == UPLOAD_FILE_WRITE)
        {
          saveData("index.html", (const char *)file.buf, file.currentSize);
        }
      });
  sv.begin();
}
void loop()
{
  sv.handleClient();
}
