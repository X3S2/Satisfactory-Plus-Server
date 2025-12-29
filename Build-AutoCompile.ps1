# Satisfactory Plus Server - Automatischer Build
# Dieses Script kompiliert die Mod automatisch ohne GUI-Interaktion

param(
    [string]$UnrealEnginePath = "",
    [string]$SatisfactoryPath = "",
    [string]$OutputPath = ""
)

# Farben für Output
function Write-Success { Write-Host $args -ForegroundColor Green }
function Write-Error { Write-Host $args -ForegroundColor Red }
function Write-Info { Write-Host $args -ForegroundColor Cyan }
function Write-Warning { Write-Host $args -ForegroundColor Yellow }

Clear-Host
Write-Host "========================================" -ForegroundColor Magenta
Write-Host "  Satisfactory Plus Server - Auto Build" -ForegroundColor Magenta
Write-Host "========================================" -ForegroundColor Magenta
Write-Host ""

# Schritt 1: Unreal Engine finden
Write-Info "Schritt 1: Unreal Engine 5.3 suchen..."

if ($UnrealEnginePath -eq "") {
    $PossiblePaths = @(
        "C:\Program Files\Epic Games\UE_5.3",
        "C:\Program Files\Epic Games\UE_5.4",
        "D:\Program Files\Epic Games\UE_5.3",
        "E:\Program Files\Epic Games\UE_5.3"
    )
    
    foreach ($path in $PossiblePaths) {
        if (Test-Path "$path\Engine\Binaries\Win64\UnrealEditor.exe") {
            $UnrealEnginePath = $path
            Write-Success "✓ Unreal Engine gefunden: $UnrealEnginePath"
            break
        }
    }
}

if ($UnrealEnginePath -eq "" -or !(Test-Path $UnrealEnginePath)) {
    Write-Error "✗ Unreal Engine nicht gefunden!"
    Write-Warning "Bitte gebe den Pfad manuell ein:"
    $UnrealEnginePath = Read-Host "Unreal Engine Pfad (z.B. C:\Program Files\Epic Games\UE_5.3)"
    
    if (!(Test-Path "$UnrealEnginePath\Engine\Binaries\Win64\UnrealEditor.exe")) {
        Write-Error "✗ Ungültiger Pfad! Script wird beendet."
        exit 1
    }
}

$UBT = "$UnrealEnginePath\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
$UAT = "$UnrealEnginePath\Engine\Build\BatchFiles\RunUAT.bat"

# Schritt 2: Satisfactory Installation finden
Write-Info "`nSchritt 2: Satisfactory Installation suchen..."

if ($SatisfactoryPath -eq "") {
    $PossibleSatisfactoryPaths = @(
        "C:\Program Files (x86)\Steam\steamapps\common\Satisfactory",
        "D:\Steam\steamapps\common\Satisfactory",
        "E:\Steam\steamapps\common\Satisfactory",
        "C:\Program Files\Epic Games\Satisfactory",
        "D:\Epic Games\Satisfactory"
    )
    
    foreach ($path in $PossibleSatisfactoryPaths) {
        if (Test-Path "$path\FactoryGame.exe") {
            $SatisfactoryPath = $path
            Write-Success "✓ Satisfactory gefunden: $SatisfactoryPath"
            break
        }
    }
}

if ($SatisfactoryPath -eq "" -or !(Test-Path $SatisfactoryPath)) {
    Write-Warning "Satisfactory nicht automatisch gefunden."
    Write-Warning "Bitte gebe den Pfad manuell ein:"
    $SatisfactoryPath = Read-Host "Satisfactory Pfad (z.B. C:\...\Satisfactory)"
    
    if (!(Test-Path "$SatisfactoryPath\FactoryGame.exe")) {
        Write-Error "✗ Ungültiger Pfad! Script wird beendet."
        exit 1
    }
}

# Schritt 3: Arbeitsverzeichnis erstellen
Write-Info "`nSchritt 3: Arbeitsverzeichnis vorbereiten..."

$WorkDir = "$env:USERPROFILE\Documents\SatisfactoryModding"
if (!(Test-Path $WorkDir)) {
    New-Item -ItemType Directory -Path $WorkDir -Force | Out-Null
    Write-Success "✓ Arbeitsverzeichnis erstellt: $WorkDir"
} else {
    Write-Success "✓ Arbeitsverzeichnis existiert: $WorkDir"
}

Set-Location $WorkDir

# Schritt 4: Satisfactory Starter Project klonen
Write-Info "`nSchritt 4: Satisfactory Starter Project herunterladen..."

$StarterProjectPath = "$WorkDir\SatisfactoryModLoader"

if (!(Test-Path $StarterProjectPath)) {
    Write-Info "Klone Starter Project von GitHub..."
    git clone --depth 1 https://github.com/satisfactorymodding/SatisfactoryModLoader.git
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error "✗ Git-Clone fehlgeschlagen!"
        Write-Warning "Stelle sicher, dass Git installiert ist: https://git-scm.com/download/win"
        exit 1
    }
    Write-Success "✓ Starter Project heruntergeladen"
} else {
    Write-Success "✓ Starter Project bereits vorhanden"
}

# Schritt 5: Unsere Mod klonen
Write-Info "`nSchritt 5: Satisfactory Plus Server Mod herunterladen..."

$ModPath = "$StarterProjectPath\Mods\SatisfactoryPlusServer"

if (!(Test-Path $ModPath)) {
    New-Item -ItemType Directory -Path "$StarterProjectPath\Mods" -Force | Out-Null
    
    Write-Info "Klone Mod von GitHub..."
    Set-Location "$StarterProjectPath\Mods"
    git clone https://github.com/X3S2/Satisfactory-Plus-Server.git SatisfactoryPlusServer
    
    if ($LASTEXITCODE -ne 0) {
        Write-Error "✗ Mod-Download fehlgeschlagen!"
        exit 1
    }
    Write-Success "✓ Mod heruntergeladen"
} else {
    Write-Success "✓ Mod bereits vorhanden"
    Write-Info "Aktualisiere Mod..."
    Set-Location $ModPath
    git pull
}

Set-Location $StarterProjectPath

# Schritt 6: .uproject Datei finden
Write-Info "`nSchritt 6: Projekt-Datei suchen..."

$UProjectFile = Get-ChildItem -Path $StarterProjectPath -Filter "*.uproject" | Select-Object -First 1

if ($null -eq $UProjectFile) {
    Write-Error "✗ Keine .uproject Datei gefunden!"
    Write-Error "Starter Project scheint unvollständig zu sein."
    exit 1
}

$UProjectPath = $UProjectFile.FullName
Write-Success "✓ Projekt gefunden: $($UProjectFile.Name)"

# Schritt 7: Visual Studio Project Files generieren
Write-Info "`nSchritt 7: Visual Studio Project generieren..."

Write-Info "Führe UnrealBuildTool aus..."
& $UBT -projectfiles -project="$UProjectPath" -game -engine

if ($LASTEXITCODE -ne 0) {
    Write-Error "✗ Projekt-Generierung fehlgeschlagen!"
    Write-Error "Prüfe, ob Visual Studio 2022 mit C++ Tools installiert ist."
    exit 1
}

Write-Success "✓ Visual Studio Project generiert"

# Schritt 8: Projekt kompilieren
Write-Info "`nSchritt 8: Mod kompilieren..."
Write-Warning "Das kann 10-30 Minuten dauern (beim ersten Mal)..."
Write-Info "Bitte warten..."

$ProjectName = [System.IO.Path]::GetFileNameWithoutExtension($UProjectPath)

& $UBT Development Win64 -Project="$UProjectPath" -TargetType=Editor -Progress

if ($LASTEXITCODE -ne 0) {
    Write-Error "✗ Kompilierung fehlgeschlagen!"
    Write-Error "Prüfe die Logs oben für Details."
    Write-Warning "`nMögliche Lösungen:"
    Write-Warning "1. Visual Studio 2022 mit C++ Tools installiert?"
    Write-Warning "2. Windows SDK installiert?"
    Write-Warning "3. Satisfactory Plus (Original) installiert?"
    exit 1
}

Write-Success "✓ Kompilierung erfolgreich!"

# Schritt 9: Plugin mit Alpakit packen
Write-Info "`nSchritt 9: Plugin packen..."

Write-Warning "HINWEIS: Automatisches Packaging über CMD ist komplex."
Write-Warning "Bitte führe folgenden Schritt MANUELL aus:"
Write-Host ""
Write-Host "1. Öffne Unreal Engine Editor:" -ForegroundColor Yellow
Write-Host "   $UnrealEnginePath\Engine\Binaries\Win64\UnrealEditor.exe" -ForegroundColor Cyan
Write-Host ""
Write-Host "2. Öffne das Projekt:" -ForegroundColor Yellow
Write-Host "   $UProjectPath" -ForegroundColor Cyan
Write-Host ""
Write-Host "3. Im Editor:" -ForegroundColor Yellow
Write-Host "   → Edit → Plugins → Suche 'Alpakit' → Aktiviere es → Restart Editor" -ForegroundColor Cyan
Write-Host "   → Tools → Alpakit → Wähle 'SatisfactoryPlusServer' → Package" -ForegroundColor Cyan
Write-Host ""

Write-Info "Möchtest du den Editor jetzt öffnen? (j/n)"
$response = Read-Host

if ($response -eq "j" -or $response -eq "J" -or $response -eq "y" -or $response -eq "Y") {
    Write-Info "Öffne Unreal Engine Editor..."
    Start-Process "$UnrealEnginePath\Engine\Binaries\Win64\UnrealEditor.exe" -ArgumentList "`"$UProjectPath`""
    Write-Success "✓ Editor gestartet!"
}

# Schritt 10: Zusammenfassung
Write-Host ""
Write-Host "========================================" -ForegroundColor Magenta
Write-Host "  Kompilierung abgeschlossen!" -ForegroundColor Magenta
Write-Host "========================================" -ForegroundColor Magenta
Write-Host ""

Write-Success "✓ Mod-Code kompiliert"
Write-Info "→ Projekt-Pfad: $StarterProjectPath"
Write-Info "→ Mod-Pfad: $ModPath"
Write-Host ""

Write-Warning "Nächste Schritte:"
Write-Host "1. Führe Alpakit-Packaging im UE Editor durch (siehe oben)" -ForegroundColor Yellow
Write-Host "2. Fertige Mod findest du in:" -ForegroundColor Yellow
Write-Host "   $SatisfactoryPath\FactoryGame\Mods\SatisfactoryPlusServer\" -ForegroundColor Cyan
Write-Host ""

Write-Info "Logs befinden sich in:"
Write-Host "$StarterProjectPath\Saved\Logs\" -ForegroundColor Cyan
Write-Host ""

# Optional: Logs öffnen
Write-Info "Logs im Explorer öffnen? (j/n)"
$response = Read-Host

if ($response -eq "j" -or $response -eq "J" -or $response -eq "y" -or $response -eq "Y") {
    Start-Process "explorer.exe" -ArgumentList "$StarterProjectPath\Saved\Logs\"
}

Write-Success "`n✓ Script abgeschlossen!"
Write-Host "Bei Problemen: https://github.com/X3S2/Satisfactory-Plus-Server/issues" -ForegroundColor Cyan
