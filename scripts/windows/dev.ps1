param(
    [string[]]$AgentArgs = @("status")
)

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
    Invoke-Native ".\build\debug\fidelio-loyalty-agent.exe" @AgentArgs
}
finally {
    Pop-Location
}
