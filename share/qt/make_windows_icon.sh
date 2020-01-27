#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/diminutivevaultcoin.ico

convert ../../src/qt/res/icons/diminutivevaultcoin-16.png ../../src/qt/res/icons/diminutivevaultcoin-32.png ../../src/qt/res/icons/diminutivevaultcoin-48.png ${ICON_DST}
