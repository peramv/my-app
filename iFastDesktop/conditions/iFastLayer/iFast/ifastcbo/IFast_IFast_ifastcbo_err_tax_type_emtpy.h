#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_emtpy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_emtpy() { }
		~CIFast_IFast_ifastcbo_err_tax_type_emtpy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_EMTPY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax type cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Type de taxe doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Type d'imposition doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype kan niet leeg zijn")); }

        // Actions
	};
}



