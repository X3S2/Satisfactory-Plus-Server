# Satisfactory Plus Server

![Version](https://img.shields.io/badge/version-1.2.3-blue)
![Satisfactory](https://img.shields.io/badge/Satisfactory-1.1-orange)
![SML](https://img.shields.io/badge/SML-3.11.1-green)

**Dedicated Server Compatibility Layer für Satisfactory Plus v1.2.3**

Dieses Plugin ermöglicht die volle **Multiplayer- und Dedicated-Server-Unterstützung** für die Mod [Satisfactory Plus](https://ficsit.app/mod/SatisfactoryPlus), ohne deren Gameplay, Balancing oder Inhalte zu verändern.

---

## ⚠️ Wichtiger Hinweis

**Satisfactory Plus ist derzeit als "Multiplayer nicht unterstützt" gekennzeichnet.**

Dieses Plugin ist ein **Community-Projekt**, das Server-Kompatibilität durch:
- Netzwerk-Replikations-Patches
- Server-Authority-Guards
- Client-Code-Isolation
- Dedicated-Server-Optimierungen

**bereitstellt, ohne die Original-Mod zu modifizieren.**

---

## 📋 Voraussetzungen

| Komponente | Version | Erforderlich |
|-----------|---------|--------------|
| **Satisfactory** | 1.1+ (Build 365306+) | ✅ Ja |
| **SML** | ^3.11.1 | ✅ Ja |
| **Satisfactory Plus** | 1.2.3 | ✅ Ja |

---

## 🚀 Installation

### Für Server-Betreiber

1. **Satisfactory Dedicated Server** installieren (Version 1.1+)
2. **Satisfactory Mod Manager (SMM)** installieren
3. Folgende Mods installieren:
   - **SML** (Version 3.11.1 oder höher)
   - **Satisfactory Plus** (Version 1.2.3)
   - **Satisfactory Plus Server** (dieses Plugin, Version 1.2.3)

4. Server starten:
```powershell
.\FactoryServer.exe
```

### Für Clients (Spieler)

1. **Satisfactory Mod Manager (SMM)** installieren
2. Folgende Mods installieren:
   - **SML** (Version 3.11.1 oder höher)
   - **Satisfactory Plus** (Version 1.2.3)
   - **Satisfactory Plus Server** (Version 1.2.3) ← **Wichtig: Auch auf Client!**

3. Spiel starten und Server beitreten

---

## 🔧 Konfiguration

### Server-Einstellungen

Die Konfiguration erfolgt in `Config/DefaultGame.ini`:

```ini
[/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem]
; Server-Patches aktivieren
bEnableServerPatches=True

; Replikations-Optimierungen
bEnableReplicationOptimizations=True

; Strikte Versions-Prüfung
bStrictVersionChecking=True

; Log-Level (0=None, 1=Error, 2=Warning, 3=Log, 4=Verbose)
ServerLogLevel=3

; Debug-Logging für Fehlersuche
bEnableDebugLogging=False
```

---

## 📦 Was macht dieses Plugin?

### ✅ Server-Guards
- **HasAuthority**-Checks für Gameplay-Logik
- **IsDedicatedServer**-Guards für Client-Code
- Verhindert UI-Ausführung auf dem Server
- Isoliert kosmetische Effekte

### ✅ Netzwerk-Replikation
- Stellt sicher, dass alle Gameplay-relevanten Actors repliziert werden
- Konfiguriert Replikationsbedingungen
- Implementiert RPC-Support wo nötig

### ✅ Kompatibilitätsprüfungen
- Validiert SatisfactoryPlus-Installation
- Prüft Versions-Kompatibilität (1.2.3)
- Warnt bei Inkonsistenzen

### ✅ Runtime-Subsystem
- `UServerCompatibilitySubsystem` für Verwaltung
- Blueprint-zugängliche Utility-Funktionen
- Umfassendes Logging

---

## 🎮 Verwendung in Blueprints

Dieses Plugin stellt Blueprint-Nodes bereit:

```blueprint
// Prüfen ob Server-Authority vorhanden
HasAuthority(WorldContext) -> bool

// Prüfen ob Dedicated Server
IsDedicatedServer(WorldContext) -> bool

// Prüfen ob Client
IsClient(WorldContext) -> bool

// Sichere Log-Ausgabe mit Kontext
ServerSafeLog(Message, WorldContext)
```

**Beispiel:**
```cpp
// Nur auf Server ausführen
if (HasAuthority(this)) {
    // Gameplay-Logik hier
}

// Nur auf Client ausführen
if (IsClient(this)) {
    // UI-Updates, Cosmetics hier
}
```

---

## 📊 Versions-Kompatibilität

| SatisfactoryPlusServer | SatisfactoryPlus | Kompatibel |
|-----------------------|------------------|-----------|
| **1.2.3** | **1.2.3** | ✅ Vollständig |
| 1.2.3 | 1.2.2 | ⚠️ Nicht getestet |
| 1.2.3 | 1.3.0+ | ❌ Nicht kompatibel |

**Wichtig:** Server und alle Clients **müssen exakt die gleichen Versionen** verwenden:
- SatisfactoryPlus: 1.2.3
- SatisfactoryPlusServer: 1.2.3

---

## 🛠️ Entwicklung & Build

### Build-Voraussetzungen
- Unreal Engine 5.3+ (Satisfactory SDK)
- Visual Studio 2022
- Satisfactory Modding Toolkit

### Projekt kompilieren

1. Projekt klonen:
```powershell
git clone https://github.com/X3S2/Satisfactory-Plus-Server.git
cd Satisfactory-Plus-Server
```

2. Unreal Engine Projekt generieren:
```powershell
# Falls vorhanden, UE4 Project Generator verwenden
.\GenerateProjectFiles.bat
```

3. In Visual Studio öffnen und kompilieren

4. Plugin testen:
```powershell
# Packaging für Release
# [Details zum Packaging-Prozess hinzufügen]
```

---

## 🐛 Bekannte Probleme & Troubleshooting

### Server startet nicht
- ✅ Prüfe, ob SatisfactoryPlus 1.2.3 installiert ist
- ✅ Prüfe SML-Version (^3.11.1 erforderlich)
- ✅ Schaue in die Server-Logs: `FactoryGame/Saved/Logs/`

### Clients können nicht beitreten
- ✅ Stelle sicher, dass **alle Spieler** SatisfactoryPlusServer installiert haben
- ✅ Versions-Mismatch? Prüfe SMM-Installation
- ✅ Firewall/Ports geöffnet?

### Crashes bei bestimmten Features
- ⚠️ Melde das Problem auf GitHub Issues mit:
  - Server-Log
  - Client-Log
  - Genaue Schritte zur Reproduktion

---

## 📜 Lizenz

**Copyright (c) 2025 X3S2**

Dieses Projekt ist ein unabhängiges Community-Plugin für Satisfactory Plus.

**Satisfactory Plus** ist Copyright von **KMods / Kyrium**.  
Dieses Plugin modifiziert die Original-Mod **nicht** und respektiert alle Urheberrechte.

---

## 🙏 Credits

- **Kyrium** – Entwickler von Satisfactory Plus
- **KMods Team** – Original-Mod-Entwicklung
- **Coffee Stain Studios** – Satisfactory & Modding-Support
- **Satisfactory Modding Community** – Tools & Dokumentation

---

## 🔗 Links

- **Satisfactory Plus (Original):** https://ficsit.app/mod/SatisfactoryPlus
- **Dieses Projekt (GitHub):** https://github.com/X3S2/Satisfactory-Plus-Server
- **Bug Reports:** https://github.com/X3S2/Satisfactory-Plus-Server/issues
- **SML Dokumentation:** https://docs.ficsit.app
- **Satisfactory Modding Discord:** https://discord.gg/satisfactory-modding

---

## ⚡ Support & Community

**Hast du Probleme oder Fragen?**
1. Schaue in die [FAQ](#-bekannte-probleme--troubleshooting)
2. Prüfe [GitHub Issues](https://github.com/X3S2/Satisfactory-Plus-Server/issues)
3. Erstelle ein neues Issue mit detaillierten Informationen

---

**Made with ❤️ by the Satisfactory Modding Community**

*Dieses Projekt steht in keiner offiziellen Verbindung zu Coffee Stain Studios oder KMods.*
