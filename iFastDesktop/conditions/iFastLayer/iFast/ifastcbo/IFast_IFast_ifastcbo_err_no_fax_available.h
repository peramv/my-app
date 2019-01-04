#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_fax_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_fax_available() { }
		~CIFast_IFast_ifastcbo_err_no_fax_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_FAX_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fax number has not been set up for the account holder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Faxnummer wurde für den Kontoinhaber nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado el número de fax para el titular de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le télécopieu n'a pas été réglé pour le titulaire du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Faxnummer is niet ingesteld voor de accounthouder")); }

        // Actions
	};
}



