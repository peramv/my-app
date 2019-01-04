#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transfer_track_has_nonoutstanding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transfer_track_has_nonoutstanding() { }
		~CIFast_IFast_ifastdbrkr_err_transfer_track_has_nonoutstanding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TRACK_HAS_NONOUTSTANDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer tracking has at least one non-outstanding item.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer tracking has at least one non-outstanding item.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfer tracking has at least one non-outstanding item.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le suivi de transfert comporte au moins un élément qui n'est pas en cours.")); }

        // Actions
	};
}



