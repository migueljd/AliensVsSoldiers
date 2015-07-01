#!/bin/sh
if [ $DEPLOYMENT_LOCATION = "YES" ]
then
cp -R AliensVsSoldiers/Binaries/IOS/Payload/AliensVsSoldiers.app/ $DSTROOT/$LOCAL_APPS_DIR/AliensVsSoldiers.app
fi
