// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Devices_SmartCards_2_H
#define WINRT_Windows_Devices_SmartCards_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.Foundation.Collections.1.h"
#include "winrt/impl/Windows.Storage.Streams.1.h"
#include "winrt/impl/Windows.Devices.SmartCards.1.h"
WINRT_EXPORT namespace winrt::Windows::Devices::SmartCards
{
    struct SmartCardPinResetHandler : Windows::Foundation::IUnknown
    {
        SmartCardPinResetHandler(std::nullptr_t = nullptr) noexcept {}
        SmartCardPinResetHandler(void* ptr, take_ownership_from_abi_t) noexcept : Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        SmartCardPinResetHandler(SmartCardPinResetHandler const&) noexcept = default;
        SmartCardPinResetHandler(SmartCardPinResetHandler&&) noexcept = default;
        SmartCardPinResetHandler& operator=(SmartCardPinResetHandler const&) & noexcept = default;
        SmartCardPinResetHandler& operator=(SmartCardPinResetHandler&&) & noexcept = default;
        template <typename L> SmartCardPinResetHandler(L lambda);
        template <typename F> SmartCardPinResetHandler(F* function);
        template <typename O, typename M> SmartCardPinResetHandler(O* object, M method);
        template <typename O, typename M> SmartCardPinResetHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> SmartCardPinResetHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Devices::SmartCards::SmartCardProvisioning const& sender, winrt::Windows::Devices::SmartCards::SmartCardPinResetRequest const& request) const;
    };
    struct __declspec(empty_bases) CardAddedEventArgs : winrt::Windows::Devices::SmartCards::ICardAddedEventArgs
    {
        CardAddedEventArgs(std::nullptr_t) noexcept {}
        CardAddedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ICardAddedEventArgs(ptr, take_ownership_from_abi) {}
        CardAddedEventArgs(CardAddedEventArgs const&) noexcept = default;
        CardAddedEventArgs(CardAddedEventArgs&&) noexcept = default;
        CardAddedEventArgs& operator=(CardAddedEventArgs const&) & noexcept = default;
        CardAddedEventArgs& operator=(CardAddedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) CardRemovedEventArgs : winrt::Windows::Devices::SmartCards::ICardRemovedEventArgs
    {
        CardRemovedEventArgs(std::nullptr_t) noexcept {}
        CardRemovedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ICardRemovedEventArgs(ptr, take_ownership_from_abi) {}
        CardRemovedEventArgs(CardRemovedEventArgs const&) noexcept = default;
        CardRemovedEventArgs(CardRemovedEventArgs&&) noexcept = default;
        CardRemovedEventArgs& operator=(CardRemovedEventArgs const&) & noexcept = default;
        CardRemovedEventArgs& operator=(CardRemovedEventArgs&&) & noexcept = default;
    };
    struct KnownSmartCardAppletIds
    {
        KnownSmartCardAppletIds() = delete;
        [[nodiscard]] static auto PaymentSystemEnvironment();
        [[nodiscard]] static auto ProximityPaymentSystemEnvironment();
    };
    struct __declspec(empty_bases) SmartCard : winrt::Windows::Devices::SmartCards::ISmartCard,
        impl::require<SmartCard, winrt::Windows::Devices::SmartCards::ISmartCardConnect>
    {
        SmartCard(std::nullptr_t) noexcept {}
        SmartCard(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCard(ptr, take_ownership_from_abi) {}
        SmartCard(SmartCard const&) noexcept = default;
        SmartCard(SmartCard&&) noexcept = default;
        SmartCard& operator=(SmartCard const&) & noexcept = default;
        SmartCard& operator=(SmartCard&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardAppletIdGroup : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup,
        impl::require<SmartCardAppletIdGroup, winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup2>
    {
        SmartCardAppletIdGroup(std::nullptr_t) noexcept {}
        SmartCardAppletIdGroup(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroup(ptr, take_ownership_from_abi) {}
        SmartCardAppletIdGroup();
        SmartCardAppletIdGroup(param::hstring const& displayName, param::vector<winrt::Windows::Storage::Streams::IBuffer> const& appletIds, winrt::Windows::Devices::SmartCards::SmartCardEmulationCategory const& emulationCategory, winrt::Windows::Devices::SmartCards::SmartCardEmulationType const& emulationType);
        SmartCardAppletIdGroup(SmartCardAppletIdGroup const&) noexcept = default;
        SmartCardAppletIdGroup(SmartCardAppletIdGroup&&) noexcept = default;
        SmartCardAppletIdGroup& operator=(SmartCardAppletIdGroup const&) & noexcept = default;
        SmartCardAppletIdGroup& operator=(SmartCardAppletIdGroup&&) & noexcept = default;
        [[nodiscard]] static auto MaxAppletIds();
    };
    struct __declspec(empty_bases) SmartCardAppletIdGroupRegistration : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration,
        impl::require<SmartCardAppletIdGroupRegistration, winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration2>
    {
        SmartCardAppletIdGroupRegistration(std::nullptr_t) noexcept {}
        SmartCardAppletIdGroupRegistration(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAppletIdGroupRegistration(ptr, take_ownership_from_abi) {}
        SmartCardAppletIdGroupRegistration(SmartCardAppletIdGroupRegistration const&) noexcept = default;
        SmartCardAppletIdGroupRegistration(SmartCardAppletIdGroupRegistration&&) noexcept = default;
        SmartCardAppletIdGroupRegistration& operator=(SmartCardAppletIdGroupRegistration const&) & noexcept = default;
        SmartCardAppletIdGroupRegistration& operator=(SmartCardAppletIdGroupRegistration&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardAutomaticResponseApdu : winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu,
        impl::require<SmartCardAutomaticResponseApdu, winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu2, winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu3>
    {
        SmartCardAutomaticResponseApdu(std::nullptr_t) noexcept {}
        SmartCardAutomaticResponseApdu(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardAutomaticResponseApdu(ptr, take_ownership_from_abi) {}
        SmartCardAutomaticResponseApdu(winrt::Windows::Storage::Streams::IBuffer const& commandApdu, winrt::Windows::Storage::Streams::IBuffer const& responseApdu);
        SmartCardAutomaticResponseApdu(SmartCardAutomaticResponseApdu const&) noexcept = default;
        SmartCardAutomaticResponseApdu(SmartCardAutomaticResponseApdu&&) noexcept = default;
        SmartCardAutomaticResponseApdu& operator=(SmartCardAutomaticResponseApdu const&) & noexcept = default;
        SmartCardAutomaticResponseApdu& operator=(SmartCardAutomaticResponseApdu&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardChallengeContext : winrt::Windows::Devices::SmartCards::ISmartCardChallengeContext
    {
        SmartCardChallengeContext(std::nullptr_t) noexcept {}
        SmartCardChallengeContext(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardChallengeContext(ptr, take_ownership_from_abi) {}
        SmartCardChallengeContext(SmartCardChallengeContext const&) noexcept = default;
        SmartCardChallengeContext(SmartCardChallengeContext&&) noexcept = default;
        SmartCardChallengeContext& operator=(SmartCardChallengeContext const&) & noexcept = default;
        SmartCardChallengeContext& operator=(SmartCardChallengeContext&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardConnection : winrt::Windows::Devices::SmartCards::ISmartCardConnection
    {
        SmartCardConnection(std::nullptr_t) noexcept {}
        SmartCardConnection(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardConnection(ptr, take_ownership_from_abi) {}
        SmartCardConnection(SmartCardConnection const&) noexcept = default;
        SmartCardConnection(SmartCardConnection&&) noexcept = default;
        SmartCardConnection& operator=(SmartCardConnection const&) & noexcept = default;
        SmartCardConnection& operator=(SmartCardConnection&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramGenerator : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator,
        impl::require<SmartCardCryptogramGenerator, winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator2>
    {
        SmartCardCryptogramGenerator(std::nullptr_t) noexcept {}
        SmartCardCryptogramGenerator(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGenerator(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGenerator(SmartCardCryptogramGenerator const&) noexcept = default;
        SmartCardCryptogramGenerator(SmartCardCryptogramGenerator&&) noexcept = default;
        SmartCardCryptogramGenerator& operator=(SmartCardCryptogramGenerator const&) & noexcept = default;
        SmartCardCryptogramGenerator& operator=(SmartCardCryptogramGenerator&&) & noexcept = default;
        static auto GetSmartCardCryptogramGeneratorAsync();
        static auto IsSupported();
    };
    struct __declspec(empty_bases) SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult();
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult const&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult(SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult&&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult const&) & noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramMaterialCharacteristicsResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult();
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult const&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult(SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult&&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult const&) & noexcept = default;
        SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramMaterialPackageCharacteristicsResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult
    {
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(std::nullptr_t) noexcept {}
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult();
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult const&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult(SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult&&) noexcept = default;
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult const&) & noexcept = default;
        SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult& operator=(SmartCardCryptogramGetAllCryptogramStorageKeyCharacteristicsResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramMaterialCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialCharacteristics
    {
        SmartCardCryptogramMaterialCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramMaterialCharacteristics();
        SmartCardCryptogramMaterialCharacteristics(SmartCardCryptogramMaterialCharacteristics const&) noexcept = default;
        SmartCardCryptogramMaterialCharacteristics(SmartCardCryptogramMaterialCharacteristics&&) noexcept = default;
        SmartCardCryptogramMaterialCharacteristics& operator=(SmartCardCryptogramMaterialCharacteristics const&) & noexcept = default;
        SmartCardCryptogramMaterialCharacteristics& operator=(SmartCardCryptogramMaterialCharacteristics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramMaterialPackageCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPackageCharacteristics
    {
        SmartCardCryptogramMaterialPackageCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialPackageCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPackageCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramMaterialPackageCharacteristics();
        SmartCardCryptogramMaterialPackageCharacteristics(SmartCardCryptogramMaterialPackageCharacteristics const&) noexcept = default;
        SmartCardCryptogramMaterialPackageCharacteristics(SmartCardCryptogramMaterialPackageCharacteristics&&) noexcept = default;
        SmartCardCryptogramMaterialPackageCharacteristics& operator=(SmartCardCryptogramMaterialPackageCharacteristics const&) & noexcept = default;
        SmartCardCryptogramMaterialPackageCharacteristics& operator=(SmartCardCryptogramMaterialPackageCharacteristics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramMaterialPossessionProof : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPossessionProof
    {
        SmartCardCryptogramMaterialPossessionProof(std::nullptr_t) noexcept {}
        SmartCardCryptogramMaterialPossessionProof(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramMaterialPossessionProof(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramMaterialPossessionProof(SmartCardCryptogramMaterialPossessionProof const&) noexcept = default;
        SmartCardCryptogramMaterialPossessionProof(SmartCardCryptogramMaterialPossessionProof&&) noexcept = default;
        SmartCardCryptogramMaterialPossessionProof& operator=(SmartCardCryptogramMaterialPossessionProof const&) & noexcept = default;
        SmartCardCryptogramMaterialPossessionProof& operator=(SmartCardCryptogramMaterialPossessionProof&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramPlacementStep : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramPlacementStep
    {
        SmartCardCryptogramPlacementStep(std::nullptr_t) noexcept {}
        SmartCardCryptogramPlacementStep(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramPlacementStep(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramPlacementStep();
        SmartCardCryptogramPlacementStep(SmartCardCryptogramPlacementStep const&) noexcept = default;
        SmartCardCryptogramPlacementStep(SmartCardCryptogramPlacementStep&&) noexcept = default;
        SmartCardCryptogramPlacementStep& operator=(SmartCardCryptogramPlacementStep const&) & noexcept = default;
        SmartCardCryptogramPlacementStep& operator=(SmartCardCryptogramPlacementStep&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramStorageKeyCharacteristics : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyCharacteristics
    {
        SmartCardCryptogramStorageKeyCharacteristics(std::nullptr_t) noexcept {}
        SmartCardCryptogramStorageKeyCharacteristics(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyCharacteristics(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramStorageKeyCharacteristics();
        SmartCardCryptogramStorageKeyCharacteristics(SmartCardCryptogramStorageKeyCharacteristics const&) noexcept = default;
        SmartCardCryptogramStorageKeyCharacteristics(SmartCardCryptogramStorageKeyCharacteristics&&) noexcept = default;
        SmartCardCryptogramStorageKeyCharacteristics& operator=(SmartCardCryptogramStorageKeyCharacteristics const&) & noexcept = default;
        SmartCardCryptogramStorageKeyCharacteristics& operator=(SmartCardCryptogramStorageKeyCharacteristics&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardCryptogramStorageKeyInfo : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo,
        impl::require<SmartCardCryptogramStorageKeyInfo, winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo2>
    {
        SmartCardCryptogramStorageKeyInfo(std::nullptr_t) noexcept {}
        SmartCardCryptogramStorageKeyInfo(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardCryptogramStorageKeyInfo(ptr, take_ownership_from_abi) {}
        SmartCardCryptogramStorageKeyInfo(SmartCardCryptogramStorageKeyInfo const&) noexcept = default;
        SmartCardCryptogramStorageKeyInfo(SmartCardCryptogramStorageKeyInfo&&) noexcept = default;
        SmartCardCryptogramStorageKeyInfo& operator=(SmartCardCryptogramStorageKeyInfo const&) & noexcept = default;
        SmartCardCryptogramStorageKeyInfo& operator=(SmartCardCryptogramStorageKeyInfo&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardEmulator : winrt::Windows::Devices::SmartCards::ISmartCardEmulator,
        impl::require<SmartCardEmulator, winrt::Windows::Devices::SmartCards::ISmartCardEmulator2>
    {
        SmartCardEmulator(std::nullptr_t) noexcept {}
        SmartCardEmulator(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulator(ptr, take_ownership_from_abi) {}
        SmartCardEmulator(SmartCardEmulator const&) noexcept = default;
        SmartCardEmulator(SmartCardEmulator&&) noexcept = default;
        SmartCardEmulator& operator=(SmartCardEmulator const&) & noexcept = default;
        SmartCardEmulator& operator=(SmartCardEmulator&&) & noexcept = default;
        static auto GetDefaultAsync();
        static auto GetAppletIdGroupRegistrationsAsync();
        static auto RegisterAppletIdGroupAsync(winrt::Windows::Devices::SmartCards::SmartCardAppletIdGroup const& appletIdGroup);
        static auto UnregisterAppletIdGroupAsync(winrt::Windows::Devices::SmartCards::SmartCardAppletIdGroupRegistration const& registration);
        [[nodiscard]] static auto MaxAppletIdGroupRegistrations();
        static auto IsSupported();
    };
    struct __declspec(empty_bases) SmartCardEmulatorApduReceivedEventArgs : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs,
        impl::require<SmartCardEmulatorApduReceivedEventArgs, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgsWithCryptograms, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs2>
    {
        SmartCardEmulatorApduReceivedEventArgs(std::nullptr_t) noexcept {}
        SmartCardEmulatorApduReceivedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs(ptr, take_ownership_from_abi) {}
        SmartCardEmulatorApduReceivedEventArgs(SmartCardEmulatorApduReceivedEventArgs const&) noexcept = default;
        SmartCardEmulatorApduReceivedEventArgs(SmartCardEmulatorApduReceivedEventArgs&&) noexcept = default;
        SmartCardEmulatorApduReceivedEventArgs& operator=(SmartCardEmulatorApduReceivedEventArgs const&) & noexcept = default;
        SmartCardEmulatorApduReceivedEventArgs& operator=(SmartCardEmulatorApduReceivedEventArgs&&) & noexcept = default;
        using winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs::TryRespondAsync;
        using impl::consume_t<SmartCardEmulatorApduReceivedEventArgs, winrt::Windows::Devices::SmartCards::ISmartCardEmulatorApduReceivedEventArgs2>::TryRespondAsync;
    };
    struct __declspec(empty_bases) SmartCardEmulatorConnectionDeactivatedEventArgs : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionDeactivatedEventArgs
    {
        SmartCardEmulatorConnectionDeactivatedEventArgs(std::nullptr_t) noexcept {}
        SmartCardEmulatorConnectionDeactivatedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionDeactivatedEventArgs(ptr, take_ownership_from_abi) {}
        SmartCardEmulatorConnectionDeactivatedEventArgs(SmartCardEmulatorConnectionDeactivatedEventArgs const&) noexcept = default;
        SmartCardEmulatorConnectionDeactivatedEventArgs(SmartCardEmulatorConnectionDeactivatedEventArgs&&) noexcept = default;
        SmartCardEmulatorConnectionDeactivatedEventArgs& operator=(SmartCardEmulatorConnectionDeactivatedEventArgs const&) & noexcept = default;
        SmartCardEmulatorConnectionDeactivatedEventArgs& operator=(SmartCardEmulatorConnectionDeactivatedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardEmulatorConnectionProperties : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionProperties
    {
        SmartCardEmulatorConnectionProperties(std::nullptr_t) noexcept {}
        SmartCardEmulatorConnectionProperties(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardEmulatorConnectionProperties(ptr, take_ownership_from_abi) {}
        SmartCardEmulatorConnectionProperties(SmartCardEmulatorConnectionProperties const&) noexcept = default;
        SmartCardEmulatorConnectionProperties(SmartCardEmulatorConnectionProperties&&) noexcept = default;
        SmartCardEmulatorConnectionProperties& operator=(SmartCardEmulatorConnectionProperties const&) & noexcept = default;
        SmartCardEmulatorConnectionProperties& operator=(SmartCardEmulatorConnectionProperties&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardPinPolicy : winrt::Windows::Devices::SmartCards::ISmartCardPinPolicy
    {
        SmartCardPinPolicy(std::nullptr_t) noexcept {}
        SmartCardPinPolicy(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinPolicy(ptr, take_ownership_from_abi) {}
        SmartCardPinPolicy();
        SmartCardPinPolicy(SmartCardPinPolicy const&) noexcept = default;
        SmartCardPinPolicy(SmartCardPinPolicy&&) noexcept = default;
        SmartCardPinPolicy& operator=(SmartCardPinPolicy const&) & noexcept = default;
        SmartCardPinPolicy& operator=(SmartCardPinPolicy&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardPinResetDeferral : winrt::Windows::Devices::SmartCards::ISmartCardPinResetDeferral
    {
        SmartCardPinResetDeferral(std::nullptr_t) noexcept {}
        SmartCardPinResetDeferral(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinResetDeferral(ptr, take_ownership_from_abi) {}
        SmartCardPinResetDeferral(SmartCardPinResetDeferral const&) noexcept = default;
        SmartCardPinResetDeferral(SmartCardPinResetDeferral&&) noexcept = default;
        SmartCardPinResetDeferral& operator=(SmartCardPinResetDeferral const&) & noexcept = default;
        SmartCardPinResetDeferral& operator=(SmartCardPinResetDeferral&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardPinResetRequest : winrt::Windows::Devices::SmartCards::ISmartCardPinResetRequest
    {
        SmartCardPinResetRequest(std::nullptr_t) noexcept {}
        SmartCardPinResetRequest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardPinResetRequest(ptr, take_ownership_from_abi) {}
        SmartCardPinResetRequest(SmartCardPinResetRequest const&) noexcept = default;
        SmartCardPinResetRequest(SmartCardPinResetRequest&&) noexcept = default;
        SmartCardPinResetRequest& operator=(SmartCardPinResetRequest const&) & noexcept = default;
        SmartCardPinResetRequest& operator=(SmartCardPinResetRequest&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SmartCardProvisioning : winrt::Windows::Devices::SmartCards::ISmartCardProvisioning,
        impl::require<SmartCardProvisioning, winrt::Windows::Devices::SmartCards::ISmartCardProvisioning2>
    {
        SmartCardProvisioning(std::nullptr_t) noexcept {}
        SmartCardProvisioning(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardProvisioning(ptr, take_ownership_from_abi) {}
        SmartCardProvisioning(SmartCardProvisioning const&) noexcept = default;
        SmartCardProvisioning(SmartCardProvisioning&&) noexcept = default;
        SmartCardProvisioning& operator=(SmartCardProvisioning const&) & noexcept = default;
        SmartCardProvisioning& operator=(SmartCardProvisioning&&) & noexcept = default;
        static auto FromSmartCardAsync(winrt::Windows::Devices::SmartCards::SmartCard const& card);
        static auto RequestVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy);
        static auto RequestVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy, winrt::guid const& cardId);
        static auto RequestVirtualSmartCardDeletionAsync(winrt::Windows::Devices::SmartCards::SmartCard const& card);
        static auto RequestAttestedVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy);
        static auto RequestAttestedVirtualSmartCardCreationAsync(param::hstring const& friendlyName, winrt::Windows::Storage::Streams::IBuffer const& administrativeKey, winrt::Windows::Devices::SmartCards::SmartCardPinPolicy const& pinPolicy, winrt::guid const& cardId);
    };
    struct __declspec(empty_bases) SmartCardReader : winrt::Windows::Devices::SmartCards::ISmartCardReader
    {
        SmartCardReader(std::nullptr_t) noexcept {}
        SmartCardReader(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardReader(ptr, take_ownership_from_abi) {}
        SmartCardReader(SmartCardReader const&) noexcept = default;
        SmartCardReader(SmartCardReader&&) noexcept = default;
        SmartCardReader& operator=(SmartCardReader const&) & noexcept = default;
        SmartCardReader& operator=(SmartCardReader&&) & noexcept = default;
        static auto GetDeviceSelector();
        static auto GetDeviceSelector(winrt::Windows::Devices::SmartCards::SmartCardReaderKind const& kind);
        static auto FromIdAsync(param::hstring const& deviceId);
    };
    struct __declspec(empty_bases) SmartCardTriggerDetails : winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails,
        impl::require<SmartCardTriggerDetails, winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails2, winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails3>
    {
        SmartCardTriggerDetails(std::nullptr_t) noexcept {}
        SmartCardTriggerDetails(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Devices::SmartCards::ISmartCardTriggerDetails(ptr, take_ownership_from_abi) {}
        SmartCardTriggerDetails(SmartCardTriggerDetails const&) noexcept = default;
        SmartCardTriggerDetails(SmartCardTriggerDetails&&) noexcept = default;
        SmartCardTriggerDetails& operator=(SmartCardTriggerDetails const&) & noexcept = default;
        SmartCardTriggerDetails& operator=(SmartCardTriggerDetails&&) & noexcept = default;
    };
}
#endif
