#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_addresses_for_this_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_addresses_for_this_shareholder() { }
		~CIFast_IFast_ifastcbo_err_no_addresses_for_this_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ADDRESSES_FOR_THIS_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The current shareholder doesn't have an address.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'actionnaire actif n'a pas d'adresse")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der aktuelle Aktionär hat keine Adresse.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El accionista actual no tiene ninguna dirección")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'actionnaire actuel n'a pas d'adresse.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De huidige aandeelhouder heeft geen enkel adres")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Enter at least one.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Saisissez au moins un actionnaire.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie mindestens eine ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Enter at least one.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Saisissez-en au moins une.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voer er ten minste één in")); }
	};
}



