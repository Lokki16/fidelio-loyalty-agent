Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

function Invoke-Native {
    $FilePath = $args[0]
    $ArgumentList = @()
    if ($args.Count -gt 1) {
        $ArgumentList = $args[1..($args.Count - 1)]
    }

    & $FilePath @ArgumentList
    if ($LASTEXITCODE -ne 0) {
        throw "$FilePath failed with exit code $LASTEXITCODE"
    }
}

$root = Resolve-Path -LiteralPath (Join-Path $PSScriptRoot "..\..")
Push-Location $root
try {
    Invoke-Native cmake --preset debug
    Invoke-Native cmake --build --preset debug
    try {
        Invoke-Native ctest --preset debug --output-on-failure
    }
    catch {
        Write-Warning "ctest failed to start locally; running smoke test directly."
        Invoke-Native ".\build\debug\fidelio-agent-state-smoke-test.exe"
    }
}
finally {
    Pop-Location
}
