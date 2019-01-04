#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_request_fields_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_request_fields_invalid() { }
		~CIFast_IFast_ifastdbrkr_err_request_fields_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REQUEST_FIELDS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid combination of the requested fields.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Kombination des Nachfragefeldes")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Combinación no válida de los campos solicitados")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Combinaison invalide des champs demandés")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige combinatie van de aangevraagde velden")); }

        // Actions
	};
}



