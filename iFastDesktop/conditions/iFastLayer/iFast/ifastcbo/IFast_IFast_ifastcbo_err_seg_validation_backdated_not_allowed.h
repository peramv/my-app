#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_seg_validation_backdated_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_seg_validation_backdated_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_seg_validation_backdated_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEG_VALIDATION_BACKDATED_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Backdated trade not allowed. Cancel all transactions on or after %TRADE_DATE% or change trade date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une transaction antidatée n'est pas autorisée. Annulez toutes les transactions de date identique ou postérieure au %TRADE_DATE% ou changez la date de transaction.")); }

        // Actions
	};
}



