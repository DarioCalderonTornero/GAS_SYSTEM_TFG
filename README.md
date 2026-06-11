# ⚔️ GAS Prototype — Unreal Engine 5

> A solo technical demo built in Unreal Engine 5 as a Bachelor's Thesis project, focused on designing and implementing a fully functional, modular and scalable ability system using the Gameplay Ability System (GAS) framework from C++.

![Engine](https://img.shields.io/badge/Engine-Unreal%20Engine%205-black?logo=unrealengine)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Language](https://img.shields.io/badge/Language-Blueprints-orange)
![Type](https://img.shields.io/badge/Type-Technical%20Demo-purple)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Solo](https://img.shields.io/badge/Team-Solo%20Project-lightgrey)

---

## 🎓 Academic Context

This project was developed as a **Bachelor's Thesis (TFG)** at Florida Universitària, degree in Videogame Design and Development.

- **Author:** Darío Calderón Tornero
- **Tutor:** Miguel Fernández-Montañés Domingo
- **Engine:** Unreal Engine 5.6.1
- **IDE:** JetBrains Rider 2025.3.0.3

📄 [Read the full thesis document](YOUR_THESIS_LINK)
🎬 [Watch the cinematic trailer](YOUR_TRAILER_LINK)

---

## 🎮 Overview

**GAS Prototype** is a playable technical demo that demonstrates a correct, structured and scalable implementation of the **Gameplay Ability System** in Unreal Engine 5. The focus is not on building a complete commercial game, but on constructing a solid gameplay architecture where every system has a clear responsibility and communicates with the rest without direct dependencies.

The project proves that GAS, when correctly structured from C++, enables full reusability between different character types — both the player and the enemy share the exact same architectural base without duplicating any logic.

---

## 🏗️ Architecture Overview

The entire base architecture is built in **C++**, establishing a solid foundation that Blueprints extend without compromising its integrity.

### Core C++ Classes

| Class | Responsibility |
|-------|----------------|
| `AGameCharacterBase` | Shared base for player and enemy. Initializes ASC, AttributeSet, and centralizes ability granting/revoking |
| `UExtendedAbilitySystemComponent` | Custom ASC extension. Detects relevant ability set changes and notifies the character to update the UI |
| `UBasicAttributeSet` | Centralizes all attributes (Health, Stamina, Shield) and the full damage pipeline via `PostGameplayEffectExecute` |
| `UMyPlayerGameplayAbility` | Base class for all abilities. Configures shared tags, death blocking, UI visibility flag, and player/enemy detection |

### Key Architectural Decisions

- **ASC on the Character** — Simplified setup appropriate for a single-player prototype without respawn requirements
- **Single centralised AttributeSet** — Health, MaxHealth, Stamina, MaxStamina, Shield, MaxShield and the Damage Meta Attribute in one place
- **Ability granting centralised in C++** — `GrantAbilities` and `RemoveAbilities` in `AGameCharacterBase`, returning `FGameplayAbilitySpecHandle` arrays for precise revocation
- **Hybrid C++ / Blueprint approach** — Structural logic in C++, ability behaviour and UI in Blueprints, following Epic's recommended workflow

---

## ⚔️ Implemented Abilities

| Ability | Type | Activation | Key Pattern |
|---------|------|------------|-------------|
| `GA_Dash` | Movement | Input Event | CommitCost + Root Motion + GameplayCue |
| `GA_MeleeAttack_AxeSwing` | Melee Attack | Input Event | AnimNotify → WaitGameplayEvent + HitScan |
| `GA_MeleeAttack_AxeCombo` | Melee Attack | Input Event | 3-level Blueprint inheritance + auto-combo for enemy |
| `GA_ShootProjectile_Base` | Ranged Attack | Input Event | Event + projectile spawn |
| `GA_AOEAttack` | Area Attack | Input Event | Bifurcated targeting + GameplayCue with parameters |
| `GA_Defense_Shield` | Defensive | Input Event | AnimNotify → Event + GE with CurveTable |
| `GA_EquipWeapon` | System | Input Event | Dynamic ability granting/revoking via WeaponsManagerComponent |
| `GA_HitReaction` | System | Internal (AttributeSet) | Activated by tag from damage pipeline |
| `GA_Death` | System | Internal (AttributeSet) | Activated when Health reaches zero |

---

## 🔥 Damage Pipeline

A complete centralised damage pipeline processes every hit before applying it to real attributes:

1. **Ability** builds a `GameplayEffectSpec` and assigns damage via `SetByCallerMagnitude` with tag `Data.Damage`
2. **MMC** (`DamageGameplayModMagnitudeCalculation`) intercepts the calculation — halves damage if target has `Status.Buff.Immunity`
3. **`PostGameplayEffectExecute`** in `UBasicAttributeSet` reads the Damage Meta Attribute, resets it immediately, and applies shield absorption logic before reducing Health
4. **Gameplay Cue** (`GameplayCue.Damage.Burst`) fires automatically from the GE asset — VFX and sound without any ability-side logic
5. **HitReaction** activates automatically via tag if the GE has `Effect.HitReaction` and damage was greater than zero
6. **Death** triggers automatically when Health reaches zero, applying `GE_Death` which adds `State.Death` tag — blocking all abilities instantly

---

## 🖥️ Reactive UI System

The UI never polls the system. It reacts to changes pushed by the ASC.

| Widget | Responsibility |
|--------|----------------|
| `W_PlayerHUD` | Root container and orchestrator |
| `W_PlayerVitals` | Reactive Health and Stamina bars via `WaitForAttributeChanged` |
| `W_AbilityBar` + `W_AbilitiesContainer` | Dynamically rebuilds ability slots when `Event.Abilities.Changed` fires |
| `W_Ability` | Individual slot: icon via DataTable lookup, cooldown timer, activation highlight |
| `W_EnemyAvatar` | Enemy UI root, instanced per enemy actor above their head |
| `W_EnemyHealthBar` + `W_EnemyArmorBar` | Reactive enemy Health and Shield bars |

**Key patterns:**
- `WaitForAttributeChanged` — Attribute bindings without polling
- `Event.Abilities.Changed` — UI rebuilds only when the ability set actually changes
- `DT_AbilityMetadata` DataTable — Icon resolution fully decoupled from ability logic
- Cooldown loop timer — Active only during cooldown, no per-frame cost when idle

---

## 🏷️ Gameplay Tags Structure

```
GameplayAbility.
    ├── Active          — Added to ASC while any ability is active
    ├── Death           — Activates GA_Death
    ├── HitReaction     — Activates GA_HitReaction
    └── [ability tags]  — Unique tag per ability

State.
    ├── Death           — Blocks all abilities when present
    └── Buff.Immunity   — Halves incoming damage via MMC

Data.
    └── Damage          — SetByCaller channel for damage magnitude

Effect.
    └── HitReaction     — Marks GEs that should trigger hit reaction

Event.
    └── Abilities.Changed — Notifies UI to rebuild ability bar

GameplayCue.
    ├── Damage.Burst    — Impact VFX and sound
    └── AOE.*           — Area attack visual indicators
```

---

## 🤖 Enemy System

The enemy shares the exact same `AGameCharacterBase` architecture as the player:

- Own `UExtendedAbilitySystemComponent` and `UBasicAttributeSet`
- Can equip weapons and execute abilities with automatic targeting via `BPI_Target` interface
- `HasPlayerController()` utility in `UMyPlayerGameplayAbility` allows abilities to bifurcate behaviour between player and enemy without separate classes
- Example: `GA_MeleeAttack_AxeCombo` sets `OverrideContinueCombo = !HasPlayerController()` — auto-continues for enemy, requires input for player

---

## 🧠 Technical Highlights

- **AnimNotify → WaitGameplayEvent** — All offensive abilities synchronise with animation frames, fully decoupled from timing
- **SetByCaller** — Single damage GE asset reused by all offensive abilities with different runtime magnitudes
- **HitActorArray** — Anti-duplicate filter for volume-based hit detection (melee HitScan and AOE SphereTrace)
- **Blueprint 3-level inheritance** — `GA_MeleeAttack_Base` → `GA_MeleeAttack_AxeSwing` → `GA_MeleeAttack_AxeCombo`
- **GA_EquipWeapon as a Gameplay Ability** — Equipping a weapon uses GAS infrastructure: cooldown, death blocking, AnimNotify sync, dynamic ability granting
- **CurveTable in GE** — Shield ability scales with character level without creating multiple effect assets
- **DelayUntilNextTick** in UI — Prevents layout inconsistencies when rebuilding widget hierarchies

---

## 🛠️ Tech Stack

| Category | Technology |
|----------|------------|
| Engine | Unreal Engine 5.6.1 |
| Language | C++ + Blueprints |
| IDE | JetBrains Rider |
| Framework | Gameplay Ability System (GAS) |
| UI | UMG (Unreal Motion Graphics) |
| Camera | Unreal Camera System |
| VFX | Niagara + Gameplay Cues |
| Animation | Animation Montages + AnimNotifies |
| Data | DataTables + CurveTables |

---

## 📸 Screenshots

<!-- Add screenshots or GIFs here -->
> *See the cinematic trailer for a full showcase of the system in action.*

---

## 📄 License

This project is not open source. All rights reserved.
