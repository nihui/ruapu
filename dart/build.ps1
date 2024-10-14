$PROJECT_DIR = Get-Location
$RUAPU_API_DIR = Join-Path -Path $PROJECT_DIR -ChildPath "ruapu-api"
$BUILD_DIR = Join-Path -Path $PROJECT_DIR -ChildPath "build"

New-Item -ItemType Directory -Force -Path $BUILD_DIR
Set-Location $BUILD_DIR

cmake $RUAPU_API_DIR
cmake --build $BUILD_DIR

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build Error!!! Plz Check!!!"
    exit 1
}

Set-Location $PROJECT_DIR

dart pub get

dart run main.dart