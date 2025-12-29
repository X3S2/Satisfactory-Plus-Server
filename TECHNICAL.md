# Technical Documentation

Technische Dokumentation für Entwickler, die mit Satisfactory Plus Server arbeiten.

## 📐 Architektur

### Komponenten-Übersicht

```
SatisfactoryPlusServer/
├── Module (FSatisfactoryPlusServerModule)
│   ├── Initialization/Shutdown
│   ├── Server Patches
│   └── Replication Setup
│
├── Subsystem (UServerCompatibilitySubsystem)
│   ├── Runtime Checks
│   ├── Version Validation
│   └── Dependency Management
│
└── Utilities (UServerGuards)
    ├── HasAuthority()
    ├── IsDedicatedServer()
    ├── IsClient()
    └── ServerSafeLog()
```

### Module Lifecycle

1. **Module Startup** (`StartupModule()`)
   ```cpp
   ValidateServerEnvironment()
   → InitializeServerPatches()
   → SetupReplicationSupport()
   ```

2. **Subsystem Initialize** (`Initialize()`)
   ```cpp
   ValidateModCompatibility()
   → IsSatisfactoryPlusLoaded()
   → ValidateVersionCompatibility()
   ```

3. **Runtime**
   - Server Guards aktiv
   - Replication läuft
   - Logging aktiv

4. **Shutdown** (`ShutdownModule()` / `Deinitialize()`)
   - Cleanup
   - Resource-Freigabe

---

## 🔧 API-Referenz

### UServerGuards (Blueprint Function Library)

#### `HasAuthority(WorldContext) -> bool`
Prüft ob der aufrufende Context Server-Authority hat.

**Return:**
- `true`: Server oder Standalone (Singleplayer)
- `false`: Client

**Verwendung:**
```cpp
if (UServerGuards::HasAuthority(this))
{
    // Server-side Gameplay-Logik
    SpawnItem();
    ProcessRecipe();
}
```

**Blueprint:**
```
Branch(HasAuthority)
├─ True: Server Logic
└─ False: Skip
```

---

#### `IsDedicatedServer(WorldContext) -> bool`
Prüft ob auf einem Dedicated Server ausgeführt wird.

**Return:**
- `true`: Dedicated Server
- `false`: Client oder Standalone

**Verwendung:**
```cpp
if (!UServerGuards::IsDedicatedServer(this))
{
    // Client-only Code (UI, Cosmetics)
    UpdateUI();
    PlaySound();
}
```

**Wichtig:** Verhindert dass UI-Code auf Server läuft!

---

#### `IsClient(WorldContext) -> bool`
Prüft ob als Client ausgeführt wird.

**Return:**
- `true`: Client (Multiplayer)
- `false`: Server oder Standalone

**Verwendung:**
```cpp
if (UServerGuards::IsClient(this))
{
    // Client-spezifischer Code
    RenderEffect();
    UpdateLocalUI();
}
```

---

#### `IsStandalone(WorldContext) -> bool`
Prüft ob im Standalone-Modus (Singleplayer).

**Return:**
- `true`: Singleplayer
- `false`: Multiplayer (Server oder Client)

---

#### `ServerSafeLog(Message, WorldContext)`
Logging mit automatischem Context-Präfix.

**Output:**
```
[SatisfactoryPlusServer] [SERVER] Message
[SatisfactoryPlusServer] [CLIENT] Message
[SatisfactoryPlusServer] [STANDALONE] Message
```

**Verwendung:**
```cpp
UServerGuards::ServerSafeLog(TEXT("Processing recipe"), this);
```

---

### UServerCompatibilitySubsystem (Game Instance Subsystem)

#### `GetCompatibilityVersion() -> FString`
Gibt die Version des Compatibility-Layers zurück.

**Return:** `"1.2.3"`

---

#### `IsCompatibilityActive() -> bool`
Prüft ob das Subsystem aktiv ist.

**Return:**
- `true`: Subsystem erfolgreich initialisiert
- `false`: Initialization fehlgeschlagen

---

#### `ValidateModCompatibility() -> bool`
Führt vollständige Kompatibilitätsprüfung durch.

**Checks:**
1. SatisfactoryPlus Plugin geladen?
2. SatisfactoryPlus Plugin enabled?
3. Version-Match (1.2.3)?

**Return:**
- `true`: Alle Checks bestanden
- `false`: Mindestens ein Check fehlgeschlagen

---

## 🌐 Network Replication

### Replication Patterns

#### Server-Authority Pattern
```cpp
void AMyActor::DoSomething()
{
    if (UServerGuards::HasAuthority(this))
    {
        // Server führt Logik aus
        ProcessLogic();
        
        // Repliziert an Clients
        MulticastUpdateClients();
    }
}

UFUNCTION(NetMulticast, Reliable)
void AMyActor::MulticastUpdateClients_Implementation()
{
    // Wird auf allen Clients ausgeführt
    UpdateVisuals();
}
```

#### Client-to-Server RPC
```cpp
// Client ruft auf
UFUNCTION(BlueprintCallable)
void AMyActor::RequestAction()
{
    ServerRequestAction();
}

UFUNCTION(Server, Reliable)
void AMyActor::ServerRequestAction_Implementation()
{
    // Nur Server führt aus
    if (UServerGuards::HasAuthority(this))
    {
        PerformAction();
    }
}
```

#### UI-Guard Pattern
```cpp
void AMyActor::UpdateDisplay()
{
    // Nur auf Client ausführen
    if (!UServerGuards::IsDedicatedServer(this))
    {
        UpdateUIWidget();
        PlayUISound();
    }
}
```

---

## ⚙️ Configuration System

### INI-Struktur

#### `Config/DefaultGame.ini`
```ini
[/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem]

; Core Settings
bEnableServerPatches=True
bEnableReplicationOptimizations=True
bStrictVersionChecking=True

; Logging
ServerLogLevel=3          ; 0=None, 1=Error, 2=Warning, 3=Log, 4=Verbose
bEnableDebugLogging=False
```

#### `Config/DefaultEngine.ini`
```ini
[/Script/OnlineSubsystemUtils.IpNetDriver]
NetServerMaxTickRate=60
MaxNetTickRate=60
MaxInternetClientRate=100000
MaxClientRate=100000
ConnectionTimeout=30.0
InitialConnectTimeout=120.0
```

### Konfiguration auslesen (C++)
```cpp
bool bStrictChecking = true;
GConfig->GetBool(
    TEXT("/Script/SatisfactoryPlusServer.ServerCompatibilitySubsystem"),
    TEXT("bStrictVersionChecking"),
    bStrictChecking,
    GGameIni
);
```

---

## 🔍 Debugging

### Log-Kategorien

**Module:**
```cpp
UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] ..."));
```

**Subsystem:**
```cpp
UE_LOG(LogTemp, Log, TEXT("[SatisfactoryPlusServer] Subsystem: ..."));
```

**Server Guards:**
```cpp
UServerGuards::ServerSafeLog(TEXT("Debug message"), WorldContext);
```

### Debugging-Workflow

1. **Enable Debug Logging:**
   ```ini
   bEnableDebugLogging=True
   ServerLogLevel=4
   ```

2. **Monitor Logs:**
   ```powershell
   # Live-Monitoring
   Get-Content "FactoryGame\Saved\Logs\FactoryGame.log" -Wait | Select-String "SatisfactoryPlusServer"
   ```

3. **Breakpoints (C++):**
   - Visual Studio: F9
   - Attach to Process: `FactoryServer.exe` oder `FactoryGame-Win64-Shipping.exe`

4. **Blueprint Debugging:**
   - Verwende `Print String` mit `ServerSafeLog()`
   - Blueprint Debugger nur für Client-Side Code

---

## 🧪 Testing

### Unit Tests (zukünftig)

Struktur für Tests:
```cpp
// Tests/ServerGuardsTests.cpp
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FServerGuardsTest,
    "SatisfactoryPlusServer.ServerGuards.HasAuthority",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter
)

bool FServerGuardsTest::RunTest(const FString& Parameters)
{
    // Test Setup
    UWorld* TestWorld = CreateTestWorld();
    
    // Test HasAuthority
    bool bHasAuth = UServerGuards::HasAuthority(TestWorld);
    TestTrue(TEXT("Standalone should have authority"), bHasAuth);
    
    return true;
}
```

### Integration Tests

**Server Start Test:**
```powershell
# Start Server
Start-Process "FactoryServer.exe" -ArgumentList "-log"
Start-Sleep 30

# Check Logs
$LogContent = Get-Content "FactoryGame\Saved\Logs\FactoryGame.log"
$InitSuccess = $LogContent | Select-String "Server compatibility layer initialized successfully"

if ($InitSuccess) {
    Write-Host "✅ Server started successfully"
} else {
    Write-Host "❌ Server initialization failed"
}
```

**Client Connection Test:**
```cpp
// Pseudo-Code
ConnectToServer("127.0.0.1:7777")
Wait(10 seconds)
AssertTrue(IsConnected())
AssertTrue(AllModsLoaded())
```

---

## 📦 Build System

### Build.cs Konfiguration

```csharp
public class SatisfactoryPlusServer : ModuleRules
{
    public SatisfactoryPlusServer(ReadOnlyTargetRules Target) : base(Target)
    {
        // Public Dependencies (exposed in headers)
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "SML",
            "FactoryGame"
        });

        // Private Dependencies (implementation only)
        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Json",
            "JsonUtilities"
        });

        // Server-specific definitions
        if (Target.Type == TargetType.Server)
        {
            PublicDefinitions.Add("UE_SERVER=1");
        }
    }
}
```

### Compile-Time Checks

```cpp
#if UE_SERVER
    // Server-only Code
    UE_LOG(LogTemp, Log, TEXT("Compiled for Dedicated Server"));
#else
    // Client/Standalone Code
    UE_LOG(LogTemp, Log, TEXT("Compiled for Client"));
#endif
```

---

## 🔐 Best Practices

### DO ✅

1. **Immer Authority prüfen:**
   ```cpp
   if (HasAuthority()) { /* Gameplay Logic */ }
   ```

2. **UI-Code guarden:**
   ```cpp
   if (!IsDedicatedServer()) { /* UI Updates */ }
   ```

3. **Replizierte Properties markieren:**
   ```cpp
   UPROPERTY(Replicated)
   int32 MyValue;
   ```

4. **RPC verwenden für Client-Server Kommunikation:**
   ```cpp
   UFUNCTION(Server, Reliable)
   void ServerDoSomething();
   ```

5. **Logs mit Context:**
   ```cpp
   ServerSafeLog(TEXT("Action performed"), this);
   ```

### DON'T ❌

1. **Keine UI-Calls auf Server:**
   ```cpp
   // BAD:
   UpdateWidget(); // Crash auf Dedicated Server!
   
   // GOOD:
   if (!IsDedicatedServer()) {
       UpdateWidget();
   }
   ```

2. **Keine Gameplay-Logik auf Client:**
   ```cpp
   // BAD:
   if (IsClient()) {
       GivePlayerItem(); // Wird nicht repliziert!
   }
   
   // GOOD:
   if (HasAuthority()) {
       GivePlayerItem(); // Server entscheidet
   }
   ```

3. **Keine blockierenden Operationen:**
   ```cpp
   // BAD:
   Sleep(1000); // Friert Server ein!
   
   // GOOD:
   GetWorldTimerManager().SetTimer(...); // Asynchron
   ```

---

## 📚 Ressourcen

- **Unreal Engine Networking:** https://docs.unrealengine.com/5.3/en-US/networking-overview-for-unreal-engine/
- **Satisfactory Modding Docs:** https://docs.ficsit.app
- **SML Documentation:** https://github.com/satisfactorymodding/SatisfactoryModLoader
- **Blueprint API:** Verfügbar in Unreal Editor unter "Server Guards"

---

**Version:** 1.2.3  
**Letzte Aktualisierung:** 29.12.2025
