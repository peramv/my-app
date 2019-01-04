#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_itf_entity_setup_for_non_itf : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_itf_entity_setup_for_non_itf() { }
		~CIFast_IFast_ifastcbo_err_itf_entity_setup_for_non_itf() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ITF_ENTITY_SETUP_FOR_NON_ITF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ITF entity defined for non-ITF account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("ITF-Objekt definiert für ein Nicht-ITF-Konto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entidad ITF definida para cuenta no ITF.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité EFP est définie pour un compte qui n'est pas EFP.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("ITF-eenheid is gedefinieerd voor niet-ITF-account")); }

        // Actions
	};
}



