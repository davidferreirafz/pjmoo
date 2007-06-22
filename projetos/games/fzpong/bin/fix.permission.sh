#!/bin/sh

CWD=$(pwd)


echo "*Fixando permissoes"

echo "..fix: chown root:users -R ./"
chown root:users -R ./
echo "..fix: chmod 2775 ./"
chmod 2775 ./
echo "..fix: chmod 2775 ./data/screen"
chmod 2775 ./data/screen
echo "..fix: chmod  775 ./FZPong"
chmod  775 ./FZPong

echo ".Ok"
