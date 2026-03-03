#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "Moto";
const char* password = "qwer1234";

String googleScriptURL = "https://script.google.com/macros/s/AKfycbwyEmo8FyuUvfjcFYI47LhfKNQh959k1Zg0RfnYq1lgLXA6imUY1nmq-wV3MUzivmCo/exec";

WebServer server(80);

#define MAX_LOGS 15

// ---- SYSTEM STATE ----
bool weightEntered = false;
float currentWeight = 0;
String systemStatus = "READY";

// ---- STORAGE ----
String inboundLogs[MAX_LOGS];
String outboundLogs[MAX_LOGS];
int inboundCount = 0;
int outboundCount = 0;

float totalInbound = 0;
float totalOutbound = 0;

// ================= GOOGLE =================

void sendToGoogleSheets(String type, float weight) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin(googleScriptURL);
  http.addHeader("Content-Type", "application/json");

  String jsonData = "{\"type\":\"" + type + "\",\"weight\":" + String(weight, 2) + "}";

  http.POST(jsonData);
  http.end();
}

// ================= LOG STORAGE =================

void addLog(String logs[], int &count, float weight) {
  String entry = String(weight, 2) + " kg";

  if (count < MAX_LOGS) {
    logs[count++] = entry;
  } else {
    for (int i = 1; i < MAX_LOGS; i++) {
      logs[i - 1] = logs[i];
    }
    logs[MAX_LOGS - 1] = entry;
  }
}

// ================= TABLE GENERATOR =================

String generateTable(String logs[], int count) {

  String table = "<table>";
  table += "<tr><th>#</th><th>Weight</th></tr>";

  for (int i = count - 1, row = 1; i >= 0; i--, row++) {
    table += "<tr><td>" + String(row) + "</td><td>" + logs[i] + "</td></tr>";
  }

  table += "</table>";
  return table;
}

// ================= SCADA WEBPAGE =================

String webpage() {

  String page = "<html><head>";
  page += "<meta http-equiv='refresh' content='2'>";
  page += "<style>";

  page += "body{margin:0;font-family:Consolas;background:#111;color:#00ffcc;}";
  page += ".header{background:#000;padding:15px;text-align:center;font-size:28px;font-weight:bold;border-bottom:2px solid #00ffcc;}";
  page += ".grid{display:grid;grid-template-columns:2fr 1fr 1fr;gap:20px;padding:20px;}";
  page += ".panel{background:#1b1b1b;padding:20px;border-radius:10px;box-shadow:0 0 15px #00ffcc;}";
  page += ".weight{font-size:60px;text-align:center;color:#00ffcc;}";
  page += ".status{font-size:18px;text-align:center;margin-top:10px;}";
  page += ".counter{font-size:24px;margin:10px 0;}";
  page += "table{width:100%;border-collapse:collapse;color:white;}";
  page += "th,td{padding:6px;border-bottom:1px solid #333;text-align:center;}";
  page += "th{background:#222;color:#00ffcc;}";
  page += "tr:hover{background:#333;}";
  page += "</style></head><body>";

  page += "<div class='header'>INDUSTRIAL WEIGHT SCADA PANEL</div>";
  page += "<div class='grid'>";

  // Digital Weight Display
  page += "<div class='panel'>";
  page += "<div class='weight'>" + String(currentWeight, 2) + " kg</div>";
  page += "<div class='status'>SYSTEM STATUS: " + systemStatus + "</div>";
  page += "</div>";

  // Inbound Panel
  page += "<div class='panel'>";
  page += "<h3 style='color:#00ff00;'>INBOUND</h3>";
  page += "<div class='counter'>Total: " + String(totalInbound, 2) + " kg</div>";
  page += generateTable(inboundLogs, inboundCount);
  page += "</div>";

  // Outbound Panel
  page += "<div class='panel'>";
  page += "<h3 style='color:#ff4444;'>OUTBOUND</h3>";
  page += "<div class='counter'>Total: " + String(totalOutbound, 2) + " kg</div>";
  page += generateTable(outboundLogs, outboundCount);
  page += "</div>";

  page += "</div></body></html>";

  return page;
}

void handleRoot() {
  server.send(200, "text/html", webpage());
}

// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();

  Serial.println("Enter weight:");
}

// ================= LOOP =================

void loop() {

  server.handleClient();

  if (Serial.available() > 0) {

    String input = Serial.readStringUntil('\n');
    input.trim();

    if (!weightEntered) {

      currentWeight = input.toFloat();

      if (currentWeight > 0) {
        weightEntered = true;
        systemStatus = "WAITING FOR TYPE";
        Serial.println("Enter 1 for INBOUND");
        Serial.println("Enter 2 for OUTBOUND");
      }

    } else {

      if (input == "1") {

        addLog(inboundLogs, inboundCount, currentWeight);
        totalInbound += currentWeight;
        sendToGoogleSheets("Inbound", currentWeight);
        systemStatus = "INBOUND LOGGED";

      } else if (input == "2") {

        addLog(outboundLogs, outboundCount, currentWeight);
        totalOutbound += currentWeight;
        sendToGoogleSheets("Outbound", currentWeight);
        systemStatus = "OUTBOUND LOGGED";

      }

      weightEntered = false;
      currentWeight = 0;
      Serial.println("Enter weight:");
    }
  }
}