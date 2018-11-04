#pragma once

#ifdef FILEWATCHER_EXPORTS
#define FILEWATCHER_API __declspec(dllexport)
#else
#define FILEWATCHER_API __declspec(dllimport)
#pragma comment(lib,"FileWatcher.lib")
#endif

#include <string>
#include <vector>

namespace FileWatcher
{
class FileWatcherAdapter;

/// <summary>
/// ファイル監視クラス
/// </summary>
class FILEWATCHER_API FileWatcher {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="hWnd">通知するウィンドウ</param>
    FileWatcher(HWND hWnd);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~FileWatcher();
    /// <summary>
    /// 監視開始
    /// </summary>
    /// <param name="dirPath">監視するディレクトリ</param>
    /// <param name="fileNames">監視するファイル名</param>
    void StartWatching(const std::string& dirPath, const std::vector<std::string>& fileNames);
    /// <summary>
    /// 監視終了
    /// </summary>
    void StopWatching();
private:
    FileWatcherAdapter * adapter_;
};

//
// ファイルに変更があった場合のウィンドウ識別子
// wParam(const char*):変更があったファイルのフルパス．コピーして使うこと．
// lParam(int):変更タイプ
//   1:Created
//   2:Deleted
//   4:Changed
const int  WM_CHANGED = WM_APP + 1;

}
