set -e
g++ -std=c++20 TestGenerator.cpp -o TestGenerator
g++ -std=c++20 SolnCorrect.cpp -o SolnCorrect
g++ -std=c++20 SolnMy.cpp -o SolnMy
for((i = 1;i<=1000000 ; ++i)); do
    ./TestGenerator $i > input_file
    ./SolnMy < input_file > AnswerMy
    ./SolnCorrect < input_file > AnswerCorrect
    diff -Z AnswerMy AnswerCorrect > /dev/null || exit
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat AnswerMy
echo "Correct answer is:"
cat AnswerCorrect

# Note: no need for file i/o anywhere
# put the correct code in SolnCorrect.cpp
# put your code in SolnMy.cpp
# put the test generator in TestGenerator.cpp
# run "bash checker.sh" in terminal
# finally, the test case, and differing answers will be in input_file, AnswerMy and AnswerCorrect
# To run the checker, just run "bash checker.sh" in the terminal