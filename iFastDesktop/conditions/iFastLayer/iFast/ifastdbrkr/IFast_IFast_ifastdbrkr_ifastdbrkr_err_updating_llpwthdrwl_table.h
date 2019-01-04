#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_updating_llpwthdrwl_table : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_updating_llpwthdrwl_table() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_updating_llpwthdrwl_table() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_UPDATING_LLPWTHDRWL_TABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown error updating LLPWthdrwl Table.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unknown error updating LLPWthdrwl Table.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur inconnue lors de la mise à jour du tableau de retrait REEP")); }

        // Actions
	};
}



