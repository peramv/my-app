#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_change_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_change_tax_type() { }
		~CIFast_IFast_ifastcbo_err_cannot_change_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_CHANGE_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot change tax type to/from RESP or RESPF.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot change tax type to/from RESP or RESPF.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart kann nicht in/von RESP oder RESPF geändert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede cambiar el tipo tributario a/de RESP o RESPF")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de changer le type d'imposition vers/de REEE ou REEE familial.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype kan niet in/van RESP of RESPF worden gewijzigd")); }

        // Actions
	};
}



