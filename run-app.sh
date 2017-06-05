source 'settings.sh'

pushd $BUILD_DIR/bin/app > /dev/null
./my-cpp-json-main
popd > /dev/null