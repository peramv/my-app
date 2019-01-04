#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_review_detail_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_review_detail_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_account_review_detail_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_REVIEW_DETAIL_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Review Detail not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Überprüfungsdetail nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el detalle de revisión de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Détails de révision du compte introuvables")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Detail accountherziening is niet gevonden")); }

        // Actions
	};
}



