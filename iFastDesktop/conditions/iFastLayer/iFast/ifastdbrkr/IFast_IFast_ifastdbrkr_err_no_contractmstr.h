#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_contractmstr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_contractmstr() { }
		~CIFast_IFast_ifastdbrkr_err_no_contractmstr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_CONTRACTMSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Contract-Mstr record found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No Contract-Mstr record found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Contract-Mstr-Eintrag nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro Contract-Mstr")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement de l'original du contrat n'a été trouvé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Contract-Mstr is niet gevonden")); }

        // Actions
	};
}



