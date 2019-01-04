#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_lsif_redemption_not_enough_units_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_lsif_redemption_not_enough_units_available() { }
		~CIFast_IFast_ifastcbo_warn_lsif_redemption_not_enough_units_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LSIF_REDEMPTION_NOT_ENOUGH_UNITS_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not enough units available to redeem the LSIF fund %FUND%, class %CLASS%, on %DATE%. LSIF units available: %AVAL%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Not enough units available to redeem the LSIF fund %FUND%, class %CLASS%, on %DATE%. LSIF units available: %AVAL%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités disponibles insuffisantes pour le rachat du fonds FIT %FUND% et de la classe %CLASS% en date du %DATE%. Unités FIT disponibles : %AVAL%")); }

        // Actions
	};
}



