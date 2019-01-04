#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_acctholder_dofbirth : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_acctholder_dofbirth() { }
		~CIFast_IFast_ifastcbo_err_missing_acctholder_dofbirth() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_ACCTHOLDER_DOFBIRTH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountholder's Date of Birth is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Geburtsdatum des Kontoinhabers fehlt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta la fecha de nacimiento del titular de la cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du titulaire du fonds est manquante.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geboortedatum accounthouder ontbreekt")); }

        // Actions
	};
}



