#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wejdan_Robot_Race";
const char* password = "12345678";

const int RED_LED = 26;
const int YELLOW_LED = 27;
const int GREEN_LED = 25;

WebServer server(80);

String currentStatus = "STOP";

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(RED_LED, red);
  digitalWrite(YELLOW_LED, yellow);
  digitalWrite(GREEN_LED, green);
}

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>

<meta charset="UTF-8">
<meta name="viewport"
content="width=device-width, initial-scale=1.0">

<title>Robot Race Control</title>

<style>

*{
  box-sizing:border-box;
}

body{
  margin:0;
  font-family:Arial,sans-serif;
  background:#080b10;
  color:white;
  overflow-x:hidden;
}

header{
  background:#0d1621;
  padding:20px;
  display:flex;
  justify-content:space-between;
  align-items:center;
}

header h1{
  margin:0;
  font-size:25px;
  letter-spacing:2px;
}

.connected{
  color:#41ef7a;
  font-size:15px;
}

/* TRAFFIC LIGHT */

.traffic-container{
  display:flex;
  justify-content:center;
  padding:28px 10px;
  background:linear-gradient(#284a67,#7892a7);
}

.traffic{
  background:#080808;
  border:5px solid #333;
  border-radius:35px;
  padding:18px;
  display:flex;
  gap:20px;
  box-shadow:0 10px 30px #000;
}

.light{
  width:80px;
  height:80px;
  border-radius:50%;
  border:none;
  cursor:pointer;
  opacity:.35;
  transition:.25s;
}

.light:hover{
  transform:scale(1.08);
}

.red{
  background:#ff1f32;
}

.yellow{
  background:#ffd633;
}

.green{
  background:#00ef65;
}

.red.active{
  opacity:1;
  box-shadow:0 0 35px #ff1f32;
}

.yellow.active{
  opacity:1;
  box-shadow:0 0 35px #ffd633;
}

.green.active{
  opacity:1;
  box-shadow:0 0 35px #00ef65;
}

/* ROAD */

.race-area{
  height:650px;
  position:relative;
  overflow:hidden;
  background:#111;
}

.road{
  position:absolute;
  width:78%;
  height:100%;
  left:11%;
  background:#292929;
  clip-path:polygon(
    34% 0,
    66% 0,
    100% 100%,
    0 100%
  );
}

/* ROAD LINES */

.center-line{
  position:absolute;
  left:50%;
  top:0;
  height:100%;
  width:9px;

  background:
  repeating-linear-gradient(
    to bottom,
    white 0,
    white 60px,
    transparent 60px,
    transparent 120px
  );
}

/* START LINE */

.start-line{
  position:absolute;
  bottom:90px;
  left:10%;
  width:80%;
  height:35px;

  background:
  repeating-linear-gradient(
    90deg,
    white 0,
    white 35px,
    black 35px,
    black 70px
  );

  border:3px solid white;
}

/* ROBOT CAR */

.robot{
  position:absolute;
  left:50%;
  bottom:145px;
  transform:translateX(-50%);
  transition:bottom 2s ease-in;
}

.robot-body{
  width:100px;
  height:65px;
  background:#555;
  border:3px solid #aaa;
  border-radius:20px;
  position:relative;
  box-shadow:0 0 20px #00ef65;
}

.robot-screen{
  position:absolute;
  width:45px;
  height:12px;
  background:#00ef65;
  top:15px;
  left:27px;
  border-radius:10px;
  box-shadow:0 0 15px #00ef65;
}

.wheel{
  position:absolute;
  width:25px;
  height:25px;
  background:#050505;
  border-radius:50%;
  bottom:-12px;
}

.w1{
  left:-12px;
}

.w2{
  right:-12px;
}

/* STATUS */

.status{
  position:absolute;
  right:5%;
  top:40px;
  width:180px;
  background:rgba(0,0,0,.85);
  border:1px solid #555;
  border-radius:20px;
  padding:20px;
}

.status h2{
  margin-top:0;
}

.stopText{
  color:#ff5360;
}

.readyText{
  color:#ffd84a;
}

.goText{
  color:#4cff82;
}

#state{
  font-size:22px;
  font-weight:bold;
}

/* FOOTER */

footer{
  text-align:center;
  padding:20px;
  color:#8793a0;
  background:#0d1621;
}

/* MOBILE */

@media(max-width:600px){

  header h1{
    font-size:20px;
  }

  .light{
    width:65px;
    height:65px;
  }

  .traffic{
    gap:12px;
  }

  .status{
    right:10px;
    width:145px;
    font-size:13px;
  }

}

</style>
</head>

<body>

<header>

<h1>ROBOT RACE CONTROL</h1>

<div class="connected">
ESP32 CONNECTED
</div>

</header>


<div class="traffic-container">

<div class="traffic">

<button
id="red"
class="light red active"
onclick="sendCommand('stop')">
</button>

<button
id="yellow"
class="light yellow"
onclick="sendCommand('ready')">
</button>

<button
id="green"
class="light green"
onclick="sendCommand('go')">
</button>

</div>

</div>


<div class="race-area">

<div class="road">

<div class="center-line"></div>

</div>


<div class="robot" id="robot">

<div class="robot-body">

<div class="robot-screen"></div>

<div class="wheel w1"></div>

<div class="wheel w2"></div>

</div>

</div>


<div class="start-line"></div>


<div class="status">

<h2>RACE STATUS</h2>

<p class="stopText">
STOP - GPIO 26
</p>

<p class="readyText">
READY - GPIO 27
</p>

<p class="goText">
GO - GPIO 25
</p>

<hr>

<div id="state">
STOP
</div>

</div>

</div>


<footer>

ESP32 Web-Controlled Robot Race System

</footer>


<script>

function sendCommand(command){

fetch('/' + command)
.then(response => response.text())
.then(data => {

document
.querySelectorAll('.light')
.forEach(light =>
light.classList.remove('active')
);

const robot =
document.getElementById('robot');

const state =
document.getElementById('state');


if(command === 'stop'){

document
.getElementById('red')
.classList.add('active');

state.innerHTML = "STOP";

robot.style.bottom = "145px";

}


if(command === 'ready'){

document
.getElementById('yellow')
.classList.add('active');

state.innerHTML = "READY";

}


if(command === 'go'){

document
.getElementById('green')
.classList.add('active');

state.innerHTML = "GO!";

robot.style.bottom = "520px";

}

});

}

</script>

</body>
</html>
)rawliteral";


void handleRoot() {

  server.send_P(
    200,
    "text/html; charset=utf-8",
    PAGE
  );
}


void setup() {

  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // Start with RED light
  setLights(HIGH, LOW, LOW);

  // ESP32 Access Point
  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Access Point Started");

  Serial.print("WiFi Name: ");
  Serial.println(ssid);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());


  server.on("/", handleRoot);


  server.on("/stop", [](){

    setLights(HIGH, LOW, LOW);

    currentStatus = "STOP";

    server.send(
      200,
      "text/plain",
      "STOP"
    );

  });


  server.on("/ready", [](){

    setLights(LOW, HIGH, LOW);

    currentStatus = "READY";

    server.send(
      200,
      "text/plain",
      "READY"
    );

  });


  server.on("/go", [](){

    setLights(LOW, LOW, HIGH);

    currentStatus = "GO";

    server.send(
      200,
      "text/plain",
      "GO"
    );

  });


  server.begin();

  Serial.println("Web Server Started");

}


void loop() {

  server.handleClient();
  
}