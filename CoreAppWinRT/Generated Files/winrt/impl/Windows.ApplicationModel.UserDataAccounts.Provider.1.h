// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_ApplicationModel_UserDataAccounts_Provider_1_H
#define WINRT_Windows_ApplicationModel_UserDataAccounts_Provider_1_H
#include "winrt/impl/Windows.ApplicationModel.UserDataAccounts.Provider.0.h"
WINRT_EXPORT namespace winrt::Windows::ApplicationModel::UserDataAccounts::Provider
{
    struct __declspec(empty_bases) IUserDataAccountPartnerAccountInfo :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAccountPartnerAccountInfo>
    {
        IUserDataAccountPartnerAccountInfo(std::nullptr_t = nullptr) noexcept {}
        IUserDataAccountPartnerAccountInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAccountPartnerAccountInfo(IUserDataAccountPartnerAccountInfo const&) noexcept = default;
        IUserDataAccountPartnerAccountInfo(IUserDataAccountPartnerAccountInfo&&) noexcept = default;
        IUserDataAccountPartnerAccountInfo& operator=(IUserDataAccountPartnerAccountInfo const&) & noexcept = default;
        IUserDataAccountPartnerAccountInfo& operator=(IUserDataAccountPartnerAccountInfo&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataAccountProviderAddAccountOperation :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAccountProviderAddAccountOperation>,
        impl::require<winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderAddAccountOperation, winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderOperation>
    {
        IUserDataAccountProviderAddAccountOperation(std::nullptr_t = nullptr) noexcept {}
        IUserDataAccountProviderAddAccountOperation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAccountProviderAddAccountOperation(IUserDataAccountProviderAddAccountOperation const&) noexcept = default;
        IUserDataAccountProviderAddAccountOperation(IUserDataAccountProviderAddAccountOperation&&) noexcept = default;
        IUserDataAccountProviderAddAccountOperation& operator=(IUserDataAccountProviderAddAccountOperation const&) & noexcept = default;
        IUserDataAccountProviderAddAccountOperation& operator=(IUserDataAccountProviderAddAccountOperation&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataAccountProviderOperation :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAccountProviderOperation>
    {
        IUserDataAccountProviderOperation(std::nullptr_t = nullptr) noexcept {}
        IUserDataAccountProviderOperation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAccountProviderOperation(IUserDataAccountProviderOperation const&) noexcept = default;
        IUserDataAccountProviderOperation(IUserDataAccountProviderOperation&&) noexcept = default;
        IUserDataAccountProviderOperation& operator=(IUserDataAccountProviderOperation const&) & noexcept = default;
        IUserDataAccountProviderOperation& operator=(IUserDataAccountProviderOperation&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataAccountProviderResolveErrorsOperation :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAccountProviderResolveErrorsOperation>,
        impl::require<winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderResolveErrorsOperation, winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderOperation>
    {
        IUserDataAccountProviderResolveErrorsOperation(std::nullptr_t = nullptr) noexcept {}
        IUserDataAccountProviderResolveErrorsOperation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAccountProviderResolveErrorsOperation(IUserDataAccountProviderResolveErrorsOperation const&) noexcept = default;
        IUserDataAccountProviderResolveErrorsOperation(IUserDataAccountProviderResolveErrorsOperation&&) noexcept = default;
        IUserDataAccountProviderResolveErrorsOperation& operator=(IUserDataAccountProviderResolveErrorsOperation const&) & noexcept = default;
        IUserDataAccountProviderResolveErrorsOperation& operator=(IUserDataAccountProviderResolveErrorsOperation&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IUserDataAccountProviderSettingsOperation :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IUserDataAccountProviderSettingsOperation>,
        impl::require<winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderSettingsOperation, winrt::Windows::ApplicationModel::UserDataAccounts::Provider::IUserDataAccountProviderOperation>
    {
        IUserDataAccountProviderSettingsOperation(std::nullptr_t = nullptr) noexcept {}
        IUserDataAccountProviderSettingsOperation(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IUserDataAccountProviderSettingsOperation(IUserDataAccountProviderSettingsOperation const&) noexcept = default;
        IUserDataAccountProviderSettingsOperation(IUserDataAccountProviderSettingsOperation&&) noexcept = default;
        IUserDataAccountProviderSettingsOperation& operator=(IUserDataAccountProviderSettingsOperation const&) & noexcept = default;
        IUserDataAccountProviderSettingsOperation& operator=(IUserDataAccountProviderSettingsOperation&&) & noexcept = default;
    };
}
#endif
