#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_review_record_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_review_record_exists() { }
		~CIFast_IFast_ifastdbrkr_err_account_review_record_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_REVIEW_RECORD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Review Record already exists for given date/s.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Überprüfungseintrag für das angegebene Datum existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de revisión de cuenta ya existe para la fecha o fechas proporcionadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de révision du compte existe déjà pour la/les date(s) donnée(s).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record voor accountherziening bestaat al voor de opgegeven datum(s)")); }

        // Actions
	};
}



