Get-Command -Name "cmake" -ErrorAction Stop
if (!(Test-Path build/cmake))
{
    mkdir build
}
cmake -B build/cmake -DBUILD_EXAMPLE=ON
if (!$?)
{
    return 1
}
cmake --build build/cmake --config Release --target install
if (!$?)
{
    return 1
}
