#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class settings
{
    bool use_flash;
    int skip_frames;
    bool force_utf8;
    int toolbox_height;
    int scenario_width;
    int zoom;
    bool maximized;
    bool restart;
    void SaveToFile();
public:
    settings();
    bool UseFlash();
    bool ForceUtf8();
    bool Maximized();
    void SetMaximized(bool Maximized);
    int SkipFrames();
    int ToolboxHeight();
    int ScenarioWidth();
    int Zoom();
    std::string Serialize();
    void Deserialize(const std::string & Data);
};

#endif // SETTINGS_H
