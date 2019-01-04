#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_trans_detl_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_trans_detl_not_found() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_trans_detl_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_TRANS_DETL_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot find Transaction Detail record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot find Transaction Detail record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'enregistrement des détails de la transaction.")); }

        // Actions
	};
}



