@echo on
:again
makedata.exe 
Assassin.exe < input.txt > gwx.out
standard.exe < input.txt > xioumu.out
fc gwx.out xioumu.out > nul
if not errorlevel 1 goto again
pause