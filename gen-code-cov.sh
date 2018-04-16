#!/bin/bash

cd cmake-build-debug

cmake .. -DENABLE_CODECOVERAGE=ON
make
make test
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/tests/*'  '/Library/Developer/*' --output-file coverage.info
lcov --list coverage.info
export CODECOV_TOKEN="5dd73d4a-b623-40c8-8926-766ee0d69711"
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"

list="$(find . -name \*.gcda -o -name \*.gcov -type f)"
for file in $list; do
    if [ -f "$file" ]; then
        echo "REMOVE: $file";
        rm -f $file;
    fi;
done