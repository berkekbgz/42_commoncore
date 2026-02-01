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
DEPS=("$@")

if [ -z "$PROJECT" ] || [ -z "$REMOTE" ]; then
    echo -e "${RED}Usage:${RESET} submit42 <project> <remote> [dependencies...]"
    echo -e "${DIM}Example: submit42 push_swap git@vogsphere.../uuid libft${RESET}"
    exit 1
fi

ORIG_DIR=$(pwd)

echo -e "${BOLD}${CYAN}═══════════════════════════════════════════${RESET}"
echo -e "${BOLD}  📦 Project:${RESET}      ${GREEN}$PROJECT${RESET}"
echo -e "${BOLD}  🔗 Dependencies:${RESET} ${YELLOW}${DEPS[*]:-none}${RESET}"
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
        rm -rf "$PROJECT/$dep"
        mv "$dep" "$PROJECT/"
        git add -A
        git commit --quiet -m "bundle $dep into $PROJECT"
    fi
done

# Flatten to root
shopt -s dotglob
mv "$PROJECT"/* . 2>/dev/null || true
rmdir "$PROJECT" 2>/dev/null || true
git add -A
git commit --quiet -m "flatten for submission" 2>/dev/null || true

# Show commits being submitted
echo ""
echo -e "${BOLD}${MAGENTA}📝 Commits to submit:${RESET}"
echo -e "${DIM}───────────────────────────────────────────${RESET}"

# Use git's built-in coloring
git -c color.ui=always log \
    --format="%C(yellow)%h%C(reset) %C(bold)%s%C(reset) %C(dim)(%cr)%C(reset)" \
    --stat \
    --stat-graph-width=15 \
    --color=always | head -100

echo -e "${DIM}───────────────────────────────────────────${RESET}"

COMMIT_COUNT=$(git rev-list --count HEAD)
FILE_COUNT=$(git ls-files | wc -l | xargs)
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