!/bin/bash

MY_CAT="../../build/cat"
ORIGINAL_CAT="/bin/cat"

TEST_FILES=("text_for_test/test_1.txt" "text_for_test/test_2.txt" "text_for_test/test_3.txt" "text_for_test/test_4.txt" "text_for_test/test_5.txt" "")

MATCH_COUNT=0
TOTAL_TEST=2000

FLAGS=("-b" "-n" "-e" "-E" "-t" "-T" "-s" "-v" "--number-nonblank" "--number" "--squeeze-blank" "")

run_test() {
    local file=$1
    local flag=$2
    original_output=$($ORIGINAL_CAT $flag "$file")
    my_output=$($MY_CAT $flag "$file")
    echo $original_output
    echo $my_output
    if [ "$original_output" == "$my_output" ]; then
        MATCH_COUNT=$((MATCH_COUNT+1))
    fi
}

for((i=0; i<TOTAL_TEST; i++)); do
    random_file=${TEST_FILES[$RANDOM % ${#TEST_FILES[@]}]}
    random_flag=${FLAGS[$RANDOM % ${#FLAGS[@]}]}
    run_test "$random_file" "$random_flag"
done

echo "Пройдено тестов: $MATCH_COUNT из $TOTAL_TEST"