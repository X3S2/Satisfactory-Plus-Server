# Installation & Setup Guide

Detaillierte Anleitung zur Installation von Satisfactory Plus Server.

## ⚠️ **WICHTIGER HINWEIS**

Diese Mod ist aktuell **nur auf GitHub verfügbar** und muss manuell kompiliert und installiert werden.
Sie ist **NOCH NICHT** auf ficsit.app veröffentlicht und kann **NICHT** über den Satisfactory Mod Manager (SMM) installiert werden.

Für die Nutzung ist ein **Unreal Engine Build** erforderlich.

---

## 📋 Was benötigt der Server vs. Client?

### 🖥️ **Auf dem DEDICATED SERVER:**
| Komponente | Quelle | Installation |
|-----------|--------|--------------|
| **Satisfactory Dedicated Server** | Steam (App ID: 1690800) | SteamCMD oder Steam Client |
| **SML** | SMM (automatisch) | Via Satisfactory Mod Manager |
| **Satisfactory Plus** (Original von Kyrium) | ficsit.app | Via Satisfactory Mod Manager |
| **Satisfactory Plus Server** (diese Mod) | GitHub (noch nicht veröffentlicht) | Manuell (siehe unten) |

### 💻 **Auf dem CLIENT:**
| Komponente | Quelle | Installation |
|-----------|--------|--------------|
| **Satisfactory Game** | Steam/Epic | Steam oder Epic Games Launcher |
| **SML** | SMM (automatisch) | Via Satisfactory Mod Manager |
| **Satisfactory Plus** (Original von Kyrium) | ficsit.app | Via Satisfactory Mod Manager |
| **Satisfactory Plus Server** (diese Mod) | GitHub (noch nicht veröffentlicht) | Manuell (siehe unten) |

### ✅ **Wichtig:**
- **JA**, du benötigst "Satisfactory Plus" von Kyrium auf Server UND Client
- **JA**, du benötigst zusätzlich "Satisfactory Plus Server" (diese Mod) auf Server UND Client
- **SML** wird automatisch installiert, wenn du Satisfactory Plus installierst
- **Beide Mods** müssen die gleiche Version haben (1.2.3)

---

## 📋 Inhaltsverzeichnis
1. [Schnellstart (wenn Mod auf ficsit.app verfügbar)](#schnellstart)
2. [Manuelle Installation (aktuell)](#manuelle-installation)
3. [Dedicated Server Setup](#dedicated-server-setup)
4. [Client Setup](#client-setup)
5. [Troubleshooting](#troubleshooting)
6. [Erweiterte Konfiguration](#erweiterte-konfiguration)

---

## Schnellstart

### ⚠️ Aktuell NICHT verfügbar
Diese Anleitung gilt erst, wenn die Mod auf ficsit.app veröffentlicht ist.

### Voraussetzungen
- Satisfactory 1.1+ (Build 365306+)
- Satisfactory Mod Manager (SMM)
- Satisfactory Plus 1.2.3
- SML 3.11.1+ (wird automatisch installiert)

### Installation (5 Minuten)

**⚠️ Diese Schritte funktionieren erst, wenn die Mod auf ficsit.app veröffentlicht ist!**

**Für Server:**
```powershell
# 1. SMM installieren
# Download: https://github.com/satisfactorymodding/SatisfactoryModManager

# 2. Mods über SMM installieren:
# - Satisfactory Plus (1.2.3) ← Original-Mod von Kyrium
#   SML wird automatisch mit installiert!
# - Satisfactory Plus Server (1.2.3) ← Diese Mod (noch nicht verfügbar!)

# 3. Server starten
.\FactoryServer.exe
```

**Für Clients:**
- Gleiche Mods über SMM installieren
- Spiel starten
- Server beitreten

---

## Manuelle Installation

### ⚠️ Aktuell erforderlich, da Mod noch nicht auf ficsit.app

Diese Schritte sind für fortgeschrittene Benutzer mit Unreal Engine Erfahrung.

#### Voraussetzungen
- Unreal Engine 5.3+ mit Satisfactory SDK
- Visual Studio 2022
- Git
- Satisfactory Modding Toolkit

#### Schritt 1: Repository klonen
```powershell
git clone https://github.com/X3S2/Satisfactory-Plus-Server.git
cd Satisfactory-Plus-Server
```

#### Schritt 2: Projekt kompilieren
```powershell
# Unreal Engine Project generieren
# (Details abhängig vom Satisfactory Modding Setup)

# In Visual Studio öffnen und kompilieren
# Build → Build Solution
```

#### Schritt 3: Plugin packen
```powershell
# Packaging-Prozess abhängig vom Alpakit/SMM Setup
# Erstellt: SatisfactoryPlusServer.zip
```

#### Schritt 4: Auf Server & Client installieren
```powershell
# Kopiere nach:
# Server: <SatisfactoryServer>\FactoryGame\Mods\SatisfactoryPlusServer\
# Client: <Satisfactory>\FactoryGame\Mods\SatisfactoryPlusServer\
```

#### Schritt 5: Satisfactory Plus installieren
```powershell
# Im Satisfactory Mod Manager:
# 1. Suche "Satisfactory Plus"
# 2. Installiere Version 1.2.3
# 3. SML wird automatisch installiert
```

---

## Dedicated Server Setup

### Option 1: Windows Server

#### Schritt 1: Satisfactory Dedicated Server installieren
```powershell
# Via SteamCMD
steamcmd +login anonymous +app_update 1690800 validate +quit

# Oder: Via Steam Client
# Library → Tools → "Satisfactory Dedicated Server"
```

#### Schritt 2: Satisfactory Mod Manager (SMM) installieren
1. Download SMM: https://github.com/satisfactorymodding/SatisfactoryModManager
2. SMM installieren und öffnen
3. Server-Installationspfad auswählen

#### Schritt 3: Mods installieren
In SMM:
1. Gehe zu "Mods" Tab
2. Suche nach **"Satisfactory Plus"** (von Kyrium)
3. Installiere **Satisfactory Plus Version 1.2.3**
   - ✅ **SML wird automatisch mit installiert** - du musst SML NICHT separat suchen!
4. ⚠️ **Satisfactory Plus Server** ist noch nicht verfügbar - siehe [Manuelle Installation](#manuelle-installation)

**Hinweis:** Im SMM findest du nur "Satisfactory Plus", nicht "SML". Das ist normal!
SML wird als Dependency automatisch installiert.

Alternativ manuell:
```powershell
# Mod-Installation-Pfad
cd "C:\SatisfactoryServer\FactoryGame\Mods"

# Lade und extrahiere Mods:
# - SatisfactoryPlus.zip (von ficsit.app)
# - SatisfactoryPlusServer.zip (manuell kompiliert, siehe oben)
# SML wird automatisch installiert
```

#### Schritt 4: Server-Konfiguration
Bearbeite `FactoryGame/Saved/Config/WindowsServer/Game.ini`:
```ini
[/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem]
bEnableServerPatches=True
bEnableReplicationOptimizations=True
bStrictVersionChecking=True
ServerLogLevel=3
```

#### Schritt 5: Server starten
```powershell
cd C:\SatisfactoryServer
.\FactoryServer.exe -log
```

**Ports öffnen (Firewall):**
```powershell
New-NetFirewallRule -DisplayName "Satisfactory Server" -Direction Inbound -Protocol UDP -LocalPort 7777 -Action Allow
New-NetFirewallRule -DisplayName "Satisfactory Server Query" -Direction Inbound -Protocol UDP -LocalPort 15000 -Action Allow
New-NetFirewallRule -DisplayName "Satisfactory Server Beacon" -Direction Inbound -Protocol UDP -LocalPort 15777 -Action Allow
```

### Option 2: Linux Server (Docker)

#### Docker Compose Setup
Erstelle `docker-compose.yml`:
```yaml
version: '3.8'

services:
  satisfactory:
    image: wolveix/satisfactory-server:latest
    container_name: satisfactory-plus-server
    restart: unless-stopped
    ports:
      - "7777:7777/udp"
      - "15000:15000/udp"
      - "15777:15777/udp"
    volumes:
      - ./config:/config
      - ./mods:/config/gamefiles/FactoryGame/Mods
    environment:
      - MAXPLAYERS=4
      - PGID=1000
      - PUID=1000
      - STEAMBETA=false
```

Starten:
```bash
# Mods in ./mods/ ablegen
docker-compose up -d

# Logs anzeigen
docker-compose logs -f
```

#### Manuelle Linux Installation
```bash
# Dependencies
sudo apt update
sudo apt install -y steamcmd

# Server installieren
steamcmd +login anonymous +app_update 1690800 validate +quit

# Mods installieren (siehe Windows Schritt 3)
cd ~/SatisfactoryServer/FactoryGame/Mods
# Lade Mods herunter und extrahiere sie

# Server starten
cd ~/SatisfactoryServer
./FactoryServer.sh -log
```

---

## Client Setup

### Schritt 1: Satisfactory Mod Manager installieren
1. Download: https://github.com/satisfactorymodding/SatisfactoryModManager
2. Installation durchführen
3. SMM starten

### Schritt 2: Mods installieren
In SMM:
1. Tab "Mods" öffnen
2. Suche nach **"Satisfactory Plus"** (von Kyrium)
3. Installiere **Satisfactory Plus Version 1.2.3**
   - ✅ **SML wird automatisch installiert** - nicht separat suchen!
4. ⚠️ **Satisfactory Plus Server (1.2.3)** - Noch nicht verfügbar (siehe [Manuelle Installation](#manuelle-installation))

**Wichtig:** Im SMM siehst du nur "Satisfactory Plus", NICHT "SML".
SML ist eine Dependency und wird automatisch installiert.

### Schritt 3: Spiel starten
```
SMM → "Play" Button
```

### Schritt 4: Server beitreten
Im Spiel:
1. Multiplayer → Join Game
2. Server-IP eingeben
3. Verbinden

---

## Troubleshooting

### Problem: "Mod version mismatch"
**Lösung:**
- Stelle sicher, dass Server UND Client **exakt die gleichen Versionen** haben
- Prüfe in SMM: Alle Mods müssen identisch sein
- Neustart von Client und Server

### Problem: Server startet nicht
**Lösung 1 - Logs prüfen:**
```powershell
# Windows
Get-Content "FactoryGame\Saved\Logs\FactoryGame.log" -Tail 50

# Linux
tail -n 50 ~/SatisfactoryServer/FactoryGame/Saved/Logs/FactoryGame.log
```

**Lösung 2 - Dependency Check:**
```powershell
# Prüfe ob alle Mods vorhanden sind
dir "FactoryGame\Mods"
# Erwarte: SML, SatisfactoryPlus, SatisfactoryPlusServer
```

### Problem: Client kann nicht verbinden
**Checkliste:**
- [ ] Firewall-Ports geöffnet? (7777, 15000, 15777)
- [ ] Server läuft? (prüfe Logs)
- [ ] Richtige IP-Adresse?
- [ ] Gleiche Mod-Versionen?

### Problem: "SatisfactoryPlus plugin not found"
**Lösung:**
```
Installationsreihenfolge prüfen:
1. SML zuerst
2. SatisfactoryPlus
3. SatisfactoryPlusServer (benötigt SatisfactoryPlus!)
```

### Problem: Crashes bei bestimmten Features
**Debugging:**
1. Logs sammeln (Server + Client)
2. Issue auf GitHub erstellen
3. Detaillierte Schritte zur Reproduktion angeben

---

## Erweiterte Konfiguration

### Performance-Tuning

#### Server-Konfiguration
Bearbeite `Config/DefaultEngine.ini`:
```ini
[/Script/OnlineSubsystemUtils.IpNetDriver]
NetServerMaxTickRate=60
MaxNetTickRate=60
MaxInternetClientRate=100000
MaxClientRate=100000
```

#### Replication-Optimierungen
Bearbeite `Config/DefaultGame.ini`:
```ini
[/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem]
bEnableReplicationOptimizations=True
```

### Debug-Logging aktivieren
```ini
[/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem]
bEnableDebugLogging=True
ServerLogLevel=4
```

Logs dann prüfen:
```powershell
# Filtere nach SatisfactoryPlusServer
Get-Content "FactoryGame\Saved\Logs\FactoryGame.log" | Select-String "SatisfactoryPlusServer"
```

### Backup-Strategie

**Savegames sichern:**
```powershell
# Windows
$BackupPath = "E:\Backups\Satisfactory"
$SavePath = "C:\SatisfactoryServer\FactoryGame\Saved\SaveGames"
Copy-Item -Path $SavePath -Destination "$BackupPath\$(Get-Date -Format 'yyyy-MM-dd_HH-mm-ss')" -Recurse

# Linux (cron)
0 */4 * * * tar -czf ~/backups/satisfactory_$(date +\%Y\%m\%d_\%H\%M\%S).tar.gz ~/SatisfactoryServer/FactoryGame/Saved/SaveGames
```

### Automatische Updates (Linux)
```bash
#!/bin/bash
# update_server.sh

echo "Stopping server..."
docker-compose down

echo "Updating server..."
docker-compose pull

echo "Starting server..."
docker-compose up -d

echo "Done!"
```

---

## 🆘 Support

**Bei Problemen:**
1. [GitHub Issues](https://github.com/X3S2/Satisfactory-Plus-Server/issues)
2. [Troubleshooting Guide](#troubleshooting)
3. Logs sammeln und Issue erstellen

**Community:**
- [Satisfactory Modding Discord](https://discord.gg/satisfactory-modding)

---

**Letzte Aktualisierung:** 29.12.2025  
**Version:** 1.2.3
