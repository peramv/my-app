#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_right_to_cancel_notallwd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_right_to_cancel_notallwd() { }
		~CIFast_IFast_ifastcbo_err_right_to_cancel_notallwd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIGHT_TO_CANCEL_NOTALLWD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reversal Code Not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de renversement non autorisé")); }

        // Actions
	};
}



