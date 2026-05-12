@echo off
set PROJ_NAME=RandonHw
set PROJECT_ROOT=D:\STM32\%PROJ_NAME%
set SAFE_HOUSE=D:\STM32\BackupForCubeMX\%PROJ_NAME%
set LOG_FILE=%PROJECT_ROOT%\CubeMX_regenerate_log.txt

:: List your folders here separated by spaces
set FOLDERS=Utilities Drivers\Custom Docs

echo %date% %time%: Starting Backup... >> "%LOG_FILE%"

for %%f in (%FOLDERS%) do (
    if exist "%PROJECT_ROOT%\%%f" (
        :: /E: subdirectories including empty ones, /IS: overwrite same files
        robocopy "%PROJECT_ROOT%\%%f" "%SAFE_HOUSE%\%%f" /E /IS /NFL /NDL /NJH /NJS
        echo Backed up: %%f >> "%LOG_FILE%"
    )
)
