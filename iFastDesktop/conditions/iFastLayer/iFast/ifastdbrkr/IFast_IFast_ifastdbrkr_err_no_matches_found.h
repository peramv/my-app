#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_matches_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_matches_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_matches_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_MATCHES_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No matches found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune correspondance n'a ete trouvee")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Übereinstimmungen gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron coincidencias")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune correspondance n'a été trouvée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen overeenkomsten gevonden")); }

        // Actions
	};
}



