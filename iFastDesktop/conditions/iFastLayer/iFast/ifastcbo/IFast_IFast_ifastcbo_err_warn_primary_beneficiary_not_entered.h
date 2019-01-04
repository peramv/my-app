#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_primary_beneficiary_not_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_primary_beneficiary_not_entered() { }
		~CIFast_IFast_ifastcbo_err_warn_primary_beneficiary_not_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_PRIMARY_BENEFICIARY_NOT_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Primary Beneficiary was not entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Erster Begünstigter wurde nicht eingetragen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo el beneficiario principal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire au décès n'a pas été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eerste begunstigde is niet opgegeven")); }

        // Actions
	};
}



