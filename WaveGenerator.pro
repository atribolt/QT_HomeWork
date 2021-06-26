TEMPLATE = subdirs

MAJOR_VER=1
MINOR_VER=0
PATCH_VER=`git rev-list HEAD --count -- ./`

VERSION=${MAJOR_VER}.${MINOR_VER}.${PATCH_VER}

SUBDIRS += \
  QtEmulator \
  QtRegistrator \
  libs\CommonLib
