#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_user_maturity_date_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_user_maturity_date_empty() { }
		~CIFast_IFast_ifastcbo_err_user_maturity_date_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_USER_MATURITY_DATE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User Maturity Date cannot be blank when Maturity Date type is User Defined.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User Maturity Date cannot be blank when Maturity Date type is User Defined.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer-Fälligkeitsdatum darf nicht leer sein, wenn das Fälligkeitsdatum benutzerdefiniert ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento del usuario no puede estar en blanco cuando el tipo de fecha de vencimiento es definido por el usuario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Date d'échéance de l'utilisateur doit être rempli lorsque le type de date d'échéance est défini par l'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum gebruiker kan niet leeg zijn als type vervaldatum door de gebruiker is gedefinieerd")); }

        // Actions
	};
}



