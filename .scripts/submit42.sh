#!/bin/bash
# submit42 - submit project to vogsphere with history

set -e

PROJECT=$1
REMOTE=$2
shift 2
DEPS=("$@")

if [ -z "$PROJECT" ] || [ -z "$REMOTE" ]; then
    echo "Usage: submit42 <project> <remote> [dependencies...]"
    echo "Example: submit42 push_swap git@vogsphere.../uuid libft"
    exit 1
fi

ORIG_DIR=$(pwd)

echo "═══════════════════════════════════════════"
echo "  Submitting: $PROJECT"
echo "  Dependencies: ${DEPS[*]:-none}"
echo "═══════════════════════════════════════════"

rm -rf /tmp/42submit
git clone . /tmp/42submit --quiet
cd /tmp/42submit

# Build filter-repo path arguments
PATHS="--path $PROJECT/"
for dep in "${DEPS[@]}"; do
    PATHS="$PATHS --path $dep/"
done

# Keep only commits touching project and its dependencies
git filter-repo $PATHS --force --quiet

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
echo "📝 Commits to submit:"
echo "───────────────────────────────────────────"
git log --oneline --stat --format="%C(yellow)%h%C(reset) %s %C(dim)(%cr)%C(reset)" | head -80
echo "───────────────────────────────────────────"
echo ""

COMMIT_COUNT=$(git rev-list --count HEAD)
echo "Total: $COMMIT_COUNT commits"
echo ""

# Confirm
read -p "Push to vogsphere? [y/N] " -n 1 -r
echo ""

if [[ $REPLY =~ ^[Yy]$ ]]; then
    git push -f "$REMOTE" HEAD:main
    echo ""
    echo "✓ Submitted $PROJECT ($COMMIT_COUNT commits)"
else
    echo "✗ Cancelled"
fi

cd "$ORIG_DIR"
rm -rf /tmp/42submit