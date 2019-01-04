#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trustee_entity_should_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trustee_entity_should_be_setup() { }
		~CIFast_IFast_ifastcbo_err_trustee_entity_should_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRUSTEE_ENTITY_SHOULD_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trustee Entity should be setup for this Account Type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Trustee Entity should be setup for this Accpunt Type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Treuhänder-Objekt sollte für diese Kontoart erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse entidad Fideicomisaria para este tipo de cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fiduciaire doit être créé pour ce type de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid trustee moet worden ingesteld voor dit accounttype")); }

        // Actions
	};
}



