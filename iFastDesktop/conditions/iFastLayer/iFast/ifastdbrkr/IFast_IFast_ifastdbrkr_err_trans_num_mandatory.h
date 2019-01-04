#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trans_num_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trans_num_mandatory() { }
		~CIFast_IFast_ifastdbrkr_err_trans_num_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANS_NUM_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer Number is mandatory in request.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfer Number is mandatory in request.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Transfer Number is mandatory in request.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de transfert est requis dans la demande.")); }

        // Actions
	};
}



