#ifndef HTML_TEXT_H
#define HTML_TEXT_H

const char DEFAULT_CONFIG_STYLE[] PROGMEM = R"rawliteral(
* {
    box-sizing: border-box;
    font-family: 'bignoodletitlingregular';
}

@font-face {
    font-family: 'bignoodletitlingregular';
    src: url('https://irobotics.illinois.edu/big_noodle_titling-webfont.woff') format('woff2'),
         url('https://irobotics.illinois.edu/big_noodle_titling-webfont.woff') format('woff');
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

.col-1 { 
    display: inline-block;
    width: 39%; 
}

.col-2 {
    display: inline-block;
    width: 29%;
}

.col-3 {
    display: inline-block;
    width: 29%;
}

[class*="col-"] {
    text-align: center;
    float: left;
    padding: 20px;
    margin: 0.5%;
    border: 0.25rem solid #fff;
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

#control-section > div {
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

</body>
</html>)rawliteral";

#endif
