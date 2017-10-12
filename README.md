Extracted test case for @MalwareMinigun and the Visual C++ Team.

I was complaining in my tweet but let me say THANK YOU for the great (FREE!) IDE and toolchain. I
use it every day and it is pretty damn good.

In my tweet "I just went from 4fps to 30fps by changing a vector<bool> to a vector<char>. !@!@%$!@#%"

To elaborate, accessing vector<bool> is at least 3 times slower than accessing vector<char> in
debug builds, even with _ITERATOR_DEBUG_LEVEL=0. It's 4x+ with _ITERATOR_DEBUG_LEVEL=2. I know I
know it's a debug build, but I need to use the debugger on my game sometimes and it would be nice
if it was only 2-4x slower (playable) rather than 10+x slower (not playable). As you can see in
the project settings I already turned off "Basic Runtime Checks" and "Security Check" which helps
enormously.

This extracted benchmark just repeatedly reads from the vector<bool/char> and writes a value to a
vector<float> depending on the state.

My game represents various variables about surface of the earth (humidity, temperature,
population, etc.) using large vector<float>, vector<bool>, etc. where each vector item is mapped
to a position/pixel on the earth's surface. It then iterates through these vectors every frame
doing a numerical simulation - pretty similar to the benchmark.


Program output on my machine (Debug/x64 build)

    initializing
    running bools
    0: 72.27ms
    1: 68.89ms
    2: 77.40ms
    3: 70.94ms
    4: 69.86ms
    5: 69.70ms
    6: 66.22ms
    7: 66.93ms
    8: 66.94ms
    9: 67.18ms
    running chars
    0: 18.69ms
    1: 18.53ms
    2: 18.79ms
    3: 24.73ms
    4: 18.18ms
    5: 18.21ms
    6: 18.83ms
    7: 19.42ms
    8: 18.14ms
    9: 18.91ms

    bool avg: 69.63ms
    char avg: 19.24ms
