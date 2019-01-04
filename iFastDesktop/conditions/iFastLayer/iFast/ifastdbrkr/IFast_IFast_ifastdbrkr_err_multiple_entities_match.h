#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_multiple_entities_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_multiple_entities_match() { }
		~CIFast_IFast_ifastdbrkr_err_multiple_entities_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ENTITIES_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Entities matched input data.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrere Objekte stimmten mit den eingegebenen Daten überein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se encontraron varias entidades coincidentes con los datos introducidos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs entités correspondent aux données saisies.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn meerdere eenheden die overeenkomen met de ingevoerde gegevens")); }

        // Actions
	};
}



