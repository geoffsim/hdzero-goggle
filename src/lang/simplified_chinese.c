/*
Author: ligen
Email: ligen@divimath.com

Note:
- Do not use Chinese punctuation.
- Do not use Chinese comments.
- After changing translate_simplified_chinese,
    run utilities/generate_font_lib.py to generate a new font libraries,
    then move the font libraries to lib/lvgl/lvgl/src/font/.
*/

#include "simplified_chinese.h"

translate_t translate_simplified_chinese[TRANSLATE_STRING_NUM] = {
    // status bar
    {"SD Card", "SD卡"},
    {"Off", "关闭"},
    {"On", "打开"},
    {"In", "输入"},
    {"Expansion Module", "扩展模块"},
    {"Integrity check", "完整性检查"},
    {"Unsupported", "不支持"},
    {"No SD Card", "无SD卡"},
    {"Searching", "WiFi: 搜索中"},
    {"RF", "信道"},
    {"clip(s)", "个文件"},
    {"full", "满"},
    {"available", "可用"},

    // scan now
    {"Scan Now", "扫频"},
    {"Scan Ready", "扫频就绪"},
    {"When scanning is complete, use the\n dial to select a channel and press\n the Enter button to choose", "扫频完成后, 使用滚轮选择信道并按下确认键进入"},
    {"Scanning", "扫频中"},
    {"Scanning done", "扫频完成"},
    {"Scanning ready", "扫频就绪"},

    // source
    {"Source", "信号源"},
    {"Expansion Module", "扩展模块"},
    {"Analog Video", "模拟制式"},
    {"HDZero Band", "HDZero频段"},
    {"Raceband", "竞速频段"},
    {"Lowband", "低频段"},
    {"HDZero BW", "HDZero带宽"},
    {"Wide", "宽带"},
    {"Narrow", "窄带"},
    {"Back", "返回"},
    {"#00FF00 Detected#", "#00FF00 已连接#"},
    {"#C0C0C0 Disconnected", "#C0C0C0 未连接"},

    // image setting
    {"Image Setting", "图像设置"},
    {"Brightness", "亮度"},
    {"Saturation", "饱和度"},
    {"Contrast", "对比度"},
    {"Auto Off", "自动关闭"},
    {"To change image settings, click the Enter button to enter video mode. \nMake sure a HDZero VTX or analog VTX is powered on for live video.", "点击进入确认键进入视频模式以修改图像参数. \n确保HDZero VTX或模拟VTX已经运行"},
    {"Never", "从不"},
    {"min", "分钟"},

    // osd
    {"OSD", "OSD"},
    {"Adjust OSD Elements", "调整OSD元素"},
    {"Orbit", "轨迹"},
    {"Mode", "模式"},
    {"Min", "最小"},
    {"Max", "最大"},
    {"At Startup", "启动时"},
    {"Show", "显示"},
    {"Hide", "隐藏"},
    {"Last", "上一次"},
    {"Note: The positioning preview will display all OSD elements. Some elements might\nnot show during normal operation, depending on input source and conditions.\nOSD Element positioning is based on a 1280x720 canvas.\nPositions can be set for 4x3 and 16x9 modes separately,\nthe Show Element toggle is shared between both modes.", "注意: 位置预览会显示所有OSD.\n某些元素在正常运行可能不会显示,这取决于信号源和其它条件.\nOSD元素基于1280x720画布进行定位.\n可以分别在4x3和16x9模式下设置位置.\n元素的显示与隐藏在两种模式下一样."},

    // power
    {"Power", "电源"},
    {"Battery", "电池"},
    {"Cell Mode", "电芯计数模式"},
    {"Manual", "手动"},
    {"Cell Count", "电芯数"},
    {"Warning Cell Voltage", "单芯警告电压"},
    {"Voltage Calibration", "电压校准"},
    {"Display Mode", "显示模式"},
    {"Total", "总电压"},
    {"Cell Avg.", "单芯电压"},
    {"Warning Type", "警报方式"},
    {"Beep", "蜂鸣器"},
    {"Visual", "屏显"},
    {"Both", "同时"},
    {"AnalogRx", "外挂模块"},
    {"Auto", "自动"},

    // fans
    {"Fans", "风扇"},
    {"Auto Control", "自动控制"},
    {"Top Fan", "顶风扇"},
    {"Side Fans", "侧风扇"},

    // record
    {"Record Option", "录像设置"},
    {"Record Mode", "录像模式"},
    {"Record Format", "录像格式"},
    {"Record OSD", "录制OSD"},
    {"Record Audio", "录制音频"},
    {"Audio Source", "音频源"},
    {"Naming Scheme", "命名规则"},
    {"Yes", "是"},
    {"No", "否"},
    {"Mic", "麦克风"},
    {"Line In", "耳机输入"},
    {"A/V In", "模拟输入"},
    {"Digits", "计数"},
    {"Date", "日期"},
    {"MP4 format requires properly closing files or the files will be corrupt. \nTS format is highly recommended.", "MP4格式在录制过程中掉电会导致文件损坏.\n强烈建议使用TS格式."},

    // auto scan
    {"Auto Scan", "自动扫频"},
    {"Default", "默认"},
    {"Expansion", "扩展模块"},
    {"AV In", "AV 输入"},
    {"HDMI In", "HDMI 输入"},
    {"*if Auto Scan is 'Last', goggles will default to show last tuned channel", "*如果自动扫频设置为'上一次',眼镜将默认显示上一次的信道"},

    // elrs
    {"ELRS", "ELRS"},
    {"Send", "发送"},
    {"Bind", "绑定"},
    {"Click to start", "点击开始"},
    {"* Press right button to cancel binding", "* 按下右键取消绑定"},
    {"Starting...", "开始..."},
    {"FAILED", "失败"},
    {"Success", "成功"},
    {"Binding...", "绑定中"},
    {"Timeout", "超时"},
    {"Cancelled", "已取消"},
    {"Backpack", "背包"},

    // wifi module
    {"WiFi Module", "WiFi模块"},
    {"#FF0000 Invalid Too Short#", "#FF0000 长度太短无效#"},
    {"#FF0000 Invalid Format#", "#FF0000 格式无效#"},
    {"Password Requirements", "密码要求"},
    {"Minimum 8 characters", "最少8个字符"},
    {"maximum 64 characters", "最多64个字符"},
    {"Live stream:", "直播:"},
    {"Connect to the WiFi network identified above", "连接上面标识的WiFi网络"},
    {"Use VLC Player to open a Network Stream", "使用VLC播放去打开网络流媒体"},
    {"Apply Settings", "生效设置"},
    {"Enable", "开关"},
    {"Host", "主机"},
    {"Client", "客户端"},
    {"Password", "密码"},
    {"Address", "地址"},
    {"Netmask", "网络掩码"},
    {"Gateway", "网关"},
    {"RF Channel", "无线信道"},
    {"Root PW", "Root 密码"},
    {"Page", "页面"},
    {"Basic", "基本"},
    {"Advanced", "专业"},
    {"System", "系统"},
    {"Updating WiFi", "更新WiFi中"},
    {"Click to confirm or Scroll to cancel", "点击确认或通过滚轮取消"},

    // head tracker
    {"Head Tracker", "头部追踪"},
    {"Set Alarm Angle", "设置报警角度"},
    {"Tracking", "追踪"},
    {"Tilt Alarm", "倾斜报警"},
    {"Alarm", "报警"},
    {"Video", "图像"},
    {"Arm", "锁定"},
    {"Calibrate", "校准"},
    {"Set Center", "设置中心位置"},
    {"Max Angle", "最大角度"},
    {"Pan", "横摇"},
    {"Tilt", "俯仰"},
    {"Roll", "滚动"},
    {"Calibrating", "校准中"},
    {"Re-calibrate", "重新校准"},
    {"Updating Angle", "角度更新中"},

    // playback
    {"Playback", "录像回放"},
    {"Long press the Enter button to exit", "长按确认按键退出"},
    {"Long press the Func button to delete", "长按功能按键删除视频"},

    // storage
    {"Storage", "存储"},
    {"Format SD Card", "格式化SD卡"},
    {"Repair SD Card", "修复SD卡"},
    {"Clear DVR Folder", "清空录像文件夹"},
    {"Format was successful", "格式化成功"},
    {"Format has failed", "格式化失败"},
    {"Press click to exit", "按下确认键退出"},
    {"Please insert a SD Card", "请插入SD卡"},
    {"Failed to extract results", "获取结果失败"},
    {"Failed to access results", "访问结果失败"},
    {"Failed to generate results", "生成结果失败"},
    {"Failed to start format", "格式化开始失败"},
    {"Unsupported status code", "不支持的状态代码"},
    {"SD Card Format Status", "SD卡格式化状态"},
    {"Filesystem is OK", "文件系统正确"},
    {"Filesystem was modified and fixed", "文件系统已修复"},
    {"Failed to remount SD Card", "重新挂载SD卡失败"},
    {"Failed to start repair", "修复开始失败"},
    {"SD Card Repair Status", "SD卡修复状态"},
    {"Logging", "日志"},
    {"Self-Test is enabled", "自检功能已启用"},
    {"All storage options are disabled", "所有存储选项都无法使用"},
    {"Detected files being accessed by SD Card", "检测到SD卡正在访问文件"},
    {"Remove the following files from the SD Card and try again", "从SD卡删除以下文件并重试"},
    {"Status", "状态"},
    {"None", "无"},
    {"Formating", "格式化中"},
    {"Repairing", "修复中"},
    {"Removing", "清理中"},
    {"Done", "完成"},
    {"SD Card integrity check is active", "SD卡完成性检查处于活动状态"},
    {"controls are disabled until process has completed", "此界面暂时被禁用"},

    // firmware
    {"Firmware   ", "固件"},
    {"Flashing", "更新中"},
    {"SUCCESS", "成功"},
    {"Verification failed, try it again", "验证失败, 再次尝试"},
    {"No firmware found", "无可用固件"},
    {"Failed, check connection", "失败, 检查连接..."},
    {"WAIT", "更新中"},
    {"DO NOT POWER OFF", "请不要关机"},
    {"Multiple versions been found", "发现多个版本"},
    {"Keep only one", "请仅保留一个"},
    {"To view release notes", "要查看发布信息"},
    {"select either Update VTX or Update Goggle", "请选择更新VTX或者更新Goggle"},
    {"then press the Func button to display or hide the release notes", "然后按下功能键显示或者隐藏发布信息"},
    {"Remove HDZERO_TX or HDZERO_GOGGLE binary files from the root of\nSD Card in order to install the latest online downloaded firmware files", "从 SD 卡根目录中删除 HDZERO_TX 或 HDZERO_GOGGLE 二进制文件, 以安装最新的在线下载的固件"},
    {"Visit https://github.com/hdzero for the complete list of changes", "请访问 https://github.com/hdzero 获取完整的更改列表"},
    {"Release Notes", "发布信息"},
    {"not found", "没有找到"},
    {"Update", "更新"},
    {"Target", "目标"},
    {"Firmware", "固件"},
    {"Current Version", "当前版本"},
    {"Reset all settings", "复位所有设置"},
    {"Update complete", "更新完成"},
    {"Goggle update completed successfully.\nPlease repower goggle now.", "Goggle更新完成.\n现在请重启goggle."},
    {"Settings reset", "重置设置"},
    {"All settings have been reset.\nPlease repower goggle now.", "所有设置已被重置.\n现在请重启goggle."},
    {"Empty", "无"},

    // focus chart
    {"Focus Chart", "对焦图"},
    {"Click the Enter Button to display the Back Focusing Chart", "点击确认按键显示对焦图"},
    {"Click the Enter Button again to exit", "再次点击确认按键退出"},

    // clock
    {"Clock", "时间"},
    {"Set Clock", "设置时间"},
    {"Format", "格式"},
    {"AM", "上午"},
    {"PM", "下午"},
    {"24 Hour", "24小时"},
    {"Battery not installed or clock not configured", "没有安装电池或者没有设置时间"},

    // input
    {"Input", "按键"},
    {"Roller", "滚轮"},
    {"Left short", "左短按"},
    {"Left long", "右短按"},
    {"Right short", "左长按"},
    {"Right long", "右长按"},
    {"Right double", "右双击"},
    {"Toggle OSD", "开关OSD"},
    {"Main menu", "主菜单"},
    {"Toggle DVR", "开关录像"},
    {"Center HT", "头追回中"},
    {"Calibrate HT", "校准头追"},
    {"Toggle fan speed", "调整风扇速度"},
    {"Star DVR", "标记录像"},
    {"Toggle source", "切换信号源"},
    {"Cycle source", "循环信号源"},
    {"Switch channel", "切换信道"},
    {"Change fan speed", "调整风扇速度"},
    {"OLED Brightness", "调整OLED背光"},
    {"Settings apply to video mode only", "设置仅在视频模式下生效"},
    {"'Toggle source' will switch between HDZero and Expansion module", "'切换信号源'将在扩展模块和HDZero之间切换"},

    // go sleep
    {"Go Sleep", "休眠"},
    {"Go Sleep!", "休眠!"},
    {"Click the Enter Button to go sleep", "点击确认进入休眠"},
    {"Click any button to exit sleep mode", "点击任意按键退出休眠"},

    // ui osd element pos
    {"Top Fan Speed", "顶风扇速度"},
    {"Latency Lock", "延时锁定"},
    {"VTX Temp", "VTX 温度"},
    {"VRX, Temp", "眼镜温度"},
    {"Battery Low", "电池电压低"},
    {"Battery Voltage", "电池电压"},
    {"Clock Date", "日期"},
    {"Clock Time", "时间"},
    {"Channel", "信道"},
    {"DVR", "录像"},
    {"VLQ", "视频信号质量"},
    {"Antenna 1", "天线1"},
    {"Antenna 2", "天线2"},
    {"Antenna 3", "天线3"},
    {"Antenna 4", "天线4"},
    {"Goggle Temp Top", "眼镜顶部温度"},
    {"Goggle Temp Left", "眼镜左侧温度"},
    {"Goggle Temp Right", "眼镜右侧温度"},
    {"Reset all elements (both modes)", "复位所有元素"},
    {"Save changes", "保存修改"},
    {"Cancel", "取消"},
    {"click to confirm", "点击确认"},
    {"scroll to cancel", "转动滚轮取消"},
    {"Elements reset", "复位元素"},
    {"Pos-X", "X轴坐标"},
    {"Pos-Y", "Y轴坐标"},
};