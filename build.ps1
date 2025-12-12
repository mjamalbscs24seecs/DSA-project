param(
    [string]$BuildDir = "build",
    [switch]$Clean
)

if ($Clean -and (Test-Path $BuildDir)) {
    Remove-Item -Recurse -Force $BuildDir
}

cmake -S . -B $BuildDir
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build $BuildDir
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "Build complete. Binaries in $BuildDir"
