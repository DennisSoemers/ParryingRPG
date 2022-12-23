#pragma once

#include <RE/Skyrim.h>
#include "Settings.h"

namespace OnMeleeHit {
#pragma warning(push)
#pragma warning(disable : 4251)

    class __declspec(dllexport) OnMeleeHitHook {
    public:
        [[nodiscard]] static OnMeleeHitHook& GetSingleton() noexcept;

        static void InstallHook();

    private:
        OnMeleeHitHook() = default;
        OnMeleeHitHook(const OnMeleeHitHook&) = delete;
        OnMeleeHitHook(OnMeleeHitHook&&) = delete;
        ~OnMeleeHitHook() = default;

        OnMeleeHitHook& operator=(const OnMeleeHitHook&) = delete;
        OnMeleeHitHook& operator=(OnMeleeHitHook&&) = delete;

        /** Our new function */
        static void OnMeleeHit(RE::Actor* attacker, RE::Actor* target, std::int64_t a_int1, bool a_bool,
                               void* a_unkptr);

        /** The original function */
        static inline REL::Relocation<decltype(OnMeleeHit)> _OnMeleeHit;
    };

    // Below here some helper functions
    bool AttackerBeatsParry(RE::Actor* attacker, RE::Actor* target, const RE::TESObjectWEAP* attackerWeapon,
                            const RE::TESObjectWEAP* targetWeapon, RE::AIProcess* const attackerAI,
                            RE::AIProcess* const targetAI);
    double GetScore(RE::Actor* actor, const RE::TESObjectWEAP* weapon,
                    RE::AIProcess* const actorAI, const Settings::Scores& scoreSettings);
    const RE::TESObjectWEAP* const GetAttackWeapon(RE::AIProcess* const aiProcess);
    bool GetWeaponPositions(RE::Actor* actor, RE::AIProcess* const aiProcess, RE::NiPoint3& outFrom,
                            RE::NiPoint3& outTo);
    bool IsParry(RE::Actor* hit_causer, RE::Actor* hit_target,
                 RE::AIProcess* const attackerAI, RE::AIProcess* const targetAI,
                 const RE::TESObjectWEAP* attackerWeapon, const RE::TESObjectWEAP* targetWeapon);
    bool IsParryBasicChecks(const RE::Actor* const hit_causer, const RE::Actor* const hit_target);
    bool IsAttacking(const RE::ATTACK_STATE_ENUM state_a);
    float Dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C, const RE::NiPoint3& D);
    RE::NiPoint3 Lerp(const RE::NiPoint3& A, const RE::NiPoint3& B, const float k);
    float Clamp01(const float t);
    RE::NiPoint3 constrainToSegment(const RE::NiPoint3& position, const RE::NiPoint3& a, const RE::NiPoint3& b);
    float dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C);
    void play_sound(RE::TESObjectREFR* object, int formid);
    float GetReach(RE::Actor* a);
    bool play_impact_1(RE::Actor* actor, const RE::BSFixedString& nodeName);
    bool play_impact_2(RE::TESObjectREFR* a, RE::BGSImpactData* impact, RE::NiPoint3* P_V, RE::NiPoint3* P_from,
                     RE::NiNode* bone);
    bool play_impact_3(RE::TESObjectCELL* cell, float one, const char* model, RE::NiPoint3* P_V, RE::NiPoint3* P_from,
                       float a6, uint32_t _7, RE::NiNode* a8);

    // From: https://github.com/fenix31415/UselessFenixUtils
    template <int id, typename x_Function>
    class _generic_foo_;

    template <int id, typename T, typename... Args>
    class _generic_foo_<id, T(Args...)> {
    public:
        static T eval(Args... args) {
            using func_t = T(Args...);
            REL::Relocation<func_t> func{REL::ID(id)};
            return func(std::forward<Args>(args)...);
        }
    };

#pragma warning(pop)
}  // namespace OnMeleeHit