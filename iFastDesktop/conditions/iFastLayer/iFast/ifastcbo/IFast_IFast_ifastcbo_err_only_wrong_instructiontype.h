#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_wrong_instructiontype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_wrong_instructiontype() { }
		~CIFast_IFast_ifastcbo_err_only_wrong_instructiontype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_WRONG_INSTRUCTIONTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Maturity/Interest instruction can be created for this Fund/Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seules les instructions à l'échéance/d'intérêt peuvent être créées pour ce fonds/cette classe.")); }

        // Actions
	};
}



