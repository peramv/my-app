#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_qualified : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_qualified() { }
		~CIFast_IFast_ifastcbo_err_rif_qualified() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_QUALIFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Qualified must be \"No\".")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Qualified must be \"No\".")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("“Berechtigt” muss auf \"Nein\" stehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Calificado debe ser \"No\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le qualifié doit être Non.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gekwalificeerd moet 'Nee' zijn")); }

        // Actions
	};
}



