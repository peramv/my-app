#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_irrevocable_not_updatable_for_acct_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_irrevocable_not_updatable_for_acct_type() { }
		~CIFast_IFast_ifastcbo_err_irrevocable_not_updatable_for_acct_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IRREVOCABLE_NOT_UPDATABLE_FOR_ACCT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Irrevocable field cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Irrevocable doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Endgültiges Feld darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo irrevocable no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ irrévocable doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld Onherroepelijk kan niet leeg zijn")); }

        // Actions
	};
}



