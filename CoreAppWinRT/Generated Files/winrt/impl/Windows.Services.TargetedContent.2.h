// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Services_TargetedContent_2_H
#define WINRT_Windows_Services_TargetedContent_2_H
#include "winrt/impl/Windows.Storage.Streams.1.h"
#include "winrt/impl/Windows.Services.TargetedContent.1.h"
WINRT_EXPORT namespace winrt::Windows::Services::TargetedContent
{
    struct __declspec(empty_bases) TargetedContentAction : winrt::Windows::Services::TargetedContent::ITargetedContentAction
    {
        TargetedContentAction(std::nullptr_t) noexcept {}
        TargetedContentAction(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentAction(ptr, take_ownership_from_abi) {}
        TargetedContentAction(TargetedContentAction const&) noexcept = default;
        TargetedContentAction(TargetedContentAction&&) noexcept = default;
        TargetedContentAction& operator=(TargetedContentAction const&) & noexcept = default;
        TargetedContentAction& operator=(TargetedContentAction&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentAvailabilityChangedEventArgs : winrt::Windows::Services::TargetedContent::ITargetedContentAvailabilityChangedEventArgs
    {
        TargetedContentAvailabilityChangedEventArgs(std::nullptr_t) noexcept {}
        TargetedContentAvailabilityChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentAvailabilityChangedEventArgs(ptr, take_ownership_from_abi) {}
        TargetedContentAvailabilityChangedEventArgs(TargetedContentAvailabilityChangedEventArgs const&) noexcept = default;
        TargetedContentAvailabilityChangedEventArgs(TargetedContentAvailabilityChangedEventArgs&&) noexcept = default;
        TargetedContentAvailabilityChangedEventArgs& operator=(TargetedContentAvailabilityChangedEventArgs const&) & noexcept = default;
        TargetedContentAvailabilityChangedEventArgs& operator=(TargetedContentAvailabilityChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentChangedEventArgs : winrt::Windows::Services::TargetedContent::ITargetedContentChangedEventArgs
    {
        TargetedContentChangedEventArgs(std::nullptr_t) noexcept {}
        TargetedContentChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentChangedEventArgs(ptr, take_ownership_from_abi) {}
        TargetedContentChangedEventArgs(TargetedContentChangedEventArgs const&) noexcept = default;
        TargetedContentChangedEventArgs(TargetedContentChangedEventArgs&&) noexcept = default;
        TargetedContentChangedEventArgs& operator=(TargetedContentChangedEventArgs const&) & noexcept = default;
        TargetedContentChangedEventArgs& operator=(TargetedContentChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentCollection : winrt::Windows::Services::TargetedContent::ITargetedContentCollection
    {
        TargetedContentCollection(std::nullptr_t) noexcept {}
        TargetedContentCollection(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentCollection(ptr, take_ownership_from_abi) {}
        TargetedContentCollection(TargetedContentCollection const&) noexcept = default;
        TargetedContentCollection(TargetedContentCollection&&) noexcept = default;
        TargetedContentCollection& operator=(TargetedContentCollection const&) & noexcept = default;
        TargetedContentCollection& operator=(TargetedContentCollection&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentContainer : winrt::Windows::Services::TargetedContent::ITargetedContentContainer
    {
        TargetedContentContainer(std::nullptr_t) noexcept {}
        TargetedContentContainer(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentContainer(ptr, take_ownership_from_abi) {}
        TargetedContentContainer(TargetedContentContainer const&) noexcept = default;
        TargetedContentContainer(TargetedContentContainer&&) noexcept = default;
        TargetedContentContainer& operator=(TargetedContentContainer const&) & noexcept = default;
        TargetedContentContainer& operator=(TargetedContentContainer&&) & noexcept = default;
        static auto GetAsync(param::hstring const& contentId);
    };
    struct __declspec(empty_bases) TargetedContentFile : winrt::Windows::Storage::Streams::IRandomAccessStreamReference
    {
        TargetedContentFile(std::nullptr_t) noexcept {}
        TargetedContentFile(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Storage::Streams::IRandomAccessStreamReference(ptr, take_ownership_from_abi) {}
        TargetedContentFile(TargetedContentFile const&) noexcept = default;
        TargetedContentFile(TargetedContentFile&&) noexcept = default;
        TargetedContentFile& operator=(TargetedContentFile const&) & noexcept = default;
        TargetedContentFile& operator=(TargetedContentFile&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentImage : winrt::Windows::Services::TargetedContent::ITargetedContentImage
    {
        TargetedContentImage(std::nullptr_t) noexcept {}
        TargetedContentImage(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentImage(ptr, take_ownership_from_abi) {}
        TargetedContentImage(TargetedContentImage const&) noexcept = default;
        TargetedContentImage(TargetedContentImage&&) noexcept = default;
        TargetedContentImage& operator=(TargetedContentImage const&) & noexcept = default;
        TargetedContentImage& operator=(TargetedContentImage&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentItem : winrt::Windows::Services::TargetedContent::ITargetedContentItem
    {
        TargetedContentItem(std::nullptr_t) noexcept {}
        TargetedContentItem(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentItem(ptr, take_ownership_from_abi) {}
        TargetedContentItem(TargetedContentItem const&) noexcept = default;
        TargetedContentItem(TargetedContentItem&&) noexcept = default;
        TargetedContentItem& operator=(TargetedContentItem const&) & noexcept = default;
        TargetedContentItem& operator=(TargetedContentItem&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentItemState : winrt::Windows::Services::TargetedContent::ITargetedContentItemState
    {
        TargetedContentItemState(std::nullptr_t) noexcept {}
        TargetedContentItemState(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentItemState(ptr, take_ownership_from_abi) {}
        TargetedContentItemState(TargetedContentItemState const&) noexcept = default;
        TargetedContentItemState(TargetedContentItemState&&) noexcept = default;
        TargetedContentItemState& operator=(TargetedContentItemState const&) & noexcept = default;
        TargetedContentItemState& operator=(TargetedContentItemState&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentObject : winrt::Windows::Services::TargetedContent::ITargetedContentObject
    {
        TargetedContentObject(std::nullptr_t) noexcept {}
        TargetedContentObject(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentObject(ptr, take_ownership_from_abi) {}
        TargetedContentObject(TargetedContentObject const&) noexcept = default;
        TargetedContentObject(TargetedContentObject&&) noexcept = default;
        TargetedContentObject& operator=(TargetedContentObject const&) & noexcept = default;
        TargetedContentObject& operator=(TargetedContentObject&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentStateChangedEventArgs : winrt::Windows::Services::TargetedContent::ITargetedContentStateChangedEventArgs
    {
        TargetedContentStateChangedEventArgs(std::nullptr_t) noexcept {}
        TargetedContentStateChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentStateChangedEventArgs(ptr, take_ownership_from_abi) {}
        TargetedContentStateChangedEventArgs(TargetedContentStateChangedEventArgs const&) noexcept = default;
        TargetedContentStateChangedEventArgs(TargetedContentStateChangedEventArgs&&) noexcept = default;
        TargetedContentStateChangedEventArgs& operator=(TargetedContentStateChangedEventArgs const&) & noexcept = default;
        TargetedContentStateChangedEventArgs& operator=(TargetedContentStateChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentSubscription : winrt::Windows::Services::TargetedContent::ITargetedContentSubscription
    {
        TargetedContentSubscription(std::nullptr_t) noexcept {}
        TargetedContentSubscription(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentSubscription(ptr, take_ownership_from_abi) {}
        TargetedContentSubscription(TargetedContentSubscription const&) noexcept = default;
        TargetedContentSubscription(TargetedContentSubscription&&) noexcept = default;
        TargetedContentSubscription& operator=(TargetedContentSubscription const&) & noexcept = default;
        TargetedContentSubscription& operator=(TargetedContentSubscription&&) & noexcept = default;
        static auto GetAsync(param::hstring const& subscriptionId);
        static auto GetOptions(param::hstring const& subscriptionId);
    };
    struct __declspec(empty_bases) TargetedContentSubscriptionOptions : winrt::Windows::Services::TargetedContent::ITargetedContentSubscriptionOptions
    {
        TargetedContentSubscriptionOptions(std::nullptr_t) noexcept {}
        TargetedContentSubscriptionOptions(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentSubscriptionOptions(ptr, take_ownership_from_abi) {}
        TargetedContentSubscriptionOptions(TargetedContentSubscriptionOptions const&) noexcept = default;
        TargetedContentSubscriptionOptions(TargetedContentSubscriptionOptions&&) noexcept = default;
        TargetedContentSubscriptionOptions& operator=(TargetedContentSubscriptionOptions const&) & noexcept = default;
        TargetedContentSubscriptionOptions& operator=(TargetedContentSubscriptionOptions&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TargetedContentValue : winrt::Windows::Services::TargetedContent::ITargetedContentValue
    {
        TargetedContentValue(std::nullptr_t) noexcept {}
        TargetedContentValue(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Services::TargetedContent::ITargetedContentValue(ptr, take_ownership_from_abi) {}
        TargetedContentValue(TargetedContentValue const&) noexcept = default;
        TargetedContentValue(TargetedContentValue&&) noexcept = default;
        TargetedContentValue& operator=(TargetedContentValue const&) & noexcept = default;
        TargetedContentValue& operator=(TargetedContentValue&&) & noexcept = default;
    };
}
#endif
