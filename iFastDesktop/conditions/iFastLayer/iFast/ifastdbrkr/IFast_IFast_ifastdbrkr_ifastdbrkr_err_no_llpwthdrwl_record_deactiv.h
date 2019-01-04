#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_llpwthdrwl_record_deactiv : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_llpwthdrwl_record_deactiv() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_no_llpwthdrwl_record_deactiv() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_NO_LLPWTHDRWL_RECORD_DEACTIV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot find LLPWthdrwl record to de-activate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot find LLPWthdrwl record to de-activate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver un enregistrement de retrait REEP à désactiver.")); }

        // Actions
	};
}



