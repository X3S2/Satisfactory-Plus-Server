# 🚀 SCHNELLSTART: Automatische Kompilierung

Für alle, die sich nicht mit Unreal Engine & Visual Studio auskennen!

## ⚡ Ein-Klick Installation

### Voraussetzungen (müssen installiert sein):
- ✅ Unreal Engine 5.3+
- ✅ Visual Studio 2022 (mit C++)
- ✅ Git
- ✅ Satisfactory (das Spiel)

**→ Siehe [BUILD_GUIDE.md](BUILD_GUIDE.md) für Installation**

---

## 🎯 So geht's:

### Schritt 1: PowerShell öffnen
```powershell
# Rechtsklick auf Windows Start-Button
→ "Windows PowerShell (Administrator)"
```

### Schritt 2: Execution Policy setzen
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
# Bei Nachfrage: "Ja" (J) eingeben
```

### Schritt 3: Script herunterladen & ausführen
```powershell
# In dein Arbeitsverzeichnis wechseln (z.B.)
cd C:\

# Repository klonen
git clone https://github.com/X3S2/Satisfactory-Plus-Server.git
cd Satisfactory-Plus-Server

# Script ausführen
.\Build-AutoCompile.ps1
```

### Schritt 4: Warten ☕
Das Script macht automatisch:
- ✅ Unreal Engine finden
- ✅ Satisfactory Installation finden
- ✅ Starter Project herunterladen
- ✅ Mod-Code herunterladen
- ✅ Visual Studio Project generieren
- ✅ Kompilierung durchführen

**Dauer: 15-30 Minuten**

### Schritt 5: Manuelles Packaging (einmal)
Das Script öffnet dann Unreal Engine für dich. Du musst nur:
```
1. Warte bis Editor geladen ist
2. Edit → Plugins → Suche "Alpakit" → Aktiviere es → Restart
3. Nach Neustart: Tools → Alpakit → Wähle "SatisfactoryPlusServer" → Package
4. Warte 5-10 Minuten
5. Fertig!
```

---

## 📍 Fertige Mod-Dateien

Nach dem Packaging findest du die Mod hier:
```
<Satisfactory>\FactoryGame\Mods\SatisfactoryPlusServer\
```

Oder als ZIP:
```
<Satisfactory>\FactoryGame\Mods\SatisfactoryPlusServer.zip
```

---

## 🔧 Manuelle Parameter (optional)

Falls das Script Pfade nicht findet:
```powershell
.\Build-AutoCompile.ps1 `
    -UnrealEnginePath "C:\Program Files\Epic Games\UE_5.3" `
    -SatisfactoryPath "C:\Steam\steamapps\common\Satisfactory"
```

---

## ❓ Troubleshooting

### Problem: "Script kann nicht geladen werden"
**Lösung:**
```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
.\Build-AutoCompile.ps1
```

### Problem: "Unreal Engine nicht gefunden"
**Lösung:**
```powershell
# Finde deinen UE5 Pfad:
Get-ChildItem "C:\Program Files\Epic Games" -Directory

# Dann mit Parameter:
.\Build-AutoCompile.ps1 -UnrealEnginePath "DeinGefundenerPfad"
```

### Problem: "Git nicht gefunden"
**Lösung:**
```powershell
# Git installieren:
# https://git-scm.com/download/win
# Dann PowerShell NEU öffnen
```

### Problem: "Kompilierung fehlgeschlagen"
**Lösung:**
```
1. Prüfe ob Visual Studio 2022 installiert ist
2. Prüfe ob "Desktop development with C++" Workload installiert ist
3. Prüfe Logs in:
   %USERPROFILE%\Documents\SatisfactoryModding\SatisfactoryModLoader\Saved\Logs\
```

---

## 🎥 Was das Script macht (im Detail)

```
1. Sucht Unreal Engine Installation
2. Sucht Satisfactory Installation
3. Erstellt Arbeitsverzeichnis: %USERPROFILE%\Documents\SatisfactoryModding
4. Klont Satisfactory Starter Project von GitHub
5. Klont unsere Mod von GitHub
6. Generiert Visual Studio Project Files
7. Kompiliert mit UnrealBuildTool
8. Öffnet Editor für Alpakit-Packaging
9. Zeigt dir, wo die fertigen Dateien sind
```

---

## 💡 Vorteile dieser Methode

✅ **Keine GUI-Navigation nötig**
✅ **Automatische Pfad-Erkennung**
✅ **Klare Fehler-Meldungen**
✅ **Wiederholbar & Skriptbar**
✅ **Zeitsparend**

---

## 📚 Weitere Hilfe

- **Detaillierte Anleitung:** [BUILD_GUIDE.md](BUILD_GUIDE.md)
- **GitHub Issues:** https://github.com/X3S2/Satisfactory-Plus-Server/issues
- **Discord:** https://discord.gg/satisfactory-modding

---

**Viel Erfolg!** 🚀
