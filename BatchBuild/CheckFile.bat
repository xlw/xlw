@IF "%3" == "" IF EXIST %1 SET %2=%1
@IF "%3" == "NOPATH" IF EXIST %1 SET %2=%~1
