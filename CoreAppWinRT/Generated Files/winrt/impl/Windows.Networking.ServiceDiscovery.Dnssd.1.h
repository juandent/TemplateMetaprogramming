// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Networking_ServiceDiscovery_Dnssd_1_H
#define WINRT_Windows_Networking_ServiceDiscovery_Dnssd_1_H
#include "winrt/impl/Windows.Networking.ServiceDiscovery.Dnssd.0.h"
WINRT_EXPORT namespace winrt::Windows::Networking::ServiceDiscovery::Dnssd
{
    struct __declspec(empty_bases) IDnssdRegistrationResult :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IDnssdRegistrationResult>
    {
        IDnssdRegistrationResult(std::nullptr_t = nullptr) noexcept {}
        IDnssdRegistrationResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IDnssdRegistrationResult(IDnssdRegistrationResult const&) noexcept = default;
        IDnssdRegistrationResult(IDnssdRegistrationResult&&) noexcept = default;
        IDnssdRegistrationResult& operator=(IDnssdRegistrationResult const&) & noexcept = default;
        IDnssdRegistrationResult& operator=(IDnssdRegistrationResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IDnssdServiceInstance :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IDnssdServiceInstance>
    {
        IDnssdServiceInstance(std::nullptr_t = nullptr) noexcept {}
        IDnssdServiceInstance(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IDnssdServiceInstance(IDnssdServiceInstance const&) noexcept = default;
        IDnssdServiceInstance(IDnssdServiceInstance&&) noexcept = default;
        IDnssdServiceInstance& operator=(IDnssdServiceInstance const&) & noexcept = default;
        IDnssdServiceInstance& operator=(IDnssdServiceInstance&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IDnssdServiceInstanceFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IDnssdServiceInstanceFactory>
    {
        IDnssdServiceInstanceFactory(std::nullptr_t = nullptr) noexcept {}
        IDnssdServiceInstanceFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IDnssdServiceInstanceFactory(IDnssdServiceInstanceFactory const&) noexcept = default;
        IDnssdServiceInstanceFactory(IDnssdServiceInstanceFactory&&) noexcept = default;
        IDnssdServiceInstanceFactory& operator=(IDnssdServiceInstanceFactory const&) & noexcept = default;
        IDnssdServiceInstanceFactory& operator=(IDnssdServiceInstanceFactory&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IDnssdServiceWatcher :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IDnssdServiceWatcher>
    {
        IDnssdServiceWatcher(std::nullptr_t = nullptr) noexcept {}
        IDnssdServiceWatcher(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IDnssdServiceWatcher(IDnssdServiceWatcher const&) noexcept = default;
        IDnssdServiceWatcher(IDnssdServiceWatcher&&) noexcept = default;
        IDnssdServiceWatcher& operator=(IDnssdServiceWatcher const&) & noexcept = default;
        IDnssdServiceWatcher& operator=(IDnssdServiceWatcher&&) & noexcept = default;
    };
}
#endif
