#!/bin/bash
# submit42 - submit project to vogsphere with history

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
DIM='\033[2m'
BOLD='\033[1m'
RESET='\033[0m'

PROJECT=$1
REMOTE=$2
shift 2
MANUAL_DEPS=("$@")

if [ -z "$PROJECT" ] || [ -z "$REMOTE" ]; then
    echo -e "${RED}Usage:${RESET} submit42 <project> <remote> [extra-dependencies...]"
    echo -e "${DIM}Example: submit42 push_swap git@vogsphere.../uuid${RESET}"
    echo -e "${DIM}Symlinked dependencies are auto-detected${RESET}"
    exit 1
fi

# Check if project exists
if [ ! -d "$PROJECT" ]; then
    echo -e "${RED}Error:${RESET} Project folder '${YELLOW}$PROJECT${RESET}' not found"
    echo -e "${DIM}Available folders:${RESET}"
    ls -d */ 2>/dev/null | sed 's/^/  /'
    exit 1
fi

# Auto-detect symlinked dependencies
# Store as "target_folder:symlink_name"
AUTO_DEPS=()
declare -A DEP_RENAME  # target -> link_name
while IFS= read -r link; do
    target=$(readlink "$link")
    link_name=$(basename "$link")           # e.g., "libft"
    dep_name=$(basename "$target")          # e.g., "0_libft"
    if [ -d "$dep_name" ]; then
        AUTO_DEPS+=("$dep_name")
        DEP_RENAME["$dep_name"]="$link_name"
    fi
done < <(find "$PROJECT" -type l 2>/dev/null)

# Combine auto + manual deps, remove duplicates
DEPS=($(echo "${AUTO_DEPS[@]}" "${MANUAL_DEPS[@]}" | tr ' ' '\n' | sort -u))

# Check if dependencies exist
for dep in "${DEPS[@]}"; do
    if [ ! -d "$dep" ]; then
        echo -e "${RED}Error:${RESET} Dependency folder '${YELLOW}$dep${RESET}' not found"
        exit 1
    fi
done

ORIG_DIR=$(pwd)

echo -e "${BOLD}${CYAN}═══════════════════════════════════════════${RESET}"
echo -e "${BOLD}  📦 Project:${RESET}      ${GREEN}$PROJECT${RESET}"
if [ ${#AUTO_DEPS[@]} -gt 0 ]; then
    for dep in "${AUTO_DEPS[@]}"; do
        link_name="${DEP_RENAME[$dep]}"
        if [ "$dep" != "$link_name" ]; then
            echo -e "${BOLD}  🔗 Auto-detected:${RESET} ${YELLOW}${dep}${RESET} ${DIM}(as ${link_name})${RESET}"
        else
            echo -e "${BOLD}  🔗 Auto-detected:${RESET} ${YELLOW}${dep}${RESET}"
        fi
    done
fi
if [ ${#MANUAL_DEPS[@]} -gt 0 ]; then
    echo -e "${BOLD}  📎 Manual deps:${RESET}   ${YELLOW}${MANUAL_DEPS[*]}${RESET}"
fi
if [ ${#DEPS[@]} -eq 0 ]; then
    echo -e "${BOLD}  🔗 Dependencies:${RESET} ${DIM}none${RESET}"
fi
echo -e "${BOLD}${CYAN}═══════════════════════════════════════════${RESET}"

rm -rf /tmp/42submit
git clone . /tmp/42submit --quiet
cd /tmp/42submit

# Build filter-repo path arguments
PATHS="--path $PROJECT/"
for dep in "${DEPS[@]}"; do
    PATHS="$PATHS --path $dep/"
done

# Keep only commits touching project and its dependencies
echo -e "${DIM}Filtering history...${RESET}"
git filter-repo $PATHS --force --quiet 2>/dev/null || git filter-repo $PATHS --force

# Move dependencies into project folder (resolve symlink structure)
for dep in "${DEPS[@]}"; do
    if [ -d "$dep" ]; then
        # Use symlink name if available, otherwise use folder name
        link_name="${DEP_RENAME[$dep]:-$dep}"
        rm -rf "$PROJECT/$link_name"
        mv "$dep" "$PROJECT/$link_name"
        git add -A
        git commit --quiet -m "bundle $dep as $link_name"
    fi
done

# Flatten to root
shopt -s dotglob
mv "$PROJECT"/* . 2>/dev/null || true
rmdir "$PROJECT" 2>/dev/null || true
git add -A
git commit --quiet -m "flatten for submission" 2>/dev/null || true

# Verify files exist after processing
FILE_COUNT=$(git ls-files | wc -l | xargs)
if [ "$FILE_COUNT" -eq 0 ]; then
    echo -e "${RED}Error:${RESET} No files after processing. Something went wrong."
    cd "$ORIG_DIR"
    rm -rf /tmp/42submit
    exit 1
fi

# Show commits being submitted
echo ""
echo -e "${BOLD}${MAGENTA}📝 Commits to submit:${RESET}"
echo -e "${DIM}───────────────────────────────────────────${RESET}"

git --no-pager -c color.ui=always log \
    --format="%C(yellow)%h%C(reset) %C(bold)%s%C(reset) %C(dim)(%cr)%C(reset)" \
    --stat=80 \
    --stat-count=10 \
    --stat-graph-width=15 \
    --color=always | head -150

echo -e "${DIM}───────────────────────────────────────────${RESET}"

COMMIT_COUNT=$(git rev-list --count HEAD)
echo ""
echo -e "${BOLD}📊 Summary:${RESET}"
echo -e "   ${BLUE}Commits:${RESET} ${COMMIT_COUNT}"
echo -e "   ${BLUE}Files:${RESET}   ${FILE_COUNT}"
echo ""

# Confirm
echo -ne "${BOLD}Push to vogsphere? [y/N]${RESET} "
read -n 1 -r
echo ""

if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${DIM}Pushing...${RESET}"
    git push -f "$REMOTE" HEAD:main 2>&1 | sed "s/^/  /"
    echo ""
    echo -e "${GREEN}${BOLD}✓ Submitted ${PROJECT} (${COMMIT_COUNT} commits)${RESET}"
else
    echo -e "${RED}✗ Cancelled${RESET}"
fi

cd "$ORIG_DIR"
rm -rf /tmp/42submit