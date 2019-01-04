#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_parent_entity_should_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_parent_entity_should_be_setup() { }
		~CIFast_IFast_ifastcbo_err_parent_entity_should_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PARENT_ENTITY_SHOULD_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Parent/Legal Guardian Entity should be setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Parent/Legal Guardian Entity should be setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eltern/ Vormund-Objekt sollte erstellt sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse la entidad Padre/Tutor legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité parent/tuteur légal doit être créée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid Ouder/Wettelijke voogd moet worden ingesteld")); }

        // Actions
	};
}



