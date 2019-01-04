#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pac_swp_units_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pac_swp_units_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_pac_swp_units_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAC_SWP_UNITS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Units is not allowed for an allocated systematic record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Units is not allowed for an allocated systematic record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("\"Anteile\" ist für einen zugewiesenen Systematischer Plan-Eintrag nicht zulässig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten unidades para un registro de plan sistemático asignado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les unités ne sont pas autorisées pour un enregistrement systématique réparti.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheden zijn niet toegestaan voor gealloceerd systeemplanrecord")); }

        // Actions
	};
}



