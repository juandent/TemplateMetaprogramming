// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Security_Authentication_Web_Core_1_H
#define WINRT_Windows_Security_Authentication_Web_Core_1_H
#include "winrt/impl/Windows.Security.Authentication.Web.Core.0.h"
WINRT_EXPORT namespace winrt::Windows::Security::Authentication::Web::Core
{
    struct __declspec(empty_bases) IFindAllAccountsResult :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IFindAllAccountsResult>
    {
        IFindAllAccountsResult(std::nullptr_t = nullptr) noexcept {}
        IFindAllAccountsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IFindAllAccountsResult(IFindAllAccountsResult const&) noexcept = default;
        IFindAllAccountsResult(IFindAllAccountsResult&&) noexcept = default;
        IFindAllAccountsResult& operator=(IFindAllAccountsResult const&) & noexcept = default;
        IFindAllAccountsResult& operator=(IFindAllAccountsResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAccountEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAccountEventArgs>
    {
        IWebAccountEventArgs(std::nullptr_t = nullptr) noexcept {}
        IWebAccountEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAccountEventArgs(IWebAccountEventArgs const&) noexcept = default;
        IWebAccountEventArgs(IWebAccountEventArgs&&) noexcept = default;
        IWebAccountEventArgs& operator=(IWebAccountEventArgs const&) & noexcept = default;
        IWebAccountEventArgs& operator=(IWebAccountEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAccountMonitor :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAccountMonitor>
    {
        IWebAccountMonitor(std::nullptr_t = nullptr) noexcept {}
        IWebAccountMonitor(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAccountMonitor(IWebAccountMonitor const&) noexcept = default;
        IWebAccountMonitor(IWebAccountMonitor&&) noexcept = default;
        IWebAccountMonitor& operator=(IWebAccountMonitor const&) & noexcept = default;
        IWebAccountMonitor& operator=(IWebAccountMonitor&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAccountMonitor2 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAccountMonitor2>
    {
        IWebAccountMonitor2(std::nullptr_t = nullptr) noexcept {}
        IWebAccountMonitor2(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAccountMonitor2(IWebAccountMonitor2 const&) noexcept = default;
        IWebAccountMonitor2(IWebAccountMonitor2&&) noexcept = default;
        IWebAccountMonitor2& operator=(IWebAccountMonitor2 const&) & noexcept = default;
        IWebAccountMonitor2& operator=(IWebAccountMonitor2&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAuthenticationCoreManagerStatics :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAuthenticationCoreManagerStatics>
    {
        IWebAuthenticationCoreManagerStatics(std::nullptr_t = nullptr) noexcept {}
        IWebAuthenticationCoreManagerStatics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAuthenticationCoreManagerStatics(IWebAuthenticationCoreManagerStatics const&) noexcept = default;
        IWebAuthenticationCoreManagerStatics(IWebAuthenticationCoreManagerStatics&&) noexcept = default;
        IWebAuthenticationCoreManagerStatics& operator=(IWebAuthenticationCoreManagerStatics const&) & noexcept = default;
        IWebAuthenticationCoreManagerStatics& operator=(IWebAuthenticationCoreManagerStatics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAuthenticationCoreManagerStatics2 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAuthenticationCoreManagerStatics2>,
        impl::require<winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics2, winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics>
    {
        IWebAuthenticationCoreManagerStatics2(std::nullptr_t = nullptr) noexcept {}
        IWebAuthenticationCoreManagerStatics2(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAuthenticationCoreManagerStatics2(IWebAuthenticationCoreManagerStatics2 const&) noexcept = default;
        IWebAuthenticationCoreManagerStatics2(IWebAuthenticationCoreManagerStatics2&&) noexcept = default;
        IWebAuthenticationCoreManagerStatics2& operator=(IWebAuthenticationCoreManagerStatics2 const&) & noexcept = default;
        IWebAuthenticationCoreManagerStatics2& operator=(IWebAuthenticationCoreManagerStatics2&&) & noexcept = default;
        using impl::consume_t<IWebAuthenticationCoreManagerStatics2, IWebAuthenticationCoreManagerStatics2>::FindAccountProviderAsync;
        using impl::consume_t<IWebAuthenticationCoreManagerStatics2, winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics>::FindAccountProviderAsync;
    };
    struct __declspec(empty_bases) IWebAuthenticationCoreManagerStatics3 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAuthenticationCoreManagerStatics3>,
        impl::require<winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics3, winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics>
    {
        IWebAuthenticationCoreManagerStatics3(std::nullptr_t = nullptr) noexcept {}
        IWebAuthenticationCoreManagerStatics3(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAuthenticationCoreManagerStatics3(IWebAuthenticationCoreManagerStatics3 const&) noexcept = default;
        IWebAuthenticationCoreManagerStatics3(IWebAuthenticationCoreManagerStatics3&&) noexcept = default;
        IWebAuthenticationCoreManagerStatics3& operator=(IWebAuthenticationCoreManagerStatics3 const&) & noexcept = default;
        IWebAuthenticationCoreManagerStatics3& operator=(IWebAuthenticationCoreManagerStatics3&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebAuthenticationCoreManagerStatics4 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebAuthenticationCoreManagerStatics4>,
        impl::require<winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics4, winrt::Windows::Security::Authentication::Web::Core::IWebAuthenticationCoreManagerStatics>
    {
        IWebAuthenticationCoreManagerStatics4(std::nullptr_t = nullptr) noexcept {}
        IWebAuthenticationCoreManagerStatics4(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebAuthenticationCoreManagerStatics4(IWebAuthenticationCoreManagerStatics4 const&) noexcept = default;
        IWebAuthenticationCoreManagerStatics4(IWebAuthenticationCoreManagerStatics4&&) noexcept = default;
        IWebAuthenticationCoreManagerStatics4& operator=(IWebAuthenticationCoreManagerStatics4 const&) & noexcept = default;
        IWebAuthenticationCoreManagerStatics4& operator=(IWebAuthenticationCoreManagerStatics4&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebProviderError :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebProviderError>
    {
        IWebProviderError(std::nullptr_t = nullptr) noexcept {}
        IWebProviderError(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebProviderError(IWebProviderError const&) noexcept = default;
        IWebProviderError(IWebProviderError&&) noexcept = default;
        IWebProviderError& operator=(IWebProviderError const&) & noexcept = default;
        IWebProviderError& operator=(IWebProviderError&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebProviderErrorFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebProviderErrorFactory>
    {
        IWebProviderErrorFactory(std::nullptr_t = nullptr) noexcept {}
        IWebProviderErrorFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebProviderErrorFactory(IWebProviderErrorFactory const&) noexcept = default;
        IWebProviderErrorFactory(IWebProviderErrorFactory&&) noexcept = default;
        IWebProviderErrorFactory& operator=(IWebProviderErrorFactory const&) & noexcept = default;
        IWebProviderErrorFactory& operator=(IWebProviderErrorFactory&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenRequest :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenRequest>
    {
        IWebTokenRequest(std::nullptr_t = nullptr) noexcept {}
        IWebTokenRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenRequest(IWebTokenRequest const&) noexcept = default;
        IWebTokenRequest(IWebTokenRequest&&) noexcept = default;
        IWebTokenRequest& operator=(IWebTokenRequest const&) & noexcept = default;
        IWebTokenRequest& operator=(IWebTokenRequest&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenRequest2 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenRequest2>
    {
        IWebTokenRequest2(std::nullptr_t = nullptr) noexcept {}
        IWebTokenRequest2(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenRequest2(IWebTokenRequest2 const&) noexcept = default;
        IWebTokenRequest2(IWebTokenRequest2&&) noexcept = default;
        IWebTokenRequest2& operator=(IWebTokenRequest2 const&) & noexcept = default;
        IWebTokenRequest2& operator=(IWebTokenRequest2&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenRequest3 :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenRequest3>
    {
        IWebTokenRequest3(std::nullptr_t = nullptr) noexcept {}
        IWebTokenRequest3(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenRequest3(IWebTokenRequest3 const&) noexcept = default;
        IWebTokenRequest3(IWebTokenRequest3&&) noexcept = default;
        IWebTokenRequest3& operator=(IWebTokenRequest3 const&) & noexcept = default;
        IWebTokenRequest3& operator=(IWebTokenRequest3&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenRequestFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenRequestFactory>
    {
        IWebTokenRequestFactory(std::nullptr_t = nullptr) noexcept {}
        IWebTokenRequestFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenRequestFactory(IWebTokenRequestFactory const&) noexcept = default;
        IWebTokenRequestFactory(IWebTokenRequestFactory&&) noexcept = default;
        IWebTokenRequestFactory& operator=(IWebTokenRequestFactory const&) & noexcept = default;
        IWebTokenRequestFactory& operator=(IWebTokenRequestFactory&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenRequestResult :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenRequestResult>
    {
        IWebTokenRequestResult(std::nullptr_t = nullptr) noexcept {}
        IWebTokenRequestResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenRequestResult(IWebTokenRequestResult const&) noexcept = default;
        IWebTokenRequestResult(IWebTokenRequestResult&&) noexcept = default;
        IWebTokenRequestResult& operator=(IWebTokenRequestResult const&) & noexcept = default;
        IWebTokenRequestResult& operator=(IWebTokenRequestResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenResponse :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenResponse>
    {
        IWebTokenResponse(std::nullptr_t = nullptr) noexcept {}
        IWebTokenResponse(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenResponse(IWebTokenResponse const&) noexcept = default;
        IWebTokenResponse(IWebTokenResponse&&) noexcept = default;
        IWebTokenResponse& operator=(IWebTokenResponse const&) & noexcept = default;
        IWebTokenResponse& operator=(IWebTokenResponse&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IWebTokenResponseFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IWebTokenResponseFactory>
    {
        IWebTokenResponseFactory(std::nullptr_t = nullptr) noexcept {}
        IWebTokenResponseFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IWebTokenResponseFactory(IWebTokenResponseFactory const&) noexcept = default;
        IWebTokenResponseFactory(IWebTokenResponseFactory&&) noexcept = default;
        IWebTokenResponseFactory& operator=(IWebTokenResponseFactory const&) & noexcept = default;
        IWebTokenResponseFactory& operator=(IWebTokenResponseFactory&&) & noexcept = default;
    };
}
#endif
