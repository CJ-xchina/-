@echo off

del /s /q *.profraw
del /s /q report
del /s /q *.exe
del /s /q *.profdata

clang -fprofile-instr-generate -fcoverage-mapping game.c -o game.exe

game.exe < input-test1-1.txt
llvm-profdata merge -sparse default.profraw -o game.profdata 

for %%i in (2 3 4 5 6 7 8 9) do (
    game.exe < input-test%%i-1.txt
    llvm-profdata merge -sparse default.profraw game.profdata -o game.profdata
)

llvm-cov show -format html -output-dir report -instr-profile=game.profdata -show-branch-summary game.exe

timeout /t 1 >nul

pause