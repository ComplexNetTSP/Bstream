#!/bin/bash

cd cmake-build-debug
find . -name *.gcda -exec rm -f {} \;
find . -name *.gcov -exec rm -f {} \;
cmake .. -DENABLE_CODECOVERAGE=ON
make 
make test
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/tests/*'  '/Library/Developer/*' --output-file coverage.info
lcov --list coverage.info
export CODECOV_TOKEN="5dd73d4a-b623-40c8-8926-766ee0d69711"
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"