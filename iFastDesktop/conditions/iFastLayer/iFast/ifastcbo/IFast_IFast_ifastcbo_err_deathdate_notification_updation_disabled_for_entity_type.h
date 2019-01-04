#pragma once

#include "ConditionObject.h"

namespace CND
{
    class CIFast_IFast_ifastcbo_err_deathdate_notification_updation_disabled_for_entity_type : public CConditionObject
    {
    public:
        CIFast_IFast_ifastcbo_err_deathdate_notification_updation_disabled_for_entity_type() { }
        ~CIFast_IFast_ifastcbo_err_deathdate_notification_updation_disabled_for_entity_type() { }

    public:
        // General
        virtual DString GetConditionName() const { return DString(I_("ERR_DEATHDATE_NOTIFICATION_UPDATION_DISABLED")); }
        virtual DString GetGroupName() const { return DString(I_("iFast")); }
        virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
        virtual int GetSeverity() const { return 6; }

        // Messages
        virtual DString GetMessage_EN_US() const { return DString(I_("Date of death Notification cannot be entered for this entity type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'avis du décès ne peut être entrée pour ce type d'entité")); }

        // Actions
    };
}