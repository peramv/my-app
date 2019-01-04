#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_designated_instit_entity_should_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_designated_instit_entity_should_be_setup() { }
		~CIFast_IFast_ifastcbo_err_resp_designated_instit_entity_should_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_DESIGNATED_INSTIT_ENTITY_SHOULD_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP Designated Institution Entity should be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("RESP Designated Institution Entity should be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("RESP-Bezeichnetes-Institut-Objekt sollte erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Institución designada RESP")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'institution désignée REEE doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid RESP-bestemmingsinstelling moet worden ingesteld")); }

        // Actions
	};
}



