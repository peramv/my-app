#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_reasoncode_rrsp_loan : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_reasoncode_rrsp_loan() { }
		~CIFast_IFast_ifastcbo_err_reasoncode_rrsp_loan() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REASONCODE_RRSP_LOAN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RRSP Loan only valid for account with Tax type RRSP or external RRSP.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RRSP Loan only valid for account with Tax type RRSP or external RRSP.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RRSP-Anleihe nur für Konto mit Steuerart RRSP oder externer RRSP gültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Préstamo RRSP sólo es válido para una cuenta con tipo tributario RRSP o RRSP externo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le prêt REER n'est valide que pour un compte dont le type d'imposition est REER ou REER externe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("RRSP-lening is alleen geldig voor account met belastingtype RRSP of externe RRSP")); }

        // Actions
	};
}



