#ifndef SETTINGS_H
#define SETTINGS_H


class settings
{
    bool use_flash;
    int skip_frames;
    bool force_utf8;
    int toolbox_height;
    int scenario_width;
public:
    settings();
    bool UseFlash();
    bool ForceUtf8();
    int SkipFrames();
    int ToolboxHeight();
    int ScenarioWidth();
};

#endif // SETTINGS_H
