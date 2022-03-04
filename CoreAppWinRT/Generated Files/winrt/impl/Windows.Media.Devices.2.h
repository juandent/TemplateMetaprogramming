// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.210503.4

#ifndef WINRT_Windows_Media_Devices_2_H
#define WINRT_Windows_Media_Devices_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.Media.Devices.1.h"
WINRT_EXPORT namespace winrt::Windows::Media::Devices
{
    struct __declspec(empty_bases) AdvancedPhotoCaptureSettings : winrt::Windows::Media::Devices::IAdvancedPhotoCaptureSettings
    {
        AdvancedPhotoCaptureSettings(std::nullptr_t) noexcept {}
        AdvancedPhotoCaptureSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAdvancedPhotoCaptureSettings(ptr, take_ownership_from_abi) {}
        AdvancedPhotoCaptureSettings();
        AdvancedPhotoCaptureSettings(AdvancedPhotoCaptureSettings const&) noexcept = default;
        AdvancedPhotoCaptureSettings(AdvancedPhotoCaptureSettings&&) noexcept = default;
        AdvancedPhotoCaptureSettings& operator=(AdvancedPhotoCaptureSettings const&) & noexcept = default;
        AdvancedPhotoCaptureSettings& operator=(AdvancedPhotoCaptureSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AdvancedPhotoControl : winrt::Windows::Media::Devices::IAdvancedPhotoControl
    {
        AdvancedPhotoControl(std::nullptr_t) noexcept {}
        AdvancedPhotoControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAdvancedPhotoControl(ptr, take_ownership_from_abi) {}
        AdvancedPhotoControl(AdvancedPhotoControl const&) noexcept = default;
        AdvancedPhotoControl(AdvancedPhotoControl&&) noexcept = default;
        AdvancedPhotoControl& operator=(AdvancedPhotoControl const&) & noexcept = default;
        AdvancedPhotoControl& operator=(AdvancedPhotoControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AudioDeviceController : winrt::Windows::Media::Devices::IAudioDeviceController
    {
        AudioDeviceController(std::nullptr_t) noexcept {}
        AudioDeviceController(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAudioDeviceController(ptr, take_ownership_from_abi) {}
        AudioDeviceController(AudioDeviceController const&) noexcept = default;
        AudioDeviceController(AudioDeviceController&&) noexcept = default;
        AudioDeviceController& operator=(AudioDeviceController const&) & noexcept = default;
        AudioDeviceController& operator=(AudioDeviceController&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AudioDeviceModule : winrt::Windows::Media::Devices::IAudioDeviceModule
    {
        AudioDeviceModule(std::nullptr_t) noexcept {}
        AudioDeviceModule(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAudioDeviceModule(ptr, take_ownership_from_abi) {}
        AudioDeviceModule(AudioDeviceModule const&) noexcept = default;
        AudioDeviceModule(AudioDeviceModule&&) noexcept = default;
        AudioDeviceModule& operator=(AudioDeviceModule const&) & noexcept = default;
        AudioDeviceModule& operator=(AudioDeviceModule&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AudioDeviceModuleNotificationEventArgs : winrt::Windows::Media::Devices::IAudioDeviceModuleNotificationEventArgs
    {
        AudioDeviceModuleNotificationEventArgs(std::nullptr_t) noexcept {}
        AudioDeviceModuleNotificationEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAudioDeviceModuleNotificationEventArgs(ptr, take_ownership_from_abi) {}
        AudioDeviceModuleNotificationEventArgs(AudioDeviceModuleNotificationEventArgs const&) noexcept = default;
        AudioDeviceModuleNotificationEventArgs(AudioDeviceModuleNotificationEventArgs&&) noexcept = default;
        AudioDeviceModuleNotificationEventArgs& operator=(AudioDeviceModuleNotificationEventArgs const&) & noexcept = default;
        AudioDeviceModuleNotificationEventArgs& operator=(AudioDeviceModuleNotificationEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) AudioDeviceModulesManager : winrt::Windows::Media::Devices::IAudioDeviceModulesManager
    {
        AudioDeviceModulesManager(std::nullptr_t) noexcept {}
        AudioDeviceModulesManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IAudioDeviceModulesManager(ptr, take_ownership_from_abi) {}
        explicit AudioDeviceModulesManager(param::hstring const& deviceId);
        AudioDeviceModulesManager(AudioDeviceModulesManager const&) noexcept = default;
        AudioDeviceModulesManager(AudioDeviceModulesManager&&) noexcept = default;
        AudioDeviceModulesManager& operator=(AudioDeviceModulesManager const&) & noexcept = default;
        AudioDeviceModulesManager& operator=(AudioDeviceModulesManager&&) & noexcept = default;
    };
    struct __declspec(empty_bases) DefaultAudioCaptureDeviceChangedEventArgs : winrt::Windows::Media::Devices::IDefaultAudioDeviceChangedEventArgs
    {
        DefaultAudioCaptureDeviceChangedEventArgs(std::nullptr_t) noexcept {}
        DefaultAudioCaptureDeviceChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IDefaultAudioDeviceChangedEventArgs(ptr, take_ownership_from_abi) {}
        DefaultAudioCaptureDeviceChangedEventArgs(DefaultAudioCaptureDeviceChangedEventArgs const&) noexcept = default;
        DefaultAudioCaptureDeviceChangedEventArgs(DefaultAudioCaptureDeviceChangedEventArgs&&) noexcept = default;
        DefaultAudioCaptureDeviceChangedEventArgs& operator=(DefaultAudioCaptureDeviceChangedEventArgs const&) & noexcept = default;
        DefaultAudioCaptureDeviceChangedEventArgs& operator=(DefaultAudioCaptureDeviceChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) DefaultAudioRenderDeviceChangedEventArgs : winrt::Windows::Media::Devices::IDefaultAudioDeviceChangedEventArgs
    {
        DefaultAudioRenderDeviceChangedEventArgs(std::nullptr_t) noexcept {}
        DefaultAudioRenderDeviceChangedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IDefaultAudioDeviceChangedEventArgs(ptr, take_ownership_from_abi) {}
        DefaultAudioRenderDeviceChangedEventArgs(DefaultAudioRenderDeviceChangedEventArgs const&) noexcept = default;
        DefaultAudioRenderDeviceChangedEventArgs(DefaultAudioRenderDeviceChangedEventArgs&&) noexcept = default;
        DefaultAudioRenderDeviceChangedEventArgs& operator=(DefaultAudioRenderDeviceChangedEventArgs const&) & noexcept = default;
        DefaultAudioRenderDeviceChangedEventArgs& operator=(DefaultAudioRenderDeviceChangedEventArgs&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ExposureCompensationControl : winrt::Windows::Media::Devices::IExposureCompensationControl
    {
        ExposureCompensationControl(std::nullptr_t) noexcept {}
        ExposureCompensationControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IExposureCompensationControl(ptr, take_ownership_from_abi) {}
        ExposureCompensationControl(ExposureCompensationControl const&) noexcept = default;
        ExposureCompensationControl(ExposureCompensationControl&&) noexcept = default;
        ExposureCompensationControl& operator=(ExposureCompensationControl const&) & noexcept = default;
        ExposureCompensationControl& operator=(ExposureCompensationControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ExposureControl : winrt::Windows::Media::Devices::IExposureControl
    {
        ExposureControl(std::nullptr_t) noexcept {}
        ExposureControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IExposureControl(ptr, take_ownership_from_abi) {}
        ExposureControl(ExposureControl const&) noexcept = default;
        ExposureControl(ExposureControl&&) noexcept = default;
        ExposureControl& operator=(ExposureControl const&) & noexcept = default;
        ExposureControl& operator=(ExposureControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ExposurePriorityVideoControl : winrt::Windows::Media::Devices::IExposurePriorityVideoControl
    {
        ExposurePriorityVideoControl(std::nullptr_t) noexcept {}
        ExposurePriorityVideoControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IExposurePriorityVideoControl(ptr, take_ownership_from_abi) {}
        ExposurePriorityVideoControl(ExposurePriorityVideoControl const&) noexcept = default;
        ExposurePriorityVideoControl(ExposurePriorityVideoControl&&) noexcept = default;
        ExposurePriorityVideoControl& operator=(ExposurePriorityVideoControl const&) & noexcept = default;
        ExposurePriorityVideoControl& operator=(ExposurePriorityVideoControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) FlashControl : winrt::Windows::Media::Devices::IFlashControl,
        impl::require<FlashControl, winrt::Windows::Media::Devices::IFlashControl2>
    {
        FlashControl(std::nullptr_t) noexcept {}
        FlashControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IFlashControl(ptr, take_ownership_from_abi) {}
        FlashControl(FlashControl const&) noexcept = default;
        FlashControl(FlashControl&&) noexcept = default;
        FlashControl& operator=(FlashControl const&) & noexcept = default;
        FlashControl& operator=(FlashControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) FocusControl : winrt::Windows::Media::Devices::IFocusControl,
        impl::require<FocusControl, winrt::Windows::Media::Devices::IFocusControl2>
    {
        FocusControl(std::nullptr_t) noexcept {}
        FocusControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IFocusControl(ptr, take_ownership_from_abi) {}
        FocusControl(FocusControl const&) noexcept = default;
        FocusControl(FocusControl&&) noexcept = default;
        FocusControl& operator=(FocusControl const&) & noexcept = default;
        FocusControl& operator=(FocusControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) FocusSettings : winrt::Windows::Media::Devices::IFocusSettings
    {
        FocusSettings(std::nullptr_t) noexcept {}
        FocusSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IFocusSettings(ptr, take_ownership_from_abi) {}
        FocusSettings();
        FocusSettings(FocusSettings const&) noexcept = default;
        FocusSettings(FocusSettings&&) noexcept = default;
        FocusSettings& operator=(FocusSettings const&) & noexcept = default;
        FocusSettings& operator=(FocusSettings&&) & noexcept = default;
    };
    struct __declspec(empty_bases) HdrVideoControl : winrt::Windows::Media::Devices::IHdrVideoControl
    {
        HdrVideoControl(std::nullptr_t) noexcept {}
        HdrVideoControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IHdrVideoControl(ptr, take_ownership_from_abi) {}
        HdrVideoControl(HdrVideoControl const&) noexcept = default;
        HdrVideoControl(HdrVideoControl&&) noexcept = default;
        HdrVideoControl& operator=(HdrVideoControl const&) & noexcept = default;
        HdrVideoControl& operator=(HdrVideoControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) InfraredTorchControl : winrt::Windows::Media::Devices::IInfraredTorchControl
    {
        InfraredTorchControl(std::nullptr_t) noexcept {}
        InfraredTorchControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IInfraredTorchControl(ptr, take_ownership_from_abi) {}
        InfraredTorchControl(InfraredTorchControl const&) noexcept = default;
        InfraredTorchControl(InfraredTorchControl&&) noexcept = default;
        InfraredTorchControl& operator=(InfraredTorchControl const&) & noexcept = default;
        InfraredTorchControl& operator=(InfraredTorchControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) IsoSpeedControl : winrt::Windows::Media::Devices::IIsoSpeedControl,
        impl::require<IsoSpeedControl, winrt::Windows::Media::Devices::IIsoSpeedControl2>
    {
        IsoSpeedControl(std::nullptr_t) noexcept {}
        IsoSpeedControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IIsoSpeedControl(ptr, take_ownership_from_abi) {}
        IsoSpeedControl(IsoSpeedControl const&) noexcept = default;
        IsoSpeedControl(IsoSpeedControl&&) noexcept = default;
        IsoSpeedControl& operator=(IsoSpeedControl const&) & noexcept = default;
        IsoSpeedControl& operator=(IsoSpeedControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LowLagPhotoControl : winrt::Windows::Media::Devices::ILowLagPhotoControl
    {
        LowLagPhotoControl(std::nullptr_t) noexcept {}
        LowLagPhotoControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::ILowLagPhotoControl(ptr, take_ownership_from_abi) {}
        LowLagPhotoControl(LowLagPhotoControl const&) noexcept = default;
        LowLagPhotoControl(LowLagPhotoControl&&) noexcept = default;
        LowLagPhotoControl& operator=(LowLagPhotoControl const&) & noexcept = default;
        LowLagPhotoControl& operator=(LowLagPhotoControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) LowLagPhotoSequenceControl : winrt::Windows::Media::Devices::ILowLagPhotoSequenceControl
    {
        LowLagPhotoSequenceControl(std::nullptr_t) noexcept {}
        LowLagPhotoSequenceControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::ILowLagPhotoSequenceControl(ptr, take_ownership_from_abi) {}
        LowLagPhotoSequenceControl(LowLagPhotoSequenceControl const&) noexcept = default;
        LowLagPhotoSequenceControl(LowLagPhotoSequenceControl&&) noexcept = default;
        LowLagPhotoSequenceControl& operator=(LowLagPhotoSequenceControl const&) & noexcept = default;
        LowLagPhotoSequenceControl& operator=(LowLagPhotoSequenceControl&&) & noexcept = default;
    };
    struct MediaDevice
    {
        MediaDevice() = delete;
        static auto GetAudioCaptureSelector();
        static auto GetAudioRenderSelector();
        static auto GetVideoCaptureSelector();
        static auto GetDefaultAudioCaptureId(winrt::Windows::Media::Devices::AudioDeviceRole const& role);
        static auto GetDefaultAudioRenderId(winrt::Windows::Media::Devices::AudioDeviceRole const& role);
        static auto DefaultAudioCaptureDeviceChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Media::Devices::DefaultAudioCaptureDeviceChangedEventArgs> const& handler);
        using DefaultAudioCaptureDeviceChanged_revoker = impl::factory_event_revoker<winrt::Windows::Media::Devices::IMediaDeviceStatics, &impl::abi_t<winrt::Windows::Media::Devices::IMediaDeviceStatics>::remove_DefaultAudioCaptureDeviceChanged>;
        [[nodiscard]] static DefaultAudioCaptureDeviceChanged_revoker DefaultAudioCaptureDeviceChanged(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Media::Devices::DefaultAudioCaptureDeviceChangedEventArgs> const& handler);
        static auto DefaultAudioCaptureDeviceChanged(winrt::event_token const& cookie);
        static auto DefaultAudioRenderDeviceChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Media::Devices::DefaultAudioRenderDeviceChangedEventArgs> const& handler);
        using DefaultAudioRenderDeviceChanged_revoker = impl::factory_event_revoker<winrt::Windows::Media::Devices::IMediaDeviceStatics, &impl::abi_t<winrt::Windows::Media::Devices::IMediaDeviceStatics>::remove_DefaultAudioRenderDeviceChanged>;
        [[nodiscard]] static DefaultAudioRenderDeviceChanged_revoker DefaultAudioRenderDeviceChanged(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Media::Devices::DefaultAudioRenderDeviceChangedEventArgs> const& handler);
        static auto DefaultAudioRenderDeviceChanged(winrt::event_token const& cookie);
    };
    struct __declspec(empty_bases) MediaDeviceControl : winrt::Windows::Media::Devices::IMediaDeviceControl
    {
        MediaDeviceControl(std::nullptr_t) noexcept {}
        MediaDeviceControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IMediaDeviceControl(ptr, take_ownership_from_abi) {}
        MediaDeviceControl(MediaDeviceControl const&) noexcept = default;
        MediaDeviceControl(MediaDeviceControl&&) noexcept = default;
        MediaDeviceControl& operator=(MediaDeviceControl const&) & noexcept = default;
        MediaDeviceControl& operator=(MediaDeviceControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) MediaDeviceControlCapabilities : winrt::Windows::Media::Devices::IMediaDeviceControlCapabilities
    {
        MediaDeviceControlCapabilities(std::nullptr_t) noexcept {}
        MediaDeviceControlCapabilities(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IMediaDeviceControlCapabilities(ptr, take_ownership_from_abi) {}
        MediaDeviceControlCapabilities(MediaDeviceControlCapabilities const&) noexcept = default;
        MediaDeviceControlCapabilities(MediaDeviceControlCapabilities&&) noexcept = default;
        MediaDeviceControlCapabilities& operator=(MediaDeviceControlCapabilities const&) & noexcept = default;
        MediaDeviceControlCapabilities& operator=(MediaDeviceControlCapabilities&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ModuleCommandResult : winrt::Windows::Media::Devices::IModuleCommandResult
    {
        ModuleCommandResult(std::nullptr_t) noexcept {}
        ModuleCommandResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IModuleCommandResult(ptr, take_ownership_from_abi) {}
        ModuleCommandResult(ModuleCommandResult const&) noexcept = default;
        ModuleCommandResult(ModuleCommandResult&&) noexcept = default;
        ModuleCommandResult& operator=(ModuleCommandResult const&) & noexcept = default;
        ModuleCommandResult& operator=(ModuleCommandResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) OpticalImageStabilizationControl : winrt::Windows::Media::Devices::IOpticalImageStabilizationControl
    {
        OpticalImageStabilizationControl(std::nullptr_t) noexcept {}
        OpticalImageStabilizationControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IOpticalImageStabilizationControl(ptr, take_ownership_from_abi) {}
        OpticalImageStabilizationControl(OpticalImageStabilizationControl const&) noexcept = default;
        OpticalImageStabilizationControl(OpticalImageStabilizationControl&&) noexcept = default;
        OpticalImageStabilizationControl& operator=(OpticalImageStabilizationControl const&) & noexcept = default;
        OpticalImageStabilizationControl& operator=(OpticalImageStabilizationControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PanelBasedOptimizationControl : winrt::Windows::Media::Devices::IPanelBasedOptimizationControl
    {
        PanelBasedOptimizationControl(std::nullptr_t) noexcept {}
        PanelBasedOptimizationControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IPanelBasedOptimizationControl(ptr, take_ownership_from_abi) {}
        PanelBasedOptimizationControl(PanelBasedOptimizationControl const&) noexcept = default;
        PanelBasedOptimizationControl(PanelBasedOptimizationControl&&) noexcept = default;
        PanelBasedOptimizationControl& operator=(PanelBasedOptimizationControl const&) & noexcept = default;
        PanelBasedOptimizationControl& operator=(PanelBasedOptimizationControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) PhotoConfirmationControl : winrt::Windows::Media::Devices::IPhotoConfirmationControl
    {
        PhotoConfirmationControl(std::nullptr_t) noexcept {}
        PhotoConfirmationControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IPhotoConfirmationControl(ptr, take_ownership_from_abi) {}
        PhotoConfirmationControl(PhotoConfirmationControl const&) noexcept = default;
        PhotoConfirmationControl(PhotoConfirmationControl&&) noexcept = default;
        PhotoConfirmationControl& operator=(PhotoConfirmationControl const&) & noexcept = default;
        PhotoConfirmationControl& operator=(PhotoConfirmationControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) RegionOfInterest : winrt::Windows::Media::Devices::IRegionOfInterest,
        impl::require<RegionOfInterest, winrt::Windows::Media::Devices::IRegionOfInterest2>
    {
        RegionOfInterest(std::nullptr_t) noexcept {}
        RegionOfInterest(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IRegionOfInterest(ptr, take_ownership_from_abi) {}
        RegionOfInterest();
        RegionOfInterest(RegionOfInterest const&) noexcept = default;
        RegionOfInterest(RegionOfInterest&&) noexcept = default;
        RegionOfInterest& operator=(RegionOfInterest const&) & noexcept = default;
        RegionOfInterest& operator=(RegionOfInterest&&) & noexcept = default;
    };
    struct __declspec(empty_bases) RegionsOfInterestControl : winrt::Windows::Media::Devices::IRegionsOfInterestControl
    {
        RegionsOfInterestControl(std::nullptr_t) noexcept {}
        RegionsOfInterestControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IRegionsOfInterestControl(ptr, take_ownership_from_abi) {}
        RegionsOfInterestControl(RegionsOfInterestControl const&) noexcept = default;
        RegionsOfInterestControl(RegionsOfInterestControl&&) noexcept = default;
        RegionsOfInterestControl& operator=(RegionsOfInterestControl const&) & noexcept = default;
        RegionsOfInterestControl& operator=(RegionsOfInterestControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) SceneModeControl : winrt::Windows::Media::Devices::ISceneModeControl
    {
        SceneModeControl(std::nullptr_t) noexcept {}
        SceneModeControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::ISceneModeControl(ptr, take_ownership_from_abi) {}
        SceneModeControl(SceneModeControl const&) noexcept = default;
        SceneModeControl(SceneModeControl&&) noexcept = default;
        SceneModeControl& operator=(SceneModeControl const&) & noexcept = default;
        SceneModeControl& operator=(SceneModeControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) TorchControl : winrt::Windows::Media::Devices::ITorchControl
    {
        TorchControl(std::nullptr_t) noexcept {}
        TorchControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::ITorchControl(ptr, take_ownership_from_abi) {}
        TorchControl(TorchControl const&) noexcept = default;
        TorchControl(TorchControl&&) noexcept = default;
        TorchControl& operator=(TorchControl const&) & noexcept = default;
        TorchControl& operator=(TorchControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) VideoDeviceController : winrt::Windows::Media::Devices::IVideoDeviceController,
        impl::require<VideoDeviceController, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController2, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController3, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController4, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController5, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController6, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController7, winrt::Windows::Media::Devices::IAdvancedVideoCaptureDeviceController8>
    {
        VideoDeviceController(std::nullptr_t) noexcept {}
        VideoDeviceController(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IVideoDeviceController(ptr, take_ownership_from_abi) {}
        VideoDeviceController(VideoDeviceController const&) noexcept = default;
        VideoDeviceController(VideoDeviceController&&) noexcept = default;
        VideoDeviceController& operator=(VideoDeviceController const&) & noexcept = default;
        VideoDeviceController& operator=(VideoDeviceController&&) & noexcept = default;
    };
    struct __declspec(empty_bases) VideoDeviceControllerGetDevicePropertyResult : winrt::Windows::Media::Devices::IVideoDeviceControllerGetDevicePropertyResult
    {
        VideoDeviceControllerGetDevicePropertyResult(std::nullptr_t) noexcept {}
        VideoDeviceControllerGetDevicePropertyResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IVideoDeviceControllerGetDevicePropertyResult(ptr, take_ownership_from_abi) {}
        VideoDeviceControllerGetDevicePropertyResult(VideoDeviceControllerGetDevicePropertyResult const&) noexcept = default;
        VideoDeviceControllerGetDevicePropertyResult(VideoDeviceControllerGetDevicePropertyResult&&) noexcept = default;
        VideoDeviceControllerGetDevicePropertyResult& operator=(VideoDeviceControllerGetDevicePropertyResult const&) & noexcept = default;
        VideoDeviceControllerGetDevicePropertyResult& operator=(VideoDeviceControllerGetDevicePropertyResult&&) & noexcept = default;
    };
    struct __declspec(empty_bases) VideoTemporalDenoisingControl : winrt::Windows::Media::Devices::IVideoTemporalDenoisingControl
    {
        VideoTemporalDenoisingControl(std::nullptr_t) noexcept {}
        VideoTemporalDenoisingControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IVideoTemporalDenoisingControl(ptr, take_ownership_from_abi) {}
        VideoTemporalDenoisingControl(VideoTemporalDenoisingControl const&) noexcept = default;
        VideoTemporalDenoisingControl(VideoTemporalDenoisingControl&&) noexcept = default;
        VideoTemporalDenoisingControl& operator=(VideoTemporalDenoisingControl const&) & noexcept = default;
        VideoTemporalDenoisingControl& operator=(VideoTemporalDenoisingControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) WhiteBalanceControl : winrt::Windows::Media::Devices::IWhiteBalanceControl
    {
        WhiteBalanceControl(std::nullptr_t) noexcept {}
        WhiteBalanceControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IWhiteBalanceControl(ptr, take_ownership_from_abi) {}
        WhiteBalanceControl(WhiteBalanceControl const&) noexcept = default;
        WhiteBalanceControl(WhiteBalanceControl&&) noexcept = default;
        WhiteBalanceControl& operator=(WhiteBalanceControl const&) & noexcept = default;
        WhiteBalanceControl& operator=(WhiteBalanceControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ZoomControl : winrt::Windows::Media::Devices::IZoomControl,
        impl::require<ZoomControl, winrt::Windows::Media::Devices::IZoomControl2>
    {
        ZoomControl(std::nullptr_t) noexcept {}
        ZoomControl(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IZoomControl(ptr, take_ownership_from_abi) {}
        ZoomControl(ZoomControl const&) noexcept = default;
        ZoomControl(ZoomControl&&) noexcept = default;
        ZoomControl& operator=(ZoomControl const&) & noexcept = default;
        ZoomControl& operator=(ZoomControl&&) & noexcept = default;
    };
    struct __declspec(empty_bases) ZoomSettings : winrt::Windows::Media::Devices::IZoomSettings
    {
        ZoomSettings(std::nullptr_t) noexcept {}
        ZoomSettings(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Media::Devices::IZoomSettings(ptr, take_ownership_from_abi) {}
        ZoomSettings();
        ZoomSettings(ZoomSettings const&) noexcept = default;
        ZoomSettings(ZoomSettings&&) noexcept = default;
        ZoomSettings& operator=(ZoomSettings const&) & noexcept = default;
        ZoomSettings& operator=(ZoomSettings&&) & noexcept = default;
    };
}
#endif
