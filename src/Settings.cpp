#include "Settings.h"

Settings* Settings::GetSingleton() {
    static Settings singleton;
    return std::addressof(singleton);
}

void Settings::Load() {
    constexpr auto path = L"Data/SKSE/Plugins/ParryingRPG.ini";

    CSimpleIniA ini;
    ini.SetUnicode();

    ini.LoadFile(path);

    core.Load(ini);
    scores.Load(ini);

    ini.SaveFile(path);
}

void Settings::Core::Load(CSimpleIniA& a_ini) { 
    static const char* section = "Core";

    detail::get_value(a_ini, useScoreSystem, section, "Use Score System",
                      ";Use the score-based system to allow certain attacks to go through and ignore parries.");
}

void Settings::Scores::Load(CSimpleIniA& a_ini) {
    static const char* section = "Scores";

    detail::get_value(a_ini, scoreDiffThreshold, section, "Score Diff Threshold",
                      ";If the difference in scores is at least equal to this threshold, attacks are not parried.");

    detail::get_value(a_ini, weaponSkillWeight, section, "Weapon Skill Weight",
                      ";Weapon Skill is multiplied by this weight and then added to the score.");

    detail::get_value(a_ini, oneHandDaggerScore, section, "One Hand Dagger Score",
                      ";Bonus score for attacks with daggers.");
    detail::get_value(a_ini, oneHandSwordScore, section, "One Hand Sword Score",
                      ";Bonus score for attacks with one-handed swords.");
    detail::get_value(a_ini, oneHandAxeScore, section, "One Hand Axe Score",
                      ";Bonus score for attacks with one-handed axes.");
    detail::get_value(a_ini, oneHandMaceScore, section, "One Hand Mace Score",
                      ";Bonus score for attacks with one-handed maces.");
    detail::get_value(a_ini, twoHandSwordScore, section, "Two Hand Sword Score",
                      ";Bonus score for attacks with two-handed swords.");
    detail::get_value(a_ini, twoHandAxeScore, section, "Two Hand Axe Score",
                      ";Bonus score for attacks with two-handed axes.");

    detail::get_value(a_ini, altmerScore, section, "Altmer Score",
                      ";Bonus score for Altmer.");
    detail::get_value(a_ini, argonianScore, section, "Argonian Score",
                      ";Bonus score for Argonians.");
    detail::get_value(a_ini, bosmerScore, section, "Bosmer Score",
                      ";Bonus score for Bosmer.");
    detail::get_value(a_ini, dunmerScore, section, "Dunmer Score",
                      ";Bonus score for Dunmer.");
    detail::get_value(a_ini, imperialScore, section, "Imperial Score",
                      ";Bonus score for Imperials.");
    detail::get_value(a_ini, khajiitScore, section, "Khajiit Score",
                      ";Bonus score for Khajiit.");
    detail::get_value(a_ini, nordScore, section, "Nord Score",
                      ";Bonus score for Nords.");
    detail::get_value(a_ini, orcScore, section, "Orc Score",
                      ";Bonus score for Orcs.");
    detail::get_value(a_ini, redguardScore, section, "Redguard Score",
                      ";Bonus score for Redguard.");

    detail::get_value(a_ini, femaleScore, section, "Female Score",
                      ";Bonus score for female characters.");

    detail::get_value(a_ini, powerAttackScore, section, "Power Attack Score",
                      ";Bonus score for power attacks.");
}