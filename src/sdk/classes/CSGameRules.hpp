#ifndef ANIUM_CSGAMERULES_HPP
#define ANIUM_CSGAMERULES_HPP

#include "../../netvars/netvar.hpp"

class CSGameRules {
private:
    NetVar freezePeriod = NetVar("DT_CSGameRules", "m_bFreezePeriod");
    NetVar warmupPeriod = NetVar("DT_CSGameRules", "m_bWarmupPeriod");
    NetVar valveDS = NetVar("DT_CSGameRules", "m_bIsValveDS");
    NetVar bombDropped = NetVar("DT_CSGameRules", "m_bBombDropped");
    NetVar bombPlanted = NetVar("DT_CSGameRules", "m_bBombPlanted");

public:
    bool IsFreezeTime() {
        return this->freezePeriod.Get<bool>(this);
    }

    bool IsWarmup() {
        return this->warmupPeriod.Get<bool>(this);
    }

    bool IsValveDS() {
        return this->valveDS.Get<bool>(this);
    }

    bool IsBombDropped() {
        return this->bombDropped.Get<bool>(this);
    }

    bool IsBombPlanted() {
        return this->bombPlanted.Get<bool>(this);
    }

};

#endif  // ANIUM_CSGAMERULES_HPP
