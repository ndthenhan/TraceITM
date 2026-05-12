@echo off
set PROJ_NAME=RandonHw
set PROJECT_ROOT=D:\STM32\%PROJ_NAME%
set SAFE_HOUSE=D:\STM32\BackupForCubeMX\%PROJ_NAME%
set LOG_FILE=%PROJECT_ROOT%\CubeMX_regenerate_log.txt

if exist "%SAFE_HOUSE%" (
    :: 1. Restore the files
    robocopy "%SAFE_HOUSE%" "%PROJECT_ROOT%" /E /IS /NFL /NDL /NJH /NJS
    echo %date% %time%: Restored folders deleted by CubeMX >> "%LOG_FILE%"

    :: 2. Clean up subfolders only
    for /d %%d in ("%SAFE_HOUSE%\*") do (
        rd /s /q "%%d"
    )
    echo %date% %time%: Cleaned up Safe House storage >> "%LOG_FILE%"
)
