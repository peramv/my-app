#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_month : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_month() { }
		~CIFast_IFast_ifastcbo_err_rif_month() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_MONTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one month must be turned on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins un mois doit être active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Monat muss aktiviert sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe activarse al menos un mes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un mois doit être activé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste een maand zijn aangezet")); }

        // Actions
	};
}



