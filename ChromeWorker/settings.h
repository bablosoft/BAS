#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>

class settings
{
    bool use_flash;
    int skip_frames;
    bool force_utf8;
    int toolbox_height;
    int scenario_width;
    bool is_safe;
    int zoom;
    bool maximized;
    bool restart;
    bool emulate_mouse;
    bool proxies_reconnect;
    bool debug_toolbox;
    bool debug_scenario;
public:
    settings();
    bool UseFlash();
    bool IsSafe();
    bool ProxiesReconnect();
    bool ForceUtf8();
    bool Maximized();
    bool DebugToolbox();
    bool DebugScenario();
    bool EmulateMouse();
    void SetMaximized(bool Maximized);
    int SkipFrames();
    int ToolboxHeight();
    int ScenarioWidth();
    int Zoom();

    void SetToolboxHeight(int height);
    void SetScenarioWidth(int width);

    void SetProxiesReconnect(bool proxies_reconnect);
    void SetForceUtf8(bool force_utf8);
    void SetSkipFrames(int skip_frames);


    void SaveToFile();
    std::string Serialize();
    void Deserialize(const std::string & Data);
    void ParseCommandLine(std::vector<std::wstring>& Params);
    void Init();
};

#endif // SETTINGS_H
