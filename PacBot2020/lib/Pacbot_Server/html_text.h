#ifndef HTML_TEXT_H
#define HTML_TEXT_H

const char DEFAULT_CONFIG_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <link rel="stylesheet" href="stylesheet.css">
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
                        <td><input type="text" name="stp" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Dynamic Coefficient (+):</span></td>
                        <td><input type="text" name="dyp" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Static Coefficient (-):</span></td>
                        <td><input type="text" name="stn" value="%.3f"></td>
                    </tr>
                    <tr>
                        <td><span>Dynamic Coefficient (-):</span></td>
                        <td><input type="text" name="dyn" value="%.3f"></td>
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
                <button type="submit" name="drive" value="1">Update</button>
            </div>
        </form>
    </div>

</body>
</html>)rawliteral";

#endif
