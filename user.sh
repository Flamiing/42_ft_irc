#!/bin/bash

ARG1="pass"
ARG2=2042

COMMAND="HELP"
COMMAND1="QUIT"


nc -c localhost $ARG2 &

echo "PASS $ARG1" && \
echo "NICK guilmira" && \
echo "USER guilmira * * : Guille Mira" \
&& echo $COMMAND \
| nc localhost $ARG2







#Notas Guille
#export /Applications/Visual\ Studio\ Code\ 2.app/Contents/MacOS/Electron
#alias vscode="/Applications/Visual\ Studio\ Code\ 2.app/Contents/MacOS/Electron"