#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_afc_match_to_afc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_afc_match_to_afc() { }
		~CIFast_IFast_ifastcbo_err_from_afc_match_to_afc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_AFC_MATCH_TO_AFC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer from Account Fund and Class to identical Account Fund and Class is not permitted.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfer from Account Fund and Class to identical Account Fund and Class is not permitted.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Transfer von Konto-Fonds und Klasse zu einem identischen Konto-Fonds und Klasse ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten las transferencias entre cuentas y clases de fondos idénticas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert du fonds et de la classe du compte vers un fonds et une classe de compte identiques n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdracht van accountfonds en categorie naar identiek accountfonds en categorie is niet toegestaan")); }

        // Actions
	};
}



