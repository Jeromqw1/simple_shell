#!/bin/bash

# Change directory to my local Git repository
cd /home/phaceless/alx-pre_course/simple_shell

# Prompt the user for a commit message
read -p "Enter your commit message: " commit_message

# Add all changes to the staging area
git add .

# Add a commit message
git commit -m "$commit_message"

# Get the name of the current branch
current_branch=$(git symbolic-ref --short HEAD)

# Push the changes to my repository
git push origin "$current_branch"
