# Changelog

All notable changes to this project will be documented in this file.
This project adheres to [Semantic Versioning](http://semver.org/).

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
