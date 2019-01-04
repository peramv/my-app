#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tofund_same_or_cash : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tofund_same_or_cash() { }
		~CIFast_IFast_ifastcbo_err_tofund_same_or_cash() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOFUND_SAME_OR_CASH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To Fund must be the same as From Fund or CASH.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("To Fund must be the same as From Fund or CASH.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("To Fund must be the same as From Fund or CASH.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds cible doit être identique au fonds source ou au champ COMPTANT.")); }

        // Actions
	};
}



