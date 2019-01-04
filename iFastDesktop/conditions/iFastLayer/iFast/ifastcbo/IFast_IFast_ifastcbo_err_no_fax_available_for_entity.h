#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_fax_available_for_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_fax_available_for_entity() { }
		~CIFast_IFast_ifastcbo_err_no_fax_available_for_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_FAX_AVAILABLE_FOR_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fax number has not been set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Faxnummer wurde nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el número de fax.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de télécopieur n'a pas été réglé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Faxnummer is niet ingesteld")); }

        // Actions
	};
}



