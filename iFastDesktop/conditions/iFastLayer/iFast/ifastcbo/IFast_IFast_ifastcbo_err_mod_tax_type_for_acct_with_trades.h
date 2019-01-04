#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mod_tax_type_for_acct_with_trades : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mod_tax_type_for_acct_with_trades() { }
		~CIFast_IFast_ifastcbo_err_mod_tax_type_for_acct_with_trades() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MOD_TAX_TYPE_FOR_ACCT_WITH_TRADES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Tax type - transactions exist for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de modifier le type de taxe - des transactions existent pour ce compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart kann nicht geändert werden – für dieses Konto existieren Transaktionen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar el tipo tributario - Existen transacciones para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier le type d'imposition – des transactions existent pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype kan niet worden gewijzigd - er zijn transacties voor dit account")); }

        // Actions
	};
}



