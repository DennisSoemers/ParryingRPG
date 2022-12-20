#pragma once

#include <RE/Skyrim.h>

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
    const RE::TESObjectWEAP* const GetAttackWeapon(RE::AIProcess* const aiProcess);
    bool GetWeaponPositions(const RE::Actor* const actor, RE::AIProcess* const aiProcess, const float reach, RE::NiPoint3& outFrom,
                            RE::NiPoint3& outTo);
    bool IsParry(const RE::Actor* const hit_causer, const RE::Actor* const hit_target,
                 RE::AIProcess* const attackerAI, RE::AIProcess* const targetAI,
                 const RE::TESObjectWEAP* attackerWeapon, const RE::TESObjectWEAP* targetWeapon);
    bool IsParryBasicChecks(const RE::Actor* const hit_causer, const RE::Actor* const hit_target);
    bool IsAttacking(const RE::ATTACK_STATE_ENUM state_a);
    float Dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C, const RE::NiPoint3& D);
    RE::NiPoint3 Lerp(const RE::NiPoint3& A, const RE::NiPoint3& B, const float k);
    float Clamp01(const float t);
    RE::NiPoint3 constrainToSegment(const RE::NiPoint3& position, const RE::NiPoint3& a, const RE::NiPoint3& b);
    float dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C);

#pragma warning(pop)
}  // namespace OnMeleeHit