#!/bin/sh

export VERSAO=2.4
export PKG_RELEASE=1
export DISTRO=/home/desenvolvimento/pjmoo/distro/games
export TMP_ROOT=/tmp/pjmoo
export TMP_DIR=$TMP_ROOT/opt/games/fzpong
export PROJETO_DIR=/home/desenvolvimento/pjmoo/projetos/games/fzpong

echo "Criando: FZPong $VERSAO"
rm -fR $TMP_DIR
mkdir -p $TMP_DIR

echo "    Copiando Arquivos..."
cp -vR $PROJETO_DIR/bin/* $TMP_DIR

echo "    Fixando permissoes"

cd $TMP_DIR; cd ..
chown root:users -R fzpong
echo "modo (chmod)"
chmod 2775 fzpong
chmod 2775 fzpong/data/etc
chmod 2775 fzpong/data/screen
chmod  775 fzpong/FZPong

echo "    Criando pacote... (Zip - All)"
zip -vrq4 $DISTRO/FZPong.$VERSAO.bin.all.zip * -x *svn* *cvsignore* *xcf* *log*

echo "    Criando pacote... (GNU/Linux)"
rm  -fv fzpong/*.exe

cd $TMP_ROOT
tar -cvzf $DISTRO/FZPong.$VERSAO.bin.linux.tar.gz * --exclude=*svn* --exclude=*xcf* --exclude=*log*


echo "    Copiando Source"
mkdir -vp /tmp/pjmoo/src/fzpong
cp $PROJETO_DIR/*  /tmp/pjmoo/src/fzpong/
cp -vR $PROJETO_DIR/src /tmp/pjmoo/src/fzpong/
cd /tmp/pjmoo/src/fzpong/

echo "    Criando pacote source ... (Linux/Win32)"
rm -vf $DISTRO/FZPong.$VERSAO.src.zip
zip -vrq4 $DISTRO/FZPong.$VERSAO.src.zip * -x *svn* *cvsignore* *doc* *objs* *bin* *log* *xcf*
rm -vfR $TMP_ROOT
echo "    Pacote Finalizado"
