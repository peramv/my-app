#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctholder_dofbirth_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctholder_dofbirth_missing() { }
		~CIFast_IFast_ifastcbo_err_acctholder_dofbirth_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTHOLDER_DOFBIRTH_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account owner date of birth is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account owner date of birth is missing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account owner date of birth is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de naissance du titulaire du compte est manquante.")); }

        // Actions
	};
}



