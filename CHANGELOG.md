# Changelog

Alle wichtigen Änderungen an diesem Projekt werden in dieser Datei dokumentiert.

Das Format basiert auf [Keep a Changelog](https://keepachangelog.com/de/1.0.0/),
und dieses Projekt folgt [Semantic Versioning](https://semver.org/lang/de/).

## [1.2.3] - 2025-12-29

### Hinzugefügt
- Initiales Release des Server-Kompatibilitäts-Plugins
- `UServerGuards` Blueprint Function Library für Server/Client-Checks
  - `HasAuthority()` - Prüft ob Server-Authority vorhanden
  - `IsDedicatedServer()` - Prüft ob Dedicated Server
  - `IsClient()` - Prüft ob Client
  - `IsStandalone()` - Prüft ob Singleplayer
  - `ServerSafeLog()` - Kontextbewusstes Logging
- `UServerCompatibilitySubsystem` Game Instance Subsystem
  - Automatische Versions-Validierung
  - Runtime-Kompatibilitätsprüfungen
  - Dependency-Checks für SatisfactoryPlus
- Dedicated Server Unterstützung für SatisfactoryPlus v1.2.3
- Netzwerk-Replikations-Optimierungen
- Server-Authority-Guards für Gameplay-Logik
- Client-Code-Isolation (UI, Cosmetics)
- Konfigurierbare Server-Einstellungen via INI
- Umfassende Dokumentation (README.md)
- Build-System (Build.cs)
- SML 3.11.1+ Integration
- Windows & Linux Server Support

### Kompatibilität
- Satisfactory 1.1+ (Build 365306+)
- SML ^3.11.1
- Satisfactory Plus ^1.2.3

### Bekannte Einschränkungen
- Erfordert Installation auf Server UND allen Clients
- Exakte Versions-Übereinstimmung erforderlich (Server 1.2.3 = Client 1.2.3)
- Keine offizielle Unterstützung durch KMods (Community-Projekt)

---

## Versions-Historie

Diese Mod folgt der Versionsnummer von Satisfactory Plus.
Version 1.2.3 korrespondiert mit Satisfactory Plus v1.2.3.

Zukünftige Versionen werden synchron mit Satisfactory Plus Updates veröffentlicht.
