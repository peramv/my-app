#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_resp_account_information : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_resp_account_information() { }
		~CIFast_IFast_ifastdbrkr_err_no_resp_account_information() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RESP_ACCOUNT_INFORMATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No RESP Account Information.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No RESP Account Information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine RESP-Kontoinformationen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información de la cuenta RESP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur le compte REEE")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen RESP-accountgegevens")); }

        // Actions
	};
}



