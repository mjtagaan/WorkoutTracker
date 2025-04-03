#!/bin/bash

read -p "Enter commit message: " commit
git add .
git commit -m "$commit"
git push origin master
echo "Changes have been committed and pushed to the master branch."