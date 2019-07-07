import glob
import re

pattern = re.compile('\S.*\(.*\).*{')
with open("ESP_Firmware.h", 'w') as header:
    for fileName in glob.glob("*.ino"):
        header.write("//File: " + fileName + '\n')
        with open(fileName, 'r') as f:
            for line in f.readlines():
                search = pattern.match(line);
                if (search != None):
                    header.write(search.group(0)[:-2] + ';\n')
        header.write('\n')
