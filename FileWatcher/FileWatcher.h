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
/// �t�@�C���Ď��N���X
/// </summary>
class FILEWATCHER_API FileWatcher {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="hWnd">�ʒm����E�B���h�E</param>
    FileWatcher(HWND hWnd);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FileWatcher();
    /// <summary>
    /// �Ď��J�n
    /// </summary>
    /// <param name="dirPath">�Ď�����f�B���N�g��</param>
    /// <param name="fileNames">�Ď�����t�@�C����</param>
    void StartWatching(const std::string& dirPath, const std::vector<std::string>& fileNames);
    /// <summary>
    /// �Ď��I��
    /// </summary>
    void StopWatching();
private:
    FileWatcherAdapter * adapter_;
};

//
// �t�@�C���ɕύX���������ꍇ�̃E�B���h�E���ʎq
// wParam(const char*):�ύX���������t�@�C���̃t���p�X�D�R�s�[���Ďg�����ƁD
// lParam(int):�ύX�^�C�v
//   1:Created
//   2:Deleted
//   4:Changed
const int  WM_CHANGED = WM_APP + 1;

}
