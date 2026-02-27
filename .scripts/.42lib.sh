#!/bin/bash
# .42lib.sh - shared library for 42 scripts
# Source this file, do not execute directly.

# ── Colors ────────────────────────────────────────────────────────────────────
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
DIM='\033[2m'
BOLD='\033[1m'
RESET='\033[0m'

# ── Paths ─────────────────────────────────────────────────────────────────────
ORIG_DIR=$(pwd)
SCRIPTS_DIR="$ORIG_DIR/.scripts"
STATE_FILE="$SCRIPTS_DIR/.42state"

# ── Remote resolution ─────────────────────────────────────────────────────────
# Usage: get_remote <project>
# Returns the vogsphere URL for the project from .42state
get_remote() {
    local project="$1"
    if [ ! -f "$STATE_FILE" ]; then
        echo -e "${RED}Error:${RESET} No state file found. Run register42 first." >&2
        return 1
    fi
    local url
    url=$(grep "^${project}[[:space:]]" "$STATE_FILE" 2>/dev/null | awk '{print $2}')
    if [ -z "$url" ]; then
        echo -e "${RED}Error:${RESET} No remote found for '${YELLOW}${project}${RESET}'" >&2
        echo -e "${DIM}Run: register42 $project git@vogsphere.../uuid${RESET}" >&2
        return 1
    fi
    echo "$url"
}

# ── State read ────────────────────────────────────────────────────────────────
# Usage: state_get_hash <project>
#        state_get_symmap <project>
state_get_hash() {
    local h
    h=$(grep "^$1 " "$STATE_FILE" 2>/dev/null | awk '{print $3}')
    [ "$h" = "-" ] && echo "" || echo "$h"
}

state_get_symmap() {
    local m
    m=$(grep "^$1 " "$STATE_FILE" 2>/dev/null | awk '{print $4}')
    [ "$m" = "-" ] && echo "" || echo "$m"
}

# ── State write ───────────────────────────────────────────────────────────────
# Usage: state_write <project> <remote> <hash|-> <symmap|->
state_write() {
    local project="$1" remote="$2" hash="$3" symmap="$4"
    mkdir -p "$SCRIPTS_DIR"
    touch "$STATE_FILE"
    if grep -q "^$project " "$STATE_FILE" 2>/dev/null; then
        sed -i "s|^$project .*|$project $remote $hash $symmap|" "$STATE_FILE"
    else
        echo "$project $remote $hash $symmap" >> "$STATE_FILE"
    fi
}

# ── Symlink detection ─────────────────────────────────────────────────────────
# Populates globals: AUTO_DEPS, DEP_RENAME, SYMLINK_ORIGINS
# Call init_dep_scan first, then scan_for_deps <dir> iteratively.
init_dep_scan() {
    AUTO_DEPS=()
    unset DEP_RENAME SYMLINK_ORIGINS SEARCHED
    declare -gA DEP_RENAME
    declare -gA SYMLINK_ORIGINS
    declare -gA SEARCHED
}

scan_for_deps() {
    local dir="$1"
    [ -d "$dir" ] || return
    [[ -n "${SEARCHED[$dir]}" ]] && return
    SEARCHED["$dir"]=1

    while IFS= read -r link; do
        local target_abs
        target_abs=$(realpath "$link" 2>/dev/null) || continue
        [ -d "$target_abs" ] || continue

        local target_rel="${target_abs#${ORIG_DIR}/}"
        [[ "$target_rel" == */* ]] && continue
        [[ "$target_rel" == "$PROJECT" ]] && continue
        [[ "$target_rel" == "." ]] && continue

        local already=false
        for d in "${AUTO_DEPS[@]}" "${MANUAL_DEPS[@]:-}"; do
            [[ "$d" == "$target_rel" ]] && already=true && break
        done
        $already && continue

        local link_name
        link_name=$(basename "$link")
        local link_abs
        link_abs="$(realpath -m "$(dirname "$link")" 2>/dev/null || echo "$ORIG_DIR/$(dirname "$link")")/$(basename "$link")"
        local link_rel="${link_abs#${ORIG_DIR}/}"

        AUTO_DEPS+=("$target_rel")
        DEP_RENAME["$target_rel"]="$link_name"
        SYMLINK_ORIGINS["$target_rel"]="$link_rel"
    done < <(find "$dir" -type l 2>/dev/null)
}

run_dep_scan() {
    local project="$1"
    init_dep_scan
    scan_for_deps "$project"
    local prev_count=0
    while [ "${#AUTO_DEPS[@]}" -gt "$prev_count" ]; do
        prev_count="${#AUTO_DEPS[@]}"
        for dep in "${AUTO_DEPS[@]}"; do
            scan_for_deps "$dep"
        done
    done
}

# ── Build symlink map string from current scan ────────────────────────────────
build_symlink_map() {
    if [ "${#AUTO_DEPS[@]}" -eq 0 ]; then
        echo "-"
        return
    fi
    local parts=()
    for dep in "${AUTO_DEPS[@]}"; do
        parts+=("${SYMLINK_ORIGINS[$dep]}:${dep}")
    done
    (IFS=,; echo "${parts[*]}")
}

# ── Git helpers ───────────────────────────────────────────────────────────────
git_push_state() {
    git push origin main --quiet 2>/dev/null || \
        echo -e "${YELLOW}⚠ State saved locally but GitHub push failed — run 'git push' manually${RESET}"
}

git_commit_state() {
    local msg="$1"
    git add "$STATE_FILE" 2>/dev/null || true
    git commit --quiet -m "$msg" 2>/dev/null || true
}
