// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Devices_Gpio_Provider_1_H
#define WINRT_Windows_Devices_Gpio_Provider_1_H
#include "winrt/impl/Windows.Devices.Gpio.Provider.0.h"
WINRT_EXPORT namespace winrt::Windows::Devices::Gpio::Provider
{
    struct __declspec(empty_bases) IGpioControllerProvider :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGpioControllerProvider>
    {
        IGpioControllerProvider(std::nullptr_t = nullptr) noexcept {}
        IGpioControllerProvider(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGpioControllerProvider(IGpioControllerProvider const&) noexcept = default;
        IGpioControllerProvider(IGpioControllerProvider&&) noexcept = default;
        IGpioControllerProvider& operator=(IGpioControllerProvider const&) & noexcept = default;
        IGpioControllerProvider& operator=(IGpioControllerProvider&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IGpioPinProvider :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGpioPinProvider>
    {
        IGpioPinProvider(std::nullptr_t = nullptr) noexcept {}
        IGpioPinProvider(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGpioPinProvider(IGpioPinProvider const&) noexcept = default;
        IGpioPinProvider(IGpioPinProvider&&) noexcept = default;
        IGpioPinProvider& operator=(IGpioPinProvider const&) & noexcept = default;
        IGpioPinProvider& operator=(IGpioPinProvider&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IGpioPinProviderValueChangedEventArgs :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGpioPinProviderValueChangedEventArgs>
    {
        IGpioPinProviderValueChangedEventArgs(std::nullptr_t = nullptr) noexcept {}
        IGpioPinProviderValueChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGpioPinProviderValueChangedEventArgs(IGpioPinProviderValueChangedEventArgs const&) noexcept = default;
        IGpioPinProviderValueChangedEventArgs(IGpioPinProviderValueChangedEventArgs&&) noexcept = default;
        IGpioPinProviderValueChangedEventArgs& operator=(IGpioPinProviderValueChangedEventArgs const&) & noexcept = default;
        IGpioPinProviderValueChangedEventArgs& operator=(IGpioPinProviderValueChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IGpioPinProviderValueChangedEventArgsFactory :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGpioPinProviderValueChangedEventArgsFactory>
    {
        IGpioPinProviderValueChangedEventArgsFactory(std::nullptr_t = nullptr) noexcept {}
        IGpioPinProviderValueChangedEventArgsFactory(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGpioPinProviderValueChangedEventArgsFactory(IGpioPinProviderValueChangedEventArgsFactory const&) noexcept = default;
        IGpioPinProviderValueChangedEventArgsFactory(IGpioPinProviderValueChangedEventArgsFactory&&) noexcept = default;
        IGpioPinProviderValueChangedEventArgsFactory& operator=(IGpioPinProviderValueChangedEventArgsFactory const&) & noexcept = default;
        IGpioPinProviderValueChangedEventArgsFactory& operator=(IGpioPinProviderValueChangedEventArgsFactory&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IGpioProvider :
        winrt::Windows::Foundation::IInspectable,
        impl::consume_t<IGpioProvider>
    {
        IGpioProvider(std::nullptr_t = nullptr) noexcept {}
        IGpioProvider(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IInspectable(ptr, take_ownership_from_abi) {}
        IGpioProvider(IGpioProvider const&) noexcept = default;
        IGpioProvider(IGpioProvider&&) noexcept = default;
        IGpioProvider& operator=(IGpioProvider const&) & noexcept = default;
        IGpioProvider& operator=(IGpioProvider&&) & noexcept = default;
    };
}
#endif
