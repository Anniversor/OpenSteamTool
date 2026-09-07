#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Config {

    enum class LogLevel { Trace, Debug, Info, Warn, Error };

    struct ManifestTimeouts {
        uint32_t resolve = 5000;
        uint32_t connect = 5000;
        uint32_t send    = 10000;
        uint32_t recv    = 10000;
    };

    struct InjectionSettings {
        bool enabled = false;
        std::string libraryX86;
        std::string libraryX64;
    };

    struct CloudSettings {
        bool enabled = false;
        std::string library;
        // appids present in Lua that should NOT be redirected through
        // CloudRedirect (e.g. family-shared games added only to lift the
        // sharing restriction). Their Steam Cloud RPCs pass through to Valve.
        std::vector<uint32_t> excludeAppIds;
        // When true, apps that OpenSteamTool detects as genuinely owned (a real
        // license, or an active Steam Family Sharing license) are automatically
        // exempted from redirection so their official Steam Cloud is used.
        bool excludeOwned = false;
    };

    struct LoadResult {
        bool applied = false;
        bool luaPathsChanged = false;
    };

    LoadResult Load(const std::string& configPath);

    ManifestTimeouts GetManifestTimeouts();
    LogLevel GetLogLevel();
    std::string GetLogDir();
    std::vector<std::string> GetLuaPaths();
    std::string GetRemoteUrlTemplate();
    InjectionSettings GetInjectionSettings();
    CloudSettings GetCloudSettings();
    bool GetStatsEnableApi();

    // [manifest] — provider selection lives in ManifestClient (table-driven).
    inline uint32_t manifestTimeoutResolve = 5000;
    inline uint32_t manifestTimeoutConnect = 5000;
    inline uint32_t manifestTimeoutSend    = 10000;
    inline uint32_t manifestTimeoutRecv    = 10000;

    // [log]
    inline LogLevel logLevel = LogLevel::Debug;

    // derived from configPath: <steam>/opensteamtool/
    inline std::string logDir;

    // [lua]
    inline std::vector<std::string> luaPaths;

    // [remote]
    inline std::string remoteUrlTemplate;

    // [stats]
    inline bool statsEnableApi = true;

    // [inject] - optional library injection into game processes.
    inline bool injectEnabled = false;
    inline std::string injectLibraryX86;
    inline std::string injectLibraryX64;

    // [cloud] - optional Steam Cloud save redirection via CloudRedirect.
    inline bool cloudEnabled = false;
    inline std::string cloudLibrary;
    inline std::vector<uint32_t> cloudExcludeAppIds;
    inline bool cloudExcludeOwned = false;

}
