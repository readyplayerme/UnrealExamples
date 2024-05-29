# Changelog

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

## [3.2.0] 2024-05-23

## Updated

- updated to latest version of glTFRuntime [#65](https://github.com/readyplayerme/rpm-unreal-sdk/pull/65)

## Fixed

- removed UE5.4 warnings [#66](https://github.com/readyplayerme/rpm-unreal-sdk/pull/66)
- fixed a crash caused by unmanaged avatar request callbacks in Avatar Creator [#67](https://github.com/readyplayerme/rpm-unreal-sdk/pull/67)

## [3.1.0] 2024-05-08

## Added

- gltfRuntime is merged now to the Ready Player Me Plugin and it is no longer needed to download it manually [#55](https://github.com/readyplayerme/rpm-unreal-sdk/pull/55)

## Fixed
- resize image based on camera resolution [#61](https://github.com/readyplayerme/rpm-unreal-sdk/pull/61)
- Fix setup guide path [#60](https://github.com/readyplayerme/rpm-unreal-sdk/pull/60)
- Fix typos in quickstart [#62](https://github.com/readyplayerme/rpm-unreal-sdk/pull/62)
- Dont show halfbody/fullbody-xr animations in quickstart [#63](https://github.com/readyplayerme/rpm-unreal-sdk/pull/63)

## Breaking

- gltfRuntime is now part of the SDK, so the separate version of gltfRuntime from the plugins folder needs to be removed [#55](https://github.com/readyplayerme/rpm-unreal-sdk/pull/55)

## [2.4.0] 2024-02-19

## Added

- Add rpm source header to requests by @rk132 in [#56](https://github.com/readyplayerme/rpm-unreal-sdk/pull/56)

## [2.3.0] 2024-01-24

## Fixed

- Fixed assetID type issue in the AvatarCreator by @harrisonhough in [#54](https://github.com/readyplayerme/rpm-unreal-sdk/pull/54)

## [2.2.0] 2024-01-12

## Added

- Added support for auto LODs for the avatars in [#52](https://github.com/readyplayerme/rpm-unreal-sdk/pull/52)

## Fixed

- Fixed root motion issue in the IK Retargeters
- Avatar Creator UI fixes

## [2.1.0] 2023-11-20

## Breaking

- Moved ReadyPlayerMeSettings.EnableAvatarCaching project property to ReadyPlayerMeSettings.AvatarCacheSettings.EnableAvatarCaching.
- Removed Preload function from UReadyPlayerMeMemoryCache class. Use the PreloadAvatarsAsync sync node instead.
- Removed bUseMemoryCache property from the ReadyPlayerMeComponent
- Renamed ClearAvatar function to ClearAvatarFromCache
- Renamed GetCacheSize function to GetAvatarCacheSize
- Renamed GetAvatarCount function to GetCachedAvatarCount
- Renamed GetAvatarGuid function to GetAvatarId

## Added

- Added AvatarCacheSettings property in the project settings and moved the EnableAvatarCaching property inside of it.
- Added EnableAutomaticCacheCleaning and CachedAvatarLimit properties in AvatarCacheSettings. These properties enable the automatic cache management.
- Added PreloadAvatarsAsync sync node to make avatar preloading easy to use.
- Added ClearAvatarsFromMemory and ClearAvatarFromMemory functions. These functions clear preloaded avatars from the memory.
- Added bKeepLoadedAvatarsInMemory property in the project settings. This property allows to keep all the loaded avatars in the memory without preloading them.

## Updated

- Moved ReadyPlayerMeSettings.EnableAvatarCaching project property to ReadyPlayerMeSettings.AvatarCacheSettings.EnableAvatarCaching.
- Removed bUseMemoryCache property from the ReadyPlayerMeComponent
- Renamed ClearAvatar function to ClearAvatarFromCache
- Renamed GetCacheSize function to GetAvatarCacheSize
- Renamed GetAvatarCount function to GetCachedAvatarCount
- Renamed GetAvatarGuid function to GetAvatarId
- Set the PhysicsAssetOverride property in the BP_RPM_Character to fix the shadow issues in UE5
- UI fixes in AvatarCreator
- Changed the background material of the avatar editor

## Removed

- Removed bUseMemoryCache property from the ReadyPlayerMeComponent
- Removed Preload function from UReadyPlayerMeMemoryCache class. Use the PreloadAvatarsAsync sync node instead.
- Broken blueprints in the Data folders

## [2.0.0] 2023-11-01

## Breaking

- Removed complicated MorphTargetGroups data assets.
  For fixing the existing custom morph target groups, open your custom avatar config and add the needed morph targets there.
- AvatarCreator plugin is merged with the ReadyPlayerMe SDK.
  The existing integrations of the avatar creator need to be added again, because the references in the blueprints would be broken.
- Removed the ReadyPlayerMeActor redundant class. If you used BP_RPM_Actor blueprint class, use BP_RPM_SimpleActor blueprint class instead. 

## Added

- Merged the AvatarCreator plugin with the ReadyPlayerMe SDK.
- Added App Id to setup guide.
- Added AvatarCreator to the QuickStart map

## Removed

- Removed complicated MorphTargetGroups data assets.
- Removed the ReadyPlayerMeActor redundant class.

## [1.4.4] 2023-10-09

## Fixed

- Fixed the finger glitching issue for the loaded avatars.

## [1.4.3] 2023-10-02

## Fixed

- Default Config file saving issues in the editor module.

## [1.4.2] 2023-09-27

## Added

- Added avatar rigs zip file to the resources. It contains IK rig, IK retargeter and basic foot IK control rig.

## [1.4.1] 2023-09-19

## Fixed

- Fixed subdomain saving in the setup guide

## [1.4.0] 2023-09-12

## Added

- Setup guide, it will be show when the sdk is integrated
- Subdomain in the project settings
- UE5.3 support
- Logic to automatically add glTFRuntime to the Additional assets to cook

## Fixed

- Fixed rendering issues in QuickStart map

## [1.3.0] 2023-09-01

## Breaking

- Renamed meshLod property with Lod in avatar config

## Fixed

- Quickstart map rendering issue
- Fixed Request cancellation issue in UE5.2

## Updated

- Analytics for AppId and AvatarCreator version

## [1.2.0] 2023-08-17

## Added

- QuickStart map with character controller to showcase avatar usage
- Added meshOpt param to the avatar config. Currently it only works when texture atlas is enabled
- AppId in the project settings

## Fixed

- Replaced meshLod property with lod

## Removed

- Existing demo map

## [1.1.1] 2023-06-21

## Added

- SkinTone parameter in metadata

## Fixed

- Added missing includes for UE5.2

## [1.1.0] 2023-04-17

## Update

- Blueprint versions of the plugins are build with VS2022

## Fixed

- Avatar caching logic when the user changes the timezone.
- Submodule setup script in the readme.

## [1.0.0] 2023-02-21

## Added

- Open source the sdk
- Load the avatar from the cache if the avatar request fails
- BlendShape support for the RenderLoader
- Female avatar FBX file into the `RPM_Avatar_Reference.zip`
- MemoryCache for preloading and saving the avatars in the runtime memory

## Updated

SDK setup should be done through the open-source GitHub repository.

## Breaking Changes

- `FAvatarDownloadCompleted` delegate now uses USkeletalMesh instead of UglTFRuntimeAsset.
- `ReadyPlayerMeComponent::LoadRender` function was removed. Use `ReadyPlayerMeRenderLoader::Load` function instead.
- `FDownloadImageCompleted` delegate now uses UTexture2D instead of UTexture.

## [0.19.0] 2022-11-30

## Added

- Access to the skeletal mesh config for material customization 
- Runtime animation retargeting support
- Editor widget for exporting skeletal mesh without materials
- Support for Draco mesh compression

## Fixed

- Updated glTFRuntime plugin to the version 20220823 to support UE5.1
- Added missing ARKit morph targets to the avatar config
- Changed the render request functionality to use avatar-api
- Removed the Viseme and ARKit morph targets from DA_StandardMorphTargets

## [0.18.1] 2022-10-07

## Fixed

- Updated glTFRuntime plugin to the version 20220823

## [0.18.0] 2022-09-28

## Added

- Avatar API configuration parameter support
- Success callback for ReadyPlayerMeComponent
- Avatar Loading cancellation

## Fixed

- Avatar caching support for Avatar API

## [0.17.1] 2022-09-01

## Fixed

- reverted short code base URL change
- logic for device ID to fix developer metrics

## [0.17.0] 2022-08-23

## Added

- 2D avatar rendering using Render API
- Avatar caching (experimental)
- Fully optional SDK-analytics

## Changed

- Big refactor and reorganization of previous C++ classes
- Avatar requests both, avatar metadata and glb in parallel to reduce wait time

## [0.16.0] 2022-05-05

## Fixed

- UE5 android (Quest) build issues caused by glTFRuntime

## Changed

- updated to latest version of glTFRuntime

## [0.15.1] 2022-04-12

## Fixed

- reverted model forward axis update to fix retargeting issues

## [0.15.0] 2022-04-08

## Changed

- updated glTFRuntime for latest changes and UE5 support
- avatars now spawn with X axis forward to match Unreal standard
- reference avatar UAssets also updated to reflect forward axis change

## [0.14.0] 2022-21-03

## Added

- Halfbody avatar reference mesh, textures and skeleton
- RPM actor for loading halfbody in RPM_Demo map

## Changed

- added support for setting skeleton when loading halfbody avatars

## [0.13.0] 2022-03-16

## Changed

- Plugin folder restructure
- Updated reference avatar and added textures
- separate BP_RPM_Component blueprint removed, now BP_RPM_Actor has a ReadyPlayerMeComponent
- removed functionality for runtime setting of animation blueprints, now it must be set in editor before running application
- removed unnecessary parameters from avatar loading helper functions

## Added

- New ReadyPlayerMeActor base class that adds required components on construction

# Fixed

- issue where animation wasn't being played in builds

## [0.12.1] 2022-02-16

## Added

- added bonemapping for humanoid skeleton

## Changed

- updated gltfRuntime fork with updates for duplicate morph target names
- enabled import morph targets on RPM_Mixamo_SkeletalMesh

## [0.12.0] 2022-02-02

## Changed

- updated glTFRuntime fork to get latest changes
- plugin config and code updates to allow for plugin packaging for BP Only projects
- RPM skeleton's retargeting settings

## Fixed

- updated skeleton retargeting for eye position issues
- conversion issues when building for Linux
- syntax errors preventing UE5 compatibility

## [0.11.0] 2022-01-11

## Added

- Ready Player Me Actor component

## Changed

- refactored ReadyPlayerMeunctionLibrary
- separated common variables into separate header

## [0.10.2] 2021-10-22

## Fixed

- updated glTFRuntime version to fix build errors

## [0.10.1] 2021-10-12

## Fixed

- error in LoadAvatarMetaData preventing the project from compiling

## [0.10.0] 2021-10-12

## Added

- basic shortcode URL validation

## Changed

- updated fullbody reference skeleton mesh and BP

## Removed

- support for old avatars with V1 skeleton

## Fixed

- errors from invalid shortcode URL's for fullbody avatars

## [0.9.0] 2021-9-10

## Fixed

- updated glTFRuntime fork with latest updates to support unreal 4.27

## [0.8.1] 2021-08-19

## Fixed

- issue with regex on different build platforms

## [0.8.0] 2021-08-03

## Changed

- general cleanup and bugfixes
- added support for shortcodes

## [0.7.0] 2021-06-09

## Changed

- bug fixes for loading VR avatar meta data
- code cleanup
- simplified example blueprints

## Added

- check for missing meta data fields and morph targets

## [0.6.0] 2021-05-19

## Changed

- removed glTFRuntime plugin and readded as forked submobule

## Added

- temporary workaround for morph targets naming clash
- include headers to ReadyPlayerMeFunctionLibrary.cpp to fix android build errors

## [0.5.0] 2021-05-04

## Changed

- avatar loading logic
- updated reference avatar fbx

## Added

- support for V2 rigged avatars
- loading generated json metadata

## [0.4.0] 2021-04-11

## Changed

- Updated reference animation skeleton
- Reworked scale logic to work with downloaded animations
- changed mesh bounds scale

## Added

- scale logic for half body

## [0.3.0] 2021-04-08

## Changed

- Skeletal mesh loading now using async

## [0.2.0] 2021-03-11

## Changed

- Added license file and readme
- Minor cleanup and refactoring
- Project name and details

## [0.1.0] 2021-03-05

## Added

- Unreal project and setup files
- glTFRuntime plugin
- Blueprint function library
- example scene
- reference rpm character and animation targets
- Demo map example scene
