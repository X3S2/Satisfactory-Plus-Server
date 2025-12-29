# Installation & Setup Guide

Detaillierte Anleitung zur Installation von Satisfactory Plus Server.

## 📋 Inhaltsverzeichnis
1. [Schnellstart](#schnellstart)
2. [Dedicated Server Setup](#dedicated-server-setup)
3. [Client Setup](#client-setup)
4. [Troubleshooting](#troubleshooting)
5. [Erweiterte Konfiguration](#erweiterte-konfiguration)

---

## Schnellstart

### Voraussetzungen
- Satisfactory 1.1+ (Build 365306+)
- Satisfactory Mod Manager (SMM)
- Satisfactory Plus 1.2.3
- SML 3.11.1+

### Installation (5 Minuten)

**Für Server:**
```powershell
# 1. SMM installieren
# Download: https://github.com/satisfactorymodding/SatisfactoryModManager

# 2. Mods über SMM installieren:
# - SML (3.11.1+)
# - Satisfactory Plus (1.2.3)
# - Satisfactory Plus Server (1.2.3)

# 3. Server starten
.\FactoryServer.exe
```

**Für Clients:**
- Gleiche Mods über SMM installieren
- Spiel starten
- Server beitreten

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
2. Installiere folgende Mods:
   - **SML** (Version 3.11.1 oder höher)
   - **Satisfactory Plus** (Version 1.2.3)
   - **Satisfactory Plus Server** (Version 1.2.3)

Alternativ manuell:
```powershell
# Mod-Installation-Pfad
cd "C:\SatisfactoryServer\FactoryGame\Mods"

# Lade und extrahiere Mods:
# - SML.zip
# - SatisfactoryPlus.zip
# - SatisfactoryPlusServer.zip
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
2. Folgende Mods installieren:
   - **SML** (3.11.1+)
   - **Satisfactory Plus** (1.2.3)
   - **Satisfactory Plus Server** (1.2.3) ← **Wichtig!**

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
