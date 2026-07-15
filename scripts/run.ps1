#Requires -Version 5.1
$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$proj = Join-Path $root "ConsoleMVC.vcxproj"

$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$msbuild = & $vswhere -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe
if (-not $msbuild) {
    Write-Error "MSBuild not found via vswhere"
    exit 1
}

Write-Output "== build =="
& $msbuild $proj /p:Configuration=Release /p:Platform=x64 /nologo /v:minimal
if ($LASTEXITCODE -ne 0) { Write-Error "build failed"; exit 1 }

$exe = Join-Path $root "x64\Release\ConsoleMVC.exe"

Write-Output "== self-test (FR-02) =="
& $exe --self-test
if ($LASTEXITCODE -ne 0) { Write-Error "self-test failed"; exit 1 }

Write-Output "== headless run, default view (FR-01) =="
cmd /c "`"$exe`" < NUL"
if ($LASTEXITCODE -ne 0) { Write-Error "headless default-view run failed"; exit 1 }

Write-Output "== headless run, plain view (FR-05/FR-06) =="
cmd /c "`"$exe`" --view=plain < NUL"
if ($LASTEXITCODE -ne 0) { Write-Error "headless plain-view run failed"; exit 1 }

Write-Output "ALL PASS"
exit 0
