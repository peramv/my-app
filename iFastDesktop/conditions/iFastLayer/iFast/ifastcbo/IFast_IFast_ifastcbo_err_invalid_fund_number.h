#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fund_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fund_number() { }
		~CIFast_IFast_ifastcbo_err_invalid_fund_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUND_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund number does not exist, please select existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Fund number does not exist, please select existing one or leave it blank and select a fund and class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fondsnummer existiert nicht, bitte wählen Sie eine existierende Nummer oder lassen Sie dieses Feld frei, und wählen Sie einen Fonds und eine Klasse.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de fondo no existe, por favor seleccione uno existente o déjelo en blanco y seleccione un fondo y clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de fonds n'existe pas. Veuillez sélectionner un numéro existant ou laisser ce champ vide et sélectionner un fonds et une classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsnummer bestaat niet, selecteer een bestaand nummer of laat het veld leeg en selecteer een fonds en categorie")); }

        // Actions
	};
}



