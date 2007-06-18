#!/bin/sh

export VERSAO=1.0
export DISTRO=/home/desenvolvimento/pjmoo/distro/games
export TMP_DIR=/tmp/pjmoo/opt/fzpong
export PROJETO_DIR=/home/desenvolvimento/pjmoo/projetos/games/fzpong

echo "Criando: FZPong $VERSAO"
rm -fR $TMP_DIR
mkdir -p $TMP_DIR

echo "    Copiando Arquivos..."
cp -R ./bin/* $TMP_DIR

echo "    Fixando permissoes"

cd $TMP_DIR; cd ..
chown root:users -R fzpong
echo "modo (chmod)"
chmod 2775 fzpong
chmod 2775 fzpong/data/etc
chmod 2775 fzpong/data/screen
chmod  775 fzpong/FZPong

echo "    Criando pacote... (Zip - All)"
zip -rq4 $DISTRO/FZPong.$VERSAO.bin.all.zip * -x *svn* *cvsignore*

echo "    Criando pacote... (GNU/Linux)"
rm  -f fzpong/*.exe
tar -czf $DISTRO/FZPong.$VERSAO.bin.linux.tar.gz * --exclude=*svn*

echo "    Copiando Source"
mkdir -p /tmp/pjmoo/src/fzpong
cp $PROJETO_DIR/*  /tmp/pjmoo/src/fzpong/
cp -R $PROJETO_DIR/src /tmp/pjmoo/src/fzpong/
cd /tmp/pjmoo/src/fzpong/

echo "    Criando pacote source ... (Linux/Win32)"
rm -f $DISTRO/FZPong.$VERSAO.src.zip
zip -rq4 $DISTRO/FZPong.$VERSAO.src.zip * -x *svn* *cvsignore* *doc* *objs* *bin* *log*
rm -fR $TMP_DIR
echo "    Pacote Finalizado"
