# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added


### Changed


### Fixed



## [0.4.0] - 2025-03-10

### Added

- Added VillageFeatureConstructionEvent @Lovelylavender4
- Added CheckIfItIsAVillageGenerationChunkEvent @Lovelylavender4
- Added PlayerAteEvent @killcerr
- Added dimension name to block event [#12] @zimuya4153
- Added EndermanTakeBlock and EndermanLeaveBlock event [#11] @zimuya4153

### Changed

- Refactored the namespaces of various events @Lovelylavender4
- Refactored event member functions @zimuya4153

### Fixed

- Fixed some event pos deserialization @zimuya4153

## [0.3.1]

### Added

- Added BlockActor, ChestPairWith and BlockActorTick event @zimuya4153

### Changed

- Refactored MoneyChange event @zimuya4153

### Fixed

- Fixed typo in local port for ServerPong event @zimuya4153
- Fixed PlayerDropItem event crash [#10] @zimuya4153


## [0.3.0] - 2025-02-24

### Added

- Adapted to LeviLamina 1.1.0-rc.1 @zimuya4153
- Added FireTryBurnBlock event [#7] @zimuya4153

### Changed

- Removed PlayerChangePermissions event @zimuya4153
- Refactored of RedstoneUpdate events @zimuya4153

### Fixed

- Fixed the serialize and deserialize for PlayerRequestItemAction event @zimuya4153


## [0.2.3] - 2025-01-27

### Added

- Added LeviAntiCheat, PLand mod event @zimuya4153

### Changed

- Reorganized the location of documents for individual events @Lovelylavender4
- Removed LeviLamina version info for ServerPong event @zimuya4153

### Fixed

- Fixed file name spelling errors and function implementation @zimuya4153
- Fixed LiquidTryFlow event cancel destroys block [#9] @zimuya4153

## [0.2.2] - 2025-01-13

### Clanged

- Adapted to LeviLamina 1.0.0-rc.3 and BDS version 1.21.50.10 @zimuya4153

## [0.2.1] - 2025-01-07

### Added

- Added MobHurtEffect event @zimuya4153

### Fixed

- Fixed PistonPush event pos error @zimuya4153
- Fixed file name error @zimuya4153
- Fixed SendPacket event serialize error @zimuya4153

## [0.2.0] - 2025-01-06

### Added

- Adapted to LeviLamina 1.0.0-rc.2 and BDS version 1.21.50 @zimuya4153
- Added registerCmd event @zimuya4153

### Changed

- Refactorred of events @zimuya4153

## [0.1.0] - 2024-12-04

### Added

- Addeded the initial batch of events. @zimuya4153

[#7]: https://github.com/MiracleForest/iListenAttentively-Release/issues/7
[#9]: https://github.com/MiracleForest/iListenAttentively-Release/issues/9
[#10]: https://github.com/MiracleForest/iListenAttentively-Release/issues/10
[#11]: https://github.com/MiracleForest/iListenAttentively-Release/issues/11
[#12]: https://github.com/MiracleForest/iListenAttentively-Release/issues/12

[Unreleased]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.4.0...HEAD
[0.4.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.3.1...v0.4.0
[0.3.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.3...v0.3.0
[0.2.3]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.2...v0.2.3
[0.2.2]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.1...v0.2.2
[0.2.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.0...v0.2.1
[0.2.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/MiracleForest/iListenAttentively-Release/releases/tag/v0.1.0