#!/bin/bash

USER42="bkabagoz"
EMAIL42="bkabagoz@student.42istanbul.com.tr"

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

# Compose a 76-char line: left-aligned text + right-aligned ASCII art.
# If text is too long, trims art from the left at symbol boundaries.
compose_line() {
    local text="$1" art="$2" width=76
    local tlen=${#text} alen=${#art}
    local overflow=$((tlen + alen - width))
    if [ $overflow -gt 0 ]; then
        art="${art:$overflow}"
        while [ ${#art} -gt 0 ] && [ "${art:0:1}" != " " ]; do
            art="${art:1}"
        done
    fi
    printf "%-$((width - ${#art}))s%s" "$text" "$art"
}

generate_header() {
    local fname="$1"
    local created_ts="$2"
    local updated_ts="$3"

    local E="                                                                            "
    local L3="                                                        :::      ::::::::   "
    local L5="                                                    +:+ +:+         +:+     "
    local L7="                                                +#+#+#+#+#+   +#+           "

    local L4="$(compose_line "   $fname" ":+:      :+:    :+:   ")"
    local L6="$(compose_line "   By: $USER42 <$EMAIL42>" "+#+  +:+       +#+        ")"
    local L8="$(compose_line "   Created: $created_ts by $USER42" "#+#    #+#             ")"
    local L9="$(compose_line "   Updated: $updated_ts by $USER42" "###   ########.fr       ")"

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
    echo "/*$(compose_line "   Updated: $1 by $USER42" "###   ########.fr       ")*/"
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
