#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_llp_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_llp_error() { }
		~CIFast_IFast_ifastdbrkr_err_llp_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LLP_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LLP Error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("LLP-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error LLP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur REEP")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("LLP-fout")); }

        // Actions
	};
}



