#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_amount_exceed_max_limit : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_amount_exceed_max_limit() { }
		~CIFast_Infrastructure_ifastcbo_err_amount_exceed_max_limit() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_EXCEED_MAX_LIMIT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An invalid address line has been requested.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("An invalid address line has been requested.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine ungültige Adressenzeile wurde angefragt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha solicitado una línea de dirección no válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une ligne d'adresse invalide a été demandée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ongeldige adresregel opgevraagd")); }

        // Actions
	};
}



