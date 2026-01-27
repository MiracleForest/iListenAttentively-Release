# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.11.0] - 2026-01-27

### Added

- Added random color logo on console @zimuya4153
- Added StructureFeatureChunkEvent @Lovelylavender4

### Changed

- Adapted to LeviLamina 1.9.x and bds 1.21.132 @zimuya4153

## [0.10.0] - 2025-11-06

### Changed

- Adapted to LeviLamina 1.7.x and bds 1.21.120 @zimuya4153

### Fixed

- Fixed the ServerPong event [#38] @zimuya4153

## [0.9.0] - 2025-10-21

### Changed

- Adapted to LeviLamina 1.6.x and bds 1.21.110 @zimuya4153 @killcerr

## [0.8.1] - 2025-10-05

### Fixed

- Fixed the LiquidFlow event [#36] @zimuya4153

## [0.8.0] - 2025-10-01

### Added

- Added BiomeDecorationSystemEvent, DecorateEvent, DecorateBiomeEvent, DecorateLargeFeature1Event, DecorateLargeFeature2Event @Lovelylavender4

### Changed

- Adapted to LeviLamina 1.5.1 @zimuya4153
- Removed the PLand mod event @zimuya4153

### Fixed

- Fixed the strange crash [#28] @zimuya4153
- Fixed the suspended reference of the MobHurtEffectBeforeEvent event [#29] @zimuya4153
- Fixed the issue of the ClientLoginAfterEvent event being kicked out of output [#34] @zimuya4153
- Fixed the interception of the LiquidFlowBeforeEvent event [#35] @zimuya4153

## [0.7.0] - 2025-07-15

### Changed

- Adapted to LeviLamina 1.4.0 and bds 1.21.93.1 @zimuya4153

## [0.6.0] - 2025-06-12

### Changed

- Adapted to LeviLamina 1.3.0 and bds 1.21.80.03 @zimuya4153

## [0.5.0] - 2025-06-11

### Changed

- Added ipAndPort info in ServerPongEvent @zimuya4153
- Change ServerNetworkHandler to non-const @zimuya4153
- Refactor SendPacket, ReceivePacket, ClientLogin event @zimuya4153
- Optimize client disconnection handling for ClientLogin event @zimuya4153

### Fixed

- Fixed Hard coding for EndermanTakeBlock event @zimuya4153

## [0.5.0-rc.1] - 2025-05-08

### Changed

- Adapted to LeviLamina 1.2.0-rc.1 and bds 1.21.70 @zimuya4153

## [0.4.2] - 2025-04-24

### Added

- Added ReceivePacket event @zimuya4153
- Added flow from position to LiquidFlow event [#18] @zimuya4153
- Added BlockFall event [#19] @zimuya4153

### Changed

- Changed source deserialize for MobHurtEffectBefore event @zimuya4153
- Reduced header dependencies in event header @zimuya4153

### Fixed

- Fixed deserialize of some events @zimuya4153
- Fixed ActorDestroyBlock event crash @zimuya4153

## [0.4.1] - 2025-04-02

### Added

- Added PlayerChangeSlot event @Lovelylavender4
- Added PlayerCloseContainer event [#15] @zimuya4153
- Added MobHealthChange event [#15] @zimuya4153
- Added LiquidFlow event [#14] @zimuya4153
- Added FireworkRocketDealDamage event [#16] @zimuya4153
- Added PlayerStartSleep and PlayerStopSleep event [#15] @zimuya4153
- Added ActorDestroyBlock event [#17] @zimuya4153

### Changed

- Changed the serialized dimension id in the ActorChangeDimension event to the dimension name @zimuya4153

### Fixed

- Fixed PlayerChangeGameType typo @zimuya4153
- Fixed PlayerRequestItemAction event @zimuya4153
- Fixed MobHurtEffect event source [#13] @killcerr
- Fixed itemActor method for SpawnItemActor event @zimuya4153

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

## [0.3.1] - 2025-03-01

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

### Changed

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
  [#13]: https://github.com/MiracleForest/iListenAttentively-Release/issues/13
  [#14]: https://github.com/MiracleForest/iListenAttentively-Release/issues/14
  [#15]: https://github.com/MiracleForest/iListenAttentively-Release/issues/15
  [#16]: https://github.com/MiracleForest/iListenAttentively-Release/issues/16
  [#17]: https://github.com/MiracleForest/iListenAttentively-Release/issues/17
  [#18]: https://github.com/MiracleForest/iListenAttentively-Release/issues/18
  [#19]: https://github.com/MiracleForest/iListenAttentively-Release/issues/19
  [#28]: https://github.com/MiracleForest/iListenAttentively-Release/issues/28
  [#29]: https://github.com/MiracleForest/iListenAttentively-Release/issues/29
  [#34]: https://github.com/MiracleForest/iListenAttentively-Release/issues/34
  [#35]: https://github.com/MiracleForest/iListenAttentively-Release/issues/35
  [#36]: https://github.com/MiracleForest/iListenAttentively-Release/issues/36
  [#38]: https://github.com/MiracleForest/iListenAttentively-Release/issues/38

  [Unreleased]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.10.0...HEAD
  [0.10.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.9.0...v0.10.0
  [0.9.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.8.1...v0.9.0
  [0.8.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.8.0...v0.8.1
  [0.8.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.7.0...v0.8.0
  [0.7.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.6.0...v0.7.0
  [0.6.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.5.0...v0.6.0
  [0.5.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.5.0-rc.1...v0.5.0
  [0.5.0-rc.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.4.2...v0.5.0-rc.1
  [0.4.2]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.4.1...v0.4.2
  [0.4.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.4.0...v0.4.1
  [0.4.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.3.1...v0.4.0
  [0.3.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.3.0...v0.3.1
  [0.3.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.3...v0.3.0
  [0.2.3]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.2...v0.2.3
  [0.2.2]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.1...v0.2.2
  [0.2.1]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.2.0...v0.2.1
  [0.2.0]: https://github.com/MiracleForest/iListenAttentively-Release/compare/v0.1.0...v0.2.0

[#7]: https://github.com/MiracleForest/iListenAttentively/issues/7
[#9]: https://github.com/MiracleForest/iListenAttentively/issues/9
[#10]: https://github.com/MiracleForest/iListenAttentively/issues/10
[#11]: https://github.com/MiracleForest/iListenAttentively/issues/11
[#12]: https://github.com/MiracleForest/iListenAttentively/issues/12
[#13]: https://github.com/MiracleForest/iListenAttentively/issues/13
[#14]: https://github.com/MiracleForest/iListenAttentively/issues/14
[#15]: https://github.com/MiracleForest/iListenAttentively/issues/15
[#16]: https://github.com/MiracleForest/iListenAttentively/issues/16
[#17]: https://github.com/MiracleForest/iListenAttentively/issues/17
[#18]: https://github.com/MiracleForest/iListenAttentively/issues/18
[#19]: https://github.com/MiracleForest/iListenAttentively/issues/19
[#28]: https://github.com/MiracleForest/iListenAttentively/issues/28
[#29]: https://github.com/MiracleForest/iListenAttentively/issues/29
[#34]: https://github.com/MiracleForest/iListenAttentively/issues/34
[#35]: https://github.com/MiracleForest/iListenAttentively/issues/35
[#36]: https://github.com/MiracleForest/iListenAttentively/issues/36
[#38]: https://github.com/MiracleForest/iListenAttentively/issues/38

[Unreleased]: https://github.com/MiracleForest/iListenAttentively/compare/v0.11.0...HEAD
[0.11.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.10.0...v0.11.0
[0.10.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.9.0...v0.10.0
[0.9.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.8.1...v0.9.0
[0.8.1]: https://github.com/MiracleForest/iListenAttentively/compare/v0.8.0...v0.8.1
[0.8.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.7.0...v0.8.0
[0.7.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.6.0...v0.7.0
[0.6.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.5.0...v0.6.0
[0.5.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.5.0-rc.1...v0.5.0
[0.5.0-rc.1]: https://github.com/MiracleForest/iListenAttentively/compare/v0.4.2...v0.5.0-rc.1
[0.4.2]: https://github.com/MiracleForest/iListenAttentively/compare/v0.4.1...v0.4.2
[0.4.1]: https://github.com/MiracleForest/iListenAttentively/compare/v0.4.0...v0.4.1
[0.4.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.3.1...v0.4.0
[0.3.1]: https://github.com/MiracleForest/iListenAttentively/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.2.3...v0.3.0
[0.2.3]: https://github.com/MiracleForest/iListenAttentively/compare/v0.2.2...v0.2.3
[0.2.2]: https://github.com/MiracleForest/iListenAttentively/compare/v0.2.1...v0.2.2
[0.2.1]: https://github.com/MiracleForest/iListenAttentively/compare/v0.2.0...v0.2.1
[0.2.0]: https://github.com/MiracleForest/iListenAttentively/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/MiracleForest/iListenAttentively/releases/tag/v0.1.0
