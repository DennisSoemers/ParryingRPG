#include <SKSE/SKSE.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "OnMeleeHit.h"

using namespace OnMeleeHit;

OnMeleeHitHook& OnMeleeHitHook::GetSingleton() noexcept {
    static OnMeleeHitHook instance;
    return instance;
}

void OnMeleeHitHook::InstallHook() {
    // Taken from: https://github.com/doodlum/MaxsuWeaponSwingParry-ng/blob/main/src/WeaponParry_Hooks.h
    // (with permission from doodlum and Maxsu)
    SKSE::AllocTrampoline(1 << 4);

    REL::Relocation<std::uintptr_t> OnMeleeHitBase{REL::RelocationID(37650, 38603)};
    auto& trampoline = SKSE::GetTrampoline();
    _OnMeleeHit = trampoline.write_call<5>(OnMeleeHitBase.address() + REL::Relocate(0x38B, 0x45A), OnMeleeHit);
}

void OnMeleeHitHook::OnMeleeHit(RE::Actor* hit_causer, RE::Actor* hit_target, std::int64_t a_int1, bool a_bool,
                                void* a_unkptr) {

    // Code here is a mix of Fenix31415's, Maxsu's / doodlum's, and my own
    if (hit_causer && hit_target) {
        if (OnMeleeHit::IsParry(hit_causer, hit_target)) {
            // TODO do the parry

            // We'll want to skip the normal game's code for this hit
            return;
        }
    }

    // Call the normal game's code
    _OnMeleeHit(hit_causer, hit_target, a_int1, a_bool, a_unkptr);
}

bool OnMeleeHit::IsParry(const RE::Actor* const hit_causer, const RE::Actor* const hit_target) {
    // First some sanity checks
    if (!hit_causer->Is3DLoaded() || !hit_target->Is3DLoaded()) {
        return false;
    }

    if (hit_causer->formType != RE::FormType::ActorCharacter || hit_target->formType != RE::FormType::ActorCharacter) {
        return false;
    }

    if (hit_causer->IsDead() || hit_target->IsDead()) {
        return false;
    }

    if (!IsAttacking(hit_target->AsActorState()->GetAttackState())) {
        // Target must be attacking. No need to check really for the hit causer because,
        // if our code is running at all, the hit causer must surely indeed be attacking.
        return false;
    }

    RE::AIProcess* const attackerAI = hit_causer->GetActorRuntimeData().currentProcess;
    RE::AIProcess* const targetAI = hit_target->GetActorRuntimeData().currentProcess;
    if (!attackerAI || !targetAI) {
        return false;
    }

    // Now looking at the weapons used
    auto attackerWeapon = GetAttackWeapon(attackerAI);
    auto targetWeapon = GetAttackWeapon(targetAI);

    if (attackerWeapon && targetWeapon) {
        if (attackerWeapon->IsMelee() && targetWeapon->IsMelee() && !attackerWeapon->IsHandToHandMelee() &&
            !targetWeapon->IsHandToHandMelee()) {
            // Make sure that actors are facing each other
            auto angle = abs(hit_causer->GetHeading(true) - hit_target->GetHeading(true));
            if (angle > M_PI) {
                angle = 2.0 * M_PI - angle;
            }

            if (angle > M_PI * 0.75) {
                // Make sure that the weapons are close together
                RE::NiPoint3 attacker_from, attacker_to, victim_from, victim_to;

                if (!GetWeaponPositions(hit_causer, attackerAI, attackerWeapon->GetReach(), attacker_from,
                                        attacker_to)) {
                    return false;
                }

                if (!GetWeaponPositions(hit_target, targetAI, targetWeapon->GetReach(), victim_from, victim_to)) {
                    return false;
                }

                const float d = Dist(attacker_from, attacker_to, victim_from, victim_to);
                return d <= 120.0f;
            }
        }
    }

    return false;
}

const RE::TESObjectWEAP* const OnMeleeHit::GetAttackWeapon(RE::AIProcess* const aiProcess) {
    if (aiProcess && aiProcess->high && aiProcess->high->attackData &&
        !aiProcess->high->attackData->data.flags.all(RE::AttackData::AttackFlag::kBashAttack)) {
        
        const RE::TESForm* equipped = aiProcess->high->attackData->IsLeftAttack() ? aiProcess->GetEquippedLeftHand()
                                                                                  : aiProcess->GetEquippedRightHand();

        if (equipped) {
            return equipped->As<RE::TESObjectWEAP>();
        }
    }

    return nullptr;
}

bool OnMeleeHit::GetWeaponPositions(const RE::Actor* const actor, RE::AIProcess* const aiProcess, const float reach,
                                    RE::NiPoint3& outFrom, RE::NiPoint3& outTo) {
    const auto nodeName = (aiProcess->high->attackData->IsLeftAttack()) ? "SHIELD"sv : "WEAPON"sv;
    const auto root = netimmerse_cast<RE::BSFadeNode*>(actor->Get3D());
    if (!root) 
        return false;
    const auto bone = netimmerse_cast<RE::NiNode*>(root->GetObjectByName(nodeName));
    if (!bone) 
        return false;
    outFrom = bone->world.translate;
    const auto weaponDirection =
        RE::NiPoint3{bone->world.rotate.entry[0][1], bone->world.rotate.entry[1][1], bone->world.rotate.entry[2][1]};
    outTo = outFrom + weaponDirection * reach;
    return true;
}

bool OnMeleeHit::IsAttacking(const RE::ATTACK_STATE_ENUM attackState) {
    return attackState == RE::ATTACK_STATE_ENUM::kHit || attackState == RE::ATTACK_STATE_ENUM::kSwing;
}

float OnMeleeHit::Dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C, const RE::NiPoint3& D) {
    const auto CD = D - C;
    float CD2 = CD * CD;
    auto inPlaneA = A - (CD * (CD * (A - C) / CD2));
    auto inPlaneB = B - (CD * (CD * (B - C) / CD2));
    auto inPlaneBA = inPlaneB - inPlaneA;
    const float inPlaneBA2 = inPlaneBA * inPlaneBA;
    float t;
    if (inPlaneBA2 < 0.00005f)
        t = 0.0f;
    else
        t = inPlaneBA * (C - inPlaneA) / inPlaneBA2;
    auto segABtoLineCD = Lerp(A, B, Clamp01(t));

    return dist(A, B, constrainToSegment(segABtoLineCD, C, D));
}

RE::NiPoint3 OnMeleeHit::Lerp(const RE::NiPoint3& A, const RE::NiPoint3& B, const float k) 
{
    return A + (B - A) * k; 
}

float OnMeleeHit::Clamp01(const float t) 
{ 
    return std::max(0.0f, std::min(1.0f, t)); 
}

RE::NiPoint3 OnMeleeHit::constrainToSegment(const RE::NiPoint3& position, const RE::NiPoint3& a,
                                            const RE::NiPoint3& b) {
    auto ba = b - a;
    auto t = ba * (position - a) / (ba * ba);
    return Lerp(a, b, Clamp01(t));
}

float OnMeleeHit::dist(const RE::NiPoint3& A, const RE::NiPoint3& B, const RE::NiPoint3& C) {
    return constrainToSegment(C, A, B).GetDistance(C);
}