#!/bin/bash

# Define the device name to search for
DEVICE_NAME="11-0048 EP0110M09"

# Read the input file
INPUT_FILE="/proc/bus/input/devices"

# Use awk and extract only the 'eventX' part
awk -v name="$DEVICE_NAME" '
    BEGIN { found = 0 }
    $1 == "N:" && $0 ~ name { found = 1 }   # Match Name line with the device name
    $1 == "H:" && found {
        for (i = 1; i <= NF; i++) {
            if ($i ~ /^event[0-9]+$/) { print $i; break }
        }
        found = 0
    }
' "$INPUT_FILE"

