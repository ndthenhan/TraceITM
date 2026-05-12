#!/bin/bash
#run : chmod +x user_backup.sh in terminal to make it executable
# Copy user_restore path to CubeMX -> Project Manager -> User Code Generation -> Post generation -> Command: /home/thenhan/STM32/RandonHw/user_backup.sh
#PROJ_NAME=RandonHw #update in new projects
#PROJECT_ROOT="/home/thenhan/STM32/$PROJ_NAME"

# Automatically get the full path and the folder name
PROJECT_ROOT="$PWD"
PROJ_NAME=$(basename "$PROJECT_ROOT")


#SAFE_HOUSE="/home/thenhan/STM32/BackupForCubeMX/$PROJ_NAME"
SAFE_HOUSE="$PROJECT_ROOT/../BackupForCubeMX/$PROJ_NAME"
TIMESTAMP=$(date +%Y%m%d_%H%M)

# Add any new folders here, separated by a space
#FOLDERS=("Utilities" "Drivers/Custom" "Docs")
FOLDERS=("Utilities" )
mkdir -p "$SAFE_HOUSE"

for FOLDER in "${FOLDERS[@]}"; do
    if [ -d "$PROJECT_ROOT/$FOLDER" ]; then
        # -R ensures it keeps the directory structure inside the backup
        rsync -avR "$PROJECT_ROOT/./$FOLDER" "$SAFE_HOUSE/"
    fi
done

echo "$TIMESTAMP: Backed up folders for $PROJ_NAME" >> "$PROJECT_ROOT/CubeMX_regenerate_log.txt"
