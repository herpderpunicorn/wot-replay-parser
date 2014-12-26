#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <map>

#include "json/json-forwards.h"

namespace WotReplayParser {

class Personal {
public:
    struct AmmoCostHistory {
        uint32_t credits;
        uint32_t gold;
    };
    struct AutoEquipCost {
        uint32_t credits;
        uint32_t gold;
    };
    struct AutoLoadCost {
        uint32_t credits;
        uint32_t gold;
    };
    struct QuestProgress {
        // Unknown format
        /** Something like this
        * "questsProgress": {"EU_05-08_Jul_2014_q4": [null, {"bonusCount": 11}, {"bonusCount": 12}]}
        * or
        * "questsProgress": {"EU_08-12_Jul_2014_q1": [null, {"bonusCount": 2, "damageDealt": 3684}, {"bonusCount": 3, "damageDealt": 406}], "EU_01-01_Aug_2014_q2": [null, {"bonusCount": 0, "vehicleKills": 23}, {"bonusCount": 0, "vehicleKills": 24}]}
        */
    };
    struct Detail {
        uint32_t spotted;
        uint32_t crits;
        uint32_t damageAssistedTrack;
        uint32_t fire;
        int32_t  deathReason;
        uint32_t damageDealt;
        uint32_t damageAssistedRadio;
        uint32_t piercings;
        uint32_t explosionHits;
        uint32_t directHits;
    };

    Personal() = default;

    ~Personal() = default;

    void parse(Json::Value root);

private:
    uint32_t                             spotted;
    uint32_t                             repair;
    uint32_t                             xpPenalty;
    uint32_t                             creditsPenalty;
    uint32_t                             vehTypeLockTime;
    uint32_t                             damageAssistedTrack;
    uint32_t                             killerID;
    uint32_t                             originalFreeXP;
    uint32_t                             directTeamHits;
    uint32_t                             damageDealt;
    uint32_t                             creditsToDraw;
    uint32_t                             movingAvgDamage;
    uint32_t                             piercingsReceived;
    uint32_t                             sniperDamageDealt;
    uint32_t                             premiumCreditsFactor10;
    uint32_t                             damageAssistedRadio;
    uint32_t                             orderXP;
    uint32_t                             marksOnGun;
    uint32_t                             piercings;
    uint32_t                             damageBlockedByArmor;
    uint32_t                             premiumXPFactor10;
    uint32_t                             serviceProviderID;
    uint32_t                             xp;
    uint32_t                             droppedCapturePoints;
    uint32_t                             creditsContributionIn;
    uint32_t                             eventFreeXP;
    uint32_t                             directHitsReceived;
    uint32_t                             autoRepairCost;
    uint32_t                             typeCompDescr;
    uint32_t                             explosionHitsReceived;
    uint32_t                             achievementXP;
    int32_t                              deathReason;
    uint32_t                             capturePoints;
    uint32_t                             eventTMenXP;
    uint32_t                             aogasFactor10;
    AmmoCostHistory                      histAmmoCost;
    uint32_t                             orderTMenXP;
    uint32_t                             eventCredits;
    uint32_t                             health;
    std::map<std::string, Detail>        details;
    bool                                 isPrematureLeave;
    uint32_t                             orderCredits;
    uint32_t                             damageRating;
    uint32_t                             achievementCredits;
    std::vector<uint32_t>                achievements;
    uint32_t                             orderFreeXP;
    bool                                 isPremium;
    uint32_t                             mileage;
    uint32_t                             freeXP;
    uint32_t                             shots;
    uint32_t                             kills;
    uint32_t                             fortResource;
    std::vector<std::vector<uint32_t>>   dossierPopUps;
    uint32_t                             damaged;
    uint32_t                             tdamageDealt;
    uint32_t                             credits;
    uint32_t                             eventGold;
    uint32_t                             igrXPFactor10;
    uint32_t                             markOfMastery;
    uint32_t                             noDamageDirectHitsReceived;
    AutoEquipCost                        autoEquipCost;
    uint32_t                             gold;
    uint32_t                             accountDBID;
    bool                                 isTeamKiller;
    uint32_t                             tmenXP;
    uint32_t                             eventXP;
    uint32_t                             tkills;
    uint32_t                             potentialDamageReceived;
    uint32_t                             damageReceived;
    uint32_t                             orderFortResource;
    AutoLoadCost                         autoLoadCost;
    uint32_t                             originalCredits;
    uint32_t                             dailyXPFactor10;
    uint32_t                             explosionHits;
    uint32_t                             team;
    uint32_t                             originalXP;
    uint32_t                             lifeTime;
    std::map<std::string, QuestProgress> questsProgress;
    uint32_t                             creditsContributionOut;
    uint32_t                             achievementFreeXP;
    uint32_t                             directHits;
};

}
