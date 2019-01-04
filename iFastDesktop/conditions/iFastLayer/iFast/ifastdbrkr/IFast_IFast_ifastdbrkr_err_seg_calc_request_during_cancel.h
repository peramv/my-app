#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_seg_calc_request_during_cancel : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_seg_calc_request_during_cancel() { }
		~CIFast_IFast_ifastdbrkr_err_seg_calc_request_during_cancel() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEG_CALC_REQUEST_DURING_CANCEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error in Seg-Calc-Request during Cancellation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Error in Seg-Calc-Request during Cancellation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur dans la demande de calcul de fonds distincts lors de l'annulation")); }

        // Actions
	};
}



