#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nominee_invalid_for_acct_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nominee_invalid_for_acct_type() { }
		~CIFast_IFast_ifastcbo_err_nominee_invalid_for_acct_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOMINEE_INVALID_FOR_ACCT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Nominee Owner may only be set up for Nominee or Intermediary account designations.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le Proprietaire nominal (21) ne peut être defini que pour les attributions de comptes a proprietaire nominal ou intermediaire.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bevollmächtigter Eigentümer (21) kann nur für Bevollmächtigten- oder Mittler (Intermediary)-Kontobezeichnungen erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El propietario nominatario (21) sólo puede configurarse para las designaciones de cuenta de nominatario o intermediario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un propriétaire nominé ne peut être réglé que pour les comptes nominée ou intermédiaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gemachtigde eigenaar (21) kan alleen worden ingesteld voor accounttypes Gemachtigde of Tussenpersoon")); }

        // Actions
	};
}



