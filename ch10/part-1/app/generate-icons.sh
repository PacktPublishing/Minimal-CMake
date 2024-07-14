#!/bin/bash

# Check if the source image is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <source_image>"
  exit 1
fi

SOURCE_IMAGE=$1
ICONSET_NAME="gol.iconset"

# Create the .iconset folder
mkdir $ICONSET_NAME

# Generate the icons
sips -z 16 16     $SOURCE_IMAGE --out $ICONSET_NAME/icon_16x16.png
sips -z 32 32     $SOURCE_IMAGE --out $ICONSET_NAME/icon_16x16@2x.png
sips -z 32 32     $SOURCE_IMAGE --out $ICONSET_NAME/icon_32x32.png
sips -z 64 64     $SOURCE_IMAGE --out $ICONSET_NAME/icon_32x32@2x.png
sips -z 128 128   $SOURCE_IMAGE --out $ICONSET_NAME/icon_128x128.png
sips -z 256 256   $SOURCE_IMAGE --out $ICONSET_NAME/icon_128x128@2x.png
sips -z 256 256   $SOURCE_IMAGE --out $ICONSET_NAME/icon_256x256.png
sips -z 512 512   $SOURCE_IMAGE --out $ICONSET_NAME/icon_256x256@2x.png
sips -z 512 512   $SOURCE_IMAGE --out $ICONSET_NAME/icon_512x512.png
sips -z 1024 1024 $SOURCE_IMAGE --out $ICONSET_NAME/icon_512x512@2x.png

# Convert the .iconset folder to an .icns file
iconutil -c icns $ICONSET_NAME

echo "Iconset and ICNS file created successfully."
