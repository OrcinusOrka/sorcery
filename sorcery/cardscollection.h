#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include "enchantment.h"

//effects
const Effect effect_none = {Ability::None, Trigger::None, Target::Yes, 0, 0, 0, "", "", false};
const Effect effect_FireElemental_1 = {Ability::AtkDef, Trigger::OppoentSummon, Target::Yes, 0, -1, 0,
                                       "Whenever an opponent's minion enters play, deal 1 damage to it.",
                                       "", false};
const Effect effect_PotionSeller_1 = {Ability::AtkDef, Trigger::OwnEnd, Target::No, 0, 1, 0,
                                      "At the end of your turn, all your minions gain +0/+1.",
                                      "", false};
const Effect effect_NovicePyromancer_1 = {Ability::AtkDef, Trigger::None, Target::Yes, 0, -1, 1,
                                          "Deal 1 damage to target minion", "", false};
const Effect effect_ApprenticeSummoner_1 = {Ability::Summon, Trigger::None, Target::Yes, 1, 0, 1,
                                            "Summon a 1/1 air elemental","Air Elemental", false};
const Effect effect_MasterSummoner_1 = {Ability::Summon, Trigger::None, Target::No, 3, 0, 2,
                                        "Summon up to three 1/1 air elementals",
                                        "Air Elemental", false};
const Effect effect_Banish_1 = {Ability::Destory, Trigger::None, Target::Yes, 0, 0, 2,
                                "Destory target minion or ritual", "", false};
const Effect effect_Unsummon_1 = {Ability::Unsummon, Trigger::None, Target::Yes, 0, 0, 1,
                                  "Return target minion to its owner's hand", "", false};
const Effect effect_Recharge_1 = {Ability::Charge, Trigger::None, Target::No, 3, 0, 1,
                                  "Your ritual gains 3 charges", "", false};
const Effect effect_Disenchant_1 = {Ability::Disenchant, Trigger::None, Target::Yes, 0, 0, 1,
                                    "Destroy the top enchantment on target minion", "", false};
const Effect effect_RaiseDead_1 = {Ability::Resurrect, Trigger::None, Target::No, 0, 0, 1,
                                   "Resurrect the top minion in your graveyard", "", false};
const Effect effect_Blizzard_1 = {Ability::AtkDef, Trigger::None, Target::No, 0, -2, 3,
                                "Deal 2 damage to all minions", "", false};
const Effect effect_GiantStrength_1 = {Ability::AtkDef, Trigger::None, Target::Yes, 2, 2, 0,
                                       "", "", false};
const Effect effect_MagicFatigue_1 = {Ability::MoreCost, Trigger::None, Target::Yes, 2, 0, 0,
                                      "Enchanted minion's activated ability costs 2 more", "",false};
const Effect effect_Silence_1 = {Ability::Silence, Trigger::None, Target::Yes, 0, 0, 0,
                                 "Enchanted minion cannot use abilities", "", false};
const Effect effect_DarkRitual_1 = {Ability::HealthMana, Trigger::OwnStart, Target::Yes, 0, 1, 1,
                                    "At the start of your turn, gain 1 mana", "", false};
const Effect effect_AuraofPower_1 = {Ability::AtkDef, Trigger::OwnSummon, Target::Yes, 1, 1, 1,
                                     "Whenever a minion enters play under your control, it gains +1/+1",
                                     "", false};
const Effect effect_Standstill_1 = {Ability::Destory, Trigger::Summon, Target::Yes, 0, 0, 2,
                                    "Whenever a minion enters play, destroy it", "", false};



//minions
const Minion EmptyMinion = {"", "Minion", 0, {effect_none}, 0, 0};
const Minion AirElemental = {"Air Elemental", "Minion", 0, {effect_none}, 1, 1};
const Minion EarthElemental = {"Earth Elemental", "Minion", 3, {effect_none}, 4, 4};
const Minion FireElemental = {"Fire Elemental", "Minion", 2, {effect_FireElemental_1}, 2, 2};
const Minion PotionSeller = {"Potion Seller", "Minion", 2, {effect_PotionSeller_1}, 1, 3};
const Minion NovicePyromancer = {"Novice Pyromancer", "Minion", 1, {effect_NovicePyromancer_1}, 0, 1};
const Minion ApprenticeSummoner = {"Apprentice Summoner", "Minion", 1, {effect_ApprenticeSummoner_1}, 1, 1};
const Minion MasterSummoner = {"Master Summoner", "Minion", 3, {effect_MasterSummoner_1}, 2, 3};


//spells
const Spell EmptySpell = {"", "Spell", 0, {effect_none}};
const Spell Banish = {"Banish", "Spell", 0 , {effect_Banish_1}};
const Spell Unsummon = {"Unsummon", "Spell", 0, {effect_Unsummon_1}};
const Spell Recharge = {"Recharge", "Spell", 0, {effect_Recharge_1}};
const Spell Disenchant = {"Disenchant", "Spell", 0, {effect_Disenchant_1}};
const Spell RaiseDead = {"Raise Dead", "Spell", 0, {effect_RaiseDead_1}};
const Spell Blizzard = {"Blizzard", "Spell", 0, {effect_Blizzard_1}};

//enchantments
const Enchantment EmptyEnchantment = {"", "Enchantment", 0, {effect_none}};
const Enchantment GiantStrength = {"Giant Strength", "Enchantment", 1, {effect_GiantStrength_1}};
const Enchantment MagicFatigue = {"Magic Fatigue", "Enchantment", 0, {effect_MagicFatigue_1}};
const Enchantment Silence = {"Silence", "Enchantment", 1, {effect_Silence_1}};

//ritual
const Ritual EmptyRitual = {"", "Ritual", 0, {effect_none}, 0};
const Ritual DarkRitual = {"Dark Ritual", "Ritual", 0, {effect_DarkRitual_1}, 5};
const Ritual AuraofPower = {"Aura of Power", "Ritual", 1, {effect_AuraofPower_1}, 4};
const Ritual Standstill = {"Standstill", "Ritual", 3, {effect_Standstill_1}, 4};
