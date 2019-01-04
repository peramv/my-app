#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_clan_plan_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_clan_plan_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_clan_plan_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLAN_PLAN_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Clan Plan not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Clan Plan not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Clanplan nicht verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Clan Plan no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun régime de clan disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Clan Plan is niet beschikbaar")); }

        // Actions
	};
}



