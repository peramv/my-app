#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancel_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancel_failed() { }
		~CIFast_IFast_ifastdbrkr_err_cancel_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCEL_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cancellation error - Trade cannot be cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'annulation — la transaction ne peut pas être annulée.")); }

        // Actions
	};
}



