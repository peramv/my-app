#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exempt_holding_excess : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exempt_holding_excess() { }
		~CIFast_IFast_ifastcbo_err_exempt_holding_excess() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXEMPT_HOLDING_EXCESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exempt - Holding excess is System generated only.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Exempt - Holding excess is System generated only.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("“4” ausgenommen – Beteiligungs-Überschreitung ist nur systemgeneriert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("4' Exempt  - Holding excess is System generated only")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Exemption – l'excédent de portefeuille n'est généré que par le système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("4' Exempt  - Holding excess is System generated only")); }

        // Actions
	};
}



