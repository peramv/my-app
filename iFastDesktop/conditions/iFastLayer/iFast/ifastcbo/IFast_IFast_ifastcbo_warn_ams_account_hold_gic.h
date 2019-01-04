#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ams_account_hold_gic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ams_account_hold_gic() { }
		~CIFast_IFast_ifastcbo_warn_ams_account_hold_gic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMS_ACCOUNT_HOLD_GIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS portfolio can not be set up for the account has ever held GIC fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS portfolio can not be set up for the account has ever held GIC fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS portfolio can not be set up for the account has ever held GIC fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille de service de gestion de portefeuille ne peut être réglé parce que le compte a déjà comporté un fonds CPG.")); }

        // Actions
	};
}



