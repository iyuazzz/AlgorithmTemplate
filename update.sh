#! /bin/bash
git add .
timenow=$(date)
git commit -m "${timenow}"
git push origin master
