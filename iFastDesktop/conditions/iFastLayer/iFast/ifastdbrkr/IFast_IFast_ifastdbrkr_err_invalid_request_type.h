#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_request_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_request_type() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_request_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_REQUEST_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid request type when searching for broker.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid request type when searching for broker.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Nachfrage-Typ bei der Suche nach einem Broker.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de solicitud no válido durante la búsqueda del corredor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de requête invalide lors de la recherche du courtier")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig opdrachttype tijdens zoeken naar makelaar")); }

        // Actions
	};
}



