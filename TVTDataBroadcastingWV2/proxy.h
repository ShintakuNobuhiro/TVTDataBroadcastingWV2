#pragma once
#include <winhttp.h>

class ProxySession
{
    HINTERNET session;
public:
    HINTERNET GetSession();
    ProxySession();
    ~ProxySession();
    ProxySession(const ProxySession&) = delete;
    ProxySession& operator=(const ProxySession&) = delete;
};

class ProxyRequest
{
    HINTERNET connect = nullptr;
    HINTERNET request = nullptr;
    // �X�g���[�~���O������͖̂ʓ|���K�v���Ȃ��̂ň�U�S�ēǂݍ���ł���Ԃ�
    std::vector<BYTE> data;
    std::function<void()> errorCallback;
    std::function<void(DWORD statusCode, LPCWSTR statusCodeText, LPCWSTR headers, size_t contentLength, BYTE* content)> callback;
    std::vector<BYTE> payload;
    ProxyRequest
    (
        HINTERNET connect,
        HINTERNET request,
        std::function<void()> errorCallback,
        std::function<void(DWORD statusCode, LPCWSTR statusCodeText, LPCWSTR headers, size_t contentLength, BYTE* content)> callback,
        std::vector<BYTE> payload
    );
    static void CALLBACK StaticAsyncCallback(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
    void Fail();
    void AsyncCallback(HINTERNET hInternet, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
    void Close();
public:
    // �񓯊�HTTP���N�G�X�g���s��
    // ��������ƕʃX���b�h��callback���Ă΂��
    static bool RequestAsync
    (
        ProxySession& session,
        LPCWSTR url,
        LPCWSTR verb,
        std::vector<BYTE> payload,
        std::vector<std::pair<LPCWSTR, LPCWSTR>>& headers,
        std::function<void()> errorCallback,
        std::function<void(DWORD statusCode, LPCWSTR statusCodeText, LPCWSTR headers, size_t contentLength, BYTE* content)> callback
    );
    ~ProxyRequest();
};
