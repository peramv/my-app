#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cesg_adcesg_amount_be_returned_because_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cesg_adcesg_amount_be_returned_because_redemption() { }
		~CIFast_IFast_ifastcbo_err_cesg_adcesg_amount_be_returned_because_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CESG_ADCESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("$%PARAM_1% CESG Grant, and $%PARAM_2% ADCESG Grant, are to be returned because of this redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("SCEE $%PARAM_1% et SCEE additionnelle $%PARAM_2% doivent être remboursées en raison de ce rachat.")); }

        // Actions
	};
}



