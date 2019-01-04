#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_criteria_all_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_criteria_all_selected() { }
		~CIFast_IFast_ifastcbo_err_criteria_all_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CRITERIA_ALL_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Criteria (%CRITERIA%) has All selected. Cannot Include more of the same type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei den Kriterien (%CRITERIA%) ist Alle ausgewählt. Mehr der gleichen Art können nicht eingeschlossen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El criterio (%CRITERIA%) tiene Todos seleccionado. No se pueden incluir más del mismo tipo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La sélection du critère (%CRITERIA%) est Tout. Impossible d'inclure plus d'éléments du même type.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor criteria (%CRITERIA%) is Alles geselecteerd. Kan niet meer van hetzelfde type bevatten")); }

        // Actions
	};
}



