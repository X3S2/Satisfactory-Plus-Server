# Build-Anleitung: Satisfactory Plus Server kompilieren

Komplette Schritt-für-Schritt Anleitung zur Kompilierung der Mod.

## ⚠️ Bevor du beginnst

**Systemanforderungen:**
- Windows 10/11 (64-bit)
- Mindestens 32 GB RAM (empfohlen: 64 GB)
- ~100 GB freier Festplattenspeicher (SSD empfohlen)
- Starke CPU (Intel i7/i9 oder AMD Ryzen 7/9)
- Stabile Internetverbindung
- **Zeitaufwand:** 6-12 Stunden (je nach System & Internet)

---

## 📥 Schritt 1: Epic Games Launcher installieren

### Download & Installation
1. **Download:** https://store.epicgames.com/de/download
   - Größe: ~60 MB
   - Dauer: 5 Minuten

2. **Installation:**
   ```
   - Installer ausführen
   - Account erstellen/einloggen
   - Standard-Installation durchführen
   ```

3. **Epic Games Account:**
   - Kostenlos registrieren
   - E-Mail-Bestätigung

---

## 🎮 Schritt 2: Unreal Engine 5.3 installieren

### Download & Installation
1. **Im Epic Games Launcher:**
   ```
   Epic Games Launcher öffnen
   → Tab "Unreal Engine" (links)
   → Oben: "Library"
   → Rechts oben: "+" Klicken
   → Version auswählen: 5.3.2 (oder neuer)
   → "Install" klicken
   ```

2. **Installationseinstellungen:**
   ```
   Install Location: C:\Program Files\Epic Games\UE_5.3
   
   Components auswählen:
   ✅ Core Components
   ✅ Starter Content
   ✅ Templates and Feature Packs
   ✅ Engine Source (WICHTIG!)
   ✅ Target Platform Support → Windows
   ❌ Android/iOS/Mac (nicht benötigt)
   ```

3. **Download-Größe:** ~45-50 GB
4. **Installationszeit:** 2-4 Stunden (je nach Internet)
5. **Installierter Speicher:** ~40-45 GB

⏳ **Lass dies im Hintergrund laufen und fahre mit Schritt 3 fort.**

---

## 🛠️ Schritt 3: Visual Studio 2022 installieren

### Download & Installation
1. **Download:** https://visualstudio.microsoft.com/de/downloads/
   - Wähle: **"Community 2022"** (kostenlos)
   - Größe: ~3 GB Installer
   - Dauer: 10 Minuten Download

2. **Installation starten:**
   ```
   vs_community.exe ausführen
   → Visual Studio Installer startet
   → Warte auf Initialisierung
   ```

3. **Workloads auswählen (WICHTIG!):**
   ```
   ✅ Desktop development with C++
   
   Rechts unter "Installation Details":
   ✅ MSVC v143 - VS 2022 C++ x64/x86 build tools
   ✅ Windows 10 SDK (10.0.19041.0 oder neuer)
   ✅ C++ profiling tools
   ✅ C++ CMake tools for Windows
   ✅ IntelliSense
   
   Optional aber empfohlen:
   ✅ Game development with C++
   ✅ Unreal Engine installer
   ```

4. **Installation durchführen:**
   ```
   "Install" klicken
   → Akzeptiere Lizenz
   → Warte auf Download & Installation
   ```

5. **Download-Größe:** ~10-15 GB
6. **Installationszeit:** 1-2 Stunden
7. **Installierter Speicher:** ~20-25 GB

⏳ **Läuft parallel zu Unreal Engine.**

---

## 📦 Schritt 4: Git installieren

### Download & Installation
1. **Download:** https://git-scm.com/download/win
   - Größe: ~50 MB
   - Dauer: 2 Minuten

2. **Installation:**
   ```
   Git-2.43.0-64-bit.exe ausführen
   
   Empfohlene Einstellungen:
   → Editor: Use Visual Studio Code (oder Standard)
   → PATH environment: Git from the command line
   → HTTPS: Use OpenSSL
   → Line endings: Checkout Windows-style
   → Terminal: Use MinTTY
   → Rest: Standard-Einstellungen
   ```

3. **Test:**
   ```powershell
   # PowerShell öffnen
   git --version
   # Sollte ausgeben: git version 2.43.0
   ```

---

## 🎯 Schritt 5: Satisfactory Modding Setup

### 5.1 Satisfactory (das Spiel) installieren
**Erforderlich, auch wenn du nur Server-Mod machst!**

1. **Via Steam:**
   ```
   Steam öffnen
   → Bibliothek
   → "Satisfactory" suchen
   → Installieren
   ```
   - **Größe:** ~30 GB
   - **Pfad notieren:** z.B. `C:\Program Files (x86)\Steam\steamapps\common\Satisfactory`

2. **Via Epic Games:**
   ```
   Epic Games Launcher
   → Store
   → "Satisfactory" suchen
   → Installieren
   ```

### 5.2 Satisfactory Mod Manager installieren
1. **Download:** https://github.com/satisfactorymodding/SatisfactoryModManager/releases/latest
   - Datei: `Satisfactory-Mod-Manager-Setup-X.X.X.exe`
   - Größe: ~100 MB

2. **Installation:**
   ```
   Setup ausführen
   → Standard-Installation
   → SMM starten
   → Satisfactory-Installationspfad auswählen
   ```

### 5.3 Wwise SDK installieren
**Benötigt für Audio in Unreal Engine Mods**

1. **Account erstellen:**
   - https://www.audiokinetic.com/
   - Kostenlos registrieren

2. **Wwise Launcher herunterladen:**
   - https://www.audiokinetic.com/download/
   - Wwise Launcher installieren

3. **Wwise 2022.1 installieren:**
   ```
   Wwise Launcher öffnen
   → WWISE Tab
   → "Install New Version"
   → Version: 2022.1.x (passend zu UE 5.3)
   → SDK installieren
   ```
   - **Größe:** ~5 GB

### 5.4 Satisfactory Modding Documentation & Starter Project

1. **Dokumentation:**
   - https://docs.ficsit.app
   - Lies Abschnitt: "Getting Started" → "Development Environment"

2. **Starter Project klonen:**
   ```powershell
   # In PowerShell:
   cd C:\Projects
   git clone https://github.com/satisfactorymodding/SatisfactoryModLoader.git
   cd SatisfactoryModLoader
   ```

3. **Projekt generieren:**
   ```powershell
   # Rechtsklick auf .uproject Datei
   → "Generate Visual Studio project files"
   # Falls nicht vorhanden, in Unreal Engine:
   → File → Generate Visual Studio Project
   ```

---

## 🔧 Schritt 6: Alpakit (Packaging Tool) einrichten

### Installation
1. **Im Satisfactory Mod Manager:**
   ```
   SMM öffnen
   → Tab "Mods"
   → Suche "SML"
   → Installiere neueste Version
   ```

2. **Alpakit Plugin:**
   - Wird automatisch mit SML installiert
   - Zu finden in: `<Satisfactory>/FactoryGame/Mods/Alpakit/`

3. **In Unreal Engine aktivieren:**
   ```
   Unreal Engine Projekt öffnen
   → Edit → Plugins
   → Suche "Alpakit"
   → Aktivieren
   → Editor neu starten
   ```

---

## 🚀 Schritt 7: Satisfactory Plus Server Mod kompilieren

### 7.1 Starter Project Setup
1. **Neues Mod-Projekt erstellen:**
   ```
   Satisfactory Starter Project öffnen (UE5)
   → File → New Plugin
   → Type: "Blank"
   → Name: "SatisfactoryPlusServer"
   → Create
   ```

2. **Unseren Code einfügen:**
   ```powershell
   cd C:\Projects\SatisfactoryProject\Plugins
   git clone https://github.com/X3S2/Satisfactory-Plus-Server.git SatisfactoryPlusServer
   ```

### 7.2 Dependencies hinzufügen
1. **In Unreal Engine:**
   ```
   Content Browser öffnen
   → Rechtsklick auf SatisfactoryPlusServer Plugin
   → "Edit Plugin"
   ```

2. **Dependencies in .uplugin hinzufügen:**
   ```json
   "Plugins": [
       {
           "Name": "SML",
           "Enabled": true
       }
   ]
   ```

### 7.3 Kompilieren
1. **Visual Studio:**
   ```
   .uproject Datei → Rechtsklick
   → "Generate Visual Studio project files"
   
   .sln Datei in Visual Studio öffnen
   → Build → Build Solution (Ctrl+Shift+B)
   ```

2. **Warte auf Kompilierung:**
   - Dauer: 10-30 Minuten (beim ersten Mal)
   - Bei Erfolg: "Build succeeded"

### 7.4 Packaging mit Alpakit
1. **In Unreal Engine:**
   ```
   Toolbar → Alpakit → Alpakit
   → "SatisfactoryPlusServer" auswählen
   → "Package" klicken
   ```

2. **Output:**
   ```
   Findet ihr in:
   <Satisfactory>/FactoryGame/Mods/SatisfactoryPlusServer.zip
   ```

---

## 📦 Schritt 8: Mod installieren & testen

### 8.1 Auf lokalem Client testen
1. **Mod kopieren:**
   ```powershell
   # Entpacke SatisfactoryPlusServer.zip nach:
   C:\...\Satisfactory\FactoryGame\Mods\SatisfactoryPlusServer\
   ```

2. **Satisfactory Plus installieren:**
   ```
   SMM → Mods → "Satisfactory Plus" → Install (v1.2.3)
   ```

3. **Spiel starten:**
   ```
   Über SMM starten
   → Prüfe Logs:
   %LOCALAPPDATA%\FactoryGame\Saved\Logs\FactoryGame.log
   
   Suche nach:
   "[SatisfactoryPlusServer] Module starting"
   ```

### 8.2 Auf Server installieren
1. **Mod auf Server kopieren:**
   ```powershell
   # Per RDP/FTP auf Server:
   Kopiere SatisfactoryPlusServer\ nach:
   <SatisfactoryServer>\FactoryGame\Mods\SatisfactoryPlusServer\
   ```

2. **Server starten:**
   ```powershell
   cd C:\SatisfactoryServer
   .\FactoryServer.exe -log
   ```

3. **Logs prüfen:**
   ```powershell
   Get-Content "FactoryGame\Saved\Logs\FactoryGame.log" -Tail 50 | Select-String "SatisfactoryPlusServer"
   ```

---

## ❓ Troubleshooting

### Problem: Unreal Engine findet Visual Studio nicht
**Lösung:**
```
1. Visual Studio schließen
2. Unreal Engine schließen
3. Windows Registry bereinigen:
   - Drücke Win+R
   - Gebe ein: regedit
   - Navigiere zu: HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\
   - Prüfe, ob VS 2022 registriert ist
4. VS 2022 Repair ausführen
```

### Problem: "Missing modules" Fehler
**Lösung:**
```powershell
# Rechtsklick auf .uproject
→ "Switch Unreal Engine version"
→ Wähle richtige UE Version
→ "Generate Visual Studio project files"
```

### Problem: Alpakit findet Plugin nicht
**Lösung:**
```
1. Prüfe, ob Plugin in Plugins\ Ordner ist
2. Edit → Plugins → "Show: All Plugins"
3. Suche "SatisfactoryPlusServer"
4. Aktiviere es
5. Editor neu starten
```

### Problem: Build-Fehler "Cannot find SML"
**Lösung:**
```
1. Satisfactory Plus via SMM installieren
2. SML wird automatisch installiert
3. In .uplugin Dependencies prüfen
4. Visual Studio Projekt neu generieren
```

---

## 📚 Hilfreiche Ressourcen

- **Satisfactory Modding Dokumentation:** https://docs.ficsit.app
- **Discord:** https://discord.gg/satisfactory-modding (Kanal: #modding-help)
- **Unreal Engine Dokumentation:** https://docs.unrealengine.com/5.3
- **Video-Tutorial (Englisch):** https://www.youtube.com/satisfactorymodding

---

## ⏱️ Zeitplan-Übersicht

| Schritt | Aktivität | Download | Installation | Konfiguration |
|---------|-----------|----------|--------------|---------------|
| 1 | Epic Games Launcher | 5min | 5min | - |
| 2 | Unreal Engine 5.3 | 2-3h | 30min | 30min |
| 3 | Visual Studio 2022 | 30min | 1-2h | 15min |
| 4 | Git | 2min | 5min | - |
| 5 | Satisfactory & Tools | 1h | 30min | 1h |
| 6 | Alpakit | - | 10min | 30min |
| 7 | Mod kompilieren | - | 30min | - |
| 8 | Testen | - | 10min | 30min |
| **GESAMT** | | **~4-5h** | **~3-4h** | **~3h** |

**Gesamtzeit: 10-12 Stunden** (bei guter Internetverbindung)

---

## 💾 Speicherplatz-Übersicht

| Komponente | Größe |
|-----------|-------|
| Epic Games Launcher | 500 MB |
| Unreal Engine 5.3 | 45 GB |
| Visual Studio 2022 | 25 GB |
| Git | 300 MB |
| Satisfactory (Spiel) | 30 GB |
| Wwise SDK | 5 GB |
| Build-Artefakte | 10 GB |
| **GESAMT** | **~115 GB** |

---

**Viel Erfolg beim Kompilieren!** 🚀

Bei Fragen: [GitHub Issues](https://github.com/X3S2/Satisfactory-Plus-Server/issues)
