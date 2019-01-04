#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_net : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_net() { }
		~CIFast_IFast_ifastcbo_err_invalid_net() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_NET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net is not allowed for an allocated systematic.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Net is not allowed for an allocated systematic.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Netto ist nicht erlaubt für einen  zugewiesenen Systematischen Plan. Bitte wählen Sie Brutto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite Neto para un plan sistemática asignado. Por favor seleccione Bruto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le net n'est pas autorisé pour les systématiques réparties.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto is niet toegestaan voor een gealloceerd systeemplan. Selecteer bruto")); }

        // Actions
	};
}



