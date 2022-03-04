// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_ApplicationModel_Payments_Provider_2_H
#define WINRT_Windows_ApplicationModel_Payments_Provider_2_H
#include "winrt/impl/Windows.ApplicationModel.Payments.Provider.1.h"
WINRT_EXPORT namespace winrt::Windows::ApplicationModel::Payments::Provider
{
    struct __declspec(empty_bases) PaymentAppCanMakePaymentTriggerDetails : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentAppCanMakePaymentTriggerDetails
    {
        PaymentAppCanMakePaymentTriggerDetails(std::nullptr_t) noexcept {}
        PaymentAppCanMakePaymentTriggerDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentAppCanMakePaymentTriggerDetails(ptr, take_ownership_from_abi) {}
        PaymentAppCanMakePaymentTriggerDetails(PaymentAppCanMakePaymentTriggerDetails const&) noexcept = default;
        PaymentAppCanMakePaymentTriggerDetails(PaymentAppCanMakePaymentTriggerDetails&&) noexcept = default;
        PaymentAppCanMakePaymentTriggerDetails& operator=(PaymentAppCanMakePaymentTriggerDetails const&) & noexcept = default;
        PaymentAppCanMakePaymentTriggerDetails& operator=(PaymentAppCanMakePaymentTriggerDetails&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PaymentAppManager : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentAppManager
    {
        PaymentAppManager(std::nullptr_t) noexcept {}
        PaymentAppManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentAppManager(ptr, take_ownership_from_abi) {}
        PaymentAppManager(PaymentAppManager const&) noexcept = default;
        PaymentAppManager(PaymentAppManager&&) noexcept = default;
        PaymentAppManager& operator=(PaymentAppManager const&) & noexcept = default;
        PaymentAppManager& operator=(PaymentAppManager&&) & noexcept = default;
        [[nodiscard]] static auto Current();
    };
    struct __declspec(empty_bases) PaymentTransaction : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentTransaction
    {
        PaymentTransaction(std::nullptr_t) noexcept {}
        PaymentTransaction(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentTransaction(ptr, take_ownership_from_abi) {}
        PaymentTransaction(PaymentTransaction const&) noexcept = default;
        PaymentTransaction(PaymentTransaction&&) noexcept = default;
        PaymentTransaction& operator=(PaymentTransaction const&) & noexcept = default;
        PaymentTransaction& operator=(PaymentTransaction&&) & noexcept = default;
        static auto FromIdAsync(param::hstring const& id);
    };
    struct __declspec(empty_bases) PaymentTransactionAcceptResult : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentTransactionAcceptResult
    {
        PaymentTransactionAcceptResult(std::nullptr_t) noexcept {}
        PaymentTransactionAcceptResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::ApplicationModel::Payments::Provider::IPaymentTransactionAcceptResult(ptr, take_ownership_from_abi) {}
        PaymentTransactionAcceptResult(PaymentTransactionAcceptResult const&) noexcept = default;
        PaymentTransactionAcceptResult(PaymentTransactionAcceptResult&&) noexcept = default;
        PaymentTransactionAcceptResult& operator=(PaymentTransactionAcceptResult const&) & noexcept = default;
        PaymentTransactionAcceptResult& operator=(PaymentTransactionAcceptResult&&) & noexcept = default;
    };
}
#endif
