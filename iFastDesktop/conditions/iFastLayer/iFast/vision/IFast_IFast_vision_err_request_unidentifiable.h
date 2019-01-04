#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_request_unidentifiable : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_request_unidentifiable() { }
		~CIFast_IFast_vision_err_request_unidentifiable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REQUEST_UNIDENTIFIABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The request cannot be identified by the: %service%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The request cannot be identified by the: %service%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Anfrage kann von %service% nicht identifiziert werden von:")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud no puede identificarse según el: %service%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande ne peut être identifiée par le : %service%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De aanvraag kan niet worden geïdentificeerd door de: %service%")); }

        // Actions
	};
}



