#ifndef HTML_TEXT_H
#define HTML_TEXT_H

#define WOFF2_LEN   14024
#define ICON_LEN     4286

const char ROOT_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="/config_stylesheet.css">
    <title></title>
</head>
<body>
    <div class="row">
        <div id="header" align="center">
            <h1 style="font:bold 25px ">iRobotics PacBot Control Station</h1>
        </div>

    </div>
    <div class="row">
        <div class="col-1 flexVert" id="batteryDisp" style="padding-bottom: 0.75rem;">
            <center>
                <div class="battery">
                    <div id="battTop" style="width: 35%; background-color: #ccc; min-height: 1.25rem; font-size: 0.1rem; border: 2px solid #333;">
                        &nbsp;
                    </div>
                    <div id="battBottom" style="width: 80%; background-color: #ccc; height: 12rem; border: 2px solid #333;">
                        <div id="battBackground" style="position:relative; margin: 0.75rem; max-height: 90%; background-color:#666;">
                            <div id="batteryCapacity" style="position:absolute; bottom: -10rem; height: 10rem; width: 100%; background-color:#0a0;">
                                
                            </div>
                            <span id="batt_voltage" style="position:absolute; bottom: -10rem; left: 0.25rem; font-size: 2.5rem;">12.6v</span>
                        </div>
                    </div>
                </div>
            </center>
        </div>

        <div class="col-2 flexVert" id ="motorDisp">
            <div class="motor">
                Motor 0: <div style="position: relative; display:inline-block; background-color: #eee; width: 10rem; height: 1.5rem;">
                    <div style="position:absolute; left: 5rem; top: -0.5rem; height:2.5rem; background-color: #000; width: 0.25rem; z-index: 1;"></div>
                    <div id="motor0Val" style="position:absolute; left: 5rem; height: 1.5rem; background-color: #f00; width: 1rem; z-index: 0"></div>
                </div>
                <span id=Motor0RPM">0 RPM</span>
            </div>
            <div class="motor">
                Motor 1:
                <div style="position: relative; display:inline-block; background-color: #eee; width: 10rem; height: 1.5rem;">
                    <div style="position:absolute; left: 5rem; top: -0.5rem; height:2.5rem; background-color: #000; width: 0.25rem; z-index: 1;"></div>
                    <div id="motor1Val" style="position:absolute; left: 5rem; height: 1.5rem; background-color: #f00; width: 0rem; z-index: 0"></div>
                </div> 
                <span id=Motor1RPM">0 RPM</span>
            </div>
            <div class="motor">
                Motor 2: <div style="position: relative; display:inline-block; background-color: #eee; width: 10rem; height: 1.5rem;">
                    <div style="position:absolute; left: 5rem; top: -0.5rem; height:2.5rem; background-color: #000; width: 0.25rem; z-index: 1;"></div>
                    <div id="motor2Val" style="position:absolute; right: 5rem; height: 1.5rem; background-color: #f00; width: 2rem; z-index: 0"></div>
                </div>
                <span id=Motor2RPM">0 RPM</span>
            </div>
            <div class="motor">
                Motor 3: <div style="position: relative; display:inline-block; background-color: #eee; width: 10rem; height: 1.5rem;">
                    <div style="position:absolute; left: 5rem; top: -0.5rem; height:2.5rem; background-color: #000; width: 0.25rem; z-index: 1;"></div>
                    <div id="motor3Val" style="position:absolute; left: 5rem; height: 1.5rem; background-color: #f00; width: 3rem; z-index: 0"></div>
                </div>
                <span id=Motor3RPM">0 RPM</span>
            </div>
        </div>

        <div class="col-3" id="direction">
            <img id="dir-pacman" src="https://ui-ex.com/images/pacman-transparent-gif-5.gif" style="transform: rotate(0deg);"/>
        </div>

        <div class="col-4" id="control-section">
            <div id="currentActivity">
                Current Activity
            </div>
            <div id="manualSwitch">
                Manual Control Switch
            </div>
            <div id="Update">
                Update Firmware
            </div>
            <a href="/config">
                <div id="Configure">
                    Tuning & Control
                </div>
            </a>
        </div>
    </div>

    <div class="row">
            <div class="col-1a" style="display:flex; flex-direction: column;">
                <div style="background-color: #ccc; width: 90%; margin: 1rem auto; vertical-align: baseline;">
                    Remaining: <span id="timer" style="color:darkslategray;text-shadow: 0.1rem 0.1rem #113758;">3:00</span>
                </div>
                
                <div style="background-color: #ccc;height: 8rem; margin: 1rem;">
                    More data?
                </div>
            </div>

            <div class="col-23">
                <div id="pacbot_frame">
                    <div id="pacbot" style="transform: rotate(10deg);">
                        <div class="smallArrow" id="gameArrow" style="transform: rotate(-135deg)"></div>
                        <div class="largeArrow" id="orientationArrow" style="transform: rotate(-135deg)"></div>
                        <div class="TOF TOF_Horiz" id="TOF_0" style="width: 3rem;"></div>
                        <div class="TOF TOF_Horiz" id="TOF_1" style="width: 6rem;"></div>
                        <div class="TOF TOF_Vert" id="TOF_2" style="height: 2rem;"></div>
                        <div class="TOF TOF_Vert" id="TOF_3" style="height: 4rem;"></div>
                    </div>
                </div>
            </div>
    
            <div class="col-4" id="logging">
                <div id="logger" class="console"></div>
            </div>
        </div>
    <style>
    .col-1 { 
        width: 9%; 
    }

    .col-2 {
        width: 27%;
    }

    .col-3 {
        width: 21%;
    }

    .col-1a {
        width: 19%;
    }

    .col-23 {
        width: 39%;
    }

    .col-4 {
        width: 39%;
    }
    </style>
</body>
</html>)rawliteral";

const char DEFAULT_CONFIG_STYLE[] PROGMEM = R"rawliteral(
* {
    box-sizing: border-box;
    font-family: 'bignoodletitlingregular';
}

@font-face {
    font-family: 'bignoodletitlingregular';
    src: url('bignoodle.woff2') format('woff2');
    font-weight: normal;
    font-style: normal;
}

h1 {
    margin-top: 0;
    margin-bottom: 0;
    font-family: 'bignoodletitlingregular';
    font-size: 10rem;
    color: #F38022;
    text-shadow: 0.25rem 0.25rem #113758;
                        
}

#header {
    display:flex;
    justify-content:center;
}

body {
    background-color: #121F26;
}

[class*="col-"] {
    text-align: center;
    float: left;
    padding: 20px;
    margin: 0.5%;
    border: 0.25rem solid #fff;
}

.config_row {
    background-color: #ccc;
    vertical-align: middle;
}

.row::after {
    content: "";
    clear: both;
    display: table;
}

.flexVert {
    display:flex;
    flex-flow: column nowrap;
    justify-content:space-evenly;
    align-items: stretch;
}

.motor {
    background-color: #aaa;
    margin: 5px;
    display: flex;
    flex-direction: row;
    justify-content: space-around;
    align-items: center;
    font-size: 2.5rem;
}

.motor > span {
    font-size: 2.5rem;
}

img {
    max-width: 100%;
    max-height: 100%;
}

#dir-pacman {
    height: 13rem!important;
    width: auto;
}
[class*="col-"] img {
    padding: 2rem;
}

#control-section div {
    background-color: #bbb;
    margin: 0.5rem;
    font-size: 2.5rem;
}

.noDisp {
    border: 0!important;
}

.console
{
    overflow: auto;
    height: 20rem;
    background: #ddd;
    border: 1px solid #ccc;
    padding: 5px;
}

#pacbot_frame {
    height: 20rem;
    padding: 1rem;
    background-color: #ccc;
    display: flex;
    justify-content: center;
}

#pacbot {
    position: relative;
    margin: auto;
    width: 10rem;
    height: 10rem;
    background-color: #13294b;
    border-radius: 3rem;
    
}

.TOF {
    position: absolute;
    background-color: #F38022;
}

.TOF_Horiz {
    height: 2rem;
}

.TOF_Vert {
    width: 2rem;
}

#TOF_0 {
    top: 4rem;
    right: 10rem;
}

#TOF_1 {
    top: 4rem;
    left: 10rem;
}

#TOF_2 {
    left: 4rem;
    top: 10rem;
}

#TOF_3 {
    left: 4rem;
    bottom: 10rem;
}

.smallArrow {
    border: solid #ccc;
    border-width: 0 0.5rem 0.5rem 0;
    display: inline-block;
    padding: 0.5rem;
  }

  .largeArrow {
    border: solid #F38022;
    border-width: 0 0.75rem 0.75rem 0;
    display: inline-block;
    padding: 1rem;

  }

  #gameArrow {
    position: absolute;
    top: 1rem;
    left: 4.25rem;
  }

  #orientationArrow {
    position: absolute;
    top: 3.5rem;
    left: 3.5rem;
  }

  .LogItem {
      display: flex;
      justify-content: space-between;
  }

  .LogItem > span {
      font-size: 2rem;
  }
)rawliteral";

const char DEFAULT_CONFIG_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="/config_stylesheet.css">
    <title></title>
</head>
<body>
    <div class="row">
        <div id="header" align="center">
            <h1 style="font:bold 25px ">iRobotics PacBot Control Station</h1>
        </div>
    </div>

    <div class="row config_row">
        <form action="/get" method="get" autocomplete="off" name="drive1">
            <div class="col-1 friction_config">
                <legend>Friction Compensation</legend>
                <table>
                    <tr>
                        <td><span>Static Coefficient (+):</span></td>
                        <td><input type="text" name="sp" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Dynamic Coefficient (+):</span></td>
                        <td><input type="text" name="dp" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Static Coefficient (-):</span></td>
                        <td><input type="text" name="sn" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Dynamic Coefficient (-):</span></td>
                        <td><input type="text" name="dn" value="%.3f"></td>
                    </tr>
                </table>
            </div>
            <div class="col-2 flexVert">
                <legend>Velocity Controller</legend>
                <table>
                    <tr>
                        <td><span>Kp</span></td>
                        <td><input type="text" name="kp" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Ki</span></td>
                        <td><input type="text" name="ki" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Kd</span></td>
                        <td><input type="text" name="kd" value="%.3f"></td>
                    </tr>
                </table>
            </div>

            <div class="col-3 flexVert">
                <button type="submit" name="dv" value="1">Update</button>
            </div>
        </form>
    </div>

    <style>
    .col-1 { 
        display: inline-block;
        width: 39%%; 
    }
    .col-2 {
        display: inline-block;
        width: 29%%;
    }
    .col-3 {
        display: inline-block;
        width: 29%%;
    }
    form button {
        font-size:3rem;
    }
    form span {
        font-size: 2rem!important;
    }
    form input {
        font-size:1.5rem;
    }
    form legend {
        font-size:3rem;
        color: #113758;
    }
    </style>
</body>
</html>)rawliteral";

#endif
