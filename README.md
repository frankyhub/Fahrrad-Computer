<a name="oben"></a>

<div align="center">

|[:skull:ISSUE](https://github.com/frankyhub/Fahrrad-Computer/issues?q=is%3Aissue)|[:speech_balloon: Forum /Discussion](https://github.com/frankyhub/Fahrrad-Computer/discussions)|[:grey_question:WiKi](https://github.com/frankyhub/Fahrrad-Computer/wiki)||
|--|--|--|--|
| | | | |
|![Static Badge](https://img.shields.io/badge/RepoNr.:-%2049-blue)|<a href="https://github.com/frankyhub/Fahrrad-Computer/issues">![GitHub issues](https://img.shields.io/github/issues/frankyhub/Fahrrad-Computer)![GitHub closed issues](https://img.shields.io/github/issues-closed/frankyhub/Fahrrad-Computer)|<a href="https://github.com/frankyhub/Fahrrad-Computer/discussions">![GitHub Discussions](https://img.shields.io/github/discussions/frankyhub/Fahrrad-Computer)|<a href="https://github.com/frankyhub/Fahrrad-Computer/releases">![GitHub release (with filter)](https://img.shields.io/github/v/release/frankyhub/Fahrrad-Computer)|
|![GitHub Created At](https://img.shields.io/github/created-at/frankyhub/Fahrrad-Computer)| <a href="https://github.com/frankyhub/Fahrrad-Computer/pulse" alt="Activity"><img src="https://img.shields.io/github/commit-activity/m/badges/shields" />| <a href="https://github.com/frankyhub/Fahrrad-Computer/graphs/traffic"><img alt="ViewCount" src="https://views.whatilearened.today/views/github/frankyhub/github-clone-count-badge.svg">  |<a href="https://github.com/frankyhub?tab=stars"> ![GitHub User's stars](https://img.shields.io/github/stars/frankyhub)|
</div>



# Fahrrad-Computer
Fahrrad-Computer mit einem NANO, OLED-Display, Encoder und Hall-Sensor

![Bild](pic/aufbau.png)

![Bild](pic/gehaeuse.png)

![Bild](pic/aktivezeit.png) ![Bild](pic/aktuellegeschw.png)

![Bild](pic/durchnschittgeschw.png) ![Bild](pic/gesamtstrecke.png)

## Story

Diese Anleitung beschreibt einen Fahrrad-Computer. Auf einem OLED-Display werden Geschwindigkeit, Durchschnitts-Geschwindigkeit, Fahrzeit und Gesamtstrecke angezeigt. Mit einem Drehwinkelgeber werden die Seiten am Display ausgewählt. Auf Knopfdruck (Drehwinkelgeber) können die Werte gelöscht werden.

## Hardware

+ 1 x NANO
+ 1 x Drehwinkelgeber KY-040
+ 1 x OLED-Display SSD1306, 128x64 Pixel
+ 1 x Hall-Sensor-Modul KY-024
+ 1 x Speichenmagnet
+ 1 x 9-V-Batterie inklusive Batterieclip
+ 3 x Kunststoffgehäuse (ca. 2,5 cm x 3,5 cm x 6 cm)
+ Kleinmaterial, Kabelbinder, Klemmen, Schaltdraht

  
## Verdrahtung

NANO - Drehwinkelgeber KY-40:

| NANO  | KY-40 | 
| -------- | -------- | 
| GND  |  GND  |
| +5V  | +5V   |
| D5	  | SW  |
| D4  |  DT  |
| D3  | CLK   |
|  --- |  ---  |


NANO - Hall-Sensor-Modu KY-024:


| NANO  | KY-024 | 
| -------- | -------- | 
| GND  | GND   |
|  +5V		 |  +5V		  |
| D2  | D0   |
| ---  | ---   |

NANO - 9V-Batterie:

| NANO | 9V | 
| -------- | -------- | 
| GND	  |  GND	  |
|  Vin	 |  +5V  |
|  --- |  ---  |


## Schaltplan

![Bild](pic/Stromlaufplan.png)

---

<div style="position:absolute; left:2cm; ">   
<ol class="breadcrumb" style="border-top: 2px solid black;border-bottom:2px solid black; height: 45px; width: 900px;"> <p align="center"><a href="#oben">nach oben</a></p></ol>
</div>  

---


