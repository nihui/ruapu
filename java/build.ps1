Get-Command -Name "cmake" -ErrorAction Stop
if (!(Test-Path build/cmake))
{
    mkdir build
}
cmake -B build/cmake
cmake --build build/cmake --config Release --target install
