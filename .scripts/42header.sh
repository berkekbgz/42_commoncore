#!/bin/bash

USER42="bkabagoz"
EMAIL42="bkabagoz@student.42istanbul.com"

INSERT_MODE=false
UPDATE_MODE=false

while getopts "iu" opt; do
    case $opt in
        i) INSERT_MODE=true ;;
        u) UPDATE_MODE=true ;;
        *)
            echo "Usage: $0 [-i|-u] <filename>" >&2
            echo "  -i    Insert header at beginning of file" >&2
            echo "  -u    Update 'Updated:' timestamp in existing header" >&2
            exit 1
            ;;
    esac
done
shift $((OPTIND-1))

FILEPATH="${1:-filename.c}"
FILENAME=$(basename "$FILEPATH")
TIMESTAMP=$(date "+%Y/%m/%d %H:%M:%S")

pad_to() {
    printf "%-${2}s" "$1"
}

generate_header() {
    local fname="$1"
    local created_ts="$2"
    local updated_ts="$3"

    local E="                                                                            "
    local L3="                                                        :::      ::::::::   "
    local L5="                                                    +:+ +:+         +:+     "
    local L7="                                                +#+#+#+#+#+   +#+           "

    local L4="$(pad_to "   $fname" 54):+:      :+:    :+:   "
    local L6="$(pad_to "   By: $USER42 <$EMAIL42>" 50)+#+  +:+       +#+        "
    local L8="$(pad_to "   Created: $created_ts by $USER42" 53)#+#    #+#             "
    local L9="$(pad_to "   Updated: $updated_ts by $USER42" 52)###   ########.fr       "

    cat << EOF
/* ************************************************************************** */
/*${E}*/
/*${L3}*/
/*${L4}*/
/*${L5}*/
/*${L6}*/
/*${L7}*/
/*${L8}*/
/*${L9}*/
/*${E}*/
/* ************************************************************************** */
EOF
}

generate_updated_line() {
    echo "/*$(pad_to "   Updated: $1 by $USER42" 52)###   ########.fr       */"
}

if [ "$UPDATE_MODE" = true ]; then
    [ ! -f "$FILEPATH" ] && { echo "Error: File not found: $FILEPATH" >&2; exit 1; }

    NEW_LINE=$(generate_updated_line "$TIMESTAMP")
    if grep -q "^/\*   Updated:" "$FILEPATH"; then
        sed -i "s|^/\*   Updated:.*\*/\$|$NEW_LINE|" "$FILEPATH"
    else
        echo "Warning: No 'Updated:' line found in $FILEPATH" >&2
        exit 1
    fi

elif [ "$INSERT_MODE" = true ]; then
    [ ! -f "$FILEPATH" ] && { echo "Error: File not found: $FILEPATH" >&2; exit 1; }

    if head -1 "$FILEPATH" | grep -q "^/\* \*\*\*"; then
        echo "Error: File already has a 42 header" >&2
        exit 1
    fi

    HEADER=$(generate_header "$FILENAME" "$TIMESTAMP" "$TIMESTAMP")
    { echo "$HEADER"; echo ""; cat "$FILEPATH"; } > "$FILEPATH.tmp"
    mv "$FILEPATH.tmp" "$FILEPATH"

else
    generate_header "$FILENAME" "$TIMESTAMP" "$TIMESTAMP"
fi
