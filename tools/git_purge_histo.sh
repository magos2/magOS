#!/bin/sh

git checkout --orphan newBranch

# Add all files and commit them
git add -A  
git commit -a -m "purge histo"

# Deletes the master branch
git branch -D master  

# Rename the current branch to master
git branch -m master  

# Force push master branch to github
git push -f origin master  

# remove the old files
git gc --aggressive --prune=all     
