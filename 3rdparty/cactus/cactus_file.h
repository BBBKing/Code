/*!
* \file cactus_file.h
* \brief �ļ�·�����ļ���д��ز�������
*
* �ļ�·�����ļ���д��ز�������
*
* \author wangyang
* \date 2015/01/30
* \version 1.0
*/
#ifndef __CACTUS_CACTUS_FILE_H__
#define __CACTUS_CACTUS_FILE_H__

#include <cactus/cactus.h>
#include <cactus/cactus_types.h>
#include <atlstr.h>
#include <atlcoll.h>
#include <atlfile.h>
#include <set>
//------------------------------------------------
// PathUtils.h

namespace cactus
{
const char16 PathDelim  = L'\\';
const char16 DirDelimiter = L'\\';
const char16 DriveDelim = L':';
const char16 PathSep    = L';';

/*! @brief ·��
 *
 * ��ϸ˵��
 */
class CACTUS_API Path
{
public:

    static BOOL IsDrive(char16* szDrive);

    static BOOL IsFileUsing(const string16& filename);

    static BOOL IsFreeSpaceAvailable(char16* szDrive);

    static long MyGetDiskFreeSpace(CString strPath);


    /*! @brief ��ȡ��ǰĿ¼
     *
     * @return ���ص�ǰĿ¼
     */
    static string16 GetCwd();

    /*! @brief ���õ�ǰĿ¼
     *
     * @param[in] dir Ŀ¼
     * @return ���ؿ�
     */
    static void SetCwd(const string16& dir);


    /*! @brief ��ȡ·���ָ���
     *
     * @return ����·���ָ���
     */
    static const char16* GetAllPathDelimiters();
    /*! @brief ��ȡ�ļ��������
     *
     * @param [in] filename �ļ���
     * @return �ļ��������
     */
    static string16 ClassifyFile(const string16& filename);

    /*! @brief �ж�·���Ƿ����·��ǰ׺
     *
     * @param [in] prefix ·��ǰ׺
     * @param [in] path ·��
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL PathIsPrefix(const string16& prefix, const string16& path);


    /*! @brief ·��ĩβ����\
     *
     * @param [in] path ����˵��
     * @return ������·��
     */
    static string16 PathAddBackslash(const string16& path);

    /*! @brief �ж��Ƿ���·���Ĺ���ǰ׺
     *
     * @param [in] srcpath ·��һ
     * @param [in] destpath ·����
     * @param [out] prefixpath ����·��ǰ׺
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL PathCommonPrefix(const string16& srcpath, const string16& destpath, string16& prefixpath);

    /*! @brief ��ʽ���ļ���С�ַ���
     *
     * @param [in] filelength �ļ���С
     * @param [out] deststr �����ַ���
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL StrFormatByteSize(LONGLONG filelength, string16& deststr);

    /*! @brief ��ȡ�ļ�����ļ�չʾ�����ļ�����
     *
     * @param [in] filename �ļ���
     * @param [in] type_name �ļ����
     * @param [in] displayname �ļ�չʾ��
     * @param [in] attributes �ļ�����
     * @return ���ؿ�
     */
    static void SHGetFileInfo2(const string16& filename, string16& type_name, string16& displayname, DWORD& attributes);


    /*! @brief �ַ���λ���Ƿ�Ϊ'\'
     *
     * @param [in] S �ַ���
     * @param [in] Index λ��
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool IsPathDelimiter(const string16& S, int Index);


    /*! @brief �Ƿ���·���ָ�����β
     *
     * @param [in] path ·��
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool EndsWithPathDelimiter(const string16& path);


    /*! @brief �Ƿ���·���ָ�����ͷ
     *
     * @param [in] path ·��
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool StartsWithPathDelimiter(const string16& path);


    /*! @brief �ַ���ĩβ���'\'
     *
     * @param [in] S �ַ���
     * @return �����ַ���
     */
    static string16 IncludeTrailingBackslash(const string16& S);

    /*! @brief �ַ���ĩβ���'\'
     *
     * @param [in] S �ַ���
     * @return �����ַ���
     */
    static string16 IncludeTrailingPathDelimiter(const string16& S);

    /*! @brief �ַ���ĩβȥ��'\'
     *
     * @param [in] S �ַ���
     * @return �����ַ���
     */
    static string16 ExcludeTrailingBackslash(const string16& S);

    /*! @brief �ַ���ĩβȥ��'\'
     *
     * @param [in] S �ַ���
     * @return �����ַ���
     */
    static string16 ExcludeTrailingPathDelimiter(const string16& S);

    static string16 PathRemoveBackslash(const string16& S);


    /*! @brief �ַ�����ͷȥ��'\'
     *
     * @param [in] S �ַ���
     * @return ���ط����ַ���
     */
    static string16 ExcludeLeadingPathDelimiter(const string16& S);


    /*! @brief �ϲ�·��
     *
     * @param [in] part1 ·��1
     * @param [in] part2 ·��2
     * @return ���غϲ����·��
     */
    static string16 CatPath(const string16& part1, const string16& part2);

    static string16 GetFullPathName(const string16& path);


    /*! @brief ��ȡ��ȫ·���ļ���
     *
     * @param [in] dir Ŀ¼
     * @param [in] filename �ļ���
     * @return ������ȫ·���ļ���
     */
    static string16 GetFullPathForDirectoryAndFilename(const string16& dir, const string16& filename);

    /*! @brief ����Ӧ�ó����Ŀ¼���ļ���
     *
     * @param [in] filename ����˵��
     * @return ����0��ʾ�ɹ�������Ϊ������
     */
    static string16 CompletePathWithModulePath(const string16& filename);

    /*! @brief ��ȡ�ļ�·��
     *
     * @param [in] FileName �ļ���
     * @return �����ļ�·��
     */
    static string16 ExtractFilePath(const string16& FileName);

    /*! @brief ��ȡ�ļ���
     *
     * @param [in] FileName �ļ���
     * @return �����ļ���
     */
    static string16 ExtractFileName(const string16& FileName);

    /*! @brief ��ȡ��չ��
     *
     * @param [in] FileName �ļ���
     * @return ������չ��
     */
    static string16 ExtractFileExt(const string16& FileName);



    /*! @brief ��ȡ��ȫ�ļ���
     *
     * @param [in] FileName �ļ���
     * @return ������ȫ�ļ���
     */
    static string16 ExpandFileName(const string16& FileName);

    /*! @brief �ı��ļ���չ��
     *
     * @param [in] FileName �ļ���
     * @param [in] Extension ��չ��
     * @return ���ظı����ļ���
     */
    static string16 ChangeFileExt(const string16& FileName, const string16& Extension);

    /*! @brief �ı��ļ�·��
     *
     * @param [in] FileName �ļ���
     * @param [in] Path �ļ���
     * @return ���ظı����ļ���
     */
    static string16 ChangeFilePath(const string16& FileName, const string16& Path);

    /*! @brief ��ȡ�ļ���·����
     *
     * @param [in] FileName �ļ���
     * @return ���ض�·����
     */
    static string16 ExtractShortPathName(const string16& FileName);


    /*! @brief ��ȡ��ǰ����Ŀ¼
     *
     * @return ���ص�ǰ����Ŀ¼
     */
    static string16 GetCurrentDirectory();


    /*! @brief ��ȡ��Ŀ¼
     *
     * @param[in] path �ļ�·��
     * @return ���ظ�Ŀ¼
     */
    static string16 GetParentDirectory(const string16& path);

    /*! @brief ����Ŀ¼
     *
     * @param [in] Dir Ŀ¼
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool CreateDir(const string16& Dir);


    static BOOL vmsBuildPathToFile(LPCTSTR ptszFileName);

    /*! @brief ��ȡ��ǰ����Ŀ¼
     *
     * @return ���ص�ǰ����Ŀ¼
     */
    static string16 GetCurrentWorkingDir();

    /*! @brief ��ȡ����ϵͳ���ڵ��̷�
     *
     * @return ���ز���ϵͳ���ڵ��̷�
     */
    static string16 GetSysDrv();

    static string16 GetSysDrv2();

    /*! @brief ��ȡ��ǰexe�ļ���
     *
     * @return ���ص�ǰexe�ļ���
     */
    static string16 GetAppFileName();

    static string16 GetAppDir();

    /*! @brief ��ȡ��ǰexe·��
     *
     * @return ���ص�ǰexe·��
     */
    static string16 GetAppPath();


    /*! @brief ��ȡ������·����exe�ļ���
     *
     * @return ���ز�����·����exe�ļ���
     */
    static string16 GetAppName();

    /*! @brief ��ȡ����·��
     *
     * @return ��������·��
     */
    static string16 GetDesktopDirectory();

    /*! @brief ��ȡProgram filesĿ¼
     *
     * @return ����Program filesĿ¼
     */
    static string16 GetProgramfilePath();

    /*! @brief ��ȡ�û�Ŀ¼
     *
     * @return �����û�Ŀ¼
     * C:\ProgramData
     */
    static string16 GetUserHomeDirectory();

    /*! @brief ��ȡ����AppDataĿ¼
     *
     * @return ���ع���AppDataĿ¼
     */
    static string16 GetCommonAppDataDirectory();

    /*! @brief ��ȡ�û�AppDataĿ¼
     *
     * @return �����û�AppDataĿ¼
     */
    static string16 GetUserDataDirectory();


    /*! @brief ��ȡ��ʱĿ¼
     *
     * @return ������ʱĿ¼
     */
    static string16 GetTempDir();

    /*! @brief ��ȡwindowsĿ¼
     *
     * @return ����windowsĿ¼
     */
    static string16 GetWindowsDir();

    /*! @brief ��ȡSystemĿ¼
     *
     * @return ����SystemĿ¼
     */
    static string16 GetSystemDir();

    /*! @brief �Ƿ�Ϊ����·��
     *
     * @param [in] path ·���ַ���
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool isAbsolutePath(const char16* path);


    /*! @brief ��ȡ�ļ������ļ���չ��
     *
     * @param [in] path �ļ�·��
     * @param [out] filename �ļ���
     * @param [out] ext ��չ��
     * @return ���ؿ�
     */
    static void dividePath(const string16& path, string16& filename, string16& ext);


    /*! @brief ��ȡ����·�����ļ���
     *
     * @param [in] filename �ļ���
     * @return ���ز���·�����ļ���
     */
    static string16 GetFilename(const string16& filename);


    /*! @brief ��ȡ��չ��
     *
     * @param [in] filename �ļ���
     * @return ������չ��
     */
    static string16 GetFileExtension(const string16& filename);


    /*! @brief �ָ�·���ַ���
     *
     * @param [in] filename �ļ�·��
     * @param [in] path ·��
     * @param [in] basename �ļ���
     * @param [in] extname ��չ��
     * @return ���ؿ�
     */
    static void SplitPathFileName(const string16& filename, string16& path, string16& basename, string16& extname);

    /*! @brief ��ȡ����·�����ļ�������չ��
     *
     * @param [in] path ·��
     * @param [in] basename �ļ���
     * @param [in] extname ��չ��
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL GetProcessPathNameAndFileName(string16& path, string16& basename, string16& extname);

    /*! @brief ���ù���·��Ϊ����·��
     *
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL AdjustProcessCurrentDirectory();

    /*! @brief �ļ��Ƿ����
     *
     * @param [in] filename �ļ���
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool FileExist(const string16& filename);


    static bool DirExists(const string16& dirname);

    /*! @brief Ŀ¼�Ƿ����
     *
     * @param [in] dirname Ŀ¼��
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool DirectoryExists(const string16& dirname);

    static bool CopyDir(const string16& source_dir, const string16& dest_dir, bool bOverwrite);

    static bool MoveDir(const string16& source_dir, const string16& dest_dir, int OverwriteMode);

    static BOOL MyMoveFile(const string16& source_file, const string16& dest_file);

    static bool RemoveDir(const string16& source_dir, bool bRecurse);

    static bool IsDifferentVolumes(const string16& path1, const string16& path2);

    /*! @brief ��ȡΨһ��ʱ�ļ���
     *
     * @return ����Ψһ��ʱ�ļ���
     */
    static string16 GetuniqueTempName();

    /*! @brief �ݹ鴴��Ŀ¼
     *
     * @param [in] dir Ŀ¼
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool CreateDirectoryNested(const string16& dir);

    static bool CreateDirEx(const char* lpDir);

    static bool CreateDirs(const char *lpFileName);

    static bool CreateDirs(const string16& filename);

    /*! @brief ��������Ŀ¼
     *
     * @param [in] dir Ŀ¼
     * @return ����true��ʾ�ɹ�������Ϊʧ��
     */
    static bool ForceCreateDirectory(string16 dir);


    static bool CreateDeepDirectory(const string16& dir);

    /*! @brief ɾ������Ŀ¼
     *
     * @param [in] dir Ŀ¼��
     * @param [in] bContinueWhenFail ʧ���Ƿ����
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL DeleteDirectory(const string16& dir, BOOL bContinueWhenFail = TRUE);


    static INT DeletePath(const string16& dir);


    static BOOL DeleteFolder(const string16& dir, BOOL bDeleteDriver);

    static BOOL DeleteAllFiles(const string16& dir, BOOL bDeleteFolderToo = FALSE);


    static string16 GetDriversDir();

    static BOOL GetSubDirs(const string16& dir_path, std::vector<string16>& dir_list, BOOL is_recursion = FALSE);






    /*! @brief ��ȡ�ı��ļ�����
     *
     * @param [in] filename �ļ���
     * @param [in] strA �ļ������ַ���
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL file_get_contents(const string16& filename, CStringA &strA);

    /*! @brief ��ȡ�ı��ļ�����
     *
     * @param [in] filename �ļ���
     * @param [in] strW �ļ������ַ���
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL file_get_contents(const string16& filename, CStringW &strW);


    /*! @brief д�ļ�
     *
     * @param [in] filename �ļ���
     * @param [in] pBuffer �ֽڻ�����
     * @param [in] nLen ����������
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL file_put_contents(const string16& filename, BYTE* pBuffer, INT nLen);

    /*! @brief д�ļ�
     *
     * @param [in] filename �ļ���
     * @param [in] lpszBuffer �ַ���������
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL file_put_contents(const string16& filename, LPCTSTR lpszBuffer);


    /*! @brief д�ļ�
     *
     * @param [in] filename �ļ���
     * @param [in] lpbData �ֽڻ�����
     * @param [in] dwFileSize ����������
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL SaveNewFile(const string16& filename, PBYTE lpbData, DWORD dwFileSize);


    /*! @brief ��ȡ�ļ���С
     *
     * @param [in] filename �ļ���
     * @return �����ļ���С
     */
    static INT64 file_get_size(const string16& filename);


    /*! @brief ��ȡ���ļ���С
     *
     * @param [in] filename �ļ���
     * @return �����ļ���С
     */
    static DWORD GetLargeFileSize(const string16& filename);


    /*! @brief ��ȡAppDataĿ¼
     *
     * @return ����AppDataĿ¼
     */
    static string16 GetApplicationDataPath();


    /*! @brief ��ӡĿ¼�µ������ļ�
     *
     * @param [in] folderpath Ŀ¼
     * @return ���ؿ�
     */
    static void FindAllFile(const string16& folderpath);


    /*! @brief �������ļ�
     *
     * @param[in] source Դ�ļ�
     * @param[in] target Ŀ���ļ�
     * @return ���ؿ�
     */
    static void RenameFile(const string16& source, const string16& target);

    static void CopyFile(const string16& source, const string16& target);

    static BOOL DeleteFile(const string16& filename);


    /*! @brief �ƶ��ļ���
     *
     * @param[in] source Դ�ļ���
     * @param[in] target Ŀ���ļ���
     * @param[in] bSilent �Ƿ�Ĭ
     * @return ���ؿ�
     */
    static void MoveDirectory(const string16& source, const string16& target, BOOL bSilent = TRUE);


    /*! @brief ͨ��shell���ļ��в�ѡ��
     *
     * @param[in] filename �ļ���
     * @return ���ؿ�
     */
    static void OpenFolder(const string16& filename);


    static void ShowItemInFolder(const string16& full_path);

    /*! @brief ��ȡ�ļ���С
     *
     * @param[in] filename �ļ���
     * @return �����ļ���С
     */
    static int64_t GetFileSize(const string16& filename);

    static LPSTREAM LoadResourceToStream(UINT uResId, LPCTSTR lpszResType);


    /*! @brief ����ͼ���Ƿ����
     *
     * @param [in] title ͼ������
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static BOOL IsExistDesktopIcon(const string16& title);

    static string16 GetSpecialFolderPath(int csidl);


    /*! @brief  Change a DOS path to a Unix path.
     *
     * Replaces '\' by '/', removes any trailing dots on directory/filenames,
     * and changes '*.*' to be equal to '*'
     *
     * @param[in] lpPath path to be modified
     * @return ����TRUE��ʾ�ɹ�������Ϊʧ��
     */
    static void FILEDosToUnixPathA(char* lpPath);

    static void FILEDosToUnixPathW(wchar_t* lpPath);

    static void FILEUnixToDosPathA(char* lpPath);

private:
    static BOOL _DeleteFolder(const string16& dir, BOOL bDeleteDriver);

};




namespace io
{

// Used to hold information about a given file path.  See GetFileInfo below.
struct FileInfo {
    // The size of the file in bytes.  Undefined when is_directory is true.
    int64_t size;

    // True if the file corresponds to a directory.
    bool is_directory;

    // Add additional fields here as needed.
};

FILE* OpenFile(const string16& filename, const char* mode);

FILE* OpenFile(const std::string& filename, const char* mode);

int ReadFile(const string16& filename, char* data, int size);

int WriteFile(const string16& filename, const char* data, int size);

bool ReadFileToString(const string16& path, std::string* contents);

bool GetFileSize(const string16& file_path, int64_t* file_size);

bool GetFileInfo(const string16& file_path, FileInfo* results);

bool CloseFile(FILE* file);
} // namespace io


bool CACTUS_API file_get_contents(const std::string& filename, std::vector<char>& buffer);
bool CACTUS_API file_get_contents(const string16& filename, std::vector<char>& buffer);
bool CACTUS_API file_get_contents(const string16& filename, std::vector<string16>& list);
bool CACTUS_API file_get_contents(const string16& filename, std::set<string16>& list);
std::string CACTUS_API file_get_contents(const string16& filename);
bool CACTUS_API file_put_contents(const string16& filename, const string16& data);
INT64 CACTUS_API filesize(const string16& filename);
BOOL CACTUS_API GetFileLargeSize(LPCWSTR lpFilePath, LARGE_INTEGER& liFileSize);
bool CACTUS_API move_file(const string16& from_filename, const string16& to_filename);
ULONG CACTUS_API FileExistCertificate(LPCWSTR lpFilePath);
BOOL CACTUS_API IsPeFile(LPCWSTR lpFilePath);
void CACTUS_API hexDump(FILE* dmpf, const char* name, BYTE* addr, size_t size);


HRESULT CACTUS_API KGetLoadModulePath(HMODULE hModule, string16& filename);
HRESULT CACTUS_API KGetCurrentLoadModulePath(string16& filename);
HRESULT CACTUS_API KGetLoadModuleDirPath(HMODULE hModule, string16& dir);
HRESULT CACTUS_API KGetCurrentLoadModuleDirPath(string16& dir);
HRESULT CACTUS_API KGetCurrentFilePathOnLoadModuleDirPath(const string16& filename, string16& strFilePath, BOOL* pbFileExist = NULL);
HRESULT CACTUS_API KGetCurrentFilePathOnImageDirPath(const string16& filename, string16& strFilePath, BOOL* pbFileExist = NULL);
HRESULT CACTUS_API KSmartGetCurrentFilePath(const string16& filename, string16& strFilePath, BOOL* pbFileExist = NULL);

} // namespace cactus


namespace cactus
{
void CACTUS_API WriteLine2File(string16& filename, LPCWSTR data);
void CACTUS_API WriteFormat2File(string16& filename, LPCWSTR Format, ...);
void CACTUS_API WriteFormat2FileV(string16& filename, LPCWSTR Format, va_list args);

typedef BOOL (*FN_PerString)(const string16& str);
void CACTUS_API EnumByLine(string16& filename, FN_PerString fnPerString);
std::string CACTUS_API SeekToPhrase(const std::string &strPhrase, std::istream &iStream);

int CACTUS_API CountFiles(const string16& dir, BOOL bSubfolders = TRUE);
INT64 CACTUS_API GetFolderSize(const string16& dir, BOOL bSubfolders = TRUE);
LPTSTR CACTUS_API FileAttribToStr(LPTSTR aBuf, DWORD aAttr);


// delphi��Ӧ����
const DWORD fmOpenRead       = 0x0000;
const DWORD fmOpenWrite      = 0x0001;
const DWORD fmOpenReadWrite  = 0x0002;
const DWORD fmShareCompat    = 0x0000; // DOS compatibility mode is not portable
const DWORD fmShareExclusive = 0x0010;
const DWORD fmShareDenyWrite = 0x0020;
const DWORD fmShareDenyRead  = 0x0030; // write-only not supported on all platforms
const DWORD fmShareDenyNone  = 0x0040;

HANDLE CACTUS_API FileOpen(const string16& FileName, DWORD Mode);

HANDLE CACTUS_API FileCreate(const string16& FileName);

DWORD CACTUS_API FileRead(HANDLE handle, BYTE* buffer, DWORD Count);

DWORD CACTUS_API FileWrite(HANDLE handle, const BYTE* buffer, DWORD Count);

DWORD CACTUS_API FileSeek(HANDLE handle, DWORD Offset, DWORD Origin);

INT64 CACTUS_API FileSeek(HANDLE handle, INT64 Offset, DWORD Origin);

void CACTUS_API FileClose(HANDLE handle);

BOOL CACTUS_API CreateDir(const string16& dir);

BOOL CACTUS_API RemoveDir(const string16& dir);

BOOL CACTUS_API ForceDirectories(string16 dir);
}


namespace cactus
{
class CNoCaseCompareTraits: public CElementTraitsBase<CString>
{
public:
    typedef const CString& INARGTYPE;
    typedef CString& OUTARGTYPE;

    static bool CompareElements(INARGTYPE element1, INARGTYPE element2)
    {
        return 0 == element1.CompareNoCase(element2);
    }

    static int CompareElementsOrdered(INARGTYPE element1, INARGTYPE element2)
    {
        return element1.CompareNoCase(element2);
    }
};




class KeyValue;
class Section;
class Document;



class KeyValue
{
public:
    KeyValue();
    KeyValue(Document* pDoc, POSITION posSection, POSITION posKeyValue);

    LPCWSTR     GetKey();
    LPCWSTR     GetValueString();
    DWORD       GetValueDWORD();
    ULONGLONG   GetValueULONGLONG();

    BOOL        IsNull();

    KeyValue    FindNextKeyValue();

protected:

    Document* m_pDoc;
    POSITION  m_posSection;
    POSITION  m_posKeyValue;
};



class Section
{
public:
    Section();
    Section(Document* pDoc, POSITION posSection);

    BOOL        HasKey(LPCWSTR lpszKey);
    size_t      GetKeyCount();

    KeyValue    operator[](LPCWSTR lpszKey);
    KeyValue    SetAt(LPCWSTR lpszKey, LPCWSTR lpszValue);

    BOOL        IsNull();
    Section     FindNextSection();

    LPCWSTR     GetName();

protected:

    Document* m_pDoc;
    POSITION  m_posSection;
};



class Document
{
public:
    Document();
    virtual ~Document();

    HRESULT     LoadFile(LPCWSTR lpszFilePath);
    HRESULT     LoadBuffer(const BYTE* pBuffer, DWORD dwBytes);

    BOOL        HasSection(LPCWSTR lpszKey);
    size_t      GetSectionCount();

    Section     operator[](LPCWSTR lpszKey);

    Section     FindFirstSection();

protected:
    Document(Document&);
    Document& operator=(Document&);

    friend class KeyValue;
    friend class Section;

    typedef CRBMap<CString, CString, CNoCaseCompareTraits>        SectionNode;
    typedef CRBMap<CString, SectionNode*, CNoCaseCompareTraits>   DocRoot;

    DocRoot m_docMap;
};


}

//------------------------------------------------
// �ڴ�ӳ���ļ�
namespace cactus
{
/*! @brief �ڴ�ӳ���ļ�
 *
 * ��ϸ˵��
 */
class CACTUS_API CMappedInFile
{
public:

    CMappedInFile(const string16& fileName);
    virtual ~CMappedInFile();

    const BYTE* GetBuffer() const;
    size_t GetSize() const;

private:
    void MapToMemory(const string16& fileName);
    void UnMap();

private:
    HANDLE          file;
    HANDLE          mapping;
    const BYTE*     buffer;
    size_t          size;

};

inline const BYTE* CMappedInFile::GetBuffer() const
{
    return buffer;
}

inline size_t CMappedInFile::GetSize() const
{
    return size;
}
}


namespace cactus
{
/// \brief ��ȡShell Folders
///
/// Example:
/// CAtlArray<CString> arrPath;
///
/// BkEnvDir::Get(CSIDL_APPDATA, arrPath);
/// ��ϸ��Ϣ
class CACTUS_API BkEnvDir
{
public:
    BkEnvDir();

    ~BkEnvDir();

    void Init();

    BOOL Get(DWORD dwCSIDL, CAtlArray<CString> &arrPathRet);

protected:

    struct __CsidlKey {
        __CsidlKey(LPCTSTR _lpszValueName = NULL, BOOL _bCommon = FALSE);
        LPCTSTR lpszValueName;
        BOOL    bCommon;
    };

    CAtlMap<DWORD, __CsidlKey> m_mapCsidl;

    void _FillCSidlMap();


    BOOL _GetPath(HKEY hRootKey, LPCWSTR lpszValueName, CString& strPathRet);
};
}


namespace cactus
{
class CACTUS_API CBkFileUtil
{
public:
    static BOOL CreateFullPath(LPCTSTR lpszFileName);

    static BOOL DenyExecute(LPCTSTR lpszFileName);

    static BOOL FixFilePrivilege(LPCTSTR lpszFileName);

    static HRESULT CreateFile(LPCTSTR lpszFileName, ATL::CAtlFile& theFile);

    static HRESULT FileExist(LPCTSTR lpszFileName);

private:

    static BOOL _IsVistaOrLater();
};
}

namespace cactus
{
/*! @brief �ڴ��ļ�ӳ��
 *
 * LPCTSTR szFilePath = TEXT("E:\xxx.zip");
 * SharedMemory sharedMemory(szFilePath, SharedMemory::AM_READ);
 * char* pFileBegin = sharedMemory.begin();
 */
class CACTUS_API SharedMemory
{
public:
    /// ����ģʽ
    enum AccessMode {
        AM_READ = 0,    ///< ��
        AM_WRITE        ///< д
    };

public:
    SharedMemory(const string16& name, std::size_t size, AccessMode mode, const void* addrHint = 0, bool server = true);
    SharedMemory(const string16& fileName, SharedMemory::AccessMode mode, const void* addrHint = 0);
    ~SharedMemory();

public:
    /// �����ڴ����ʼָ��
    char* begin() const;

    /// �����ڴ��β��ָ��
    char* end() const;

    /// �����ڴ������
    string16 name() const;

protected:
    void map();

    void unmap();

    void close();

private:
    SharedMemory();
    SharedMemory(const SharedMemory&);
    SharedMemory& operator = (const SharedMemory&);

    string16    m_name;
    HANDLE        m_memHandle;
    HANDLE        m_fileHandle;
    DWORD        m_size;
    DWORD        m_mode;
    char*        m_address;
};
}

namespace cactus
{

class CACTUS_API CAtlFile_CT : public ATL::CAtlFile
{
public:
    CAtlFile_CT() throw()
    {
    }

    CAtlFile_CT(__in cactus::CAtlFile_CT& file) throw()
        : ATL::CAtlFile(file)    // Transfers ownership
    {
    }

    explicit CAtlFile_CT(__in HANDLE hFile) throw()
        : ATL::CAtlFile(hFile)    // Takes ownership
    {
    }
    virtual ~CAtlFile_CT() {};
public:
    DWORD get_Pos();
    void set_Pos(DWORD dwPos, DWORD dwMethod);
    UINT64 get_Size();

    void WriteString(LPCSTR psz);
    void ReadString(string8& str);
    void WriteDouble(double f);
    void ReadDouble(double &f);
    void WriteInt64(__int64 i);
    void ReadInt64(__int64 &i);
    void WriteInt(int i);
    void ReadInt(int &i);
private:
    static BOOL _SaveStrToFile(LPCSTR pszStr, HANDLE hFile);
    static BOOL _ReadStrFromFile(LPSTR *ppszStr, HANDLE hFile);


};
}

#endif // __CACTUS_CACTUS_FILE_H__
