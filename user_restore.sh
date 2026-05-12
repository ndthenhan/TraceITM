#!/bin/bash

#run : chmod +x user_restore.sh in terminal to make it executable
# Copy user_restore path to CubeMX -> Project Manager -> User Code Generation -> Post generation -> Command: /home/thenhan/STM32/RandonHw/user_restore.sh

#PROJ_NAME=RandonHw # ! update new project's name in new projects
#PROJECT_ROOT="/home/thenhan/STM32/$PROJ_NAME"

# Automatically get the full path and the folder name
PROJECT_ROOT="$PWD"
PROJ_NAME=$(basename "$PROJECT_ROOT")

SAFE_HOUSE="$PROJECT_ROOT/../BackupForCubeMX/$PROJ_NAME" # backup folder is located one level up from project root, in BackupForCubeMX folder, with subfolder named after the project
TIMESTAMP=$(date +%Y%m%d_%H%M)

if [ -d "$SAFE_HOUSE" ]; then
    # Copies everything from the safe house back into project root
    rsync -av "$SAFE_HOUSE/" "$PROJECT_ROOT/"
    echo "$TIMESTAMP: Restored folders deleted by CubeMX" >> "$PROJECT_ROOT/CubeMX_regenerate_log.txt"
fi

# After restoring, remove the subfolders in the safe house to save space, 
# but keep the $SAFE_HOUSE directory itself so you can see the project was modified.
find "$SAFE_HOUSE" -mindepth 1 -maxdepth 1 -type d -exec rm -rf {} +



#DESTINATION="$BACKUP_ROOT/pre_gen_$TIMESTAMP"
#DESTINATION="$BACKUP_ROOT"
# Create backup directory
#mkdir -p "$DESTINATION"

# Backup the Core and App folders (where your custom code usually lives)
# Add or remove folders as needed
#rsync -av "$PROJECT_DIR/Utilities"  "$DESTINATION/"
#if [ -d "$BACKUP_DIR" ]; then
#    rsync -av "$BACKUP_DIR/" "$PROJECT_DIR/"
#    echo "Restore complete: $(date)" >> "$PROJECT_DIR/CubeMX_regenerate_log.txt"
#else
#    echo "Restore failed: Backup folder not found" >> "$PROJECT_DIR/CubeMX_regenerate_log.txt"
#fi


#echo "$TIMESTAMP - Restore folder completed to $DESTINATION" >> "$PROJECT_DIR/CubeMX_regenerate_log.txt"
