# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Fixed
- Fixed HasComponent conditional not returning any error when no component class is configured
- Fixed debug trace not formatting in error string
- Fixed MultiCombine conditional not calculating correct Percintile fuzzy answer
- Fixed crash potential in UConditional::ForThisAndEachChildrenDo
- Fixed crash potential in FConditionalEvaluationContext::GetWorld()
- Fixed crash potential in BP function library when actor can't be retrieved from evaluation context
- Fixed MultiCombine yielding true binary answer in OR mode with only false-answering children
- Fixed MultiCombine conditional tests where fuzzy answer is 0.5 and not 0 or 1
- Added second mock error answer that is used in conditional answer spec
- Fixed tests for transform based conditionals where tested actor was missing a root scene component
- Fixed ActorIsTicking conditional test missing setting actor tick to be allowed
- Added initialization to FConditionalEvaluationContext::OptionalDebugTrace
- Fixed crash potential in evaluation context when actor owner is null
- Fixed tests that failed due to conditional error being NoActorProvider instead of NoActor
- Fixed crash in IsOfClass conditional when no class is configured
- Fixed answer comparison yielding equality though error messages differ

## [2.1.0] - 2026-05-18
### Changed
- Improved editor UX of conditionals that allow children
- Renamed a few `FConditionalDebugTrace` members
### Fixed
- Fixed missing SF:: prefix in Readme

## [2.0.0] - 2026-05-16
### Changed
- Moved all types to the SF namespace and removed their SF prefix
### Added
- Added object context to selected runtime error constructors, so it's
easier to understand if a specific object causes the issue
- Implemented that conditionals with children answer with the new 
`HasChildWithRuntimeError` when any child answers with error

## [1.0.0] - 2026-02-21
### Added
- Added SFConditional
- Added SFConditionalAnswer
- Added SFConditionalDebugTrace
- Added SFConditionalEvaluationContext
- Added Conditional Types
  - Actor - Has Component
  - Actor - Is Ticking
  - Area - Screen Box
  - Area - World Distance Radius
  - Logic - Not
  - Logic - And
  - Logic - Or
  - Logic - Multi Combine
  - Object - Is Of Class
