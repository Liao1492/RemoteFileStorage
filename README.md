# RemoteFileStorage
A simple remote storage built with C++

RemoteFileStorage
-Include 2 header file with the function.
-Compile client.cpp with the other's file(commands,menuInterface) in the same directory.
-First 2 inputs are server address and port number.
-Function supported ( UPLOAD,DOWNLOAD,RETRIEVE,EXIT).Not case sensitive.

ALLERT : I tried to solve the problem about spacing. For Upload,download and retrieve, 
we can't have inizial spacing but the extra spaces between command and data file is handled. For the exit command,
please not include any blank space because I could not find any TRIM function for string in C++ except for the 
"boost" library which is not incuded in the STL.

In Upload and Download I have included some usefull information such as the Sending status,file status, line 
sent/received, completition of the process meanwhile for retrieve,exit and default function, for simplicity of the code,
i have simply print out the message from the server.

For upload,the file must be in the same directory as the CPP or exe file of client.

The downloaded file has the string "_downloaded_" attached to differentiate it from the files we want to upload.

-Included screen clear ( only tested on windows because I do not own a MacBook or any pc with linux).
