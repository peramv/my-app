#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_benef_wrong_relate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_benef_wrong_relate() { }
		~CIFast_IFast_ifastcbo_err_benef_wrong_relate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEF_WRONG_RELATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary wrong relationship to owner.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Begünstigte steht in einer falschen Beziehung zum Eigentümer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Vínculo incorrecto de beneficiario con el propietario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La relation du bénéficiare avec le titulaire est incorrecte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begunstigde heeft een verkeerde relatie met eigenaar")); }

        // Actions
	};
}



