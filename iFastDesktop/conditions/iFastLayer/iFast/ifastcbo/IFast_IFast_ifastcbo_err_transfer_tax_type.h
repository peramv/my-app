#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_tax_type() { }
		~CIFast_IFast_ifastcbo_err_transfer_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfers are not allowed between tax type %FROMTAX% to tax type %TOTAX%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Transfers are not allowed between the tax types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transfers zwischen Steuerarten sind nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias entre los tipos tributarios")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transferts ne sont pas autorisés du type d'imposition %FROMTAX% au type d'impôt %TOTAX%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Overdrachten zijn niet toegestaan tussen de belastingtypes")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please select another account number")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please select another account number")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie bitte eine andere Kontonummer")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please select another account number")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez sélectionner un autre numéro de compte.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("selecteer een ander accountnummer")); }
	};
}



