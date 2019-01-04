#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trxr_cancel_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trxr_cancel_failed() { }
		~CIFast_IFast_ifastdbrkr_err_trxr_cancel_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRXR_CANCEL_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Both sides of Transfer/Exchange must be either settled or unsettled in order for trade to be cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les deux parties du transfert/de l'échange doivent être réglées ou non réglées pour que la transaction puisse être annulée.")); }

        // Actions
	};
}



