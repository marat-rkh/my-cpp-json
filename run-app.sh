source 'settings.sh'

pushd $BUILD_DIR/bin/app > /dev/null
./json-parser-main
popd > /dev/null