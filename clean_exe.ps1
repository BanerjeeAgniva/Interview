# Script to permanently delete all .exe files recursively (PowerShell)
# Usage: .\clean_exe.ps1

Write-Host "Searching for .exe files..." -ForegroundColor Yellow

# Find and delete all .exe files recursively
Get-ChildItem -Path . -Filter "*.exe" -Recurse -File | ForEach-Object {
    Write-Host "Deleting: $($_.FullName)" -ForegroundColor Red
    Remove-Item -Path $_.FullName -Force
}

# Also delete a.out if it exists
if (Test-Path "a.out") {
    Write-Host "Found a.out, deleting..." -ForegroundColor Red
    Remove-Item -Path "a.out" -Force
}

Write-Host "Cleanup complete! All .exe files have been permanently deleted." -ForegroundColor Green

