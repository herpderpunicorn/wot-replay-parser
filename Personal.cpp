#include "Personal.hpp"

#include <json/json.h>

namespace WotReplayParser {

void Personal::parse(Json::Value root) {
    spotted = root.get("spotted", Json::nullValue).asUInt();
    repair = root.get("repair", Json::nullValue).asUInt();
    xpPenalty = root.get("xpPenalty", Json::nullValue).asUInt();
    creditsPenalty = root.get("creditsPenalty", Json::nullValue).asUInt();
    vehTypeLockTime = root.get("vehTypeLockTime", Json::nullValue).asUInt();
    damageAssistedTrack = root.get("damageAssistedTrack", Json::nullValue).asUInt();
    killerID = root.get("killerID", Json::nullValue).asUInt();
    originalFreeXP = root.get("originalFreeXP", Json::nullValue).asUInt();
    directTeamHits = root.get("directTeamHits", Json::nullValue).asUInt();
    damageDealt = root.get("damageDealt", Json::nullValue).asUInt();
    creditsToDraw = root.get("creditsToDraw", Json::nullValue).asUInt();
    movingAvgDamage = root.get("movingAvgDamage", Json::nullValue).asUInt();
    piercingsReceived = root.get("piercingsReceived", Json::nullValue).asUInt();
    sniperDamageDealt = root.get("sniperDamageDealt", Json::nullValue).asUInt();
    premiumCreditsFactor10 = root.get("premiumCreditsFactor10", Json::nullValue).asUInt();
    damageAssistedRadio = root.get("damageAssistedRadio", Json::nullValue).asUInt();
    orderXP = root.get("orderXP", Json::nullValue).asUInt();
    marksOnGun = root.get("marksOnGun", Json::nullValue).asUInt();
    piercings = root.get("piercings", Json::nullValue).asUInt();
    damageBlockedByArmor = root.get("damageBlockedByArmor", Json::nullValue).asUInt();
    premiumXPFactor10 = root.get("premiumXPFactor10", Json::nullValue).asUInt();
    serviceProviderID = root.get("serviceProviderID", Json::nullValue).asUInt();
    xp = root.get("xp", Json::nullValue).asUInt();
    droppedCapturePoints = root.get("droppedCapturePoints", Json::nullValue).asUInt();
    creditsContributionIn = root.get("creditsContributionIn", Json::nullValue).asUInt();
    eventFreeXP = root.get("eventFreeXP", Json::nullValue).asUInt();
    directHitsReceived = root.get("directHitsReceived", Json::nullValue).asUInt();
    autoRepairCost = root.get("autoRepairCost", Json::nullValue).asUInt();
    typeCompDescr = root.get("typeCompDescr", Json::nullValue).asUInt();
    explosionHitsReceived = root.get("explosionHitsReceived", Json::nullValue).asUInt();
    achievementXP = root.get("achievementXP", Json::nullValue).asUInt();
    deathReason = root.get("deathReason", Json::nullValue).asInt();
    capturePoints = root.get("capturePoints", Json::nullValue).asUInt();
    eventTMenXP = root.get("eventTMenXP", Json::nullValue).asUInt();
    aogasFactor10 = root.get("aogasFactor10", Json::nullValue).asUInt();

    Json::Value histAmmoCostRoot = root.get("histAmmoCost", Json::nullValue);
    if (histAmmoCostRoot.isArray() && histAmmoCostRoot.size() >= 2) {
        histAmmoCost.credits = histAmmoCostRoot[0].asUInt();
        histAmmoCost.gold = histAmmoCostRoot[1].asUInt();
    }

    orderTMenXP = root.get("orderTMenXP", Json::nullValue).asUInt();
    eventCredits = root.get("eventCredits", Json::nullValue).asUInt();
    health = root.get("health", Json::nullValue).asUInt();

    Json::Value detailsRoot = root.get("details", Json::nullValue);
    if (detailsRoot.size() > 0) {
        for (auto it = detailsRoot.begin(); it != detailsRoot.end(); it++) {
            std::string key(it.memberName());
            Json::Value detailRoot = detailsRoot.get(key, Json::nullValue);
            Detail detail;
            detail.spotted = detailRoot.get("spotted", Json::nullValue).asUInt();
            detail.crits = detailRoot.get("crits", Json::nullValue).asUInt();
            detail.damageAssistedTrack = detailRoot.get("damageAssistedTrack", Json::nullValue).asUInt();
            detail.fire = detailRoot.get("fire", Json::nullValue).asUInt();
            detail.deathReason = detailRoot.get("deathReason", Json::nullValue).asInt();
            detail.damageDealt = detailRoot.get("damageDealt", Json::nullValue).asUInt();
            detail.damageAssistedRadio = detailRoot.get("damageAssistedRadio", Json::nullValue).asUInt();
            detail.piercings = detailRoot.get("piercings", Json::nullValue).asUInt();
            detail.explosionHits = detailRoot.get("explosionHits", Json::nullValue).asUInt();
            detail.directHits = detailRoot.get("directHits", Json::nullValue).asUInt();
            details.insert(std::make_pair(key, detail));
        }
    }

    isPrematureLeave = root.get("isPrematureLeave", Json::nullValue).asBool();
    orderCredits = root.get("orderCredits", Json::nullValue).asUInt();
    damageRating = root.get("damageRating", Json::nullValue).asUInt();
    achievementCredits = root.get("achievementCredits", Json::nullValue).asUInt();

    Json::Value achievementsRoot = root.get("achivements", Json::nullValue);
    if (achievementsRoot.isArray()) {
        for (unsigned int i = 0; i < achievementsRoot.size(); i++) {
            achievements.push_back(achievementsRoot[i].asUInt());
        }
    }

    orderFreeXP = root.get("orderFreeXP", Json::nullValue).asUInt();
    isPremium = root.get("isPremium", Json::nullValue).asBool();
    mileage = root.get("mileage", Json::nullValue).asUInt();
    freeXP = root.get("freeXP", Json::nullValue).asUInt();
    shots = root.get("shots", Json::nullValue).asUInt();
    kills = root.get("kills", Json::nullValue).asUInt();
    fortResource = root.get("fortResource", Json::nullValue).asUInt();

    Json::Value dossierPopUpsRoot = root.get("dossierPopUps", Json::nullValue);
    if (dossierPopUpsRoot.isArray()) {
        for (unsigned int i = 0; i < dossierPopUpsRoot.size(); i++) {
            if (dossierPopUpsRoot[i].isArray()) {
                std::vector<uint32_t> inner(dossierPopUpsRoot[i].size());
                for (unsigned int j = 0; j < dossierPopUpsRoot[i].size(); j++) {
                    inner.push_back(dossierPopUpsRoot[i][j].asUInt());
                }
                dossierPopUps.push_back(inner);
            }
        }
    }

    damaged = root.get("damaged", Json::nullValue).asUInt();
    tdamageDealt = root.get("tdamageDealt", Json::nullValue).asUInt();
    credits = root.get("credits", Json::nullValue).asUInt();
    eventGold = root.get("eventGold", Json::nullValue).asUInt();
    igrXPFactor10 = root.get("igrXPFactor10", Json::nullValue).asUInt();
    markOfMastery = root.get("markOfMastery", Json::nullValue).asUInt();
    noDamageDirectHitsReceived = root.get("noDamageDirectHitsReceived", Json::nullValue).asUInt();

    Json::Value autoEquipCostRoot = root.get("autoEquipCost", Json::nullValue);
    if (autoEquipCostRoot.isArray() && autoEquipCostRoot.size() >= 2) {
        autoEquipCost.credits = autoEquipCostRoot[0].asUInt();
        autoEquipCost.gold = autoEquipCostRoot[1].asUInt();
    }

    gold = root.get("gold", Json::nullValue).asUInt();
    accountDBID = root.get("accountDBID", Json::nullValue).asUInt();
    isTeamKiller = root.get("isTeamKiller", Json::nullValue).asBool();
    tmenXP = root.get("tmenXP", Json::nullValue).asUInt();
    eventXP = root.get("eventXP", Json::nullValue).asUInt();
    tkills = root.get("tkills", Json::nullValue).asUInt();
    potentialDamageReceived = root.get("potentialDamageReceived", Json::nullValue).asUInt();
    damageReceived = root.get("damageReceived", Json::nullValue).asUInt();
    orderFortResource = root.get("orderFortResource", Json::nullValue).asUInt();

    Json::Value autoLoadCostRoot = root.get("autoLoadCost", Json::nullValue);
    if (autoEquipCostRoot.isArray() && autoEquipCostRoot.size() >= 2) {
        autoLoadCost.credits = autoLoadCostRoot[0].asUInt();
        autoLoadCost.gold = autoLoadCostRoot[1].asUInt();
    }

    originalCredits = root.get("originalCredits", Json::nullValue).asUInt();
    dailyXPFactor10 = root.get("dailyXPFactor10", Json::nullValue).asUInt();
    explosionHits = root.get("explosionHits", Json::nullValue).asUInt();
    team = root.get("team", Json::nullValue).asUInt();
    originalXP = root.get("originalXP", Json::nullValue).asUInt();
    lifeTime = root.get("lifeTime", Json::nullValue).asUInt();

    Json::Value questsProgressRoot = root.get("questsProgress", Json::nullValue);
    if (questsProgressRoot.size() > 0) {
        for (auto it = questsProgressRoot.begin(); it != questsProgressRoot.end(); it++) {
            std::string key(it.memberName());
            Json::Value questRoot = questsProgressRoot.get(key, Json::nullValue);
            QuestProgress quest;
            questsProgress.insert(std::make_pair(key, quest));
        }
    }

    creditsContributionOut = root.get("creditsContributionOut", Json::nullValue).asUInt();
    achievementFreeXP = root.get("achievementFreeXP", Json::nullValue).asUInt();
    directHits = root.get("directHits", Json::nullValue).asUInt();
}

}
