#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_print_duplicate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_print_duplicate() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_print_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_PRINT_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Slips not produced for this Tax Process.  Cannot print duplicate.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Slips not produced for this Tax Process.  Cannot print duplicate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Formular nicht für diesen Steuerprozess angelegt. Duplikat kann nicht gedruckt werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se generan comprobantes para este proceso tributario. No se puede imprimir un duplicado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les bordereaux ne sont pas produits pour ce processus d'imposition. Impossible d'imprimer une copie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen strookjes gemaakt voor deze belastingverwerking. Kan duplicaat niet afdrukken")); }

        // Actions
	};
}



