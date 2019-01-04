#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mod_acct_type_trans_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mod_acct_type_trans_exist() { }
		~CIFast_IFast_ifastcbo_err_mod_acct_type_trans_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MOD_ACCT_TYPE_TRANS_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Account type - transactions exist for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de modifier le type de compte - des transactions existent pour ce compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart kann nicht geändert werden – für dieses Konto existieren Transaktionen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar el tipo de cuenta - Existen transacciones para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier le type de compte – des transactions existent pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounttype kan niet worden gewijzigd - er zijn transacties voor dit account")); }

        // Actions
	};
}



